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
#include <QSqlQuery>
#include <QSqlRecord>
#include <QInputDialog>
#include <QFileDialog>
#include <QSqlError>

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
	connect( PBAgregarEstablecimientoOrigen, SIGNAL( clicked() ), this, SLOT( agregarEstablecimientoOrigen() ) );
	connect( PBAgregarEstablecimientoDestino, SIGNAL( clicked() ), this, SLOT( agregarEstablecimientoDestino() ) );
	connect( PBAgregar, SIGNAL( clicked() ), this, SLOT( agregarCaravana() ) );
	connect( PBEliminar, SIGNAL( clicked() ), this, SLOT( eliminarCaravana() ) );
	connect( PBCargarArchivo, SIGNAL( clicked() ), this, SLOT( cargarDesdeArchivo() ) );

	connect( LENumCar, SIGNAL( returnPressed () ), this, SLOT( agregarCaravana() ) );

	// Inicializo los modelos
	CBCategoria->setModel( new MCategoria( CBCategoria ) );
	CBCategoria->setModelColumn( 1 );
	qobject_cast<QSqlTableModel *>(CBCategoria->model())->select();

	QSqlQueryModel *mcli = new QSqlQueryModel( this );
	mcli->setQuery( "SELECT id, apellido || ', ' || nombre FROM clientes" );
	CBCliente->setModel( mcli );
	CBCliente->setModelColumn( 1 );
	CBCliente->setCurrentIndex( 0 );

	// pongo la fecha de hoy
	dEFecha->setDate( QDate::currentDate() );

	//Inicializo el modelo de las carvanas
	model = new QStringListModel( TVCaravanas );
	model->setHeaderData( 0, Qt::Horizontal, "Numero de Caravana" );
	TVCaravanas->setModel( model );
	TVCaravanas->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
	TVCaravanas->horizontalHeader()->hide();

	// Seteo el numero de tri
	setearNumeroTri();

	switch( accion )
	{
		case compra:
		{
			LTitulo->setText( "Ingreso de caravanas por compra" );
			LOrigen->hide();
			CBEstablecimientoDestino->setModel( new MEstablecimiento( CBEstablecimientoDestino ) );
			CBEstablecimientoDestino->setModelColumn( 1 );
			qobject_cast<QSqlTableModel *>(CBEstablecimientoDestino->model())->select();
			CBEstablecimientoOrigen->hide();
			PBAgregarEstablecimientoOrigen->hide();
			break;
		}
		case venta:
		{
			LTitulo->setText( "Salida de caravanas por venta" );
			LDestino->hide();
			CBEstablecimientoOrigen->setModel( new MEstablecimiento( CBEstablecimientoOrigen ) );
			CBEstablecimientoOrigen->setModelColumn( 1 );
			qobject_cast<QSqlTableModel *>(CBEstablecimientoOrigen->model())->select();
			CBEstablecimientoDestino->hide();
			PBAgregarEstablecimientoDestino->hide();
			break;
		}
		case movimiento:
		{
			LTitulo->setText( "Movimiento interno de caravanas" );
			LCliente->hide();
			CBCliente->hide();
			PBAgregarCliente->hide();
			CBEstablecimientoOrigen->setModel( new MEstablecimiento( CBEstablecimientoOrigen ) );
			CBEstablecimientoOrigen->setModelColumn( 1 );
			qobject_cast<QSqlTableModel *>(CBEstablecimientoOrigen->model())->select();
			
			CBEstablecimientoDestino->setModel( new MEstablecimiento( CBEstablecimientoDestino ) );
			CBEstablecimientoDestino->setModelColumn( 1 );
			qobject_cast<QSqlTableModel *>(CBEstablecimientoDestino->model())->select();
			break;
		}
		case stock:
		{
			LTitulo->setText( "Ingreso de caravanas por stock" );
			// oculto el origen ( viene del limbo )
			LOrigen->hide();
			CBEstablecimientoOrigen->hide();
			PBAgregarEstablecimientoOrigen->hide();
			// oculto el comprador/vendedor
			LCliente->hide();
			CBCliente->hide();
			PBAgregarCliente->hide();
			// Oculto la categoria 
			LCategoria->hide();
			CBCategoria->hide();
			PBAgregarCategoria->hide();
			// Oculto el DTA y el TRI
			LTri->hide();
			LDTA->hide();
			LETRI->hide();
			LEDTA->hide();
			CBEstablecimientoOrigen->setModel( new MEstablecimiento( CBEstablecimientoOrigen ) );
			CBEstablecimientoOrigen->setModelColumn( 1 );
			qobject_cast<QSqlTableModel *>(CBEstablecimientoOrigen->model())->select();
			CBEstablecimientoDestino->setModel( new MEstablecimiento( CBEstablecimientoDestino ) );
			CBEstablecimientoDestino->setModelColumn( 1 );
			qobject_cast<QSqlTableModel *>(CBEstablecimientoDestino->model())->select();
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
 if( d.contains( LENumCar->text() ) )
 {
  return;
 }
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



/*!
    \fn FormMovimiento::setearNumeroTri()
 */
void FormMovimiento::setearNumeroTri()
{
 QSqlQuery cola;
 if( cola.exec( "SELECT seq FROM sqlite_sequence WHERE name = 'car_tri'" ) )
 {
  if( cola.next() )
  {
	///@todo Agregar una mascara para que el numero salga mejor
    LETRI->setText( QString( "%1" ).arg( cola.record().value(0).toInt() ) );
  }
  else
  {
   qWarning( "Error al ejecutar la obtencion del proximo numero de tri (next)" );
   LETRI->setText( QString( "%1" ).arg( -1 ) );
  }
 }
 else
 {
  qWarning( "Error al ejecutar la obtencion del proximo numero de tri" );
  LETRI->setText( QString( "%1" ).arg( -1 ) );
 }
}


/*!
    \fn FormMovimiento::agregarCategoria()
 */
void FormMovimiento::agregarCategoria()
{
     bool ok;
    QString text = QInputDialog::getText(this, tr("Nueva Categoria"),
                                         tr("Nombre de la categoria:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty())
    {
	QSqlTableModel *mod = qobject_cast<QSqlTableModel *>(CBCategoria->model());
	QSqlRecord rec = mod->record();
	rec.remove(0);
	rec.setValue( "nombre", text );
	if( mod->insertRecord( -1, rec ) )
	{
		///@todo Selecciono el id insertado en el combo automaticamente???
		return;
	}
	else
	{
		qWarning( "Error al insertar el registro de categoria" );
		return;
	}
    }
}


/*!
    \fn FormMovimiento::agregarCliente()
 */
void FormMovimiento::agregarCliente()
{
    bool ok1,ok2;
    QString nombre = QInputDialog::getText(this, tr("Nuevo Cliente - Paso 1"),
                                         tr("Nombre del cliente:"), QLineEdit::Normal,
                                         "", &ok1);
    if( !ok1 )
    { return; }
    QString apellido = QInputDialog::getText(this, tr("Nuevo Cliente - Paso 2"),
                                         tr("Apellido del cliente:"), QLineEdit::Normal,
                                         "", &ok2);
    if ( ok1 && ok2 && !nombre.isEmpty() && !apellido.isEmpty())
    {
	QSqlQuery cola;
	if( cola.exec( QString( "INSERT INTO clientes( nombre, apellido ) VALUES ( '%1', '%2' )" ).arg( nombre ).arg( apellido ) ) )
	{
		///@todo Selecciono el id insertado en el combo automaticamente???
		qobject_cast<QSqlQueryModel *>(CBCliente->model())->clear();
		qobject_cast<QSqlQueryModel *>(CBCliente->model())->setQuery( "SELECT id, apellido || ', ' || nombre FROM clientes" );
		return;
	}
	else
	{
		qWarning( QString( "Error al insertar el registro de cliente \n Error: %1").arg( cola.lastError().text() ).toLocal8Bit() );
		return;
	}
    }
}


/*!
    \fn FormMovimiento::agregarEstablecimientoOrigen()
 */
void FormMovimiento::agregarEstablecimientoOrigen()
{
      bool ok1,ok2;
    QString nombre = QInputDialog::getText(this, tr("Nuevo Establecimiento - Paso 1"),
                                         tr("Nombre del Establecimiento:"), QLineEdit::Normal,
                                         "", &ok1 );
    if( !ok1 )
    { return; }
    QString respma = QInputDialog::getText(this, tr("Nuevo Establecimiento - Paso 2"),
                                         tr("Numero de RESPMA:"), QLineEdit::Normal,
                                         "", &ok2 );
    if ( ok1 && ok2 && !nombre.isEmpty() && !respma.isEmpty())
    {
	QSqlTableModel *mod = qobject_cast<QSqlTableModel *>(CBEstablecimientoOrigen->model());
	QSqlRecord rec = mod->record();
	rec.remove(0);
	rec.setValue( "nombre", nombre );
	rec.setValue( "respma", respma );
	if( mod->insertRecord( -1, rec ) )
	{
		///@todo Selecciono el id insertado en el combo automaticamente???
		return;
	}
	else
	{
		qWarning( QString( "Error al insertar el registro de establecimiento \n Error: %1").arg( mod->lastError().text() ).toLocal8Bit() );
		return;
	}
    }
}

/*!
    \fn FormMovimiento::agregarEstablecimientoDestino()
 */
void FormMovimiento::agregarEstablecimientoDestino()
{
      bool ok1,ok2;
    QString nombre = QInputDialog::getText(this, tr("Nuevo Establecimiento - Paso 1"),
                                         tr("Nombre del Establecimiento:"), QLineEdit::Normal,
                                         "", &ok1 );
    if( !ok1 )
    { return; }
    QString respma = QInputDialog::getText(this, tr("Nuevo Establecimiento - Paso 2"),
                                         tr("Numero de RESPMA:"), QLineEdit::Normal,
                                         "", &ok2 );
    if ( ok1 && ok2 && !nombre.isEmpty() && !respma.isEmpty())
    {
	QSqlTableModel *mod = qobject_cast<QSqlTableModel *>(CBEstablecimientoDestino->model());
	QSqlRecord rec = mod->record();
	rec.remove(0);
	rec.setValue( "nombre", nombre );
	rec.setValue( "respma", respma );
	if( mod->insertRecord( -1, rec ) )
	{
		///@todo Selecciono el id insertado en el combo automaticamente???
		return;
	}
	else
	{
		qWarning( QString( "Error al insertar el registro de establecimiento \n Error: %1").arg( mod->lastError().text() ).toLocal8Bit() );
		return;
	}
    }
}


/*!
    \fn FormMovimiento::cargarDesdeArchivo()
 */
void FormMovimiento::cargarDesdeArchivo()
{
     QFileDialog::Options opciones;
     QString filtroSeleccion;
    QString archivo = QFileDialog::getOpenFileName( this,
                                "Importar desde archivo...",
                                "",
                                "Todos los archivos (*);;Archivos de texto (*.txt)",
                                &filtroSeleccion,
                                opciones);
    if ( !archivo.isEmpty() )
    {
	qWarning( "Esta opcion todavia no fue implementada" );
    }
}
