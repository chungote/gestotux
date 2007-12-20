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
#ifndef EVLISTA_H
#define EVLISTA_H

#include <eventana.h>
class QBoxLayout;
class QSplitter;
class QFrame;
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;
class QCheckBox;
class QFrame;
class QSqlTableModel;
class QSpacerItem;
class QTableView;
class QSqlRecord;

/**
 * 	\brief Clase base para todas las ventanas de tipo lista
 *
 *	Clase generica para mostrar un listado simple de datos del programa
 *
 * 	@author Esteban Zeller <juiraze@yahoo.com.ar>
 */
class EVLista : public EVentana
{
	Q_OBJECT
public:
    EVLista(QWidget *parent = 0,  bool vertical = true );
    ~EVLista();
    void closeEvent( QCloseEvent * c);

    // Especifico del formulario
    QBoxLayout *boxLayout;
    QBoxLayout *boxLayoutgeneral;
    QSplitter *splitter;
    QFrame *frame;
    QVBoxLayout *vboxLayout;
    QPushButton *PBAgregar;
    QPushButton *PBEliminar;
    QFrame *linea;
    QPushButton *PBImprimir;
    QCheckBox *CBprevisualizar;
    QSpacerItem *spacerItem;
    QPushButton *PBCerrar;
    QTableView *vista;

protected:
  /**
   * Puntero a modelo generico para la vista
   */
   QSqlTableModel *modelo;

protected slots:
    void cerrar();
    void agregar();
    void eliminar();
    void imprimir();
    virtual void antes_de_insertar( int row, QSqlRecord & record ) = 0;
};

#endif
