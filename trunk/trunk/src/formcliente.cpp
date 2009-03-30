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
#include "formcliente.h"

#include <QDataWidgetMapper>

#include "eactcerrar.h"
#include "eactguardar.h"

FormCliente::FormCliente ( QWidget* parent, QSqlTableModel *modelo, Qt::WFlags fl )
: EVentana ( parent, fl ), Ui::FormClienteBase()
{
	setupUi ( this );
	setObjectName( "visorCliente" );
	setWindowTitle( "Visor de Cliente" );
	setWindowIcon( QIcon( ":/imagenes/cliente.png" ) );

	QDataWidgetMapper *map = new QDataWidgetMapper( this );
	map->setModel( modelo );
	map->addMapping( LERazonSocial, modelo->fieldIndex( "razon_social" ) );
	map->addMapping( LENombre, modelo->fieldIndex( "nombre" ) );
	map->addMapping( LESegundoNombre, modelo->fieldIndex( "segundo" ) );
	map->addMapping( LEApellido, modelo->fieldIndex( "apellido" ) );
	map->addMapping( LECalle, modelo->fieldIndex( "calle" ) );
	map->addMapping( LENumero, modelo->fieldIndex( "numero" ) );
	map->addMapping( LEPiso, modelo->fieldIndex( "piso" ) );
	map->addMapping( LEDepto, modelo->fieldIndex( "depto" ) );
	map->addMapping( LECiudad, modelo->fieldIndex( "ciudad" ) );
	map->addMapping( LECodPostal, modelo->fieldIndex( "codigo_postal" ) );
	map->addMapping( LEProvincia, modelo->fieldIndex( "provincia" ) );
	map->addMapping( LEPais, modelo->fieldIndex( "pais" ) );
	map->addMapping( LETelFijo, modelo->fieldIndex( "tel_fijo" ) );
	map->addMapping( LETelCel, modelo->fieldIndex( "tel_cel" ) );
	map->addMapping( LEEmail, modelo->fieldIndex( "email" ) );
	map->addMapping( CkBComprobanteEmail, modelo->fieldIndex( "comprobante_email" ) );

	map->setOrientation( Qt::Horizontal );
	map->setSubmitPolicy( QDataWidgetMapper::ManualSubmit );
	//map->setCurrentIndex(

	//Acciones predefinidas
	EActGuardar *ActGuardar = new EActGuardar( this );
	this->addAction( ActGuardar );
	EActCerrar *ActCerrar = new EActCerrar( this );
	this->addAction( ActCerrar );

}

FormCliente::~FormCliente()
{
}





/*!
    \fn FormCliente::guardar()
 */
void FormCliente::guardar()
{
    /// @todo implement me
}


/*!
    \fn FormCliente::setearCliente( QModelIndex &indice )
 */
void FormCliente::setearCliente( QModelIndex &indice )
{
    /// @todo implement me
}
