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

#include "appointmentdetailsform.h"
#include "quickcalendarview.h"
#include "dayitem.h"
#include "weekdayheaderitem.h"

QuickCalendarView::QuickCalendarView(QWidget *parent) :
        QGraphicsView(new QGraphicsScene(), parent)
{
    ptrStyle = new QuickCalendarStyle();
    myDisplayMode = DisplayFullWeeks;

    ptrContentPane = new CalendarItem();
    scene()->addItem(ptrContentPane);

    ptrHeader = new CalendarItem();
    
    scene()->addItem(ptrHeader);
    scene()->setBackgroundBrush(QColor(127, 127, 127));

    for(int i=1;i<=7;i++)
    {
        WeekDayHeaderItem *item = new WeekDayHeaderItem(this, i, ptrHeader);
    }

    myExpandedDayOfWeek = 0;
    myExpandedWeekItem = 0;

    myExpandedDate = QDate(0,0,0);

    myWeekCount = 0;

    ptrCalendars = new QList <Calendar *>();

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameShape(QFrame::NoFrame);
    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
}

void QuickCalendarView::setDisplayMode(DisplayMode mode)
{
    if(mode != myDisplayMode)
    {
        myDisplayMode = mode;
        setRange(myRangeStart, myRangeEnd);
    }
}

void QuickCalendarView::setRange(const QDate &start,
                                 const QDate &end)
{
    //TODO optioimti jos on sama päivä kuin mitä jo näytettään

    collapseAll();
    //qDeleteAll(myWeeks);
    if(myWeeks.count() > 0)
    {
      qDeleteAll(myWeeks);
      myWeeks.clear();
    }

    myRangeStart = start;
    myRangeEnd = end;

    if(myRangeEnd < myRangeStart)
        myRangeEnd = myRangeStart;

    if(myRangeStart.daysTo(myRangeEnd) > (7*10)-1)
        myRangeEnd = myRangeStart.addDays((7*10)-1);

    if(myDisplayMode == DisplayFullWeeks)
    {
        myStartDate = myRangeStart.addDays(-(myRangeStart.dayOfWeek() - 1));
        myEndDate = myRangeEnd.addDays(7-myRangeEnd.dayOfWeek());

        myWeekCount = (myStartDate.daysTo(myEndDate) + 1) / 7;

        for(int i=0;i<myWeekCount;i++)
        {
            WeekItem *week;
            if(i==0)
                week = new WeekItem(this, myRangeStart, myRangeEnd, ptrContentPane);
            else
                week = new WeekItem(this, myStartDate.addDays(i*7), myRangeEnd, ptrContentPane);

            myWeeks.append(week);
        }
        dataChanged();

        if(myWeekCount == 1)
            expandWeek(myWeeks.at(0));
        else
            layoutChanged();

    }else if(myDisplayMode == DisplayOnlyRange)
    {
        myStartDate = myRangeStart;

        if(myRangeStart.daysTo(myRangeEnd) > 13)
            myRangeEnd = myRangeStart.addDays(13);

        myEndDate = myRangeEnd;

        WeekItem *week = new WeekItem(this, myStartDate, myEndDate, ptrContentPane);
        myWeeks.append(week);

        myWeekCount = 1;
        dataChanged();
        expandWeek(week);
    }
}

void QuickCalendarView::setMonth(int year, int month)
{
    QDate start(year, month, 1);
    QDate end = start.addDays(start.daysInMonth() - 1);

    setRange(start, end);
}

void QuickCalendarView::setCalendars(QList <Calendar *> *calendars)
{
    ptrCalendars = calendars;
}

void QuickCalendarView::expandDate(const QDate &date)
{
    bool weekChanged = false;

    if(date != myExpandedDate)
    {
        QListIterator <WeekItem *> i(myWeeks);
        while(i.hasNext())
        {
            WeekItem *week = i.next();

            int dayOfWeek = week->dayOfWeek(date);
            if(dayOfWeek >= 0)
            {
                if(myExpandedWeekItem != week)
                    weekChanged = true;

                myExpandedWeekItem = week;                
                myExpandedDayOfWeek = dayOfWeek;
                myExpandedDate = date;
                i.toBack();

                emit dateExpanded(date);
            }
        }
    }else
    {
        myExpandedDayOfWeek = 0;
        myExpandedDate = QDate(0,0,0);
    }

    layoutChanged();

    if(myExpandedWeekItem != 0 && weekChanged)
        myExpandedWeekItem->ptrScrollArea->scrollTo(ptrStyle->quarterHeight * 4 * 7);
}

void QuickCalendarView::expandWeek(int number)
{
    QListIterator <WeekItem*> i(myWeeks);
    while(i.hasNext())
    {
        WeekItem *week = i.next();

        if(week->myDate.weekNumber() == number)
        {
            expandWeek(week);
            i.toBack();
        }
    }
}

void QuickCalendarView::expandWeek(WeekItem *week)
{
    if(week != myExpandedWeekItem)
    {
        myExpandedWeekItem = week;
    }else
    {
        if(myWeeks.count() > 1)
        {
            myExpandedWeekItem = 0;
            myExpandedDayOfWeek = 0;
            myExpandedDate = QDate(0,0,0);
        }
    }

    layoutChanged();

    if(myExpandedWeekItem != 0)
        myExpandedWeekItem->ptrScrollArea->scrollTo(ptrStyle->quarterHeight * 4 * 7);
}

int QuickCalendarView::expandedWeekNumber() const
{
    if(myExpandedWeekItem != 0)
        return myExpandedWeekItem->myDate.weekNumber();
    else
        return 0;
}

