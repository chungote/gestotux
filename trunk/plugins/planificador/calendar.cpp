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

#include "calendar.h"

/*!
    Compares calendars by key values.
*/
bool Calendar::operator==(const Calendar &other) const {
    if(this == &other)
        return true;
    else if(other.myKey == myKey)
        return true;
    else
        return false;
}

/*!
    Compares calendars by key values.
*/
bool Calendar::operator!=(const Calendar &other) const {
    return !(*this == other);
}

QList <Appointment *> Calendar::getAppointments(const QDate &date)
{
    QList <Appointment *> result;

    QListIterator <Appointment *> i(myAppointments);
    while(i.hasNext())
    {
        Appointment *app = i.next();

        if(app->startDate() == date ||
           app->endDate() == date ||
           (app->startDate() < date && app->endDate() > date))
        {
            result.append(app);
        }
    }
    return result;
}

bool Calendar::insertAppointment(Appointment *appointment)
{
    if(appointment->key() == 0)
    {
        appointment->setKey(myCounter);
        appointment->setCalendar(this);
        myCounter++;
    }

    if(!myAppointments.contains(appointment))
    {
        myAppointments.append(appointment);
        return true;
    }

    return false;
}

bool Calendar::updateAppointment(const Appointment &appointment)
{
//    if(!ptrAppointments->contains(appointment))
//    {
//        ptrAppointments->replace(ptrAppointments->indexOf(appointment), appointment);
//        return true;
//    }

    return false;

}

bool Calendar::removeAppointment(Appointment *appointment)
{
    return myAppointments.removeOne(appointment);
}
