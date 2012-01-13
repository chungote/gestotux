/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   				   *
 *   juiraze@yahoo.com.ar   						   *
 *                                                                         *
 *    This program is free software; you can redistribute it and/or modify  *
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
#include "mproductostotales.h"
#include "dproductostotales.h"
#include "emcliente.h"
#include <QTableView>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QCompleter>
#include "eactcerrar.h"
#include "eactguardar.h"
#include "eregistroplugins.h"
#include "../CtaCte/mcuentacorriente.h"
#include "../CtaCte/mitemcuentacorriente.h"
#include "../productos/mproductos.h"
#include "preferencias.h"
#include "EReporte.h"
#include "MFactura.h"
#include "mitemfactura.h"
#include "NumeroComprobante.h"
#include "ecbproductos.h"

FormAgregarVenta::FormAgregarVenta ( QWidget* parent, Qt::WFlags fl )
: EVentana ( parent, fl ), Ui::FormAgregarVentaBase()
{
        setupUi( this );
        this->setObjectName( "formagregarcompra" );
        this->setWindowTitle( "Agregar Venta" );
        this->setWindowIcon( QIcon(":/imagenes/factura-nueva.png" ) );

        PBAgregarProducto->setIcon( QIcon( ":/imagenes/add.png" ) );
        PBAgregarProducto->setText( "Agregar Producto" );
        PBEliminar->setIcon( QIcon( ":/imagenes/eliminar.png" ) );
        PBEliminar->setText( "Eliminar seleccion" );
        PBEliminarTodo->setIcon( QIcon( ":/imagenes/eliminar.png" ) );
        PBEliminarTodo->setText( "Eliminar todo");

        connect( PBAgregarProducto, SIGNAL( clicked() ), this, SLOT( agregarProducto() ) );

        // Inicio los modelos
        CBCliente->setEditable( true );

        connect( CBProducto, SIGNAL( agregarProducto() ), this, SLOT( agregarProducto() ) );

        DEFecha->setMaximumDate( QDate::currentDate() );
        DEFecha->setDate( QDate::currentDate() );

        // Modelo del tableview
        mcp = new MProductosTotales( TVProductos, CBProducto->listadoProductos() );
        mcp->calcularTotales( true );
        if( preferencias::getInstancia()->value( "Preferencias/Ventas/buscarPrecio", true ).toBool() )
            mcp->buscarPrecios( true );
        TVProductos->setModel( mcp );
        TVProductos->setItemDelegate( new DProductosTotales( TVProductos ) );
        TVProductos->setAlternatingRowColors( true );
        TVProductos->setSelectionBehavior( QAbstractItemView::SelectRows );
        TVProductos->horizontalHeader()->setResizeMode( QHeaderView::ResizeToContents );
        TVProductos->horizontalHeader()->setResizeMode( 1, QHeaderView::Stretch );
        TVProductos->horizontalHeader()->setMinimumSectionSize( 140 );
        TVProductos->setSortingEnabled( false );


        this->addAction( new EActGuardar( this ) );
        this->addAction( new EActCerrar( this ) );

        connect( CBCliente, SIGNAL( currentIndexChanged( int ) ), this, SLOT( cambioCliente( int ) ) );

        connect( PBEliminar, SIGNAL( clicked() ), this, SLOT( eliminarProducto() ) );
        connect( PBEliminarTodo, SIGNAL( clicked() ), this, SLOT( eliminarTodo() ) );

        DSBCant->setValue( 1.0 );
        DSBCant->setPrefix( "" );

        // Verifico si la venta a cta corriente esta habilitada
        preferencias *p = preferencias::getInstancia();
        p->inicio();
        p->beginGroup( "Preferencias" );
        p->beginGroup( "CtaCte" );
        if( !p->value( "habilitada" ).toBool() )
        {
                GBFormaPago->setVisible( false );
                RBContado->setChecked( true );
        }
        p->endGroup(); p->endGroup(); p=0;

        // deshabilito el item de cuotas por no estar programado
        RBCuotas->setVisible( false );

        // Coloco el proximo numero de comprobante
        LNumeroComprobante->setText( LNumeroComprobante->text().append( "       <b>" ).append( MFactura::proximoComprobante().aCadena() ).append( "</b>" ) );

}


