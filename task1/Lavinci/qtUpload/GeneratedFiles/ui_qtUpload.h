/********************************************************************************
** Form generated from reading UI file 'qtUpload.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTUPLOAD_H
#define UI_QTUPLOAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qtUploadClass
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QTextBrowser *textBrowser;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qtUploadClass)
    {
        if (qtUploadClass->objectName().isEmpty())
            qtUploadClass->setObjectName(QStringLiteral("qtUploadClass"));
        qtUploadClass->resize(600, 400);
        centralWidget = new QWidget(qtUploadClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 70, 75, 23));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(20, 190, 551, 141));
        qtUploadClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(qtUploadClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        qtUploadClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(qtUploadClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        qtUploadClass->setStatusBar(statusBar);

        retranslateUi(qtUploadClass);
        QObject::connect(pushButton, SIGNAL(clicked()), qtUploadClass, SLOT(btnClicked()));

        QMetaObject::connectSlotsByName(qtUploadClass);
    } // setupUi

    void retranslateUi(QMainWindow *qtUploadClass)
    {
        qtUploadClass->setWindowTitle(QApplication::translate("qtUploadClass", "qtUpload", Q_NULLPTR));
        pushButton->setText(QApplication::translate("qtUploadClass", "\346\211\223\345\274\200", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class qtUploadClass: public Ui_qtUploadClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTUPLOAD_H
