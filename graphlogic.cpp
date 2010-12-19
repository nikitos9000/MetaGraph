#include <QString>
#include <QStringList>
#include <QtCore>
#include <QImage>
#include <QImageWriter>
#include <QPainter>
#include <QInputDialog>
#include <QFileDialog>
#include <QProgressDialog>
#include <QTableWidget>
#include <QMessageBox>
#include <QErrorMessage>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutqtwindow.h"
#include "graphlogic.h"
#include "graphview.h"
#include "graphobject.h"
#include "graphobjectarc.h"
#include "graphobjecttsp.h"
#include "graphobjectvertex.h"
#include "graphobjectstore.h"
#include "graphscene.h"
#include "graphscenenode.h"
#include "graphsceneedge.h"

GraphLogic::GraphLogic(Ui::MainWindow* ui, MainWindow* mainWindow) :
        _ui(ui), _mainWindow(mainWindow),
        _graphObject(new GraphObject()), _graphObjectStore(new GraphObjectStore()), _graphObjectTSP(0),
        _graphFilename(), _graphChanged(true),
        _graphSelectedNodes(), _graphSelectedEdges()
{
    _graphScene = new GraphScene(this);
    populateGraphScene(_graphScene, _graphObject);

    _graphView = new GraphView(this, _ui->graphFrame);
    _ui->graphLayout->addWidget(_graphView);

    updateUi();
    updateUiItems();
    updateUiSelection();
}

GraphLogic::~GraphLogic()
{
    delete _graphView;
    delete _graphObject;
    delete _graphObjectStore;
}

GraphScene* GraphLogic::graphScene() const
{
    return _graphScene;
}

QSet<int> GraphLogic::selectedNodes() const
{
    return _graphSelectedNodes;
}

QSet<int> GraphLogic::selectedEdges() const
{
    return _graphSelectedEdges;
}

void GraphLogic::sceneVertexSelect(int id)
{
    if (_graphSelectedNodes.contains(id)) return;

    _graphSelectedNodes.insert(id);
    updateUiSelection();
}

void GraphLogic::sceneVertexDeselect(int id)
{
    if (!_graphSelectedNodes.contains(id)) return;

    _graphSelectedNodes.remove(id);
    updateUiSelection();
}

void GraphLogic::sceneVertexMove(int id, int x, int y)
{
    GraphObjectVertex* vertex = _graphObject->getVertex(id);
    vertex->setX(x);
    vertex->setY(y);

    _graphChanged = true;
    updateUi();
}

void GraphLogic::sceneVertexMenuActionDelete(int id)
{
    if (!_graphSelectedNodes.contains(id)) return;

    menuActionDelete();
}

void GraphLogic::sceneVertexMenuActionChange(int id)
{
    if (!_graphSelectedNodes.contains(id)) return;

    menuActionChange();
}

void GraphLogic::sceneVertexMenuActionArcCreate(int id)
{
    if (!_graphSelectedNodes.contains(id)) return;

    menuActionArcCreate();
}

void GraphLogic::sceneArcSelect(int id)
{
    _graphSelectedEdges.insert(id);
    updateUiSelection();
}

void GraphLogic::sceneArcDeselect(int id)
{
    _graphSelectedEdges.remove(id);
    updateUiSelection();
}

void GraphLogic::sceneArcMenuActionDelete(int id)
{
    if (!_graphSelectedEdges.contains(id)) return;

    menuActionDelete();
}

void GraphLogic::sceneArcMenuActionChange(int id)
{
    if (!_graphSelectedEdges.contains(id)) return;

    menuActionChange();
}

void GraphLogic::sceneMenuActionVertexCreate(int x, int y)
{
    bool inputAccepted = false;
    QString label = QInputDialog::getText(_ui->graphFrame, trUtf8("Вершина..."), trUtf8("Метка новой вершины: "), QLineEdit::Normal, QString(), &inputAccepted);
    if (!inputAccepted) return;

    GraphObjectVertex* vertex = _graphObject->addVertex(label.toStdWString(), 0, 0);
    GraphSceneNode* node = _graphScene->addNode(vertex->id(), QString::number(vertex->id()), x, y);
    vertex->setX(node->x());
    vertex->setY(node->y());

    _graphView->ensureVisible(node, GraphScene::GRID_SIZE, GraphScene::GRID_SIZE);

    delete _graphObjectTSP;
    _graphObjectTSP = 0;

    _graphChanged = true;
    updateUi();
    updateUiItems();
}