void QuickCalendarView::collapseAll()
{
    if(myExpandedWeekItem != 0)
    {
        if(myWeeks.count() > 1)
        {
            myExpandedWeekItem = 0;
            myExpandedDayOfWeek = 0;
            myExpandedDate = QDate(0,0,0);
            layoutChanged();
        }
    }
}

void QuickCalendarView::resizeEvent(QResizeEvent *event)
{
    layoutChanged();
}

void QuickCalendarView::layoutChanged()
{
    if(myWeeks.count() == 0)
        return;

    int width = this->width();
    int height = this->height();


    setSceneRect(0,0,width,height);

    // Calculate day widths
    int workAreaWidth = width - ptrStyle->weekLeftMargin - ptrStyle->weekRightMargin;

    for(int i=0;i<21;i++)
        myDayWidths[i] = 0;

    int dayCount;
    int firstDay = 0;

    if(myDisplayMode == DisplayFullWeeks)
        dayCount = 7;
    else if(myDisplayMode == DisplayOnlyRange)
    {
        firstDay = myStartDate.dayOfWeek() - 1;
        dayCount = myStartDate.daysTo(myEndDate) + 1;
    }

    if(dayCount > 1)
    {
        if(myExpandedDayOfWeek != 0)
        {
            int expandedDayWidth = (workAreaWidth / 3) * 2;
            workAreaWidth -= expandedDayWidth;
            int dayWidth = workAreaWidth / (dayCount - 1);
            int mod = workAreaWidth % (dayCount - 1);

            for(int i=firstDay;i<firstDay+dayCount;i++)
            {
                if(i == firstDay + myExpandedDayOfWeek - 1)
                {
                    myDayWidths[i] = expandedDayWidth + mod;
                }else
                {
                    myDayWidths[i] = dayWidth;
                }
            }
        }else
        {
            int dayWidth = workAreaWidth / dayCount;
            int mod = workAreaWidth % dayCount;

            for(int i=firstDay;i<firstDay+dayCount;i++)
            {
                myDayWidths[i] = dayWidth;
            }
            myDayWidths[firstDay] += mod;
        }
    }else
    {
        myDayWidths[firstDay] = workAreaWidth;
    }

//    for(int i=0;i<21;i++)
//    {
//        qDebug(qPrintable("W: [" + QString::number(i) + "] = " + QString::number(myDayWidths[i])));
//    }

    int weekTop = 0;
    int weekHeight = 0;
    int expandedWeekHeight = 0;

    if(myWeekCount > 1)
    {
        int headerLeft = 0;
        int headerCount = 0;
        int headerHeight = 40 + (height - 40)%myWeeks.count();

        ptrHeader->setPos(ptrStyle->weekLeftMargin, 0);
        ptrHeader->setSize(width, headerHeight);
        ptrHeader->setVisible(true);

        QListIterator <QGraphicsItem *> i(ptrHeader->childItems());
        while(i.hasNext())
        {
            WeekDayHeaderItem *item = (WeekDayHeaderItem *)i.next();
            item->setPos(headerLeft, 0);
            item->setSize(myDayWidths[headerCount], headerHeight);
            item->layoutChanged();

            headerLeft += myDayWidths[headerCount];

            headerCount++;
        }

        weekTop = headerHeight;
    }else
    {
        ptrHeader->setVisible(false);
    }

    if(myExpandedWeekItem != 0)
    {
        expandedWeekHeight = (height - weekTop) - ((myWeekCount - 1) *
                                  ptrStyle->collapsedWeekHeight());
        weekHeight = ptrStyle->collapsedWeekHeight();
    }else
    {
        weekHeight = (height - weekTop)/myWeeks.count();
    }

    for(int i=0;i<myWeeks.count();i++)
    {
        WeekItem *week = myWeeks.at(i);

        week->setPos(0, weekTop);
        if(week == myExpandedWeekItem)
        {
            week->setSize(width, expandedWeekHeight);
            weekTop += expandedWeekHeight;
        }else
        {
            week->setSize(width, weekHeight);
            weekTop += weekHeight;
        }

        week->layoutChanged();        
    }

    //update();
}

void QuickCalendarView::showAppointmentForm(Appointment *appointment)
{
    bool someSelected = false;

    for(int i=0;i<ptrCalendars->count();i++)
    {
        if(ptrCalendars->at(i)->isSelected())
            someSelected = true;
    }

    if(!someSelected)
    {
        QMessageBox::warning(0, QObject::tr("Calendar error"), QObject::tr("Select at least one calendar first!"));
        return;
    }

    if(ptrCalendars->count() > 0)
    {
        AppointmentDetailsForm *form = new AppointmentDetailsForm(appointment,
                                                                  ptrCalendars);

        connect(form, SIGNAL(onClose(Appointment*)), this, SLOT(onFormClosed(Appointment*)));

        if(appointment->key() == 0)
            form->deleteAppointmentButton->hide();

        form->setGeometry(300,300,400,250);
        form->show();

    }
}

void QuickCalendarView::dataChanged()
{
    QListIterator <WeekItem *> i(myWeeks);
    while(i.hasNext())
    {
        WeekItem *week = i.next();
        week->dataChanged();
    }    
}

void QuickCalendarView::onFormClosed(Appointment *appointment)
{
    if(appointment != 0)
    {
        dataChanged();
        layoutChanged();
    }
}

void QuickCalendarView::expandDayOfWeek(int dayOfWeek)
{
    if(myExpandedWeekItem != 0)
    {
        if(dayOfWeek != myExpandedDayOfWeek)
            myExpandedDayOfWeek = dayOfWeek;
        else
            myExpandedDayOfWeek = 0;

        layoutChanged();
    }
}
