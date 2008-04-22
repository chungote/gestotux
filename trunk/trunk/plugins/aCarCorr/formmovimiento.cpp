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
#include <QListView>
#include <QMessageBox>
#include <QHeaderView>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QInputDialog>
#include <QFileDialog>
#include <QSqlError>
#include <QFile>
#include <QItemDelegate>

#include "mestablecimiento.h"
#include "mcategoria.h"
#include "mclientes.h"
#include "mcaravanadueno.h"
#include "mduenos.h"

//Tempral
//#include <modeltest.h>

FormMovimiento::FormMovimiento(QWidget* parent, Qt::WFlags fl, int accion )
: QWidget( parent, fl ), Ui::FormMovimientoBase()
{
	_accion = accion;
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
	CBCategoria->setCurrentIndex( -1 );

	QSqlQueryModel *mcli = new QSqlQueryModel( this );
	mcli->setQuery( "SELECT id, apellido || ', ' || nombre FROM clientes" );
	CBCliente->setModel( mcli );
	CBCliente->setModelColumn( 1 );
	CBCliente->setCurrentIndex( -1 );

	// pongo la fecha de hoy
	dEFecha->setDate( QDate::currentDate() );

	//Inicializo el modelo de las carvanas
	model = new MCaravanaDueno( TVCaravanas );
	//new ModelTest(model, this);
	TVCaravanas->setModel( model );
	TVCaravanas->setItemDelegate( new QItemDelegate( TVCaravanas ) );
	TVCaravanas->hideColumn( 0 );
	TVCaravanas->horizontalHeader()->setResizeMode( QHeaderView::Stretch );

	// Seteo el numero de tri
	setearNumeroTri();

	switch( accion )
	{
		case compra:
		{
			LTitulo->setText( "Ingreso de caravanas por compra" );
			LOrigen->hide();
			LCliente->setText( "Vendedor:" );
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
			LCliente->setText( "Comprador:" );
			LDestino->hide();
			CBEstablecimientoOrigen->setModel( new MEstablecimiento( CBEstablecimientoOrigen ) );
			CBEstablecimientoOrigen->setModelColumn( 1 );
			qobject_cast<QSqlTableModel *>(CBEstablecimientoOrigen->model())->select();
			CBEstablecimientoDestino->hide();
			PBAgregarEstablecimientoDestino->hide();
			break;
		}
		case mudanza:
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
	CBEstablecimientoDestino->setCurrentIndex( -1 );
	CBEstablecimientoOrigen->setCurrentIndex( -1 );
}

FormMovimiento::~FormMovimiento()
{
}

void FormMovimiento::cerrar()
{
 close();
}

void FormMovimiento::agregarCaravana()
{
 if( LENumCar->text().isEmpty() )
 {
  return;
 }
 model->verificarAgregar( LENumCar->text(), "" );
 LENumCar->clear();
 LENumCar->setFocus();
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
    LETRI->setText( QString( "%1" ).arg( cola.record().value(0).toInt() + 1 ) );
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
                                "Archivo csv (*.csv *.CSV);; Todos los archivos (*.*)",
                                &filtroSeleccion,
                                opciones);
    if ( !archivo.isEmpty() )
    {
	QFile arch( archivo );
	if( !arch.open( QIODevice::ReadOnly ) )
	{
		qWarning( "No se puede abrir el archivo como solo lectura" );
		return;
	}
	// Leo el archivo
	QString cadena( arch.readAll() );
	QStringList cadenas = cadena.split( "\n", QString::SkipEmptyParts, Qt::CaseInsensitive );
	if( cadenas.size() <= 0 )
	{
		qWarning( "No se obtuvo ningun codigo de caravana del archivo" );
		return;
	}
	// separo las cadenas por punto y comas
	QStringList caravanas;
	QString cad, dta;
	foreach( cad, cadenas )
	{
		QStringList temp = cad.split( ";" );
		if( temp.size() >= 2 )
		{
			if(!temp[0].isEmpty())
			{
				caravanas.append( temp[0] );
				qDebug( QString( "Agregado: %1, dta: %2 " ).arg( temp[0] ).arg( temp[1] ).toLocal8Bit() );
				if( dta.isEmpty() )
				{
					dta = temp[1];
				}
			}
		}
		else
		{
			qDebug( "Cadena Vacia" );
		}
	}
	bool ok;
	// Busco la lista de dueños
	MDuenos *duenos = new MDuenos( this );
	QString dueno = QInputDialog::getItem(this, "Elija el dueño",tr("Elija el dueño"), duenos->getLista(), 0, false, &ok );
	if( ok )
	{
		model->verificarAgregar( caravanas, dueno );
	}
	else
	{
		model->verificarAgregar( caravanas );
	}
	LEDTA->setText( dta );
    }
}


/*!
    \fn FormMovimiento::verificar()
 */
bool FormMovimiento::verificar()
{
 // Verifico para todos los formularios el dta y la categoria
 // la fecha siempre esta puesta en hoy y no va a ser invalida
 if( CBCategoria->currentIndex() == -1 )
 {
 	qWarning( "No ha seleccionado una categoria. Por favor elija una" );
 	return false;
 }
 if( LEDTA->text().isEmpty() )
 {
	qWarning( "No ha ingresado un Numero de DTA. Por favor ingrese uno" );
 	return false;
 }
 // Verifico para cada tipo de formulario
 switch( _accion )
 {
	case compra:
	{
		// Destino y vendedor
		if( CBEstablecimientoDestino->currentIndex() == -1 )
		{
			qWarning( "No ha seleccionado un establecimiento de destino. Por favor elija uno" );
			return false;
		}
		if( CBCliente->currentIndex() == -1 )
		{
			qWarning( "No ha seleccionado un comprador. Por favor elija uno" );
			return false;
		}
		break;
	}
	case venta:
	{
		// origen y comprador
		if( CBEstablecimientoOrigen->currentIndex() == -1 )
		{
			qWarning( "No ha seleccionado un establecimiento de origen. Por favor elija uno" );
			return false;
		}
		if( CBCliente->currentIndex() == -1 )
		{
			qWarning( "No ha seleccionado un vendedor. Por favor elija uno" );
			return false;
		}
		break;
	}
	case mudanza:
	{
		// origen y destino
		if( CBEstablecimientoOrigen->currentIndex() == -1 )
		{
			qWarning( "No ha seleccionado un establecimiento de origen. Por favor elija uno" );
			return false;
		}
		if( CBEstablecimientoDestino->currentIndex() == -1 )
		{
			qWarning( "No ha seleccionado un establecimiento de destino. Por favor elija uno" );
			return false;
		}
		break;
	}
	case stock:
	{	
		// Destino
		if( CBEstablecimientoDestino->currentIndex() == -1 )
		{
			qWarning( "No ha seleccionado un establecimiento de destino. Por favor elija uno" );
			return false;
		}
		break;
	}
	default:
	{
		break;
	}
 }
 // verifico que exista al menos una caravana
 if( model->listaCaravanas().isEmpty() )
 {
	qWarning( "No hay caravanas ingresadas. Por favor ingrese alguna" );
	return false;
 }
 // Si llege hasta aca, los datos estan bien
 return true;
}


/*!
    \fn FormMovimiento::hacerInformeSenasa()
 */
void FormMovimiento::hacerInformeSenasa()
{
 qWarning( "Ver como hacer el informe para el senasa" );
}
