/*******************************************************************************

    Copyright (C) 2008 Jukka-Pekka Mäkelä.
    Contact: jpm@mehteenit.net

    This file is part of QuickCalendar.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QuickCalendar.  If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************/

#include <QtCore>
#include <QtGui>

#include "quickcalendarwindow.h"
#include "quickcalendarview.h"

QuickCalendarWindow::QuickCalendarWindow()
{
    //setupUi(this);

    myColors << QColor(56, 128, 189)
    << QColor(249, 162, 57)
    << QColor(0, 139, 70)
    << QColor(237, 19, 93)
    << QColor(165, 93, 38)
    << QColor(239, 71, 63)
    << QColor(132, 199, 112)
    << QColor(0, 90, 157);

    QListIterator <QColor> i(myColors);
    while(i.hasNext())
    {
        QColor color = i.next();
        QPixmap pixmap(24, 24);
        pixmap.fill(color);
        QIcon icon;
        icon.addPixmap(pixmap);
        myIcons.append(icon);
    }

    ptrCalendarModel = new CalendarTableModel();
    ptrCalendarModel->setCalendars(&myCalendars);

    //generateData();
}

void QuickCalendarWindow::generateData()
{
    // Holiday calendar

    Calendar *cal = new Calendar(0);
    cal->setName("Holiday Calendar");
    cal->setColor(myColors.at(0));
    cal->setSelected(false);
    myCalendars.append(cal);

    Appointment *app = new Appointment();
    app->setDateTimes(QDateTime(QDate(2008,12,23),QTime(19,0,0)),
                     QDateTime(QDate(2008,12,23),QTime(23,0,0)));

    app->setSubject("Holiday party!");
    app->setPlace("Secret place");
    app->setDescription("Secret holiday party at secret place. Everybody is welcome!");
    cal->insertAppointment(app);

    app = new Appointment();
    app->setDateTimes(QDateTime(QDate(2008,12,24),QTime(12,0,0)),
                     QDateTime(QDate(2008,12,24),QTime(23,59,0)));

    app->setSubject("Christmas party!");
    app->setPlace("Everywhere");
    app->setDescription("Everybody is welcome!");
    cal->insertAppointment(app);

    // Work Calendar

    cal = new Calendar(1);
    cal->setName("Work Calendar");
    cal->setColor(myColors.at(1));
    cal->setSelected(false);
    myCalendars.append(cal);

    app = new Appointment();
    app->setDateTimes(QDateTime(QDate(2008,12,22),QTime(9,0,0)),
                     QDateTime(QDate(2008,12,22),QTime(11,00,0)));
    app->setSubject("Meeting");
    app->setPlace("Somewhere");
    app->setDescription("Remember this meeting!");
    cal->insertAppointment(app);

    app = new Appointment();
    app->setDateTimes(QDateTime(QDate(2008,12,22),QTime(11,00,0)),
                     QDateTime(QDate(2008,12,22),QTime(12,30,0)));
    app->setSubject("Lunch with Boss");
    app->setPlace("Hilton");
    app->setDescription("Good food.");
    cal->insertAppointment(app);

    app = new Appointment();
    app->setDateTimes(QDateTime(QDate(2008,12,23),QTime(10,00,0)),
                     QDateTime(QDate(2008,12,23),QTime(11,00,0)));
    app->setSubject("Call to collegue");
    cal->insertAppointment(app);

    // QuickCalendar

    cal = new Calendar(2);
    cal->setName("QuickCalendar");
    cal->setColor(myColors.at(2));
    cal->setSelected(false);
    myCalendars.append(cal);

    app = new Appointment();
    app->setDateTimes(QDateTime(QDate(2008,12,22),QTime(8,0,0)),
                     QDateTime(QDate(2008,12,22),QTime(23,59,0)));
    app->setSubject("Rewrite QuickCalendar");
    app->setPlace("Home");
    app->setDescription("Rewrite QuickCalendar to better meet contest requirements.");
    cal->insertAppointment(app);

    app = new Appointment();
    app->setDateTimes(QDateTime(QDate(2008,12,23),QTime(8,0,0)),
                     QDateTime(QDate(2008,12,23),QTime(23,59,0)));
    app->setSubject("Finish QuickCalendar");
    app->setPlace("Home");
    app->setDescription("Make QuickCalendar as ready as possible!");
    cal->insertAppointment(app);

    app = new Appointment();
    app->setDateTimes(QDateTime(QDate(2008,12,27),QTime(10,0,0)),
                     QDateTime(QDate(2008,12,27),QTime(18,30,0)));
    app->setSubject("Design and implement new features");
    app->setPlace("Home");
    app->setDescription("Design and implement new features!");
    cal->insertAppointment(app);

    // Personal Calendar

    cal = new Calendar(3);
    cal->setName("Personal calendar");
    cal->setColor(myColors.at(3));
    cal->setSelected(false);
    myCalendars.append(cal);

    app = new Appointment();
    app->setDateTimes(QDateTime(QDate(2008,12,23),QTime(16,0,0)),
                     QDateTime(QDate(2008,12,23),QTime(19,0,0)));
    app->setSubject("Shopping");
    app->setPlace("Everywhere");
    app->setDescription("Buy some Christmas presents!");
    cal->insertAppointment(app);

    app = new Appointment();
    app->setDateTimes(QDateTime(QDate(2008,12,26),QTime(10,0,0)),
                     QDateTime(QDate(2008,12,26),QTime(23,59,0)));
    app->setSubject("Family meeting");
    app->setPlace("Pamis");
    app->setDescription("Do not miss this!");
    cal->insertAppointment(app);

    app = new Appointment();
    app->setDateTimes(QDateTime(QDate(2008,12,27),QTime(19,0,0)),
                     QDateTime(QDate(2008,12,27),QTime(23,59,0)));
    app->setSubject("Dining with friends");
    app->setPlace("Downtown");
    app->setDescription("");
    cal->insertAppointment(app);

    app = new Appointment();
    app->setDateTimes(QDateTime(QDate(2008,12,28),QTime(8,0,0)),
                     QDateTime(QDate(2008,12,28),QTime(23,59,0)));
    app->setSubject("Try to relax...");
    app->setPlace("Home");
    app->setDescription("Relax after \"hard\" week.");
    cal->insertAppointment(app);
}

