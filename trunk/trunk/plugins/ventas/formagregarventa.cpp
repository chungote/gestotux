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
#include "formagregarventa.h"
#include "mproductostotales.h"
#include "dproductostotales.h"
#include "emcliente.h"
#include <QTableView>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QCompleter>
#include "eactcerrar.h"
#include "eactguardar.h"
#include "mventa.h"
#include "mventaproducto.h"
#include "mlistaprecio.h"

FormAgregarVenta::FormAgregarVenta ( QWidget* parent, Qt::WFlags fl )
: EVentana ( parent, fl ), Ui::FormAgregarVentaBase()
{
	setupUi( this );
	this->setObjectName( "formagregarcompra" );
	this->setWindowTitle( "Agregar Venta" );
	this->setWindowIcon( QIcon(":/imagenes/venta.png" ) );

	PBAgregarProducto->setIcon( QIcon( ":/imagenes/add.png" ) );
	PBAgregarProducto->setText( "Agregar Producto" );
	PBEliminarProducto->setText( "Eliminar Producto" );
	PBEliminarProducto->setIcon( QIcon( ":/imagenes/eliminar.png" ) );

	connect( PBAgregarProducto, SIGNAL( clicked() ), this, SLOT( agregarProducto() ) );
	connect( PBEliminarProducto, SIGNAL( clicked() ), this, SLOT( eliminarProducto() ) );

	// Inicio los modelos
	CBCliente->setModel( new EMCliente( CBCliente ) );
	CBCliente->setModelColumn( 1 );

	// Lista de Precios
	CBListaPrecio->setModel( new MListaPrecio( CBListaPrecio ) );
	CBListaPrecio->setModelColumn( 1 );
	qobject_cast<QSqlTableModel *>(CBListaPrecio->model())->select();

	// Rellenar los items de productos
	QSqlQuery cola( "SELECT nombre, id FROM producto WHERE habilitado = 1" );
	while( cola.next() )
	{  CBProducto->insertItem( cola.record().value( "id" ).toInt(), cola.record().value("nombre").toString(), cola.record().value( "id" ) ); }
	CBProducto->setSizeAdjustPolicy( QComboBox::AdjustToContentsOnFirstShow );
	CBProducto->setEditable( true );
	CBProducto->completer()->setCompletionMode( QCompleter::PopupCompletion );
	CBProducto->setCurrentIndex( -1 );

        DEFecha->setMaximumDate( QDate::currentDate() );
        DEFecha->setDate( QDate::currentDate() );

	// Modelo del tableview
	mcp = new MProductosTotales( TVProductos );
	mcp->calcularTotales( true );
	mcp->buscarPrecios( true );
	TVProductos->setModel( mcp );
	TVProductos->setItemDelegate( new DProductosTotales( TVProductos ) );
	TVProductos->setAlternatingRowColors( true );
	TVProductos->setSelectionBehavior( QAbstractItemView::SelectRows );
	TVProductos->horizontalHeader()->setResizeMode( QHeaderView::Stretch );

	this->addAction( new EActCerrar( this ) );
	this->addAction( new EActGuardar( this ) );

	connect( CBListaPrecio, SIGNAL( currentIndexChanged( int ) ), this, SLOT( cambioListaPrecio( int ) ) );
	cambioListaPrecio( CBListaPrecio->currentIndex() );
}

FormAgregarVenta::~FormAgregarVenta()
{
}


/*!
    \fn FormAgregarVenta::agregarProducto()
 */
void FormAgregarVenta::agregarProducto()
{
 mcp->insertRow( -1 );
 QModelIndex indice = mcp->index( mcp->rowCount()-2 , 0 );
 mcp->setData( indice, CBProducto->currentIndex(), Qt::EditRole );
 indice = mcp->index( mcp->rowCount()-2 , 1 );
 TVProductos->setCurrentIndex( indice );
 TVProductos->edit( indice );
}


/*!
    \fn FormAgregarVenta::eliminarProducto()
 */
void FormAgregarVenta::eliminarProducto()
{
 //Preguntar al usuario si esta seguro
 QItemSelectionModel *selectionModel = TVProductos->selectionModel();
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
		{
			TVProductos->model()->removeRow( indice.row() );
		}
	}
 }
 return;
}


/*!
    \fn FormAgregarVenta::guardar()
 */
