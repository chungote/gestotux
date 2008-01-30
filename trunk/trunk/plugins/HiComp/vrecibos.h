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
#ifndef VRECIBOS_H
#define VRECIBOS_H

#include <QWidget>

class QAction;
class QSqlTableModel;
class QTableView;
/**
	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class VRecibos : public QWidget
{
Q_OBJECT
public:
    VRecibos(QWidget *parent = 0);
    ~VRecibos();

private:
    QAction *ActAgregar;
    QAction *ActEliminar;
    QAction *ActImprimir;
    QAction *ActVer;
    QAction *ActCerrar;
    QAction *ActModificar;
    QSqlTableModel *modelo;
    QTableView *vista;

protected slots:
    void ver();
    void eliminar();
    void modificar();
    void agregar();
};

#endif
