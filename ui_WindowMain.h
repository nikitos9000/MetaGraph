/********************************************************************************
** Form generated from reading UI file 'WindowMain.ui'
**
** Created: Fri 16. Apr 21:40:42 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWMAIN_H
#define UI_WINDOWMAIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowMain
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QFrame *toolFrame;
    QPushButton *pushButton;
    QFrame *centerFrame;
    QVBoxLayout *verticalLayout;
    QFrame *viewFrame;
    QVBoxLayout *verticalLayout_2;
    QFrame *headerFrame;
    QLabel *label;
    QLabel *label_2;
    QFrame *workFrame;
    QFrame *infoFrame;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_3;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_13;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QGroupBox *groupBox_6;
    QFrame *listFrame;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QListWidget *graphListWidget;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_5;
    QListWidget *vertexSetListWidget;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_6;
    QListWidget *arcSetListWidget;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_7;
    QListWidget *pathListWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;

    void setupUi(QMainWindow *WindowMain)
    {
        if (WindowMain->objectName().isEmpty())
            WindowMain->setObjectName(QString::fromUtf8("WindowMain"));
        WindowMain->resize(671, 572);
        WindowMain->setMinimumSize(QSize(0, 0));
        centralWidget = new QWidget(WindowMain);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(4);
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        toolFrame = new QFrame(centralWidget);
        toolFrame->setObjectName(QString::fromUtf8("toolFrame"));
        toolFrame->setMinimumSize(QSize(30, 0));
        toolFrame->setMaximumSize(QSize(30, 16777215));
        toolFrame->setFrameShape(QFrame::NoFrame);
        toolFrame->setFrameShadow(QFrame::Sunken);
        pushButton = new QPushButton(toolFrame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(0, 10, 21, 23));

        horizontalLayout->addWidget(toolFrame);

        centerFrame = new QFrame(centralWidget);
        centerFrame->setObjectName(QString::fromUtf8("centerFrame"));
        centerFrame->setFrameShape(QFrame::NoFrame);
        centerFrame->setFrameShadow(QFrame::Raised);
        centerFrame->setLineWidth(0);
        verticalLayout = new QVBoxLayout(centerFrame);
        verticalLayout->setSpacing(4);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        viewFrame = new QFrame(centerFrame);
        viewFrame->setObjectName(QString::fromUtf8("viewFrame"));
        viewFrame->setFrameShape(QFrame::StyledPanel);
        viewFrame->setFrameShadow(QFrame::Sunken);
        verticalLayout_2 = new QVBoxLayout(viewFrame);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        headerFrame = new QFrame(viewFrame);
        headerFrame->setObjectName(QString::fromUtf8("headerFrame"));
        headerFrame->setMinimumSize(QSize(200, 22));
        headerFrame->setMaximumSize(QSize(16777215, 22));
        headerFrame->setFrameShape(QFrame::NoFrame);
        headerFrame->setFrameShadow(QFrame::Plain);
        label = new QLabel(headerFrame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(5, 4, 45, 13));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        font.setKerning(true);
        label->setFont(font);
        label_2 = new QLabel(headerFrame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 4, 92, 13));

        verticalLayout_2->addWidget(headerFrame);

        workFrame = new QFrame(viewFrame);
        workFrame->setObjectName(QString::fromUtf8("workFrame"));
        workFrame->setMinimumSize(QSize(400, 300));
        workFrame->setStyleSheet(QString::fromUtf8("#workFrame {\n"
"  background-color: #FFF;\n"
"}"));
        workFrame->setFrameShape(QFrame::NoFrame);
        workFrame->setFrameShadow(QFrame::Raised);

        verticalLayout_2->addWidget(workFrame);


        verticalLayout->addWidget(viewFrame);

        infoFrame = new QFrame(centerFrame);
        infoFrame->setObjectName(QString::fromUtf8("infoFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(infoFrame->sizePolicy().hasHeightForWidth());
        infoFrame->setSizePolicy(sizePolicy);
        infoFrame->setMinimumSize(QSize(300, 100));
        infoFrame->setMaximumSize(QSize(16777215, 16777215));
        infoFrame->setFrameShape(QFrame::Box);
        infoFrame->setFrameShadow(QFrame::Sunken);
        horizontalLayout_2 = new QHBoxLayout(infoFrame);
        horizontalLayout_2->setSpacing(4);
        horizontalLayout_2->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        groupBox_5 = new QGroupBox(infoFrame);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        groupBox_5->setFont(font1);
        groupBox_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        horizontalLayout_3 = new QHBoxLayout(groupBox_5);
        horizontalLayout_3->setSpacing(14);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_3->setContentsMargins(8, 4, 8, 6);
        frame = new QFrame(groupBox_5);
        frame->setObjectName(QString::fromUtf8("frame"));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        frame->setFont(font2);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(4);
        gridLayout_2->setVerticalSpacing(6);
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setMinimumSize(QSize(0, 14));
        label_3->setMaximumSize(QSize(16777215, 14));
        label_3->setFont(font2);
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(0, 14));
        label_4->setMaximumSize(QSize(16777215, 14));
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(0, 14));
        label_5->setMaximumSize(QSize(16777215, 14));
        label_5->setFont(font2);
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_5, 2, 0, 1, 1);

        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(0, 14));
        label_6->setMaximumSize(QSize(16777215, 14));
        label_6->setFont(font2);
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_6, 3, 0, 1, 1);

        label_7 = new QLabel(frame);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setMinimumSize(QSize(0, 14));
        label_7->setMaximumSize(QSize(16777215, 14));
        label_7->setFont(font2);
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_7, 4, 0, 1, 1);

        label_8 = new QLabel(frame);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(0, 14));
        label_8->setMaximumSize(QSize(16777215, 14));
        label_8->setFont(font2);
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_8, 5, 0, 1, 1);

        label_11 = new QLabel(frame);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(0, 14));
        label_11->setMaximumSize(QSize(16777215, 14));
        label_11->setFont(font1);

        gridLayout_2->addWidget(label_11, 0, 1, 1, 1);

        label_12 = new QLabel(frame);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMinimumSize(QSize(0, 14));
        label_12->setMaximumSize(QSize(16777215, 14));
        label_12->setFont(font1);

        gridLayout_2->addWidget(label_12, 1, 1, 1, 1);

        label_9 = new QLabel(frame);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(0, 14));
        label_9->setMaximumSize(QSize(16777215, 14));
        label_9->setFont(font1);

        gridLayout_2->addWidget(label_9, 2, 1, 1, 1);

        label_10 = new QLabel(frame);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(0, 14));
        label_10->setMaximumSize(QSize(16777215, 14));
        label_10->setFont(font1);

        gridLayout_2->addWidget(label_10, 3, 1, 1, 1);

        label_13 = new QLabel(frame);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMinimumSize(QSize(0, 14));
        label_13->setMaximumSize(QSize(16777215, 14));
        label_13->setFont(font1);

        gridLayout_2->addWidget(label_13, 4, 1, 1, 1);


        horizontalLayout_3->addWidget(frame);

        frame_2 = new QFrame(groupBox_5);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setEnabled(true);
        QFont font3;
        font3.setBold(false);
        font3.setWeight(50);
        font3.setStyleStrategy(QFont::PreferDefault);
        frame_2->setFont(font3);
        frame_2->setMouseTracking(false);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(4);
        gridLayout_3->setVerticalSpacing(6);
        label_14 = new QLabel(frame_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font2);

        gridLayout_3->addWidget(label_14, 0, 0, 1, 1);

        label_15 = new QLabel(frame_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setFont(font2);

        gridLayout_3->addWidget(label_15, 1, 0, 1, 1);

        label_16 = new QLabel(frame_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setFont(font2);

        gridLayout_3->addWidget(label_16, 2, 0, 1, 1);

        label_17 = new QLabel(frame_2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font2);

        gridLayout_3->addWidget(label_17, 3, 0, 1, 1);

        label_18 = new QLabel(frame_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setFont(font2);

        gridLayout_3->addWidget(label_18, 4, 0, 1, 1);

        label_19 = new QLabel(frame_2);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setFont(font2);

        gridLayout_3->addWidget(label_19, 5, 0, 1, 1);

        label_20 = new QLabel(frame_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setFont(font1);

        gridLayout_3->addWidget(label_20, 0, 1, 1, 1);

        label_21 = new QLabel(frame_2);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setFont(font1);

        gridLayout_3->addWidget(label_21, 1, 1, 1, 1);

        label_22 = new QLabel(frame_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setFont(font1);

        gridLayout_3->addWidget(label_22, 2, 1, 1, 1);

        label_23 = new QLabel(frame_2);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font1);

        gridLayout_3->addWidget(label_23, 3, 1, 1, 1);

        label_24 = new QLabel(frame_2);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setFont(font1);

        gridLayout_3->addWidget(label_24, 4, 1, 1, 1);

        label_25 = new QLabel(frame_2);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setFont(font1);

        gridLayout_3->addWidget(label_25, 5, 1, 1, 1);


        horizontalLayout_3->addWidget(frame_2);


        horizontalLayout_2->addWidget(groupBox_5);

        groupBox_6 = new QGroupBox(infoFrame);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setFont(font1);

        horizontalLayout_2->addWidget(groupBox_6);


        verticalLayout->addWidget(infoFrame);


        horizontalLayout->addWidget(centerFrame);

        listFrame = new QFrame(centralWidget);
        listFrame->setObjectName(QString::fromUtf8("listFrame"));
        listFrame->setMinimumSize(QSize(150, 0));
        listFrame->setMaximumSize(QSize(150, 16777215));
        listFrame->setFrameShape(QFrame::NoFrame);
        listFrame->setFrameShadow(QFrame::Sunken);
        verticalLayout_4 = new QVBoxLayout(listFrame);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(3, 3, 3, 3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox = new QGroupBox(listFrame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setFont(font2);
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(6, 6, 6, 6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        graphListWidget = new QListWidget(groupBox);
        graphListWidget->setObjectName(QString::fromUtf8("graphListWidget"));
        sizePolicy1.setHeightForWidth(graphListWidget->sizePolicy().hasHeightForWidth());
        graphListWidget->setSizePolicy(sizePolicy1);
        graphListWidget->setFont(font2);

        verticalLayout_3->addWidget(graphListWidget);


        verticalLayout_4->addWidget(groupBox);

        groupBox_2 = new QGroupBox(listFrame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFont(font2);
        verticalLayout_5 = new QVBoxLayout(groupBox_2);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(6, 6, 6, 6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        vertexSetListWidget = new QListWidget(groupBox_2);
        vertexSetListWidget->setObjectName(QString::fromUtf8("vertexSetListWidget"));
        sizePolicy1.setHeightForWidth(vertexSetListWidget->sizePolicy().hasHeightForWidth());
        vertexSetListWidget->setSizePolicy(sizePolicy1);
        vertexSetListWidget->setFont(font2);

        verticalLayout_5->addWidget(vertexSetListWidget);


        verticalLayout_4->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(listFrame);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_6 = new QVBoxLayout(groupBox_3);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(6, 6, 6, 6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        arcSetListWidget = new QListWidget(groupBox_3);
        arcSetListWidget->setObjectName(QString::fromUtf8("arcSetListWidget"));
        sizePolicy1.setHeightForWidth(arcSetListWidget->sizePolicy().hasHeightForWidth());
        arcSetListWidget->setSizePolicy(sizePolicy1);

        verticalLayout_6->addWidget(arcSetListWidget);


        verticalLayout_4->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(listFrame);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_7 = new QVBoxLayout(groupBox_4);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(6, 6, 6, 6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        pathListWidget = new QListWidget(groupBox_4);
        pathListWidget->setObjectName(QString::fromUtf8("pathListWidget"));
        sizePolicy1.setHeightForWidth(pathListWidget->sizePolicy().hasHeightForWidth());
        pathListWidget->setSizePolicy(sizePolicy1);

        verticalLayout_7->addWidget(pathListWidget);


        verticalLayout_4->addWidget(groupBox_4);


        horizontalLayout->addWidget(listFrame);

        WindowMain->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WindowMain);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 671, 20));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        WindowMain->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());

        retranslateUi(WindowMain);

        QMetaObject::connectSlotsByName(WindowMain);
    } // setupUi

    void retranslateUi(QMainWindow *WindowMain)
    {
        WindowMain->setWindowTitle(QApplication::translate("WindowMain", "MainWindow", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("WindowMain", "PushButton", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WindowMain", "\320\223\321\200\320\260\321\204 2: ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("WindowMain", "\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265 \320\263\321\200\320\260\321\204\320\260 2", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("WindowMain", "\320\223\321\200\320\260\321\204 2", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("WindowMain", "\320\247\320\270\321\201\320\273\320\276 \320\262\320\265\321\200\321\210\320\270\320\275:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("WindowMain", "\320\247\320\270\321\201\320\273\320\276 \320\264\321\203\320\263: ", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("WindowMain", "\320\241\320\273\320\260\320\261\320\276-\321\201\320\262\321\217\320\267\320\275\321\213\320\271: ", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("WindowMain", "\320\241\320\270\320\273\321\214\320\275\320\276-\321\201\320\262\321\217\320\267\320\275\321\213\320\271: ", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("WindowMain", "\320\220\321\206\320\270\320\272\320\273\320\270\321\207\320\275\321\213\320\271: ", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("WindowMain", "\320\237\320\276\320\273\320\275\321\213\320\271: ", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("WindowMain", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">10 </span><span style=\" font-size:8pt; font-weight:400;\">\320\262\320\265\321\200\321\210\320\270\320\275</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("WindowMain", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">5</span><span style=\" font-size:8pt; font-weight:400;\"> \320\264\321\203\320\263</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("WindowMain", "\320\224\320\260", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("WindowMain", "\320\235\320\265\321\202", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("WindowMain", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; text-decoration: underline;\">\320\235\320\265\320\270\320\267\320\262\320\265\321\201\321\202\320\275\320\276</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("WindowMain", "\320\241\320\265\321\202\320\265\320\262\320\276\320\271:", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("WindowMain", "\320\235\320\260\321\207\320\260\320\273\320\276 \321\201\320\265\321\202\320\270:", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("WindowMain", "\320\232\320\276\320\275\320\265\321\206 \321\201\320\265\321\202\320\270:", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("WindowMain", "\320\234\320\260\320\272\321\201\320\270\320\274\320\260\320\273\321\214\320\275\321\213\320\271 \320\277\320\276\321\202\320\276\320\272:", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("WindowMain", "\320\241\320\262\320\276\320\271\321\201\321\202\320\262\320\276:", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("WindowMain", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200:", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("WindowMain", "\320\224\320\260", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("WindowMain", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:400;\">\320\222\320\265\321\200\321\210\320\270\320\275\320\260 </span><span style=\" font-size:8pt;\">10</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("WindowMain", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; font-weight:400;\">\320\222\320\265\321\200\321\210\320\270\320\275\320\260 </span><span style=\" font-size:8pt;\">5</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("WindowMain", "10", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("WindowMain", "\320\224\320\260", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("WindowMain", "4", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("WindowMain", "\320\237\321\203\321\202\321\214 1", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("WindowMain", "\320\223\321\200\320\260\321\204\321\213:", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("WindowMain", "\320\235\320\260\320\261\320\276\321\200\321\213 \320\262\320\265\321\200\321\210\320\270\320\275:", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("WindowMain", "\320\235\320\260\320\261\320\276\321\200\321\213 \320\264\321\203\320\263:", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("WindowMain", "\320\237\321\203\321\202\320\270:", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("WindowMain", "\320\244\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("WindowMain", "\320\237\320\276\320\274\320\276\321\211\321\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WindowMain: public Ui_WindowMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWMAIN_H
