/********************************************************************************
** Form generated from reading UI file 'MainWindows.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWS_H
#define UI_MAINWINDOWS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowsClass
{
public:
    QAction *actOpen;
    QAction *actSave;
    QAction *actZoomIn;
    QAction *actZoomOut;
    QAction *actReturn;
    QAction *actRotate;
    QAction *actShear;
    QAction *actClear;
    QAction *actEraser;
    QAction *actPen;
    QAction *actRect;
    QAction *actEllipse;
    QAction *actionPainter_2_0;
    QAction *actionProgrammer;
    QAction *actfill4;
    QAction *actFillScan;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QComboBox *comboBoxLine;
    QComboBox *comboBoxColor;
    QSlider *horizontalSlider;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QTextBrowser *textBrowser;
    QPushButton *pushButton_data;

    void setupUi(QMainWindow *MainWindowsClass)
    {
        if (MainWindowsClass->objectName().isEmpty())
            MainWindowsClass->setObjectName(QStringLiteral("MainWindowsClass"));
        MainWindowsClass->resize(742, 476);
        actOpen = new QAction(MainWindowsClass);
        actOpen->setObjectName(QStringLiteral("actOpen"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/MainWindows/Resources/open_pokeball_24px_1203093_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        actOpen->setIcon(icon);
        actSave = new QAction(MainWindowsClass);
        actSave->setObjectName(QStringLiteral("actSave"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/MainWindows/Resources/abra_26.608695652174px_1203038_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        actSave->setIcon(icon1);
        actZoomIn = new QAction(MainWindowsClass);
        actZoomIn->setObjectName(QStringLiteral("actZoomIn"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/MainWindows/Resources/bellsprout_19.235294117647px_1203045_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        actZoomIn->setIcon(icon2);
        actZoomOut = new QAction(MainWindowsClass);
        actZoomOut->setObjectName(QStringLiteral("actZoomOut"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/MainWindows/Resources/charmander_21.021897810219px_1203052_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        actZoomOut->setIcon(icon3);
        actReturn = new QAction(MainWindowsClass);
        actReturn->setObjectName(QStringLiteral("actReturn"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/MainWindows/Resources/eevee_20.029197080292px_1203058_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        actReturn->setIcon(icon4);
        actRotate = new QAction(MainWindowsClass);
        actRotate->setObjectName(QStringLiteral("actRotate"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/MainWindows/Resources/dratini_24.058536585366px_1203057_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        actRotate->setIcon(icon5);
        actShear = new QAction(MainWindowsClass);
        actShear->setObjectName(QStringLiteral("actShear"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/MainWindows/Resources/blue_team_16.759124087591px_1203046_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        actShear->setIcon(icon6);
        actClear = new QAction(MainWindowsClass);
        actClear->setObjectName(QStringLiteral("actClear"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/MainWindows/Resources/camera_21.529411764706px_1203049_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        actClear->setIcon(icon7);
        actEraser = new QAction(MainWindowsClass);
        actEraser->setObjectName(QStringLiteral("actEraser"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/MainWindows/Resources/mew_31.587096774194px_1203088_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        actEraser->setIcon(icon8);
        actPen = new QAction(MainWindowsClass);
        actPen->setObjectName(QStringLiteral("actPen"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/MainWindows/Resources/squirtle_19.153284671533px_1203122_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        actPen->setIcon(icon9);
        actRect = new QAction(MainWindowsClass);
        actRect->setObjectName(QStringLiteral("actRect"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/MainWindows/Resources/snorlax_28.182857142857px_1203121_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        actRect->setIcon(icon10);
        actEllipse = new QAction(MainWindowsClass);
        actEllipse->setObjectName(QStringLiteral("actEllipse"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/MainWindows/Resources/pikachu_25.554404145078px_1203098_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        actEllipse->setIcon(icon11);
        actionPainter_2_0 = new QAction(MainWindowsClass);
        actionPainter_2_0->setObjectName(QStringLiteral("actionPainter_2_0"));
        actionProgrammer = new QAction(MainWindowsClass);
        actionProgrammer->setObjectName(QStringLiteral("actionProgrammer"));
        actfill4 = new QAction(MainWindowsClass);
        actfill4->setObjectName(QStringLiteral("actfill4"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/MainWindows/Resources/psyduck_19.473945409429px_1203114_easyicon.net.png"), QSize(), QIcon::Normal, QIcon::Off);
        actfill4->setIcon(icon12);
        actFillScan = new QAction(MainWindowsClass);
        actFillScan->setObjectName(QStringLiteral("actFillScan"));
        actFillScan->setIcon(icon4);
        centralWidget = new QWidget(MainWindowsClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindowsClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowsClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 742, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindowsClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowsClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindowsClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowsClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowsClass->setStatusBar(statusBar);
        dockWidget = new QDockWidget(MainWindowsClass);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidget->setMinimumSize(QSize(150, 90));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        comboBoxLine = new QComboBox(dockWidgetContents);
        comboBoxLine->setObjectName(QStringLiteral("comboBoxLine"));
        comboBoxLine->setGeometry(QRect(20, 50, 121, 22));
        comboBoxColor = new QComboBox(dockWidgetContents);
        comboBoxColor->setObjectName(QStringLiteral("comboBoxColor"));
        comboBoxColor->setGeometry(QRect(20, 120, 121, 22));
        horizontalSlider = new QSlider(dockWidgetContents);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(10, 210, 141, 22));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(25);
        horizontalSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(dockWidgetContents);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 72, 15));
        label_2 = new QLabel(dockWidgetContents);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 90, 72, 15));
        label_3 = new QLabel(dockWidgetContents);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 170, 72, 15));
        label_4 = new QLabel(dockWidgetContents);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 240, 101, 16));
        textBrowser = new QTextBrowser(dockWidgetContents);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(70, 160, 61, 31));
        pushButton_data = new QPushButton(dockWidgetContents);
        pushButton_data->setObjectName(QStringLiteral("pushButton_data"));
        pushButton_data->setGeometry(QRect(20, 290, 93, 28));
        dockWidget->setWidget(dockWidgetContents);
        MainWindowsClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionPainter_2_0);
        menu->addAction(actionProgrammer);
        mainToolBar->addAction(actOpen);
        mainToolBar->addAction(actSave);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actZoomIn);
        mainToolBar->addAction(actZoomOut);
        mainToolBar->addAction(actReturn);
        mainToolBar->addAction(actRotate);
        mainToolBar->addAction(actShear);
        mainToolBar->addAction(actClear);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actEraser);
        mainToolBar->addAction(actPen);
        mainToolBar->addAction(actRect);
        mainToolBar->addAction(actEllipse);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actfill4);
        mainToolBar->addAction(actFillScan);

        retranslateUi(MainWindowsClass);

        QMetaObject::connectSlotsByName(MainWindowsClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowsClass)
    {
        MainWindowsClass->setWindowTitle(QApplication::translate("MainWindowsClass", "MainWindows", 0));
        actOpen->setText(QApplication::translate("MainWindowsClass", "\346\211\223\345\274\200", 0));
        actSave->setText(QApplication::translate("MainWindowsClass", "\344\277\235\345\255\230", 0));
        actZoomIn->setText(QApplication::translate("MainWindowsClass", "\346\224\276\345\244\247", 0));
        actZoomOut->setText(QApplication::translate("MainWindowsClass", "\347\274\251\345\260\217", 0));
        actReturn->setText(QApplication::translate("MainWindowsClass", "\350\277\230\345\216\237", 0));
        actRotate->setText(QApplication::translate("MainWindowsClass", "\346\227\213\350\275\254", 0));
        actShear->setText(QApplication::translate("MainWindowsClass", "\346\213\211\344\274\270", 0));
        actClear->setText(QApplication::translate("MainWindowsClass", "\346\270\205\347\251\272", 0));
        actEraser->setText(QApplication::translate("MainWindowsClass", "\346\251\241\347\232\256", 0));
        actPen->setText(QApplication::translate("MainWindowsClass", "\347\254\224", 0));
        actRect->setText(QApplication::translate("MainWindowsClass", "\347\237\251\345\275\242", 0));
        actEllipse->setText(QApplication::translate("MainWindowsClass", "\345\234\206", 0));
        actionPainter_2_0->setText(QApplication::translate("MainWindowsClass", "painter 2.0", 0));
        actionProgrammer->setText(QApplication::translate("MainWindowsClass", "programmer", 0));
        actfill4->setText(QApplication::translate("MainWindowsClass", "\345\233\233\351\202\273\345\237\237\345\241\253\345\205\205", 0));
        actFillScan->setText(QApplication::translate("MainWindowsClass", "\346\211\253\346\217\217\345\241\253\345\205\205", 0));
#ifndef QT_NO_TOOLTIP
        actFillScan->setToolTip(QApplication::translate("MainWindowsClass", "\346\211\253\346\217\217\345\241\253\345\205\205", 0));
#endif // QT_NO_TOOLTIP
        menu->setTitle(QApplication::translate("MainWindowsClass", "\345\205\263\344\272\216", 0));
        comboBoxLine->clear();
        comboBoxLine->insertItems(0, QStringList()
         << QApplication::translate("MainWindowsClass", "\345\256\236\347\272\277", 0)
         << QApplication::translate("MainWindowsClass", "\347\202\271\347\272\277", 0)
         << QApplication::translate("MainWindowsClass", "\347\240\264\346\212\230\345\217\267\347\272\277", 0)
         << QApplication::translate("MainWindowsClass", "\347\202\271\347\240\264\346\212\230\345\217\267\347\272\277", 0)
        );
        comboBoxColor->clear();
        comboBoxColor->insertItems(0, QStringList()
         << QApplication::translate("MainWindowsClass", "\351\273\221\350\211\262", 0)
         << QApplication::translate("MainWindowsClass", "\347\231\275\350\211\262", 0)
         << QApplication::translate("MainWindowsClass", "\347\272\242\350\211\262", 0)
         << QApplication::translate("MainWindowsClass", "\347\273\277\350\211\262", 0)
         << QApplication::translate("MainWindowsClass", "\350\223\235\350\211\262", 0)
         << QApplication::translate("MainWindowsClass", "\347\262\211\350\211\262", 0)
         << QApplication::translate("MainWindowsClass", "\347\264\253\347\272\242\350\211\262", 0)
         << QApplication::translate("MainWindowsClass", "\351\273\204\350\211\262", 0)
        );
        label->setText(QApplication::translate("MainWindowsClass", "\347\272\277\345\275\242", 0));
        label_2->setText(QApplication::translate("MainWindowsClass", "\351\242\234\350\211\262", 0));
        label_3->setText(QApplication::translate("MainWindowsClass", "\347\254\224\347\262\227", 0));
        label_4->setText(QApplication::translate("MainWindowsClass", "1\345\210\26025\344\271\213\351\227\264", 0));
        pushButton_data->setText(QApplication::translate("MainWindowsClass", "\346\225\260\346\215\256", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowsClass: public Ui_MainWindowsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWS_H
