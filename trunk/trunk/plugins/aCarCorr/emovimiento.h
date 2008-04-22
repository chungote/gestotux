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
class QProgressDialog;
#include "TipoMovs.h"

/**
	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class EMovimiento : public QObject
{
Q_OBJECT
public:
    EMovimiento( QObject *parent = 0 );
    ~EMovimiento();

    bool cargarMovimiento( int idDb );
    int guardar( QProgressDialog *dialogo );

    QStringList caravanas();
    QString getDTA() const;
    QDate getFecha() const;
    int tipoMov() const;

    void setTipoMov( const int& theValue );
    bool setDTA( const QString& theValue );
    void setComprador( int id );
    void setVendedor( int idDB );
    void setEstablecimientoDestino( int idDB );
    void setEstablecimientoOrigen( int idDB );
    void setCategoria( int id );
    void setFecha( const QDate& theValue );
    void eliminarCaravana( QString codigo );
    bool agregarCaravana( QString codigo, bool verificar = true );

private:
	QPair<int,QString> destino;
	QPair<int,QString> origen;
	QPair<int,QString> vendedor;
	QPair<int,QString> comprador;
	QPair<int,QString> categoria;
	QDate fecha;
	QString DTA;
	int id_db;
	QStringList _caravanas;

private:
    void cargarNombreCategoria( const int idDB );
    void cargarNombreComprador( const int idDB );
    void cargarNombreVendedor( const int idDB );
    void cargarNombreEstablecimientoDestino( const int idDB );
    void cargarNombreEstablecimientoOrigen( const int idDB );
    void setCaravanas( QStringList caravanas );
    bool guardarCaravana( QString codigo );
    bool cargarCaravanas();
    bool asociarCaravana( int id_caravana );
    bool aduenarCaravana( int id_caravana, int id_cliente, QDate fecha, bool cambiar_dueno = true );
    int getIDCaravana( QString codigo );

    int tipo_mov;
    
};

#endif
