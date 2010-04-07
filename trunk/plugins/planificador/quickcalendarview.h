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

#ifndef QUICKCALENDARVIEW_H
#define QUICKCALENDARVIEW_H

#include <QGraphicsView>
#include <QList>

#include "calendaritem.h"
#include "quickcalendarstyle.h"
#include "weekitem.h"
#include "calendar.h"
#include "appointment.h"

class QuickCalendarView : public QGraphicsView
{
    Q_OBJECT

public:
    QuickCalendarView(QWidget *parent = 0);
    ~QuickCalendarView() {}

    enum DisplayMode{
      DisplayFullWeeks = 0,
      DisplayOnlyRange = 1,
    };

    int displayMode() const { return myDisplayMode; }

    int expandedDayOfWeek() const { return myExpandedDayOfWeek; }

    int expandedWeekNumber() const;

    WeekItem* expandedWeekItem() const { return myExpandedWeekItem; }

    int weekCount() const { return myWeekCount; }

    int dayWidth(int dayOfWeek) const {
        if(dayOfWeek >= 0 && dayOfWeek < 21) return myDayWidths[dayOfWeek]; else return 0;
    }


    QuickCalendarStyle* style() const { return ptrStyle; }

    QList <Calendar*>* calendars() { return ptrCalendars; }

signals:
    void dateExpanded(const QDate &date);

public slots:
    void expandDate(const QDate &date);
    void expandDayOfWeek(int dayOfWeek);
    void expandWeek(int weekNumber);
    void expandWeek(WeekItem *week);
    void collapseAll();

    void setRange(const QDate &start, const QDate &end);
    void setMonth(int year, int month);

    void setDisplayMode(DisplayMode mode);
    void setCalendars(QList <Calendar *> *calendars);

    void showAppointmentForm(Appointment *appointment);

    void dataChanged();
    void layoutChanged();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void onFormClosed(Appointment *appointment);

private:
    int myWeekMode;
    int myDisplayMode;

    QDate myStartDate;
    QDate myEndDate;

    QDate myRangeStart;
    QDate myRangeEnd;

    QDate myExpandedDate;

    int myWeekCount;

    CalendarItem *ptrHeader;
    CalendarItem *ptrContentPane;

    QList <WeekItem *> myWeeks;

    int myExpandedDayOfWeek;
    WeekItem *myExpandedWeekItem;

    QuickCalendarStyle *ptrStyle;

    int myDayWidths[21];

    QList <Calendar *> *ptrCalendars;
};

#endif // QUICKCALENDARVIEW_H
