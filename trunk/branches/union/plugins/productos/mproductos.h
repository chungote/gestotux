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
#ifndef MPRODUCTOS_H
#define MPRODUCTOS_H

#include <QSqlRelationalTableModel>

/**
	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class MProductos : public QSqlRelationalTableModel
{
Q_OBJECT
public:
    MProductos(QObject *parent = 0);
    QVariant data(const QModelIndex& item, int role) const;
    static double stock( const int id_producto );
    static bool modificarStock( const int id_producto, const double cantidad );
    static bool agregarProducto( const QString codigo, const QString nombre, const double costo, const double venta, int stock = 0, int categoria = -1, QString descripcion = QString(), QString marca = QString(), QString modelo = QString() );
};

#endif