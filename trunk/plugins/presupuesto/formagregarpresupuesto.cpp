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
#include <QCompleter>
#include <QSqlQuery>
#include "mproductostotales.h"
#include "dproductostotales.h"
#include "NumeroComprobante.h"
#include "mpresupuesto.h"
#include "MItemPresupuesto.h"
#include "EReporte.h"
#include "mclientes.h"

FormAgregarPresupuesto::FormAgregarPresupuesto(QWidget* parent, Qt::WFlags fl)
: EVentana( parent, fl ), Ui::FormPresupuestoBase()
{

        setupUi(this);
        this->setAttribute( Qt::WA_DeleteOnClose );
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

         // Agrego las acciones
        addAction( ActGuardar );
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
        m = new MProductosTotales( this, CBProductos->listadoProductos() );
        m->calcularTotales( true );
        m->buscarPrecios( true );
        TVContenido->setModel( m );
        DProductosTotales *d = new DProductosTotales( TVContenido );
        d->setearListaProductos( m->listaProductos() );
        connect( m, SIGNAL( cambioListaProductos( MProductosTotales* ) ), d, SLOT( neceistoActualizarListaSlots( MProductosTotales* ) ) );
        TVContenido->setItemDelegateForColumn( 1, d );
        TVContenido->setSelectionBehavior( QAbstractItemView::SelectRows );
        TVContenido->horizontalHeader()->setResizeMode( QHeaderView::ResizeToContents );
        TVContenido->horizontalHeader()->setResizeMode( 1, QHeaderView::Stretch );
        TVContenido->horizontalHeader()->setMinimumSectionSize( 140 );
        TVContenido->setSortingEnabled( false );

        connect( CBProductos, SIGNAL( agregarProducto() ), this, SLOT( agregarProducto() ) );

        // Pongo los botones en funcionamiento
        PBAgregar->setIcon( QIcon( ":/imagenes/add.png" ) );
        PBAgregar->setText( "Agregar" );
        PBEliminar->setIcon( QIcon( ":/imagenes/eliminar.png" ) );
        PBEliminarTodo->setIcon( QIcon( ":/imagenes/eliminar.png" ) );

        connect( PBAgregar     , SIGNAL( clicked() ), this, SLOT( agregarProducto()    ) );
        connect( PBEliminar    , SIGNAL( clicked() ), this, SLOT( eliminarProducto()   ) );
        connect( PBEliminarTodo, SIGNAL( clicked() ), this, SLOT( borrarTodoProducto() ) );

        // Busco el siguiente numero de comprobante valido para un presupuesto
        LNumeroComprobante->setText( LNumeroComprobante->text() + "   <b>" + MPresupuesto::proximoComprobante().aCadena() + "</b>" );

        DSBCant->setValue( 1.0 );
        DSBCant->setPrefix( "" );
}

/*!
    \fn FormAgregarPresupuesto::cancelar()
        Elimina datos temporales y cierra el formulario
 */
void FormAgregarPresupuesto::cancelar()
{ this->close(); }


