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
#ifndef MTPRODUCTOSPRESUPUESTO_H
#define MTPRODUCTOSPRESUPUESTO_H

#include <QSqlRelationalTableModel>
class QVariant;

/**
	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class MTProductosPresupuesto : public QSqlRelationalTableModel
{
public:
    MTProductosPresupuesto( QObject * parent = 0 );
    ~MTProductosPresupuesto();

    QVariant data ( const QModelIndex & item, int role = Qt::DisplayRole ) const;
    Qt::ItemFlags flags( const QModelIndex & index ) const;
    int columnCount( const QModelIndex &parent = QModelIndex() ) const;
    int rowCount( const QModelIndex &parent = QModelIndex() ) const;
    bool guardar( const int id_presupuesto );
    bool setData( const QModelIndex &item, const QVariant &data, int role = Qt::EditRole );
    QVariant buscarPrecioProducto( const int fila ) const;
    QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const ;
    bool removeRow ( int row, const QModelIndex & parent = QModelIndex() );
};

#endif
