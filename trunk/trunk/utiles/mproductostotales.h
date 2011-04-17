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
#ifndef MPRODUCTOSTOTALES_H
#define MPRODUCTOSTOTALES_H


#include <QAbstractTableModel>

/**
Modelo que calcula totales segun modelo de venta, compra y presupuesto

        @author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class MProductosTotales : public QAbstractTableModel
{
Q_OBJECT
public:
    MProductosTotales( QObject *parent = 0 );
    ~MProductosTotales();

    bool insertRow(int row, const QModelIndex& parent = QModelIndex() );
    bool removeRow(int row, const QModelIndex& parent = QModelIndex() );
    bool setData(const QModelIndex& index, const QVariant& value, int role);
    int columnCount(const QModelIndex& parent = QModelIndex() ) const;
    int rowCount(const QModelIndex& parent = QModelIndex() ) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;
    QVariant data(const QModelIndex& idx, int role) const;
    void recalcularTotal();
    double total();
    QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    void calcularTotales( bool sino = true );
    bool buscaPrecios();
    void buscarPrecios( bool activado = true );
    QMap<int, QString> *listaProductos() { return this->prods; }
    QMap<int, QString> *prods;
    void agregarNuevoProducto( const QString nombre );

signals:
    void cambioListaProductos( MProductosTotales * );

private:
        QHash<int, double> *subtotales;
        QHash<int, double> *cantidades;
        QHash<int, double> *precio_unitario;
        QHash<int, int> *productos;
        double Total;
        bool _calcularTotal;
        bool _buscarPrecio;
        int _min;
        double buscarPrecioVenta( int id_producto );
};

#endif
