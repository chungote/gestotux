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

#ifndef EVENTOCALENDARIO_H
#define EVENTOCALENDARIO_H

#include <QDate>
#include <QDateTime>
#include <QMetaType>
#include <QString>
#include <QTime>

class VCalendario;

/*!
    \class EventoCalendario
    \brief Clse que mantiene los datos de los eventos del calendario.
*/

class EventoCalendario
{
public:
    EventoCalendario()  : myKey(0), ptrCalendar(0) {}
    ~EventoCalendario() {}
    int key() const {return myKey;}
     void setKey(int key) {myKey = key;}

     int calendarKey() const {return myCalendarKey;}
     void setCalendarKey(int calendarKey) {myCalendarKey = calendarKey;}

     VCalendario* calendar() const {return ptrCalendar;}
     void setCalendaior(VCalendario *calendar) {ptrCalendar = calendar;}

     QString subject() const {return mySubject;}
     void setSubject(const QString &subject) {mySubject = subject;}

     QString place() const {return myPlace;}
     void setPlace(const QString &place) {myPlace = place;}

     QString description() const {return myDescription;}
     void setDescription(const QString &description) {myDescription = description;}

     QTime startTime() const { return myStartDateTime.time(); }
     QDate startDate() const { return myStartDateTime.date(); }
     QDateTime startDateTime() const {return myStartDateTime;}
     void setStartDateTime(const QDateTime &startDateTime);

     QTime endTime() const { return myEndDateTime.time(); }
     QDate endDate() const { return myEndDateTime.date(); }
     QDateTime endDateTime() const {return myEndDateTime; }
     void setEndDateTime(const QDateTime &endDateTime);

     void setDateTimes(const QDateTime &startDateTime, const QDateTime &endDateTime);
     void setTimes(const QTime &startTime, const QTime &endTime);

     int startQuater(const QDate &date) const;
     int endQuater(const QDate &date) const;

     static bool before(EventoCalendario *app1, EventoCalendario *app2);

     bool operator==(const EventoCalendario &other) const;
     bool operator!=(const EventoCalendario &other) const;
     bool operator<(const EventoCalendario &other) const;

 private:
     int myKey;
     int myCalendarKey;

     VCalendario *ptrCalendar;

     QString mySubject;
     QString myPlace;
     QString myDescription;

     QDateTime myStartDateTime;
     QDateTime myEndDateTime;
};

Q_DECLARE_METATYPE(EventoCalendario)

#endif // EVENTOCALENDARIO_H
