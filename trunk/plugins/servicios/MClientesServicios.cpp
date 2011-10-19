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

#include "MClientesServicios.h"

MClientesServicios::MClientesServicios(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
  inicializar();
  // Relaciones
  relacionar();

}

void MClientesServicios::inicializar()
{
    this->setTable( "servicios_clientes" );
    this->setHeaderData( 0, Qt::Horizontal, "Servicio" );
    this->setHeaderData( 1, Qt::Horizontal, "Cliente");
    this->setHeaderData( 2, Qt::Horizontal, "Fecha Alta" );
    this->setHeaderData( 3, Qt::Horizontal, "Fecha Baja" );
}

void MClientesServicios::relacionar()
{
    this->setRelation( 1, QSqlRelation( "clientes", "id", "razon_social" ) );
    this->setRelation( 0, QSqlRelation( "servicios", "id_servicio", "nombre" ) );
}

void MClientesServicios::filtrarPorCliente( const int id_cliente )
{
    this->setFilter( QString( "servicios_clientes.id_cliente = %1 ").arg( id_cliente ) );
}

void MClientesServicios::filtrarPorServicio( const int id_servicio )
{
    this->setFilter( QString( "servicios_clientes.id_servicio = %1 ").arg( id_servicio ) );
}

QVariant MClientesServicios::data(const QModelIndex &item, int role) const
{
 switch( item.column() ) {
    case 2:
    case 3:
    {
     switch( role ) {
        case Qt::TextAlignmentRole:
        {  return int( Qt::AlignCenter | Qt::AlignVCenter ); break; }
        default:
        { return QSqlRelationalTableModel::data( item, role ); break; }
     }
     break;
    }
    default:
    { return QSqlRelationalTableModel::data( item, role ); break; }
 }
}

Qt::ItemFlags MClientesServicios::flags(const QModelIndex& index) const
{
 return QFlags<Qt::ItemFlag>( !Qt::ItemIsEditable |  Qt::ItemIsSelectable | Qt::ItemIsEnabled );
}

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <EReporte.h>
#include <QDate>
#include "mcobroservicioclienteperiodo.h"
#include <QMessageBox>
/*!
 * @fn MClientesServicios::darDeBaja( int id_cliente, int id_servicio, QString razon )
 * Da de baja al cliente seleccionado segun la razon espcificada
 * Si no se especifica una razon, se coloca una predeterminada.
 * La fecha de baja es cuando se realiza la operación.
 * Si la baja se realizo correctamente, se imprime el comprobante de baja. El no imprimirlo, no modifica el resultado.
 * \param id_cliente Identificador del cliente.
 * \param id_servicio Identificador del servicio.
 * \param razon Texto de por que da de baja el servicio.
 * \return Verdadero se pudo realizar la baja.
 */
bool MClientesServicios::darDeBaja( int id_cliente, int id_servicio, QString razon ) {
    // Verificar existencia de la asociacion
    QSqlQuery cola;
    if( !cola.exec( QString( "SELECT COUNT(id_cliente) FROM servicios_clientes WHERE id_cliente = %1 AND id_servicio = %2" ).arg( id_cliente ).arg( id_servicio ) ) ) {
        qDebug( "Error al ejecutar la cola de obtencion de lciente servicio." );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
    } else {
        if( !cola.next() ) {
            qDebug( "Error al hacer next en la cola de obtencion del cliente servicio" );
            qDebug( cola.lastQuery().toLocal8Bit() );
            return false;
        } else {
            if( cola.record().value(0).toInt() <= 0 ) {
                qWarning( "El cliente seleccionado no esta adherido al servicio especificado" );
                return false;
            }
        }
    } // Existe
    // verificar deudas existentes respecto a servicios
    if( MCobroServicioClientePeriodo::esDeudor( id_cliente, id_servicio ) ) {
        QMessageBox::warning( 0, "Saldo incompleto", "El cliente todavía tiene cuotas pendientes de pago. <br/> No se podrá realizar la baja hasta que se paguen las deudas pendientes" );
        return false;
    }
    // verificar fecha respecto al periodo del servicio y facturar lo que falte ? ( ya esta echo por el punto anterior )
    // Verificar la razon
    if( razon.isEmpty() ) {
        qDebug( "Razon de baja de adhesion desconocida. Colocando la default." );
        razon = "Desconocida - No Especificada.";
    }
    // Ingresar baja
    if( !cola.prepare( "UPDATE servicios_clientes SET fecha_baja = :fecha, razon = :razon WHERE id_cliente = :id_cliente AND id_servicio = :id_servicio" ) ) {
        qDebug( "Error al preparar la cola" );
        return false;
    }
    cola.bindValue( "fecha" , QDate::currentDate() );
    cola.bindValue( "razon", razon );
    cola.bindValue( "id_cliente",  id_cliente );
    cola.bindValue( "id_servicio", id_servicio );
    if( !cola.exec() ) {
        qDebug( "Error al ejecutar la cola de inservion de fecha de baja y razon en la tabla de servicios_clientes" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
        return false;
    }
    // Imprimir comprobante de baja
    EReporte *rep = new EReporte( 0 );
    ParameterList parametros;
    parametros.append( Parameter( "id_cliente", id_cliente ) );
    parametros.append( Parameter( "id_servicio", id_servicio ) );
    parametros.append( Parameter( "razon", razon ) );
    parametros.append( Parameter( "fecha", QDate::currentDate() ) );
    rep->especial( "baja-servicio", parametros );
    rep->hacer();
    delete rep;
    return true;
}
