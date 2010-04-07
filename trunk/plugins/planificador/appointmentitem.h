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

#ifndef APPOINTMENTITEM_H
#define APPOINTMENTITEM_H

#include <QColor>
#include <QFont>
#include <QString>

#include "appointment.h"
#include "calendaritem.h"
#include "dayitem.h"

/*!
    \class AppointmentItem
    \brief Graphics view item for appointments.
*/

class AppointmentItem : public CalendarItem
{

public:
    AppointmentItem(Appointment *appointment,
                    DayItem *dayItem,
                    QGraphicsItem *parent = 0,
                    QGraphicsScene *scene = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                QWidget *widget);

    int column() const { return myColumn; }
    void setColumn(int column) { myColumn = column; }

    int columnSpan() const { return myColumnSpan; }
    void setColumnSpan(int columnSpan) { myColumnSpan = columnSpan; }

    void layoutChanged();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    Appointment *ptrAppointment;
    DayItem *ptrDayItem;
    QColor myColor;
    QFont myFont;
    QString mySubject;

    int myColumn;
    int myColumnSpan;

    friend class DayContentItem;
};


#endif
