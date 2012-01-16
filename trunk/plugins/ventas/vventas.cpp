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
#include "vventas.h"

#include "eactcerrar.h"
#include "MFactura.h"
#include <QIcon>
#include <QTableView>
#include "MVFacturas.h"
#include <QMessageBox>
#include <QInputDialog>
#include "EReporte.h"


VVentas::VVentas(QWidget *parent)
 : EVLista(parent)
{
    this->setObjectName( "ListaFacturas" );
    this->setWindowTitle( "Lista de Facturas" );
    this->setWindowIcon( QIcon( ":/imagenes/factura.png" ) );

    this->modelo = new MVFacturas( this->vista );
    this->vista->setModel( this->modelo );

    this->vista->hideColumn( 0 );
    this->vista->hideColumn( 6 );
    this->vista->setAlternatingRowColors( true );

    QAction *ActPagar = new QAction( this );
    ActPagar->setText( "Pagar" );
    ActPagar->setIcon( QIcon( ":/imagenes/pagarfactura.png" ) );
    ActPagar->setStatusTip( "Genera un recibo por las facturas seleccionadas." );
    connect( ActPagar, SIGNAL( triggered() ), this, SLOT( pagar() ) );

    QAction *ActAnular = new QAction( this );
    ActAnular->setText( "Anular" );
    ActAnular->setIcon( QIcon( ":/imagenes/anularfactura.png" ) );
    ActAnular->setStatusTip( "Anula las facturas seleccionadas" );
    connect( ActAnular, SIGNAL( triggered() ), this, SLOT( anular() ) );

    QAction *ActVerAnuladas = new QAction( this );
    ActVerAnuladas->setText( "Ver anuladas" );
    ActVerAnuladas->setStatusTip( "Muestra o oculta las facturas anuladas" );
    ActVerAnuladas->setIcon( QIcon( ":/imagenes/verfacturaanuladas.png" ) );
    ActVerAnuladas->setCheckable( true );
    ActVerAnuladas->setChecked( true );
    connect( ActVerAnuladas, SIGNAL( toggled( bool ) ), this, SLOT( cambioVerAnuladas( bool ) ) );

    ActAgregar->setIcon( QIcon( ":/imagenes/facturanueva.png" ) );

    QAction *ActSep = new QAction( this );
    ActSep->setSeparator( true );

    ActVerItems = new QAction( this );
    ActVerItems->setText( "Ver items" );
    ActVerItems->setStatusTip( "Muestra el listado de items de la factura" );
    connect( ActVerItems, SIGNAL( triggered() ), this, SLOT( verItems() ) );

    //agregarFiltroBusqueda( "Numero de Factura", " ``" );
    agregarFiltroBusqueda( "Numero de Cliente", " `id_cliente` = '%%1%' " );
    agregarFiltroBusqueda( "Fecha", " `fecha` = '%%1%' ");
    habilitarBusqueda();

    this->addAction( ActAgregar );
    this->addAction( ActVerItems );
    //this->addAction( ActPagar );
    this->addAction( ActAnular );
    this->addAction( ActSep );
    this->addAction( ActVerAnuladas );
    this->addAction( ActBuscar );
    this->addAction( ActVerTodos );
    this->addAction( ActCerrar );

}

#include "formagregarventa.h"
void VVentas::agregar()
{ emit agregarVentana( new FormAgregarVenta() ); }

void VVentas::eliminar()
{ return; }

void VVentas::imprimir()
{ return; }

void VVentas::modificar()
{ return; }

void VVentas::anular()
{
    // Busco todos los IDs a anular
    if( this->modelo->rowCount() == 0 ) {
        // error, nada seleccionado....
        // Solicito el numero de factura
        bool ok = false;
        QString numero = QInputDialog::getText( this, "Ingrese numero", "Numero de Factura:", QLineEdit::Normal, QString(), &ok );
        if( ok ) {
            int id_factura = MFactura::idFacturaPorComprobante( numero );
            if( id_factura != -1 ) {
                ok = false;
                QString razon = QInputDialog::getText( this, "Ingrese razon", QString::fromUtf8( "Ingrese razon de anulación" ), QLineEdit::Normal, QString(), &ok );
                if( ok ) {
                    this->imprimirAnulacion( id_factura, razon, numero ); // Este metodo tiene el mfactura::anular factura
                }
            }
        }
        return;
    }
    QModelIndexList lista = this->vista->selectionModel()->selectedRows();
    if( lista.size() < 1 ) {
        QMessageBox::warning( this, "Seleccione un item",
                        "Por favor, seleccione al menos un item para anular",
                        QMessageBox::Ok );
        return;
    }
    foreach( QModelIndex indice, lista ) {
        bool ok = false;
        QString numero = this->modelo->data( this->modelo->index( indice.row(), 1 ) ).toString();
        QString razon = QInputDialog::getText( this, "Ingrese razon", QString::fromUtf8( "Ingrese razon de anulación" ), QLineEdit::Normal, QString(), &ok );
        int id_factura = this->modelo->data( this->modelo->index( indice.row(), 0 ) ).toInt();
        if( ok && !razon.isEmpty() ) {
            this->imprimirAnulacion( id_factura, razon, numero ); // Este metodo tiene el mfactura::anular factura
        }

    }
    this->modelo->select();
    return;
}

