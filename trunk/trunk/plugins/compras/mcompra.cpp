/***************************************************************************
 *   Copyright (C) 2006 by Esteban Zeller & Daniel Sequeira		   *
 *   juiraze@yahoo.com.ar  - daniels@hotmail.com			   *
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
#include "mcompra.h"

#include <QSqlRecord>
#include <QSqlError>
#include <QDate>

MCompra::MCompra(QObject *parent, bool relaciones )
 : QSqlRelationalTableModel(parent)
{
    inicializar();
    if( relaciones )
        relacionar();
}

void MCompra::inicializar()
{
    setTable( "compras" );
    setHeaderData( 0, Qt::Horizontal, "#ID" );
    setHeaderData( 1, Qt::Horizontal, "Proveedor" );
    setHeaderData( 2, Qt::Horizontal, "Fecha" );
    setHeaderData( 3, Qt::Horizontal, "Costo" );
    setHeaderData( 4, Qt::Horizontal, "#ID caja" );
}

void MCompra::relacionar()
{
    setRelation( 1, QSqlRelation( "proveedor", "id", "nombre" ) );
}

#include "mmovimientoscaja.h"
#include "mcajas.h"
#include "eregistroplugins.h"
/*!
    \fn MCompra::agregarCompra( QVariant fecha, QVariant proveedor )
	Función que agrega un registro de compra directamente
	@param fecha QDate con la fecha de la compra
	@param proveedor Id del proveedor
        @param total Total de la compra
        @param contado Indica si la compra se realizo al contado y de ser cierto genera el movimiento de caja correspondiente.
	@return Verdadero o falso si fue exitoso o no
 */
bool MCompra::agregarCompra( QVariant fecha, QVariant proveedor, double total, bool contado )
{
 int id_caja = 0;
 if( contado ) {
     /*if( ERegistroPlugins::getInstancia()->existePlugin( "caja" ) ) {*/
         // Agrego el movimiento en la caja predeterminada
         MMovimientosCaja *m = new MMovimientosCaja();
         if( !m->agregarMovimiento( MCajas::cajaPredeterminada(), "Pago de compra al contado a proveedor", QString(), 0.0, total ) ) {
             qDebug( "Error al agregar el movimiento de caja cuando se pago una compra en contado.");
             return false;
         }
         id_caja = m->ultimoIdInsertado();
         delete m;
     /*}*/
 }
 QSqlRecord regCompra = record();
 regCompra.remove( 0 );
 regCompra.setValue( "fecha"       , fecha );
 regCompra.setValue( "id_proveedor", proveedor );
 regCompra.setValue( "total"       , total );
 if( contado ) {
     regCompra.setValue( "id_caja", id_caja );
 } else {
     regCompra.setNull( "id_caja" );
 }
 if( !insertRecord( -1, regCompra ) )
 {
  qDebug( "Error de insercion de registro de compra" );
  qDebug( QString( "Detalles: tipo: %1, errno: %2, descripcion: %3" ).arg( lastError().type() ).arg( lastError().number() ).arg( lastError().text() ).toLocal8Bit() );
  return false;
 }
 else
 { return true; }
}


/*!
    \fn MCompra::data(const QModelIndex &index, int role ) const
 */
QVariant MCompra::data(const QModelIndex &index, int role ) const
{
 switch( role )
 {
	case Qt::TextAlignmentRole:
	{
		if( index.column() == 2 )
		{
			return int( Qt::AlignHCenter | Qt::AlignVCenter );
		}
		else if( index.column() == 3 )
		{
			return int( Qt::AlignRight | Qt::AlignVCenter );
		}
		else
		{
			return QSqlRelationalTableModel::data( index, role );
		}
		break;
	}
	case Qt::DisplayRole:
	{
		switch( index.column() )
		{
			case 3:
            {
                return QString( "$ %L1" ).arg( QSqlRelationalTableModel::data( index, role ).toDouble(), 10, 'f', 2 );
				break;
			}
			default:
			{
				return QSqlRelationalTableModel::data( index, role );
				break;
			}
		}
		break;
	}
	case Qt::EditRole:
	{
		switch( index.column() )
		{
			case 3:
			{
				return QSqlRelationalTableModel::data( index, role ).toDouble();
				break;
			}
			case 2:
			{
				return QSqlRelationalTableModel::data( index, role ).toDate();
				break;
			}
			default:
			{
				return QSqlRelationalTableModel::data( index, role );
			}
		}
	}
	case Qt::ToolTipRole:
	case Qt::StatusTipRole:
	{
		return QVariant( "Haga doble click o seleccione y F2 para editar" );
		break;
	}
	default:
	{
		return QSqlRelationalTableModel::data( index, role );
		break;
	}
 }
}

