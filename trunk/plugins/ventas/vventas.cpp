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
    this->modelo->select();

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

    this->addAction( ActAgregar );
    //this->addAction( ActPagar );
    this->addAction( ActAnular );
    this->addAction( new EActCerrar( this ) );
    this->addAction( ActSep );
    this->addAction( ActVerAnuladas );
}


#include "formagregarventa.h"
void VVentas::agregar()
{ emit agregarVentana( new FormAgregarVenta() ); }

void VVentas::buscar()
{ return; }

void VVentas::eliminar()
{ return; }

void VVentas::imprimir()
{ return; }

void VVentas::modificar()
{ return; }

void VVentas::anular()
{
    // Busco todos los IDs a anular
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
        if( ok && !razon.isEmpty() ) {
            if( MFactura::anularFactura( this->modelo->data( this->modelo->index( indice.row(), 0 ) ).toInt(), razon, QDateTime::currentDateTime() ) ) {
                int ret = QMessageBox::question( this, "Correcto", QString::fromUtf8( "La Factura %1 ha sido anulada correctamente. <br /> ¿Desea imprimir la anulaciòn?" ).arg( numero ), QMessageBox::Yes, QMessageBox::No );
                if( ret == QMessageBox::Yes ) {
                    QMessageBox::information( this, "Esperando", QString::fromUtf8( "Por favor, ingrese la factura en la impresora para imprimir la anulaciòn. <br /> Presione OK para enviar a imprimir la anulacion" ), QMessageBox::Ok );
                    EReporte *rep = new EReporte( this );
                    rep->anulacionFactura();
                    ParameterList lista;
                    lista.append( Parameter( "razon", razon ) );
                    lista.append( Parameter( "fechahora", QDateTime::currentDateTime().toString( "dd/MM/yyyy") ) );
                    if( !rep->hacer( lista, true ) ) {
                        QMessageBox::information( this, "Error de impresion", QString::fromUtf8( "Error al hacer la anulación. Ingresela a mano." ), QMessageBox::Ok );
                    }
                }
            } else {
                QMessageBox::warning( this, "Error", "Hubo un error la intentar anular la factura. No se anulo" );
            }
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
