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

#ifndef FORMMOVIMIENTO_H
#define FORMMOVIMIENTO_H

#include <QWidget>
#include "ui_FormMovimientoBase.h"
class QAction;
class QStringListModel;

class FormMovimiento : public QWidget, public Ui::FormMovimientoBase
{
  Q_OBJECT

public:
  enum tipo
  {
    compra,
    venta,
    movimiento,
    indefinido
  };

  FormMovimiento(QWidget* parent = 0, Qt::WFlags fl = 0, tipo accion = indefinido );
  ~FormMovimiento();
    void setearNumeroTri();


protected:
	QAction *ActCerrar;
	QAction *ActGuardar;


protected slots:
    virtual void cerrar() = 0;
    void eliminarCaravana();
    void agregarCaravana();
    virtual void guardar() = 0;

private:
	QStringListModel *model;

public slots:
    void agregarCategoria();
    void agregarCliente();
    void agregarEstablecimientoOrigen();
    void agregarEstablecimientoDestino();
};

#endif

