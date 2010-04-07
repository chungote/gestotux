/********************************************************************************
** Form generated from reading ui file 'quickcalendarwindow.ui'
**
** Created: Wed 24. Dec 00:02:45 2008
**      by: Qt User Interface Compiler version 4.5.0-tp1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_QUICKCALENDARWINDOW_H
#define UI_QUICKCALENDARWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QuickCalendarWindow
{
public:
    QAction *monthAction;
    QAction *weekAction;
    QAction *dayAction;
    QAction *rangeAction;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *mainMenu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *QuickCalendarWindow)
    {
        if (QuickCalendarWindow->objectName().isEmpty())
            QuickCalendarWindow->setObjectName(QString::fromUtf8("QuickCalendarWindow"));
        QuickCalendarWindow->resize(800, 600);
        monthAction = new QAction(QuickCalendarWindow);
        monthAction->setObjectName(QString::fromUtf8("monthAction"));
        weekAction = new QAction(QuickCalendarWindow);
        weekAction->setObjectName(QString::fromUtf8("weekAction"));
        dayAction = new QAction(QuickCalendarWindow);
        dayAction->setObjectName(QString::fromUtf8("dayAction"));
        rangeAction = new QAction(QuickCalendarWindow);
        rangeAction->setObjectName(QString::fromUtf8("rangeAction"));
        centralwidget = new QWidget(QuickCalendarWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QuickCalendarWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(QuickCalendarWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 19));
        mainMenu = new QMenu(menubar);
        mainMenu->setObjectName(QString::fromUtf8("mainMenu"));
        QuickCalendarWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(QuickCalendarWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        QuickCalendarWindow->setStatusBar(statusbar);

        menubar->addAction(mainMenu->menuAction());
        mainMenu->addAction(monthAction);
        mainMenu->addAction(weekAction);
        mainMenu->addAction(rangeAction);

        retranslateUi(QuickCalendarWindow);

        QMetaObject::connectSlotsByName(QuickCalendarWindow);
    } // setupUi

    void retranslateUi(QMainWindow *QuickCalendarWindow)
    {
        QuickCalendarWindow->setWindowTitle(QApplication::translate("QuickCalendarWindow", "QuickCalendar", 0, QApplication::UnicodeUTF8));
        monthAction->setText(QApplication::translate("QuickCalendarWindow", "Month based", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        monthAction->setToolTip(QApplication::translate("QuickCalendarWindow", "Manage user accounts.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        weekAction->setText(QApplication::translate("QuickCalendarWindow", "Week based", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        weekAction->setToolTip(QApplication::translate("QuickCalendarWindow", "Manage user gorups.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        dayAction->setText(QApplication::translate("QuickCalendarWindow", "Day based", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        dayAction->setToolTip(QApplication::translate("QuickCalendarWindow", "Manage calendars.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        rangeAction->setText(QApplication::translate("QuickCalendarWindow", "Range based", 0, QApplication::UnicodeUTF8));
        mainMenu->setTitle(QApplication::translate("QuickCalendarWindow", "QuickCalendar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class QuickCalendarWindow: public Ui_QuickCalendarWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUICKCALENDARWINDOW_H
