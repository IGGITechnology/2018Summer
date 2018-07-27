/********************************************************************************
** Form generated from reading UI file 'IGGE.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IGGE_H
#define UI_IGGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IGGEClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *IGGEClass)
    {
        if (IGGEClass->objectName().isEmpty())
            IGGEClass->setObjectName(QStringLiteral("IGGEClass"));
        IGGEClass->resize(600, 400);
        menuBar = new QMenuBar(IGGEClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        IGGEClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(IGGEClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        IGGEClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(IGGEClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        IGGEClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(IGGEClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        IGGEClass->setStatusBar(statusBar);

        retranslateUi(IGGEClass);

        QMetaObject::connectSlotsByName(IGGEClass);
    } // setupUi

    void retranslateUi(QMainWindow *IGGEClass)
    {
        IGGEClass->setWindowTitle(QApplication::translate("IGGEClass", "IGGE", 0));
    } // retranslateUi

};

namespace Ui {
    class IGGEClass: public Ui_IGGEClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IGGE_H
