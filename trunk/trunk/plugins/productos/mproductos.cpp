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
 preferencias *p = preferencias::getInstancia();
 p->beginGroup( "Preferencias" );
 p->beginGroup( "Productos" );
 if( p->value( "categorias" ).toBool() )
 {
  setRelation( 1, QSqlRelation( "categoria_producto", "id", "nombre" ) );
 }
 p->endGroup();
 p->endGroup();
 p=0;
 setHeaderData( 2, Qt::Horizontal, QString::fromUtf8( "#Código" ) );
 setHeaderData( 3, Qt::Horizontal, "Nombre" );
 setHeaderData( 4, Qt::Horizontal, "Precio de Costo" );
 setHeaderData( 5, Qt::Horizontal, "Precio de venta" );
 setHeaderData( 6, Qt::Horizontal, "Descripcion" );
 setHeaderData( 7, Qt::Horizontal, "Marca" );
 setHeaderData( 8, Qt::Horizontal, "Stock" );
 setHeaderData( 9, Qt::Horizontal, "Habilitado" );
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
                        case 4:
                        case 5:
                        {
                                return QString( "$ %1" ).arg( QString::number( QSqlRelationalTableModel::data(item, role).toDouble(), 'f', 2 ) );
                                break;
                        }
                        case 9:
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
                        case 5:
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
                        case 5:
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
                        case 5:
                        case 4:
                        case 6:
                        case 7:
                        case 8:
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

Qt::ItemFlags MProductos::flags(const QModelIndex &/*index*/) const
{
    return QFlags<Qt::ItemFlag>( !Qt::ItemIsEditable |  Qt::ItemIsSelectable | Qt::ItemIsEnabled );
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
 preferencias *p = preferencias::getInstancia();
 p->beginGroup( "Preferencias" );
 p->beginGroup( "Productos" );
 bool stock = p->value( "stock" ).toBool();
 p->endGroup();p->endGroup();p=0;
 if( !stock )
 { return 10000000; }
 if( id_producto <= 0 ) {
     qDebug( "Id de producto erroneo" );
     return -1.0;
 }
 QSqlQuery cola( QString( "SELECT stock FROM producto WHERE id = %1 LIMIT 1" ).arg( id_producto ) );
 if( cola.next() )
 {
  return cola.record().value(0).toDouble();
 }
 else
 {
  qWarning( "Error al intentar obtener el stock del producto" );
  qDebug( qPrintable( cola.lastError().text() ) );
  qDebug( qPrintable( cola.executedQuery() ) );
  return -1.0;
 }
}


/*!
    \fn MProductos::modificarStock( const int id_producto, const double cantidad )
    Ajusta el stock del producto segun la cantidad aplicada como parametro.
    Si la cantidad es negativa se disminuye el stock del producto.
    Si la cantidad es positiva se aumenta el stock del producto.
    \param id_producto Identificador del producto
    \param cantidad Cantidad a aplicar
    \return Verdadero si se pudo actualizar el stock
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

/*!
 * \fn MProductos::agregarProducto( const QString codigo, const QString nombre, const double costo, const double venta, int stock, int categoria, QString descripcion, QString marca, QString modelo )
 * Agrega un nuevo producto a la base de datos con los parametros pasados.
 * \param codigo Codigo del producto a agregar
 * \param nombre Nombre del producto a agregar
 * \param costo Costo del producto a agregar
 * \param venta Precio de venta del producto
 * \param stock Stock inicial del producto
 * \param categoria Categoría a la que pertenece el producto
 * \param descripcion Descripción del producto
 * \param marca Marca del producto
 * \param modelo Modelo del producto
 * \returns Verdadero si se pudo ingresar correctamente el producto a la base de datos, falso en caso contrario.
 */
