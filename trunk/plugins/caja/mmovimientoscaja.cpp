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

#include "mcajas.h"

MMovimientosCaja::MMovimientosCaja( QObject *parent, bool relaciones ) :
    QSqlRelationalTableModel(parent)
{
    setTable( "movimiento_caja" );
    setHeaderData( 0, Qt::Horizontal, "#Movimiento" );
    setHeaderData( 1, Qt::Horizontal, "#Caja" );
    setHeaderData( 2, Qt::Horizontal, "Fecha y Hora" );
    setHeaderData( 3, Qt::Horizontal, "Debe" );
    setHeaderData( 4, Qt::Horizontal, "Haber" );
    setHeaderData( 5, Qt::Horizontal, "Razon" );
    setHeaderData( 6, Qt::Horizontal, "Responsable" );
    setHeaderData( 7, Qt::Horizontal, "¿Cierre?" );
    if( relaciones ) {
     setRelation( 1, QSqlRelation( "caja", "id_caja", "nombre" ) );
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
      responsable = "USERNAME()";  /// @todo VERIFICAR X TIPO DE PLUGIN COMO SACAR EL USUARIO ACTUAL
  }
  rec.setValue( "responsable", responsable );
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
 * @fn MMovimientosCaja::recalcularSaldo( int id_caja )
 * Recalcula el saldo actual de la caja revisando todas las operaciones guardadas
 * @param id_caja #ID de caja
 * @return saldo calculado
 */
double MMovimientosCaja::recalcularSaldo( int id_caja )
{
    // Sumar todos los ingresos y restarle los egresos en una consulta con QSqlQuery
    QSqlQuery cola( QString( "SELECT SUM(ingreso)-SUM(egreso) FROM %1 WHERE id_caja = %2 AND cierre = %3" ).arg( this->tableName() ).arg( id_caja ).arg( false ) );
    if( cola.next() ) {
        return MCajas::actualizarSaldo( id_caja, cola.record().value(0).toDouble() );
    } else { return false; }
}

/*!
 * @fn MMovimientosCaja::agregarCiere( int id_caja, QDateTime fechahora, double saldo )
 * Recalcula el saldo actual de la caja revisando todas las operaciones guardadas
 * @param id_caja #ID de caja
 * @param fechahora Fech y hora del cierre
 * @param double Saldo computado para el cierre
 * @return Verdadero si se pudo realizar el cierre
 */
bool MMovimientosCaja::agregarCierre( int id_caja, QDateTime fechahora, double saldo )
{
    QSqlRecord rec = this->record();
    rec.setValue( "id_caja", id_caja );
    rec.setValue( "razon", "Cierre de caja del dia " + fechahora.toString() );
    rec.setValue( "responsable", "USERNAME()" );
    rec.setValue( "fecha_hora", fechahora );
    rec.setValue( "cierre", true );
    double saldo_anterior = MCajas::saldo( id_caja );
    double dif = saldo_anterior - saldo;
    if( dif == 0 ) {
        this->agregarMovimiento( id_caja, "Diferencia en el cierre de caja", QString(), dif );
    } else if( dif < 0 ){
        this->agregarMovimiento( id_caja, "Diferencia en el cierre de caja", QString(), 0.0, dif );
    }
    rec.setValue( "egreso", 0.0 );
    rec.setValue( "ingreso", 0.0 );
    if( this->insertRecord( -1, rec ) ) {
        return true;
    } else {
        qWarning( QString( "Error al insertar movimiento de cierre: %1" ).arg( this->lastError().text() ).toLocal8Bit() );
        return false;
    }
}