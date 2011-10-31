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

#include "../proveedor/mproveedor.h"
#include "eactcerrar.h"
#include "eactguardar.h"
#include "mcompra.h"
#include "mproductostotales.h"
#include "dproductostotales.h"
#include <QMessageBox>
#include <QTableView>
#include <QCompleter>
#include <QDate>
#include <QtSql>
#include <QLineEdit>
#include "mcompraproducto.h"

FormAgregarCompra::FormAgregarCompra( MCompra *m, QWidget* parent )
: EVentana( parent ), Ui::FormAgregarCompraBase()
{
	setupUi(this);
	setObjectName( "agregar_compra" );
	setWindowTitle( "Agregar nueva compra" );

        if( m == 0 ) {
            this->modelo = new MCompra( this, false );
        } else {  this->modelo = m; }

        modeloProveedor = new MProveedor( CBProveedor );
        CBProveedor->setModel( modeloProveedor );
        CBProveedor->setModelColumn( 1 );
        modeloProveedor->select();

        DEFecha->setMaximumDate( QDate::currentDate() );
        DEFecha->setDate( QDate::currentDate() );

	PBAgregarProducto->setIcon( QIcon( ":/imagenes/add.png" ) );
	PBEliminarProducto->setIcon( QIcon( ":/imagenes/eliminar.png" ) );

	connect( PBAgregarProducto, SIGNAL( clicked() ), this, SLOT( agregarProducto() ) );
	connect( PBEliminarProducto, SIGNAL( clicked() ), this, SLOT( eliminarProducto() ) );

        // Rellenar los items de productos
        connect( CBProducto, SIGNAL( agregarProducto() ), PBAgregarProducto, SIGNAL( clicked() ) );

        mcp = new MProductosTotales( this, CBProducto->listadoProductos() );
	mcp->calcularTotales( true );
        mcp->buscarPrecios( false );
        TVLista->setModel( mcp );
	TVLista->setAlternatingRowColors( true );
        TVLista->setItemDelegateForColumn( 1, new DProductosTotales( TVLista ) );
	TVLista->setSelectionBehavior( QAbstractItemView::SelectRows );
	TVLista->horizontalHeader()->setResizeMode( QHeaderView::Stretch );

        this->addAction( new EActGuardar( this ) );
        this->addAction( new EActCerrar( this ) );

}

#include <QInputDialog>
#include "mproductos.h"
#include "formagregarproducto.h"
/*!
    \fn FormAgregarCompra::guardar()
 */
