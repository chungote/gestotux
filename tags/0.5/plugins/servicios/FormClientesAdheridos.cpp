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

#include "FormClientesAdheridos.h"

#include "mservicios.h"
#include "eactimprimir.h"
#include "eactpdf.h"
#include "MClientesServicios.h"
#include "eactcerrar.h"
#include "EReporte.h"
#include "ecbtabla.h"

#include <QMessageBox>
#include <QInputDialog>
#include <QTableView>

FormClientesAdheridos::FormClientesAdheridos(QWidget *parent) :
    EVentana(parent) {
    setupUi(this);

    setObjectName( "ClientesAdheridos" );
    setWindowTitle( "Clientes Adheridos" );
    setWindowIcon( QIcon( ":/imagenes/clientes_adheridos.png" ) );

    CBServicios->setearTabla( "servicios" );
    CBServicios->setearCampoId( "id_servicio" );
    CBServicios->setearCampoTexto( "nombre" );
    CBServicios->setearCampoOrden( "nombre" );
    connect( CBServicios, SIGNAL( cambioId( int ) ), this, SLOT( cambioServicio( int ) ) );

    modelo = new MClientesServicios( this );
    TVAdheridos->setModel( modelo );
    TVAdheridos->hideColumn( 0 );
    TVAdheridos->setSelectionBehavior( QAbstractItemView::SelectRows );
    TVAdheridos->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
    //modelo->select();

    // Acciones
    //// Dar de baja
    QAction *ActDarDeBaja = new QAction( this );
    ActDarDeBaja->setText( "Dar de Baja" );
    connect( ActDarDeBaja, SIGNAL( triggered() ), this, SLOT( darDeBaja() ) );
    this->addAction( ActDarDeBaja );

    //// Eliminar adhesion
    QAction *ActEliminar = new QAction( this );
    ActEliminar->setText( "Eliminar" );
    ActEliminar->setIcon( QIcon( ":/imagenes/eliminar.png" ) );
    connect( ActEliminar, SIGNAL( triggered() ), this, SLOT( eliminar() ) );
    this->addAction( ActEliminar );

    QAction *ActVerBaja = new QAction( this );
    ActVerBaja->setText( "Ver solo baja" );
    ActVerBaja->setStatusTip( "Muestra solamente los clientes que han sido dados de baja del servicio" );
    ActVerBaja->setCheckable( true );
    ActVerBaja->setChecked( false );
    connect( ActEliminar, SIGNAL( toggled( bool ) ), this, SLOT( verBaja( bool ) ) );
    this->addAction( ActVerBaja );

    this->addAction( new EActImprimir( this ) );
    this->addAction( new EActPdf( this ) );

    this->addAction( new EActCerrar( this ) );

}

void FormClientesAdheridos::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

void FormClientesAdheridos::setServicioInicial( int id_servicio )
{
    if( id_servicio <= 0 )
        return;

    CBServicios->setearId( id_servicio );
    modelo->filtrarPorServicio( id_servicio );
    modelo->select();

}

void FormClientesAdheridos::cambioServicio( int id_servicio )
{
    if( id_servicio <= 0 )
        return;

    modelo->filtrarPorServicio( id_servicio );
    modelo->select();
}


void FormClientesAdheridos::darDeBaja()
{
 // Busco el ID que quiere dar de baja
 QModelIndexList lista = TVAdheridos->selectionModel()->selectedRows();
 if( lista.isEmpty() ) {
     QMessageBox::information( this, "Error", "Por favor, seleccione algun cliente adherido para darlo de baja" );
     return;
 }
  int id_servicio = CBServicios->idActual();
  foreach( QModelIndex item, lista ) {
      int id_cliente = item.model()->data( item.model()->index( item.row(), 0 ), Qt::EditRole ).toInt();
      bool ok = false;
      QString razon = QInputDialog::getText( this, "Razon de baja", "Ingrese la razon de baja:", QLineEdit::Normal, QString(), &ok );
      if( ok )
        modelo->darDeBaja( id_cliente, id_servicio, razon );
  }
}

#include "mcobroservicioclienteperiodo.h"
void FormClientesAdheridos::eliminar() {
    // Busco el ID que quiere dar de baja
    QModelIndexList lista = TVAdheridos->selectionModel()->selectedRows();
    if( lista.isEmpty() ) {
        QMessageBox::information( this, "Error", "Por favor, seleccione algun cliente adherido para darlo de baja" );
        return;
    }
     int id_servicio = CBServicios->idActual();
     foreach( QModelIndex item, lista ) {
         int id_cliente = item.model()->data( item.model()->index( item.row(), 0 ), Qt::EditRole ).toInt();
         QDate fecha_baja = item.model()->data( item.model()->index( item.row(), 3 ), Qt::EditRole ).toDate();
         if( !fecha_baja.isValid() ) {
             QMessageBox::information( this, "Error", QString::fromUtf8( "El cliente que está intentando eliminar no ha sido dado de baja todavía. Delo de baja antes de eliminar la asociación." ) );
         } else {
             if( MCobroServicioClientePeriodo::tieneDatosRelacionados( id_servicio, id_cliente ) ) {
                 QMessageBox::warning( this, "Error", QString::fromUtf8( "La asociación del servicio que está intentando eliminar posee datos de facturación. No se puede eliminar la asociación para no comprometer la integridad de los datos." ) );
             } else {
                bool ok = false;
                QString razon = QInputDialog::getText( this, "Razon de baja", "Ingrese la razon de baja:", QLineEdit::Normal, QString(), &ok );
                if( ok )
                    modelo->darDeBaja( id_cliente, id_servicio, razon );
             }
         }
     }
}

void FormClientesAdheridos::imprimir()
{
    EReporte *rep = new EReporte( 0 );
    ParameterList lista;

    lista.append( Parameter( "id_servicio", CBServicios->idActual() ) );
    if( !modelo->filter().isEmpty() )
        lista.append( Parameter( "filtro", modelo->filter() ) );
    rep->especial( "ListadoClientesServicio", lista );

    rep->hacer();
    delete rep;
}

void FormClientesAdheridos::aPdf()
{
   EReporte *rep = new EReporte( 0 );
   ParameterList lista;
   lista.append( Parameter( "id_servicio", CBServicios->idActual() ) );

   if( !modelo->filter().isEmpty() )
    lista.append( Parameter( "filtro", modelo->filter() ) );

   rep->especial( "ListadoClientesServicio", lista );
   rep->hacerPDF( lista, QString( "Listado de clientes adheridos a %1 al %2 " ).arg( CBServicios->currentText() ).arg( QDate::currentDate().toString( Qt::SystemLocaleShortDate ) ) );

   delete rep;
}

void FormClientesAdheridos::verBaja( bool estado )
{
    if( estado ) {
        modelo->setFilter( " fecha_baja IS NOT NULL " );
        modelo->select();
    } else {
        modelo->setFilter( "" );
        modelo->select();
    }
}