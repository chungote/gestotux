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

#include "mmovimientoscaja.h"

#include <QSqlRecord>
#include <QSqlError>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlQuery>

#include "mcajas.h"

MMovimientosCaja::MMovimientosCaja( QObject *parent, bool relaciones ) :
    QSqlRelationalTableModel(parent)
{
    setTable( "movimiento_caja" );
    setHeaderData( 0, Qt::Horizontal, "#Movimiento" );
    setHeaderData( 1, Qt::Horizontal, "#Caja" );
    setHeaderData( 2, Qt::Horizontal, "Fecha y Hora" );
    setHeaderData( 3, Qt::Horizontal, "Ingreso" );
    setHeaderData( 4, Qt::Horizontal, "Egreso" );
    setHeaderData( 5, Qt::Horizontal, "Razon" );
    setHeaderData( 6, Qt::Horizontal, "Responsable" );
    setHeaderData( 7, Qt::Horizontal, "¿Cierre?" );
    if( relaciones ) {
     setRelation( 1, QSqlRelation( "caja", "id_caja", "nombre" ) );
    }
}


QVariant MMovimientosCaja::data(const QModelIndex& item, int role) const
{
 switch( item.column() )
 {
     case 2:
     {
         return QSqlRelationalTableModel::data( item, role ).toDateTime().toString( Qt::SystemLocaleDate );
     }
     case 3:
     case 4:
     {
         if( role == Qt::DisplayRole )
         { return QString( "$ %L1" ).arg( QSqlRelationalTableModel::data( item, role ).toDouble() ); }
         else if( role == Qt::TextAlignmentRole )
         { return int( Qt::AlignCenter | Qt::AlignVCenter ); }
         else
         { return QSqlRelationalTableModel::data( item, role ); }
     }
     case 5:
     {
         if( role == Qt::TextAlignmentRole ) {
             return int( Qt::AlignLeft | Qt::AlignVCenter );
         } else {
             return QSqlRelationalTableModel::data( item, role ).toString();
         }
     }
     case 7:
     {
         if( QSqlRelationalTableModel::data( item, role ).toBool() ) { return "Si"; } else { return "No"; }
     }
     default:
     {
        if( role == Qt::TextAlignmentRole ) {
             return int( Qt::AlignCenter | Qt::AlignVCenter );
         } else {
             return QSqlRelationalTableModel::data( item, role );
         }
     }
 }
}



/*!
 * @fn MMovimientosCaja::agregarMovimiento( int id_caja, QString razon, QString responsable, double ingreso, double egreso )
 * Almacena una operación de caja. ingreso y egreso son mutuamente excluentes y no pueden ser los 2 iguales a 0
 * @param id_caja #ID de caja para la operacion
 * @param razon Texto para incluir ( luego sale en el resumen de caja )
 * @param responsable Persona responsable del movimiento ( usuario de la db o persona )
 * @param ingreso cantidad que ingresa a la caja
 * @param egreso cantidad que sacamos de la caja
 * @param agregando_caja Verdadero si no se desea actualizar el saldo por estar agregando la caja
 * @return verdadero si la operacion se completo satisfactoriamente
 */
bool MMovimientosCaja::agregarMovimiento( int id_caja, QString razon, QString responsable, double ingreso, double egreso, bool agregando_caja )
{
  // Verificaciones previas
  if( ( ingreso != 0 && egreso != 0 ) || ( ingreso > 0 && egreso > 0 ) ) {
       qWarning( QString( "El movimiento debe ser de entrada o salida, no ambos" ).toLocal8Bit() );
       return false;
  }
  QSqlRecord rec = this->record();
  rec.setValue( "id_caja", id_caja );
  rec.setValue( "razon", razon );
  if( responsable == QString() ) {
      rec.setValue( "responsable", this->usuarioActual() );
  }
  rec.setValue( "fecha_hora", QDateTime::currentDateTime() );
  rec.setValue( "cierre", false );
  if( ingreso != 0 ) {
      rec.setValue( "ingreso", ingreso );
      rec.setValue( "egreso", 0.0 );
  } else {
      rec.setValue( "egreso", egreso );
      rec.setValue( "ingreso", 0.0 );
  }
  if( this->insertRecord( -1, rec ) ) {
      // Actualizo el saldo de la cuenta en la tabla de cajas
      if( agregando_caja ) {
          // Si estamos agregando caja, busca el saldo anterior para actualizarlo el cual no existe todavia.
          return true;
      } else {
          return MCajas::actualizarSaldo( id_caja, ingreso-egreso );
      }

  } else {
      qWarning( QString( "Error al insertar movimiento: %1" ).arg( this->lastError().text() ).toLocal8Bit() );
      return false;
  }

}

/*!
 * @fn MMovimientosCaja::recalcularSaldo( const int id_caja )
 * Recalcula el saldo actual de la caja revisando todas las operaciones guardadas
 * @param id_caja #ID de caja
 * @return saldo calculado
 */
