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

#include "mcajas.h"

#include <QSqlRecord>
#include <QSqlError>

MCajas::MCajas(QObject *parent ) :
    QSqlTableModel(parent)
{
    setTable( "caja" );
    this->setHeaderData( 0, Qt::Horizontal, "#ID" );
    this->setHeaderData( 1, Qt::Horizontal, "Nombre" );
    this->setHeaderData( 2, Qt::Horizontal, "Fecha de Alta"  );
    this->setHeaderData( 3, Qt::Horizontal, "Saldo Actual" );
}

/*!
  @fn MCajas::agregarCaja( QString nombre, QDate fecha_alta = QDate::currentDate(), double saldo_inicial )
  Funcion para agregar una caja nueva al sistema
  @param nombre Nombre de la caja
  @param fecha_alta Fecha en que se da de alta
  @param saldo_inicial Saldo inicial de la caja
 */
bool MCajas::agregarCaja( QString nombre, QDate fecha_alta, double saldo_inicial )
{
  QSqlRecord rec = this->record();
  rec.setValue( "nombre", nombre );
  rec.setValue( "fecha_alta", fecha_alta );
  rec.setValue( "saldo", saldo_inicial );
  // Agregar el registro de transaccion inicial en la tabla de movimientos

  if( insertRecord( -1, rec ) ) {
      return true;
  } else {
      qWarning( QString( "Error al insertar caja nueva: %1" ).arg( this->lastError().text() ).toLocal8Bit() );
      return false;
  }
}
