#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include <QMainWindow>
#include "ui_WindowMain.h"

#include "GView.h"
#include "GController.h"

typedef Ui::WindowMain WindowMainUI;

class GView;
class GController;

class WindowMain : public QMainWindow
{
    Q_OBJECT

    private:
        WindowMainUI* _ui;
        GView* _gview;
        GController* _gcontroller;

    protected:
        void changeEvent(QEvent* event);
        
    public:
        WindowMain(QWidget* parent = 0);
        ~WindowMain();

        WindowMainUI* getUI();

        void setGView(GView* gview);
        void setGController(GController* gcontroller);

    public slots:
        void notify1();
        void notify2(QListWidgetItem* item);
};

#endif // WINDOWMAIN_H
