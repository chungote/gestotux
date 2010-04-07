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

#ifndef QUICKCALENDARWINDOW_H
#define QUICKCALENDARWINDOW_H

#include <QColor>
#include <QIcon>
#include <QList>
#include <QWidget>
#include <QTableView>
#include "ui_quickcalendarwindow.h"
#include "quickcalendarview.h"
#include "selectorwidget.h"
#include "calendar.h"
#include "calendartablemodel.h"

class QuickCalendarWindow: public QWidget, public Ui::QuickCalendarWindow
{
    Q_OBJECT

public:
    QuickCalendarWindow();

    void startUp();

protected:
    void closeEvent(QCloseEvent *event);
    void createDockWidgets();

private slots:
    void onExit();
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    void modeChanged(int mode);

private:
    void generateData();

    QList <QColor> myColors;
    QList <QIcon> myIcons;

    QuickCalendarView *ptrCalendarView;
    SelectorWidget *ptrSelectorWidget;
    QTableView *ptrTableView;
    CalendarTableModel *ptrCalendarModel;

    QList <Calendar *> myCalendars;
};

#endif