/*!
    \fn FormAgregarVenta::agregarProducto()
 */
void FormAgregarVenta::agregarProducto()
{
 // Verificación previa
 if( DSBCant->value() == 0 )
 { QMessageBox::information( this, "Error de dato", "La cantidad a agregar debe ser mayor que cero" ); return; }

 if( CBProducto->currentText().isEmpty() )
 { QMessageBox::information( this, "Error de datos", "Por favor, ingrese un producto", QMessageBox::Ok ); return; }

 CBProducto->verificarExiste();
 mcp->agregarNuevoProducto( DSBCant->value(), CBProducto->idActual() );

 // Reseteo los ingresos de producto
 DSBCant->setValue( 1.0 );
 CBProducto->setCurrentIndex( -1 );
 // Seteo el foco
 DSBCant->setFocus();
}


/*!
    \fn FormAgregarVenta::eliminarProducto()
 */
void FormAgregarVenta::eliminarProducto()
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
 // cuento las filas distintas
 QModelIndex indice;
 int ultimo = -1;
 foreach( indice, indices )
 {
  if( indice.row() == ultimo )
  {
   indices.removeOne( indice );
  }
  else
  {
   ultimo = indice.row();
  }
 }
 //Hacer dialogo de confirmacion..
 int ret = QMessageBox::warning( this, "Esta seguro?",
                   QString( "Esta seguro de eliminar %1 item?").arg( indices.size() ),
                   "Si", "No" );
 if ( ret == 0 )
 {
        QModelIndex indice;
        foreach( indice, indices )
        {
                if( indice.isValid() )
                {
                    mcp->removeRow( indice.row() );
                } /*else {
                    qDebug( " Indice no valido! - " );
                }*/
        }
 }
 TVProductos->update();
 return;
}

/*!
    \fn FormAgregarVenta::eliminarTodo()
    Elimina todos los productos de la factura
 */
void FormAgregarVenta::eliminarTodo()
{
 //Preguntar al usuario si esta seguro
 //Hacer dialogo de confirmacion..
 int ret = QMessageBox::warning( this, "Esta seguro?",
                   QString( "Esta seguro de eliminar todos los items?"),
                   "Si", "No" );
 if ( ret == 0 )
 {
     int fin = mcp->rowCount() - 1;
     for( int i = 0; i <= fin; i++ ) { mcp->removeRow( i ); }
 }
 TVProductos->update();
 return;
}

#include "mclientes.h"
/*!
    \fn FormAgregarVenta::guardar()
 */
