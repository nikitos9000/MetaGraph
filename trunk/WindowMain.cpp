#include "WindowMain.h"

WindowMain::WindowMain(QWidget *parent) :
                       QMainWindow(parent),
                       _ui(new WindowMainUI),
                       _gview(NULL),
                       _gcontroller(NULL)
{
    _ui->setupUi(this);

    connect(_ui->pushButton, SIGNAL(clicked()), this, SLOT(notify1()));
    connect(_ui->graphListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(notify2(QListWidgetItem*)));
}

WindowMain::~WindowMain()
{
    delete _ui;
}

void WindowMain::changeEvent(QEvent* event)
{
    QMainWindow::changeEvent(event);

    switch (event->type())
    {
        case QEvent::LanguageChange:
            _ui->retranslateUi(this);
            break;

        default: break;
    }
}

WindowMainUI* WindowMain::getUI()
{
    return _ui;
}

void WindowMain::setGView(GView* gview)
{
    _gview = gview;
}

void WindowMain::setGController(GController* gcontroller)
{
    _gcontroller = gcontroller;
}

void WindowMain::notify1()
{
    if (_gview) _gview->notify1();
}

void WindowMain::notify2(QListWidgetItem* item)
{
    if (_gview) _gview->notify2(item);
}