void GraphLogic::sceneMenuActionClear()
{
    delete _graphObject;
    _graphObject = new GraphObject();
    _graphScene->clear();
    _graphSelectedNodes.clear();
    _graphSelectedEdges.clear();

    delete _graphObjectTSP;
    _graphObjectTSP = 0;

    _graphChanged = true;
    updateUi();
    updateUiItems();
    updateUiSelection();
}

void GraphLogic::menuActionNew()
{
    setGraphObject(new GraphObject());
    _graphFilename = QString();
    _graphSelectedNodes.clear();
    _graphSelectedEdges.clear();

    delete _graphObjectTSP;
    _graphObjectTSP = 0;

    _graphChanged = true;
    updateUi();
    updateUiItems();
    updateUiSelection();
}

void GraphLogic::menuActionOpen()
{
    QString filename = QFileDialog::getOpenFileName(_ui->graphFrame, trUtf8("Выберите файл для открытия..."), QString(), trUtf8("Граф (*.grf)"));
    if (filename.isEmpty()) return;

    setGraphObject(_graphObjectStore->load(filename.toStdWString()));
    _graphFilename = filename;
    _graphSelectedNodes.clear();
    _graphSelectedEdges.clear();

    delete _graphObjectTSP;
    _graphObjectTSP = 0;

    _graphChanged = false;
    updateUi();
    updateUiItems();
    updateUiSelection();
}

void GraphLogic::menuActionSave()
{
    if (!_graphFilename.isEmpty())
    {
        _graphObjectStore->save(_graphObject, _graphFilename.toStdWString());
        _graphChanged = false;
        updateUi();
    }
    else menuActionSaveAs();
}

void GraphLogic::menuActionSaveAs()
{
    QString filename = QFileDialog::getSaveFileName(_ui->graphFrame, trUtf8("Выберите файл для сохранения..."), QString(), trUtf8("Граф (*.grf)"));
    if (filename.isEmpty()) return;

    _graphObjectStore->save(_graphObject, filename.toStdWString());
    _graphFilename = filename;
    _graphChanged = false;
    updateUi();
}

void GraphLogic::menuActionExport()
{
    QList<QByteArray> formats = QImageWriter::supportedImageFormats();

    QString filetypes;

    int index = 0;
    foreach(QByteArray format, formats)
    {
        QString type(format);
        filetypes.append(trUtf8("Изображение ") + type.toUpper() + " (*." + type + ")");
        if (index++ < formats.size() - 1) filetypes.append(";;");
    }

    QString filename = QFileDialog::getSaveFileName(_ui->graphFrame, trUtf8("Выберите файл для экспорта..."), QString(), filetypes);
    if (filename.isEmpty()) return;

    QRectF boundingRect = _graphScene->itemsBoundingRect();
    boundingRect.setLeft(int(boundingRect.left() / GraphScene::GRID_SIZE - 1) * GraphScene::GRID_SIZE);
    boundingRect.setTop(int(boundingRect.top() / GraphScene::GRID_SIZE - 1) * GraphScene::GRID_SIZE);
    boundingRect.setRight(-int(-boundingRect.right() / GraphScene::GRID_SIZE - 1) * GraphScene::GRID_SIZE);
    boundingRect.setBottom(-int(-boundingRect.bottom() / GraphScene::GRID_SIZE - 1) * GraphScene::GRID_SIZE);

    QSize imageSize(boundingRect.width(), boundingRect.height());

    QImage image(imageSize, QImage::Format_RGB32);
    image.fill(QColor(Qt::white).rgb());

    QRectF imageRect(QPointF(0, 0), imageSize);

    QPainter painter(&image);
    _graphScene->drawBackground(&painter, imageRect);
    _graphScene->render(&painter, imageRect, boundingRect);

    painter.end();
    image.save(filename);
}


