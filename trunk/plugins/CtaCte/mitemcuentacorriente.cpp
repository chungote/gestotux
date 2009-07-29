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
#include "mitemcuentacorriente.h"

#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>

MItemCuentaCorriente::MItemCuentaCorriente(QObject *parent)
 : QSqlRelationalTableModel(parent)
{
 setTable( "item_ctacte" );
 setHeaderData( 0, Qt::Horizontal, "IdOperacion" );
 setHeaderData( 1, Qt::Horizontal, "Fecha" );
 setHeaderData( 2, Qt::Horizontal, "Ref Id" );
 setHeaderData( 3, Qt::Horizontal, "Tipo Operacion" );
 setHeaderData( 4, Qt::Horizontal, "Descripcion" );
 setHeaderData( 5, Qt::Horizontal, "Debe" );
 setHeaderData( 6, Qt::Horizontal, "Haber" );
 setHeaderData( 7, Qt::Horizontal, "Numero cuenta Corriente" );
 setHeaderData( 8, Qt::Horizontal, "Numero de Comprobante" );
}


MItemCuentaCorriente::~MItemCuentaCorriente()
{
}


/*!
    \fn MItemCuentaCorriente::agregarOperacion( const QString &numero_cuenta, const QString &num_comb, const int &num_ref, const QDate &fecha, const QString &descripcion, const double &aplicar )
 	Genera un registro unico de la opercion en cuenta corriente
	@param numero_cuenta Numero de cuenta corriente a aplicar la operacion
	@param num_comb Numero del comprobante relacionado a la operacion
	@param num_ref ID de clave foranea que tiene la operacion
	@param fecha Fecha de la operacion
	@param descripcion Descripcion de la operacion
	@param aplicar Valor a aplicar a la cuenta. Si es positivo es en favor nuestro -> el cliente nos debe. Si es negativo  es a favor del cliente -> recibimos pago ( ej ).
	@return Operacion satisfactoria o no.
 */
bool MItemCuentaCorriente::agregarOperacion( const QString &numero_cuenta, const QString &num_comb, const int &num_ref, const QDate &fecha, const QString &descripcion, const double &aplicar )
{
 MItemCuentaCorriente modelo;
 QSqlRecord reg = modelo.record();
 reg.setValue( "id_ctacte", numero_cuenta );
 reg.setValue( "fecha", fecha );
 reg.setValue( "num_comb", num_comb );
 reg.setValue( "id_referencia", num_ref );
 reg.setValue( "descripcion", descripcion );
 if( aplicar > 0.0 )
 {
  reg.setValue( "debe", aplicar );
  reg.setValue( "haber", 0.0 );
 }
 else
 {
  reg.setValue( "debe", 0.0 );
  reg.setValue( "haber", aplicar );
 }
 if( modelo.insertRecord( -1, reg ) )
 { return true; }
 else
 {
  qWarning( "Error al intentar guardar la operacion de item de cuenta corriente" );
  qDebug( qPrintable( modelo.lastError().text() ) );
  qDebug( qPrintable( modelo.query().lastQuery() ) );
  return false;
 }

}
