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
#include "vcuentacorriente.h"

#include "mcuentacorriente.h"
#include <QTableView>
#include <QAction>
#include <QMenu>
#include <QInputDialog>
#include <QMessageBox>

VCuentaCorriente::VCuentaCorriente(QWidget *parent)
 : EVLista(parent)
{
 this->setObjectName( "visor_ctaCte" );
 this->setWindowTitle( "Cuentas Corrientes" );

 rmodelo = new MCuentaCorriente( this );
 vista->setModel( rmodelo );
 modelo = 0;
 rmodelo->select();

 ActResumen = new QAction( "Ver Resumen de Cuenta", this );
 connect( ActResumen, SIGNAL( triggered() ), this, SLOT( verResumen() ) );

 ActAgregar->setText( "Agregar Nueva CtaCte" );

 addAction( ActAgregar );
 addAction( ActResumen );
 addAction( ActCerrar );
}


VCuentaCorriente::~VCuentaCorriente()
{
}


#include "formnuevactacte.h"
/*!
    \fn VCuentaCorriente::agregar( bool autoeliminarid )
 */
void VCuentaCorriente::agregar( bool autoeliminarid )
{
 FormNuevaCtaCte d;
 d.setModelo( rmodelo );
 d.exec();
}


/*!
    \fn VCuentaCorriente::menuContextual( const QModelIndex &indice, QMenu *menu )
 */
void VCuentaCorriente::menuContextual( const QModelIndex &indice, QMenu *menu )
{
 menu->addAction( ActAgregar );
 menu->addSeparator();
 if( !indice.model()->data( indice.model()->index( indice.row(), rmodelo->fieldIndex( "fecha_baja" ) ) ).toDate().isValid() )
 {
	QAction *ActDarBaja = new QAction( "Dar de Baja", this );
	connect( ActDarBaja, SIGNAL( triggered() ), this, SLOT( darBaja() ) );
	menu->addAction( ActDarBaja );

 	QAction *ActModificarLimite = new QAction( "Modificar Limite", this );
 	connect( ActModificarLimite, SIGNAL( triggered() ), this, SLOT( modificarLimite() ) );
 	menu->addAction( ActModificarLimite );
 }

 menu->addAction( ActResumen );

}


/*!
    \fn VCuentaCorriente::modificarLimite()
 */
void VCuentaCorriente::modificarLimite()
{
 // Busco el item
 QModelIndex indice = vista->selectionModel()->selectedRows().first();
 double limite_anterior = indice.model()->data( indice.model()->index( indice.row(), rmodelo->fieldIndex( "limite" ) ) ).toDouble();
 bool ok;
 double limite_nuevo = QInputDialog::getDouble( this, "Limite maximo de credito:", "Ingrese el limite maximo", limite_anterior, 0.0, 1000000.0, 3, &ok );
 if( ok )
 {
  //Verifico que no sean el mismo
  if( limite_anterior == limite_nuevo )
  { return; }
   rmodelo->setData( rmodelo->index( indice.row(), rmodelo->fieldIndex( "limite" ) ), limite_nuevo, Qt::EditRole );
   rmodelo->submitAll();
 }
 else
 { return; }

}


/*!
    \fn VCuentaCorriente::darBaja()
 */
void VCuentaCorriente::darBaja()
{
 // busco el item
 QModelIndex indice = vista->selectionModel()->selectedRows().first();
 int ret = QMessageBox::question( this, "¿Esta seguro?", "Esta seguro que desea deshabilitar esta cuenta corriente?", QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel );
 if( ret == QMessageBox::Ok )
 {
  rmodelo->setData( rmodelo->index( indice.row(), rmodelo->fieldIndex( "fecha_baja" ) ), QDate::currentDate(), Qt::EditRole );
  rmodelo->submitAll();
 }
}


#include "formresumenctacte.h"
/*!
    \fn VCuentaCorriente::verResumen()
 */
void VCuentaCorriente::verResumen()
{
 if( vista->selectionModel()->selectedRows().isEmpty() )
 { qWarning( "Elija una cuenta corriente para ver su resumen" ); return; } ///@todo Cambiar por un cuadro de dialogo
 QModelIndex indice = vista->selectionModel()->selectedRows().first();
 //Obtengo el numero de cuenta
 int numero_cuenta = indice.model()->data( indice.model()->index( indice.row(), rmodelo->fieldIndex( "numero_cuenta" ) ), Qt::EditRole ).toInt();
 FormResumenCtaCte *form = new FormResumenCtaCte( this );
 form->setNumeroCuenta( numero_cuenta );
 emit agregarVentana( form );
}
