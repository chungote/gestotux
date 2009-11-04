/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   				   *
 *   juiraze@yahoo.com.ar   						   *
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

#ifndef FORMRESUMENCTACTE_H
#define FORMRESUMENCTACTE_H

#include "eventana.h"
#include "ui_FormResumenCtaCteBase.h"
class MItemCuentaCorriente;

class FormResumenCtaCte : public EVentana, private Ui::FormResumenCtaCteBase
{
Q_OBJECT

public:
	FormResumenCtaCte ( QWidget* parent = 0, Qt::WFlags fl = 0 );
	~FormResumenCtaCte();
	void setNumeroCuenta( const int &numero_cuenta );

protected slots:
    void cambioCtaCte( int numero_cuenta );
    void imprimir();
    void pdf();
    void email();
    void menuContextual( const QModelIndex &indice );
    void pagarTodo();
    void verFactura();
    void verRecibo();
    void pagarFactura();

protected:
    MItemCuentaCorriente *modeloItem;

};

#endif

