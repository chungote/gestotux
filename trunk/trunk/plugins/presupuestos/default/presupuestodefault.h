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
#ifndef DEFAULT_H
#define DEFAULT_H

#include "epresupuesto.h"
#include <QObject>
class QSqlRecord;

/**
 *  \brief Implementacion predeterminada de un presupuesto
 *    
 *  Implementacion predeterminada del modelado de un presupuesto para gestotux
 *	@author Esteban Zeller <juiraze@yahoo.com.ar>
 */
class PresupuestoDefault : public QObject, EPresupuesto
{
Q_OBJECT
Q_INTERFACES(EPresupuesto)
public:
    QString nombre() const;
    double version() const;
    void setRegistro( QSqlRecord *rec );
    QString obtenerHtml();
    QString obtenerContenido();

private:
   /*!
    * Puntero interno a el registro que se va a modelar
    */ 
    QSqlRecord *_rec;
};

#endif
