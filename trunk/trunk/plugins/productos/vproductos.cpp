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
#include "dsino.h"
#include <QMessageBox>
#include "formagregarproducto.h"

VProductos::VProductos(QWidget *parent)
 : EVLista(parent)
{
 this->setObjectName( "listaproductos" );
 this->setWindowTitle( "Lista de Productos");
 this->setWindowIcon( QIcon( ":/imagenes/productos.png" ) );

 modelo = 0;
 rmodelo = new MProductos( vista );

 vista->setModel( rmodelo );

 vista->setItemDelegateForColumn( rmodelo->fieldIndex( "habilitado" ), new DSiNo( vista ) );

 vista->hideColumn( 0 );
 if( !preferencias::getInstancia()->value( "Preferencias/Productos/categorias" ).toBool() )
 { vista->hideColumn( rmodelo->fieldIndex( "id_categoria" ) ); }
 if( !preferencias::getInstancia()->value( "Preferencias/Productos/descripcion" ).toBool() )
 { vista->hideColumn( rmodelo->fieldIndex( "descripcion" ) ); }
 if( !preferencias::getInstancia()->value( "Preferencias/Productos/marcas" ).toBool() )
 { vista->hideColumn( rmodelo->fieldIndex( "marca" ) ); }
 if( !preferencias::getInstancia()->value( "Preferencias/Productos/stock" ).toBool() )
 { vista->hideColumn( rmodelo->fieldIndex( "stock" ) ); }
 if( !preferencias::getInstancia()->value( "Preferencias/Productos/modelo" ).toBool() )
 { vista->hideColumn( rmodelo->fieldIndex( "modelo" ) ); }

 vista->resizeColumnsToContents();
 vista->verticalHeader()->setResizeMode( QHeaderView::ResizeToContents );
 vista->setAlternatingRowColors( true );
 vista->setSortingEnabled( true );

 addAction( ActAgregar );
 addAction( ActModificar );
 //addAction( ActEliminar );

 if( preferencias::getInstancia()->value( "Preferencias/Productos/categorias" ).toBool() )
 {
         QAction *ActCategorias = new QAction( "Categorias" , this );
         ActCategorias->setIcon( QIcon( ":/imagenes/categorias.png" ) );
         ActCategorias->setStatusTip( "Ver y administrar las categorias de productos" );
         ActCategorias->setShortcut( QKeySequence( "Ctrl + c" ) );
         connect( ActCategorias, SIGNAL( triggered() ), this, SLOT( verCategorias() ) );

         addAction( ActCategorias );
 }

 QAction *ActListadoVenta = new QAction( this );
 ActListadoVenta->setText( "Listado de venta" );
 ActListadoVenta->setIcon( QIcon( ":/imagenes/listado.png" ) );
 ActListadoVenta->setStatusTip( "Muestra el listado de productos con su precio de venta" );
 ActListadoVenta->setIcon( QIcon( ":/imagenes/listaventa.png" ) );
 connect( ActListadoVenta, SIGNAL( triggered() ), this, SLOT( listaVenta() ) );

 addAction( ActListadoVenta );
 addAction( ActVerTodos );
 addAction( ActCerrar );
}

/*!
    \fn VProductos::antes_de_insertar(  int row, QSqlRecord &registro )
        Funcion que coloca en el valor predeterminado los valores del registro. Esto evita la falla al insertar el registro.
        @param row Numero de fila a insertar
        @param registro Registro a insertar
 */
void VProductos::antes_de_insertar(  int /* row */, QSqlRecord &registro )
{
 registro.setValue( "descripcion", "" );
 registro.setValue( "marca", "" );
 registro.setValue( "modelo", "" );
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
void VProductos::agregar( bool /*autoeliminarid*/ )
{
 // Ver si existe alguna categoria primero
 if( preferencias::getInstancia()->value( "Preferencias/Productos/categorias" ).toBool() )
 {
         qDebug( "Verificando que existan categorias" );
         MCategorias *m = new MCategorias();
         int cantidad_categorias = m->rowCount();
         delete m;
         if( cantidad_categorias <= 0 )
         {
          qWarning( "Por favor, primero ingrese al menos una categoria de productos" );
          return;
         }
 }
 // Muestro el formulario
 FormAgregarProducto *f = new FormAgregarProducto();
 connect( f, SIGNAL( accepted() ), this, SLOT( actualizar() ) );
 emit agregarVentana( f );
}

#include <QMessageBox>
#include "EReporte.h"
/*!
 * \fn VProductos::listaVenta()
 * Muestra el listado de productos con sus codigos y precio de venta
 */
void VProductos::listaVenta()
{
    if( this->rmodelo->rowCount() <= 0 ) {
        QMessageBox::information( this, "Error", "No hay ningun producto declarado como para  dar un listado." );
        return;
    }
    EReporte *rep = new EReporte( 0 );
    rep->especial( "ListadoProductosPrecio", ParameterList() );
    rep->hacer();
    delete rep;
}

void VProductos::actualizar() {
    this->rmodelo->select();
}

#include "formmodificarproducto.h"
void VProductos::modificar()
{
    // busco el que esta seleccionado
    QItemSelectionModel *selectionModel = vista->selectionModel();
    QModelIndexList indices = selectionModel->selectedRows();
    if( indices.size() < 1 )
    {
      QMessageBox::warning( this, "Seleccione un item",
                      "Por favor, seleccione un item para modificar",
                      QMessageBox::Ok );
      return;
    }
    int fila = indices.first().row();
    FormModificarProducto *f = new FormModificarProducto( qobject_cast<MProductos *>( this->rmodelo ) );
    f->setearProducto( fila );
    connect( f, SIGNAL( accepted() ), this, SLOT( actualizar() ) );
    f->exec();
}