void GraphLogic::menuActionVertexCreate()
{
    sceneMenuActionVertexCreate(0, 0);
}

void GraphLogic::menuActionArcCreate()
{
    if (_graphSelectedNodes.size() < 2) return;

    QSet<int>::const_iterator startNodeIt = _graphSelectedNodes.begin();
    QSet<int>::const_iterator nodeEndIt = _graphSelectedNodes.end();

    for(; startNodeIt != nodeEndIt; ++startNodeIt)
    {
        QSet<int>::const_iterator endNodeIt = startNodeIt;
        ++endNodeIt;

        int startId = *startNodeIt;
        GraphObjectVertex* startVertex = _graphObject->getVertex(startId);

        for(; endNodeIt != nodeEndIt; ++endNodeIt)
        {
            int endId = *endNodeIt;
            GraphObjectVertex* endVertex = _graphObject->getVertex(endId);

            if (_graphObject->getArc(startVertex, endVertex)) continue;

            bool inputAccepted = false;
            QString text = trUtf8("Вес дуги между вершинами ") + QString::number(startId) + trUtf8(" и ") + QString::number(endId) + ": ";
            double weight = QInputDialog::getDouble(_ui->graphFrame, trUtf8("Дуга..."), text, 1.0, 0.1, 1e9, 1, &inputAccepted);
            if (!inputAccepted) return;

            GraphObjectArc* arc = _graphObject->addArc(QString::number(weight).toStdWString(), startVertex, endVertex, weight);

            GraphSceneEdge* edge = _graphScene->addEdge(arc->id(), QString::number(weight), startId, endId);
            edge->adjust();
        }
    }

    delete _graphObjectTSP;
    _graphObjectTSP = 0;

    _graphChanged = true;
    updateUi();
    updateUiItems();
}

void GraphLogic::menuActionChange()
{
    if (_graphSelectedNodes.size() + _graphSelectedEdges.size() != 1) return;

    if (!_graphSelectedNodes.isEmpty())
    {
        int id = *_graphSelectedNodes.begin();

        GraphObjectVertex* vertex = _graphObject->getVertex(id);
        QString label = QString::fromStdWString(vertex->label());

        bool inputAccepted = false;
        QString text = trUtf8("Метка вершины ") + QString::number(vertex->id()) + ":";
        QString newLabel = QInputDialog::getText(_ui->graphFrame, trUtf8("Вершина..."), text, QLineEdit::Normal, label, &inputAccepted);
        if (!inputAccepted) return;

        vertex->setLabel(newLabel.toStdWString());

        _graphScene->node(id)->setLabel(newLabel);
    }
    else if (!_graphSelectedEdges.isEmpty())
    {
        int id = *_graphSelectedEdges.begin();

        GraphObjectArc* arc = _graphObject->getArc(id);

        bool inputAccepted = false;
        QString text = trUtf8("Вес дуги между вершинами ") + QString::number(arc->startVertex()->id()) + trUtf8(" и ") + QString::number(arc->endVertex()->id()) + ": ";
        double newWeight = QInputDialog::getDouble(_ui->graphFrame, trUtf8("Дуга..."), text, arc->weight(), 0.1, 1e9, 1, &inputAccepted);
        if (!inputAccepted) return;

        arc->setWeight(newWeight);
        arc->setLabel(QString::number(newWeight).toStdWString());

        _graphScene->edge(id)->setLabel(QString::number(newWeight));

        delete _graphObjectTSP;
        _graphObjectTSP = 0;
    }

    _graphChanged = true;
    updateUi();
    updateUiItems();
}

void GraphLogic::menuActionDelete()
{
    if (_graphSelectedNodes.isEmpty() && _graphSelectedEdges.isEmpty()) return;

    foreach(int id, _graphSelectedEdges)
    {
        _graphObject->removeArc(_graphObject->getArc(id));
        _graphScene->removeEdge(id);
    }
    _graphSelectedEdges.clear();

    foreach(int id, _graphSelectedNodes)
    {
        _graphObject->removeVertex(_graphObject->getVertex(id));
        _graphScene->removeNode(id);
    }
    _graphSelectedNodes.clear();

    delete _graphObjectTSP;
    _graphObjectTSP = 0;

    _graphChanged = true;
    updateUi();
    updateUiItems();
    updateUiSelection();
}

