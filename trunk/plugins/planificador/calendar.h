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

#ifndef CALENDAR_H
#define CALENDAR_H

#include <QColor>
#include <QList>
#include <QMetaType>
#include <QString>

#include "appointment.h"
/*!
    \class Calendar
    \brief Class to hold data for calendars.
*/

class Calendar
{
public:
    Calendar(int key) : mySelected(false), myColor(255,0,0), myCounter(0) { myKey = key; }
    ~Calendar() { qDeleteAll(myAppointments); }

    int key() const {return myKey;}
    void setKey(int key) {myKey = key;}

    QString name() const {return myName;}
    void setName(const QString &name) {myName = name;}

    QString description() const {return myDescription;}
    void setDescription(const QString &description) {myDescription = description;}

    bool isSelected() const { return mySelected; }
    void setSelected(bool selected) { mySelected = selected; }

    QColor color() const { return myColor; }
    void setColor(const QColor &color) { myColor = color; }

    QList <Appointment *> getAppointments(const QDate &date);
    bool insertAppointment(Appointment *appointment);
    bool updateAppointment(const Appointment &appointment);
    bool removeAppointment(Appointment *appointment);

    bool operator==(const Calendar &other) const;
    bool operator!=(const Calendar &other) const;
private:
    int myKey;

    bool mySelected;

    QColor myColor;

    QString myName;
    QString myDescription;

    QList <Appointment *> myAppointments;

    int myCounter;
};

//Q_DECLARE_METATYPE(Calendar)

#endif
