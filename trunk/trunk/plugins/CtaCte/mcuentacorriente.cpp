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
#include "mcuentacorriente.h"

#include <QColor>
#include <QDate>
#include <QSqlError>

MCuentaCorriente::MCuentaCorriente( QObject *parent, bool relaciones )
 : QSqlRelationalTableModel( parent )
{
 setTable( "ctacte" );
 inicializar();
 if( relaciones ) { relacionar(); }
}

/*!
 * \fn MCuentaCorriente::inicializar()
 * Inicializa el modelo
 */
void MCuentaCorriente::inicializar()
{
 setHeaderData( 0, Qt::Horizontal, "Numero de cuenta" );
 setHeaderData( 1, Qt::Horizontal, "Cliente" );
 setHeaderData( 2, Qt::Horizontal, "Fecha Alta" );
 setHeaderData( 3, Qt::Horizontal, "Fecha Baja" );
 setHeaderData( 4, Qt::Horizontal, "Saldo" );
 setHeaderData( 5, Qt::Horizontal, "Limite" );
 setHeaderData( 6, Qt::Horizontal, "Suspendida" );
}

/*!
 * \fn MCuentaCorriente::relacionar()
 * Crea las relaciones para el modelo
 */
void MCuentaCorriente::relacionar()
{
 setRelation( 1, QSqlRelation( "clientes", "id", "razon_social" ) );
}

Qt::ItemFlags MCuentaCorriente::flags(const QModelIndex& index) const
{
    switch( index.column() )
    {
        // Campos editables de la vista
        case 4:
        case 5:
        case 3:
        {
            return QFlags<Qt::ItemFlag>( Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled );
            break;
        }
        default:
        {
            return QFlags<Qt::ItemFlag>( !Qt::ItemIsEditable |  Qt::ItemIsSelectable | Qt::ItemIsEnabled );
            break;
        }
    }
}

