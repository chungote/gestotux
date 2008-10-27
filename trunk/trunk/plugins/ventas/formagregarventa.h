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
#ifndef FORMAGREGARVENTA_H
#define FORMAGREGARVENTA_H

#include "eventana.h"
class QPushButton;
class QHBoxLayout;
class QVBoxLayout;
class QLCDNumber;
class QTableView;
class QComboBox;
class QGroupBox;
class QLabel;
class QGridLayout;
class QLineEdit;
class QSpacerItem;
class QFrame;
class MVenta;
class MVentaProducto;
class QSplitter;
class QModelIndex;

/**
Formulario para agregar venta

	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class FormAgregarVenta : public EVentana
{
Q_OBJECT
public:
    FormAgregarVenta( QWidget *parent = 0 );
    ~FormAgregarVenta();

protected:
	MVentaProducto *modeloVentaProducto;

private:
    QVBoxLayout *vboxLayout;
    QLabel *LTitulo;
    QHBoxLayout *hboxLayout;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout1;
    QGroupBox *GBProductos;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout1;
    QTableView *TVProductos;
    QVBoxLayout *vboxLayout2;
    QPushButton *PBAgregar;
    QPushButton *PBBorrar;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout2;
    QLabel *label_2;
    QLCDNumber *LcdNCantidad;
    QSpacerItem *spacerItem1;
    QLabel *label_3;
    QLineEdit *LETotal;
    QFrame *line;
    QHBoxLayout *hboxLayout3;
    QSpacerItem *spacerItem2;
    QPushButton *PBAceptar;
    QPushButton *PBCancelar;
    QSplitter *splitter;
    QWidget *widget;
    void closeEvent( QCloseEvent * event );

protected slots:
    void agregar();
    void borrar();
    void guardar();
    void buscarPrecio( const QModelIndex & topLeft, const QModelIndex & bottomRight );
    void cerrar();
};

#endif
