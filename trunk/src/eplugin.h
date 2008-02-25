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
#ifndef EPLUGIN_H
#define EPLUGIN_H

#include <QtPlugin>
#include <QString>
#include <QAction>
#include <QList>
#include <QStackedWidget>
#include <QSettings>
#include <QMenuBar>

/**
 *  \brief Interface de plugin en general
 * 
 *  Clase que sirve como interfaz de un plugin general
 *  Tambien posee los metodos para integrarse a la ventana principal y asociar los punteros necesarios.
 *
 *	@author Esteban Zeller <juiraze@yahoo.com.ar>
 */
class EPlugin
{
public:
    enum tipo
    {
      db = 0,
      comun = 1,
      info = 2
    };
    virtual ~EPlugin() {}
    virtual QList<QAction *> accionesBarra() const = 0;
    virtual bool inicializar( QStackedWidget *formCen, QSettings *pref ) = 0;
    virtual QWidgetList formsPreferencias() = 0;
    virtual QString nombre() const = 0;
    virtual int tipo() const = 0;
    virtual void crearMenu( QMenuBar *m ) = 0;
    virtual void verificarTablas() = 0;
    virtual double version() const = 0;

};

Q_DECLARE_INTERFACE( EPlugin,
                     "tranfuga.EPlugin/1.0" );

#endif
