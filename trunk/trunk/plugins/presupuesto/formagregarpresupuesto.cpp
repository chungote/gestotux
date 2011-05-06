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

#include "emcliente.h"
#include <QDate>
#include <QSqlError>
#include <QHeaderView>
#include "eeditor.h"
#include "presupuesto.h"
#include "mproductostotales.h"
#include "dproductostotales.h"
#include "NumeroComprobante.h"
#include "mpresupuesto.h"

FormAgregarPresupuesto::FormAgregarPresupuesto(QWidget* parent, Qt::WFlags fl)
: EVentana( parent, fl ), Ui::FormPresupuestoBase()
{
        // Inicializo el presupeusto!
        pre = new Presupuesto( this );
        this->setAttribute( Qt::WA_DeleteOnClose );
        setupUi(this);
        this->setObjectName( "FormAgregarPresupuesto" );
        this->setWindowTitle( "Agregar Presupuesto" );
        this->setWindowIcon( QIcon( ":/imagenes/presupuesto-nuevo.png" ) );

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
        addAction( ActGuardarImprimir );
        addAction( ActImprimir );
        addAction( ActCancelar );

        // Seteo la lista de clientes
        CBCliente->setModel( new EMCliente( CBCliente ) );
        CBCliente->setModelColumn( 1 );
        CBCliente->setCurrentIndex( -1 );
        // Permito la creacion para un no cliente
        CBCliente->setAutoCompletion( true );
        CBCliente->setEditable( true );

        // Habilita el buscador de direccion.
        connect( CBCliente, SIGNAL( currentIndexChanged( int ) ), this, SLOT( cambioCliente( int ) ) );

        // Pongo la fecha actual
        dEFecha->setDate( QDate::currentDate() );

        // Pongo el sistema de relleno
        m = new MProductosTotales( this );
        m->calcularTotales( true );
        m->buscarPrecios( true );
        TVContenido->setModel( m );
        DProductosTotales *d = new DProductosTotales( TVContenido );
        d->setearListaProductos( m->listaProductos() );
        connect( m, SIGNAL( cambioListaProductos( MProductosTotales* ) ), d, SLOT( neceistoActualizarListaSlots( MProductosTotales* ) ) );
        TVContenido->setItemDelegateForColumn( 1, d );
        TVContenido->horizontalHeader()->setResizeMode( QHeaderView::Stretch );

        // Pongo los botones en funcionamiento
        PBAgregar->setIcon( QIcon( ":/imagenes/add.png" ) );
        PBEliminar->setIcon( QIcon( ":/imagenes/eliminar.png" ) );
        PBEliminarTodo->setIcon( QIcon( ":/imagenes/eliminar.png" ) );

        connect( PBAgregar     , SIGNAL( clicked() ), this, SLOT( agregarProducto()    ) );
        connect( PBEliminar    , SIGNAL( clicked() ), this, SLOT( eliminarProducto()   ) );
        connect( PBEliminarTodo, SIGNAL( clicked() ), this, SLOT( borrarTodoProducto() ) );

        // Busco el siguiente numero de comprobante valido para un presupuesto
        LNumeroComprobante->setText( LNumeroComprobante->text() + ":    " + MPresupuesto::proximoComprobante().aCadena() );
}

/*!
    \fn FormAgregarPresupuesto::cancelar()
        Elimina datos temporales y cierra el formulario
 */
void FormAgregarPresupuesto::cancelar()
{
    this->close();
}


#include <QMessageBox>
#include <QSqlDatabase>
#include "mpresupuesto.h"
/*!
    \fn FormAgregarPresupuesto::guardar( bool cerrar )
 */
void FormAgregarPresupuesto::guardar( bool cerrar )
{
 // Verifico que esten todos los datos - fecha valida
 if( !dEFecha->date().isValid() ) {
     QMessageBox::information( this, "Error de fecha", "La fecha no es valida. Ingrese una correcta." );
     return;
 }
 // Algun cliente seleccionado o agregado
 if( !CBCliente->currentIndex() > 0 ) {
     QMessageBox::information( this, "Error de destinatario", "El cliente no es valido o no existe un destinatario ingresado. Por favor coloque uno." );
     return;
 }
 QMessageBox::critical( this, "No implementado", "Todavía no se implemento esto!" );
 // Inicio la transacción
 /*QSqlDatabase::database().transaction();
 MPresupuesto *mod = new MPresupuesto( this );

 int id_cliente = CBCliente->model()->data( CBCliente->model()->index( CBCliente->currentIndex() ,0 ) ).toInt();

 int id_presupuesto = -1;

 if( mod->agregarPrespuesto(
             id_cliente,
             CBCliente->currentText(),
             LEDireccion->text(),
             dEFecha->dateTime() ) ) {
     // Guardo el id del presupuesto recién agregado para los datos
     id_presupuesto = mod->ultimoIdInsertado();
 } else {
     qDebug( "Error al intentar agregar un prespuesto." );
     QMessageBox::Information( this, "Error", "No se pudo agregar el presupuesto. No se guardo nada" );
     return;
 }
 if( cerrar )
 {
  this->close();
 }*/
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
 //guardar( false );
 //imprimir();
 qWarning( "No implementado todavia" );
}


/*!
    \fn FormAgregarPresupuesto::guardar()
 */
void FormAgregarPresupuesto::guardar()
{
 //guardar( true );
 qWarning( "No implementado todavia" );
}

/*!
    \fn FormAgregarPresupuesto::agregarProducto()
 */
void FormAgregarPresupuesto::agregarProducto()
{  m->insertRow( -1 ); }

/*!
    \fn FormAgregarPresupuesto::eliminarProducto()
 */
void FormAgregarPresupuesto::eliminarProducto()
{
 QModelIndexList lista = TVContenido->selectionModel()->selectedRows();
 int ret = QMessageBox::question( this, "¿Seguro?",QString( "Esta seguro que desea eliminar %1 elemento(s)?" ).arg( lista.size() ) );
 if( ret == QMessageBox::Accepted ) {
     foreach( QModelIndex item, lista )
     {
        if( item.isValid() ) {
            m->removeRow( item.row() );
        }
     }
 }
}

/*!
    \fn FormAgregarPresupuesto::borrarTodoProducto()
 */
void FormAgregarPresupuesto::borrarTodoProducto()
{
 int ret = QMessageBox::question( this, "¿Seguro?", "Esta seguro que desea eliminar todos los elementos del prespuesto?" );
 if( ret == QMessageBox::Accepted ) {
         TVContenido->model()->removeRows( 0, TVContenido->model()->rowCount() );
 }
}

#include <mclientes.h>
/*!
  \fn FormAgregarPresupuesto::cambioCliente( int id_combo )
  Slot llamado cada vez que el usuario cambia el contenido del combo de cliente o destinatario
  @param id_combo ID del combobox
 */
void FormAgregarPresupuesto::cambioCliente( int id_combo ) {
   /// @todo agregar cambio de direccion
    int id_cliente = CBCliente->model()->data( CBCliente->model()->index( id_combo, 0 ), Qt::EditRole ).toInt();
    LEDireccion->setText( MClientes::direccionEntera( id_cliente ) );
}