void FormAgregarCompra::guardar()
{
 if( CBProveedor->currentIndex() == -1 )
 {
  QMessageBox::warning( this, "Faltan Datos" , "Por favor, ingrese un proveedor para esta compra" );
  return;
 }
 if( !DEFecha->date().isValid() )
 {
  QMessageBox::warning( this, "Faltan Datos" , "Por favor, ingrese una fecha valida para esta compra" );
  return;
 }
 mcp->calcularTotales( false );
 if( mcp->rowCount() < 1 )
 {
  QMessageBox::warning( this, "Faltan Datos" , "Por favor, ingrese productos para esta compra" );
  mcp->calcularTotales( true );
  return;
 }
 //return;
 //Inicio una transacción
 QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).transaction();
 //seteo el modelo para que no calcule totales y subtotales
 mcp->calcularTotales( false );
 // veo el id del proveedor
 int id_proveedor = CBProveedor->model()->data( CBProveedor->model()->index( CBProveedor->currentIndex(), 0 ) , Qt::EditRole ).toInt();
 // Genero la compra
 MCompra *compra = new MCompra( this, false );
 if( compra->agregarCompra( DEFecha->date(), id_proveedor, mcp->total() ) == false )
 {
     QSqlDatabase::database().rollback();
     return;
 }
 // Busco el ultimo id de compra
 int id_compra = compra->ultimoId();
 //qDebug( qPrintable( QString( "idCompra: %1" ).arg( id_compra ) ) );
 // recorro el modelo y guardo los datos
 MCompraProducto *m = new MCompraProducto( this );
 bool siATodo = false;
 bool noATodo = false;
 for( int i= 0; i<mcp->rowCount(); i++ )
 {
     if( mcp->data( mcp->index( i, 1 ), Qt::EditRole ).toInt() <= -1 ) {
         // El producto no existe
         // Pregunto si lo quiere agregar
         int ret = -1;
         if( noATodo )
             // No quiere agregar ningun producto, siempre salto al siguiente
             continue;
         if( siATodo )
                 ret = QMessageBox::Yes;
            else
                 ret = QMessageBox::question( this, "¿Agregar?", "Desea agregar el producto?", QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No | QMessageBox::NoToAll, QMessageBox::Yes );
         switch( ret ) {
            case QMessageBox::YesToAll:
            {
                siATodo = true;
                // No pongo break para que agrege el producto
            }
            case QMessageBox::Yes:
            {
                 // Agrego el producto
                qWarning( "todavía no implementado" );
                continue;
                FormAgregarProducto *f = new FormAgregarProducto();
                f->setearNombre( mcp->data( mcp->index( i, 1 ), Qt::DisplayRole ).toString() );
                f->setearStockInicial(mcp->data( mcp->index( i, 0 ), Qt::EditRole ).toInt() );
                f->setearPrecioCosto( mcp->data( mcp->index( i, 2 ), Qt::EditRole ).toDouble() );
                emit agregarVentana( f );
                break;
            }
            case QMessageBox::NoToAll:
            {
                noATodo = true;
            }
            case QMessageBox::No:
            default:
            {
                // Desconocido, salteo al siguiente producto
                continue;
                break;
            }

         }
     }
     if( !m->agregarCompraProducto( id_compra,
                                   mcp->data( mcp->index( i, 1 ), Qt::EditRole ).toInt(), // id_producto
                                   mcp->data( mcp->index( i, 2 ), Qt::EditRole ).toDouble(), // precio compra
                                   mcp->data( mcp->index( i, 0 ), Qt::EditRole ).toInt() ) ) { // cantidad

         qWarning( "No se pudo agregar el producto a la compra" );
         QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback();
         return;
     }

  } // fin del for
  // Si llegue hasta aca sin problema, hago el submit
  // listo
  if( QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).commit() )
  {
   QMessageBox::information( this, "Correcto" , "La compra se ha registrado correctamente" );
   this->close();
   return;
  }
  else
  {
   QMessageBox::information( this, "Incorrecto" , "La compra no se pudo guardar correctamente" );
   return;
  }
}


/*!
    \fn FormAgregarCompra::agregarProducto()
 */
void FormAgregarCompra::agregarProducto()
{
 mcp->agregarNuevoProducto( SBCant->value(), CBProducto->idActual() );
 SBCant->setValue( 1.0 );
 CBProducto->setCurrentIndex( -1 );
 SBCant->setFocus();
}


/*!
    \fn FormAgregarCompra::eliminarProducto()
 */
void FormAgregarCompra::eliminarProducto()
{
 //Preguntar al usuario si esta seguro
 QItemSelectionModel *selectionModel = TVLista->selectionModel();
 QModelIndexList indices = selectionModel->selectedIndexes();
 if( indices.size() < 1 )
 {
   QMessageBox::warning( this, "Seleccione un item",
                   "Por favor, seleccione un item para eliminar",
                   QMessageBox::Ok );
   return;
 }
 // cuento las filas distintas
 QModelIndex indice;
 int ultimo = -1;
 foreach( indice, indices )
 {
  if( indice.row() == ultimo )
  {
   indices.removeOne( indice );
  }
  else
  {
   ultimo = indice.row();
  }
 }
 //Hacer dialogo de confirmacion..
 int ret;
 ret = QMessageBox::warning( this, "Esta seguro?",
                   QString( "Esta seguro de eliminar %1 item?").arg( indices.size() ),
                   "Si", "No" );
 if ( ret == 0 )
 {
	QModelIndex indice;
	foreach( indice, indices )
	{
		if( indice.isValid() )
		{  mcp->removeRow( indice.row() ); }
	}
 }
 return;
}
