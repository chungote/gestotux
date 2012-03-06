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
#include <QTableView>
#include "MClientesServicios.h"
#include "eactcerrar.h"
#include <QMessageBox>
#include <QInputDialog>

FormClientesAdheridos::FormClientesAdheridos(QWidget *parent) :
    EVentana(parent) {
    setupUi(this);

    setObjectName( "ClientesAdheridos" );
    setWindowTitle( "Clientes Adheridos" );
    //setWindowIcon();

    CBServicios->setModel( new MServicios( CBServicios ) );
    CBServicios->setModelColumn( 1 );
    qobject_cast<QSqlTableModel *>(CBServicios->model())->select();
    connect( CBServicios, SIGNAL( currentIndexChanged( int ) ), this, SLOT( cambioServicio( int ) ) );

    modelo = new MClientesServicios( this );
    TVAdheridos->setModel( modelo );
    TVAdheridos->hideColumn( 0 );
    TVAdheridos->setSelectionBehavior( QAbstractItemView::SelectRows );
    TVAdheridos->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
    modelo->select();

    // Acciones
    //// Dar de baja
    QAction *ActDarDeBaja = new QAction( this );
    ActDarDeBaja->setText( "Dar de Baja" );
    connect( ActDarDeBaja, SIGNAL( triggered() ), this, SLOT( darDeBaja() ) );
    this->addAction( ActDarDeBaja );
    //// Eliminar adhesion
    QAction *ActEliminar = new QAction( this );
    ActEliminar->setText( "Eliminar" );
    connect( ActEliminar, SIGNAL( triggered() ), this, SLOT( eliminar() ) );
    this->addAction( ActEliminar );

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
    modelo->filtrarPorServicio( id_servicio );
    modelo->select();
    // Coloco el combo box en la posicion correcta
    CBServicios->setCurrentIndex( CBServicios->findData( id_servicio ) );
}

void FormClientesAdheridos::cambioServicio( int /*id_combo*/ )
{
    int id_servicio = CBServicios->model()->data( CBServicios->model()->index( CBServicios->currentIndex(), 0), Qt::EditRole ).toInt();
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
  int id_servicio = CBServicios->model()->data( CBServicios->model()->index( CBServicios->currentIndex(), 0), Qt::UserRole ).toInt();
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
     int id_servicio = CBServicios->model()->data( CBServicios->model()->index( CBServicios->currentIndex(), 0 ), Qt::UserRole ).toInt();
     foreach( QModelIndex item, lista ) {
         int id_cliente = item.model()->data( item.model()->index( item.row(), 0 ), Qt::EditRole ).toInt();
         QDate fecha_baja = item.model()->data( item.model()->index( item.row(), 3 ), Qt::EditRole ).toDate();
         if( !fecha_baja.isValid() ) {
             QMessageBox::information( this, "Error", "El cliente que está intentando eliminar no ha sido dado de baja todavía. Delo de baja antes de eliminar la asociación." );
         } else {
             if( MCobroServicioClientePeriodo::tieneDatosRelacionados( id_servicio, id_cliente ) ) {
                 QMessageBox::warning( this, "Error", "La asociación del servicio que está intentando eliminar posee datos de facturación. No se puede eliminar la asociación para no comprometer la integridad de los datos." );
             } else {
                bool ok = false;
                QString razon = QInputDialog::getText( this, "Razon de baja", "Ingrese la razon de baja:", QLineEdit::Normal, QString(), &ok );
                if( ok )
                    modelo->darDeBaja( id_cliente, id_servicio, razon );
             }
         }
     }
}
