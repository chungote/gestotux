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
#include "mclientes.h"

MClientes::MClientes( QObject *parent )
 : QSqlRelationalTableModel( parent )
{
 setTable( "clientes" );
/*
-- Describe CLIENTES
CREATE TABLE IF NOT EXISTS `clientes` (
    `id` bigint(10) NOT NULL auto_increment,
    `razon_social` tinytext NOT NULL,
    `nombre` tinytext,
    `apellido` tinytext,
    `calle` tinytext,
    `numero` int(2) default NULL,
    `piso` int(2) default NULL,
    `depto` tinytext,
    `ciudad` tinytext,
    `codigo_postal` tinytext,
    `provincia` tinytext,
    `pais` tinytext,
    `tel_fijo` tinytext,
    `tel_celular` tinytext,
    `fax` tinytext,
    `email` tinytext,
    `comprobante_email` tinyint(1) default '1',
    `ctacte` tinyint(1) default NULL,
    `CUIT/CUIL` tinytext default null,
    `id_estado_fiscal` INT NULL
);
*/
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "Razon Social" );
 setHeaderData( 2, Qt::Horizontal, "Nombre" );
 setHeaderData( 3, Qt::Horizontal, "Apellido" );
 setHeaderData( 4, Qt::Horizontal, "Calle" );
 setHeaderData( 5, Qt::Horizontal, "Numero" );
 setHeaderData( 6, Qt::Horizontal, "Piso" );
 setHeaderData( 7, Qt::Horizontal, "Depto" );
 setHeaderData( 8, Qt::Horizontal, "Ciudad" );
 setHeaderData( 9, Qt::Horizontal, "Codigo Postal" );
 setHeaderData( 10, Qt::Horizontal, "Provincia" );
 setHeaderData( 11, Qt::Horizontal, "Pais" );
 setHeaderData( 12, Qt::Horizontal, "Telefono" );
 setHeaderData( 13, Qt::Horizontal, "Celular" );
 setHeaderData( 14, Qt::Horizontal, "Fax" );
 setHeaderData( 15, Qt::Horizontal, "Em@il" );
 setHeaderData( 16, Qt::Horizontal, "EnviarComprobantexEmail" );
 setHeaderData( 17, Qt::Horizontal, QString::fromUtf8("¿CtaCte?" ) );
 setHeaderData( 18, Qt::Horizontal, "CUIT/CUIL" );
 setHeaderData( 19, Qt::Horizontal, "Estado Fiscal" );
}

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
QString MClientes::direccionEntera(int id_cliente) {
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT calle, numero, piso, depto, ciudad, codigo_postal, provincia FROM clientes WHERE id = %1 ").arg( id_cliente ) ) ) {
        if( cola.next() ) {
            QString ret;
            if( !cola.record().value(0).isNull() ) {
                ret.append( cola.record().value(0).toString() );
            }
            if( !cola.record().value(1).isNull() ) {
                ret.append( " " + cola.record().value(1).toString() );
            }
            if( !cola.record().value(2).isNull()) {
                ret.append( " P " + cola.record().value(2).toString() );
            }
            if( !cola.record().value(3).isNull()) {
                ret.append( " dept " + cola.record().value(3).toString() );
            }
            if( !cola.record().value(4).isNull()) {
                ret.append( " - " + cola.record().value(4).toString() );
            }
            /*if( !cola.record().value(5).isNull()) {
                ret.append( " - CP " + cola.record().value(5).toString() );
            }
            if( !cola.record().value(6).isNull()) {
                ret.append( " - " + cola.record().value(6).toString() );
            }*/
            return ret;
        } else {
            qDebug( "Error haciendo next en la cola para obtener la direcicon de un cliente");
            qDebug( cola.lastError().text().toLocal8Bit() );
            return "Desconocido";
        }
    } else {
        qDebug( "Error haciendo exec en la cola para obtener la direcci´on de un cliente");
        qDebug( cola.lastError().text().toLocal8Bit() );
        return "Desconocido";
    }
}

Qt::ItemFlags MClientes::flags( const QModelIndex &index ) const
{
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

/*!
 * \fn MClientes:tieneDatosRelacionados( const int id_cliente )
 * Verifica si existe alguna asociacion en alguna tabla que corresponda con el cliente pasado como paraemtro
 * \param ID de cliente
 * \return Verdadero si hay alguna asociación
 */
bool MClientes::tieneDatosRelacionados( const int id_cliente )
{
 return true;
}
