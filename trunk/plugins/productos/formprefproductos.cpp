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
#include "formprefproductos.h"

#include "preferencias.h"

FormPrefProductos::FormPrefProductos ( QWidget* parent, Qt::WFlags fl )
: FormPrefHijo(), Ui::FormPrefProductosBase()
{
 setupUi ( this );
 this->setWindowTitle( "Productos" );
 this->setWindowIcon( QIcon( ":/imagenes/productos.png" ) );
}

FormPrefProductos::~FormPrefProductos()
{
}




/*!
    \fn FormPrefProductos::cargar()
 */
void FormPrefProductos::cargar()
{
 preferencias *p = preferencias::getInstancia();
 CkBCategorias->setChecked( p->value( "Preferencias/Productos/categorias", false ).toBool() );
 CkBMarcas->setChecked( p->value( "Preferencias/Productos/marcas", false ).toBool() );
 CkBDescripcion->setChecked( p->value( "Preferencias/Productos/descripcion", false ).toBool() );
 GBStock->setChecked( p->value( "Preferencias/Productos/stock", false ).toBool() );
 CkBPermitir->setChecked( p->value( "Preferencias/Productos/Stock/permitir", false ).toBool() );
 CkBLimitarVenta->setChecked( p->value( "Preferencias/Productos/Stock/limitar", false ).toBool() );
 CkBAvisosStock->setChecked( p->value( "Preferencias/Productos/Stock/avisos", false ).toBool() );
 DSBLimiteMinimo->setValue( p->value( "Preferencias/Productos/Stock/limiteMinimo", 0.0 ).toDouble() );
}


/*!
    \fn FormPrefProductos::aplicar()
 */
void FormPrefProductos::aplicar()
{ return; }


/*!
    \fn FormPrefProductos::guardar()
 */
void FormPrefProductos::guardar()
{

 preferencias *p = preferencias::getInstancia();
 p->setValue( "Preferencias/Productos/categorias",CkBCategorias->isChecked() );
 p->setValue( "Preferencias/Productos/marcas", CkBMarcas->isChecked() );
 p->setValue( "Preferencias/Productos/descripcion",CkBDescripcion->isChecked() );
 p->setValue( "Preferencias/Productos/stock", GBStock->isChecked() );
 p->setValue( "Preferencias/Productos/Stock/permitir", CkBPermitir->isChecked() );
 p->setValue( "Preferencias/Productos/Stock/limitar", CkBLimitarVenta->isChecked() );
 p->setValue( "Preferencias/Productos/Stock/avisos", CkBAvisosStock->isChecked() );
 p->setValue( "Preferencias/Productos/Stock/limiteMinimo", DSBLimiteMinimo->value() );
}
