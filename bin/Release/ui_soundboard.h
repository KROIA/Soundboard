/********************************************************************************
** Form generated from reading UI file 'soundboard.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SOUNDBOARD_H
#define UI_SOUNDBOARD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <ribbon.h>

QT_BEGIN_NAMESPACE

class Ui_Soundboard
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    Ribbon *ribbonTabWidget;
    QFrame *frame;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menuInfo;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Soundboard)
    {
        if (Soundboard->objectName().isEmpty())
            Soundboard->setObjectName(QString::fromUtf8("Soundboard"));
        Soundboard->resize(785, 416);
        centralwidget = new QWidget(Soundboard);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 0, -1, -1);
        ribbonTabWidget = new Ribbon(centralwidget);
        ribbonTabWidget->setObjectName(QString::fromUtf8("ribbonTabWidget"));
        ribbonTabWidget->setMinimumSize(QSize(0, 120));
        ribbonTabWidget->setMaximumSize(QSize(16777215, 120));
        ribbonTabWidget->setTabPosition(QTabWidget::North);

        verticalLayout->addWidget(ribbonTabWidget);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 10, 111, 24));

        verticalLayout->addWidget(frame);

        Soundboard->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Soundboard);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 785, 21));
        menuInfo = new QMenu(menubar);
        menuInfo->setObjectName(QString::fromUtf8("menuInfo"));
        Soundboard->setMenuBar(menubar);
        statusbar = new QStatusBar(Soundboard);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Soundboard->setStatusBar(statusbar);

        menubar->addAction(menuInfo->menuAction());

        retranslateUi(Soundboard);

        QMetaObject::connectSlotsByName(Soundboard);
    } // setupUi

    void retranslateUi(QMainWindow *Soundboard)
    {
        Soundboard->setWindowTitle(QCoreApplication::translate("Soundboard", "Soundboard", nullptr));
        pushButton->setText(QCoreApplication::translate("Soundboard", "PushButton", nullptr));
        menuInfo->setTitle(QCoreApplication::translate("Soundboard", "Info", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Soundboard: public Ui_Soundboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOUNDBOARD_H
