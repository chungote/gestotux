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

#ifndef QUICKCALENDARSTYLE_H
#define QUICKCALENDARSTYLE_H

#include <QFont>
#include <QList>
#include <QDate>
#include <QLinearGradient>
#include <QPen>

class QuickCalendarStyle
{

public:
    QuickCalendarStyle();

    QFont weekNumberFont;
    QFont dayNumberFont;
    QFont dayNameFont;

    QFont appointmentSubjectFont;
    QFont clockBarFont;

    int weekLeftMargin;
    int weekRightMargin;
    int quarterHeight;

    int expandedWeekHeaderHeight;

    QPen pastDayPen;
    QPen todayPen;
    QPen comingDayPen;

    QLinearGradient pastDayGradient;
    QLinearGradient todayGradient;
    QLinearGradient comingDayGradient;
    
    QLinearGradient pastWeekendGradient;
    QLinearGradient weekendGradient;
    QLinearGradient comingWeekendGradient;

    QFont expandedDayNumberFont;
    QFont collapsedDayNumberFont;

    int collapsedWeekHeight() const;
};


#endif