void QuickCalendarWindow::startUp()
{
    QWidget *central = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setMargin(0);

    ptrSelectorWidget = new SelectorWidget(this);
    layout->addWidget(ptrSelectorWidget);

    ptrCalendarView = new QuickCalendarView();
    ptrCalendarView->setCalendars(&myCalendars);
    ptrCalendarView->setMonth(QDate::currentDate().year(), QDate::currentDate().month());
    layout->addWidget(ptrCalendarView);

    central->setLayout(layout);

    //setCentralWidget(central);

    createDockWidgets();

    connect(ptrSelectorWidget,
            SIGNAL(monthChanged(int, int)),
            ptrCalendarView,
            SLOT(setMonth(int, int)));
    connect(ptrSelectorWidget,
            SIGNAL(rangeChanged(const QDate &, const QDate &)),
            ptrCalendarView,
            SLOT(setRange(const QDate &, const QDate &)));
    connect(ptrSelectorWidget,
            SIGNAL(modeChanged(int)),
            this,
            SLOT(modeChanged(int)));

    connect(monthAction, SIGNAL(triggered()),
            ptrSelectorWidget, SLOT(showMonthBased()));
    connect(weekAction, SIGNAL(triggered()),
            ptrSelectorWidget, SLOT(showWeekBased()));
//    connect(dayAction, SIGNAL(triggered()),
//            ptrSelectorWidget, SLOT(showDayBased()));
    connect(rangeAction, SIGNAL(triggered()),
            ptrSelectorWidget, SLOT(showRangeBased()));

    show();
}

void QuickCalendarWindow::onExit()
{
    exit(0);
}

void QuickCalendarWindow::closeEvent(QCloseEvent *event)
{

}

void QuickCalendarWindow::createDockWidgets()
{
    ptrTableView = new QTableView();
    ptrTableView->setModel(ptrCalendarModel);
    ptrTableView->setSelectionMode(QAbstractItemView::NoSelection);
    ptrTableView->setGridStyle(Qt::NoPen);
    ptrTableView->setDragDropMode(QAbstractItemView::NoDragDrop);
    ptrTableView->setSelectionMode(QAbstractItemView::NoSelection);
    ptrTableView->horizontalHeader()->hide();
    ptrTableView->verticalHeader()->hide();
    ptrTableView->resizeColumnsToContents();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->addWidget(ptrTableView);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    widget->setGeometry(0,0,100,100);

    QDockWidget *dock = new QDockWidget(tr("Calendars"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    dock->setWidget(widget);

    connect(ptrCalendarModel, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
            this, SLOT(dataChanged(const QModelIndex &, const QModelIndex &)));
}


void QuickCalendarWindow::dataChanged(const QModelIndex &topLeft,
                                      const QModelIndex &bottomRight)
{
    ptrCalendarView->dataChanged();
    ptrCalendarView->layoutChanged();

    //update();
}

void QuickCalendarWindow::modeChanged(int mode)
{
    if(mode == 0)
    {
        ptrCalendarView->setDisplayMode(QuickCalendarView::DisplayFullWeeks);
    }else
    {
        ptrCalendarView->setDisplayMode(QuickCalendarView::DisplayOnlyRange);
    }
}
