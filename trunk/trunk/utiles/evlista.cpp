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
#include "evlista.h"
#include <QSqlRelationalTableModel>
#include <QSqlTableModel>
#include <QTableView>
#include <QHeaderView>
#include "preferencias.h"
#include "eactemail.h"
#include "eactcerrar.h"
#include "eactpdf.h"
#include <QSqlRecord>
#include <QSqlError>
#include <QMessageBox>
#include <QAction>
#include <QGridLayout>
#include <QModelIndex>
#include <QMenu>
#include <QApplication>

EVLista::EVLista( QWidget *parent, Qt::WFlags fl )
: EVentana( parent, fl )
{
 QGridLayout *layout = new QGridLayout( this );
 vista = new QTableView( this );
 vista->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );
 layout->addWidget( vista );
 this->setLayout( layout );
 // Propiedades varias
 vista->setSelectionMode( QAbstractItemView::SingleSelection );
 vista->setSelectionBehavior( QAbstractItemView::SelectRows );
 vista->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
 vista->setTextElideMode( Qt::ElideRight );

 //////////////////////////////////////////////////////////////////////////////////////////
 // Acciones Genericas
 ////////////////////////////////////////////////////////////////////////////////////////
 ActAgregar = new QAction( "&Agregar", this );
 ActAgregar->setIcon( QIcon( ":/imagenes/add.png" ) );
 ActAgregar->setShortcut( QKeySequence( "Ctrl+a" ) );
 ActAgregar->setToolTip( "Agregar un nuevo item ( Ctrl + a )" );
 connect( ActAgregar, SIGNAL( triggered() ), this, SLOT( agregar() ) );

 ActModificar = new QAction( "&Modificar", this );
 ActModificar->setIcon( QIcon( ":/imagenes/editar.png" ) );
 ActModificar->setShortcut( QKeySequence( "Ctrl+m" ) );
 ActModificar->setToolTip( "Modifica el item actual ( Ctrl + m )" );
 connect( ActModificar, SIGNAL( triggered() ), this, SLOT( modificar() ) );

 ActImprimir = new QAction( "&Imprimir", this );
 ActImprimir->setIcon( QIcon( ":/imagenes/impresora.png" ) );
 ActImprimir->setToolTip( "Imprime el/los items seleccionados ( Ctrl + i )" );
 ActImprimir->setShortcut( QKeySequence( "Ctrl+i" ) );
 connect( ActImprimir, SIGNAL( triggered() ), this, SLOT( imprimir() ) );

 ActEliminar = new QAction( "&Eliminar", this );
 ActEliminar->setIcon( QIcon( ":/imagenes/eliminar.png" ) );
 ActEliminar->setShortcut( QKeySequence( "Ctrl+e" ) );
 ActEliminar->setToolTip( "Eliminar el o los items seleccionados ( Ctrl + e )" );
 connect( ActEliminar, SIGNAL( triggered() ), this, SLOT( eliminar()  ) );

 ActBuscar = new QAction( "&Buscar", this );
 ActBuscar->setIcon( QIcon( ":/imagenes/buscar.png" ) );
 ActBuscar->setShortcut( QKeySequence( "Ctrl+b" ) );
 ActBuscar->setToolTip( "Buscar items ( Ctrl + b )" );
 connect( ActBuscar, SIGNAL( triggered() ), this, SLOT( buscar() ) );

 ActEmail = new EActEmail( this );

 ActPdf = new EActPdf( this );
 connect( ActPdf, SIGNAL( triggered() ), this, SLOT( aPdf() ) );

 ActCerrar = new EActCerrar( this );
 connect( ActCerrar, SIGNAL( triggered() ), this, SLOT( cerrar() ) );
 ////////////////////////////////
 // Sistema para el menu contextual
 /////////////////////////////////////
 connect( vista, SIGNAL( pressed( const QModelIndex & ) ), this, SLOT( hacerMenuContextual( const QModelIndex & ) ) );

 rmodelo = 0;
 modelo = 0;
}


EVLista::~EVLista()
{
}


/*!
    \fn EVLista::cerrar()
    Llamada cuando se presiona el boton cerrar, cierra la ventana
 */
void EVLista::cerrar()
{
 this->close();
}


/*!
    \fn EVLista::agregar( bool autoeliminarid )
        Agrega un nuevo registro mediante la vista al modelo
        @param autoeliminarid elimina el primer campo de los registros
 */
