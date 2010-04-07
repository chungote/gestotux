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
#include "vcalendario.h"

#include <QList>
#include <QColor>
#include <QPixmap>
#include <QIcon>
#include <QDockWidget>

VCalendario::VCalendario(QWidget *parent) :
    EVentana(parent)
{
    this->setObjectName( "VentanaCalendario" );

   /* myColors << QColor(56, 128, 189)
    << QColor(249, 162, 57)
    << QColor(0, 139, 70)
    << QColor(237, 19, 93)
    << QColor(165, 93, 38)
    << QColor(239, 71, 63)
    << QColor(132, 199, 112)
    << QColor(0, 90, 157);

    QListIterator <QColor> i(myColors);
    while(i.hasNext())
    {
        QColor color = i.next();
        QPixmap pixmap(24, 24);
        pixmap.fill(color);
        QIcon icon;
        icon.addPixmap(pixmap);
        myIcons.append(icon);
    }
*/
    ptrCalendarModel = new CalendarTableModel();
    ptrCalendarModel->setCalendars(&myCalendars);

    //cargarDatos();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);

    ptrSelectorWidget = new SelectorWidget(this);
    layout->addWidget(ptrSelectorWidget);

    ptrCalendarView = new QuickCalendarView();
    ptrCalendarView->setCalendars(&myCalendars);
    ptrCalendarView->setMonth(QDate::currentDate().year(), QDate::currentDate().month());
    layout->addWidget(ptrCalendarView);

    this->setLayout(layout);

    createDockWidgets();

   /* connect(ptrSelectorWidget,
            SIGNAL(monthChanged(int, int)),
            ptrCalendarView,
            SLOT(setMonth(int, int)));
    connect(ptrSelectorWidget,
            SIGNAL(rangeChanged(const QDate &, const QDate &)),
            ptrCalendarView,
            SLOT(setRange(const QDate &, const QDate &)));
    connect(ptrSelectorWidget,
            SIGNAL(modeChanged(int)),
            this,
            SLOT(modeChanged(int)));

    connect( ActMes, SIGNAL(triggered()),
            ptrSelectorWidget, SLOT(showMonthBased()));
    connect( ActSemana, SIGNAL(triggered()),
            ptrSelectorWidget, SLOT(showWeekBased()));
//    connect(dayAction, SIGNAL(triggered()),
//            ptrSelectorWidget, SLOT(showDayBased()));
    connect( ActRango, SIGNAL(triggered()),
            ptrSelectorWidget, SLOT(showRangeBased()));*/
    this->setWindowTitle("Calendario");
    this->setWindowIcon( QIcon( ":/imagenes/calendario.png" ) );
}

void VCalendario::closeEvent(QCloseEvent *event)
{

}

void VCalendario::createDockWidgets()
{
    ptrTableView = new QTableView();
    ptrTableView->setModel(ptrCalendarModel);
    ptrTableView->setSelectionMode(QAbstractItemView::NoSelection);
    ptrTableView->setGridStyle(Qt::NoPen);
    ptrTableView->setDragDropMode(QAbstractItemView::NoDragDrop);
    ptrTableView->setSelectionMode(QAbstractItemView::NoSelection);
    ptrTableView->horizontalHeader()->hide();
    ptrTableView->verticalHeader()->hide();
    ptrTableView->resizeColumnsToContents();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->addWidget(ptrTableView);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);
    //widget->setGeometry(0,0,100,100);

    QDockWidget *dock = new QDockWidget();
    dock->setWindowTitle( tr("Calendarios") );
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(widget);
    emit agregarDockWidget( Qt::LeftDockWidgetArea, dock);


    connect( ptrCalendarModel, SIGNAL( dataChanged( const QModelIndex &, const QModelIndex & ) ),
            this, SLOT( dataChanged( const QModelIndex &, const QModelIndex & ) ) );
}


void VCalendario::dataChanged(const QModelIndex &topLeft,
                                      const QModelIndex &bottomRight)
{
    ptrCalendarView->dataChanged();
    ptrCalendarView->layoutChanged();

    //update();
}

void VCalendario::modeChanged(int mode)
{
    if(mode == 0)
    {
        ptrCalendarView->setDisplayMode(QuickCalendarView::DisplayFullWeeks);
    }else
    {
        ptrCalendarView->setDisplayMode(QuickCalendarView::DisplayOnlyRange);
    }
}

void VCalendario::cargarDatos()
{
 // Carga todos los calendarios que haya en la base de datos

}
