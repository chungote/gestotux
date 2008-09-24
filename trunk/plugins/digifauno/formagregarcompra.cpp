/***************************************************************************
 *   Copyright (C) 2006 by Esteban Zeller & Daniel Sequeira		   *
 *   juiraze@yahoo.com.ar  - daniels@hotmail.com			   *
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
#include "formagregarcompra.h"

#include "mproveedor.h"
#include "mcompra.h"
#include <QMessageBox>
#include <QDate>

FormAgregarCompra::FormAgregarCompra( QWidget* parent )
: EVentana( parent ), Ui::FormAgregarCompraBase()
{
	setupUi(this);
	nombre_ventana = "agregar_compra";
	setNombreVentana( "Agregar nueva compra" );

	PBCancelar->setText( "Cer&rar" );
	PBCancelar->setShortcut( QKeySequence( "Alt+c" ) );
	PBCancelar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
        connect( PBCancelar, SIGNAL( clicked() ), this, SLOT( close() ) );

        PBAceptar->setText( "&Guardar" );
        PBAceptar->setShortcut( QKeySequence( "Alt+g" ) );
        PBAceptar->setIcon( QIcon( ":/imagenes/guardar.png" ) );
        connect( PBAceptar, SIGNAL( clicked() ), this, SLOT( guardar() ) );

        modeloProveedor = new MProveedor( CBProveedor );
        CBProveedor->setModel( modeloProveedor );
        CBProveedor->setModelColumn( 1 );
        modeloProveedor->select();

        CWFecha->setMaximumDate( QDate::currentDate() );
        CWFecha->setSelectedDate( QDate::currentDate() );
}

FormAgregarCompra::~FormAgregarCompra()
{
}

/*!
    \fn FormAgregarCompra::guardar()
 */
void FormAgregarCompra::guardar()
{
 if( CBProveedor->currentIndex() != -1 )
 {
  if( dSBCosto->value() > 0 )
  {
   MCompra *modelo = new MCompra( this );
   if( modelo->agregarCompra(  CWFecha->selectedDate(),
                               CBProveedor->model()->data( CBProveedor->model()->index( CBProveedor->currentIndex(), 0 ), Qt::EditRole ),
                               dSBCosto->value() ) )
   {
    QMessageBox::information( this, "Correcto!", "Los datos de esta compra se guardaron correctamente" );
    this->close();
    return;
   }
   else
   {
    QMessageBox::critical( this, "Error", "Hubo un error al guardar los datos" );
    return;
   }
  }
  else
  {
   QMessageBox::warning( this,  "Faltan Datos", "Por favor, ingrese un costo para esta compra" );
   return;
  }
 }
 else
 {
  qDebug( "Proveedor incorrecto" );
  QMessageBox::warning( this, "Faltan Datos" , "Por favor, ingrese un proveedor para eta compra" );
  return;
 }
}