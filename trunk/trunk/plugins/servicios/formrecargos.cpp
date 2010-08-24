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

FormRecargos::FormRecargos( QWidget *parent, Qt::WFlags fl ) :
        EVentana( parent, fl ), Ui::FormRecargoBase()
{
    setupUi(this);
    setObjectName( "recargos" );
    setWindowTitle( "Recargos" );

    // Modelo de los servicios para el combobox
    CBServicios->setModel( new MServicios( CBServicios ) );
    CBServicios->setModelColumn( 1 );
    connect( CBServicios, SIGNAL( currentIndexChanged(int) ), SLOT( cambioServicio(int) ), Qt::AutoConnection );

    // Imagenes de los botones
    PBAgregar->setIcon( QIcon( ":/imagenes/add.png" ) );
    PBEliminar->setIcon( QIcon( ":/imagenes/delete.png" ) );
    PBCancelar->setIcon( QIcon( ":/imagenes/stop.png" ) );
    //PBAceptar->setIcon( QIcon( ":/imagenes/" ) );

    // Conexiones para los botones
    connect( PBAgregar , SIGNAL( clicked() ), this, SLOT( agregarRecargo() ) );
    connect( PBEliminar, SIGNAL( clicked() ), this, SLOT( eliminarRecargo()) );
    connect( PBCancelar, SIGNAL( clicked() ), this, SLOT( close()          ) );
    connect( PBAceptar , SIGNAL( clicked() ), this, SLOT( guardarTodo()    ) );
}

void FormRecargos::cambioServicio( int servicio )
{

}

void FormRecargos::agregarRecargo()
{

}

void FormRecargos::eliminarRecargo()
{

}

void FormRecargos::guardarTodo()
{

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
