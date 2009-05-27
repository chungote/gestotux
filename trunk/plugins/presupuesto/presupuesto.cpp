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
#include "presupuesto.h"
#include "preferencias.h"

#include <QDir>
#include <QApplication>
#include <QSqlRecord>
#include <QPainter>
#include <QSqlQuery>
#include <QSqlError>

#include "prespuesto.h"
#include <QMessageBox>

Presupuesto::Presupuesto(QObject *parent)
 : QObject(parent)
{
}


Presupuesto::~Presupuesto()
{
}


/*!
    \fn Presupuesto::registro( int id )
 */
bool Presupuesto::registro( int id )
{
 QSqlQuery cola( QString( "SELECT * FROM presupuestos WHERE id = '%1'" ).arg( id ) );
 if( cola.next() )
 {
	_registro = cola.record();
	return true;
 }
 else
 {
  qDebug( "Error al buscar el registro de presupuesto" );
  qDebug(  QString( "detalle: %1" ).arg( cola.lastError().text() ).toLocal8Bit() );
  return false;
 }
}
