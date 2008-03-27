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
#ifndef EMOVIMIENTO_H
#define EMOVIMIENTO_H

#include <QObject>
#include <QPair>
#include <QString>
#include <QStringList>
#include <QDate>

/**
	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class EMovimiento : public QObject
{
Q_OBJECT
public:
    enum tipo
    {
     invalido = 0,
     stock = 1,
     compra = 2,
     venta = 3,
     mudanza = 4
    } tipo_mov;
    EMovimiento( QObject *parent = 0 );
    ~EMovimiento();

    bool cargarMovimiento( int idDb );
    int guardar();

    QStringList caravanas();
    QString getDTA() const;
    QDate getFecha() const;
    int tipoMov() const;

    void setTipoMov( const tipo& theValue );
    void setDTA ( const QString& theValue );
    void setComprador( int id );
    void setVendedor( int idDB );
    void setEstablecimientoDestino( int idDB );
    void setEstablecimientoOrigen( int idDB );
    void setCategoria( int id );
    void setFecha ( const QDate& theValue );

private:
	QPair<int,QString> destino;
	QPair<int,QString> origen;
	QPair<int,QString> vendedor;
	QPair<int,QString> comprador;
	QPair<int,QString> categoria;
	QDate fecha;
	QString DTA;
	int id_db;

private:
    void cargarNombreCategoria( int idDB );
    void cargarNombreComprador( int idDB );
    void cargarNombreVendedor( int idDB );
    void cargarNombreEstablecimientoDestino( int idDB );
    void cargarNombreEstablecimientoOrigen( int idDB );
};

#endif
