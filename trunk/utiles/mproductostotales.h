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
    MProductosTotales( QObject *parent = 0, QMap<int, QString> *mapa = 0 );
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
    /*!
     * Contiene el listado de ids relacionados con los nombres de los productos
     */
    QMap<int, QString> *prods;
    void agregarNuevoProducto( const int cantidad, const QString nombre );

signals:
    void cambioListaProductos( MProductosTotales * );

private:
        /*!
         * Contiene el listado de subtotales por definicion de fila
         */
        QHash<int, double> *subtotales;
        /*!
         * Contiene el listado de cantidades por definicion de fila
         */
        QHash<int, double> *cantidades;
        /*!
         * Contiene el listado de precios unitarios por definicion de fila
         */
        QHash<int, double> *precio_unitario;
        /*!
         * Contiene el mapeo de posicion de fila a id de productos
         */
        QHash<int, int> *productos;
        /*!
         * Contiene el total de la factura calculado
         */
        double Total;
        /*!
         * Define si se calculará el total
         */
        bool _calcularTotal;
        /*!
         * Define si se hará la busqueda de precio del producto
         */
        bool _buscarPrecio;
        /*!
         * Indice para indicar el nuevo ingreso
         */
        int _min;
        double buscarPrecioVenta( int id_producto );
};

#endif
