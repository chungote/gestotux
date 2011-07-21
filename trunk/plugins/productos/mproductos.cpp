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
#include "mproductos.h"
#include "preferencias.h"
#include <QColor>
#include <QBrush>

MProductos::MProductos(QObject *parent)
 : QSqlRelationalTableModel(parent)
{
 setTable( "producto" );
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "Categoria" );
 if( preferencias::getInstancia()->value( "Preferencias/Productos/categorias" ).toBool() )
 {
  setRelation( 1, QSqlRelation( "categoria_producto", "id", "nombre" ) );
 }
 setHeaderData( 2, Qt::Horizontal, "Nombre" );
 setHeaderData( 3, Qt::Horizontal, "Precio de Costo" );
 setHeaderData( 4, Qt::Horizontal, "Precio de venta" );
 setHeaderData( 5, Qt::Horizontal, "Descripcion" );
 setHeaderData( 6, Qt::Horizontal, "Marca" );
 setHeaderData( 7, Qt::Horizontal, "Stock" );
 setHeaderData( 8, Qt::Horizontal, "Habilitado" );
 setHeaderData( 9, Qt::Horizontal, QString::fromUtf8( "#Código" ) );
 setSort( 0, Qt::AscendingOrder );
}


QVariant MProductos::data(const QModelIndex& item, int role) const
{
 if( !item.isValid() )
 {
   qDebug( QString( "Indice invalido Productos: col=%1, row=%2, role=%3").arg( item.column() ).arg( item.row() ).arg( role ).toLocal8Bit() );
   return( QVariant() );
 }
 switch( role )
 {
        case Qt::DisplayRole:
        {
                switch( item.column() )
                {
                        case 3:
                        case 4:
                        {
                                return QString( "$ %1" ).arg( QString::number( QSqlRelationalTableModel::data(item, role).toDouble(), 'f', 3 ) );
                                break;
                        }
                        case 8:
                        {
                                if( QSqlRelationalTableModel::data( item, role ).toBool() )
                                { return "Si"; }
                                else
                                { return "No"; }
                                break;
                        }
                        case 7:
                        {
                            return QString::number( QSqlRelationalTableModel::data( item, role ).toDouble(), 'f', 2 );
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
        case Qt::TextColorRole:
        {
                switch ( item.column() )
                {
                        case 3:
                        case 4:
                        {
                                return QColor(Qt::blue);
                                break;
                        }
                        default:
                        {
                                return QColor(Qt::black);
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
                        case 4:
                        {
                                return QSqlRelationalTableModel::data( item, role ).toDouble();
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
        case Qt::TextAlignmentRole:
        {
                switch( item.column() )
                {
                        case 3:
                        case 4:
                        case 6:
                        case 7:
                        {
                                return int( Qt::AlignHCenter | Qt::AlignVCenter );
                                break;
                        }
                        default:
                        {
                                return int( Qt::AlignLeft | Qt::AlignVCenter );
                                break;
                        }
                }
                break;
        }
        case Qt::ToolTipRole:
        case Qt::StatusTipRole:
        {
                return QVariant( "Haga doble click o seleccione y F2 para editar" );
                break;
        }
        default:
        {
                return QSqlRelationalTableModel::data( item, role );
                break;
        }
 }
}


#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
/*!
    \fn MProductos::stock( const int id_producto )
        Devuelve la cantidad de stock que existe de un producto si el control de stock esta habilitado
 */
double MProductos::stock( const int id_producto )
{
 if( !preferencias::getInstancia()->value( "Preferencias/Productos/stock" ).toBool() )
 { return 10000000; }
 QSqlQuery cola( QString( "SELECT stock FROM producto WHERE id = %1" ).arg( id_producto ) );
 if( !cola.next() )
 {
  return cola.record().value(0).toDouble();
 }
 else
 {
  qWarning( "Error al intentar obtener el stock del producto" );
  qDebug( qPrintable( cola.lastError().text() ) );
  qDebug( qPrintable( cola.executedQuery() ) );
  return 0;
 }
}


/*!
    \fn MProductos::modificarStock( const int id_producto, const double cantidad )
 */
bool MProductos::modificarStock( const int id_producto, const double cantidad )
{
 QSqlQuery cola( QString( "SELECT stock FROM producto WHERE id = %2" ).arg( id_producto ) );
 if( cola.next() )
 {
        double anterior = cola.record().value(0).toDouble();
        anterior += cantidad;
        if(  cola.exec( QString( "UPDATE producto SET stock = %1 WHERE id = %2" ).arg( anterior ).arg( id_producto ) ) )
        {
                qDebug( "Stock actualizado correctamente" );
                return true;
        }
        else
        {
                qWarning( "Error al actualizar el stock del producto" );
                qDebug( qPrintable( cola.lastError().text() ) );
                qDebug( qPrintable( cola.executedQuery() ) );
                return false;
        }
 }
 else
 {
  qWarning( "Error al intentar actualizar el stock del producto solicitado" );
  qDebug( qPrintable( cola.lastError().text() ) );
  qDebug( qPrintable( cola.executedQuery() ) );
  return false;
 }
}

bool MProductos::agregarProducto(const QString codigo, const QString nombre, const double costo, const double venta, int stock, int categoria, QString descripcion, QString marca, QString modelo) {
    QSqlQuery cola;
    if( !cola.prepare( "INSERT INTO producto ( codigo, nombre, precio_costo, precio_venta, stock, id_categoria, descripcion, marca, modelo, habilitado ) VALUES( :codigo, :nombre, :precio_costo, :precio_venta, :stock, :categoria, :descripcion, :marca, :modelo, :habilitado )" ) ) {
        qDebug( cola.lastError().text().toLocal8Bit() );
        return false;
    }
    cola.bindValue( ":codigo", codigo );
    cola.bindValue( ":nombre", nombre );
    if( descripcion == "" )
    { cola.bindValue( ":descripcion", QVariant() ); }
    else
    { cola.bindValue( ":descripcion", descripcion ); }
    if( marca == "" )
    { cola.bindValue( ":marca", QVariant() ); }
    else
    { cola.bindValue( ":marca", marca ); }
    if( modelo == "" )
    { cola.bindValue( ":modelo", QVariant() ); }
    else
    { cola.bindValue( ":modelo", modelo); }
    if( categoria == -1 )
    { cola.bindValue( ":categoria", QVariant() ); }
    else
    { cola.bindValue( ":categoria", categoria ); }
    if( stock ==  0 ) {
        cola.bindValue( ":stock", QVariant() );
    } else {
        cola.bindValue( ":stock", stock );
    }
    cola.bindValue( ":precio_costo", costo );
    cola.bindValue( ":precio_venta", venta );
    cola.bindValue( ":habilitado", true );
    if( cola.exec() ) {
        qDebug( "Producto agregado correctamente" );
     return true;
    } else {
      qWarning( "Error al intentar insertar el producto." );
      qDebug( cola.lastError().text().toLocal8Bit() );
      qDebug( cola.lastQuery().toLocal8Bit() );
      return false;
    }
}
