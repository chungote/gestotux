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
#include "formagregar.h"

#include "emovimiento.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QProgressDialog>
#include <QErrorMessage>
#include <QMessageBox>
#include <QStringListModel>

FormAgregar::FormAgregar(QWidget* parent, Qt::WFlags fl)
: FormMovimiento( parent, fl, FormMovimiento::compra )
{
 
}

FormAgregar::~FormAgregar()
{
}


/*!
    \fn FormAgregar::guardar()
 */
void FormAgregar::guardar()
{
    /// @todo implement me
 QProgressDialog *dialogo = new QProgressDialog( this );
 dialogo->setLabelText( "Guardando datos del TRI" );
 dialogo->setMinimum( 0 );
 dialogo->setMaximum( 6 );
 dialogo->setValue( 0 );
 dialogo->show();
 EMovimiento *movimiento = new EMovimiento( this );
 // Tipo de Movimiento
 movimiento->setTipoMov( EMovimiento::compra );
 dialogo->setValue( dialogo->value() + 1 );
 // DTA
 movimiento->setDTA( LEDTA->text() );
 dialogo->setValue( dialogo->value() + 1 );
 // Fecha
 movimiento->setFecha( dEFecha->date() );
 dialogo->setValue( dialogo->value() + 1 );
 // Categoria
 movimiento->setCategoria( CBCategoria->model()->data( CBCategoria->model()->index( CBCategoria->currentIndex(), 0 ), Qt::EditRole ).toInt() );
 dialogo->setValue( dialogo->value() + 1 );
 // Establecimiento  de destino
 movimiento->setEstablecimientoDestino( CBEstablecimientoDestino->model()->data( CBEstablecimientoDestino->model()->index( CBEstablecimientoDestino->currentIndex(), 0 ), Qt::EditRole ).toInt() );
 dialogo->setValue( dialogo->value() + 1 );
 // Vendedor
 movimiento->setVendedor( CBCliente->model()->data( CBCliente->model()->index( CBCliente->currentIndex(), 0 ), Qt::EditRole ).toInt() );
 dialogo->setValue( dialogo->value() + 1 );
 // Chequear que no existan los numeros de caravanas ya en la tabla
 // Busco todos los codigos dados de alta en la tabla de caravanas
 dialogo->setLabelText( "Comprobando caravanas..." );
 QStringList lista = model->stringList();
 dialogo->setRange( 0, lista.size() );
 dialogo->setValue( 0 );
 QString cadena; QSqlQuery cola;
 foreach( cadena, lista )
 {
  if( cola.exec( QString( "SELECT COUNT(codigo) FROM car_caravanas WHERE codigo = '%1'" ).arg( cadena ) ) )
  {
   if( cola.next() )
   {
    if( cola.record().value(0).toInt() >= 1 )
    {
 	QErrorMessage *di = new QErrorMessage( this );
	di->showMessage( QString( "La caravana de codigo %1 ya existe al menos %2 veces en el sistema, no sera guardada en este tri" ).arg( cadena ).arg( cola.record().value(0).toInt() ) );
	lista.removeAt( lista.indexOf( cadena ) );
    }
    dialogo->setValue( dialogo->value() +1 );
   }
   else
   {
     qWarning( QString( "Error al hace next en buscar codigos de caravanas\n Error: %1\n %2" ).arg( cola.lastError().text() ).arg( cola.lastQuery() ).toLocal8Bit() );
   }
  }
  else
  {
    qWarning( QString( "Error al buscar codigos de caravanas\n Error: %1\n %2" ).arg( cola.lastError().text() ).arg( cola.lastQuery() ).toLocal8Bit() );
  }
 }
 // Lista la comprobacion de caravanas
 // comienzo a guardar todo
 dialogo->setLabelText( "Guardando datos..." );
 dialogo->setValue( 0 );
 dialogo->setRange( 0, lista.size() +1 );
 int id = movimiento->guardar();
 if( id < 0 )
 {
	QMessageBox::critical( this, "Error al guardar los datos", "No se ha podido guardar los datos de esta compra" );
	return;
 }
 dialogo->setValue( dialogo->value() +1 );
 // guardo las caravanas
}


/*!
    \fn FormAgregar::cerrar()
 */
void FormAgregar::cerrar()
{
 close();
}
