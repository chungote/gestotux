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

#ifndef FILTROCLIENTES_H
#define FILTROCLIENTES_H

#include <QWidget>
#include "ui_FiltroClientesBase.h"

class FiltroClientes : public QWidget, private Ui::FiltroClientesBase
{
  Q_OBJECT

public:
  FiltroClientes(QWidget* parent = 0, Qt::WFlags fl = 0 );
  ~FiltroClientes();

signals:
	void cambioCliente( int );
	void seteaFiltrado( bool, int );

protected slots:
    void seteaFiltradoSlot( bool activo );
    void cambioClienteSlot( int idcombo );
};

#endif