void GraphLogic::menuActionTSP()
{
    if (_graphObjectTSP != 0) return;

    QProgressDialog progressDialog(trUtf8("Решаю задачу коммивояжера..."), trUtf8("Отмена"), 1, 100, _mainWindow);
    progressDialog.setModal(true);

    _graphObjectTSP = _graphObject->calculateTSP(GraphLogicProgressHandler(&progressDialog));

    if (_graphObjectTSP != 0)
    {
        progressDialog.setValue(progressDialog.maximum());
        updateUiItems();
    }
    else if (!progressDialog.wasCanceled())
    {
        progressDialog.cancel();
        QMessageBox messageBox(QMessageBox::Warning, trUtf8("Печаль"), trUtf8("Поиск решения задачи коммивояжера провалился =("), QMessageBox::Ok, _mainWindow);
        messageBox.exec();
    }
}

void GraphLogic::menuActionTSPClear()
{
    if (_graphObjectTSP == 0) return;

    delete _graphObjectTSP;
    _graphObjectTSP = 0;

    updateUiItems();
}

void GraphLogic::menuActionAbout()
{
    QMessageBox::about(_mainWindow,
        trUtf8("TSPGraph 0.0.1"),
        trUtf8("Это программа <b>TSP Graph</b>.<br>Она решает задачу коммивояжера. Возможно.<br><br><i>Автор: Сметанин Никита Алексеевич, Р-38032</i><br><i>РТФ, УрФУ, 2010 г.</i>"));
}

void GraphLogic::menuActionAboutQt()
{
    AboutQtWindow aboutQt;
    aboutQt.exec();
}

void GraphLogic::sliderScale(int value)
{
    int minimum = _ui->scaleSlider->minimum();
    int maximum = _ui->scaleSlider->maximum();
    int power = value - minimum - (maximum - minimum) / 2;

    qreal scale = qPow(2.0, qreal(power));
    _graphView->setScale(scale, scale);

    _ui->scaleLabel->setText(QString::number(int(scale * 100)) + "%");
}

void GraphLogic::quit()
{
    _mainWindow->close();
}

void GraphLogic::updateUi()
{
    QString unnamedFile = trUtf8("Несохранённый граф");
    _mainWindow->setWindowTitle((_graphFilename.isEmpty() ? unnamedFile : _graphFilename) + "[*] - TSPGraph");
    _mainWindow->setWindowModified(_graphChanged);
    _ui->actionSave->setEnabled(_graphChanged);
}

void GraphLogic::updateUiItems()
{
    map<int, GraphObjectVertex*> vertexList = _graphObject->vertexList();
    map<int, GraphObjectVertex*>::const_iterator vertexIt = vertexList.begin();
    map<int, GraphObjectVertex*>::const_iterator vertexEndIt = vertexList.end();

    QStringList itemList;
    QString emptyLabel = trUtf8("[Пустая метка]");
    _ui->listWidget->clear();
    for(; vertexIt != vertexEndIt; ++vertexIt)
    {
        QString label = QString::fromStdWString(vertexIt->second->label());
        itemList.append(QString::number(vertexIt->first) + ". " + (label.isEmpty() ? emptyLabel : label));
        _graphScene->node(vertexIt->first)->setMark(false);
    }
    _ui->listWidget->addItems(itemList);

    map<int, GraphObjectArc*> arcList = _graphObject->arcList();
    map<int, GraphObjectArc*>::const_iterator arcIt = arcList.begin();
    map<int, GraphObjectArc*>::const_iterator arcEndIt = arcList.end();

    for(; arcIt != arcEndIt; ++arcIt)
        _graphScene->edge(arcIt->first)->setMark(false);

    if (_graphObjectTSP != 0)
    {
        vector<GraphObjectArc*> path = _graphObjectTSP->arcPath();

        for (unsigned int i = 0; i < path.size(); ++i)
        {
            _graphScene->edge(path[i]->id())->setMark(true);
            _graphScene->node(path[i]->startVertex()->id())->setMark(true);
            _graphScene->node(path[i]->endVertex()->id())->setMark(true);
        }
    }

    _ui->actionTSP->setEnabled(_graphObject->vertexCount() > 0 && _graphObjectTSP == 0);

    updateUiSelection();
}