bool MProductos::agregarProducto(const QString codigo, const QString nombre, const double costo, const double venta, int stock, int categoria, QString descripcion, QString marca, QString modelo) {
    QSqlQuery cola;
    if( !cola.prepare( "INSERT INTO producto ( codigo, nombre, precio_costo, precio_venta, stock, id_categoria, descripcion, marca, modelo, habilitado ) VALUES( :codigo, :nombre, :precio_costo, :precio_venta, :stock, :categoria, :descripcion, :marca, :modelo, :habilitado )" ) ) {
        qDebug( cola.lastError().text().toLocal8Bit() );
        return false;
    }
    preferencias *p = preferencias::getInstancia();
    p->beginGroup( "Preferencias" );
    p->beginGroup( "Productos" );
    bool pdescripcion = p->value( "descripcion", false ).toBool();
    bool pmarcas = p->value( "marcas", false ).toBool();
    bool pmodelo = p->value( "modelo", false ).toBool();
    bool pcategorias = p->value( "categorias", false ).toBool();
    bool pstock = p->value( "stock", false ).toBool();
    p->endGroup(); p->endGroup(); p=0;
    cola.bindValue( ":codigo", codigo );
    cola.bindValue( ":nombre", nombre );
    if( descripcion == "" || pdescripcion  )
    { cola.bindValue( ":descripcion", QVariant() ); }
    else
    { cola.bindValue( ":descripcion", descripcion ); }
    if( marca == "" || pmarcas  )
    { cola.bindValue( ":marca", QVariant() ); }
    else
    { cola.bindValue( ":marca", marca ); }
    if( modelo == "" || pmodelo )
    { cola.bindValue( ":modelo", QVariant() ); }
    else
    { cola.bindValue( ":modelo", modelo); }
    if( categoria == -1 || pcategorias )
    { cola.bindValue( ":categoria", QVariant() ); }
    else
    { cola.bindValue( ":categoria", categoria ); }
    if( stock ==  0 || pstock ) {
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

/*!
    \fn MProductos::actualizarPrecioCompra( const int id_producto, const double precio )
    Actualiza el precio de costo del producto indicado.
    ATENCION: ¡ No actualiza el precio de venta !
    \param id_producto identificador del producto.
    \param precio Precio de costo a aplicar.
    \return Verdadero si se pudo actualizar, falso en caso contrario.
 */
bool MProductos::actualizarPrecioCompra( const int id_producto, const double precio )
{
 QSqlQuery cola;
 if( cola.exec( QString( "UPDATE producto SET precio_costo = %1 WHERE id = %2" ).arg( precio ).arg( id_producto ) ) )
 {
        qDebug( "Precio de compra actualizado correctamente" );
        return true;
 }
 else
 {
  qWarning( "Error al intentar actualizar el precio de compra del producto solicitado" );
  qDebug( qPrintable( cola.lastError().text() ) );
  qDebug( qPrintable( cola.lastQuery() ) );
  return false;
 }
}

/*!
    \fn MProductos::actualizarPrecioVenta( const int id_producto, const double precio )
    Actualiza el precio de venta del producto indicado.
    \param id_producto identificador del producto.
    \param precio Precio de venta a aplicar.
    \return Verdadero si se pudo actualizar, falso en caso contrario.
 */
bool MProductos::actualizarPrecioVenta( const int id_producto, const double precio )
{
 QSqlQuery cola;
 if( cola.exec( QString( "UPDATE producto SET precio_venta = %1 WHERE id = %2" ).arg( precio ).arg( id_producto ) ) )
 {
        qDebug( "Precio de venta actualizado correctamente" );
        return true;
 }
 else
 {
  qWarning( "Error al intentar actualizar el precio de venta del producto solicitado" );
  qDebug( qPrintable( cola.lastError().text() ) );
  qDebug( qPrintable( cola.lastQuery() ) );
  return false;
 }
}

/*!
    \fn MProductos::buscarPrecioCompra( const int id_producto )
    Busca el precio de compra del producto dado por id.
    \param id_producto Identificador del producto.
    \returns Precio de venta del producto o -1 si hubo error.
 */
double MProductos::buscarPrecioCompra( const int id_producto )
{
 QSqlQuery cola;
 if( cola.exec( QString( "SELECT precio_costo FROM producto WHERE id = %1" ).arg( id_producto ) ) )
 {
     if( cola.next() ) {
         return cola.record().value(0).toDouble();
     } else {
         qWarning( "Error al hacer next la cola de busqueda del precio de compra del producto solicitado" );
     }
 }
 else
 {
  qWarning( "Error al ejecutar la cola de busqueda del precio de compra del producto solicitado" );
 }
 qDebug( qPrintable( cola.lastError().text() ) );
 qDebug( qPrintable( cola.lastQuery() ) );
 return -1.0;
}

/*!
    \fn MProductos::buscarPrecioCompra( const QString codigo )
    Busca el precio de compra del producto dado por codigo del producto.
    \param codigo Codigo del producto.
    \returns Precio de venta del producto o -1 si hubo error o el codigo no existe.
 */
double MProductos::buscarPrecioCompra( const QString codigo )
{
    if( !MProductos::existeCodigo( codigo ) ) {
        return -1.0;
    }
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT precio_costo FROM producto WHERE codigo = %1" ).arg( codigo ) ) )
    {
        if( cola.next() ) {
            return cola.record().value(0).toDouble();
        } else {
            qWarning( "Error al hacer next la cola de busqueda del precio de compra del producto solicitado - codigo" );
        }
    }
    else
    {
     qWarning( "Error al ejecutar la cola de busqueda del precio de compra del producto solicitado - codigo" );
    }
    qDebug( qPrintable( cola.lastError().text() ) );
    qDebug( qPrintable( cola.lastQuery() ) );
    return -1.0;

}

/*!
 * \fn MProductos::existeCodigo( const QString codigo )
 * Deuelve verdadero si existe un producto con el codigo pasado como parametro.
 * \param codigo Codigo a buscar
 */
bool MProductos::existeCodigo( const QString codigo )
{
    if( codigo.isNull() || codigo.isEmpty() ) {  return false;  }
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT COUNT(id) FROM producto WHERE codigo = %1" ).arg( codigo ) ) ) {
        cola.next();
        if( cola.record().value(0).toInt() > 0 ) {
            return true;
        }
    } else {
        qDebug( "Error de ejecucion de la cola de averiguacion de codigo de producto" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit()  );
    }
    return false;
}

/*!
 * \fn MProductos::existeNombre( const QString nombre )
 * Devuelve verdadero si existe un producto con el nombre pasado como parametro
 * \param nombre Nombre del producto a buscar
 */
bool MProductos::existeNombre( const QString nombre )
{
    if( nombre.isNull() || nombre.isEmpty() ) {  return false;  }
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT COUNT(id) FROM producto WHERE nombre = '%1'" ).arg( nombre ) ) ) {
        cola.next();
        if( cola.record().value(0).toInt() > 0 ) {
            return true;
        }
    } else {
        qDebug( "Error de ejecucion de la cola de averiguacion de codigo de producto" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit()  );
    }
    return false;
}