void FormAgregarVenta::guardar()
{
 if( CBCliente->currentIndex() == -1 )
 {
  QMessageBox::warning( this, "Faltan Datos" , "Por favor, ingrese un cliente para esta venta" );
  return;
 }
 if( !DEFecha->date().isValid() )
 {
  QMessageBox::warning( this, "Faltan Datos" , "Por favor, ingrese una fecha valida para esta venta" );
  return;
 }
 if( !( RBContado->isChecked() || RBCuotas->isChecked() || RBCtaCte->isChecked()  ) ) {
     QMessageBox::warning( this, "Faltan Datos" , "Por favor, elija una forma de pago para esta venta" );
     return;
 }
 /// @todo ver si esta restriccion tiene sentido
 /*if( CBCliente->currentIndex() == 0 && LEDireccion->text().isEmpty() ) {
     QMessageBox::warning( this, "Error", QString::fromUtf8("No ingreso una dirección para el cliente" ) );
     return;
 }*/
 mcp->calcularTotales( false );
 if( mcp->rowCount() < 1 )
 {
  QMessageBox::warning( this, "Faltan Datos" , "Por favor, ingrese una cantidad de productos vendidos distinta de cero para esta venta" );
  mcp->calcularTotales( true );
  return;
 }
 // Verifico que no se le venda a cuenta corriente a un cliente consumidor final
 if( RBCtaCte->isChecked() && CBCliente->currentIndex() <=  0 ) {
     QMessageBox::warning( this, "Error", "No se puede vender a consumidor final en cuenta corriente. Se eligirá pago a contado" );
     RBCtaCte->setChecked( false );
     RBContado->setChecked( true );
 }
 // Remuevo el texto que dice "Observaciones:"
 QString observacion = PTEObservaciones->toPlainText();
 observacion.remove( "Observaciones: " );
 //Inicio una transacción
 QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).transaction();
 //seteo el modelo para que no calcule totales y subtotales
 mcp->calcularTotales( false );
 // veo el id del proveedor
 int id_cliente = CBCliente->idClienteActual();
 MFactura::FormaPago id_forma_pago;
 if( RBCtaCte->isChecked() && RBCtaCte->isEnabled() )
 {
   id_forma_pago = MFactura::CuentaCorriente;
   //qDebug( "MFactura::CuentaCorriente" );
 }
 else if( RBContado->isChecked() )
 {
   id_forma_pago = MFactura::Contado;
   //qDebug( "MFactura::Contado" );
 }
 else if( RBCuotas->isChecked() )
 {
     id_forma_pago = MFactura::Cuotas;
     //qDebug( "MFactura::Cuotas" );
 } else {
     QMessageBox::warning( this, "Faltan Datos" , "Por favor, elija una forma de pago para esta venta" );
     mcp->calcularTotales( true );
     return;
 }
 // Genero la venta
 MFactura *venta = new MFactura();
 int id_venta = venta->agregarVenta( DEFecha->dateTime(), id_cliente, id_forma_pago, mcp, observacion );
 if( id_venta == -1 ) {
    QMessageBox::information( this, "Error", "No se pudo agregar la venta" );
    QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback();
    return;
 }
 if( QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).commit() ) {
   // Ver si quiere ver la factura o imprimirla
   int respuesta = QMessageBox::question( this, "Correcto", "La venta se ha registrado correctamente. Desea imprimir un comprobante de venta?",
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel );
   switch( respuesta )
   {
    case QMessageBox::Yes:
    {
     ParameterList lista;
     lista.append( "cliente", CBCliente->currentText());
     lista.append( "direccion", LEDireccion->text() );
     lista.append( "id_factura", id_venta );

     EReporte *rep = new EReporte( this );
     rep->factura();
     if( !rep->hacer( lista ) ) {
         QMessageBox::critical( this, "Error", "No se pudo imprimir el reporte. Consulte con el administrador del sistema" );
         return;
     }
     break;
    }
    case QMessageBox::No:
    case QMessageBox::Cancel:
    {
           //qDebug( "Respondio no o cancelar" );
           break;
    }
   }
   this->close();
   return;

  } else {
   QMessageBox::information( this, "Incorrecto" , "La venta no se pudo guardar correctamente" );
   return;
  }
}

/*!
    \fn FormAgregarVenta::cambioCliente( int id_combo )
        Slot llamado cada vez que cambia el cliente para verificar si tiene cuenta corriente habilitada
        @param id_combo Indice en la lista de combobox que indica el cliente
 */
void FormAgregarVenta::cambioCliente( int /*id_combo*/ )
{
 // Busco la dirección
 int id_cliente = CBCliente->idClienteActual();
 if( id_cliente > 0 ) { // 0 => Consumidor final.
     LEDireccion->setText( MClientes::direccionEntera( id_cliente ) );
     // Veo si esta habilitado el cliente con cueta corriente y el plugin esta cargado
     if( ERegistroPlugins::getInstancia()->existePlugin( "ctacte" ) )
     {
         if( MCuentaCorriente::existeCuentaCliente( id_cliente ) )
         {
             if( !MCuentaCorriente::suspendida( id_cliente ) ) {
                RBCtaCte->setEnabled( true );
                GBFormaPago->setEnabled( true );
             } else {
                 qDebug( "Cuenta corriente suspendida" );
                 RBContado->setChecked( true );
                 RBCtaCte->setEnabled( false );
             }
         }
         else
         {
           // qDebug( "No se encontro una cuenta corriente para el cliente." );
            RBContado->setChecked( true );
            RBCtaCte->setEnabled( false );
         }
     }

 } else {
     //qDebug( "Cliente consumidor final - Sin direccion" );
     RBContado->setChecked( true );
     RBCtaCte->setEnabled( false );
 }
 return;
}
