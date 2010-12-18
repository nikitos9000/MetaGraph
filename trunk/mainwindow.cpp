#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDialog>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QSizePolicy>

#include "graphscene.h"
#include "graphview.h"
#include "graphlogic.h"
#include "graphobject.h"
#include "graphobjectstore.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _graphLogic = new GraphLogic(ui, this);
}

MainWindow::~MainWindow()
{   
    delete _graphLogic;
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_actionOpen_triggered()
{
    _graphLogic->menuActionOpen();
}

void MainWindow::on_actionSaveAs_triggered()
{
    _graphLogic->menuActionSaveAs();
}

void MainWindow::on_actionSave_triggered()
{
    _graphLogic->menuActionSave();
}

void MainWindow::on_actionNew_triggered()
{
    _graphLogic->menuActionNew();
}

void MainWindow::on_actionVertexAdd_triggered()
{
    _graphLogic->menuActionVertexCreate();
}

void MainWindow::on_actionArcAdd_triggered()
{
    _graphLogic->menuActionArcCreate();
}

void MainWindow::on_actionQuit_triggered()
{
    _graphLogic->quit();
}

void MainWindow::on_actionExport_triggered()
{
    _graphLogic->menuActionExport();
}

void MainWindow::on_scaleSlider_valueChanged(int value)
{
    _graphLogic->sliderScale(value);
}

void MainWindow::on_actionChange_triggered()
{
    _graphLogic->menuActionChange();
}

void MainWindow::on_actionDelete_triggered()
{
    _graphLogic->menuActionDelete();
}

void MainWindow::on_actionAboutQt_triggered()
{
    _graphLogic->menuActionAboutQt();
}

void MainWindow::on_actionAbout_triggered()
{
    _graphLogic->menuActionAbout();
}

void MainWindow::on_vertexChangeButton_clicked()
{
    _graphLogic->menuActionChange();
}

void MainWindow::on_vertexDeleteButton_clicked()
{
    _graphLogic->menuActionDelete();
}

void MainWindow::on_arcChangeButton_clicked()
{
    _graphLogic->menuActionChange();
}

void MainWindow::on_arcDeleteButton_clicked()
{
    _graphLogic->menuActionDelete();
}

void MainWindow::on_allArcCreate_clicked()
{
    _graphLogic->menuActionArcCreate();
}

void MainWindow::on_allDeleteButton_clicked()
{
    _graphLogic->menuActionDelete();
}

void MainWindow::on_actionTSP_triggered()
{
    _graphLogic->menuActionTSP();
}

void MainWindow::on_graphCreateVertexButton_clicked()
{
    _graphLogic->menuActionVertexCreate();
}

void MainWindow::on_graphClearButton_clicked()
{
    _graphLogic->sceneMenuActionClear();
}

void MainWindow::on_tspClearButton_clicked()
{
    _graphLogic->menuActionTSPClear();
}
