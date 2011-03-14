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

#include "FormFacturarServicio.h"
#include "eactcerrar.h"
#include "mservicios.h"
#include "mrecargos.h"
#include "MTempClientesFacturarServicio.h"
#include "dsino.h"

FormFacturarServicio::FormFacturarServicio(QWidget *parent) :
EVentana(parent), _id_servicio(0)  {

    setupUi(this);

    this->setWindowTitle( "Facturación de un servicio" );
    //this->setWindowIcon( QIcon( ":/imagenes/" ) );
    this->setObjectName( "facturaservicios" );

    ActCerrar = new EActCerrar( this );

    ActFacturar = new QAction( this );
    ActFacturar->setText( "Facturar" );
    ActFacturar->setStatusTip( "Factura el servicio con los clientes seleccionados" );
    ActFacturar->setIcon( QIcon( ":/imagenes/" ) );
    connect( ActFacturar, SIGNAL( triggered() ), this, SLOT( facturar() ) );

    this->addAction( ActFacturar );
    this->addAction( ActCerrar );

}

void FormFacturarServicio::changeEvent(QEvent *e)
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

/*!
 * \fn FormFacturarServicio::setearServicio( const int id_servicio )
 *  Setea el id de servicio que se desea realizar la facturación
 * \param id_servicio ID del servicio
 */
void FormFacturarServicio::setearServicio(const int id_servicio)
{
    if( id_servicio > 0 ) {
        this->_id_servicio = id_servicio;
        this->cargar_datos_servicio();
    } else {
        qWarning( "Servicios:FormFacturarServicio: Seteando un servicio < o = 0");
        return;
    }
}

/*!
 * \fn FormFacturarServicio::cargar_datos_servicio()
 * Carga los datos de un servicio seleccionado
 */
void FormFacturarServicio::cargar_datos_servicio()
{
    MServicios *m = new MServicios( this );
    this->LNombreServicio->setText( m->getNombreServicio( this->_id_servicio ) );
    double precio_base = m->precioBase( this->_id_servicio );
    this->LPrecioBase->setText( QString( "$ %L1" ).arg( precio_base  ) );
    this->LPeriodo->setText( m->getPeriodoActual( this->_id_servicio ) );
    // Cargo los clientes del servicio
    MTempClientesFacturarServicio *mc = new MTempClientesFacturarServicio( this );
    // Cargo los clientes
    this->TVClientes->setModel( mc );
    mc->cargarClientesDelServicio( this->_id_servicio );
    this->TVClientes->setItemDelegateForColumn( 0, new DSiNo( this->TVClientes ) );
    this->TVClientes->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
    // Cargo los recargos del servicio
    MRecargos *mr = new MRecargos( this, false );
    mr->setFilter( QString( "id_servicio = %1 " ).arg( this->_id_servicio ) );
    mr->setearPrecioBase( precio_base );
    this->TVRecargos->setModel( mr );
    this->TVRecargos->hideColumn( 0 );
    this->TVRecargos->hideColumn( 1 );
    this->TVRecargos->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
    mr->select();
}

/*!
 * \fn FormFacturarServicio::facturar()
 * Realiza la facturación efectiva del servicio. El usuario ya acepto el facturar y los datos.
 */
void FormFacturarServicio::facturar()
{

}
