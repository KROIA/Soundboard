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
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <ribbon.h>

QT_BEGIN_NAMESPACE

class Ui_Soundboard
{
public:
    QWidget *centralwidget;
    QFrame *ribbonFrame;
    QVBoxLayout *verticalLayout_2;
    QDockWidget *ribbonDockWidget_2;
    QWidget *dockWidgetContents_3;
    QGridLayout *gridLayout_2;
    Ribbon *ribbonTabWidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Soundboard)
    {
        if (Soundboard->objectName().isEmpty())
            Soundboard->setObjectName(QString::fromUtf8("Soundboard"));
        Soundboard->resize(800, 600);
        centralwidget = new QWidget(Soundboard);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        ribbonFrame = new QFrame(centralwidget);
        ribbonFrame->setObjectName(QString::fromUtf8("ribbonFrame"));
        ribbonFrame->setGeometry(QRect(0, 0, 1400, 150));
        ribbonFrame->setMinimumSize(QSize(1400, 150));
        ribbonFrame->setMaximumSize(QSize(16777215, 150));
        ribbonFrame->setFrameShape(QFrame::StyledPanel);
        ribbonFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(ribbonFrame);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        ribbonDockWidget_2 = new QDockWidget(ribbonFrame);
        ribbonDockWidget_2->setObjectName(QString::fromUtf8("ribbonDockWidget_2"));
        ribbonDockWidget_2->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ribbonDockWidget_2->sizePolicy().hasHeightForWidth());
        ribbonDockWidget_2->setSizePolicy(sizePolicy);
        ribbonDockWidget_2->setMinimumSize(QSize(145, 100));
        ribbonDockWidget_2->setFeatures(QDockWidget::NoDockWidgetFeatures);
        ribbonDockWidget_2->setAllowedAreas(Qt::TopDockWidgetArea);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        gridLayout_2 = new QGridLayout(dockWidgetContents_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        ribbonTabWidget = new Ribbon(dockWidgetContents_3);
        ribbonTabWidget->setObjectName(QString::fromUtf8("ribbonTabWidget"));

        gridLayout_2->addWidget(ribbonTabWidget, 0, 0, 1, 1);

        ribbonDockWidget_2->setWidget(dockWidgetContents_3);

        verticalLayout_2->addWidget(ribbonDockWidget_2);

        Soundboard->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Soundboard);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        Soundboard->setMenuBar(menubar);
        statusbar = new QStatusBar(Soundboard);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Soundboard->setStatusBar(statusbar);

        retranslateUi(Soundboard);

        QMetaObject::connectSlotsByName(Soundboard);
    } // setupUi

    void retranslateUi(QMainWindow *Soundboard)
    {
        Soundboard->setWindowTitle(QCoreApplication::translate("Soundboard", "Soundboard", nullptr));
        ribbonDockWidget_2->setWindowTitle(QCoreApplication::translate("Soundboard", "Ribbon", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Soundboard: public Ui_Soundboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOUNDBOARD_H
