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
#include "formmudanza.h"

#include <QSqlQuery>
#include <QProgressDialog>
#include "emovimiento.h"
#include <QMessageBox>
#include <QSqlError>
#include <QStringListModel>

FormMudanza::FormMudanza(QWidget* parent, Qt::WFlags fl)
: FormMovimiento( parent, fl, FormMovimiento::movimiento )
{
 LTitulo->setText( "Movimiento de Caravanas Interno" );
 //Agrego el completador
}

FormMudanza::~FormMudanza()
{
}






/*!
    \fn FormMudanza::cerrar()
 */
void FormMudanza::cerrar()
{
 FormMovimiento::cerrar();
}


/*!
    \fn FormMudanza::guardar()
 */
void FormMudanza::guardar()
{
  if( !verificar() )
 {
  return;
 }
 QSqlQuery c( "BEGIN TRANSACTION" );
 QProgressDialog *dialogo = new QProgressDialog( this );
 dialogo->setLabelText( "Guardando datos del TRI" );
 dialogo->setMinimum( 0 );
 dialogo->setMaximum( 6 );
 dialogo->setValue( 0 );
 dialogo->setMinimumDuration( 0 );
 dialogo->show();
 EMovimiento *movimiento = new EMovimiento( this );
 // Tipo de Movimiento
 movimiento->setTipoMov( EMovimiento::mudanza );
 dialogo->setValue( dialogo->value() + 1 );
 // DTA
 if( !movimiento->setDTA( LEDTA->text() ) )
 {
	dialogo->close();
	return;
 }
 dialogo->setValue( dialogo->value() + 1 );
 // Fecha
 movimiento->setFecha( dEFecha->date() );
 dialogo->setValue( dialogo->value() + 1 );
 // Categoria
 movimiento->setCategoria( CBCategoria->model()->data( CBCategoria->model()->index( CBCategoria->currentIndex(), 0 ), Qt::EditRole ).toInt() );
 dialogo->setValue( dialogo->value() + 1 );
 // Establecimiento de origen
 movimiento->setEstablecimientoOrigen( CBEstablecimientoOrigen->model()->data( CBEstablecimientoOrigen->model()->index( CBEstablecimientoOrigen->currentIndex(), 0 ), Qt::EditRole ).toInt() );
 dialogo->setValue( dialogo->value() + 1 );
 // Comprador
 movimiento->setEstablecimientoDestino( CBEstablecimientoDestino->model()->data( CBEstablecimientoDestino->model()->index( CBEstablecimientoDestino->currentIndex(), 0 ), Qt::EditRole ).toInt() );
 dialogo->setValue( dialogo->value() + 1 );
 // Lista de caravanas
 dialogo->setLabelText( "Comprobando caravanas..." );
 QStringList lista = model->stringList();
 dialogo->setRange( 0, lista.size() );
 dialogo->setValue( 0 );
 QString cadena;
 foreach( cadena, lista )
 {
  movimiento->agregarCaravana( cadena );
 }
 // Lista la comprobacion de caravanas
 // comienzo a guardar todo
 dialogo->setLabelText( "Guardando datos..." );
 int id = movimiento->guardar( dialogo );
 if( id < 0 )
 {
	QMessageBox::critical( this, "Error al guardar los datos", "No se ha podido guardar los datos de esta compra" );
	dialogo->close();
	c.exec( "ROLLBACK TRANSACTION" );
	return;
 }
 else
 {
  if( c.exec( "COMMIT" ) )
  {
   QMessageBox::information( this, "Correcto", "La informacion se ha guardado correctamente");
  }
  else
  {
   qWarning( QString( "Error al hacer el commit\n Error: %1" ).arg( c.lastError().text() ).toLocal8Bit() );
  }
 }
 dialogo->close();
 this->close();
}
