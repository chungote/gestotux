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
#include "formasociarserviciocliente.h"

#include "emcliente.h"
#include "mservicios.h"
#include <QSqlQuery>

FormAsociarServicioCliente::FormAsociarServicioCliente(QWidget* parent, tipoForm tipo, Qt::WFlags fl)
: QDialog( parent, fl ), Ui::Dialog()
{
        _tipo = tipo;
        setupUi(this);
        _id_cliente = _id_servicio = -1;
        _fecha = QDate::currentDate();
        switch( tipo )
        {
                case Cliente:
                {
                        CBServicio->setVisible( false );
                        LServicio->setVisible( false );
                        CBCliente->setModel( new EMCliente( CBCliente ) );
                        qobject_cast<EMCliente *>( CBCliente->model())->setQuery( "SELECT id, razon_social FROM clientes WHERE id != 0" );
                        CBCliente->setModelColumn( 1 );
                        break;
                }
                case Servicio:
                {
                        CBCliente->setVisible( false );
                        LCliente->setVisible( false );
                        break;
                }
                case SoloFecha:
                {
                        CBCliente->setVisible( false );
                        LCliente->setVisible( false );
                        CBServicio->setVisible( false );
                        LServicio->setVisible( false );
                        CBCliente->setModel( new EMCliente( CBCliente ) );
                        qobject_cast<EMCliente *>( CBCliente->model())->setQuery( "SELECT id, razon_social FROM clientes WHERE id != 0" );
                        CBCliente->setModelColumn( 1 );
                        break;
                }
                default:
                { break; }
        }
        DEFechaAlta->setDate( _fecha );
        this->adjustSize();
}

FormAsociarServicioCliente::~FormAsociarServicioCliente()
{
}

void FormAsociarServicioCliente::reject()
{
  QDialog::reject();
}

void FormAsociarServicioCliente::accept()
{
 this->setIdCliente( CBCliente->model()->data( CBCliente->model()->index( CBCliente->currentIndex(), 0 ) , Qt::EditRole ).toInt() );
 this->setIdServicio( CBServicio->model()->data( CBServicio->model()->index( CBServicio->currentIndex(), 0 ) , Qt::EditRole ).toInt()  );
 switch( this->_tipo )
 {
        case Cliente:
        {
                this->setIdCliente( CBCliente->model()->data( CBCliente->model()->index( CBCliente->currentIndex(), 0 ) , Qt::EditRole ).toInt() );
                break;
        }
        case Servicio:
        {
                this->setIdServicio( CBServicio->model()->data( CBServicio->model()->index( CBServicio->currentIndex(), 0 ) , Qt::EditRole ).toInt()  );
                break;
        }
        default:
        { break; }
 }
 if( _id_cliente == -1 || _id_servicio == -1 || !_fecha.isValid() )
 {
  return;
 }
 MServicios *mservicios = new MServicios( this );
 if( mservicios->asociarCliente( _id_cliente, _id_servicio, DEFechaAlta->date() ) )
 {
  QDialog::accept();
 }
 else
 {
  return;
 }
}


/*!
    \fn FormAsociarServicioCliente::idCliente()
        Devuelve el id del cliente
        @return int - id cliente en tabla clientes
 */
int FormAsociarServicioCliente::idCliente()
{ return _id_cliente; }


/*!
    \fn FormAsociarServicioCliente::idServicio()
        Devuelve el id del servicio
        @return int - id del servicio en tabla servicios
 */
int FormAsociarServicioCliente::idServicio()
{ return _id_servicio; }


/*!
    \fn FormAsociarServicioCliente::fecha()
        Devuelve la fecha de asociacion
        @return QDate - Fecha de asociacion
 */
QDate FormAsociarServicioCliente::fecha()
{ return _fecha; }


/*!
    \fn FormAsociarServicioCliente::setFecha( QDate fecha )
        Coloca la fecha de asociación
        @param fecha QDate con la fecha de asociación
 */
void FormAsociarServicioCliente::setFecha( QDate fecha )
{ this->_fecha = fecha; }


/*!
    \fn FormAsociarServicioCliente::setIdCliente( int id_cliente )
        Coloca el id de cliente al cual se quiere asociar
        @param id_cliente int - Id de tabla clientes
 */
void FormAsociarServicioCliente::setIdCliente( int id_cliente )
{
 if( id_cliente > 0 )
 {
  _id_cliente = id_cliente;
 }
}


/*!
    \fn FormAsociarServicioCliente::setIdServicio( int id_servicio )
        Coloca el id del servicio al cual se quiere asociar un cliente
        @param id_servicio int - id de tabla servicio
 */
void FormAsociarServicioCliente::setIdServicio( int id_servicio )
{ _id_servicio = id_servicio; }


/*!
    \fn FormAsociarServicioCliente::exec()
 */
int FormAsociarServicioCliente::exec()
{
 switch( this->_tipo )
 {
        case Servicio:
        {
                // Tengo que eliminar todos los clientes que ya estan adheridos a este servicio
                QSqlQueryModel *modelo = new QSqlQueryModel( CBCliente );
                modelo->setQuery( QString( "SELECT id, razonsocial FROM clientes WHERE id IN ( SELECT id_cliente FROM servicios_clientes WHERE id_servicio = %1 )" ).arg( _id_servicio ) );
                CBCliente->setModel( modelo );
                CBCliente->setModelColumn( 1 );
                break;
        }
        case Cliente:
        default:
        {
                break;
        }
 }
 return QDialog::exec();
}