QVariant MCuentaCorriente::data(const QModelIndex& item, int role) const
{
 switch( role )
 {
        case Qt::DisplayRole:
        {
                switch( item.column() )
                {
                        case 0:
                        {
                                return QSqlRelationalTableModel::data(item, role).toString().prepend( "#" );
                                break;
                        }
                        case 4:
                        case 5:
                        {
                                return QString( "$ %L1" ).arg( QSqlRelationalTableModel::data(item,role).toDouble(), 10, 'f', 2 );
                                break;
                        }
                        case 6:
                        {
                                if( QSqlRelationalTableModel::data( item, role ).toBool() ) {
                                    return "Si";
                                } else {
                                    return "No";
                                }
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
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                        {
                                return Qt::AlignCenter;
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
        case Qt::TextColorRole:
        {
                switch( item.column() )
                {
                        case 0:
                        {
                                return Qt::blue;
                                break;
                        }
                        case 4:
                        {
                                if( this->data( this->index( item.row(), 4 ), Qt::EditRole ).toDouble() >= this->data( this->index( item.row(), 5 ), Qt::EditRole ).toDouble() )
                                { return Qt::red; }
                                else
                                { return Qt::black; }
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
                        case 6:
                        {
                                return QSqlRelationalTableModel::data( item, role ).toBool();
                                break;
                        }
                        default:
                        {
                                return QSqlRelationalTableModel::data( item, role );
                                break;
                        }
                }
                break;
        }
        default:
        {
                return QSqlRelationalTableModel::data(item, role);
        }
 }
}


#include <QSqlQuery>
#include <QSqlRecord>

/*!
    \fn MCuentaCorriente::obtenerNumeroCuentaCorriente( const int id_cliente )
        Funcion que obtiene el numero de cuenta corriente para el id de cliente seleccionado.
        @param id_cliente Identificador de cliente
        @return MCuentaCorriente::Invalido si el @param id_cliente no es correcto. "Error" si no se pudo conseguir, o finalmente el valor buscado.
 */
QString MCuentaCorriente::obtenerNumeroCuentaCorriente( const int id_cliente )
{
 if( id_cliente < 0 )
 {
        qDebug( "MCuentaCorriente::obtenerNumeroCuentaCorriente::Error, el numero de cliente es invalido" );
        return QString::number( MCuentaCorriente::ErrorClienteInvalido );
 } else if ( id_cliente == 0 ) {
     qDebug( "Cliente .:Consumidor final:. no posee cuenta corriente." );
     return QString::number( MCuentaCorriente::ErrorNumeroCuenta );
 }
 QSqlQuery cola( QString( "SELECT numero_cuenta FROM ctacte WHERE id_cliente = %1" ).arg( id_cliente ) );
 if( cola.next() )
 { return cola.record().value(0).toString(); }
 else
 {
        qDebug( "MCuentaCorriente::obtenerNumeroCuentaCorriente::Error al buscar el numero de cuenta para el cliente solicitado - posiblemente no tenga cuenta corriente habilitada" );
        return QString::number( MCuentaCorriente::ErrorNumeroCuenta );
 }
}


/*!
    \fn MCuentaCorriente::verificarSaldo( const QString numero_cuenta, double aplicar )
        Verifica el saldo para un cliente especifico dado el saldo actual y el aplicar para ver si se excede o no.
        @param numero_cuenta Numero de cuenta corriente
        @param aplicar Cantidad de saldo a aplicar
        @return Entero segun defines CTACTE_LIMITE_xxxxxxx o el numero de error.

 */
int MCuentaCorriente::verificarSaldo( const QString numero_cuenta, double aplicar )
{
 // Busco el saldo del cliente
 QSqlQuery cola;
 if( cola.exec(QString( "SELECT saldo, limite FROM ctacte WHERE numero_cuenta = %1" ).arg( numero_cuenta ) ) ) {
     if( cola.next() )
     {
      if( cola.record().value(0).toDouble() + aplicar > cola.record().value(1).toDouble() )
      {
            qDebug( "Limite de la cuenta corriente solicitada excedido" );
            return MCuentaCorriente::LimiteExcedido;
      }
      else if( cola.record().value(0).toDouble() + aplicar == cola.record().value(1).toDouble() )
      {
            qDebug( "Limite de la cuenta corriente solicitada alcanzado" );
            return MCuentaCorriente::EnLimite;
      }
      else
      {
            qDebug( "limite de la cuenta corriente solicitada correcto" );
            return MCuentaCorriente::LimiteCorrecto;
      }
     }
     else
     {
      // Error al buscar
      qWarning( "Error al buscar el limite de la cuenta corriente solicitada ( next )" );
      qDebug( qPrintable( cola.lastError().text() ) );
      qDebug( qPrintable( cola.executedQuery() ) );
      return MCuentaCorriente::ErrorBuscarLimite;
     }
 } else {
     // Error al buscar
     qWarning( "Error al buscar el limite de la cuenta corriente solicitada ( exec )" );
     qDebug( qPrintable( cola.lastError().text() ) );
     qDebug( qPrintable( cola.executedQuery() ) );
     return MCuentaCorriente::ErrorBuscarLimite;
 }
 return -10;
}


/*!
    \fn MCuentaCorriente::actualizarSaldo( const QString numero_cuenta, const double aplicar )
        Actualiza el saldo en el campo de la cuenta corriente
        @param numero_cuenta Numero de cuenta
        @param aplicar diferencia a aplicar ( si es positiva -> contra el cliente / si es negativa -> a favor del cliente )
        @return Realizado o no.
 */
bool MCuentaCorriente::actualizarSaldo( const QString numero_cuenta, const double aplicar )
{
 QSqlQuery cola( QString( "SELECT saldo FROM ctacte WHERE numero_cuenta = %1" ).arg( numero_cuenta ) );
 if( cola.next() )
 {
        double anterior = cola.record().value(0).toDouble();
        anterior += aplicar;
        if(  cola.exec( QString( "UPDATE ctacte SET saldo = %1 WHERE numero_cuenta = %2" ).arg( anterior ).arg( numero_cuenta ) ) )
        {
                qDebug( "Saldo actualizado correctamente" );
                return true;
        }
        else
        {
                qWarning( "Error al buscar el saldo de la cuenta corriente solicitada al intentar actualizar el saldo" );
                qDebug( qPrintable( cola.lastError().text() ) );
                qDebug( qPrintable( cola.executedQuery() ) );
                return false;
        }
 }
 else
 {
  qWarning( "Error al intentar actualizar el saldo de la cuenta corriente solicitada" );
  qDebug( qPrintable( cola.lastError().text() ) );
  qDebug( qPrintable( cola.executedQuery() ) );
  return false;
 }
}


/*!
    \fn MCuentaCorriente::saldo( const QString numero_cuenta )
    Devuelve el saldo de una cuenta corriente
    \param numero_cuenta Numero de la cuenta corriente
    \return El saldo o MCuentaCorriente::ErrorBuscarSaldo
 */
double MCuentaCorriente::saldo( const QString numero_cuenta )
{
  QSqlQuery cola( QString( "SELECT saldo FROM ctacte WHERE numero_cuenta = %1" ).arg( numero_cuenta ) );
 if( cola.next() )
 {
  return cola.record().value(0).toDouble();
 }
 else
 {
  qWarning( "MCuentaCorriente::saldo::Error al intentar buscar el saldo de la cuenta corriente solicitada" );
  qDebug( qPrintable( cola.lastError().text() ) );
  qDebug( qPrintable( cola.executedQuery() ) );
  return MCuentaCorriente::ErrorBuscarSaldo;
 }
}

#include "preferencias.h"
/*!
 * \fn MCuentaCorriente::agregarCuentaCorrientePredeterminada( const int id_cliente, const QDateTime fecha_alta )
 *  Genera una cuenta corriente nueva para el cliente seleccionado en la fecha de alta elegida con los valores de saldo inicial y limite de credito seleccionados en las preferencias
 * @param id_cliente Identificador del cliente al cual se le abrirá la cuenta corriente.
 * @param fecha_alta Fecha en que se dará de alta la cuenta corriente
 * @return Verdadero si se pudo crear
 */
bool MCuentaCorriente::agregarCuentaCorrientePredeterminada(const int id_cliente, const QDateTime fecha_alta )
{
    QSqlQuery cola;
    // Datos predeterminados
    preferencias *p = preferencias::getInstancia();
    p->beginGroup( "Preferencias" );
    p->beginGroup( "CtaCte" );
    double saldo = preferencias::getInstancia()->value( "saldo-inicial", 0.0 ).toDouble();
    double limite = preferencias::getInstancia()->value( "limite", 1000.0 ).toDouble();
    p->endGroup();
    p->endGroup();
    p=0;
    delete p;
    // Numero de cuenta
    cola.prepare( "INSERT INTO ctacte( numero_cuenta, id_cliente, fecha_alta, saldo, limite ) VALUES( :num_cuenta, :id_cliente, :fecha_alta, :saldo, :limite )" );
    QString num_cuenta = QString( "%L1" ).arg( id_cliente );
    cola.bindValue( ":num_cuenta", num_cuenta );
    cola.bindValue( ":id_cliente", id_cliente );
    cola.bindValue( ":fecha_alta", fecha_alta );
    cola.bindValue( ":saldo", saldo );
    cola.bindValue( ":limite", limite );
    if( cola.exec() ) {
        return true;
    } else {
        qDebug( "MCuentaCorriente::Error al intentar insertar una cuenta corriente predeterminada" );
        qDebug( QString( "%1" ).arg( cola.lastError().text() ).toLocal8Bit() );
        return false;
    }
}

/*!
 * \fn MCuentaCorriente::filtrarSoloDeudoras( bool sino )
 * Setea el filtro del modelo para que solo tenga las cuentas tales que el saldo es >= que el limite
 * \param sino Habilitado el filtro o no
 */
void MCuentaCorriente::filtrarSoloDeudoras( bool sino )
{
    if( sino ) {
        this->setFilter( "saldo >= limite" );
    } else {
        this->setFilter( "" );
    }
}

/*!
 * \fn MCuentaCorriente::existeCuenta( cost QString num_cuenta )
 * Realiza la busqueda de si existe la cuenta corriente o no
 * \param num_cuenta Numero de cuenta corriente
 * \return Verdadero si existe, falso si no existe o hubo un error
 */
bool MCuentaCorriente::existeCuenta( const QString num_cuenta )
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT COUNT(numero_cuenta) FROM ctacte WHERE num_cuenta = %1" ).arg( num_cuenta )  ) )
    {
        if( cola.next() ) {
            if( cola.record().value(0).toInt() <= 0 ) { return false; } else { return true; }
        } else {
            qDebug( "Error al intentar hacer next en la cola para averiguar si existe el numero de cuenta" );
        }
    } else {
        qDebug( "Error al hacer next en la cola para averiguar si existe el numero de cuenta" );
    }
    qDebug( cola.lastError().text().toLocal8Bit() );
    qDebug( cola.lastQuery().toLocal8Bit() );
    return false;
}

/*!
 * \fn MCuentaCorriente::existeCuentaCliente( cost int id_cliente )
 * Realiza la busqueda de si existe la cuenta corriente o no del cliente pasado como parametro
 * \param num_cuenta Numero de cuenta corriente
 * \return Verdadero si existe, falso si no existe o hubo un error
 */
bool MCuentaCorriente::existeCuentaCliente( const int id_cliente )
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT COUNT(numero_cuenta) FROM ctacte WHERE id_cliente = %1" ).arg( id_cliente )  ) )
    {
        if( cola.next() ) {
            if( cola.record().value(0).toInt() <= 0 ) { return false; } else { return true; }
        } else {
            qDebug( "Error al intentar hacer next en la cola para averiguar si existe el numero de cuenta de un cliente" );
        }
    } else {
        qDebug( "Error al hacer next en la cola para averiguar si existe el numero de cuenta de un cliente" );
    }
    qDebug( cola.lastError().text().toLocal8Bit() );
    qDebug( cola.lastQuery().toLocal8Bit() );
    return false;
}

/*!
 * \fn MCuentaCorriente::modificarLimite( const QString numero_cuenta, const double nuevo_limite, QModelIndex indice )
 * Modifica el límite de la cuenta corriente con el nuevo valor si es valido y emite una actualización del indice para refrescar la vista.
 * \param numero_cuenta Numero de cuenta a actualizar
 * \param nuevo_limite Nuevo limite a aplicar
 * \returns Verdadero si el limite se modifico correctamente.
 */
bool MCuentaCorriente::modificarLimite( const QString numero_cuenta, const double nuevo_limite )
{
    if( numero_cuenta.isEmpty() || numero_cuenta.isNull() || nuevo_limite < 0 ) {
        return false;
    }
    QSqlQuery cola;
    if( cola.exec( QString( "UPDATE ctacte SET limite = %2 WHERE num_cuenta = %1" ).arg( numero_cuenta ).arg( nuevo_limite ) ) ) {
        qDebug( "Limite de cuenta corriente modificado correctamente." );
        return true;
    } else {
        qWarning( "Error al intentar actualizar el limite para una cuena corriente." );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
    }
    return false;
}

/*!
 * \fn MCuentaCorriente::modificarLimite( const QString numero_cuenta, const double nuevo_limite, QModelIndex indice )
 * Modifica el límite de la cuenta corriente con el nuevo valor si es valido y emite una actualización del indice para refrescar la vista.
 * \param numero_cuenta Numero de cuenta a actualizar
 * \param nuevo_limite Nuevo limite a aplicar
 * \param indice Indice con el cual se hara un emit dataChanged()
 * \returns Verdadero si el limite se modifico correctamente.
 */
bool MCuentaCorriente::modificarLimite( const QString numero_cuenta, const double nuevo_limite, QModelIndex indice )
{
    if( !indice.isValid() ) { return false; }
    if( modificarLimite( numero_cuenta, nuevo_limite ) ) {
        emit dataChanged( indice, indice );
        return true;
    }
    return false;
}

/*!
 * \fn MCuentaCorriente::limite( const QString numero_cuenta )
 * Devuelve el limite actual de la cuenta corriente.
 * \param numero_cuenta Numero de cuenta para devolver el limite.
 * \returns Limite, 0 si la cuenta esta suspendida o -1 si hubo un error.
 */
double MCuentaCorriente::limite( const QString numero_cuenta )
{
    if( numero_cuenta.isEmpty() ) {
        qDebug( "Numero de cuenta invalido" );
        return -1;
    }
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT limite FROM ctacte WHERE numero_cuenta = %1" ).arg( numero_cuenta ) ) ) {
        if( cola.next() ) {
            return cola.record().value(0).toDouble();
        } else {
            qDebug( "Error al hacer next en la cola de obtención del limite de ctacte" );
        }
    } else {
        qDebug( "Error al hacer exec en la cola de obtención del limite de ctacte" );
    }
    qDebug( cola.lastError().text().toLocal8Bit() );
    qDebug( cola.lastQuery().toLocal8Bit() );
    return false;
}

