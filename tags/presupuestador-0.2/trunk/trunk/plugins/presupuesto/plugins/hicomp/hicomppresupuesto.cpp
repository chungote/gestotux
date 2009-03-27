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
#include "hicomppresupuesto.h"
#include <QString>
#include <QDate>

QString HiCompPresupuesto::nombre() const
{
 return "hicomp";
}

double HiCompPresupuesto::version() const
{
 return 0.1;
}

Q_EXPORT_PLUGIN2(hicomp, HiCompPresupuesto )


/*!
    \fn HiCompPresupuesto::total()
 */
double HiCompPresupuesto::total()
{
    /// @todo implement me
}


/*!
    \fn HiCompPresupuesto::cliente()
 */
QString HiCompPresupuesto::cliente()
{
    /// @todo implement me
}


/*!
    \fn HiCompPresupuesto::titulo()
 */
QString HiCompPresupuesto::titulo()
{
    /// @todo implement me
}


/*!
    \fn HiCompPresupuesto::getDocumento()
 */
QTextDocument * HiCompPresupuesto::getDocumento()
{
    /// @todo implement me
}


/*!
    \fn HiCompPresupuesto::tablaProductos()
 */
QTextTable * HiCompPresupuesto::tablaProductos()
{
    /// @todo implement me
}


/*!
    \fn HiCompPresupuesto::inicializar()
 */
void HiCompPresupuesto::inicializar()
{
    /// @todo implement me
}


/*!
    \fn HiCompPresupuesto::fecha()
 */
QDate HiCompPresupuesto::fecha()
{
    /// @todo implement me
}


/*!
    \fn HiCompPresupuesto::setCliente( QString nombre )
 */
void HiCompPresupuesto::setCliente( QString nombre )
{
    /// @todo implement me
}


/*!
    \fn HiCompPresupuesto::setFecha( QDate fecha )
 */
void HiCompPresupuesto::setFecha( QDate fecha )
{
    /// @todo implement me
}


/*!
    \fn HiCompPresupuesto::setTituloPersonalizado( QString titulo )
 */
void HiCompPresupuesto::setTituloPersonalizado( QString titulo )
{
    /// @todo implement me
}


/*!
    \fn HiCompPresupuesto::setTotal( double total )
 */
void HiCompPresupuesto::setTotal( double total )
{
    /// @todo implement me
}


/*!
    \fn HiCompPresupuesto::generarTabla( QSqlTableModel *modelo, QString titulo, bool cabecera )
 */
void HiCompPresupuesto::generarTabla( QSqlTableModel *modelo, QString titulo, bool cabecera )
{
    /// @todo implement me
}


/*!
    \fn HiCompPresupuesto::limpieza()
 */
void HiCompPresupuesto::limpieza()
{
    /// @todo implement me
}


/*!
    \fn HiCompPresupuesto::regenerar( const QTextDocument *doc )
 */
void HiCompPresupuesto::regenerar( const QTextDocument *doc )
{
    /// @todo implement me
}
