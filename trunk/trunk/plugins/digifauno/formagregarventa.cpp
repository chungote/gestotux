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
#include "formagregarventa.h"
#include "mdueno.h"
#include "mventa.h"
#include "mventaproducto.h"
#include "preferencias.h"
#include "mproductos.h"
#include "dventacompra.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QLCDNumber>
#include <QLabel>
#include <QGroupBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QTableView>
#include <QSpacerItem>
#include <QComboBox>
#include <QSplitter>
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
#include <QItemSelectionModel>
#include <QSqlQuery>
#include <QHeaderView>

//#include "edsbprecio.h"

FormAgregarVenta::FormAgregarVenta(QWidget *parent)
 : EVentana( parent )
{
    setWindowIcon( QIcon( ":/imagenes/add.png" ) );
    setWindowTitle( "Agregar Venta" );
    vboxLayout = new QVBoxLayout(this);
    LTitulo = new QLabel(this);
    LTitulo->setTextFormat(Qt::RichText);
    LTitulo->setAlignment(Qt::AlignCenter);
    LTitulo->setOpenExternalLinks(false);
    LTitulo->setMaximumHeight( 200 );

   /* EDSBPrecio *test = new EDSBPrecio( this );
    vboxLayout->addWidget( test );*/

    vboxLayout->addWidget(LTitulo);

    GBProductos = new QGroupBox(this);
    GBProductos->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    vboxLayout1 = new QVBoxLayout(GBProductos);
    splitter = new QSplitter(GBProductos);
    splitter->setOrientation(Qt::Horizontal);
    splitter->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    TVProductos = new QTableView(splitter);
    TVProductos->setSelectionBehavior(QAbstractItemView::SelectItems);
    TVProductos->setTextElideMode(Qt::ElideNone);
    splitter->addWidget(TVProductos);
    widget = new QWidget( splitter );
    vboxLayout2 = new QVBoxLayout(widget);
    vboxLayout2->setContentsMargins( 0, 0, 0, 0 );
    PBAgregar = new QPushButton( widget );

    vboxLayout2->addWidget(PBAgregar);

    PBBorrar = new QPushButton(widget);

    vboxLayout2->addWidget( PBBorrar );

    spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout2->addItem(spacerItem);

    splitter->addWidget(widget);

    vboxLayout1->addWidget(splitter);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setContentsMargins(0, 0, 0, 0);
    label_2 = new QLabel(GBProductos);

    hboxLayout1->addWidget(label_2);

    LcdNCantidad = new QLCDNumber(GBProductos);
    LcdNCantidad->setFrameShape(QFrame::NoFrame);
    LcdNCantidad->setFrameShadow(QFrame::Sunken);
    LcdNCantidad->setLineWidth(3);
    LcdNCantidad->setMidLineWidth(1);
    LcdNCantidad->setNumDigits(3);
    LcdNCantidad->setSegmentStyle(QLCDNumber::Filled);

    hboxLayout1->addWidget(LcdNCantidad);

    spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem1);

    label_3 = new QLabel(GBProductos);

    hboxLayout1->addWidget(label_3);

    LETotal = new QLineEdit(GBProductos);
    LETotal->setMaximumSize(QSize(101, 16777215));
    LETotal->setMouseTracking(false);
    LETotal->setAcceptDrops(false);
    LETotal->setAutoFillBackground(true);
    LETotal->setAlignment(Qt::AlignRight);
    LETotal->setReadOnly(true);

    hboxLayout1->addWidget(LETotal);


    vboxLayout1->addLayout(hboxLayout1);


    vboxLayout->addWidget(GBProductos);

    line = new QFrame(this);
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);

    vboxLayout->addWidget(line);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setContentsMargins(0, 0, 0, 0);


    spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout2->addItem(spacerItem2);

    PBAceptar = new QPushButton(this);

    hboxLayout2->addWidget(PBAceptar);

    PBCancelar = new QPushButton(this);

    hboxLayout2->addWidget(PBCancelar);


    vboxLayout->addLayout(hboxLayout2);

    // Textos e imagenes
    LTitulo->setText( "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
                         "p, li { white-space: pre-wrap; }\n"
                         "</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
                         "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600;\">Agregar Venta</span></p></body></html>" );
    GBProductos->setTitle( "Productos");
    PBAgregar->setText( "&Agregar" );
    PBBorrar->setText( "&Borrar" );
    label_2->setText( "Cantidad de productos:" );
    label_3->setText( "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
			   "p, li { white-space: pre-wrap; }\n"
 			   "</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal; text-decoration:none;\">\n"
			   "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Total:</span></p></body></html>" );
    LETotal->setInputMask(  "$ 99999.99; " );
    PBAceptar->setText(  "Ace&ptar" );
    PBCancelar->setText(  "Cancela&r" );
    // Impongo el modelo de venta_producto
    modeloVentaProducto = new MVentaProducto( this, true );
    modeloVentaProducto->setEditStrategy( QSqlTableModel::OnManualSubmit );
    TVProductos->setModel( modeloVentaProducto );
    TVProductos->hideColumn( 0 );
    TVProductos->hideColumn( 1 );
    TVProductos->setItemDelegate( new DVentaCompra( TVProductos ) );
    TVProductos->resizeColumnToContents( 2 );
    TVProductos->resizeColumnToContents( 5 );
    TVProductos->horizontalHeader()->resizeSection( 2, 300 );
    // Conecto los slots
    ///@todo Cambiar esto por acciones
    connect( PBCancelar , SIGNAL( clicked()       ), this, SLOT( cerrar()                   ) );
    connect( PBAceptar  , SIGNAL( clicked()       ), this, SLOT( guardar()                  ) );
    connect( PBAgregar  , SIGNAL( clicked()       ), this, SLOT( agregar()                  ) );
    connect( PBBorrar   , SIGNAL( clicked()       ), this, SLOT( borrar()                   ) );
    connect( modeloVentaProducto, SIGNAL( dataChanged( const QModelIndex &, const QModelIndex & ) ), this, SLOT( buscarPrecio( const QModelIndex &, const QModelIndex & ) ) );
    // Imagenes
    PBAceptar->setIcon(  QIcon( ":/imagenes/guardar.png"   ) );
    PBCancelar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
    PBAgregar->setIcon(  QIcon( ":/imagenes/add.png"       ) );
    PBBorrar->setIcon(   QIcon( ":/imagenes/eliminar.png"  ) );
    // Accesos de teclas
    PBAceptar->setShortcut( QKeySequence( "Ctrl+p" ) );
    PBCancelar->setShortcut( QKeySequence( "Ctrl+r" ) );
    PBAgregar->setShortcut( QKeySequence( "Ctrl+a" ) );
    PBBorrar->setShortcut( QKeySequence( "Ctrl+b" ) );
}


