/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   *
 *   juiraze@yahoo.com.ar   *
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
#include "mpresupuesto.h"
#include <QDate>
#include <QColor>

MPresupuesto::MPresupuesto(QObject *parent )
 : QSqlRelationalTableModel(parent)
{
    inicializar();
    relacionar();
}

void MPresupuesto::inicializar()
{
    setTable( "presupuestos" );
    // Descripciondes de las cabeceras
    setHeaderData( 0, Qt::Horizontal, "#ID" );
    setHeaderData( 1, Qt::Horizontal, "Cliente" );
    setHeaderData( 2, Qt::Horizontal, "Destinatario" );
    setHeaderData( 3, Qt::Horizontal, "Fecha" );
    setHeaderData( 4, Qt::Horizontal, "Total" );
    setHeaderData( 5, Qt::Horizontal, "Contenido" );
}

void MPresupuesto::relacionar()
{
  setRelation( 1, QSqlRelation( "clientes", "id", "razon_social" ) );
}

QVariant MPresupuesto::data(const QModelIndex& idx, int role) const
{
 switch( role )
 {
        case Qt::DisplayRole:
        {
                switch( idx.column() )
                {
                        case 1:
                        case 2:
                        {
                                return QSqlRelationalTableModel::data( idx, role ).toString();
                                break;
                        }
                        case 3:
                        {
                                return QSqlRelationalTableModel::data( idx, role ).toDate();
                                break;
                        }
                        case 4:
                        {
                                return QString( "$ %L1" ).arg( QSqlRelationalTableModel::data( idx, role ).toDouble() );
                                break;
                        }
                        default:
                        {
                                return QSqlRelationalTableModel::data( idx, role );
                                break;
                        }
                }
                break;
        }
        case Qt::EditRole:
        {
                switch( idx.column() )
                {
                        case 1:
                        {
                                return QSqlRelationalTableModel::data( idx, role );
                                break;
                        }
                        case 2:
                        {
                                return QSqlRelationalTableModel::data( idx, role ).toString();
                                break;
                        }
                        case 3:
                        {
                                return QSqlRelationalTableModel::data( idx, role ).toDate();
                                break;
                        }
                        case 4:
                        {
                                return QSqlRelationalTableModel::data( idx, role ).toDouble();
                                break;
                        }
                        default:
                        {
                                return QSqlRelationalTableModel::data( idx, role);
                                break;
                        }
                }
                break;
        }
        case Qt::TextAlignmentRole:
        {
                switch( idx.column() )
                {
                        case 1:
                        case 2:
                        {
                                return int( Qt::AlignLeft | Qt::AlignVCenter );
                                break;
                        }
                        case 3:
                        {
                                return int( Qt::AlignCenter | Qt::AlignVCenter );
                                break;
                        }
                        case 4:
                        {
                                return int( Qt::AlignRight | Qt::AlignVCenter );
                                break;
                        }
                        default:
                        {
                                return QSqlRelationalTableModel::data( idx, role );
                                break;
                        }
                }
                break;
        }
        case Qt::BackgroundRole:
        {
                switch( idx.column() )
                {
                        case 2:
                        {
                                if( QSqlRelationalTableModel::data( QSqlRelationalTableModel::index( idx.row(), 2 ), Qt::EditRole ).toString().isEmpty() )
                                { return QColor( Qt::gray ); }
                                else
                                { return QSqlRelationalTableModel::data( idx, role ); }
                                break;
                        }
                        default:
                        {
                                return QSqlRelationalTableModel::data( idx, role );
                                break;
                        }
                }
                break;
        }
        default:
        {
                return QSqlRelationalTableModel::data( idx, role );
                break;
        }
 }
}

bool MPresupuesto::setData(const QModelIndex& index, const QVariant& value, int role)
{
    return QSqlRelationalTableModel::setData(index, value, role);
}