#include <QSqlQuery>
/*!
 * \fn MCompra::ultimoId()
 */
int MCompra::ultimoId()
{ return this->query().lastInsertId().toInt(); }

/*!
 * \fn MCompra::flags( const QModelIndex& index ) const
 *
 */
Qt::ItemFlags MCompra::flags(const QModelIndex& /*index*/) const
{
 return QFlags<Qt::ItemFlag>( !Qt::ItemIsEditable |  Qt::ItemIsSelectable | Qt::ItemIsEnabled );
}

#include "mcajas.h"
#include "mmovimientoscaja.h"
#include "mproductos.h"
/*!
 * \fn MCompra::eliminarCompra( int id_compra )
 * Elimina la compra y reajusta los datos de productos y caja correspondientes
 * \param id_compra Identificador de compra
 * \return Verdadero si se pudieron realizar todas las compras
 */
bool MCompra::eliminarCompra( int id_compra )
{
 return false;
 /*
 Ajustar saldo de caja predeterminada
 Ajustar por cada item el stock de los productos
 Eliminar los items de la compra
 Eliminar la compra propiamente dicha
 */
 QSqlDatabase::database().transaction();
 QSqlQuery cola;
 // Ajusto el movimiento de caja
 double costo_compra = -1.0;
 bool contado = false;
 if( !cola.exec( QString( "SELECT total, contado FROM compras WHERE id_compra = %1" ).arg( id_compra ) ) ) {
     qWarning( "Error al buscar el importe de la compra seleccionada" );
     qDebug( "Error al ejecutar la cola de busqueda de importe del registro de compra" );
     qDebug( cola.lastError().text().toLocal8Bit() );
     qDebug( cola.lastQuery().toLocal8Bit() );
     QSqlDatabase::database().rollback();
     return false;
 } else {
     cola.next();
     costo_compra = cola.record().value(0).toDouble();
     contado = cola.record().value(1).toBool();
 }
 if( costo_compra <= 0.0 ) {
     qWarning( "Error al buscar el precio <= 0 " );
     QSqlDatabase::database().rollback();
     return false;
 }
 if( contado ) {
     // Ajusto el saldo de caja
     MMovimientosCaja *mc = new MMovimientosCaja();
     if( !mc->agregarMovimiento(
                 MCajas::cajaPredeterminada(),
                 "Eliminacion de compra efectuada en efectivo",
                 QString(),
                 costo_compra
                 ) ) {
         qWarning( "No se pudo generar el ajuste de caja necesario para la eliminacion de la compra" );
         qDebug( "Error al intentar guardar el registro de movimiento de caja para ajustar el saldo al eliminar una compra" );
         QSqlDatabase::database().rollback();
         delete mc;
         return false;
     }
     delete mc;
 }
 // Ajusto el stock
 if( cola.exec( QString( "SELECT id_producto, cantidad, texto FROM compras_productos WHERE id_compra = %1" ).arg( id_compra ) ) ) {
     while( cola.next() ) {
         int id_producto = cola.record().value(0).toInt();
         int cantidad = cola.record().value(1).toDouble();
         if( !MProductos::modificarStock( id_producto, (-1) * cantidad ) ) {
             qDebug( QString( "No se pudo ajustar el stock del producto comprado, id = %1" ).arg( id_producto ).toLocal8Bit() );
             QSqlDatabase::database().rollback();
             return false;
         }
     }
 } else {
     qWarning( "No se pudo consultar los productos de la compra" );
     qDebug( "Error al ejecutar la cola de consulta de productos de compra" );
     qDebug( cola.lastError().text().toLocal8Bit() );
     qDebug( cola.lastQuery().toLocal8Bit() );
     QSqlDatabase::database().rollback();
     return false;
 }
 // Elimino los items de la compra
 if( !cola.exec( QString( "DELETE FROM compras_productos WHERE id_compra = %1 LIMIT 1" ).arg( id_compra ) ) ) {
     qWarning( "No se pudo eliminar los productos de la compra" );
     qDebug( "Error al ejecutar la cola de eliminación de registros de productos de compra" );
     qDebug( cola.lastError().text().toLocal8Bit() );
     qDebug( cola.lastQuery().toLocal8Bit() );
     QSqlDatabase::database().rollback();
     return false;
 }
 // Elimino la compra propiamente dicha
 if( !cola.exec( QString( "DELETE FROM compras WHERE id_compra = %1 LIMIT 1" ).arg( id_compra ) ) ) {
     qWarning( "No se pudo eliminar el registro de la compra" );
     qDebug( "Error al ejecutar la cola de eliminación de registro de compra" );
     qDebug( cola.lastError().text().toLocal8Bit() );
     qDebug( cola.lastQuery().toLocal8Bit() );
     QSqlDatabase::database().rollback();
     return false;
 }
 return true;
}