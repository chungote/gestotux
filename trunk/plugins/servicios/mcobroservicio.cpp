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
#include "mcobroservicio.h"

#include <QSqlQuery>
#include <QSqlError>

MCobroServicio::MCobroServicio(QObject *parent)
 : QSqlRelationalTableModel(parent)
{
 setTable( "cobro_servicio" );
 setHeaderData( 0, Qt::Horizontal, tr( "#ID" ) );
 setHeaderData( 1, Qt::Horizontal, tr( "#Cliente-Servicio" ) );
 setHeaderData( 2, Qt::Horizontal, tr( "Fecha" ) );
 setHeaderData( 3, Qt::Horizontal, tr( "#Factura" ) );
 setHeaderData( 4, Qt::Horizontal, tr( "#Recibo" ) );
 setHeaderData( 5, Qt::Horizontal, tr( "#Periodo" ) );
 setHeaderData( 6, Qt::Horizontal, tr( "#Año" ) );
}


MCobroServicio::~MCobroServicio()
{
}


bool MCobroServicio::setData(const QModelIndex& item, const QVariant& value, int role)
{
    return QSqlRelationalTableModel::setData(item, value, role);
}

QVariant MCobroServicio::data(const QModelIndex& item, int role) const
{
    return QSqlRelationalTableModel::data(item, role);
}

/*!
 * \fn MCobroServicio::agregarCobro( const int id_servicio, const int id_cliente, const int id_factura, const int periodo, const int ano )
 * Agrega el registro de que se realizo el cobro de un servicio identificado mediante la factura en un periodo del servicio.
 * @param id_servicio Identificador del servicio a facturar
 * @param id_cliente Cliente al cual se le esta cobrando el servicio
 * @param id_factura Numero de comprobante que da la deuda al cliente
 * @param periodo Numero de periodo dentro del año
 * @param ano Año del cobro
 * @return Verdadero si se pudo agregar
 */
bool MCobroServicio::agregarCobro( const int id_servicio, const int id_cliente, const int id_factura, const int periodo, const int ano )
{
 QSqlQuery cola;
 cola.prepare( "INSERT INTO cobro_servicio VALUES( :id_servicio, :id_cliente, :factura, :periodo, :ano )" );
 cola.bindValue( ":id_servicio", id_servicio );
 cola.bindValue( ":id_cliente", id_cliente );
 cola.bindValue( ":factura", id_factura );
 cola.bindValue( ":periodo", periodo );
 cola.bindValue( ":ano", ano );
 if( cola.exec() ) {
     return true;
 } else {
     qDebug( "Servicios::MCobroServicio::agregarCobro - Error al intentar agregar el cobro de un servicio ( exec )" );
     qDebug( QString( cola.lastError().text() ).toLocal8Bit() );
     return false;
 }

}
/*!

  @todo PASAR TODOS LOS INDICES MYSQL A BIGINT SIN NUMERO DE DIGITOS DETERMINADOS

*/

/*
CREATE TABLE `gestotux`.`cobro_servicio` (
`id_cobro_servicio` BIGINT NOT NULL AUTO_INCREMENT,
`id_servicio` BIGINT(1) NOT NULL,
`id_cliente` BIGINT(1) NOT NULL ,
`fecha` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ,
`factura` BIGINT NOT NULL ,
`recibo` BIGINT NOT NULL ,
`periodo` INT NOT NULL ,
`ano` YEAR NOT NULL,
 INDEX ( id_servicio, id_cliente ),
 FOREIGN KEY ( id_servicio, id_cliente )
 REFERENCES `servicios_clientes`( id_servicio, id_cliente ),
 PRIMARY KEY ( id_cobro_servicio ),
 FOREIGN KEY ( factura ) REFERENCES ventas( id ),
 FOREIGN KEY ( recibo ) REFERENCES recibos( id_recibo )
) ENGINE = InnoDB;
*/