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
#include <QHeaderView>
#include "dsino.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

VCuentaCorriente::VCuentaCorriente(QWidget *parent)
 : EVLista(parent)
{
 this->setObjectName( "visor_ctaCte" );
 this->setWindowTitle( "Cuentas Corrientes" );
 this->setWindowIcon( QIcon( ":/imagenes/ctacte.png" ) );

 rmodelo = new MCuentaCorriente( this );
 vista->setModel( rmodelo );
 vista->setItemDelegateForColumn( 6, new DSiNo( this->vista ) );
 vista->horizontalHeader()->setResizeMode( QHeaderView::ResizeToContents );
 vista->horizontalHeader()->setResizeMode( 1, QHeaderView::Stretch );
 vista->horizontalHeader()->setMinimumSectionSize( 60 );
 vista->setSortingEnabled( true );
 connect( rmodelo, SIGNAL( dataChanged( QModelIndex, QModelIndex ) ), vista, SLOT( dataChanged( QModelIndex, QModelIndex ) ) );
 modelo = 0;

 ActResumen = new QAction( "Ver Resumen de Cuenta", this );
 connect( ActResumen, SIGNAL( triggered() ), this, SLOT( verResumen() ) );

 ActAgregar->setText( "Agregar Nueva CtaCte" );
 ActAgregar->setIcon( QIcon( ":/imagenes/ctacte_nueva.png" ) );

 QAction *ActSep = new QAction( this );
 ActSep->setSeparator(true );

 ActVerDeudoras = new QAction( this );
 ActVerDeudoras->setStatusTip( "Muestra solo las cuentas corrientes que tienen registrados movimientos mas altos que su limite." );
 ActVerDeudoras->setText( "Solo Sobrepasadas" );
 ActVerDeudoras->setCheckable( true );
 connect( ActVerDeudoras, SIGNAL( toggled( bool ) ), this, SLOT( mostrarDeudoras( bool ) ) );

 ActModificarLimite = new QAction( "Modificar Limite", this );
 connect( ActModificarLimite, SIGNAL( triggered() ), this, SLOT( modificarLimite() ) );

 addAction( ActAgregar );
 addAction( ActModificarLimite );
 addAction( ActVerTodos );
 addAction( ActResumen );
 addAction( ActCerrar );
 addAction( ActSep );
 addAction( ActVerDeudoras );
}

#include "formnuevactacte.h"
/*!
    \fn VCuentaCorriente::agregar( bool autoeliminarid )
 */
void VCuentaCorriente::agregar( bool /*autoeliminarid*/ )
{
 // Verifico si existe algún cliente para agregar que no sea el consumidor final
 QSqlQuery cola;
 if( cola.exec( "SELECT COUNT(id) FROM clientes WHERE id NOT IN ( SELECT id_cliente FROM ctacte ) AND id != 0" ) ) {
     if( cola.next() ) {
         if( cola.record().value(0).toInt() <= 0 ) {
             QMessageBox::information( this, "No hay clientes", "No existen clientes a los que se les pueda agregar cuenta corriente" );
             return;
         }
     } else {
         qDebug( "Error de next en la cola de averiguación de cantidad de clientes para la ctacte." );
         qDebug( cola.lastError().text().toLocal8Bit() );
         qDebug( cola.lastQuery().toLocal8Bit() );
     }
 } else {
     qWarning( "Error de exec en la cola de averiguación de cantidad de clientes para la ctacte." );
     qDebug( cola.lastError().text().toLocal8Bit() );
     qDebug( cola.lastQuery().toLocal8Bit() );
 }
 FormNuevaCtaCte d;
 d.setModelo( qobject_cast<MCuentaCorriente *>( rmodelo ) );
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
 }

 menu->addAction( ActModificarLimite );
 menu->addAction( ActResumen );

}


/*!
    \fn VCuentaCorriente::modificarLimite()
 */
void VCuentaCorriente::modificarLimite()
{
 // Busco el item
 if( vista->selectionModel()->selectedRows().isEmpty() ) {
     QMessageBox::warning( this, "Error", QString::fromUtf8( "Por favor, seleccione una cuenta corriente para cambiarle el límite." ) );
     return;
 }
 QModelIndex indice = vista->selectionModel()->selectedRows().first();
 double limite_anterior = rmodelo->data( rmodelo->index( indice.row(), rmodelo->fieldIndex( "limite" ) ), Qt::EditRole ).toDouble();
 QString id_ctacte = rmodelo->data( rmodelo->index( indice.row(), rmodelo->fieldIndex( "numero_cuenta" ) ), Qt::EditRole ).toString();
 bool ok = false;
 double limite_nuevo = QInputDialog::getDouble( this, "Ingrese el limite maximo", QString::fromUtf8("Límite máximo de credito:"), limite_anterior, 0.0, 1000000.0, 3, &ok );
 if( ok )
 {
  //Verifico que no sean el mismo
  if( limite_anterior == limite_nuevo )
  { return; }
  if( rmodelo->modificarLimite( id_ctacte, limite_nuevo, indice ) ) {
      QMessageBox::information( this, "Correcto", QString::fromUtf8( "El nuevo límite ha sido colocado correctamente" ) );
      vista->update( rmodelo->index( indice.row(), 5 ) );
      return;
  } // El error lo reportara el metodo de existir
 }
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
 {
     QMessageBox::warning( this, "Error", "Elija una cuenta corriente para ver su resumen", QMessageBox::Ok );
     return;
 }
 QModelIndex indice = vista->selectionModel()->selectedRows().first();
 //Obtengo el numero de cuenta
 QString numero_cuenta = indice.model()->data( indice.model()->index( indice.row(), rmodelo->fieldIndex( "numero_cuenta" ) ), Qt::EditRole ).toString();
 FormResumenCtaCte *form = new FormResumenCtaCte( this );
 form->setNumeroCuenta( numero_cuenta );
 emit agregarVentana( form );
}

/*!
 * \fn VCuentaCorriente::mostrarDeudoras( bool estado )
 * Setea para que se vean solo las cuentas deudoras o no.
 */
void VCuentaCorriente::mostrarDeudoras( bool estado ) {
    this->rmodelo->filtrarSoloDeudoras( estado );
    this->rmodelo->select();
}
