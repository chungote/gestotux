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
    TVAdheridos->hideColumn( 1 );
    TVAdheridos->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
    modelo->select();

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
}

void FormClientesAdheridos::cambioServicio( int id_servicio )
{
    modelo->filtrarPorServicio( id_servicio );
    modelo->select();
}
