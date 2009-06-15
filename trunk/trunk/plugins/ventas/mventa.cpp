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
#include "mventa.h"

#include <QDate>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>

MVenta::MVenta(QObject *parent, bool relaciones)
 : QSqlRelationalTableModel(parent)
{
 setTable( "ventas" );
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "Fecha de Venta" );
}


MVenta::~MVenta()
{
}




/*!
    \fn MVenta::agregarVenta( QDate fecha, int id_cliente, int id_lista_precio, int id_forma_pago, QString num_comprobante )
 */
bool MVenta::agregarVenta( QDate fecha, int id_cliente, int id_lista_precio, int id_forma_pago, QString num_comprobante )
{
  QSqlRecord regVenta = record();
 regVenta.remove( 0 );
 regVenta.setValue( "fecha"       , fecha );
 regVenta.setValue( "id_cliente", id_cliente );
 regVenta.setValue( "id_lista_precio", id_lista_precio );
 regVenta.setValue( "id_forma_pago", id_forma_pago );
 regVenta.setValue( "num_comprobante", num_comprobante );
 if( !insertRecord( -1, regVenta ) )
 {
  qDebug( "Error de insercion de registro de venta" );
  qDebug( QString( "Detalles: tipo: %1, errno: %2, descripcion: %3" ).arg( lastError().type() ).arg( lastError().number() ).arg( lastError().text() ).toLocal8Bit() );
  return false;
 }
 else
 {
  return true;
 }
}


/*!
    \fn MVenta::ultimoId()
 */
int MVenta::ultimoId()
{
  return this->query().lastInsertId().toInt();
}
