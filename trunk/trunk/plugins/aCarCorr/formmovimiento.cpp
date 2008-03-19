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
#include "formmovimiento.h"

#include <QAction>
#include <QDate>
#include <QStringListModel>
#include <QListView>
#include <QMessageBox>
#include <QHeaderView>

#include "mestablecimiento.h"
#include "mcategoria.h"
#include "mclientes.h"

FormMovimiento::FormMovimiento(QWidget* parent, Qt::WFlags fl,  tipo accion )
: QWidget( parent, fl ), Ui::FormMovimientoBase()
{
	setupUi(this);
	setAttribute( Qt::WA_DeleteOnClose );

	ActCerrar = new QAction( "Cerrar", this );
	ActCerrar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
	ActCerrar->setText( "Cerrar" );
	ActCerrar->setStatusTip( "Cierra la ventana actual" );
	connect( ActCerrar, SIGNAL( triggered() ), this, SLOT( cerrar() ) );

	ActGuardar = new QAction( "Guardar", this );
	ActGuardar->setIcon( QIcon( ":/imagenes/guardar.png" ) );
	ActGuardar->setToolTip( "Guarda los datos actuales del formulario" ) ;
	connect( ActGuardar, SIGNAL( triggered() ), this, SLOT( guardar() ) );

	addAction( ActGuardar );
	addAction( ActCerrar );

	//Iconos de ls botones
	PBAgregarCategoria->setIcon( QIcon( ":/imagenes/add.png" ) );
	PBAgregarCliente->setIcon( QIcon( ":/imagenes/add.png" ) );
	PBAgregarEstablecimientoOrigen->setIcon( QIcon( ":/imagenes/add.png" ) );
	PBAgregarEstablecimientoDestino->setIcon( QIcon( ":/imagenes/add.png" ) );
	PBAgregar->setIcon( QIcon( ":/imagenes/add.png" ) );
	PBEliminar->setIcon( QIcon( ":/imagenes/eliminar.png" ) );

	// Conecto los botones
	connect( PBAgregarCategoria, SIGNAL( clicked() ), this, SLOT( agregarCategoria() ) );
	connect( PBAgregarCliente, SIGNAL( clicked() ), this, SLOT( agregarCliente() ) );
	connect( PBAgregarEstablecimientoOrigen, SIGNAL( clicked() ), this, SLOT( agregarEstablecimiento() ) );
	connect( PBAgregarEstablecimientoDestino, SIGNAL( clicked() ), this, SLOT( agregarEstablecimiento() ) );
	connect( PBAgregar, SIGNAL( clicked() ), this, SLOT( agregarCaravana() ) );
	connect( PBEliminar, SIGNAL( clicked() ), this, SLOT( eliminarCaravana() ) );

	// Inicializo el modelo

	CBEstablecimientoOrigen->setModel( new MEstablecimiento( CBEstablecimientoOrigen ) );
	CBEstablecimientoOrigen->setModelColumn( 1 );
	qobject_cast<QSqlTableModel *>(CBEstablecimientoOrigen->model())->select();

	CBEstablecimientoDestino->setModel( new MEstablecimiento( CBEstablecimientoDestino ) );
	CBEstablecimientoDestino->setModelColumn( 1 );
	qobject_cast<QSqlTableModel *>(CBEstablecimientoDestino->model())->select();

	CBCategoria->setModel( new MCategoria( CBCategoria ) );
	CBCategoria->setModelColumn( 1 );
	qobject_cast<QSqlTableModel *>(CBCategoria->model())->select();

	QSqlQueryModel *mcli = new QSqlQueryModel( this );
	mcli->setQuery( "SELECT id, apellido || ', ' || nombre FROM clientes" );
	CBCliente->setModel( mcli );
	CBCliente->setModelColumn( 1 );
	CBCliente->setCurrentIndex( 0 );

	///@todo Insertar el numero de TRI automaticamente
	
	// pongo la fecha de hoy
	dEFecha->setDate( QDate::currentDate() );

	//Inicializo el modelo de las carvanas
	model = new QStringListModel( TVCaravanas );
	model->setHeaderData( 0, Qt::Horizontal, "Numero de Caravana" );
	TVCaravanas->setModel( model );
	TVCaravanas->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
	TVCaravanas->horizontalHeader()->hide();

	switch( accion )
	{
		case compra:
		{
			LOrigen->hide();
			CBEstablecimientoOrigen->hide();
			PBAgregarEstablecimientoOrigen->hide();
			break;
		}
		case venta:
		{
			LDestino->hide();
			CBEstablecimientoDestino->hide();
			PBAgregarEstablecimientoDestino->hide();
			break;
		}
		case movimiento:
		{
			break;
		}
		default:
		{
			LDestino->hide();
			CBEstablecimientoDestino->hide();
			PBAgregarEstablecimientoDestino->hide();
			LOrigen->hide();
			CBEstablecimientoOrigen->hide();
			PBAgregarEstablecimientoOrigen->hide();
			break;
		}
	}
}

FormMovimiento::~FormMovimiento()
{
}


void FormMovimiento::agregarCaravana()
{
 if( LENumCar->text().isEmpty() )
 {
  return;
 }
 QStringList d = model->stringList();
 d.append( LENumCar->text() );
 model->setStringList( d );
 LENumCar->clear();
}

/*!
    \fn FormMovimiento::eliminarCaravana()
 */
void FormMovimiento::eliminarCaravana()
{
 QModelIndexList indexes = TVCaravanas->selectionModel()->selectedRows();
 if( indexes.count() <= 0 )
 {
  QMessageBox::information( this, "Error", "No ha elegido ningun item para eliminar. Por favor seleccione uno o varios y presione el boton eliminar" );
  return;
 }
 
 if( QMessageBox::question( this, "¿Esta seguro?", "¿Esta seguro que desea eliminar este/os numero/s de caravanas?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes ) == QMessageBox::Yes )
 {
  QModelIndex index;
  foreach( index, indexes )
  {
   model->removeRow( index.row() );
  }
 }
}

