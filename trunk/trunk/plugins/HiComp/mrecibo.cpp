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
#include "mrecibo.h"

#include <QLocale>
#include <QDate>

MRecibo::MRecibo( QObject *parent )
 : QSqlRelationalTableModel(parent)
{
 setTable( "recibos" );
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "Cliente" );
 setHeaderData( 2, Qt::Horizontal, "Mes" );
 setHeaderData( 3, Qt::Horizontal, "Texto" );
 setHeaderData( 4, Qt::Horizontal, "Precio" );
 setHeaderData( 5, Qt::Horizontal, "Fecha Pago" );
 setHeaderData( 6, Qt::Horizontal, "Contado" );
 setHeaderData( 7, Qt::Horizontal, "Cuenta Corriente" );
 setRelation( 1, QSqlRelation( "clientes", "id", "nombre" ) );
}


MRecibo::~MRecibo()
{
}


QVariant MRecibo::data(const QModelIndex& idx, int role) const
{
 if( !idx.isValid() )
 {
  return QVariant();
 }
 else
 {
  switch( role )
  {
   case Qt::DisplayRole:
   {
    switch( idx.column() )
    {
     case 0:
     {
      // ID
      return QSqlRelationalTableModel::data( idx, role ).toInt();
      break;
     }
     case 1:
     {
      //cliente
      return QSqlRelationalTableModel::data( idx, role ).toString();
      break;
     }
     case 2:
     {
      // mes
      QLocale locale;
      return locale.monthName( QSqlRelationalTableModel::data( idx, role ).toInt()+1 );
      break;
     }
     case 3:
     { // texto del recibo
      return QSqlRelationalTableModel::data( idx, role ).toString();
      break;
     }
     case 4:
     { // Precio
      return QString().number( QSqlRelationalTableModel::data( idx, role ).toDouble() ).prepend( "$" );
      break;
     }
     case 5:
     { // Fecha de Pago
      return QSqlRelationalTableModel::data( idx, role ).toDate();
      break;
     }
     case 6:
     case 7:
     {
      // Cuenta Corriente y contado
      return QSqlRelationalTableModel::data( idx, role ).toBool();
      break;
     }
     default:
     {
      return QSqlRelationalTableModel::data( idx, role );
      break;
     }
    }// fin switch columna
    break;
   }


   case Qt::EditRole:
   {
    switch( idx.column() )
    {
      case 0:
      {
        // El ID no debe ser editable
        return QVariant();
        break;
      }
      case 5:
      {
        // Fecha
        return QSqlRelationalTableModel::data( idx, role ).toDate();
        break;
      }
      case 4:
      {
        // Precio
        return QSqlRelationalTableModel::data( idx, role ).toDouble();
        break;
      }
      case 2:
      {
        // numero de mes
        return QSqlRelationalTableModel::data( idx, role ).toInt();
        break;
      }
      case 6:
      case 7:
      {
       return QSqlRelationalTableModel::data( idx, role ).toBool();
       break;
      }
      default:
      {
        // Cualquier otro va con string
        return QSqlRelationalTableModel::data( idx, role );
        break;
      }
    } // fin switch columna
    break;
   }// fin edit role
   case Qt::TextAlignmentRole:
   {
    switch( idx.column() )
    {
     //Fecha
     case 5:
     //mes
     case 2:
     {
      return int( Qt::AlignVCenter | Qt::AlignHCenter );
      break;
     }
     case 4: // Precio
     {
      return int( Qt::AlignRight | Qt::AlignVCenter );
      break;
     }
     default:
     {
      return QSqlRelationalTableModel::data( idx,role );
      break;
     }
    }// fin switch col
    break;
   }// fin switch rol
   default:
   {
    return QSqlRelationalTableModel::data(idx, role);
    break;
   }
  }
 }
}

Qt::ItemFlags MRecibo::flags(const QModelIndex& index) const
{
    return QSqlRelationalTableModel::flags(index);
}

bool MRecibo::setData(const QModelIndex& index, const QVariant& value, int role )
{
 if( !index.isValid() )
 {
  return false;
 }
 switch(  index.column() )
 {
  case 0:
  {
   return false;
   break;
  }
  case 5:
  {
   return QSqlRelationalTableModel::setData( index, value.toDate() );
   break;
  }
  case 6:
  {
   if( value.toInt() == 1 )
   {
     if( QSqlRelationalTableModel::setData( index, true ) &&
     QSqlRelationalTableModel::setData( this->index( index.row(), 7 ), false ) )
     {
       return true;
     }
     else
     {
       return false;
     }
   }
   else
   {
     return QSqlRelationalTableModel::setData( index, false );
   }
  }
  case 7:
  {
   if( value.toInt() == 1 )
   {
    if( QSqlRelationalTableModel::setData( index, true ) &&
    QSqlRelationalTableModel::setData( this->index( index.row(), 6 ), false ) )
    {
      return true;
    }
    else
    {
     return false;
    }
   }
   else
   {
    return QSqlRelationalTableModel::setData( index, true );
   }
  }
  default:
  {
   return QSqlRelationalTableModel::setData( index, value, role );
   break;
  }
 }
}

