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
#include "vrecibos.h"
#include "mrecibo.h"
#include "hicomp.h"
#include "formmodificarrecibo.h"
#include "formagregarrecibo.h"
#include "drecibo.h"
#include "visorrecibo.h"
#include "filtroclientes.h"
#include <QTableView>
#include <QAction>
#include <QToolBar>
#include <QHeaderView>
#include <QGridLayout>
#include <QMessageBox>
#include <QModelIndex>
#include <QPrinter>
#include <QPrintDialog>
#include <QStackedWidget>
#include <QToolBar>
#include <QMainWindow>

VRecibos::VRecibos( QWidget *parent )
 : QWidget( parent )
{
 setObjectName( "Recibos Emitidos" );
 this->setAttribute( Qt::WA_DeleteOnClose );

 modelo = new MRecibo( this );

 vista = new QTableView( this );
 QGridLayout *layout = new QGridLayout( this );
 layout->addWidget( vista );
 vista->setModel( modelo );
 vista->hideColumn( 0 );
 vista->setItemDelegate( new DRecibo( vista ) );

 modelo->select();

 vista->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
 vista->setTextElideMode( Qt::ElideRight );
 vista->setSelectionBehavior( QAbstractItemView::SelectRows );
 vista->setSortingEnabled( true );
 // permite que no se pueda editar desde la vista
 vista->setEditTriggers( QAbstractItemView::NoEditTriggers );
 // edicion
 connect( vista, SIGNAL( activated( const QModelIndex& ) ), this, SLOT( modificar( const QModelIndex& ) ) );

 ActVer = new QAction( "&Ver", this );
 ActVer->setIcon( QIcon( ":/imagenes/ver.png" ) );
 ActVer->setShortcut( QKeySequence( "Ctrl+v" ) );
 ActVer->setToolTip( "Ver recibo seleccionado ( Ctrol + v )" );
 ActVer->setStatusTip( "Ver el primer recibo que se encuentra seleccionado (Ctrl+v)" );
 connect( ActVer, SIGNAL( triggered() ), this, SLOT( ver() ) );

 ActAgregar = new QAction( "Agregar", this );
 ActAgregar->setIcon( QIcon( ":/imagenes/nuevo.png" ) );
 ActAgregar->setShortcut( QKeySequence( "Ctrl+a" ) );
 ActAgregar->setStatusTip( "Genera un nuevo recibo" );
 ActAgregar->setToolTip( "Abre la ventana para agregar un nuevo recibo ( Ctrl + a ) " );
 connect( ActAgregar, SIGNAL( triggered() ), this, SLOT( agregar() ) );

 ActModificar = new QAction( "Modificar", this );
 ActModificar->setIcon( QIcon( ":/imagenes/editar.png" ) );
 ActModificar->setStatusTip( "Modifica el recibo seleccionado" );
 ActModificar->setToolTip( "Modifica el recibo seleccionado ( Ctrl + m ) " );
 ActModificar->setShortcut( QKeySequence( "Ctrl+m" ) );
 connect( ActModificar, SIGNAL( triggered() ), this, SLOT( modificar() ) );

 ActEliminar = new QAction( "Eliminar", this );
 ActEliminar->setIcon( QIcon( ":/imagenes/eliminar.png" ) );
 ActEliminar->setStatusTip( "Elimina el recibo seleccionado" );
 ActEliminar->setToolTip( "Eliminar registro activo  Ctrl + e ) " );
 ActEliminar->setShortcut( QKeySequence( "Ctrl+e" ) );
 connect( ActEliminar, SIGNAL( triggered() ), this, SLOT( eliminar() ) );

  ActImprimir = new QAction( "Imprimir", this );
  ActImprimir->setIcon( QIcon( ":/imagenes/impresora.png" ) );
  ActImprimir->setStatusTip( "Imprime el/los recibos seleccionados" );
  ActImprimir->setShortcut( QKeySequence( "Ctrl + i " ) );
  ActImprimir->setToolTip( "Imprimir registros seleccionados" );
  connect( ActImprimir, SIGNAL( triggered() ), this, SLOT( imprimir() ) );

 ActCerrar = new QAction( "Cerrar", this );
 ActCerrar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
 ActCerrar->setStatusTip( "Cierra esta ventana" );
 ActCerrar->setToolTip( "Cierra la ventana actual ( Ctrl + c ) " );
 ActCerrar->setShortcut( QKeySequence( "Ctrl+c" ) );
 connect( ActCerrar, SIGNAL( triggered() ), this, SLOT( close() ) );

 d = new QToolBar( this ); 
 d->setObjectName( "dockFiltroClientes" );
 FiltroClientes *f = new FiltroClientes( this );
 d->addWidget( f );
 qobject_cast<QMainWindow *>(HiComp::tabs()->parentWidget())->addToolBar( Qt::BottomToolBarArea ,d );
 connect( f, SIGNAL( seteaFiltrado( bool, int ) ), this, SLOT( setearFiltrado( bool, int ) ) );
 connect( f, SIGNAL( cambioCliente( int ) ), this, SLOT( cambioClienteFiltro( int ) ) );

 addAction( ActVer );
 addAction( ActAgregar );
 addAction( ActModificar );
 addAction( ActEliminar );
 addAction( ActImprimir );
 addAction( ActCerrar );
}


VRecibos::~VRecibos()
{
}


