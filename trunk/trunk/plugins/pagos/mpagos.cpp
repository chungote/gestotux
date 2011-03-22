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
#include "mpagos.h"
#include <QDate>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
#include "eregistroplugins.h"
#include "../caja/mmovimientoscaja.h"
#include "../caja/mcajas.h"

/*
DROP TABLE `recibos`;
CREATE TABLE IF NOT EXISTS `recibos` (
  `id_recibo` bigint(20) NOT NULL AUTO_INCREMENT,
  `id_cliente` bigint(20) REFERENCES clientes(id),
  `fecha_pago` datetime NOT NULL,
  `texto` tinyblob,
  `precio` double(15,4) DEFAULT NULL,
  `cancelado` tinyint(4) NOT NULL DEFAULT '0',
  `pagado` tinyint(4) NOT NULL DEFAULT '1',
  `id_caja` bigint(20) REFERENCES movimiento_caja(id_movimiento),
  PRIMARY KEY (`id_recibo`)
) ENGINE=InnoDB;
*/

MPagos::MPagos(QObject *parent, bool relaciones )
 : QSqlRelationalTableModel(parent)
{
 inicializar();
 if( relaciones ) { relacionar(); }
}

void MPagos::inicializar()
{
    setTable( "recibos" );
    setHeaderData( 0, Qt::Horizontal, "#ID" );
    setHeaderData( 1, Qt::Horizontal, "Cliente" );
    setHeaderData( 2, Qt::Horizontal, "Fecha Pago" );
    setHeaderData( 3, Qt::Horizontal, "Texto" );
    setHeaderData( 4, Qt::Horizontal, "Cantidad" );
    setHeaderData( 5, Qt::Horizontal, "Cancelado" );
    setHeaderData( 6, Qt::Horizontal, "Pagado" ); // Campo utilizado en hicomp
    setHeaderData( 7, Qt::Horizontal, "ID mov caja" );
}

void MPagos::relacionar()
{
    setRelation( 1, QSqlRelation( "clientes", "id", "razon_social" ) );
    //setRelation( 7, QSqlRelation( "movimientos_caja", "id_movimiento", "descripcion" ) );
}

MPagos::~MPagos()
{
}


QVariant MPagos::data(const QModelIndex& item, int role) const
{
 switch( role )
 {
  case Qt::DisplayRole:
  {
   switch( item.column() )
   {
     case 0: // ID
     { return QString( "#%L1" ).arg( QSqlRelationalTableModel::data( item, role ).toInt() ); break;}
     case 1: // Cliente
     { return QSqlRelationalTableModel::data( item, role ).toString(); break; }
     case 2: // fecha de pago
     { return QSqlRelationalTableModel::data( item, role ).toDate(); break; }
     case 3: // Texto
     { return QSqlRelationalTableModel::data( item, role ).toString(); break; }
     case 4: // Cantidad pagada
     { return QString( "$ %L1" ).arg( QSqlRelationalTableModel::data( item, role ).toDouble() ); break; }
     case 5: // Cancelado ( anulado ) y pagado
     case 6:
     //{ return QSqlRelationalTableModel::data( item, role ).toBool(); break; }
     {
             if( QSqlRelationalTableModel::data( item, role ).toBool() ) {
                return "Si";
             } else {
                 return "No";
             }
             break;
     }
     default:
     { return QSqlRelationalTableModel::data( item, role ); break; }
   }
   break;
  }
  case Qt::TextAlignmentRole:
  {
   switch( item.column() )
   {
    case 2:
    case 3:
    case 4:
    case 5:
    { return int( Qt::AlignCenter | Qt::AlignVCenter ); break; }
    default:
    { return QSqlRelationalTableModel::data( item, role ); break; }
   }
   break;
  }
  default:
  {
   return QSqlRelationalTableModel::data( item, role );
   break;
  }
 }
 return QSqlRelationalTableModel::data(item, role);
}

/*!
   \fn MPagos::buscarUltimoNumeroRecibo() const
   Busca el maximo ID de la tabla de recibos
   \return ID del ultimo recibo o -1 si ocurrio un error
 */
int MPagos::buscarUltimoNumeroRecibo() const
{
  // Busco el maximo de los recibos
  QSqlQuery cola( QString( "SELECT MAX(id_recibo) FROM %1" ).arg( this->tableName() ) );
  if( cola.exec() ) {
      if( cola.next() ) {
          return cola.record().value(0).toInt();
      } else {
          qDebug( "MPagos::buscarUltimoNumeroRecibo::Error al hacer next en la cola" );
          qDebug( this->lastError().text().toLocal8Bit() );
          return -1;
      }
  } else {
      qDebug( "MPagos::buscarUltimoNumeroRecibo::Error al hacer exec de la cola" );
      qDebug( this->lastError().text().toLocal8Bit() );
      return -1;
  }
}

