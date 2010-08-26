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

bool MMovimientosCaja::agregarMovimiento( int id_caja, QString razon, QString responsable, double ingreso, double egreso )
{
  // Verificaciones previas
  if( ingreso != 0 && egreso != 0 ) {
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
      MCajas::actualizarSaldo( id_caja, ingreso-egreso );
      return true;
  } else {
      qWarning( QString( "Error al insertar movimiento: %1" ).arg( this->lastError().text() ).toLocal8Bit() );
      return false;
  }

}
