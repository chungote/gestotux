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
#include "definiciones.h"
#include "eactcerrar.h"
#include "eactguardar.h"
#include "mventa.h"
#include "mventaproducto.h"
#include "eregistroplugins.h"
#include "../CtaCte/mcuentacorriente.h"
#include "../CtaCte/mitemcuentacorriente.h"
#include "../productos/mproductos.h"
#include "preferencias.h"
#include "EReporte.h"

FormAgregarVenta::FormAgregarVenta ( QWidget* parent, Qt::WFlags fl )
: EVentana ( parent, fl ), Ui::FormAgregarVentaBase()
{
        setupUi( this );
        this->setObjectName( "formagregarcompra" );
        this->setWindowTitle( "Agregar Venta" );
        this->setWindowIcon( QIcon(":/imagenes/factura-nueva.png" ) );

        PBAgregarProducto->setIcon( QIcon( ":/imagenes/add.png" ) );
        PBAgregarProducto->setText( "Agregar Producto" );

        connect( PBAgregarProducto, SIGNAL( clicked() ), this, SLOT( agregarProducto() ) );

        // Inicio los modelos
        CBCliente->setModel( new EMCliente( CBCliente ) );
        CBCliente->setModelColumn( 1 );
        CBCliente->setEditable( true );

        // Rellenar los items de productos
        QSqlQueryModel *cola = new QSqlQueryModel( this );
        cola->setQuery( "SELECT id, nombre FROM producto" );
        CBProducto->setModel( cola );
        CBProducto->setModelColumn( 1 );
        CBProducto->setSizeAdjustPolicy( QComboBox::AdjustToContentsOnFirstShow );
        CBProducto->setEditable( true );
        CBProducto->completer()->setCompletionMode( QCompleter::PopupCompletion );
        CBProducto->setCurrentIndex( -1 );

        DEFecha->setMaximumDate( QDate::currentDate() );
        DEFecha->setDate( QDate::currentDate() );

        // Modelo del tableview
        mcp = new MProductosTotales( TVProductos );
        mcp->calcularTotales( true );
        mcp->buscarPrecios( true );
        TVProductos->setModel( mcp );
        TVProductos->setItemDelegate( new DProductosTotales( TVProductos ) );
        TVProductos->setAlternatingRowColors( true );
        TVProductos->setSelectionBehavior( QAbstractItemView::SelectRows );
        TVProductos->horizontalHeader()->setResizeMode( QHeaderView::Stretch );

        this->addAction( new EActGuardar( this ) );
        this->addAction( new EActCerrar( this ) );

        connect( CBCliente, SIGNAL( currentIndexChanged( int ) ), this, SLOT( cambioCliente( int ) ) );

        DSBCant->setValue( 1.0 );
        DSBCant->setPrefix( "" );

        // Verifico si la venta a cta corriente esta habilitada
        if( !preferencias::getInstancia()->value( "Preferencias/CtaCte/habilitada" ).toBool() )
        {
                GBFormaPago->setVisible( false );
                RBContado->setChecked( true );
        }


}

FormAgregarVenta::~FormAgregarVenta()
{
}


/*!
    \fn FormAgregarVenta::agregarProducto()
 */