double MMovimientosCaja::recalcularSaldo( const int id_caja )
{
    // Sumar todos los ingresos y restarle los egresos en una consulta con QSqlQuery
    QSqlQuery cola( QString( "SELECT SUM(ingreso)-SUM(egreso) FROM %1 WHERE id_caja = %2 AND cierre = %3" ).arg( this->tableName() ).arg( id_caja ).arg( false ) );
    if( cola.next() ) {
        return MCajas::actualizarSaldo( id_caja, cola.record().value(0).toDouble() );
    } else { return false; }
}

/*!
 * @fn MMovimientosCaja::agregarCiere( const int id_caja, QDateTime fechahora, double saldo )
 * Recalcula el saldo actual de la caja revisando todas las operaciones guardadas
 * @param id_caja #ID de caja
 * @param fechahora Fech y hora del cierre
 * @param double Saldo computado para el cierre
 * @return Verdadero si se pudo realizar el cierre
 */
bool MMovimientosCaja::agregarCierre( const int id_caja, QDateTime fechahora, double saldo )
{
    QSqlRecord rec = this->record();
    rec.setValue( "id_caja", id_caja );
    rec.setValue( "razon", "Cierre de caja del dia " + fechahora.toString() );
    rec.setValue( "responsable", this->usuarioActual() );
    rec.setValue( "fecha_hora", fechahora );
    rec.setValue( "cierre", true );
    double saldo_anterior = MCajas::saldo( id_caja );
    double dif = saldo_anterior - saldo;
    if( dif > 0 ) {
        this->agregarMovimiento( id_caja, "Diferencia en el cierre de caja", QString(), dif );
        saldo_anterior += dif;
    } else if( dif < 0 ){
        this->agregarMovimiento( id_caja, "Diferencia en el cierre de caja", QString(), 0.0, dif );
        saldo_anterior -= dif;
    }
    // ATENCION: Se guarda el saldo en los 2 campos igual
    rec.setValue( "egreso", saldo_anterior );
    rec.setValue( "ingreso", saldo_anterior );
    if( this->insertRecord( -1, rec ) ) {
        return true;
    } else {
        qWarning( QString( "Error al insertar movimiento de cierre: %1" ).arg( this->lastError().text() ).toLocal8Bit() );
        return false;
    }
}

/*!
 * @fn MMovimientosCaja::buscarUltimoCierre( const int id_caja )
 * Busca el ultimo cierre de la caja especificada
 * @param id_caja Identificador de la caja
 * @returns ID de Movimiento de cierre si existe, -1 si hubo error al ejecutar la cola y 0 si error al obtener los datos por next
 */
int MMovimientosCaja::buscarUltimoCierre( const int id_caja ) {
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT id_movimiento FROM %1 WHERE id_caja = %3 AND cierre = %2 ORDER BY fecha_hora DESC LIMIT 1" ).arg( this->tableName() ).arg( true ).arg( id_caja ) ) ) {
        if( cola.next() ) {
            return cola.record().value(0).toInt();
        } else {
            qWarning( "Error al hacer next en la cola de ultimo cierre " );
            return 0;
        }
    } else {
        qWarning( QString( "Error al ejecutar la cola de ultimo cierre: %1" ).arg( this->lastError().text() ).toLocal8Bit() );
        return -1;
    }
}

/*!
 * @fn MMovimientosCaja::buscarMovimientos( const int id_caja, const int id_cierre )
 * Funcion que retorna los datos de todos los movimientos en una caja desde el cierre anterior al pasado como parametro
 * @param id_caja Identificador de la caja
 * @param id_cierre Cierre desde el cual se desean obtener todos los datos al cierre anterior
 * @returns Objeto QSqlQuery vacio si no hay ningun dato o con los datos asociados
 */
QSqlQuery MMovimientosCaja::buscarMovimientos( const int id_caja, const int id_cierre )
{
  // Busco el cierre anterior al que me pasaron
    int id_cierre_anterior = -1;
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT id_movimiento FROM %1 WHERE cierre = %2 AND id_movimiento < %3 AND id_caja = %4 ORDER BY fecha_hora DESC" ).arg( this->tableName() ).arg( true ).arg( id_cierre ).arg( id_caja )  ) ) {
        if( cola.next() ) {
            id_cierre_anterior = cola.record().value(0).toInt();
        } else {
            qWarning( "Error al hacer next en la cola de ultimo cierre " );
            id_cierre_anterior = 0;
        }
    } else {
        qWarning( QString( "Error al ejecutar la cola de ultimo cierre: %1" ).arg( this->lastError().text() ).toLocal8Bit() );
    }
    // Busco los datos
    if( cola.exec( QString( "SELECT id_movimiento, fecha_hora, ingreso, egreso, razon, responsable, cierre FROM %1 WHERE id_movimiento >= %2 AND id_movimiento <= %3 ORDER BY fecha_hora ASC" ).arg( this->tableName() ).arg( id_cierre_anterior ).arg( id_cierre ) ) ) {
        if( cola.next() ) {
            return cola;
        } else {
            return QSqlQuery();
        }
    } else {
        return QSqlQuery();
    }
}

