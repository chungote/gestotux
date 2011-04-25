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
  `forma_pago` int(11) NOT NULL,
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
    setHeaderData( 5, Qt::Horizontal, "Forma Pago" );
    setHeaderData( 6, Qt::Horizontal, "Cancelado" );
    setHeaderData( 7, Qt::Horizontal, "Pagado" ); // Campo utilizado en hicomp
    setHeaderData( 8, Qt::Horizontal, "#Serie" );
    setHeaderData( 9, Qt::Horizontal, "#Numero" );
    setHeaderData( 10, Qt::Horizontal, "ID mov caja" );
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
     case 5:
     {
       switch( QSqlRelationalTableModel::data( item, role ).toInt() )
       {
        case Efectivo:
        { return "Efectivo"; break; }
        case Otro:
        { return "Otro"; break; }
       }
       break;
     }
     case 6: // Cancelado ( anulado ) y pagado
     case 7:
     //{ return QSqlRelationalTableModel::data( item, role ).toBool(); break; }
     {
             if( QSqlRelationalTableModel::data( item, role ).toBool() ) {
                return "Si";
             } else {
                 return "No";
             }
             break;
     }
     case 8:
     case 9:
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
    case 6:
    case 7:
    case 8:
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
  @param fecha Fecha de emisi�n del recibo
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
    // Elimino la asociaci�n si existe
    int ret = -1;
    this->clear();
    this->inicializar();
    QSqlRecord rec = this->record();
    // Cliente
    rec.setValue( "id_cliente", id_cliente );
    rec.setValue( "fecha_pago", fecha );
    rec.setValue( "texto", contenido );
    rec.setValue( "precio", total );
    rec.setValue( "pagado", pagado ); ///@todo Ver si esto andar�a bien con el formulario de pago retrasado
    if( efectivo && pagado )  {
        rec.setValue( "forma_pago", MPagos::Efectivo );
        rec.setValue( "id_caja", id_caja );
    } else {
        if( pagado ) {
            rec.setValue( "forma_pago", MPagos::Otro );
            rec.setNull( "id_caja" );
        } else {
            rec.setValue( "forma_pago", MPagos::SinPagar );
            rec.setNull( "id_caja" );
        }
    }
    QPair<int,int> proximo = this->proximoSerieNumeroRecibo();
    // Ver por el tema de numero de caja
    if( proximo.first == -1 ) { qDebug( "Error de numeracion!" );  return -1; }
    rec.setValue( "serie", proximo.first );
    rec.setValue( "numero",proximo.second );
    rec.setValue( "cancelado", false );
    /*for( int i=0; i<rec.count(); ++i ) {
        qDebug( QString( "Campo %1 es %2: %3 " ).arg( i ).arg( rec.fieldName(i) ).arg( rec.value(i).toString() ).toLocal8Bit() );
    }*/
    if( this->insertRecord( -1, rec ) ) {
        this->submitAll();
        int id_recibo = query().lastInsertId().toInt();
        qDebug( QString( "ultimo id query=%1" ).arg( id_recibo ).toLocal8Bit() );
        qDebug( query().lastQuery().toLocal8Bit() );
        if( id_recibo > 0 ) {
            ret = id_recibo;
        } else {
            // �no se lleno el campo ?
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
 * Devuelve un par de numeros indicando la serie y numero de recibo que se deber�a guardar al agregar un recibo.
 * \return NumeroRecibo indicando <serie, numero> o <-1,-1> si hubo un error
 */
MPagos::NumeroRecibo MPagos::proximoSerieNumeroRecibo()
{
 QSqlQuery cola;
 if( cola.exec( "SELECT serie, numero FROM recibos ORDER BY serie DESC, numero DESC LIMIT 1" ) )
 {
     if( cola.next() )
     {
         int serie = cola.record().value(0).toInt();
         qDebug( QString( "Numero serie actual: %1 ").arg( serie ).toLocal8Bit() );
         int numero = cola.record().value(1).toInt();
         qDebug( QString( "Numero actual: %1 ").arg( numero ).toLocal8Bit() );
         if( numero == 999999 ) {
             if( serie == 999999) {
                 qCritical( "Numero de serie terminado! :S?" );
                 abort();
             }
             serie++;
             numero = 0;
         } else { numero ++; }
         qDebug( QString( "Devuelto: %1-%2").arg( serie ).arg( numero ).toLocal8Bit() );
         return MPagos::NumeroRecibo( serie, numero );
     } else {
         return MPagos::NumeroRecibo( -1, -1 );
     }
 } else {
     return MPagos::NumeroRecibo( -1, -1 );
 }
}

#include "../CtaCte/mitemcuentacorriente.h"
#include "../CtaCte/mcuentacorriente.h"
#include "../caja/mcajas.h"
#include "../caja/mmovimientoscaja.h"
/*!
 * \fn MPagos::setearComoPagado( const in id_recibo, const bool efectivo )
 * Setea como pago el recibo que se pasa como id. Si ya esta como pagado, no hace nada y devuelve true.
 * \param id_recibo ID del recibo
 * \param efectivo Define si la forma de pago es MPagos::Efectivo ( si el parametro es true ) o MPagos::Otro ( si es false )
 * \return Verdadero si pudo ser puesto como pagado o si ya estaba como pagado.
 */
bool MPagos::setearComoPagado( const int id_recibo, const bool efectivo )
{
 QSqlDatabase::database().transaction();
 if( this->query().exec( QString( "UPDATE recibos SET pagado = 1 WHERE id_recibo = %1" ).arg( id_recibo ) ) ) {
    if( this->query().exec( QString( "SELECT id_cliente, precio, serie, numero FROM recibos WHERE id_recibo = %1" ).arg( id_recibo ) ) )
    {
        int id_cliente = this->query().value(0).toInt();
        double precio = this->query().value(1).toDouble();
        QString t = QString( "%1-%2" ).arg( this->query().value(2).toInt() ).arg( this->query().value(3).toInt() );
        // Coloco el recibo en la cuenta corriente del cliente si no es el consumidor final
        if( id_cliente > 0 ) {
            MItemCuentaCorriente *m = new MItemCuentaCorriente();
            if( m->agregarOperacion( MCuentaCorriente::obtenerNumeroCuentaCorriente( id_cliente ), // Numero de cuenta del cliente
                                     t, // Numero de recibo ( real )
                                     id_recibo, // Id de referencia
                                     MItemCuentaCorriente::Recibo,
                                     QDate::currentDate(),
                                     QString( "Pago mediante recibo %1" ).arg( t ),
                                     precio ) )
            {
                qDebug( "Operaci�n de cuenta corriente guardada correctamente" );
            } else {
                qDebug( "Error al intentar agregar la operaci�n de cuenta corriente cuando poniendo como pagado un recibo." );
                QSqlDatabase::database().rollback();
                return false;
            }
            delete m;
        } // El cliente es consumidor final sino
        // Si el recibo se pago en efectivo, hago su ingreso en caja
        if( efectivo )
        {
            MMovimientosCaja *m = new MMovimientosCaja();
            if( m->agregarMovimiento( MCajas::cajaPredeterminada(),
                                      QString( "Pago del recibo %1" ).arg( t ),
                                      QString(),
                                      precio ) )
            {
                qDebug( "Operaci�n de movimiento de caja agregado correctamente" );
            } else {
                qDebug( "Error al intentar registrar el movimiento de caja al pagar un recibo ya emitido." );
                QSqlDatabase::database().rollback();
                return false;
            }
            delete m;
        } else {
            // El metodo de pago es otro ( desconocido )
            if( this->query().exec( QString( "UPDATE recibos SET forma_pago = %1 WHERE id_recibo = %2" ).arg( MPagos::Otro ).arg( id_recibo ) ) ) {
                // Todos los pasos guardados correctamente
            } else {
                qDebug( "Error al intentar poner la forma de pago en otro al poner como pagado un recibo ya emitido" )   ;
                QSqlDatabase::database().rollback();
                return false;
            }
        }
    }
 } else {
    qDebug( "Error al intentar colocar el recibo como pagado" );
    QSqlDatabase::database().rollback();
    return false;
 }
 if( !QSqlDatabase::database().commit() ) {
     qCritical( "Error al hacer commit de la base de datos!" );
     abort();
 } else {
     return true;
 }
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