void GraphLogic::updateUiSelection()
{
    int nodes = _graphSelectedNodes.size();
    int edges = _graphSelectedEdges.size();

    _ui->actionVertexAdd->setEnabled(true);
    _ui->actionArcAdd->setEnabled(nodes >= 2);
    _ui->actionArcAdd->setText(trUtf8(nodes > 2 ? "Добавить дуги..." : "Добавить дугу..."));

    _ui->actionChange->setEnabled(nodes + edges == 1);
    _ui->actionDelete->setEnabled(nodes + edges >= 1);

    QWidget* previousStackedWidget = _ui->stackedWidget->currentWidget();
    QWidget* currentStackedWidget = _ui->graphPage;

    if (nodes + edges > 1)
        currentStackedWidget = _ui->allPage;
    else if (nodes == 1 && edges == 0)
        currentStackedWidget = _ui->vertexPage;
    else if (nodes == 0 && edges == 1)
        currentStackedWidget = _ui->arcPage;

    if (_graphObjectTSP != 0) currentStackedWidget = _ui->tspPage;

    if (nodes == 1 && edges == 0)
    {
        GraphObjectVertex* vertex = _graphObject->getVertex(*_graphSelectedNodes.begin());
        _ui->vertexIdLabel->setText(trUtf8("Вершина ") + QString::number(vertex->id()));

        if (vertex->label().length() > 0)
            _ui->vertexLabel->setText(trUtf8("Метка: \"") + QString::fromStdWString(vertex->label()) + "\"");
        else
            _ui->vertexLabel->setText(trUtf8("Метки нет"));

        QStringList vertexIds;

        map<int, GraphObjectArc*> arcList = _graphObject->arcList();
        map<int, GraphObjectArc*>::const_iterator arcIt = arcList.begin();
        map<int, GraphObjectArc*>::const_iterator arcEndIt = arcList.end();

        for(; arcIt != arcEndIt; ++arcIt)
        {
            GraphObjectArc* arc = arcIt->second;
            if (arc->startVertex() == vertex)
                vertexIds.append(QString::number(arc->endVertex()->id()));
            else if (arc->endVertex() == vertex)
                vertexIds.append(QString::number(arc->startVertex()->id()));
        }

        if (vertexIds.length() > 0)
            _ui->vertexArcsLabel->setText(trUtf8("Дуги в ") + trUtf8(vertexIds.length() > 1 ? "вершины " : "вершину ") + vertexIds.join(", "));
        else
            _ui->vertexArcsLabel->setText(trUtf8("Дуг нет"));
    }

    if (nodes == 0 && edges == 1)
    {
        GraphObjectArc* arc = _graphObject->getArc(*_graphSelectedEdges.begin());
        _ui->arcIdLabel->setText(trUtf8("Дуга ") + QString::number(arc->id()));
        _ui->arcWeightLabel->setText(trUtf8("Вес: ") + QString::number(arc->weight()));
        _ui->arcStartVertexLabel->setText(trUtf8("Начальная вершина: ") + QString::number(arc->startVertex()->id()));
        _ui->arcEndVertexLabel->setText(trUtf8("Конечная вершина: ") + QString::number(arc->endVertex()->id()));
    }

    if (nodes + edges > 1)
    {
        QString label = trUtf8("Выбрано ");

        if (nodes > 0)
            label += QString::number(nodes) + " " + numeric(nodes, trUtf8("вершина"), trUtf8("вершины"), trUtf8("вершин"));

        if (nodes > 0 && edges > 0)
            label += trUtf8(" и ");

        if (edges > 0)
            label += QString::number(edges) + " " + numeric(edges, trUtf8("дуга"), trUtf8("дуги"), trUtf8("дуг"));

        _ui->allLabel->setText(label);
    }

    if (nodes == 0 && edges == 0)
    {
        int vertexCount = _graphObject->vertexCount();
        int arcCount = _graphObject->arcCount();

        if (vertexCount > 0)
            _ui->graphVertexCountLabel->setText(QString::number(vertexCount ) + " " + numeric(vertexCount, trUtf8("вершина"), trUtf8("вершины"), trUtf8("вершин")));
        else
            _ui->graphVertexCountLabel->setText(trUtf8("Вершин нет"));

        if (arcCount > 0)
            _ui->graphArcCountLabel->setText(QString::number(arcCount) + " " + numeric(arcCount, trUtf8("дуга"), trUtf8("дуги"), trUtf8("дуг")));
        else
            _ui->graphArcCountLabel->setText(trUtf8("Дуг нет"));

        _ui->graphClearButton->setEnabled(vertexCount + arcCount > 0);
    }

    if (_graphObjectTSP != 0)
    {
        _ui->tspWeight->setText(trUtf8("Вес пути: ") + QString::number(_graphObjectTSP->pathWeight()));

        QStringList vertexIds;
        vector<GraphObjectVertex*> vertexList = _graphObjectTSP->vertexPath();
        vector<GraphObjectVertex*>::const_iterator vertexIt = vertexList.begin();
        vector<GraphObjectVertex*>::const_iterator vertexEndIt = vertexList.end();

        for(; vertexIt != vertexEndIt; ++vertexIt)
            vertexIds.append(QString::number((*vertexIt)->id()));

        _ui->tspPath->setText(trUtf8("Путь проходит через ") + trUtf8(vertexIds.length() > 1 ? "вершины " : "вершину ") + vertexIds.join(", "));
    }

    if (previousStackedWidget != currentStackedWidget && currentStackedWidget != 0)
    {
        _ui->graphPage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        _ui->vertexPage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        _ui->arcPage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        _ui->allPage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        _ui->tspPage->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

        currentStackedWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        currentStackedWidget->adjustSize();
        _ui->stackedWidget->setCurrentWidget(currentStackedWidget);
    }
}

