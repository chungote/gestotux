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
#ifndef FORMMODIFICARRECIBO_H
#define FORMMODIFICARRECIBO_H

#include <ui_FormAgregarReciboBase.h>
#include <QWidget>

class EEditor;
class QSqlTableModel;
/**
	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class FormModificarRecibo : public QWidget, Ui_FormAgregarReciboBase
{
Q_OBJECT
public:
    FormModificarRecibo( QWidget *parent = 0 );
    ~FormModificarRecibo();
    void cargarDatos( QModelIndex idDB, QSqlTableModel *modelo );
    QString nombre();

private:
    double recargo;
    void recalcular();

protected slots:
    void cambioImporte( double );
    void cambioEstadoPagoMes( int estado );
    void cambioEstadoRecargos( int estado );
    void guardar();
    void guardarImprimir();
private:
    QAction *ActGuardar;
    QAction *ActGuardarImprimir;
    QAction *ActCerrar;
    QModelIndex indice;
    QSqlTableModel *modelo;
    EEditor *TETexto;

signals:
    void agregarVentana( QWidget *w );
};

#endif
