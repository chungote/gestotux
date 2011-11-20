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

#include "formprefventa.h"

#include "preferencias.h"
#include <QCheckBox>
#include <QDoubleSpinBox>

FormPrefVenta::FormPrefVenta( QWidget* parent, Qt::WFlags fl ) :
 FormPrefHijo(), Ui::FormPrefVentaBase()
{
    this->setParent( parent );
    setupUi(this);
    this->setWindowTitle( "Ventas" );
    this->setWindowIcon( QIcon( ":/imagenes/factura.png" ) );
}


/*!
    \fn FormPrefVenta::cargar()
 */
void FormPrefVenta::cargar()
{
 preferencias *p = preferencias::getInstancia();
 this->CkBBusquedaPrecio->setChecked( p->value( "Preferencias/Ventas/buscarPrecio", false ).toBool() );
 this->CkBLimitarAStock->setChecked( p->value( "Preferencias/Ventas/limitarastock", false ).toBool() );
}


/*!
    \fn FormPrefVenta::aplicar()
 */
void FormPrefVenta::aplicar()
{ return; }


/*!
    \fn FormPrefVenta::guardar()
 */
void FormPrefVenta::guardar()
{
 preferencias *p = preferencias::getInstancia();
 p->setValue( "Preferencias/Ventas/buscarPrecio", this->CkBBusquedaPrecio->isChecked() );
 p->setValue( "Preferencias/Ventas/limitarastock", this->CkBLimitarAStock->isChecked() );
}
