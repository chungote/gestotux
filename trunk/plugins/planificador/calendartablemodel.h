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

#ifndef CALENDARMODEL_H
#define CALENDARMODEL_H

#include <QSqlTableModel>
#include <QColor>
#include <QList>
#include <QModelIndex>

#include "calendar.h"

class CalendarTableModel : public QSqlTableModel
{
    Q_OBJECT

public:
    CalendarTableModel(QObject *parent = 0);
    ~CalendarTableModel() {}

    QVariant data(const QModelIndex &index, int role) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

};

#endif