/*!
   \fn MPagos::buscarUltimoNumeroRecibo() const
   Busca la fecha mas tardia de cualquier recibo
   \return Objeto QDate valido con la fecha, o invalido si no se pudo ejecutar la consulta
 */
QDate MPagos::buscarFechaUltimoRecibo() const
{
  // Busco la fecha maxima de los recibos
  QSqlQuery cola( QString( "SELECT MAX(fecha_pago) FROM %1" ).arg( this->tableName() ) );
  if( cola.exec() ) {
      if( cola.next() ) {
          return cola.record().value(0).toDate();
      } else {
          qDebug( "MPagos::buscarFechaUltimoRecibo::Error al hacer next en la cola" );
          qDebug( this->lastError().text().toLocal8Bit() );
          return QDate();
      }
  } else {
      qDebug( "MPagos::buscarFechaUltimoRecibo::Error al hacer exec de la cola" );
      qDebug( this->lastError().text().toLocal8Bit() );
      return QDate();
  }
}

/*!
  \fn MPagos::agregarRecibo( const int id_cliente, const QDate fecha, const QString contenido, const double total, const bool efectivo, const bool pagado )
  Agrega un nuevo recibo con los datos pasados como parametro y devuelve el numero de recibo insertado o -1 si ocurrio un error
  @param id_cliente ID de la tabla cliente del cliente en cuestion
  @param fecha Fecha de emisión del recibo
  @param contenido Texto o contenido html que ira en el recibo
  @param total Total pagado en este recibo
  @param pagado Coloca como pagado el recibo
  @param efectivo indica si el recibo fue pagado en efectivo
  @return Numero de recibo emitido o -1 en caso de cualquier error
*/
int MPagos::agregarRecibo( int id_cliente, QDate fecha, QString contenido, double total, bool efectivo, bool pagado )
{
    int id_caja = -1;
    if( efectivo && pagado ) {
        // Genero la entrada en la caja
        if( ERegistroPlugins::getInstancia()->existePlugin("caja") ) {
            int pid_caja = MCajas::cajaPredeterminada();
            MMovimientosCaja *mc = new MMovimientosCaja( this );
            if( mc->agregarMovimiento( pid_caja, "Pago en efectivo de recibo", QString(), total, 0.0 ) )
            {
                id_caja = mc->ultimoIdInsertado();
            } else {
                qDebug( "MPagos::agregarRecibo::MovimientoCaja:: error al agregar el movimiento" );
                return -1;
            }
        }
    }
    // Elimino la asociación si existe
    int ret = -1;
    this->clear();
    this->inicializar();
    QSqlRecord rec = this->record();
    // Cliente
    rec.setValue( "id_cliente", id_cliente );
    rec.setValue( "fecha_pago", fecha );
    rec.setValue( "texto", contenido );
    rec.setValue( "precio", total );
    rec.setValue( "pagado", pagado );
    if( efectivo == true ) {
       rec.setValue( "id_caja", id_caja );
    } else {
        rec.setNull( "id_caja" );
    }
    rec.setValue( "cancelado", false );
    for( int i=0; i<rec.count(); ++i ) {
        qDebug( QString( "Campo %1 es %2: %3 " ).arg( i ).arg( rec.fieldName(i) ).arg( rec.value(i).toString() ).toLocal8Bit() );
    }
    if( this->insertRecord( -1, rec ) ) {
        this->submitAll();
        int id_recibo = query().lastInsertId().toInt();
        qDebug( QString( "ultimo id query=%1" ).arg( id_recibo ).toLocal8Bit() );
        qDebug( query().lastQuery().toLocal8Bit() );
        if( id_recibo > 0 ) {
            ret = id_recibo;
        } else {
            // ¿no se lleno el campo ?
            qDebug( "MPagos::agregarRecibo::No se pudo llenar el id del recibo?" );
        }
    } else {
        // Error al insertar el registro
        qDebug( "MPagos::agregarRecibo:: Error al insertar el registro" );
        qDebug( this->lastError().text().toLocal8Bit() );
    }
    this->relacionar();
    return ret;
}

/*!
 * MPagos::numeroSerieActual()
 * Devuelve el numero de serie actual para el recibo
 * \return Numero de serie
 */
int MPagos::numeroSerieActual()
{
 QSqlQuery cola;
 if( cola.exec( QString( "SELECT MAX(serie) FROM recibos") ) ) {

 } else {

 }
 return "AAAAA";
}

/*!
 * MPagos::numeroReciboActual()
 * Devuelve el numero de recibo de ultima emision
 * \return Numero de recibo actual
 */
int MPagos::numeroReciboActual( const int serie )
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT MAX(numero) FROM recibos WHERE serie = %1" ).arg( serie ) ) ) {

    } else {

    }
    return "AAAAA";
}
