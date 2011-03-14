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
#include "vproductos.h"
#include "mproductos.h"
#include "dproductos.h"
#include <QTableView>
#include <QSqlRecord>
#include <QHeaderView>
#include <QAction>
#include "productos.h"
#include "mcategorias.h"
#include "vcategorias.h"
#include "preferencias.h"
#include <QSqlRelationalDelegate>
#include <QSqlQuery>
#include <QSqlField>
#include "dsino.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QSqlError>

VProductos::VProductos(QWidget *parent)
 : EVLista(parent)
{
 this->setObjectName( "listaproductos" );
 this->setWindowTitle( "Lista de Productos");
 this->setWindowIcon( QIcon( ":/imagenes/productos.png" ) );

 modelo = 0;
 rmodelo = new MProductos( vista );

 vista->setModel( rmodelo );
 vista->hideColumn( 0 );
 if( !preferencias::getInstancia()->value( "Preferencias/Productos/categorias" ).toBool() )
 { vista->hideColumn( rmodelo->fieldIndex( "id_categoria" ) ); }
 if( !preferencias::getInstancia()->value( "Preferencias/Productos/descripcion" ).toBool() )
 { vista->hideColumn( rmodelo->fieldIndex( "descripcion" ) ); }
 if( !preferencias::getInstancia()->value( "Preferencias/Productos/marcas" ).toBool() )
 { vista->hideColumn( rmodelo->fieldIndex( "marca" ) ); }
 if( !preferencias::getInstancia()->value( "Preferencias/Productos/stock" ).toBool() )
 { vista->hideColumn( rmodelo->fieldIndex( "stock" ) ); }

 vista->setItemDelegate( new DProductos( vista ) );
 vista->setItemDelegateForColumn( rmodelo->fieldIndex( "habilitado" ), new DSiNo( vista ) );

 rmodelo->select();
 vista->resizeColumnsToContents();
 vista->verticalHeader()->setResizeMode( QHeaderView::ResizeToContents );
 vista->setAlternatingRowColors( true );
 vista->setSortingEnabled( true );

 addAction( ActAgregar );
 addAction( ActEliminar );

 if( preferencias::getInstancia()->value( "Preferencias/Productos/categorias" ).toBool() )
 {
         QAction *ActCategorias = new QAction( "Categorias" , this );
         ActCategorias->setIcon( QIcon( ":/imagenes/categorias.png" ) );
         ActCategorias->setStatusTip( "Ver y administrar las categorias de productos" );
         ActCategorias->setShortcut( QKeySequence( "Ctrl + c" ) );
         connect( ActCategorias, SIGNAL( triggered() ), this, SLOT( verCategorias() ) );

         addAction( ActCategorias );
 }

 addAction( ActCerrar );
}


VProductos::~VProductos()
{
}



/*!
    \fn VProductos::antes_de_insertar(  int row, QSqlRecord &registro )
        Funcion que coloca en el valor predeterminado los valores del registro. Esto evita la falla al insertar el registro.
        @param row Numero de fila a insertar
        @param registro Registro a insertar
 */
void VProductos::antes_de_insertar(  int row, QSqlRecord &registro )
{
 (void)row;
 registro.setValue( "descripcion", "" );
 registro.setValue( "marca", "" );
}


/*!
    \fn VProductos::closeEvent( QCloseEvent * event )
        Metodo llamado cuando se cierra la ventana
 */
void VProductos::closeEvent( QCloseEvent * event )
{
 EVLista::closeEvent( event );
}


/*!
    \fn VProductos::verCategorias()
        Slot llamado para ver la lista de categorias
 */
void VProductos::verCategorias()
{ emit agregarVentana( new VCategorias() ); }


/*!
    \fn VProductos::agregar( bool autoeliminarid )
 */
