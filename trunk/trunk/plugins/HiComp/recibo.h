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
#ifndef RECIBO_H
#define RECIBO_H

#include <QObject>
#include <QDomDocument>
#include <QDate>
#include <QPainter>

/**
	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class Recibo : public QObject
{
Q_OBJECT
public:
    Recibo(QObject *parent = 0);
    ~Recibo();
    QByteArray obtenerByteArray();
    QString titulo();
    bool cargarRegistro( int idDB );
    void imprimir( QPainter *impresora );

private:
    QString nombre_cliente;
    QString descripcion;
    QString direccion;
    int num_recibo;
    bool contado;
    bool cuenta_corriente;
    double total;
    QDate fecha_pagado;
    int num_mes;
    QDomDocument domdoc;
    void reajusteXML();
    QString generarNumeroRecibo();

private:
    void hacerText( QDomNode padre,const double ancho, double x, double y );
    double anchoCaracter( QString car );
};

#endif
