/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   				   *
 *   juiraze@yahoo.com.ar  						   *
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
#include "formagregarpresupuesto.h"

#include <QSqlQueryModel>
#include <QDate>
#include "presupuesto.h"
#include "formlistaproductos.h"

FormAgregarPresupuesto::FormAgregarPresupuesto(QWidget* parent, Qt::WFlags fl)
: EVentana( parent ), Ui::FormPresupuestoBase()
{
	// Inicializo el presupeusto!
	pre = new Presupuesto( this );
	this->setAttribute( Qt::WA_DeleteOnClose );
	setupUi(this);
	this->setObjectName( "FormAgregarPresupuesto" );
	LTitulo->setText( "Agregar Presupuesto" );

	connect( RBCliente, SIGNAL( toggled( bool ) ), CBCliente , SLOT( setEnabled( bool ) ) );
	connect( RBOtro   , SIGNAL( toggled( bool ) ), LEOtro    , SLOT( setEnabled( bool ) ) );
	connect( CkBTitulo, SIGNAL( toggled( bool ) ), LETitulo  , SLOT( setEnabled( bool ) ) );

	QAction *ActGuardar = new QAction( "Guardar", this );
	ActGuardar->setIcon( QIcon( ":/imagenes/guardar.png" ) );
	ActGuardar->setStatusTip( "Guarda el formulario de presupuesto actual y lo muestra ( Ctrl + g )" );
	ActGuardar->setShortcut( QKeySequence( "Ctrl+g" ) );
	connect( ActGuardar, SIGNAL( triggered() ), this, SLOT( guardar() ) );

	QAction *ActCancelar = new QAction( "Cancelar", this );
	ActCancelar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
	ActCancelar->setStatusTip( "Cancela los cambios realizados y cierra la ventana" );
	ActCancelar->setShortcut( QKeySequence( "Ctrl+c" ) );
	connect( ActCancelar, SIGNAL( triggered() ), this, SLOT( cancelar() ) );

	QAction *ActProductos = new QAction( "Lista de productos", this );
	ActProductos->setIcon( QIcon( ":/imagenes/productos.png" ) );
	ActProductos->setStatusTip( "Inserta una lista de productos en el presupuesto" );
	ActProductos->setShortcut( QKeySequence( "Ctrl+p" ) );
	connect( ActProductos, SIGNAL( triggered() ), this, SLOT( listaProductos() ) );

	QAction *ActGuardarImprimir = new QAction( "Guardar e Imprimir", this );
	ActGuardarImprimir->setIcon( QIcon( ":/imagenes/guardarimprimir.png" ) );
	ActGuardarImprimir->setStatusTip( "Guarda los datos y abre el dialogo de imprimir" );
	connect( ActGuardarImprimir, SIGNAL( triggered() ), this, SLOT( guardarImprimir() ) );

	QAction *ActImprimir = new QAction( "Imprimir", this );
	ActImprimir->setIcon( QIcon( ":/imagenes/imprimir.png" ) );
	ActImprimir->setStatusTip( "Imprime el presupuesto actual sin guardarlo" );
	connect( ActImprimir, SIGNAL( triggered() ), this, SLOT( imprimir() ) );

	// Agrego las acciones
	addAction( ActGuardar );
	addAction( ActProductos );
	addAction( ActGuardarImprimir );
	addAction( ActImprimir );
	addAction( ActCancelar );

	// Seteo la lista de clientes
	modeloClientes = new QSqlQueryModel( this );
	modeloClientes->setQuery( "SELECT id, apellido || ', ' || nombre FROM clientes" );

	CBCliente->setModel( modeloClientes );
	CBCliente->setModelColumn( 1 );
	CBCliente->setCurrentIndex( -1 );

	// Pongo la fecha actual
	dEFecha->setDate( QDate::currentDate() );

	// Inicializo el formulario ahora para poder usar la modificacion
	formLista = new FormListaProductos( this );
	connect( formLista, SIGNAL( agregarTabla() ), this, SLOT( ponerTabla() ) );
}

FormAgregarPresupuesto::~FormAgregarPresupuesto()
{
 delete pre;
}


/*!
    \fn FormAgregarPresupuesto::listaProductos()
	Metodo que agrega o modifica la lista de productos que se van a colocar en el presupuesto
 */
void FormAgregarPresupuesto::listaProductos()
{
  formLista->show();
}


/*!
    \fn FormAgregarPresupuesto::cancelar()
	Elimina datos temporales y cierra el formulario
 */
void FormAgregarPresupuesto::cancelar()
{
    /// @todo Verificar el cierre de este formulario por asociaciones con otras tablas
    formLista->getModelo()->revertAll();
    this->close();
}

#include <QTextTableCell>
#include <QTextTable>

/*!
    \fn FormAgregarPresupuesto::ponerTabla()
 */
void FormAgregarPresupuesto::ponerTabla()
{
 formLista->hide();
 if( formLista->getModelo()->rowCount() <= 1 )
 {
 	// no existen productos en realidad no hago nada
	return;
 }
 pre->generarTablaProductos( formLista->getModelo(), formLista->tituloTabla(), formLista->cabeceraColumnas() );
 ///@todo, ver bien si quiero hacerlo asi
}

#include <QMessageBox>
#include <QSqlRecord>
#include "mpresupuesto.h"
/*!
    \fn FormAgregarPresupuesto::guardar( bool cerrar )
 */
void FormAgregarPresupuesto::guardar( bool cerrar )
{
 // Verifico que esten todos los datos
 if( !RBCliente->isChecked() || !RBOtro->isChecked() )
 {
  QMessageBox::information( this, "Faltan Datos", "Por favor, elija un cliente o destinatario" );
  return;
 }
 if( CkBTitulo->isChecked() && LETitulo->text().isEmpty() )
 {
	QMessageBox::information( this, "Faltan Datos", "Por favor, ingrese el titulo personalizado" );
	return;
 }
 if( dSBTotal->value() <= 0 )
 {
	QMessageBox::information( this, "Faltan Datos", "Por favor, ingrese un total presupuestado" );
	return;
 }
 MPresupuesto *mod = new MPresupuesto( this );
 mod->setEditStrategy( QSqlTableModel::OnManualSubmit );
 QSqlRecord reg = mod->record();
 // le pongo los valores a el registro
 reg.setValue( "titulo", LETitulo->text() );
 reg.setValue( "total", dSBTotal->value() );
 if( RBOtro->isChecked() )
 {
  reg.setValue( "destinatario", LEOtro->text() );
 }
 else
 {
  //Busco el id del cliente
  //reg.setValue( "id_cliente", id_cliente );
 }
 if( cerrar )
 {
  this->close();
 }
}


/*!
    \fn FormAgregarPresupuesto::imprimir()
 */
void FormAgregarPresupuesto::imprimir()
{
 qWarning( "No implementado todavia" );
}


/*!
    \fn FormAgregarPresupuesto::guardarImprimir()
 */
void FormAgregarPresupuesto::guardarImprimir()
{
 guardar( false );
 imprimir();
}


/*!
    \fn FormAgregarPresupuesto::guardar()
 */
void FormAgregarPresupuesto::guardar()
{
 guardar( true );
}