void FormAgregarVenta::guardar()
{
 if( CBCliente->currentIndex() == -1 )
 {
  QMessageBox::warning( this, "Faltan Datos" , "Por favor, ingrese un cliente para esta venta" );
  return;
 }
 if( CBListaPrecio->currentIndex() == -1 )
 {
  QMessageBox::warning( this, "Faltan Datos" , "Por favor, ingrese una lista de precio para esta venta" );
  return;
 }
 if( !DEFecha->date().isValid() )
 {
  QMessageBox::warning( this, "Faltan Datos" , "Por favor, ingrese una fecha valida para esta venta" );
  return;
 }
 mcp->calcularTotales( false );
 if( mcp->rowCount() < 1 )
 {
  QMessageBox::warning( this, "Faltan Datos" , "Por favor, ingrese una cantidad de productos vendidos distinta de cero para esta venta" );
  mcp->calcularTotales( true );
  return;
 }
 //Inicio una transacción
 QSqlDatabase::database().transaction();
 //seteo el modelo para que no calcule totales y subtotales
 mcp->calcularTotales( false );
 // veo el id del proveedor
 int id_cliente = CBCliente->model()->data( CBCliente->model()->index( CBCliente->currentIndex(), 0 ) , Qt::EditRole ).toInt();
 int id_lista_precio = CBListaPrecio->model()->data( CBListaPrecio->model()->index( CBListaPrecio->currentIndex(), 0 ) , Qt::EditRole ).toInt();
 //int id_forma_pago = CBFormaPago->model()->data( CBFormaPago->model()->index( CBFormaPago->currentIndex(), 0 ) , Qt::EditRole ).toInt();
  int id_forma_pago = -1;
 QString num_comprobante = LENumComp->text();
 // Genero la compra
 MVenta *compra = new MVenta( this, false );
 if( compra->agregarVenta( DEFecha->date(), id_cliente, id_lista_precio, id_forma_pago, num_comprobante ) == false )
 { QSqlDatabase::database().rollback(); return; }
 // Busco el ultimo id de compra
 int id_venta = compra->ultimoId();
 // recorro el modelo y guardo los datos
 MVentaProducto *m = new MVentaProducto( this );
 for( int i= 0; i<mcp->rowCount(); i++ )
 {
  QSqlRecord registro = m->record();
  registro.setValue( "id_venta", id_venta );
  registro.setValue( "id_producto", mcp->data( mcp->index( i, 0 ), Qt::EditRole ) );
  registro.setValue( "precio_venta", mcp->data( mcp->index( i, 1 ), Qt::EditRole ) );
  registro.setValue( "cantidad", mcp->data( mcp->index( i, 2 ), Qt::EditRole ) );
  if( m->insertRecord( -1, registro ) == false ) {
   qDebug( "Error al insertar Registro" );
  }
  else
  {
   // Disminuyo el stock
   int id_producto = mcp->data( mcp->index( i, 0 ), Qt::EditRole ).toInt();
   QSqlQuery cola( QString( "SELECT stock FROM producto WHERE id = %1" ).arg( id_producto ) );
   if( cola.next() )
   {
    double cantidad = cola.record().value( 0 ).toDouble();
    cantidad -= mcp->data( mcp->index( i, 2 ), Qt::EditRole ).toDouble();
    if( cola.exec( QString( "UPDATE producto SET stock = %1 WHERE id = %2" ).arg( cantidad ).arg( id_producto ) ) ) {
	qDebug( "Stock Actualizado correctamente" );
    }
    else
    {
      qWarning( "Error al actualizar el stock" );
    }
   }
   else
   {
    qWarning( "Error al bsucar el stock" );
   }
  }
 }
 m->submit();
 // listo
  if( QSqlDatabase::database().commit() ) {
   QMessageBox::information( this, "Correcto" , "La venta se ha registrado correctamente" );
   this->close();
   return;

  } else {
   QMessageBox::information( this, "Incorrecto" , "La venta no se pudo guardar correctamente" );
   return;
  }
}


/*!
    \fn FormAgregarVenta::cambioListaPrecio( int id_combo )
 */
void FormAgregarVenta::cambioListaPrecio( int id_combo )
{
 qDebug( qPrintable( QString( "Cambiado id lista precio: %1" ).arg( id_combo ) ) );
 mcp->setearListaPrecio( CBListaPrecio->model()->data( CBListaPrecio->model()->index(CBListaPrecio->currentIndex(), 0 ) , Qt::EditRole ).toInt() );
}
