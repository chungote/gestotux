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
#ifndef FORMAGREGARRECIBO_H
#define FORMAGREGARRECIBO_H

#include "eventana.h"
#include "ui_FormAgregarReciboBase.h"
class EEditor;

/**
	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class FormAgregarRecibo : public EVentana, public Ui_FormAgregarReciboBase
{
Q_OBJECT
public:
    FormAgregarRecibo(QWidget *parent = 0);
    ~FormAgregarRecibo();
    QString nombre();

private:
    double recargo;
    void recalcular();

    QAction* ActCancelar;
    QAction* ActGuardar;
    QAction* ActGuardarImprimir;

    EEditor *TETexto;

protected slots:
    void cambioImporte( double );
    void cambioEstadoPagoMes( int estado );
    void cambioEstadoRecargos( int estado );
    void guardar( bool imprimir = false );
    void guardarImprimir();
};

#endif
