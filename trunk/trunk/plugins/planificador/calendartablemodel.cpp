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

#include <QtCore>
#include <QtGui>

#include "calendartablemodel.h"

CalendarTableModel::CalendarTableModel(QObject *parent) :
        QSqlTableModel(parent)
{
    setTable( "calendarios" );
}


QVariant CalendarTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    switch( index.column() )
    {
        case 0:
        {
            switch( role )
            {
            case Qt::TextAlignmentRole:
                { return int(Qt::AlignLeft | Qt::AlignVCenter ); }
            case Qt::DisplayRole:
            {}
            case Qt::CheckStateRole:
            {}
            }
        }
        default:
        {
            switch( role )
            {
            case Qt::TextAlignmentRole:
                { return int(Qt::AlignLeft | Qt::AlignVCenter ); }
            case Qt::BackgroundColorRole:
                {
                    // Busco el color elegido para este calendario
                    /*QColor color;
                    QString cadena = this->data( this->index( index.row(), 2 ), Qt::DisplayRole ).toString();
                    color.setRgb( QRgb( cadena ) );
                    return color;*/
                }
            case Qt::DisplayRole:
                { return QSqlTableModel::data( index, role ); }

            default:
                { return QSqlTableModel::data( index, role ); }
            }
        }
    }

/*
    if(role == Qt::DisplayRole)
    {
        if(index.row() < ptrCalendars->count())
        {
            if(index.column() == 1)
                //return ptrCalendars->at(index.row())->name();
        }
    }else if(role == Qt::EditRole && index.column() == 0)
    {
    }else if(role == Qt::UserRole)
    {
    }else if(role == Qt::CheckStateRole && index.column() == 0)
    {
        return QVariant(ptrCalendars->at(index.row())->isSelected());
    }*/

    return QVariant();
}

bool CalendarTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
   /* if(index.isValid() && index.column() == 0 && role == Qt::CheckStateRole)
    {
        Calendar *calendar = ptrCalendars->at(index.row());
        if(calendar->isSelected())
            calendar->setSelected(false);
        else
            calendar->setSelected(true);

        //ptrCalendars->replace(index.row(), calendar);
        emit dataChanged(index, index);
        return true;
    }*/
    return false;
}

/*!
  \fn CalendarTableModel::flags( const QModelIndex &index ) const
  Función llamada para conocer las propiedades de el item especifico.
  Se utiliza la columna 0 con chequeable para mostrar o no mostrar un calendario especifico
  @param index Item del cual se desea conocer los flags
 */
Qt::ItemFlags CalendarTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlTableModel::flags(index);
    if(index.column() == 0)
    {
        flags |= Qt::ItemIsUserCheckable;
    }
    return flags;
}