void VRecibos::agregar()
{
 FormAgregarRecibo *f = new FormAgregarRecibo( HiComp::tabs() );
 HiComp::tabs()->setCurrentWidget( HiComp::tabs()->widget( HiComp::tabs()->addWidget( f ) ) );
}

void VRecibos::modificar()
{
 QItemSelectionModel *selectionModel = vista->selectionModel();
 QModelIndexList indices = selectionModel->selectedRows();
 if( indices.size() < 1 )
 {
   QMessageBox::warning( this, "Seleccione un recibo",
                   "Por favor, seleccione un recibo para ver",
                   QMessageBox::Ok );
   return;
 }
 QModelIndex indice;
 FormModificarRecibo *f = new FormModificarRecibo( HiComp::tabs() );
 HiComp::tabs()->setCurrentWidget( HiComp::tabs()->widget( HiComp::tabs()->addWidget( f ) ) );
 f->cargarDatos( indices[0], modelo );
}


void VRecibos::ver()
{
 QItemSelectionModel *selectionModel = vista->selectionModel();
 QModelIndexList indices = selectionModel->selectedRows();
 if( indices.size() < 1 )
 {
   QMessageBox::warning( this, "Seleccione un recibo",
                   "Por favor, seleccione un recibo para ver",
                   QMessageBox::Ok );
   return;
 }
 QModelIndex indice;
 foreach( indice, indices )
 {
   if ( indice.isValid() )
   {
      int id = indice.model()->data( indice.model()->index( indice.row(), 0 ), Qt::DisplayRole ).toInt();
      visorRecibo *v = new visorRecibo( this );
      v->verRecibo( id );
      HiComp::tabs()->setCurrentWidget( HiComp::tabs()->widget( HiComp::tabs()->addWidget( v ) ) );
   }
 }
}



/*!
    \fn VRecibos::eliminar()
 */
void VRecibos::eliminar()
{
//Preguntar al usuario si esta seguro
 QItemSelectionModel *selectionModel = vista->selectionModel();
 QModelIndexList indices = selectionModel->selectedRows();
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
                   QString( "Esta seguro de eliminar %1 item?").arg( indices.size() ),
                   "Si", "No" );
 if ( ret == 0 )
 {
	QModelIndex indice;
	foreach( indice, indices )
	{
		if( indice.isValid() )
		{
			modelo->removeRow( indice.row() );
		}
	}
 }
 return;
}



/*!
    \fn VRecibos::imprimir()
 */
void VRecibos::imprimir()
{
 // Veo la impresora
#ifndef QT_NO_PRINTER
 QPrinter printer( QPrinter::HighResolution );
 #ifdef QT_WS_WIN
  printer.setOutputFormat(QPrinter::NativeFormat);
 #endif
 ///@todo Poner las propiedades de las hojas desde las preferencias
 if( HiComp::pref()->value( "preferencias/recibos/orientacion", QPrinter::Landscape ).toInt() == QPrinter::Landscape )
 {
   printer.setOrientation( QPrinter::Landscape );
 }
 else
 {
  printer.setOrientation( QPrinter::Portrait );
 }
 QPrintDialog *dialog = new QPrintDialog( &printer, this );
 dialog->setWindowTitle( "Imprimir" );
 if ( dialog->exec() != QDialog::Accepted )
 { return; }
 // veo que quiere imprimir
 QItemSelectionModel *selectionModel = vista->selectionModel();
 QModelIndexList indices = selectionModel->selectedRows();
 if( indices.size() < 1 )
 {
   QMessageBox::warning( this, "Seleccione un recibo",
                   "Por favor, seleccione un recibo para imprimir",
                   QMessageBox::Ok );
   return;
 }
 // espacio de impresion
 QPainter pintor;
 pintor.begin( &printer );

 QModelIndex indice;
 foreach( indice, indices )
 {
   if ( indice.isValid() )
   {
    Recibo r;
    r.cargarRegistro( indice.model()->data( indice.model()->index( indice.row(), 0 ), Qt::DisplayRole ).toInt() );
    r.imprimir( &pintor );
   }
  printer.newPage();
 }
 pintor.end();
#endif
}


/*!
    \fn VRecibos::modificar( const QModelIndex& index )
 */
void VRecibos::modificar( const QModelIndex& index )
{
 FormModificarRecibo *f = new FormModificarRecibo( HiComp::tabs() );
 HiComp::tabs()->setCurrentWidget( HiComp::tabs()->widget( HiComp::tabs()->addWidget( f ) ) );
 f->cargarDatos( index, modelo );
}


/*!
    \fn VRecibos::close()
 */
void VRecibos::close()
{
  d->close();
  QWidget::close();
}


/*!
    \fn VRecibos::setearFiltrado( bool activo )
 */
void VRecibos::setearFiltrado( bool activo, int id_cliente )
{
  if( !activo )
  {
   modelo->setFilter( "" );
   modelo->select();
   return;
  }
  else
  {
   qDebug( QString( "cliente = '%1'" ).arg( id_cliente ).toLocal8Bit() );
   modelo->setFilter( QString( "cliente = '%1'" ).arg( id_cliente )  );
   modelo->select();
  }
}


/*!
    \fn VRecibos::cambioClienteFiltro( int id_cliente )
 */
void VRecibos::cambioClienteFiltro( int id_cliente )
{
 qDebug( QString( "cliente = '%1'" ).arg( id_cliente ).toLocal8Bit() );
 modelo->setFilter( QString( "cliente = '%1'" ).arg( id_cliente )  );
 modelo->select();
}
