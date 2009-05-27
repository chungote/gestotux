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
#include "mrecargos.h"

#include <QSqlRecord>

MRecargos::MRecargos(QObject *parent)
 : QSqlRelationalTableModel(parent), _precio_base(0.0)
{
 setTable( "recargos" );
 setHeaderData( 0, Qt::Horizontal, tr( "#ID" ) );
 setHeaderData( 1, Qt::Horizontal, tr( "Serivicio" ) );
 setRelation  ( 1, QSqlRelation( "servicios", "id_servicio", "nombre" ) );
 setHeaderData( 2, Qt::Horizontal, tr( "Dias pasados" ) );
 setHeaderData( 3, Qt::Horizontal, tr( "Porcentaje" ) );
 setHeaderData( 4, Qt::Horizontal, tr( "Recargo" ) );
 setHeaderData( 5, Qt::Horizontal, tr( "Precio recargado" ) );
}


MRecargos::~MRecargos()
{
}


bool MRecargos::setData(const QModelIndex& index, const QVariant& value, int role)
{
    return QSqlRelationalTableModel::setData(index, value, role);
}

QVariant MRecargos::data(const QModelIndex& idx, int role) const
{
 switch( role )
 {
  case Qt::EditRole:
  {
   switch( idx.column() )
   {
    case 2:
    { return QSqlRelationalTableModel::data( idx, role ).toInt(); break; }
    case 3:
    case 4:
    { return QSqlRelationalTableModel::data( idx, role ).toDouble(); break; }
    case 5:
    {
     if( this->data( this->index( idx.row(), 3 ), Qt::EditRole ).toDouble() <= 0 )
     {
       return _precio_base + ( _precio_base * this->data( this->index( idx.row(), 3 ), Qt::EditRole ).toDouble() *.01 );
     }
     else if( this->data( this->index( idx.row(), 4 ), Qt::EditRole ).toDouble() <= 0 )
     {
       return _precio_base + this->data( this->index( idx.row(), 4 ), Qt::EditRole ).toDouble();
     }
     break;
    }
    default:
    { return QSqlRelationalTableModel::data( idx, role ); break; }
   }
   break;
  }
  default:
  { return QSqlRelationalTableModel::data(idx, role); break; }
 }
 return QSqlRelationalTableModel::data( idx, role );
}



/*!
    \fn MRecargos::agregarTemporal()
 */
void MRecargos::agregarTemporal()
{
 QSqlRecord registro = this->record();
 registro.remove( 0 );
 registro.setValue( "id_servicio", -2 );
 registro.setGenerated( 2, true );
 registro.setGenerated( 3, true );
 registro.setGenerated( 4, true );
 this->insertRecord( -1, registro );
}


/*!
    \fn MRecargos::ponerEnTemporal()
 */
void MRecargos::ponerEnTemporal()
{
  if( this->filter().isEmpty() )
  {
   this->setFilter( "id_servicio = -2" );
  }
}


/*!
    \fn MRecargos::setearPrecioBase( double precio )
 */
void MRecargos::setearPrecioBase( double precio )
{
 _precio_base = precio;
}


/*!
    \fn MRecargos::columnCount()
 */
int MRecargos::columnCount()
{
 return QSqlRelationalTableModel::columnCount() + 2;
}

