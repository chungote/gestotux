/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller  				   *
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
#include "formcliente.h"

#include <QMessageBox>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>

#include "eactcerrar.h"
#include "eactguardar.h"
#include "mclientes.h"

FormCliente::FormCliente ( QWidget* parent, MClientes *modelo,  Qt::WFlags fl )
: EVentana ( parent, fl ), Ui::FormClienteBase()
{
	setupUi ( this );
	setObjectName( "visorCliente" );
	setWindowTitle( "Visor de Cliente" );
	setWindowIcon( QIcon( ":/imagenes/clientes.png" ) );
	this->modelo = modelo;
	modelo->setEditStrategy( QSqlTableModel::OnManualSubmit );

	connect( LENombre       , SIGNAL( textChanged( const QString & ) ), this, SLOT( rehaceRazonSocial( const QString & ) ) );
	connect( LESegundoNombre, SIGNAL( textChanged( const QString & ) ), this, SLOT( rehaceRazonSocial( const QString & ) ) );
	connect( LEApellido     , SIGNAL( textChanged( const QString & ) ), this, SLOT( rehaceRazonSocial( const QString & ) ) );

	//Acciones predefinidas
	EActGuardar *ActGuardar = new EActGuardar( this );
	this->addAction( ActGuardar );
	EActCerrar *ActCerrar = new EActCerrar( this );
	this->addAction( ActCerrar );

}

FormCliente::~FormCliente()
{}


/*!
    \fn FormCliente::guardar()
 */
void FormCliente::guardar()
{
 // Chequeo los datos que no pueden ser nulos
 if( LERazonSocial->text().isNull() )
 {
  QMessageBox::warning( this, "Faltan Datos", "Por favor ingrese minimamente una razon social para el cliente" );
  return;
 }
 QSqlRecord rc = modelo->record();
 rc.setValue( "razon_social", LERazonSocial->text() );
 if( LERazonSocial->text().isEmpty() )
 { rc.setNull( "razon_social" ); }
 else
 { rc.setValue( "razon_social", LERazonSocial->text() ); }
 ///////////////////////////////////////////////////////////////////////
 if( LENombre->text().isEmpty() )
 { rc.setNull( "nombre" ); }
 else
 { rc.setValue( "nombre", LENombre->text() ); }
 ///////////////////////////////////////////////////////////////////////
 if( LESegundoNombre->text().isEmpty() )
 { rc.setNull( "segundo" ); }
 else
 { rc.setValue( "segundo", LESegundoNombre->text() ); }
 ///////////////////////////////////////////////////////////////////////
 if( LEApellido->text().isEmpty() )
 { rc.setNull( "apellido" ); }
 else
 { rc.setValue( "apellido", LEApellido->text() ); }
 ////////////////////////////////////////////////////////////////////////
 if( LECalle->text().isEmpty() )
 { rc.setNull( "calle" ); }
 else
 { rc.setValue( "calle", LECalle->text() ); }
 ////////////////////////////////////////////////////////////////////////
 if( LENumero->text().isEmpty() )
 { rc.setNull( "numero" ); }
 else
 { rc.setValue( "numero", LENumero->text() ); }
 ////////////////////////////////////////////////////////////////////////
 if( LEPiso->text().isEmpty() )
 { rc.setNull( "piso" ); }
 else
 { rc.setValue( "piso", LEPiso->text() ); }
 ////////////////////////////////////////////////////////////////////////
 if( LEDepto->text().isEmpty() )
 { rc.setNull( "depto" ); }
 else
 { rc.setValue( "depto", LEDepto->text() ); }
 ////////////////////////////////////////////////////////////////////////
 if( LECiudad->text().isEmpty() )
 { rc.setNull( "ciudad" ); }
 else
 { rc.setValue( "ciudad", LECiudad->text() ); }
 ////////////////////////////////////////////////////////////////////////
 if( LECodPostal->text().isEmpty() )
 { rc.setNull( "codigo_postal" ); }
 else
 { rc.setValue( "codigo_postal", LECodPostal->text() ); }
 ////////////////////////////////////////////////////////////////////////
 if( LEProvincia->text().isEmpty() )
 { rc.setNull( "provincia" ); }
 else
 { rc.setValue( "provincia", LEProvincia->text() ); }
 ////////////////////////////////////////////////////////////////////////
 if( LEProvincia->text().isEmpty() )
 { rc.setNull( "provincia" ); }
 else
 { rc.setValue( "provincia", LEProvincia->text() ); }
 ////////////////////////////////////////////////////////////////////////
 if( LEPais->text().isEmpty() )
 { rc.setNull( "pais" ); }
 else
 { rc.setValue( "pais", LEPais->text() ); }
 ////////////////////////////////////////////////////////////////////////
 if( LETelFijo->text().isEmpty() )
 { rc.setNull( "tel_fijo" ); }
 else
 { rc.setValue( "tel_fijo", LETelFijo->text() ); }
 ////////////////////////////////////////////////////////////////////////
 if( LETelCel->text().isEmpty() )
 { rc.setNull( "tel_celular" ); }
 else
 { rc.setValue( "tel_celular", LETelCel->text() ); }
 ////////////////////////////////////////////////////////////////////////
 if( LEFax->text().isEmpty() )
 { rc.setNull( "fax" ); }
 else
 { rc.setValue( "fax", LEFax->text() ); }
 ////////////////////////////////////////////////////////////////////////
 if( LEEmail->text().isEmpty() )
 { rc.setNull( "email" ); }
 else
 { rc.setValue( "email", LEEmail->text() ); }
 ////////////////////////////////////////////////////////////////////////
 rc.setValue( "comprobante_email", CkBComprobanteEmail->isChecked() );
 //map->addMapping( CBListaPrecio      , modelo->fieldIndex( "lista_precio_id"   ) );
 if( modelo->insertRecord( -1, rc ) )
 {
  if( modelo->submitAll() )
  {
   QMessageBox::information( this, "Correcto", "El cliente se guardo correctamente" );
   close();
   return;
  }
  else
  {
   qWarning( "Error al hacer submit del modelo de datos de cliente" );
   qWarning( qPrintable( modelo->lastError().text() ) );
   qWarning( qPrintable( modelo->query().lastQuery() ) );

   return;
  }
 }
 else
 {
   qWarning( "Error al insertar el registro de datos de cliente" );
   qWarning( qPrintable( modelo->lastError().text() ) );
   qWarning( qPrintable( modelo->query().lastQuery() ) );
   return;
 }
}


/*!
    \fn FormCliente::setearCliente( QModelIndex &indice )
 */
void FormCliente::setearCliente( QModelIndex &indice )
{
    /// @todo implement me
}


/*!
    \fn FormCliente::rehaceRazonSocial( const QString & )
 */
void FormCliente::rehaceRazonSocial( const QString &texto )
{
 // Este slot siempre se llama por diferencia de 1 caracter o texto vacio.
 if( texto.isEmpty() )
 { return; }
 QString anterior = texto; anterior.remove( texto.length()-1, 1 );
 if( LERazonSocial->text().contains( anterior ) || LERazonSocial->text().isEmpty() )
 {
  LERazonSocial->setText( LEApellido->text() + ", " + LENombre->text() + " " + LESegundoNombre->text() );
 }
 return;
}