/*!
 * \fn MProductos::cambiarHabilitado( const int id_producto, bool estado )
 *
 */
bool MProductos::cambiarHabilitado( int id_producto, bool estado )
{
    QSqlQuery cola;
    if( cola.exec( QString( "UPDATE producto SET habilitado = %2 WHERE id = %1" ).arg( id_producto ).arg( estado ) ) ) {
        return true;
    } else {
        qDebug( "Error de ejecucion de la cola de cambio de estado de habilitacion del producto" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit()  );
    }
    return false;
}

/*!
 * \fn MProductos::habilitar( int id_producto )
 * Habilita el producto pasado como parametro
 * \param id_producto Identificador del producto
 * \returns Verdaderos si se pudo habilitar
 */
bool MProductos::habilitar( int id_producto )
{  return cambiarHabilitado( id_producto, true ); }

/*!
 * \fn MProductos::deshabilitar( int id_producto )
 * Deshabilita el producto pasado como parametro
 * \param id_producto Identificador del producto
 * \returns Verdaderos si se pudo deshabilitar
 */
bool MProductos::deshabilitar( int id_producto )
{  return cambiarHabilitado( id_producto, false ); }

/*!
 * \fn MProductos::habilitado( int id_producto )
 * Devuelve el estado de habilitacion del producto pasado como parametro
 * \param id_producto Identificador del producto
 * \returns Verdaderos si se encuentra habilitado
 */
bool MProductos::habilitado( int id_producto )
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT habilitado FROM producto WHERE id = %1" ).arg( id_producto ) ) ) {
        if( cola.next() ) {
            return cola.record().value(0).toBool();
        } else {
            qDebug( "Error de next de la cola de averiguacion de habilitacion de producto" );
            qDebug( cola.lastError().text().toLocal8Bit() );
            qDebug( cola.lastQuery().toLocal8Bit()  );
        }
    } else {
        qDebug( "Error de ejecucion de la cola de averiguacion de habilitacion de producto" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit()  );
    }
    return false;
}

/*!
 * \fn MProductos::cambiarHabilitado( const QModelIndex idx, bool estado )
 *
 */
bool MProductos::cambiarHabilitado( QModelIndex idx, bool estado )
{
    setData( index( idx.row(), fieldIndex( "habilitado" ) ), estado );
    return submit();
}

/*!
 * \fn MProductos::habilitar( QModelIndex idx )
 * Habilita el producto pasado como parametro
 * \param idx Identificador del producto
 * \returns Verdaderos si se pudo habilitar
 */
bool MProductos::habilitar( QModelIndex idx )
{  return cambiarHabilitado( idx, true ); }

/*!
 * \fn MProductos::deshabilitar( QModelIndex idx )
 * Deshabilita el producto pasado como parametro
 * \param idx Identificador del producto
 * \returns Verdaderos si se pudo deshabilitar
 */
bool MProductos::deshabilitar( QModelIndex idx )
{  return cambiarHabilitado( idx, false ); }

/*!
 * \fn MProductos::idProductoPorCodigo( const QString codigo )
 * Obtiene el ID de producto del codigo pasado como parametro
 * \param codigo Codigo del producto a buscar
 * \return ID del codigo o 0 si no existe
 */
int MProductos::idProductoPorCodigo( const QString codigo )
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT id FROM producto WHERE codigo = '%1'" ).arg( codigo ) ) ) {
        if( cola.next() ) {
            return cola.record().value(0).toInt();
        } else {
            qDebug( "Error de next de la cola de averiguacion de id de producto x codigo" );
            qDebug( cola.lastError().text().toLocal8Bit() );
            qDebug( cola.lastQuery().toLocal8Bit()  );
        }
    } else {
        qDebug( "Error de ejecucion de la cola de averiguacion de id de producto x codigo" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit()  );
    }
    return 0;
}
