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
  `serie` int NOT NULL,
  `numero` int NOT NULL,
  `id_caja` bigint(20) REFERENCES movimiento_caja(id_movimiento),
  PRIMARY KEY (`id_recibo`),
  UNIQUE KEY `numero_recibo` (`serie`,`numero`)
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
    setHeaderData( 7, Qt::Horizontal, "#Serie" );
    setHeaderData( 8, Qt::Horizontal, "#Numero" );
    setHeaderData( 9, Qt::Horizontal, "ID mov caja" );
}

void MPagos::relacionar()
{
    setRelation( 1, QSqlRelation( "clientes", "id", "razon_social" ) );
    //setRelation( 9, QSqlRelation( "movimientos_caja", "id_movimiento", "descripcion" ) );
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
     case 7:
     case 8:
     { return QSqlRelationalTableModel::data( item, role ).toInt(); }
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
    case 6:
    case 7:
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
    QPair<int,int> proximo = this->proximoSerieNumeroRecibo();
    rec.setValue( "serie", proximo.first );
    rec.setValue( "numero",proximo.second );
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
 * \fn MPagos::numeroSerieActual()
 * Devuelve el numero de serie actual para el recibo
 * \return Numero de serie o -1 si hay error
 */
int MPagos::numeroSerieActual()
{
 QSqlQuery cola;
 if( cola.exec( QString( "SELECT MAX(serie) FROM recibos") ) ) {
    if( cola.next() ) {
        return cola.record().value(0).toInt();
    } else {
        return -1;
    }
 } else {
    return -1;
 }
}

/*!
 * \fn MPagos::numeroReciboActual()
 * Devuelve el numero de recibo de ultima emision
 * \return Numero de recibo actual o -1 si hay error
 */
int MPagos::numeroReciboActual( const int serie )
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT MAX(numero) FROM recibos WHERE serie = %1" ).arg( serie ) ) ) {
        if( cola.next() ) {
           return cola.record().value(0).toInt();
        } else {
            return -1;
        }
    } else {
        return -1;
    }
}

#include <QMessageBox>
/*!
 * \fn MPagos::proximoSerieNumeroRecibo()
 * Devuelve un par de numeros indicando la serie y numero de recibo que se debería guardar al agregar un recibo.
 * \return NumeroRecibo indicando <serie, numero>
 */
MPagos::NumeroRecibo MPagos::proximoSerieNumeroRecibo()
{
    QMessageBox::critical(0, "error", "No implementado" );
    abort();
    return QPair<int,int>();
}

/*!
 * \fn MPagos::setearComoPagado( const in id_recibo )
 * Setea como pago el recibo que se pasa como id. Si ya esta como pagado, no hace nada y devuelve true.
 * \param id_recibo ID del recibo
 * \return Verdadero si pudo ser puesto como pagado y descontado de la ctacte o si ya estaba como pagado.
 */
bool MPagos::setearComoPagado( const int /*id_recibo*/ )
{
 QMessageBox::critical(0, "error", "No implementado" );
 return false;
}

#include <QSqlQuery>
#include <QSqlRecord>
/*!
 * \fn MPagos::buscarMenorSerieNumeroPagado()
 * Devuelve el par serie-numero del menor recibo pagado de la base de datos
 * \return NumeroRecibo indicando <serie,numero> o <0,0> si se produjo un error
 */
MPagos::NumeroRecibo MPagos::buscarMenorSerieNumeroPagado()
{
 QSqlQuery cola;
 if( cola.exec( QString( "SELECT serie, numero FROM recibos WHERE pagado = 0 ORDER BY serie ASC, numero ASC LIMIT 1" ) ) )
 {
     if( cola.next() ) {
         return QPair<int,int>( cola.record().value( 0 ).toInt(), cola.record().value( 1 ).toInt() );
     } else {
         qDebug( "Error en cola.next al obtener el minimo de serie y numero de un recibo" );
         return QPair<int,int>( 0, 0 );
     }
 } else {
     qDebug( "Error en cola.exec al obtener el minimo de serie y numero de un recibo" );
     return QPair<int,int>( 0, 0 );
 }
}

/*!
 * \fn MPagos::buscarSiPagado( const int serie, const int numero )
 * Busca si un recibo con los datos del parametro esta pagado o no
 * \param serie Serie del recibo buscado
 * \param numero Numero del recibo buscado
 * \returns pagado o no
 */
bool MPagos::buscarSiPagado(const int serie, const int numero)
{
 if( this->query().exec( QString( "SELECT pagado FROM recibos WHERE serie = %1 AND numero = %2" ).arg( serie ).arg( numero ) ) ) {
     if( this->query().next() ) {
         if( this->query().record().value(1).toBool() ) {
             return true;
         } else {
             return false;
         }
     } else {
         qDebug( "Error al hacer next en cola de si pagado serie-numero" );
         return false;
     }
 } else {
     qDebug( "error al hacer exec de cola de si pagado serie-numero" );
     return false;
 }
}

/*!
 * \fn MPagos::buscarSiPagado( const NumeroRecibo num )
 * Sobrecarga
 * \param Numero y serie del recibo buscado
 * \returns pagado o no
 */
bool MPagos::buscarSiPagado( const MPagos::NumeroRecibo num )
{ return buscarSiPagado( num.first, num.second ); }

/*!
 * \fn MPagos::buscarIdPorSerieNumero( const int serie, const int numero )
 * Devuelve el identificador de base de datos para una serie y numero de recibo
 * \param Numero y serie del recibo buscado
 * \returns ID en la base de datos
 */
int MPagos::buscarIdPorSerieNumero( const int serie, const int numero )
{
 if( this->query().exec( QString( "SELECT id_recibo FROM recibos WHERE serie = %1 AND numero = %2" ).arg( serie ).arg( numero ) ) )
 {
     if( this->query().next() )
     {
         return this->query().record().value(0).toInt();
     } else {
         qDebug( "Error al hacer next en la cola de buscar id recibo x num y serie" );
         return -1;
     }
 } else {
     qDebug( "Error al hacer exec en la cola de buscar id recibo x num y serie" );
     return -2;
 }
}

/*!
 * \fn MPagos::buscarIdPorSerieNumero( const NumeroRecibo num )
 * Sobrecarga para tomar el parametro NumeroRecibo
 * \param Numero y serie del recibo buscado
 * \returns ID en la base de datos
 */
int MPagos::buscarIdPorSerieNumero( const MPagos::NumeroRecibo num )
{ return buscarIdPorSerieNumero( num.first, num.second ); }

double MPagos::buscarImporte( MPagos::NumeroRecibo num )
{
  if( this->query().exec( QString( "SELECT precio FROM recibos WHERE serie = %1 AND numero = %2" ).arg( num.first ).arg( num.second ) ) ) {
    if( this->query().next() ) {
       if( this->query().record().value(1).toBool() ) {
         return true;
       } else {
         return false;
       }
    } else {
       qDebug( "Error al hacer next en cola de importe de recibo" );
       return false;
    }
  } else {
    qDebug( "error al hacer exec de cola de importe de recibo" );
    return false;
  }
}
