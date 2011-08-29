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
#include "mcompraproducto.h"

FormAgregarCompra::FormAgregarCompra( MCompra *m, QWidget* parent )
: EVentana( parent ), Ui::FormAgregarCompraBase()
{
	setupUi(this);
	setObjectName( "agregar_compra" );
	setWindowTitle( "Agregar nueva compra" );

	this->addAction( new EActCerrar( this ) );
	this->addAction( new EActGuardar( this ) );

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
	QSqlQueryModel *cola = new QSqlQueryModel( this );
	cola->setQuery( "SELECT id, nombre FROM producto WHERE habilitado = 1" );
	CBProducto->setModel( cola );
	CBProducto->setModelColumn( 1 );
	CBProducto->setSizeAdjustPolicy( QComboBox::AdjustToContentsOnFirstShow );
	CBProducto->setEditable( true );
	CBProducto->completer()->setCompletionMode( QCompleter::PopupCompletion );
	CBProducto->setCurrentIndex( -1 );

	mcp = new MProductosTotales( this );
	mcp->calcularTotales( true );
	TVLista->setModel( mcp );
	TVLista->setAlternatingRowColors( true );
	TVLista->setItemDelegate( new DProductosTotales( TVLista ) );
	TVLista->setSelectionBehavior( QAbstractItemView::SelectRows );
	TVLista->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
}

/*!
    \fn FormAgregarCompra::guardar()
 */
void FormAgregarCompra::guardar()
{
 return;
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
 //Inicio una transacción
 QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).transaction();
 //seteo el modelo para que no calcule totales y subtotales
 mcp->calcularTotales( false );
 // veo el id del proveedor
 int id_proveedor = CBProveedor->model()->data( CBProveedor->model()->index( CBProveedor->currentIndex(), 0 ) , Qt::EditRole ).toInt();
 // Genero la compra
 MCompra *compra = new MCompra( this, false );
 if( compra->agregarCompra( DEFecha->date(), id_proveedor ) == false )
 { QSqlDatabase::database().rollback(); return; }
 // Busco el ultimo id de compra
 int id_compra = compra->ultimoId();
 qDebug( qPrintable( QString( "idCompra: %1" ).arg( id_compra ) ) );
 // recorro el modelo y guardo los datos
 MCompraProducto *m = new MCompraProducto( this );
 for( int i= 0; i<mcp->rowCount(); i++ )
 {
  QSqlRecord registro = m->record();
  registro.setValue( "id_compra", id_compra );
  registro.setValue( "id_producto", mcp->data( mcp->index( i, 0 ), Qt::EditRole ) );
  registro.setValue( "precio_compra", mcp->data( mcp->index( i, 1 ), Qt::EditRole ) );
  registro.setValue( "cantidad", mcp->data( mcp->index( i, 2 ), Qt::EditRole ) );
  if( m->insertRecord( -1, registro ) == false )
  {
   qDebug( "Error al insertar Registro" );
  }
  else
  {
   // Actualizo el stock
   int id_producto = mcp->data( mcp->index( i, 0 ), Qt::EditRole ).toInt();
   QSqlQuery cola( QString( "SELECT stock FROM producto WHERE id = %1" ).arg( id_producto ) );
   if( cola.next() )
   {
    double cantidad = cola.record().value(0).toDouble();
    cantidad += mcp->data( mcp->index( i, 2 ), Qt::EditRole ).toDouble();
    if( cola.exec( QString( "UPDATE producto SET stock = %1 WHERE id = %2" ).arg( cantidad ).arg( id_producto ) ) )
    {
     qDebug( "Stock actualizado correctamente" );
    }
    else
    {
     qWarning( "Error al actualizar el stcok" );
     qDebug( qPrintable( cola.lastError().text() ) );
     qDebug( qPrintable( cola.lastQuery() ) );
    }
   }
   else
   {
    qWarning( "Error al intentar buscar el stock del producto" );
    qDebug( qPrintable( cola.lastError().text() ) );
    qDebug( qPrintable( cola.lastQuery() ) );
   }
  }
 }
 m->submit();
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
 mcp->insertRow( -1 );
 QModelIndex indice = mcp->index( mcp->rowCount()-2 , 0 );
 mcp->setData( indice, CBProducto->model()->data( CBProducto->model()->index( CBProducto->currentIndex(), 0 ) , Qt::EditRole ).toInt(), Qt::EditRole );
 indice = mcp->index( mcp->rowCount()-2 , 1 );
 TVLista->setCurrentIndex( indice );
 TVLista->edit( indice );
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
