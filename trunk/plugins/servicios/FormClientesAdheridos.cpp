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
#include "ui_FormClietnesAdheridosBase.h"
#include "mservicios.h"

FormClientesAdheridos::FormClientesAdheridos(QWidget *parent) :
    EVentana(parent),
    ui(new Ui::FormClientesAdheridos)
{
    ui->setupUi(this);
    setObjectName("Servicios_clientes");
    setWindowTitle( "Clientes para un servicio");
    setWindowIcon( QIcon( ":/imagenes/desconocido.png" ) );

    mservicios = new MServicios( ui->CBServicios );
    ui->CBServicios->setModel( mservicios );
    ui->CBServicios->setModelColumn( 1 );
    connect( ui->CBServicios, SIGNAL( currentIndexChanged( int ) ), this, SLOT( cambioServicio( int ) ) );


}

FormClientesAdheridos::~FormClientesAdheridos()
{
    delete ui;
}

void FormClientesAdheridos::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