/*!
 * @fn MMovimientosCaja::saldoEnMovimientoAnteriorA( const int id_caja, const int id_movimiento_cierre )
 * Devuelve el sado que existia en el cierre anterior al recibido como parametro para la caja indicada
 * @param id_caja Caja sobre la cual se busca
 * @param id_movimiento_cierre Identificador del movimiento de cierre del cual queremos saber el saldo del cierre anterior
 * @return Saldo anterior al cierre pasado como parametro
 */
double MMovimientosCaja::saldoEnMovimientoAnteriorA( const int id_caja, const int id_movimiento_cierre ) {
  // Busco el movimiento de cierre anterior al recibido de parametro y devuelvo el saldo
  QSqlQuery cola;
  if( cola.exec( QString( "SELECT id_movimiento, ingreso, egreso FROM %1 WHERE cierre = %2 AND id_movimiento < %3 AND id_caja = %4 ORDER BY fecha_hora DESC" ).arg( this->tableName() ).arg( true ).arg( id_movimiento_cierre ).arg( id_caja ) ) ) {
     if( cola.next() ) {
         if( cola.record().value("ingreso").toDouble() == cola.record().value("egreso").toDouble() ) {
             return cola.record().value( "ingreso" ).toDouble();
         } else {
             qWarning( "Los datos del cierre no coinciden entre si" );
             return 0.0;
         }
     } else {
        // Este error se produce posiblemente porque noe xiste un movimiento de cierre anterior. Busco el saldo inicial.
         if( cola.exec( QString( "SELECT id_movimiento, ingreso, egreso FROM movimiento_caja WHERE id_movimiento < %1 AND id_caja = %2 ORDER BY fecha_hora DESC LIMIT 1" ).arg( id_movimiento_cierre ).arg( id_caja ) ) ) {
             if( cola.next() ) {
                 if( cola.record().value("ingreso").toDouble() == cola.record().value("egreso").toDouble() ) {
                     return cola.record().value( "ingreso" ).toDouble();
                 } else {
                     qWarning( "Los datos del cierre no coinciden entre si" );
                     return 0.0;
                 }
             } else {
                qWarning( "Error al intentar encontrar el saldo inicial despues de no encontrar un cierre anterior haciendo next" );
                return 0.0;
             }
         } else {
             qWarning( "Error al ejecutar la cola al intentar encontrar el saldo inicial despues de no encontrar un cierre anterior" );
             return 0.0;
         }
     }
  } else {
     qWarning( QString( "Error al ejecutar la cola de ultimo cierre para saldo anterior a movimiento: %1" ).arg( this->lastError().text() ).toLocal8Bit() );
     return 0.0;
  }
}

/*!
 * @fn MMovimientosCaja::ultimosMovimientosCaja( const int id_caja )
 * Funcion que genera el filtro para mostrar los movimientos de caja desde el ultimo cierre, incluyendolo. Esta funcion hace select()
 * @param id_caja Identificador de caja
 **/
void MMovimientosCaja::ultimosMovimientosCaja( const int id_caja )
{
 int id_mov = this->buscarUltimoCierre( id_caja );
 this->setFilter( QString( " id_movimiento >=  %1 AND id_caja = %2 " ).arg( id_mov ).arg( id_caja ) );
 this->select();
}

/*!
 * @fn MMovimientosCaja::usuarioActual()
 * Devuelve el usuario loggeado en la base de datos actualmente
 */
QString MMovimientosCaja::usuarioActual()
{
   if( QSqlDatabase::database().driverName() == "QMYSQL" ) {
       QSqlQuery cola;
       if( cola.exec( "SELECT SUBSTRING_INDEX( USER(), '@', 1 );" ) )
       { cola.next(); return cola.record().value(0).toString(); } else { return "default"; }
   } else { return "default"; }
}

/*!
 * @fn MMovimientosCaja::verificarCierreCaja( const int id_caja )
 * Verifica si se puede hacer el cierre de caja, o sea, si existe algun movimiento aparte del ultimo cierre.
 * @param id_caja Identificador de la caja de la cual se desea averiguar
 * @returns Verdadero si se puede hacer, falso si no se puede hacer
 */
bool MMovimientosCaja::verificarCierreCaja( const int id_caja )
{
    QSqlQuery cola;
    // Busco el ultimo cierre
    int id_ultimo_cierre = this->buscarUltimoCierre( id_caja );
    if( id_ultimo_cierre <= 0 ) { return false; }
    // Cuento la cantidad de movimientos que hubo despues de ese movimiento de cierre
    if( cola.exec( QString( "SELECT COUNT(id_movimiento) FROM %2 WHERE id_caja = %1 AND id_movimiento > %3" ).arg( id_caja ).arg( this->tableName() ).arg( id_ultimo_cierre ) ) ) {
        if( cola.next() ) {
            if( cola.record().value(0).toInt() > 0 ) {
                return true;
            } else {
                return false;
            }
        } else {
            qWarning( "Error al hacer next en la cola de averiguacion de si se puede hacer el cierre de caja" );
            return false;
        }
    } else {
        qWarning( "No se pudo ejecutar la cola de averiguacion de si se puede hacer el cierre de caja" );
        return false;
    }
}
