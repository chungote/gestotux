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

#include "MFactura.h"
#include <QDate>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlField>
#include "NumeroComprobante.h"

MFactura::MFactura(QObject *parent) :
QSqlRelationalTableModel(parent)
{
    inicializar();
    relacionar();
}

void MFactura::inicializar() {
 setTable("factura");
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "#Cliente" );
 setHeaderData( 2, Qt::Horizontal, "Fecha Emision" );
 setHeaderData( 3, Qt::Horizontal, "Forma de Pago" );
 setHeaderData( 4, Qt::Horizontal, "#Serie" );
 setHeaderData( 5, Qt::Horizontal, "#Numero" );
}

void MFactura::relacionar() {
    setRelation( 1, QSqlRelation( "clientes", "id", "razon_social" ) );
}

/*
CREATE TABLE IF NOT EXISTS `factura` (
  `id_factura` bigint(20) NOT NULL AUTO_INCREMENT,
  `id_cliente` bigint(20) REFERENCES `clientes`(`id`),
  `fecha` datetime NOT NULL,
  `id_forma_pago` int(1) NOT NULL,
  `serie` bigint(20) NOT NULL,
  `numero` bigint(20) NOT NULL,
  PRIMARY KEY (`id_factura`),
  UNIQUE KEY `factura-serie-numero` (`serie`,`numero`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
*/

/*!
    \fn MFactura::agregarVenta( QDate fecha, int id_cliente, MFactura::FormaPago id_forma_pago, QString num_comprobante )
    Agrega el registro para una factura y devuelve el id o -1 si hubo un error.
 */
int MFactura::agregarVenta( QDate fecha, int id_cliente, MFactura::FormaPago id_forma_pago )
{
 this->clear();
 this->inicializar();
 QSqlRecord regVenta = record();
 regVenta.remove( regVenta.indexOf( "id_factura" ) );
 regVenta.setValue( "fecha", fecha );
 regVenta.setValue( "id_cliente", id_cliente );
 regVenta.setValue( "id_forma_pago", id_forma_pago );
 NumeroComprobante num = this->proximoComprobante();
 regVenta.setValue( "serie", num.serie() );
 regVenta.setValue( "numero", num.numero() );
 //regVenta.setValue( "num_comprobante", num_comprobante );
 if( !insertRecord( -1, regVenta ) )
 {
  qDebug( "Error de insercion de registro de venta" );
  qDebug( QString( "Detalles: tipo: %1, errno: %2, descripcion: %3" ).arg( lastError().type() ).arg( lastError().number() ).arg( lastError().text() ).toLocal8Bit() );
  return -1;
 }
 else
 {
  this->relacionar();
  return this->query().lastInsertId().toInt();
 }
}


NumeroComprobante &MFactura::proximoComprobante() {
  QSqlQuery cola;
  if( cola.exec( QString( "SELECT MAX( serie ) FROM factura" ) ) ) {
      if( cola.next() ) {
          int serie = cola.record().value(0).toInt();
          if( cola.exec( QString( "SELECT MAX( numero ) FROM factura WHERE serie = %1" ).arg( serie ) ) ) {
              if( cola.next() ) {
                  int numero = cola.record().value(0).toInt();
                  NumeroComprobante *num = new NumeroComprobante( 0, serie, numero );
                  num->siguienteNumero();
                  return *num;
              } else {
                  qDebug( "Error de cola al hacer next al obtener el numero de factura maximo");
              }
          } else {
              qDebug( "Error de cola al hacer exec al obtener el numero de factura maximo" );
          }
      } else {
          qDebug( "Error de cola al hacer next al obtener el numero de serie de factura maximo -  Se inicio una nueva numeracion" );
      }
  } else {
      NumeroComprobante *num = new NumeroComprobante( 0, 0, 1 );
      num->siguienteNumero();
      qDebug( "Error de cola al hacer exec al obtener el numero de serie de factura maximo - Se inicio una nueva numeracion" );
      return *num;
  }
  NumeroComprobante *invalido = new NumeroComprobante( 0, -1, -1 );
  return *invalido;
}
