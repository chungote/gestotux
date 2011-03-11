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

#include "mcuentacorriente.h"

MItemCuentaCorriente::MItemCuentaCorriente(QObject *parent, bool /*s */)
 : QSqlRelationalTableModel(parent), _saldo(saldos)
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
 if( saldos )
 {
  setHeaderData( 9, Qt::Horizontal, "Saldo" );
  saldos = new QHash<int, double>();
 }
 _num_cuenta = "";
}


MItemCuentaCorriente::~MItemCuentaCorriente()
{
}


/*!
    \fn MItemCuentaCorriente::agregarOperacion( const QString &numero_cuenta, const QString &num_comb, const int &num_ref, const TipoOperacionCtaCte tipo, const QDate &fecha, const QString &descripcion, const double &aplicar )
        Genera un registro unico de la opercion en cuenta corriente sin hacer confirmacion ( commit ) en la base de datos.
        @param numero_cuenta Numero de cuenta corriente a aplicar la operacion
        @param num_comb Numero del comprobante relacionado a la operacion
        @param num_ref ID de clave foranea que tiene la operacion
        @param tipo Tipo de operación
        @param fecha Fecha de la operacion
        @param descripcion Descripcion de la operacion
        @param aplicar Valor a aplicar a la cuenta. Si es positivo es en favor nuestro -> el cliente nos debe. Si es negativo  es a favor del cliente -> recibimos pago ( ej ).
        @return Operacion satisfactoria o no.
 */
bool MItemCuentaCorriente::agregarOperacion( const QString &numero_cuenta, const QString &num_comb, const int &num_ref, const TipoOperacionCtaCte tipo, const QDate &fecha, const QString &descripcion, const double &aplicar )
{
 MItemCuentaCorriente modelo;
 QSqlRecord reg = modelo.record();
 reg.setValue( "id_ctacte", numero_cuenta );
 reg.setValue( "fecha", fecha );
 reg.setValue( "num_comb", num_comb );
 reg.setValue( "id_referencia", num_ref );
 reg.setValue( "tipo_op", tipo );
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
 {
  // Actualizo el saldo
   return MCuentaCorriente::actualizarSaldo( numero_cuenta, aplicar );
 }
 else
 {
  qWarning( "Error al intentar guardar la operacion de item de cuenta corriente" );
  qDebug( qPrintable( modelo.lastError().text() ) );
  qDebug( qPrintable( modelo.query().lastQuery() ) );
  return false;
 }

}


#include <QDate>
/*!
    \fn MItemCuentaCorriente::data(const QModelIndex& item, int role) const
 */
QVariant MItemCuentaCorriente::data(const QModelIndex& item, int role) const
{
  switch( role )
 {
        case Qt::DisplayRole:
        {
                switch( item.column() )
                {
                        case 3:
                        {
                                switch( QSqlRelationalTableModel::data(item, role).toInt() )
                                {
                                        case Factura:
                                        { return "F"; break; }
                                        case Recibo:
                                        { return "R"; break; }
                                        case NotaCredito:
                                        { return "NC"; break; }
                                        case NotaDebito:
                                        { return "ND"; break; }
                                        default:
                                        { return "";  break; }
                                }
                                break;
                        }
                        case 5:
                        case 6:
                        {
                                return QString( "$ %L1" ).arg( QSqlRelationalTableModel::data(item, role).toDouble() );
                                break;
                        }
                        case 1:
                        {
                                return QSqlRelationalTableModel::data( item, role ).toDate().toString( Qt::DefaultLocaleShortDate );
                                break;
                        }
                        case 8:
                        {
                                if( _saldo && !saldos->keys().contains( item.row() ) )
                                {
                                        // Calcular el saldo
                                        if( item.row() > 1 )
                                        {
                                                /*double saldoNuevo = saldos->value( item.row()-1 );
                                                saldoNuevo -= this->data( this->index( item.row(), 5 ), Qt::DisplayRole ).toDouble();
                                                saldoNuevo += this->data( this->index( item.row(), 6 ), Qt::DisplayRole ).toDouble();
                                                saldos->insert( item.row(), saldoNuevo );*/
                                                saldos->insert( item.row(),
                                                        saldos->value(item.row()-1) -
                                                        this->data( this->index( item.row(), 5 ), Qt::DisplayRole ).toDouble() +
                                                        this->data( this->index( item.row(), 6 ), Qt::DisplayRole ).toDouble() );
                                        }
                                }
                                return QString( "$ %L1" ).arg( saldos->value( item.row() ) );
                                break;
                        }
                        default:
                        {
                                return QSqlRelationalTableModel::data(item, role);
                                break;
                        }
                }
                break;
        }
        case Qt::TextAlignmentRole:
        {
                switch( item.column() )
                {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 8:
                        {
                                return Qt::AlignCenter;
                                break;
                        }
                        case 5:
                        case 6:
                        default:
                        {
                                return QSqlRelationalTableModel::data(item, role);
                                break;
                        }
                }
                break;
        }
        case Qt::EditRole:
        {
                switch( item.column() )
                {
                        case 3:
                        { return QSqlRelationalTableModel::data( item, role ).toInt(); break; }
                        default:
                        { return QSqlRelationalTableModel::data( item, role ); break; }
                }
                break;
        }
        default:
        {
                return QSqlRelationalTableModel::data(item, role);
        }
 }
}


/*!
    \fn MItemCuentaCorriente::seleccionarNumCuenta( const QString &num_cuenta )
 */
bool MItemCuentaCorriente::seleccionarNumCuenta( const QString &num_cuenta )
{
  _num_cuenta = num_cuenta;
  if( _num_cuenta.isEmpty() )
  {
   this->setFilter( _num_cuenta );
  }
  else
  {
   this->setFilter( QString( "num_cuenta = %1" ).arg( _num_cuenta ) );
  }
  return true;
 ///@todo Verificar que existe la cuenta
}
