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
#ifndef EPRESUPUESTO_H
#define EPRESUPUESTO_H

#include <QtPlugin>
class QString;
class QDate;
class QTextTable;
class QTextDocument;
class QSqlTableModel;
/**
 * \brief Interfaz de presupuesto
 *
 * Interfaz para especificaciones del plugin presupuesto
 *
 *	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class EPresupuesto
{
public:
    virtual ~EPresupuesto() {}
    virtual QString nombre() const = 0;
    virtual double version() const = 0;
    virtual void setCliente( const QString nombre ) = 0;
    virtual void setFecha( const QDate fecha ) = 0;
    virtual void setTituloPersonalizado( const QString titulo ) = 0;
    virtual QTextTable *tablaProductos() = 0;
    virtual void setTotal( const double t ) = 0;
    virtual QTextDocument *getDocumento() = 0;
    virtual double total() = 0;
    virtual QString cliente() = 0;
    virtual QString titulo() = 0;
    virtual QDate fecha() = 0;
    virtual void generarTabla( QSqlTableModel *mod, const QString tituloTabla, const bool cabceras ) = 0;
    virtual void regenerar( const QTextDocument *doCont ) = 0;
};

Q_DECLARE_INTERFACE(EPresupuesto,
                    "tranfuga.EPresupuesto/1.0" )

#endif

