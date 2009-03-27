/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   *
 *   juiraze@yahoo.com.ar   *
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
#include "mtproductospresupuesto.h"

#include <QSqlQuery>
#include <QStringList>
#include <QSqlError>
#include <QSqlRecord>

MTProductosPresupuesto::MTProductosPresupuesto( QObject * parent )
 : QSqlRelationalTableModel( parent )
{
 setTable( "presupuestos_productos" );
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "#Presupuesto" );
 setHeaderData( 2, Qt::Horizontal, "Producto" );
   setRelation( 2, QSqlRelation( "producto", "id", "nombre" ) );
 setHeaderData( 3, Qt::Horizontal, "Cantidad" );
 setHeaderData( 4, Qt::Horizontal, "Precio Unitario" );
 setHeaderData( 5, Qt::Horizontal, "Sub-Total" );
 setEditStrategy( QSqlTableModel::OnManualSubmit );
 connect( this, SIGNAL( beforeInsert( QSqlRecord & ) ), this, SLOT( seteaPresupuesto( QSqlRecord & ) ) );
}


MTProductosPresupuesto::~MTProductosPresupuesto()
{
}

/*!
    \fn MTProductosPresupuesto::data ( const QModelIndex & item, int role ) const
 */
QVariant MTProductosPresupuesto::data( const QModelIndex & item, int role ) const
{
 if( item.row() >= QSqlRelationalTableModel::rowCount() )
 {
  switch( item.column() )
  {
	case 2:
	{
		if( role != Qt::DisplayRole )
		{
			return QVariant();
		}
		return "Cant:";
		break;
	}
	case 3:
	{
		if( role != Qt::DisplayRole )
		{
			return QVariant();
		}
		return QString( "%L1" ).arg( QSqlRelationalTableModel::rowCount() );
		break;
	}
	case 4:
	{
		if( role != Qt::DisplayRole )
		{
			return QVariant();
		}
		return "Total:";
		break;
	}
	case 5:
	{
		if( role != Qt::DisplayRole )
		{ return QVariant(); }
		// Calculo el precio total
		double total = 0;
		for( int i = 0; i< QSqlRelationalTableModel::rowCount(); i++ )
		{
			double temp = data( index( i, 5 ), Qt::EditRole ).toDouble();
			if( temp > 0 )
			{ total += temp; }
		}
		return QString( "$ %L1" ).arg( total );
		break;
	}
	default:
	{
		return QVariant();
		break;
	}
  }
 }
 switch( item.column() )
 {
   // id del producto
   case 2:
   {
	switch( role )
	{
		case Qt::UserRole:
		{
			// retorno el id, si no hay uno puesto, retorno -1
			if( QSqlTableModel::data( item, Qt::DisplayRole ).toInt() > 0 )
			{
				return QSqlTableModel::data( item, Qt::EditRole ).toInt();
			}
			else
			{
				return -1;
			}
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
   // Precio Unitario
   case 4:
   {
	switch( role )
	{
		case Qt::DisplayRole:
		{
			return QString( "$ %L1" ).arg( buscarPrecioProducto( item.row() ).toDouble() );
			break;
		}
		case Qt::EditRole:
		{
			return buscarPrecioProducto( item.row() ).toDouble();
			break;
		}
		default:
		{
			return QVariant();
			break;
		}
	}
	break;
   }
   // Sub Total
   case 5:
   {
	if( role == Qt::DisplayRole || role == Qt::EditRole )
	{
		double cant = QSqlTableModel::data( index( item.row(), 3 ), Qt::EditRole ).toDouble();
		double precio = buscarPrecioProducto( item.row() ).toDouble();
		if( cant <= 0 && precio <= 0 )
		{
			if( role == Qt::EditRole ) { return 0.0; }
			else { return QVariant(); }
		}
		else
		{
			if( role == Qt::EditRole ) { return cant*precio; }
			else { return QString( "$ %L1" ).arg( cant*precio ); }
		}
	}
	else
	{
		return QVariant();
	}
	break;
   }
   default:
   {
	return QSqlRelationalTableModel::data( item, role );
  	break;
   }
 }
}


/*!
    \fn MTProductosPresupuesto::QAbstractItemModel::flags ( const QModelIndex & index ) const
 */
Qt::ItemFlags MTProductosPresupuesto::flags ( const QModelIndex & index ) const
{
 if( index.row() == QSqlTableModel::rowCount() + 1 )
 {
  return int( !Qt::ItemIsEnabled );
 }
 if( index.column() >= 4 )
 {
  return int( !Qt::ItemIsEnabled );
 }
 else
 {
    return QSqlRelationalTableModel::flags( index );
 }
}


/*!
    \fn MTProductosPresupuesto::columnCount( QModelIndex &parent ) const
 */
int MTProductosPresupuesto::columnCount( const QModelIndex &parent ) const
{
  int conteo = QSqlRelationalTableModel::columnCount() + 2;
  return conteo;
}

int MTProductosPresupuesto::rowCount( const QModelIndex &parent ) const
{
  int conteo = QSqlRelationalTableModel::rowCount() + 1;
  return conteo;
}

#include <QSqlError>
/*!
    \fn MTProductosPresupuesto::guardar( const int id_presupuesto )
 */
bool MTProductosPresupuesto::guardar( const int id_presupuesto )
{
 QSqlQuery cola;
 if( cola.exec( QString( "UPDATE presupuesto_productos SET id_presupuesto = %1 WHERE id_presupuesto = -1" ).arg( id_presupuesto ) ) )
 {
  return true;
 }
 else
 {
  qWarning( qPrintable( "Error db: " + this->query().lastError().text() ) );
  return false;
 }
}

bool MTProductosPresupuesto::setData( const QModelIndex &item, const QVariant &value, int role )
{
 switch( item.column() )
 {
	// Producto
	case 2:
	{
		// Cuando se setea el producto busco el precio e intento calcular el subtotal
		bool estado = QSqlRelationalTableModel::setData( item, value, role );
		if( role == Qt::EditRole )
		{
			QVariant estado2 = buscarPrecioProducto( item.row() );
			if( estado && estado2.isValid() )
			{
				emit dataChanged( index( item.row(), 4 ), index( item.row(), 5 ) ); // subtotal
				emit dataChanged( index( QSqlRelationalTableModel::rowCount() + 1, 5 ), index( QSqlRelationalTableModel::rowCount() + 1, 5 ) ); // total
				return true;
			}
			else
			{
				qDebug( "Error en la insercion del precio" );
				return false;
			}
		}
	}
	// cantidad
	case 3:
	{
		// Cuando se actualiza la columna de cantidad intento actualizar el subtotal y total
		if( QSqlRelationalTableModel::setData( item, value, role ) )
		{
			emit dataChanged( index( item.row(), 4 ), index( item.row(), 5 ) );
			emit dataChanged( index( QSqlRelationalTableModel::rowCount() + 1, 2 ), index( QSqlRelationalTableModel::rowCount()+1, 5 ) );
			return true;
		}
		else
		{
			return false;
		}
		break;
	}
	default:
	{
		return QSqlRelationalTableModel::setData( item, value, role );
		break;
	}
 }
}


/*!
    \fn MTProductosPresupuesto::buscarPrecioProducto( const int fila ) const
 */
QVariant MTProductosPresupuesto::buscarPrecioProducto( const int fila ) const
{
 // Busco el id del producto
 int id = data( index( fila, 2 ), Qt::UserRole ).toInt();
 if( id != -1 )
 {
 	QSqlQuery cola( QString("SELECT precio_venta FROM producto WHERE id = '%1'").arg( id ) );
	if( cola.next() )
	{
		return cola.record().value(0).toDouble();
	}
	else
	{
		qDebug( "Error al buscar el precio del producto" );
		qDebug( cola.lastError().text().toLocal8Bit() );
		return QVariant();
	}
 }
 else
 {
 	return QVariant();
 }
}


/*!
    \fn MTProductosPresupuesto::index ( int row, int column, const QModelIndex & parent ) const
 */
QModelIndex MTProductosPresupuesto::index ( int row, int column, const QModelIndex & parent ) const
{
 if( row >= QSqlRelationalTableModel::rowCount() )
 {
	return createIndex( row, column, 0 );
 }
 else
 {
  return QSqlRelationalTableModel::index( row, column, parent );
 }
}


/*!
    \fn MTProductosPresupuesto::removeRow ( int row, const QModelIndex & parent )
 */
bool MTProductosPresupuesto::removeRow ( int row, const QModelIndex & parent )
{
 if( row >= QSqlRelationalTableModel::rowCount() )
 {
  return true;
 }
 else
 {
  return QSqlRelationalTableModel::removeRow( row, parent );
 }
}


/*!
    \fn MTProductosPresupuesto::seteaPresupuesto( QSqlRecord &registro )
 */
void MTProductosPresupuesto::seteaPresupuesto( QSqlRecord &registro )
{
 registro.setValue( "id_presupuesto", -1 );
}


/*!
    \fn MTProductosPresupuesto::getTotal()
 */
double MTProductosPresupuesto::getTotal()
{
 double total = 0;
 for( int i = 0; i< QSqlRelationalTableModel::rowCount(); i++ )
 {
	double temp = data( index( i, 5 ), Qt::EditRole ).toDouble();
	if( temp > 0 )
 	{ total += temp; }
 }
 return total;
}