#include <QMessageBox>
#include <QSqlDatabase>
#include <QDir>
#include "mpresupuesto.h"
#include "EReporte.h"
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
 if( !(CBCliente->currentIndex() >= 0 ) ) {
     QMessageBox::information( this, "Error de destinatario", "El cliente no es valido o no existe un destinatario ingresado. Por favor coloque uno." );
     return;
 }
 // Inicio la transacción
 QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).transaction();
 MPresupuesto *mod = new MPresupuesto();

 int id_cliente = CBCliente->model()->data( CBCliente->model()->index( CBCliente->currentIndex() ,0 ) ).toInt();

 int id_presupuesto = mod->agregarPresupuesto( id_cliente,
                                               CBCliente->currentText(),
                                               LEDireccion->text(),
                                               dEFecha->dateTime(),
                                               m->total() );

 if( id_presupuesto == -1 ) {
     qDebug( "Error al intentar agregar un prespuesto." );
     QMessageBox::information( this, "Error", "No se pudo agregar el presupuesto. No se guardo nada" );
     return;
 }
 // tengo el id del presupuesto y procedo a guardar los datos de los items
 //////////////////////////////////////////////////////////////////////////
 // Guardo los items del presupuesto
 // elimino la fila de total
  m->calcularTotales( false );
 MItemPresupuesto *items = new MItemPresupuesto();
 for( int fila = 0; fila< TVContenido->model()->rowCount(); fila++ ) {
     if( !items->agregarItemPresupuesto( id_presupuesto,
                                         m->data( m->index( fila, 0 ), Qt::EditRole ).toDouble(), // Cantidad
                                         m->data( m->index( fila, 1 ), Qt::DisplayRole ).toString(), // Texto
                                         m->data( m->index( fila, 2 ), Qt::EditRole ).toDouble()  // Precio unitario
                                       ) ) {
         qDebug( QString( "No se pudo agregar el item %1 del presupuesto a la base de datos" ).arg( fila ).toLocal8Bit() );
         QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback();
         return;
     }
 }
 // Si llego hasta aca, termine de guardar todos los datos y ninguno fallo
 QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).commit();
 delete items;
 delete mod;
 // Imprimo el presupuesto
 ParameterList lista;
 lista.append( Parameter( "id_presupuesto", id_presupuesto ) );
 if( id_cliente < 0 ) {
     lista.append( Parameter( "cliente_existe", false ) );
     lista.append( Parameter( "direccion", LEDireccion->text() ) );
 } else if( id_cliente >= 0 ){
     lista.append( Parameter( "cliente_existe", true ) );
     if( id_cliente > 0 ) {
         lista.append( Parameter( "direccion", MClientes::direccionEntera( id_cliente ) ) );
     } else {
         lista.append( Parameter( "direccion", LEDireccion->text() ) );
     }
 }
 EReporte *rep = new EReporte( this );
 rep->presupuesto();
 if( rep->hacer( lista, false ) ) {
     QMessageBox::warning( this, "reporte", "Presupuesto impreso correctamente" );
 } else {
     QMessageBox::warning( this, "Error", "No se pudo hacer el reporte" );
 }
 if( cerrar )
 { this->close(); }
}


/*!
    \fn FormAgregarPresupuesto::guardar()
 */
void FormAgregarPresupuesto::guardar()
{ guardar( true ); }


/*!
    \fn FormAgregarPresupuesto::agregarProducto()
 */
void FormAgregarPresupuesto::agregarProducto()
{
    // Verificación previa
    if( DSBCant->value() == 0 )
    { QMessageBox::information( this, "Error de dato", "La cantidad a agregar debe ser mayor que cero", QMessageBox::Ok ); return; }
    if( CBProductos->currentText().isEmpty() )
    { QMessageBox::information( this, "Error de datos", "Ingrese un producto a agregar", QMessageBox::Ok ); return; }
    // Inserto el producto
    m->agregarNuevoProducto( DSBCant->value(), CBProductos->currentText() );

    // Reseteo los ingresos de producto
    DSBCant->setValue( 1.0 );
    CBProductos->setCurrentIndex( -1 );
    // Seteo el foco
    DSBCant->setFocus();
}

/*!
    \fn FormAgregarPresupuesto::eliminarProducto()
 */
void FormAgregarPresupuesto::eliminarProducto()
{
 QModelIndexList lista = TVContenido->selectionModel()->selectedRows();
 if( lista.size() < 1 ) {
     QMessageBox::warning( this, "Seleccione un item",
                     "Por favor, seleccione un item para eliminar",
                     QMessageBox::Ok, QMessageBox::Cancel );
     return;
 }
 int ret = QMessageBox::question( this, QString::fromUtf8( "¿Seguro?" ), QString( "Esta seguro que desea eliminar %1 elemento(s)?" ).arg( lista.size() ), QMessageBox::Ok, QMessageBox::Cancel );
 if( ret == QMessageBox::Ok ) {
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
 int ret = QMessageBox::question( this, QString::fromUtf8( "¿Seguro?" ), QString::fromUtf8( "¿Esta seguro que desea eliminar todos los elementos del prespuesto?" ), QMessageBox::Ok, QMessageBox::Cancel );
 if( ret == QMessageBox::Ok ) {
     int fin = m->rowCount() - 1;
     for( int i = 0; i <= fin; i++ ) { m->removeRow( i );  }
     TVContenido->update();
 }
}

#include <mclientes.h>
/*!
  \fn FormAgregarPresupuesto::cambioCliente( int id_combo )
  Slot llamado cada vez que el usuario cambia el contenido del combo de cliente o destinatario
  \param id_combo ID del combobox
 */
void FormAgregarPresupuesto::cambioCliente( int id_combo ) {
    int id_cliente = CBCliente->model()->data( CBCliente->model()->index( id_combo, 0 ), Qt::EditRole ).toInt();
    LEDireccion->setText( MClientes::direccionEntera( id_cliente ) );
}