void VVentas::pagar()
{
    return;
    // Busco todos los IDs a pagar
    QModelIndexList lista = this->vista->selectionModel()->selectedRows();
    if( lista.size() < 1 ) {
        QMessageBox::warning( this, "Seleccione un item",
                        "Por favor, seleccione al menos un item para pagar.",
                        QMessageBox::Ok );
        return;
    }
    // Busco los datos de las facturas
    double total = 0;
    QString texto_recibo = "Pago de las factura";
    if( lista.size() > 1 ) { texto_recibo.append( "s" ); }
    foreach( QModelIndex indice, lista ) {
        total += this->modelo->data( this->modelo->index( indice.row(), 5 ) ).toDouble();
        texto_recibo.append( "#" );
        texto_recibo.append( this->modelo->data( this->modelo->index( indice.row(), 1 ) ).toString() );
        texto_recibo.append( '\n' );
    }
    // Abro la ventana del recibo
    /*FormAgregarRecibo *f = new FormAgregarRecibo();
    f->TETexto->setText( texto_recibo );
    f->dSBPagado->setValue( total );
    emit agregarVentana( f );*/
    return;
}

void VVentas::cambioVerAnuladas( bool parametro )
{ qobject_cast<MVFacturas *>(this->modelo)->verAnuladas( !parametro ); }

#include "vitemfactura.h"
void VVentas::verItems()
{
    // Busco todos los IDs a pagar
    QModelIndexList lista = this->vista->selectionModel()->selectedRows();
    if( lista.size() < 1 ) {
        QMessageBox::warning( this, "Seleccione un item",
                        "Por favor, seleccione al menos un item para ver sus items.",
                        QMessageBox::Ok );
        return;
    }
    QModelIndex indice = lista.first();
    VItemFactura *f = new VItemFactura();
    f->setearIdFactura( indice.model()->data( indice.model()->index( indice.row(), 0 ), Qt::EditRole ).toInt() );
    emit agregarVentana( f );
}

/*!
 * \fn VVentas::imprimirAnulacion( const int id_factura, const QString razon, const QString numero )
 * Anula la factura e imprime el reporte correspondiente
 * \param id_factura ID de la factura a anular
 * \param razon Razon por la cual se anula
 * \param numero Identificador de comprobante que se pasa para el cuadro de dialogo
 */
void VVentas::imprimirAnulacion( const int id_factura, const QString razon, const QString numero )
{
    if( MFactura::anularFactura( id_factura, razon, QDateTime::currentDateTime() ) ) {
        int ret = QMessageBox::question( this, "Correcto", QString::fromUtf8( "La Factura %1 ha sido anulada correctamente. <br /> ¿Desea imprimir la anulaciòn?" ).arg( numero ), QMessageBox::Yes, QMessageBox::No );
        if( ret == QMessageBox::Yes ) {
            QMessageBox::information( this, "Esperando", QString::fromUtf8( "Por favor, ingrese la factura en la impresora para imprimir la anulaciòn. <br /> Presione OK para enviar a imprimir la anulacion" ), QMessageBox::Ok );
            EReporte *rep = new EReporte( this );
            rep->anulacionFactura();
            ParameterList lista;
            lista.append( Parameter( "razon", razon ) );
            lista.append( Parameter( "fechahora", QDateTime::currentDateTime().toString( "dd/MM/yyyy") ) );
            if( !rep->hacer( lista, true ) ) {
                QMessageBox::information( this, "Error de impresion", QString::fromUtf8( "Error al imprimir la anulación. Ingresela a mano." ), QMessageBox::Ok );
            }
        }
    } else {
        QMessageBox::warning( this, "Error", "Hubo un error la intentar anular la factura. No se anulo" );
    }
}