void FormAgregarVenta::agregarProducto()
{
 // Verificaci�n previa
 if( DSBCant->value() == 0 )
 { QMessageBox::information( this, "Error de dato", "La cantidad a agregar debe ser mayor que cero" ); return; }
 // Inserto la fila
 mcp->insertRow( -1 );
 // Pongo el producto
 QModelIndex indice = mcp->index( mcp->rowCount()-2, 0 );
 int id_producto = CBProducto->model()->data( CBProducto->model()->index( CBProducto->currentIndex(), 0 ) , Qt::EditRole ).toInt();
 mcp->setData( indice, id_producto, Qt::EditRole );
 // Pongo la cantidad
 indice = mcp->index( mcp->rowCount()-2, 2 );
 mcp->setData( indice, DSBCant->value(), Qt::EditRole );
 // Edito el item que agrege
 //indice = mcp->index( mcp->rowCount()-2 , 1 );
 //TVProductos->setCurrentIndex( indice );
 //TVProductos->edit( indice );
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
                { TVProductos->model()->removeRow( indice.row() ); }
        }
 }
 return;
}


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
 mcp->calcularTotales( false );
 if( mcp->rowCount() < 1 )
 {
  QMessageBox::warning( this, "Faltan Datos" , "Por favor, ingrese una cantidad de productos vendidos distinta de cero para esta venta" );
  mcp->calcularTotales( true );
  return;
 }
 double total_calculado = mcp->total();
 //Inicio una transacci�n
 QSqlDatabase::database().transaction();
 //seteo el modelo para que no calcule totales y subtotales
 mcp->calcularTotales( false );
 // veo el id del proveedor
 int id_cliente = CBCliente->model()->data( CBCliente->model()->index( CBCliente->currentIndex(), 0 ) , Qt::EditRole ).toInt();
  int id_forma_pago = -1;
 if( RBCtaCte->isChecked() )
 {
   id_forma_pago = VENTA_CTACTE;
 }
 else if( RBContado->isChecked() )
 {
   id_forma_pago = VENTA_CONTADO;
 }
 else if( RBCuotas->isChecked() )
 {
     id_forma_pago = VENTA_CUOTAS;
 }
 QString num_comprobante = LENumComp->text();
 // Genero la compra
 MVenta *compra = new MVenta( this, false );
 if( compra->agregarVenta( DEFecha->date(), id_cliente, id_forma_pago, num_comprobante ) == false )
 { QSqlDatabase::database().rollback(); return; }
 // Busco el ultimo id de compra
 int id_venta = compra->ultimoId();
 // recorro el modelo y guardo los datos
 MVentaProducto *m = new MVentaProducto( this );
 for( int i= 0; i<mcp->rowCount(); i++ )
 {
  QSqlRecord registro = m->record();
  registro.setValue( "id_venta", id_venta );
  registro.setValue( "id_producto", mcp->data( mcp->index( i, 0 ), Qt::EditRole ) );
  registro.setValue( "precio_venta", mcp->data( mcp->index( i, 1 ), Qt::EditRole ) );
  registro.setValue( "cantidad", mcp->data( mcp->index( i, 2 ), Qt::EditRole ) );
  if( m->insertRecord( -1, registro ) == false ) {
   qDebug( "Error al insertar Registro" );
  }
  else
  {
   // Disminuyo el stock
  bool devuelve = MProductos::modificarStock( mcp->data( mcp->index( i, 0 ), Qt::EditRole ).toInt() , mcp->data( mcp->index( i, 2 ), Qt::EditRole ).toDouble() );
  if( !devuelve )
  { qWarning( "Error al intentar disminuir el stock de un producto" ); ///@ todo Cancelar todo return; }
     }
  }
 }
 m->submit();
 // Si la venta es a cuenta corriente actualizo la cuenta corriente
 if( ERegistroPlugins::getInstancia()->existePlugin( "ctacte" ) && id_forma_pago == VENTA_CTACTE )
 {
  // Si se ingresa aqui el cliente tiene cuenta corriente
  // Busco el numero de cuenta
  QString num_ctacte = MCuentaCorriente::obtenerNumeroCuentaCorriente( id_cliente );
  switch( MCuentaCorriente::verificarSaldo( num_ctacte, total_calculado ) )
  {
        case CTACTE_LIMITE_EXCEDIDO:
        {
                QMessageBox::information( this, "Limite de Saldo Excedido", "El limite de saldo para este cliente ha sido excedido. No se hara la factura" );
                QSqlDatabase::database().rollback();
                return;
                break;
        }
        case CTACTE_LIMITE_ENLIMITE:
        {
                QMessageBox::information( this, "Limite de Saldo Alcanzado", "El limite de saldo para este cliente ha sido alcanzado." );
                break;
        }
        case E_CTACTE_BUSCAR_LIMITE:
        {
                QSqlDatabase::database().rollback();
                return;
                break;
        }
        default:
        { break; }
  }
  if( !MItemCuentaCorriente::agregarOperacion(    num_ctacte,
                                                 num_comprobante,
                                                 id_venta,
                                                 MItemCuentaCorriente::Factura,
                                                 DEFecha->date(),
                                                 "Venta a CtaCte",
                                                 total_calculado ) )
  { QSqlDatabase::database().rollback(); qWarning( "Error al actualizar la cuenta corriente - inserccion de item" ); }
 }
 // Actualizar la cuenta general del programa
 ///@todo Actualizar la cuenta general del programa
 // listo
  if( QSqlDatabase::database().commit() ) {
   // Ver si quiere ver la factura o imprimirla
   int respuesta = QMessageBox::question( this, "Correcto", "La venta se ha registrado correctamente. Desea imprimir un comprobante de venta?",
                                     QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel );
   switch( respuesta )
   {
    case QMessageBox::Yes:
    {
     ParameterList lista;
     lista.append( "id_factura", id_venta );
     orReport *rep = new orReport( "factura", lista );
     rep->print();
     break;
    }
    case QMessageBox::No:
    case QMessageBox::Cancel:
    {
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
void FormAgregarVenta::cambioCliente( int id_combo )
{
 (void)id_combo;
 if( ERegistroPlugins::getInstancia()->existePlugin( "ctacte" ) )
 {
  int id_cliente = CBCliente->model()->data( CBCliente->model()->index( CBCliente->currentIndex(), 0 ) , Qt::EditRole ).toInt();
  if( id_cliente == 0 ) {
      // Es el Consumidor Final
      RBContado->setChecked( true );
      GBFormaPago->setEnabled( false );
      return;
  }
  QString num_cuenta = MCuentaCorriente::obtenerNumeroCuentaCorriente( id_cliente );
  if( num_cuenta.toInt() > 0 )
  {
   RBCtaCte->setEnabled( true );
   return;
  }
  else
  {
   RBContado->setChecked( true );
   RBCtaCte->setEnabled( false );
   return;
  }
 }
}