FormAgregarVenta::~FormAgregarVenta()
{
}

/*!
    \fn FormAgregarVenta::closeEvent ( QCloseEvent * event )
    Antes de cerrase a si misma guarda las preferencias de las ventanas en la configuracion para que queden del mismo tama�o al abrirse nuevamente
	@param event Evento a procesar
 */
void FormAgregarVenta::closeEvent( QCloseEvent * event )
{
 if ( !objectName().isEmpty() )
 {
	preferencias *p = preferencias::getInstancia();
	p->beginGroup( "Ventanas" );
	p->beginGroup( objectName() );
	p->setValue( "dimensiones", splitter->saveState() );
	p->endGroup();
	p->endGroup();
// 	qDebug( "Guardo tama�o de splitter" );
 }
 EVentana::closeEvent( event );
}



/*!
    \fn FormAgregarVenta::agregar()
 */
void FormAgregarVenta::agregar()
{
 QSqlRecord registro = modeloVentaProducto->record();
 registro.remove( 0 );
 registro.setValue( "cantidad", 1 );
 if( !modeloVentaProducto->insertRecord( -1, registro ) )
 {
  qDebug( "Error al insertar el registro" );
  qDebug( QString( "Detalles: tipo: %1, errno: %2, descripcion: %3" ).arg( modeloVentaProducto->lastError().type() ).arg( modeloVentaProducto->lastError().number() ).arg( modeloVentaProducto->lastError().text() ).toLocal8Bit() );
 }
 else
 {
//   qDebug( "Registro insertado Correctamente" );
  TVProductos->edit( modeloVentaProducto->index( modeloVentaProducto->get_ultima_row(), 2 ) );
 }
}


/*!
    \fn FormAgregarVenta::borrar()
 */
