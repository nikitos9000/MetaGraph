#ifndef GRAPHLOGIC_H
#define GRAPHLOGIC_H

#include <QString>
#include <QSet>
#include <QHash>
#include <QMenu>
#include <QListWidget>
#include <QListWidgetItem>
#include <QProgressDialog>
#include <algorithm>

#include "mainwindow.h"

class GraphObject;
class GraphObjectStore;
class GraphObjectTSP;
class GraphScene;
class GraphView;
class MainWindow;

namespace Ui {
    class MainWindow;
}

class GraphLogicProgressHandler
{
public:
    GraphLogicProgressHandler(QProgressDialog* dialog) : _dialog(dialog) {}
    GraphLogicProgressHandler(const GraphLogicProgressHandler& other) : _dialog(other._dialog) {}

    int ticks() const { return _dialog->maximum() - _dialog->minimum() + 1; }
    int tick() const { return _dialog->value(); }
    void setTick(int value) { _dialog->setValue(std::min(_dialog->maximum(), value)); }
    bool canceled() const { return _dialog->wasCanceled(); }

private:
    QProgressDialog* _dialog;
};

class GraphLogic
{
public:
    GraphLogic(Ui::MainWindow* ui, MainWindow* mainWindow);
    ~GraphLogic();

    GraphScene* graphScene() const;

    QSet<int> selectedNodes() const;
    QSet<int> selectedEdges() const;

    void sceneVertexSelect(int id);
    void sceneVertexDeselect(int id);
    void sceneVertexMove(int id, int x, int y);
    void sceneVertexMenuActionDelete(int id);
    void sceneVertexMenuActionChange(int id);
    void sceneVertexMenuActionArcCreate(int id);

    void sceneArcSelect(int id);
    void sceneArcDeselect(int id);
    void sceneArcMenuActionDelete(int id);
    void sceneArcMenuActionChange(int id);

    void sceneMenuActionVertexCreate(int x, int y);
    void sceneMenuActionClear();

    void menuActionNew();
    void menuActionOpen();
    void menuActionSave();
    void menuActionSaveAs();
    void menuActionExport();

    void menuActionVertexCreate();
    void menuActionArcCreate();

    void menuActionChange();
    void menuActionDelete();

    void menuActionTSP();
    void menuActionTSPClear();

    void menuActionAbout();
    void menuActionAboutQt();

    void sliderScale(int value);

    void quit();

private:
    Ui::MainWindow* _ui;
    MainWindow* _mainWindow;

    GraphObject* _graphObject;
    GraphObjectStore* _graphObjectStore;
    GraphObjectTSP* _graphObjectTSP;
    GraphScene* _graphScene;
    GraphView* _graphView;

    QString _graphFilename;
    bool _graphChanged;

    QSet<int> _graphSelectedNodes;
    QSet<int> _graphSelectedEdges;

    void updateUi();
    void updateUiItems();
    void updateUiSelection();

    void setGraphObject(GraphObject* graphObject);
    void populateGraphScene(GraphScene* graphScene, GraphObject* graphObject);

    QString trUtf8(const char* sourceText) const;
    QString numeric(int value, QString nominative, QString genitiveSingular, QString genitivePlural) const;
};

#endif // GRAPHLOGIC_H
