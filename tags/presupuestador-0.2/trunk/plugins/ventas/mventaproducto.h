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
#ifndef MVENTAPRODUCTO_H
#define MVENTAPRODUCTO_H

#include <QSqlRelationalTableModel>
#include <QHash>

/**
Modelo para los productos vendidos

	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class MVentaProducto : public QSqlRelationalTableModel
{
Q_OBJECT
public:
    MVentaProducto(QObject *parent = 0 , bool calcula = false );
    ~MVentaProducto();
    QVariant data(const QModelIndex& idx, int role) const;
    void calcularTotales();
    double total();
    QModelIndex index( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
    int columnCount( const QModelIndex & parent = QModelIndex() ) const;
    bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );

    /*!
        \fn MVentaProducto::rowCount ( const QModelIndex & parent = QModelIndex() ) const
     */
    int rowCount ( const QModelIndex & parent = QModelIndex() ) const  { return QSqlRelationalTableModel::rowCount( parent); }
    Qt::ItemFlags flags ( const QModelIndex & index ) const;
    bool isDirty( const QModelIndex & index ) const;

	int get_ultima_row() const;

private:
	bool calculaTotales;
	QHash<int, double> *subtotales;
	double Total;
private:
    void recalcularTotal();
    void primeInsert ( int row, QSqlRecord & record )  ;
protected:
    int ultima_row;
};

#endif
