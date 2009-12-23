/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   				   *
 *   juiraze@yahoo.com.ar   						   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "eventocalendario.h"


/*!
    Sets start and end date and time.
*/
void EventoCalendario::setDateTimes(const QDateTime &startDateTime, const QDateTime &endDateTime)
{
    if(startDateTime <= endDateTime)
    {
        myStartDateTime = startDateTime;
        myEndDateTime = endDateTime;
    }
    else
    {
        myEndDateTime = myStartDateTime = startDateTime;
    }
}

/*!
    Sets start and end time.
*/
void EventoCalendario::setTimes(const QTime &startTime, const QTime &endTime)
{
    if(startTime <= endTime)
    {
        myStartDateTime.setTime(startTime);
        myEndDateTime.setTime(endTime);
    }
    else
    {
        myStartDateTime.setTime(startTime);
        myEndDateTime.setTime(endTime);
    }
}

/*!
    Sets start date and time.
*/
void EventoCalendario::setStartDateTime(const QDateTime &startDateTime)
{
    if(startDateTime <= myEndDateTime)
    {
        myStartDateTime = startDateTime;
    }else
    {
        myStartDateTime = myEndDateTime;
    }
}

/*!
    Sets end and end date and time.
*/
void EventoCalendario::setEndDateTime(const QDateTime &endDateTime)
{
    if(endDateTime >= myStartDateTime)
    {
        myEndDateTime = endDateTime;
    }else
    {
        myEndDateTime = myStartDateTime;
    }
}

/*!
    Gets number of quarter when EventoCalendario starts.
*/
int EventoCalendario::startQuater(const QDate &date) const
{
    QTime time = myStartDateTime.time();

    if(date == myStartDateTime.date())
        return ((time.hour() * 60) + time.minute()) / 15;
    else if(date <= myEndDateTime.date())
        return 0;
    else
        return -1;
}

/*!
    Gets number of quarter when EventoCalendario ends.
*/
int EventoCalendario::endQuater(const QDate &date) const
{
    QTime time = myEndDateTime.time();

    if(date == myEndDateTime.date())
        return ((time.hour() * 60) + time.minute()) / 15;
    else if(myEndDateTime.date() > date)
        return (24 * 60) / 15;
    else
        return -1;
}

bool EventoCalendario::before(EventoCalendario *app1, EventoCalendario *app2)
{
    return app1->startDateTime() < app2->startDateTime();
}

/*!
    Compares EventoCalendarios by key values.
*/
bool EventoCalendario::operator==(const EventoCalendario &other) const {
    if(this == &other)
        return true;
    else if(other.myKey == myKey)
        return true;
    else
        return false;
}

/*!
    Compares EventoCalendarios by key values.
*/
bool EventoCalendario::operator!=(const EventoCalendario &other) const {
    return !(*this == other);
}


bool EventoCalendario::operator<(const EventoCalendario &other) const {
    if(this == &other)
        return false;
    else if(other.myStartDateTime > myStartDateTime)
        return true;
    else
        return false;
}
