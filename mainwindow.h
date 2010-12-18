#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graphlogic.h"

namespace Ui {
    class MainWindow;
}

class GraphView;
class GraphLogic;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    GraphLogic* _graphLogic;

private slots:
    void on_tspClearButton_clicked();
    void on_graphClearButton_clicked();
    void on_graphCreateVertexButton_clicked();
    void on_actionTSP_triggered();
    void on_allDeleteButton_clicked();
    void on_allArcCreate_clicked();
    void on_arcDeleteButton_clicked();
    void on_arcChangeButton_clicked();
    void on_vertexDeleteButton_clicked();
    void on_vertexChangeButton_clicked();
    void on_actionAbout_triggered();
    void on_actionAboutQt_triggered();
    void on_actionDelete_triggered();
    void on_actionChange_triggered();
    void on_scaleSlider_valueChanged(int value);
    void on_actionExport_triggered();
    void on_actionQuit_triggered();
    void on_actionArcAdd_triggered();
    void on_actionVertexAdd_triggered();
    void on_actionNew_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionOpen_triggered();
};

#endif // MAINWINDOW_H