void GraphLogic::setGraphObject(GraphObject* graphObject)
{
    delete _graphObject;
    _graphObject = graphObject;

    _graphView->setScene(0);
    delete _graphScene;
    _graphScene = new GraphScene(this);
    populateGraphScene(_graphScene, _graphObject);
    _graphView->setScene(_graphScene);
}

void GraphLogic::populateGraphScene(GraphScene* graphScene, GraphObject* graphObject)
{    
    graphScene->clear();

    map<int, GraphObjectVertex*> vertexList = graphObject->vertexList();
    map<int, GraphObjectVertex*>::iterator vertexListIt = vertexList.begin();
    map<int, GraphObjectVertex*>::iterator vertexListEndIt = vertexList.end();

    for (; vertexListIt != vertexListEndIt; ++vertexListIt)
    {
        GraphObjectVertex* vertex = vertexListIt->second;
        QString label = QString::number(vertex->id());

        GraphSceneNode* node = graphScene->addNode(vertex->id(), label, vertex->x(), vertex->y());
        _graphView->ensureVisible(node, GraphScene::GRID_SIZE, GraphScene::GRID_SIZE);
    }

    map<int, GraphObjectArc*> arcList = graphObject->arcList();
    map<int, GraphObjectArc*>::iterator arcListIt = arcList.begin();
    map<int, GraphObjectArc*>::iterator arcListEndIt = arcList.end();

    for(; arcListIt != arcListEndIt; ++arcListIt)
    {
        GraphObjectArc* arc = arcListIt->second;
        QString label = QString::number(arc->weight());

        graphScene->addEdge(arc->id(), label, arc->startVertex()->id(), arc->endVertex()->id());
    }
}

QString GraphLogic::trUtf8(const char* sourceText) const
{
    return QObject::trUtf8(sourceText);
}

QString GraphLogic::numeric(int value, QString nominative, QString genitiveSingular, QString genitivePlural) const
{
    int lastOne = value % 10;
    int lastTwo = value % 100;

    if (lastOne == 1 && lastTwo != 11) return nominative;

    if ((lastOne == 2 && lastTwo != 12) ||
        (lastOne == 3 && lastTwo != 13) ||
        (lastOne == 4 && lastTwo != 14)) return genitiveSingular;

    return genitivePlural;
}
