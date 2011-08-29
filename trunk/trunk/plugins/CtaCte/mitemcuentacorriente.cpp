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
#include <QVariant>

#include "mcuentacorriente.h"

MItemCuentaCorriente::MItemCuentaCorriente(QObject *parent, bool /*s */)
 : QSqlRelationalTableModel(parent), _saldo(saldos)
{
 setTable( "item_ctacte" );
 setHeaderData( 0, Qt::Horizontal, "IdOperacion" );
 setHeaderData( 1, Qt::Horizontal, "Fecha" );
 setHeaderData( 2, Qt::Horizontal, "Ref Id" );
 setHeaderData( 3, Qt::Horizontal, "Tipo" );
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
    if( saldos != 0 ) {
        delete saldos;
        saldos = 0;
    }
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
        @return ID de la nueva operación o -1 si hubo un error.
 */
int MItemCuentaCorriente::agregarOperacion( const QString &numero_cuenta, const QString &num_comb, const int &num_ref, const TipoOperacionCtaCte tipo, const QDate &fecha, const QString &descripcion, const double &aplicar )
{
 QSqlQuery cola;
 cola.prepare( "INSERT INTO item_ctacte"
               "( id_ctacte, fecha, numero_comprobante, id_referencia, tipo_op, descripcion, debe, haber ) VALUES "
               "( :id_ctacte, :fecha, :num_comb, :id_referencia, :tipo_op, :descripcion, :debe, :haber )"
             );
 cola.bindValue( ":id_ctacte", numero_cuenta );
 cola.bindValue( ":fecha", fecha );
 cola.bindValue( ":num_comb", num_comb );
 cola.bindValue( ":id_referencia", num_ref );
 cola.bindValue( ":tipo_op", tipo );
 cola.bindValue( ":descripcion", descripcion );
 if( aplicar > 0.0 )
 {
  cola.bindValue( ":debe", aplicar );
  cola.bindValue( ":haber", 0.0 );
 }
 else
 {
  cola.bindValue( ":debe", 0.0 );
  cola.bindValue( ":haber", (-1) * aplicar );
 }

 if( cola.exec() )
 {
  // Actualizo el saldo
  bool act = MCuentaCorriente::actualizarSaldo( numero_cuenta, aplicar );
  QVariant id = cola.lastInsertId();
  if( act ){
      if( id.isValid() ) {
        return id.toInt();
      } else {
          qDebug( "ID de operación retornado invalido" );
          return -1;
      }
  } else {
      qDebug( "Error al actualizar el saldo en la cuenta corriente" );
      return -1;
  }
 }
 else
 {
  qWarning( "Error al intentar guardar la operacion de item de cuenta corriente" );
  qDebug( qPrintable( cola.lastError().text() ) );
  qDebug( qPrintable( cola.lastQuery() ) );
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
                                        case CobroServicio:
                                        { return "CS"; break; }
                                        case RecargoCobroServicio:
                                        { return "RCS"; break; }
                                        case AnulacionFactura:
                                        { return "FA"; break; }
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
                        case 9:
                        {
                                // Genero el saldo si no esta generado.
                                if( _saldo && !saldos->keys().contains( item.row() ) )
                                {
                                        // Calcular el saldo
                                        if( item.row() >= 1 )
                                        {
                                                saldos->insert( item.row(),
                                                        saldos->value(item.row()-1) -
                                                        this->data( this->index( item.row(), 6 ), Qt::EditRole ).toDouble() +
                                                        this->data( this->index( item.row(), 5 ), Qt::EditRole ).toDouble() );
                                        } else {
                                            saldos->insert( item.row(),
                                                    0 - this->data( this->index( item.row(), 6 ), Qt::EditRole ).toDouble() +
                                                    this->data( this->index( item.row(), 5 ), Qt::EditRole ).toDouble() );
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
                        case 5:
                        case 6:
                        case 9:
                        {
                                return int( Qt::AlignCenter | Qt::AlignHCenter );
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
        case Qt::EditRole:
        {
                switch( item.column() )
                {
                        case 3:
                        { return QSqlRelationalTableModel::data( item, role ).toInt(); break; }
                        case 9:
                        {
                            if( !saldos->keys().contains( item.row() ) )
                            { return 0.0; }
                            else
                            { return saldos->value( item.row() ); }
                        }
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
      if( MCuentaCorriente::existeCuenta( num_cuenta ) ) {
        this->setFilter( QString( "num_cuenta = %1" ).arg( _num_cuenta ) );
      } else {
          qWarning( "El numero de cuenta corriente no existe" );
          return false;
      }
  }
  return true;
}

/*!
 * \fn MItemCuentaCorriente::agregarOperacion( const QString &numero_cuenta, const NumeroComprobante &num_comb, const int &num_ref, const TipoOperacionCtaCte tipo, const QDate &fecha, const QString &descripcion, const double &aplicar )
 */
int MItemCuentaCorriente::agregarOperacion( const QString &numero_cuenta, const NumeroComprobante &num_comb, const int &num_ref, const TipoOperacionCtaCte tipo, const QDate &fecha, const QString &descripcion, const double &aplicar ) {
    NumeroComprobante *c = new NumeroComprobante( num_comb );
    return agregarOperacion( numero_cuenta, c->aCadena(), num_ref, tipo, fecha, descripcion, aplicar );
}

double MItemCuentaCorriente::valorOperacion( const int id_op_ctacte ) {
    QSqlQuery cola;
    cola.prepare( "SELECT debe, haber FROM item_ctacte WHERE id_op_ctacte = :id_op_ctacte" );
    cola.bindValue( ":id_op_ctacte", id_op_ctacte );
    if( cola.exec() ) {
        if( cola.next() ) {
            return cola.record().value(0).toDouble() - cola.record().value(1).toDouble();
        } else {
            qDebug( "CtaCte::MItemCuentaCorriente::valorOperación:: Error en el next de la cola para obtener los valores de la operación.");
            qDebug( cola.lastError().text().toLocal8Bit() );
            return 0.0; /// \todo ver si esto es 0 o -1
        }
    } else {
        qDebug( "CtaCte::MItemCuentaCorriente::valorOperación:: Error en el next de la cola para obtener los valores de la operación.");
        qDebug( cola.lastError().text().toLocal8Bit() );
        return -1.0;
    }
}

int MItemCuentaCorriente::columnCount(const QModelIndex& /*parent*/) const
{
    if( _saldo ) {
        return QSqlRelationalTableModel::columnCount()+1;
    } else {
        return QSqlRelationalTableModel::columnCount();
    }
}
