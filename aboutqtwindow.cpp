#include "aboutqtwindow.h"
#include "ui_aboutqtwindow.h"

AboutQtWindow::AboutQtWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutQtWindow)
{
    ui->setupUi(this);
}

AboutQtWindow::~AboutQtWindow()
{
    delete ui;
}

void AboutQtWindow::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void AboutQtWindow::on_buttonBox_accepted()
{
    close();
}
