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
#include "appointmentitem.h"
#include "calendar.h"
#include "weekitem.h"
#include "quickcalendarview.h"

/*!
    Constructor for AppointmentItem
*/
AppointmentItem::AppointmentItem(Appointment *appointment,
                                 DayItem *dayItem,
                                 QGraphicsItem *parent,
                                 QGraphicsScene *scene) :
    CalendarItem(parent, scene),
    ptrAppointment(appointment),    
    ptrDayItem(dayItem),
    myFont("Arial", 12, QFont::Bold)
{
    myColumn = 1;
    myColumnSpan = 1;

    setFlag(QGraphicsItem::ItemIsSelectable);
}

/*!
    Paints appointment.
*/
void AppointmentItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setFont(myFont);

    painter->setPen(QPen(myColor));
    QColor color = myColor;
    color.setAlpha(159);
    painter->setBrush(QBrush(color));
    painter->drawRoundedRect(myBoundingRect, 10, 10);


    painter->setPen(QPen(QColor(255,255,255)));
    painter->drawText(myBoundingRect.adjusted(3,3,0,0),
                      Qt::AlignLeft | Qt::TextWordWrap,
                      ptrAppointment->startTime().toString("HH:mm") + " " + mySubject);
}

/*!
    Validates layout.
*/
void AppointmentItem::layoutChanged()
{
    myColor = ptrAppointment->calendar()->color();
    mySubject = ptrAppointment->subject();
}

/*!
    Handles double click events.
*/
void AppointmentItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    ptrDayItem->ptrCalendarView->showAppointmentForm(ptrAppointment);
}
