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

    // Genero las acciones
    ActAgregar = new QAction( this );
    ActAgregar->setText( "Agregar" );
    ActAgregar->setIcon( QIcon( ":/imagenes/add.png" ) );
    this->addAction( ActAgregar );

    ActEliminar = new QAction( this );
    ActEliminar->setIcon( QIcon( ":/imagenes/eliminar.png" ) );
    ActEliminar->setText( "Eliminar" );
    this->addAction( ActEliminar );

    this->addAction( new EActCerrar( this ) );

    // Conexiones para los botones
    connect( ActAgregar , SIGNAL( triggered() ), this, SLOT( agregarRecargo() ) );
    connect( ActEliminar, SIGNAL( triggered() ), this, SLOT( eliminarRecargo()) );

    // Inizializo el modelo de los recargos
    mrecargos = new MRecargos( this );
    TVRecargos->setModel( mrecargos );
    mrecargos->select();
}

void FormRecargos::cambioServicio( int servicio )
{
  // Busco los datos de los recargos del servicio seleccionado
  int id_servicio = mservicios->data( mservicios->index( servicio, 0 ), Qt::DisplayRole ).toInt();
  mrecargos->setearServicio( id_servicio );
  mrecargos->select();
}

void FormRecargos::agregarRecargo()
{
 // Agrega un nuevo recargo a la lista del servicio seleccionado
    mrecargos->setearServicio( mservicios->data( mservicios->index( CBServicios->currentIndex(), 0 ), Qt::DisplayRole ).toInt() );
    mrecargos->agregarRecargo();
}

void FormRecargos::eliminarRecargo()
{

}

void FormRecargos::guardarTodo()
{
 this->close();
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
