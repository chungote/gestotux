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
#include "mcompraproducto.h"
#include <QSqlRecord>

MCompraProducto::MCompraProducto(QObject *parent)
 : QSqlRelationalTableModel(parent)
{
 setTable( "compras_productos" );
}

#include <QSqlError>
#include <QSqlQuery>
/*!
 * \fn MCompraProducto::agregarCompraProducto( const int id_compra, const int id_producto, const double precio_compra, const int cantidad )
 * Agrega la compra de un producto para una ceirta compra.
 * \param id_compra Identificador de compra
 * \param id_producto Identificador del producto
 * \param precio_compra Precio al cual se lo compro
 * \param cantidad Cantidad comprada
 * \return Verdader si se pudo registrar
 */
bool MCompraProducto::agregarCompraProducto( const int id_compra, const int id_producto, const double precio_compra, const int cantidad )
{
    if( id_compra <= 0 )
        return false;
    if( id_producto <= 0 )
        return false;
    if( cantidad <= 0 )
        return false;
    if( precio_compra <= 0 )
        return false;

    return false;
}
