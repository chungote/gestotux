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
#include "gestotuxdefault.h"

bool GestotuxDefault::publicidad()
//{ return true; }
{ return false; }

double GestotuxDefault::version() const
{ return 1; }

QIcon GestotuxDefault::iconoPrograma() const
{ return QIcon( ":/imagenes/gestotux32.png"  ); }

QImage GestotuxDefault::imagenPrograma() const
{ return QImage( ":/imagenes/gestotux.png"  ); }

QString GestotuxDefault::companeros()
{ return ""; }

QString GestotuxDefault::directorioActualizaciones() const
{ return ""; }

QString GestotuxDefault::directorioBackup() const
{ return ""; }

QString GestotuxDefault::empresa() const
{ return "uso generico"; }

QString GestotuxDefault::nombrePrograma() const
{ return "Gestotux"; }

bool GestotuxDefault::inicializar()
{
    Q_INIT_RESOURCE(default);
    return true;
}

bool GestotuxDefault::verificarTablas( QStringList /*tablas*/ )
{ return true; }

int GestotuxDefault::tipo() const
{ return EPlugin::info; }

QList< QActionGroup * > GestotuxDefault::accionesBarra()
{ return QList<QActionGroup *>(); }

QString GestotuxDefault::nombre() const
{ return "default"; }

QWidgetList GestotuxDefault::formsPreferencias()
{ return QWidgetList();}

void GestotuxDefault::crearMenu(QMenuBar* m)
{
    (void)m;
}

void GestotuxDefault::crearToolBar(QToolBar* t)
{
    (void)t;
}

void GestotuxDefault::seCierraGestotux()
{
 qDebug( "Cerrado plugin default" );
 Q_CLEANUP_RESOURCE(default);
 return;
}

QAction *GestotuxDefault::botonPantallaInicial()
{ return 0; }

Q_EXPORT_PLUGIN2( zinfo, GestotuxDefault );
