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
#include "presupuestodefault.h"

#include <QSqlRecord>

/*!
    \fn PresupuestoDefault::nombre() const
	Devuelve el nombre  del plugin
	@return Nombre del plugin
 */
QString PresupuestoDefault::nombre() const
{
    return "default";
}

/*!
    \fn PresupuestoDefault::version() const
	Devuelve la version actual del plugin
	@return Version del plugin
 */
double PresupuestoDefault::version() const
{
    return 0.1;
}

/*!
    \fn PresupuestoDefault::setRegistro( const QSqlRecord *rec )
	Setea los valores del registro actual que se desea modelar
	@param rec Puntero al registro
 */
void PresupuestoDefault::setRegistro( QSqlRecord *rec )
{
  if( _rec == 0 )
  {
    _rec = new QSqlRecord();
  }
  _rec = rec;
}

/*!
    \fn PresupuestoDefault::obtenerHtml()
	Devuelve el contenido renderizado del presupuesto en formato html
 */
QString PresupuestoDefault::obtenerHtml()
{
    /// @todo implementar retorno de html de plugin default de prespuesto
}


/*!
    \fn PresupuestoDefault::obtenerContenido()
	Devuelve el contenido renderizado del presupuesto en formato interno
 */
QString PresupuestoDefault::obtenerContenido()
{
    /// @todo implementar retorno de contenido de plugin default de prespuesto
}

Q_EXPORT_PLUGIN2( default, PresupuestoDefault );