void EVLista::agregar( bool autoeliminarid )
{
    QSqlTableModel *m = qobject_cast<QSqlTableModel *>(vista->model());
    QSqlRecord registro = m->record();

    if( autoeliminarid )
    { registro.remove( 0 ); }

    if( !m->insertRecord( -1, registro ) )
    {
         qDebug( "Error al insertar el registro" );
         qDebug( QString( "Detalles: tipo: %1, errno: %2, descripcion: %3" ).arg( m->lastError().type() ).arg( m->lastError().number() ).arg( m->lastError().text() ).toLocal8Bit() );
    }
}

/*!
    \fn EVLista::eliminar()
        Elimina los items seleccionados de la vista
 */
void EVLista::eliminar()
{
 QSqlRelationalTableModel *m = qobject_cast<QSqlRelationalTableModel *>(vista->model());
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
                        if( m->removeRow( indice.row() ) )
                        { return; }
                        else
                        { qWarning( qPrintable( "Error al eliminar el registro" + m->lastError().text() ) ); }
                }
        }
 }
 return;
}

/*!
    \fn EVLista::closeEvent( QCloseEvent * c)
        Metodo llamado al cerrarse el form
        @param c evento de cierre
 */
void EVLista::closeEvent( QCloseEvent * c)
{
 /*if( vista != 0 )
    delete vista;*/
 /*if( modelo )
 { modelo->submitAll(); }*/
// delete modelo;
 EVentana::closeEvent( c );
}


/*!
    \fn EVLista::buscar()
 */
void EVLista::buscar()
{
    /// \todo implement me
}


/*!
    \fn EVLista::imprimir()
 */
void EVLista::imprimir()
{
    /// \todo implement me
}


/*!
    \fn EVLista::modificar()
 */
void EVLista::modificar()
{
    /// \todo implement me
}


/*!
    \fn EVLista::email()
 */
void EVLista::email()
{
    /// \todo implement me
}


/*!
    \fn EVLista::aPdf()
 */
void EVLista::aPdf()
{
    /// \todo implement me
}

#include <QDate>
void EVLista::antes_de_insertar( int /*row*/, QSqlRecord & /*record*/ )
{
 /*if( QSqlDatabase::database().driverName() == "QSQLITE" )
 {
        Se utiliza este truco para que no falle la insercion y se puedan agregar registros sin problemas
        como sqlite no tiene forma de insertar timestamps en los registros al actualizar hay que hacerlo a mano
   if( record.contains( "creado" ) )
   {  record.setValue( "creado", QDate::currentDate() );  }
   if( record.contains( "modificado" ) )
   { record.setValue( "modificado", QDate::currentDate() ); }
 }
 else if( QSqlDatabase::database().driverName() == "QMYSQL" )
 {
          MySql solo permite tener un registro con timestamp activado, asique ponemos la fecha en el de crear
        if( record.contains( "creado" ) )
        { record.setValue( "creado", QDate::currentDate() ); }
 }*/
}


/*!
    \fn EVLista::menuContextual( const QModelIndex &indice, QMenu *menu )
        Rellena el menu contextual con las acciones que se deben utilizar para el item en indice. Debe reimplementarse para cada vista que dese agregar acciones personalizadas.
 */
void EVLista::menuContextual( const QModelIndex &/*indice*/, QMenu */*menu*/ )
{
 // este metodo se debe reimplementar para ser util, retorno automaticamente
 return;
}


/*!
    \fn EVLista::hacerMenuContextual( const QModelIndex &indice )
 */
void EVLista::hacerMenuContextual( const QModelIndex &indice )
{
  if( QApplication::mouseButtons() == Qt::RightButton )
 {
   // Calculo la posicion en que esta el item
   QPoint posicion;
   posicion.setX( vista->columnViewportPosition( indice.column() ) );
   posicion.setY( vista->rowViewportPosition( indice.row() ) );
   QMenu *_menuContextual = new QMenu( this );
   // Pido el menu contextual a la clase que esta manejando la vista acutlamente
   menuContextual( indice, _menuContextual );
   // Si no hay nada en el menu, no agrego el separador
   if( _menuContextual->isEmpty() ) { _menuContextual->addSeparator(); }
   _menuContextual->addAction( ActCerrar );
   _menuContextual->popup( this->mapToGlobal( posicion ) );
 }
}
