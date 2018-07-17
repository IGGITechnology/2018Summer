/********************************************************************************
** Form generated from reading UI file 'mywin.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYWIN_H
#define UI_MYWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QKeySequenceEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mywin
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QTextBrowser *textBrowser;
    QWidget *widget_2;
    QPushButton *pushButton;
    QLabel *label;
    QToolButton *toolButton;
    QRadioButton *radioButton;
    QDialogButtonBox *buttonBox;
    QSlider *horizontalSlider;
    QKeySequenceEdit *keySequenceEdit;
    QSlider *verticalSlider;
    QScrollBar *verticalScrollBar;

    void setupUi(QWidget *mywin)
    {
        if (mywin->objectName().isEmpty())
            mywin->setObjectName(QStringLiteral("mywin"));
        mywin->resize(1112, 599);
        verticalLayout_2 = new QVBoxLayout(mywin);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(mywin);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        textBrowser = new QTextBrowser(mywin);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(textBrowser);


        horizontalLayout->addLayout(verticalLayout);

        widget_2 = new QWidget(mywin);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setMinimumSize(QSize(191, 0));
        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(40, 90, 93, 28));
        label = new QLabel(widget_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 161, 41));
        toolButton = new QToolButton(widget_2);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(40, 140, 91, 31));
        radioButton = new QRadioButton(widget_2);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(30, 210, 115, 19));
        buttonBox = new QDialogButtonBox(widget_2);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(0, 330, 193, 28));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        horizontalSlider = new QSlider(widget_2);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(20, 270, 160, 22));
        horizontalSlider->setOrientation(Qt::Horizontal);
        keySequenceEdit = new QKeySequenceEdit(widget_2);
        keySequenceEdit->setObjectName(QStringLiteral("keySequenceEdit"));
        keySequenceEdit->setGeometry(QRect(20, 390, 113, 21));
        verticalSlider = new QSlider(widget_2);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setGeometry(QRect(30, 420, 22, 131));
        verticalSlider->setOrientation(Qt::Vertical);
        verticalScrollBar = new QScrollBar(widget_2);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(120, 420, 16, 141));
        verticalScrollBar->setOrientation(Qt::Vertical);

        horizontalLayout->addWidget(widget_2);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(mywin);

        QMetaObject::connectSlotsByName(mywin);
    } // setupUi

    void retranslateUi(QWidget *mywin)
    {
        mywin->setWindowTitle(QApplication::translate("mywin", "mywin", 0));
        label_2->setText(QString());
        pushButton->setText(QApplication::translate("mywin", "open", 0));
        label->setText(QApplication::translate("mywin", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600;\">\345\220\204\347\247\215\346\262\241\347\224\250\347\232\204\346\216\247\344\273\266</span></p></body></html>", 0));
        toolButton->setText(QApplication::translate("mywin", "...", 0));
        radioButton->setText(QApplication::translate("mywin", "RadioButton", 0));
    } // retranslateUi

};

namespace Ui {
    class mywin: public Ui_mywin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYWIN_H
