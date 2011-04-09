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

#include "formrecargos.h"

#include "mservicios.h"
#include "mrecargos.h"
#include <QMessageBox>
#include <QSqlError>
#include <QItemDelegate>

#include "eactcerrar.h"

FormRecargos::FormRecargos( QWidget *parent, Qt::WFlags fl ) :
        EVentana( parent, fl ), Ui::FormRecargoBase()
{
    setupUi(this);
    setObjectName( "recargos" );
    setWindowTitle( "Recargos" );

    // Modelo de los servicios para el combobox
    mservicios = new MServicios( this );
    CBServicios->setModel( mservicios );
    CBServicios->setModelColumn( 1 );
    mservicios->select();
    connect( CBServicios, SIGNAL( currentIndexChanged(int) ), this, SLOT( cambioServicio(int) ) );
    CBServicios->setCurrentIndex( 0 );

    // Genero las acciones
    ActAgregar = new QAction( this );
    ActAgregar->setText( "Agregar" );
    ActAgregar->setIcon( QIcon( ":/imagenes/add.png" ) );
    this->addAction( ActAgregar );

    ActEliminar = new QAction( this );
    ActEliminar->setIcon( QIcon( ":/imagenes/eliminar.png" ) );
    ActEliminar->setText( "Eliminar" );
    this->addAction( ActEliminar );

    ActCerrar = new EActCerrar( this );
    this->addAction( ActCerrar );

    // Conexiones para los botones
    connect( ActAgregar , SIGNAL( triggered() ), this, SLOT( agregarRecargo() ) );
    connect( ActEliminar, SIGNAL( triggered() ), this, SLOT( eliminarRecargo()) );
    connect( ActCerrar  , SIGNAL( triggered() ), this, SLOT( guardarTodo()    ) );

    // Inizializo el modelo de los recargos
    mrecargos = new MRecargos( this );
    mrecargos->setEditStrategy( QSqlTableModel::OnManualSubmit );
    TVRecargos->setModel( mrecargos );
    TVRecargos->hideColumn( 0 );
    TVRecargos->hideColumn( 1 );
    TVRecargos->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
    this->cambioServicio( CBServicios->currentIndex() );
    mrecargos->select();
}

void FormRecargos::cambioServicio( int servicio )
{
  // Busco los datos de los recargos del servicio seleccionado
  int id_servicio = mservicios->data( mservicios->index( servicio, 0 ), Qt::EditRole ).toInt();
  mrecargos->setearServicio( id_servicio );
  mrecargos->select();
}

void FormRecargos::agregarRecargo()
{
 // Agrega un nuevo recargo a la lista del servicio seleccionado
    mrecargos->setearServicio( mservicios->data( mservicios->index( CBServicios->currentIndex(), 0 ), Qt::EditRole ).toInt() );
    mrecargos->agregarRecargo();
}

void FormRecargos::eliminarRecargo()
{
 QMessageBox::information( this, "this", "Todavia no implementado!" );
}

void FormRecargos::guardarTodo()
{
  if( QMessageBox::question( this, "Guardar cambios", "¿Desea guardar los cambios realizados?", QMessageBox::Ok, QMessageBox::Cancel ) ==  QMessageBox::Ok )
  {
      if( mrecargos->submitAll() ) {
                QMessageBox::information( this, "Correcto", "Cambios guardados correctamente" );
                this->close();
                return;
            } else {
                QMessageBox::critical( this, "Erroneo", "No se pudieron guardar los cambios realizados" );
                qDebug( "FormRecargos::guardarTodo::ErrorGuardado::infodb:" );
                qDebug( mrecargos->lastError().text().toLocal8Bit() );
            }
  }
}

void FormRecargos::changeEvent(QEvent *e)
{
    switch (e->type()) {
        case QEvent::LanguageChange:
            retranslateUi(this);
            break;
        default:
            break;
    }
}

void FormRecargos::setearId(const int id)
{ this->cambioServicio( id ); }
