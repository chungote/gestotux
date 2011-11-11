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
#include "mrecargoshechos.h"
#include <QSqlRelation>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include "mcuentacorriente.h"
#include "mitemcuentacorriente.h"
#include "mrecargos.h"

MRecargosHechos::MRecargosHechos(QObject *parent)
 : QSqlRelationalTableModel(parent)
{
    inicializar();
}

void MRecargosHechos::inicializar()
{
    setTable( "recargos_hechos" );
    setHeaderData( 0, Qt::Horizontal, tr( "#ID Periodo Servicio" ) );
    setHeaderData( 1, Qt::Horizontal, tr( "#ID Servicio" ) );
    setHeaderData( 2, Qt::Horizontal, tr( "#ID Cliente" ) );
    setHeaderData( 3, Qt::Horizontal, tr( "#ID Recargo" ) );
    setHeaderData( 4, Qt::Horizontal, tr( "Fecha Generado" ) );
    setHeaderData( 5, Qt::Horizontal, tr( "Detalle" ) );
    setHeaderData( 6, Qt::Horizontal, tr( "Costo" ) );
    setHeaderData( 7, Qt::Horizontal, tr( "#ID Item Cta Cte" ) );
    setHeaderData( 8, Qt::Horizontal, tr( "#ID Recibo" ) );
}

void MRecargosHechos::relacionar()
{
    setRelation( 2, QSqlRelation( "clientes", "id", "razon_social" ) );
    setRelation( 1, QSqlRelation( "servicios", "id_servicio", "nombre" ) );
}

bool MRecargosHechos::setData(const QModelIndex& item, const QVariant& value, int role)
{
    return QSqlRelationalTableModel::setData(item, value, role);
}

QVariant MRecargosHechos::data(const QModelIndex& item, int role) const
{
    switch( role )
    {
        case Qt::DisplayRole:
        {
            switch( item.column() ) {
                case 4:
                {
                    return QSqlRelationalTableModel::data( item, role ).toDateTime().toLocalTime();
                    break;
                }
                case 6:
                {
                    return QString::number( QSqlRelationalTableModel::data( item, role ).toDouble() ).prepend( "$ ");
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
        {   return QSqlRelationalTableModel::data(item, role);  }
    }
}

/*!
 * \fn MRecargosHechos::agregarRecargo( const int id_periodo_servicio, const int id_servicio, const int id_cliente, const int id_recargo, const QDateTime fecha, const QString detalle, const double costo )
 * Agrego un registro del tipo recargo para un servicio especifico y el cliente especificado.
 * Si no se especifica detalle se generará una entrada predeterminada.
 * Si no se especifica el costo se autocalculara.
 * Aparte de generar el registro correspondiente agrega la operacion en la cuenta corriente y guarda el identificador en el registro.
 * El registro va a estar como no pagado automaticamente. ( id_recibo = null )
 * \param id_periodo_servicio Identificador del periodo para el servicio.
 * \param id_servicio Identificador del servicio
 * \param id_cliente Identificador del cliente
 * \param id_recargo Identificador del recargo que estoy haciendo.
 * \param fecha Fecha y hora generado
 * \param detalle Detalle del item para la cuenta corriente y la factura
 * \param costo Costo total del recargo
 * \returns Verdadero si ha podido ser guardado.
 */
bool MRecargosHechos::agregarRecargo( const int id_periodo_servicio, const int id_servicio, const int id_cliente, const int id_recargo, const QDateTime fecha, QString detalle, double costo )
{
    // Verifico los defaults
    if( detalle.isEmpty() ) {
        detalle.append("Recargor por pago fuera de termino");
    }
    if( costo ) {
        costo = MRecargos::calcularRecargo( id_recargo );
    }

    // Veo de actualizar la cuenta corriente del cliente
    QString ctacte = MCuentaCorriente::obtenerNumeroCuentaCorriente( id_cliente );
    if( ctacte == QString::number( MCuentaCorriente::ErrorNumeroCuenta )
        || ctacte == QString::number( MCuentaCorriente::ErrorClienteInvalido ) ) {
        qDebug( "El cliente no posee una cuenta corriente!!! ( aseveracion que implica error anterior en el sistema!)" );
        qDebug( QString( "ID Cliente: %1" ).arg( id_cliente ).toLocal8Bit() );
        return false;
    }
    /// @todo Verificar identificador de referencia pasado como parametro a esta funcion
    // Teoricamente el identificador sirve para vincular de vuelta el item con su origen. ¿Que numero colocamos aca?
    // Que numero de comprobante posee?? teoricamente ninguno,a si que le mandamos una cadena vacia.
    int id_ctacte = MItemCuentaCorriente::agregarOperacion( ctacte,
                                                            QString(), // no tenemos numero de comprobante
                                                            0, // tampoco tenemos refencia
                                                            MItemCuentaCorriente::RecargoCobroServicio,
                                                            fecha.date(),
                                                            detalle,
                                                            costo );
    if( id_ctacte == -1 ) {
        qDebug( "No se pudo guardar el item en la cuenta corriente. Verificar log." );
        return false;
    }

    // Intento generar el registro
    QSqlQuery cola;
    cola.prepare(
                "INSERT INTO recargos_hechos"
                "( id_periodo_servicio, id_servicio, id_cliente, fecha, detalle, precio, id_ctacte ) VALUES"
                "( :id_periodo_servicio, :id_servicio, :id_cliente, :fecha, :detalle, :precio, :id_ctacte )"
                );
    cola.bindValue( ":id_periodo_servicio", id_periodo_servicio );
    cola.bindValue( ":id_servicio", id_servicio );
    cola.bindValue( ":id_cliente", id_cliente );
    cola.bindValue( ":id_recargo", id_recargo );
    cola.bindValue( ":fecha", fecha );
    cola.bindValue( ":detalle", detalle );
    cola.bindValue( ":precio", costo );
    cola.bindValue( ":id_ctacte", id_ctacte );
    if( cola.exec() ) {
        qDebug( "Registro de recargo insertado correctamente" );
        return true;
    } else {
        qDebug( "Cola de insercion de recargo incorrecta" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
    }
    return false;
}