void FormAgregarVenta::borrar()
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
 //Hacer dialogo de confirmacion..
 int ret;
 ret = QMessageBox::warning( this, "Esta seguro?",
                   QString("Esta seguro de eliminar %1 item?").arg( indices.size() ),
                   "Si", "No" );
 if ( ret == 0 )
 {
	QModelIndex indice;
	foreach( indice, indices )
	{
		if( indice.isValid() )
		{
			modeloVentaProducto->removeRow( indice.row() );
			qDebug( QString("Eliminando fila  %1" ).arg( indice.row() ).toLocal8Bit() );
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
//  qDebug( "Iniciando guardado" );
 // Creo el registro de venta
 MVenta *modeloVenta = new MVenta();
 modeloVenta->setEditStrategy( QSqlTableModel::OnManualSubmit );
 QSqlRecord recVenta = modeloVenta->record();
 recVenta.setValue( "fecha", QVariant::fromValue( QDate::currentDate() ) );
 if( !modeloVenta->insertRecord( -1, recVenta ) )
 {
    qDebug( "Error al insertar el registro" );
    qDebug( QString( "Detalles: tipo: %1, errno: %2, descripcion: %3" ).arg( modeloVentaProducto->lastError().type() ).arg( modeloVentaProducto->lastError().number() ).arg( modeloVentaProducto->lastError().text() ).toLocal8Bit() );
    QMessageBox::warning( this, "No se pudo guardar el registro",
                    "Ha ocurrido un error al guardar los datos de esta venta. No se guardo ningun dato. Error( 100 )",
                    QMessageBox::Ok );
    close();
    return;
 }
 else
 {
//   qDebug( "Registro de venta agregado correctamente" );
 }
 if( !modeloVenta->submitAll() )
 {
  qDebug( "Error al guardar datos de venta" );
  qDebug( QString( "Detalles: tipo: %1, errno: %2, descripcion: %3" ).arg( modeloVenta->lastError().type() ).arg( modeloVenta->lastError().number() ).arg( modeloVenta->lastError().text() ).toLocal8Bit() );
 }
 delete modeloVenta;
 // Obtengo el ultimo id que se genero
 QSqlQuery cola( "SELECT seq FROM sqlite_sequence WHERE name = 'ventas'" );
 if( !cola.next() )
 {
  qDebug( "Error al obtener el numero de sequencia de venta" );
  return;
 }
 // Actualizo los datos de los productos
 for( int f=0; f< modeloVentaProducto->rowCount(); f++ )
 {
  QModelIndex indice = modeloVentaProducto->index( f, 1 );
  if( modeloVentaProducto->isDirty( indice ) )
  {
	if( !modeloVentaProducto->setData( indice, cola.record().value( "seq" ) ) )
	{
		qDebug( "Error al actualizar el indice de venta" );
		qDebug( QString( "Detalles: tipo: %1, errno: %2, descripcion: %3" ).arg( modeloVentaProducto->lastError().type() ).arg( modeloVentaProducto->lastError().number() ).arg( modeloVentaProducto->lastError().text() ).toLocal8Bit() );
	}
  }
 }
 if( !modeloVentaProducto->submitAll() )
 {
  qDebug( "Error al guardar los datos de los productos vendidos" );
  qDebug( QString( "Detalles: tipo: %1, errno: %2, descripcion: %3" ).arg( modeloVentaProducto->lastError().type() ).arg( modeloVentaProducto->lastError().number() ).arg( modeloVentaProducto->lastError().text() ).toLocal8Bit() );
  return;
 }
 else
 {
//   qDebug( "Datos de productos vendidos guardados correctamente" );
  delete modeloVentaProducto;
  //////////////////////////////////////////////////////////////////////
  QMessageBox::warning( this, "Guardado Satisfactoriamente",
                    "Los datos se han guardado satisfactoriamente",
                    QMessageBox::Ok );
   close();
 }

}

/*!
    \fn FormAgregarVenta::buscarPrecio(const QModelIndex & topLeft, const QModelIndex & bottomRight )
 */
void FormAgregarVenta::buscarPrecio(const QModelIndex & topLeft, const QModelIndex & bottomRight )
{
  LETotal->setText( QString::number( modeloVentaProducto->total() ) );
  TVProductos->resizeColumnsToContents();
  //qDebug( QString( "Posiciones: topleft: %1,%2; bottomright: %3.%4" ).arg( topLeft.row() ).arg( topLeft.column() ).arg( bottomRight.row() ).arg( bottomRight.column() ).toLocal8Bit() );
  if( topLeft.column() == 2 )
  {
//    //qDebug( "Buscando Precio" );
   //Busco el precio
   QModelIndex indice1 = modeloVentaProducto->index( bottomRight.row(), topLeft.column() );
   //qDebug( QString( "Indice modeloventaproducto: %1,%2" ).arg( indice1.row() ).arg( indice1.column() ).toLocal8Bit() );
   QVariant IdProd = modeloVentaProducto->data( indice1, 2 );
   //qDebug( QString( "Id de producto: %1" ).arg( IdProd.toInt() ).toLocal8Bit() );
   QSqlQuery cola( QString( "SELECT precio_venta FROM producto WHERE id = %1 " ).arg( IdProd.toInt() ) );
   if( cola.next() )
   {
     QVariant precio = cola.record().value( "precio_venta" );
     //lo pongo en el lugar correspondiente
     TVProductos->model()->setData( TVProductos->model()->index( bottomRight.row(), 3 ), precio );
     return;
   }
   else
   {
    qDebug( "Error al obtener el precio del producto solicitado" );
    return;
   }
  }
}


/*!
    \fn FormAgregarVenta::cerrar()
 */
void FormAgregarVenta::cerrar()
{
  modeloVentaProducto->revertAll();
  close();
}
