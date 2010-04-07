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
#include "daycontentitem.h"
#include "appointmentitem.h"
#include "appointmentdetailsform.h"
#include "weekitem.h"
#include "dayitem.h"
#include "quickcalendarview.h"

DayContentItem::DayContentItem(DayItem *dayItem, QGraphicsItem *parent, QGraphicsScene *scene) : 
    CalendarItem(parent, scene), ptrDayItem(dayItem)
{
    myColumns = 1;
    dragStart = dragEnd = 0;
    dragSelection = false;

    setHandlesChildEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setAcceptsHoverEvents(true);
}

void DayContentItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int left = 0;
    int width = (int)myBoundingRect.width();
    int height = (int)myBoundingRect.height();

    if(ptrDayItem->myDate.dayOfWeek() < 6)
    {
        painter->setBrush(QBrush(QColor(255,255,233)));
        painter->drawRect(0,height/3,width,height/3);

        painter->setBrush(QBrush(QColor(233,233,233)));
        painter->drawRect(0,0,width,height/3);
        painter->drawRect(0,(height*2)/3,width,height/3);
    }else
    {
        painter->setBrush(QBrush(QColor(225,225,203)));
        painter->drawRect(0,height/3,width,height/3);

        painter->setBrush(QBrush(QColor(203,203,203)));
        painter->drawRect(0,0,width,height/3);
        painter->drawRect(0,(height*2)/3,width,height/3);
    }

    painter->setPen(QPen(QColor(127,127,127)));
    for(int i=0;i<24;i++)
    {
        painter->drawLine(left, i*10*4, left+width, i*10*4);
    }

    painter->setPen(QPen(QColor(191,191,191)));
    for(int i=0;i<24;i++)
    {
        painter->drawLine(left, i*10*4 + 10 * 2, left+width, i*10*4 + 10 * 2);
    }

    if(option->state & QStyle::State_MouseOver)
    {
    }

    // Selection
    if(dragSelection)
    {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QBrush(QColor(0,63,255,127)));
        painter->drawRect(0, dragStart, width, dragEnd);
    }
}

void DayContentItem::dataChanged()
{
    qDeleteAll(childItems());

    int minEndTime = 0;
    int currentColumn = 0;
    QVector<int> columns;
    columns << 0;

    QListIterator <Appointment *> i(ptrDayItem->myAppointments);
    while(i.hasNext())
    {
        Appointment *appointment = i.next();

        AppointmentItem *item = new AppointmentItem(appointment, ptrDayItem, this);

        minEndTime = 24 * 4;

        for(int j=0;j<columns.size();j++)
        {
            if(columns[j] < minEndTime)
            {
                minEndTime = columns[j];
                currentColumn = j;
            }
        }

        if(appointment->startQuater(ptrDayItem->myDate) < minEndTime)
        {
            item->setColumn(columns.size());
            item->setColumnSpan(1);
            columns.append(appointment->endQuater(ptrDayItem->myDate));
        }else{

            int beginTime = appointment->startQuater(ptrDayItem->myDate);
            int columnSpan = 1;

            for(int j=0;j<columns.size();j++)
            {
                if(columns[j] <= beginTime)
                {
                    int width = 1;
                    for(int k=j+1;k<columns.size();k++)
                    {
                        if(columns[k] <= beginTime)
                        {
                            width++;
                        }else
                        {
                            break;
                        }
                    }

                    if(width > columnSpan)
                    {
                        columnSpan = width;
                        currentColumn = j;
                    }
                }
            }

            item->setColumn(currentColumn);
            item->setColumnSpan(columnSpan);

            for(int j=currentColumn;j<currentColumn+columnSpan;j++)
                columns[j] = appointment->endQuater(ptrDayItem->myDate);
        }
    }

    myColumns = columns.size();
}


void DayContentItem::layoutChanged()
{
    int left = 0;
        //int top = 0;
    int width = (int)myBoundingRect.width();
        //int height = myBoundingRect.height();

    int quarterHeight = 10;

    int columnWidth = width / myColumns;

    QListIterator <QGraphicsItem *> j(childItems());
    while(j.hasNext())
    {
        AppointmentItem *item = (AppointmentItem *)j.next();

        const Appointment *appointment = item->ptrAppointment;

        int itemTop = quarterHeight * appointment->startQuater(ptrDayItem->myDate);
        int itemHeight = (quarterHeight * appointment->endQuater(ptrDayItem->myDate)) - itemTop;

        if(item->column() == 0){
            item->setPos(left + (columnWidth * item->column()),itemTop);
            item->setSize((width%myColumns) + (columnWidth*item->columnSpan()),itemHeight);
        }else
        {
            item->setPos(left + (width%myColumns) + (columnWidth * item->column()), itemTop);
            item->setSize(columnWidth*item->columnSpan(),itemHeight);
        }

        item->layoutChanged();
    }
}

void DayContentItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->scenePos();

    QListIterator <QGraphicsItem *> j(childItems());
    while(j.hasNext())
    {
        AppointmentItem *item = (AppointmentItem *)j.next();
        if(item->sceneBoundingRect().contains(pos))
        {
            ptrDayItem->ptrCalendarView->showAppointmentForm(item->ptrAppointment);
        }
    }
}

void DayContentItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int y = (int)event->pos().y();
    dragStart = (int)event->pos().y() - y%20;
    dragEnd = 0;
    dragSelection = true;
}

void DayContentItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(dragSelection)
    {
        int y = (int)event->pos().y();
        dragEnd = y + 20 - y%20 - dragStart;

        //ptrDayItem->ptrWeekItem->myScrollArea.ensureVisibility(0, event->pos().y());

        update();
    }
}

void DayContentItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(dragSelection && dragEnd != 0)
    {
        int startHour = dragStart / 40;
        int startMinute = 0;
        if(dragStart%40 > 0)
            startMinute = 30;
        QDateTime start(ptrDayItem->myDate, QTime(startHour, startMinute, 0));

        int endHour = (dragStart + dragEnd) / 40;
        int endMinute = 0;
        if((dragStart + dragEnd)%40 > 0)
            endMinute = 30;
        if(endHour == 24)
        {
            endHour = 23;
            endMinute = 59;
        }
        QDateTime end(ptrDayItem->myDate, QTime(endHour, endMinute, 0));

        Appointment *appointment = new Appointment();

        if(startHour < endHour)
            appointment->setDateTimes(start, end);
        else
            appointment->setDateTimes(end, start);

        ptrDayItem->ptrCalendarView->showAppointmentForm(appointment);

        dragSelection = false;
        update();
    }
}