void VProductos::agregar( bool autoeliminarid )
{
 (void)autoeliminarid;
 // Ver si existe alguna categoria primero
 if( preferencias::getInstancia()->value( "Preferencias/Productos/categorias" ).toBool() )
 {
         qDebug( "Verificando que existan categorias" );
         MCategorias *m = new MCategorias();
         if( m->rowCount() <= 0 )
         {
          qWarning( "Por favor, primero ingrese al menos una categoria de productos" );
          delete m;
          return;
         }
         delete m;
 }
 bool ok;
 QString nombre = QInputDialog::getText(this,tr("Nombre"), tr("Ingrese un nombre para el producto"), QLineEdit::Normal, QString(), &ok);
 if (!ok || nombre.isEmpty() )
 { return; }
 ////////////////////////////////////////////////////////////////////////////////////////////////////
 // Solicito la categoria del producto si esta habilitado
 if( preferencias::getInstancia()->value( "Preferencias/Productos/categorias" ).toBool() )
 {
   //vista->hideColumn( rmodelo->fieldIndex( "id_categoria" ) );
 }
 ////////////////////////////////////////////////////////////////////////////////////////////////////
 // Solicito la descripcion si esta habilitado
 QString descripcion = ""; ok = false;
 if( preferencias::getInstancia()->value( "Preferencias/Productos/descripcion" ).toBool() )
 {
   descripcion = QInputDialog::getText( this, "Descripcion:", "Ingrese una descripcion", QLineEdit::Normal, "", &ok );
   if( !ok ) { return; }
 }
 ////////////////////////////////////////////////////////////////////////////////////////////////////
 // Solicito la marca del producto si esta habilitado
 QString marca = ""; ok = false;
 if( preferencias::getInstancia()->value( "Preferencias/Productos/marcas" ).toBool() )
 {
   marca = QInputDialog::getText( this, "Marca:", "Ingrese una marca", QLineEdit::Normal, marca, &ok );
   if( !ok ) { return; }
 }
 ////////////////////////////////////////////////////////////////////////////////////////////////////
 // Solicito el stock del producto si esta habilitado
 ok = false; double stock = -100.0;
 if( preferencias::getInstancia()->value( "Preferencias/Productos/stock" ).toBool() ) {
    stock = QInputDialog::getDouble( this, "Stock:", "Ingrese el stock inicial", 0.0, 0.0, 2147483647, 3, &ok );
    if( !ok ) { return; }
 }
 ////////////////////////////////////////////////////////////////////////////////////////////////////
 // Solicito el precio de costo del producto
 ok = false;double precio_costo = 0.0;
 precio_costo = QInputDialog::getDouble( this, "Precio:", "Ingrese el precio de costo", 0.0, 0.0, 2147483647, 3, &ok );
 if( !ok ) { return; }
 ////////////////////////////////////////////////////////////////////////////////////////////////////
 // Solicito el precio de venta del producto
 ok = false;double precio_venta = 0.0;
 double recargo = preferencias::getInstancia()->value( "Preferencias/Productos/ganancia", 10.0 ).toDouble();
 precio_venta = precio_costo * ( 1 + ( recargo / 100 ) );
 precio_venta = QInputDialog::getDouble( this, "Precio:", "Ingrese el precio de venta que desea", precio_venta, precio_costo, 2147483647, 3, &ok );
 if( !ok ) { return; }
 ////////////////////////////////////////////////////////////////////////////////////////////////////
 // Agrego el producto
 QSqlRecord rec = rmodelo->record();
 rec.setValue( "nombre", nombre );
 if( descripcion == "" )
 { rec.setNull( "descripcion" ); }
 else
 { rec.setValue( "descripcion", descripcion ); }
 if( marca == "" )
 { rec.setNull( "marca" ); }
 else
 { rec.setValue( "marca", marca ); }
 if( stock == -100.0 ) {
     rec.setNull( "stock" );
 } else {
     rec.setValue( "stock", stock );
 }
 rec.setValue( "precio_costo", precio_costo );
 rec.setValue( "precio_venta", precio_venta );
 rec.setValue( "habilitado", true );
 rec.remove( rmodelo->fieldIndex( "id_categoria" ) );
 rec.remove( rmodelo->fieldIndex( "id" ) );
 /* for( int i = 0; i < rec.count(); i++ ) { qDebug( qPrintable( QString( "campo: %1 - %2" ).arg( i ).arg( rec.fieldName(i) ) ) ); } */
 if( rmodelo->insertRecord( -1, rec ) )
 {
  QMessageBox::information( this, "Correcto", "El producto fue agregado correctamente" );
  return;
 }
 else
 {
  qWarning( "Error al intentar insertar el producto." );
  qDebug( "visorProductos::Salida debug modelo relacional:" );
  qDebug( rmodelo->lastError().text().toLocal8Bit() );
 }
}
