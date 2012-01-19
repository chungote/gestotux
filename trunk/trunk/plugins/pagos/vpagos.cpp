/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   				   *
 *   juiraze@yahoo.com.ar   						   *
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
#include "vpagos.h"

#include <QTableView>
#include <QIcon>
#include <QMessageBox>
#include <QInputDialog>

#include "mvpagos.h"
#include "formagregarrecibo.h"
#include "EReporte.h"
#include "dsino.h"
#include "eregistroplugins.h"

VPagos::VPagos(QWidget *parent)
 : EVLista(parent)
{
 this->setObjectName( "vpagos" );
 this->setWindowTitle( "Visor de Pagos" );
 this->setWindowIcon( QIcon( ":/imagenes/recibo.png" ) );

 modelo = new MVPagos( this );
 vista->setModel( modelo );
 vista->hideColumn( 0 );
 vista->setSortingEnabled( true );
 vista->setAlternatingRowColors( true );

 if( ERegistroPlugins::getInstancia()->existePluginExterno( "hicomp" ) ) {
     vista->setItemDelegateForColumn( 6, new DSiNo( vista ) );
 } else {
     vista->hideColumn( 6 );
 }
 vista->setItemDelegateForColumn( 7, new DSiNo( vista ) );


 ActCancelarRecibo = new QAction( this );
 ActCancelarRecibo->setText( "Cancelar" );
 connect( ActCancelarRecibo, SIGNAL( triggered() ), this, SLOT( cancelarPago() ) );

 addAction( ActAgregar );
 addAction( ActCancelarRecibo );
 addAction( ActVerTodos );
 addAction( ActImprimir );
 addAction( ActPdf );
 addAction( ActCerrar );
}

/*!
  \fn VPagos::agregar( bool a )
  Llama al formulario para agregar un nuevo cliente
  */
void VPagos::agregar( bool /*a*/)
{
 FormAgregarRecibo *f = new FormAgregarRecibo( this );
 //f->setearModelo( qobject_cast<MPagos *>(this->modelo) );
 emit agregarVentana( f );
}

/*!
  \fn VPagos::imprimir()
  Imprime el recibo que se encuentre seleccionado en la vista actual
 */
void VPagos::imprimir()
{
    // Imprime el recibo que se encuentre seleccionado
    QItemSelectionModel *selectionModel = vista->selectionModel();
    QModelIndexList indices = selectionModel->selectedRows();
    if( indices.size() < 1 )
    {
      QMessageBox::warning( this, "Seleccione un item",
                      "Por favor, seleccione un item para imprimir",
                      QMessageBox::Ok );
      return;
    }
    //Hacer dialogo de confirmacion..
    int ret;
    ret = QMessageBox::warning( this, "Esta seguro?",
                      QString::fromUtf8( "Esta seguro de reimprimir %1 recibo(s)?\n Se conservará el mismo numero de recibo que cuando fue emitido").arg( indices.size() ),
                      "Si", "No" );
    if ( ret == 0 )
    {
           QModelIndex indice;
           EReporte *rep = new EReporte( 0 );
           rep->recibo();
           ParameterList lista;
           foreach( indice, indices )
           {
                   if( indice.isValid() )
                   {
                           QModelIndex r = indice.model()->index( indice.row(), 0 );
                           QModelIndex c = indice.model()->index( indice.row(), 1 );
                           lista.append( "id_recibo", r.data( Qt::EditRole ).toInt() );
                           rep->hacer( lista );
                           lista.clear();
                   }
           }
           delete rep;
    }
    return;
}

/*!
  \fn VPagos::aPdf()
  Imprime en pdf el recibo que se encuentre seleccionado en la vista actual
 */
void VPagos::aPdf()
{
    // Imprime el recibo que se encuentre seleccionado
    QItemSelectionModel *selectionModel = vista->selectionModel();
    QModelIndexList indices = selectionModel->selectedRows();
    if( indices.size() < 1 )
    {
      QMessageBox::warning( this, "Seleccione un item",
                      "Por favor, seleccione un item para exportar a pdf",
                      QMessageBox::Ok );
      return;
    }
    QModelIndex indice;
    EReporte *rep = new EReporte( 0 );
    rep->recibo();
    ParameterList lista;
    foreach( indice, indices )
    {
        if( indice.isValid() )
        {
            QModelIndex r = indice.model()->index( indice.row(), 0 );
            //QModelIndex c = indice.model()->index( indice.row(), 1 );
            lista.append( "id_recibo", r.data( Qt::EditRole ).toInt() );
            rep->hacer( lista );
            lista.clear();
        }
        delete rep;
    }
    return;
}

/*!
 * \fn VPagos::cancelarPago()
 * Cancela un recibo seleccionado
 */
void VPagos::cancelarPago()
{
    // Cancela el recibo que se encuentre seleccionado
    QItemSelectionModel *selectionModel = vista->selectionModel();
    QModelIndexList indices = selectionModel->selectedRows();
    if( indices.size() < 1 )
    {
      QMessageBox::warning( this, "Seleccione un item",
                      "Por favor, seleccione un item para cancelar",
                      QMessageBox::Ok );
      return;
    }
    //Hacer dialogo de confirmacion..
    int ret;
    ret = QMessageBox::warning( this, "Esta seguro?",
                      QString( "Esta seguro de cancelar %1 recibo(s)?\n Se eliminaran las operaciones asociadas con este recibo.").arg( indices.size() ),
                      "Si", "No" );
    if ( ret == 0 )
    {
           MPagos *mp = new MPagos();
           foreach( QModelIndex indice, indices )
           {
                   if( indice.isValid() )
                   {
                       bool ok;
                       int id_recibo = indice.model()->data( indice.model()->index( indice.row(), 0 ), Qt::EditRole ).toInt();
                       QString razon = QInputDialog::getText( this, "Razón", QString::fromUtf8( "Razón de cancelación:" ), QLineEdit::Normal, QString(), &ok );
                       NumeroComprobante num = mp->buscarNumeroComprobantePorId( id_recibo );
                       if( mp->cancelarRecibo( id_recibo, razon, QDateTime::currentDateTime() ) ) {
                           QMessageBox::information( this, "Correcto", QString( "El recibo %1 fue cancelado correctamente" ).arg( num.aCadena() ) );
                       } else {
                           QMessageBox::warning( this, "Error", QString( "El recibo  %1 <b>no</b> pudo ser cancelado" ).arg( num.aCadena() ) );
                       }
                   }
           }
           delete mp;
           mp = 0;
    }
    return;
}

/*!
    \fn VPagos::menuContextual( const QModelIndex &indice, QMenu *menu )
 */
void VPagos::menuContextual( const QModelIndex &indice, QMenu *menu )
{
 // Agrego las acciones que quiero que aparezcan en el menu
 menu->addAction( ActCancelarRecibo );
 menu->addAction( ActImprimir );
 menu->addAction( ActPdf );
 menu->addSeparator();
 menu->addAction( ActAgregar );
 indiceMenu = indice;
 return;
}
