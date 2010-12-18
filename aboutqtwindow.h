#ifndef ABOUTQTWINDOW_H
#define ABOUTQTWINDOW_H

#include <QDialog>

namespace Ui {
    class AboutQtWindow;
}

class AboutQtWindow : public QDialog {
    Q_OBJECT
public:
    AboutQtWindow(QWidget *parent = 0);
    ~AboutQtWindow();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AboutQtWindow *ui;

private slots:
    void on_buttonBox_accepted();
};

#endif // ABOUTQTWINDOW_H
