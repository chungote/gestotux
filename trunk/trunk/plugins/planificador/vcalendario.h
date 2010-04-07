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

#ifndef VCALENDARIO_H
#define VCALENDARIO_H

#include "eventana.h"
#include <QTableView>
#include "ui_quickcalendarwindow.h"
#include "quickcalendarview.h"
#include "selectorwidget.h"
#include "calendar.h"
#include "calendartablemodel.h"

class VCalendario : public EVentana
{
Q_OBJECT
public:
    explicit VCalendario(QWidget *parent = 0);

protected:
    void closeEvent(QCloseEvent *event);
    void createDockWidgets();

private slots:
    void onExit();
    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    void modeChanged(int mode);

private:
    void cargarDatos();

    QList <QColor> myColors;
    QList <QIcon> myIcons;

    QuickCalendarView *ptrCalendarView;
    SelectorWidget *ptrSelectorWidget;
    QTableView *ptrTableView;
    CalendarTableModel *ptrCalendarModel;

    QList <Calendar *> myCalendars;

    QAction *ActMes;
    QAction *ActSemana;
    QAction *ActRango;

 signals:
    void agregarVentana( QWidget * );
    void agregarDockWidget( Qt::DockWidgetArea area, QDockWidget *ventana );
};

#endif // VCALENDARIO_H
