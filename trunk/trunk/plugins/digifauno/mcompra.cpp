/***************************************************************************
 *   Copyright (C) 2006 by Esteban Zeller & Daniel Sequeira		   *
 *   juiraze@yahoo.com.ar  - daniels@hotmail.com			   *
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
#include "mcompra.h"

#include <QSqlRecord>
#include <QSqlError>
#include <QDate>

MCompra::MCompra(QObject *parent, bool relaciones )
 : QSqlRelationalTableModel(parent)
{
 setTable( "compras" );
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "Proveedor" );
 setHeaderData( 2, Qt::Horizontal, "Fecha" );
 setHeaderData( 3, Qt::Horizontal, "Costo" );
 if( relaciones )
 {
 setRelation( 1, QSqlRelation( "proveedor", "id", "nombre" ) );
 }
}


MCompra::~MCompra()
{
}




/*!
    \fn MCompra::agregarCompra( QVariant fecha, QVariant proveedor, QVariant costo )
 */
bool MCompra::agregarCompra( QVariant fecha, QVariant proveedor, QVariant costo )
{
 QSqlRecord regCompra = record();
 regCompra.remove( 0 );
 regCompra.setValue( "fecha"       , fecha.toDate().toString( "yyyy-MM-dd" ) );
 regCompra.setValue( "id_proveedor", proveedor );
 regCompra.setValue( "costo"       , costo.toDouble() );
 if( !insertRecord( -1, regCompra ) )
 {
  qDebug( "Error de insercion de registro de compra" );
  qDebug( QString( "Detalles: tipo: %1, errno: %2, descripcion: %3" ).arg( lastError().type() ).arg( lastError().number() ).arg( lastError().text() ).toLocal8Bit() );
  return false;
 }
 else
 {
  return true;
 }
}
