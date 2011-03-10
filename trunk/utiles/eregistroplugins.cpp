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
#include "eregistroplugins.h"
#include "einterfazemail.h"
#include "einfoprogramainterface.h"

ERegistroPlugins *ERegistroPlugins::instance = 0;
EInfoProgramaInterface *ERegistroPlugins::_pluginInfo = 0;
QHash<QString, EPlugin *> *ERegistroPlugins::_plugins = 0;
EInterfazEmail *ERegistroPlugins::_pluginEmail = 0;

ERegistroPlugins::ERegistroPlugins(QWidget *parent)
{
 (void)parent; // Elimina el mensaje de warning
 _plugins = new QHash<QString, EPlugin *>();
}


ERegistroPlugins::~ERegistroPlugins()
{
}

ERegistroPlugins* ERegistroPlugins::getInstancia()
{
 if (instance==0)
 {
  instance = new ERegistroPlugins();
 }
 return instance;
}

EInfoProgramaInterface *ERegistroPlugins::pluginInfo()
{
 if( _pluginInfo != 0 )
 {
  return _pluginInfo;
 }
 else
 {
  qWarning( "Llamando al pluginInfo antes de cargarlo" );
  abort();
 }
}


/*!
    \fn ERegistroPlugins::plugins()
 */
QList<EPlugin *> ERegistroPlugins::plugins()
{
  return _plugins->values();
}

/*!
    \fn ERegistroPlugins::pluginsHash()
 */
QHash<QString, EPlugin *> *ERegistroPlugins::pluginsHash()
{ return _plugins; }


EInterfazEmail *ERegistroPlugins::pluginEmail()
{
 return _pluginEmail;
}



/*!
    \fn ERegistroPlugins::agregarPlugin( EPlugin *obj )
 */
void ERegistroPlugins::agregarPlugin( EPlugin *obj )
{
 _plugins->insert( obj->nombre(),obj );
}


/*!
    \fn ERegistroPlugins::plugin( const QString &nombre )
        Devuelve el objeto referenciante al plugin con ese nombre
 */
EPlugin* ERegistroPlugins::plugin( const QString &nombre )
{
 return _plugins->value(nombre);
}


/*!
    \fn ERegistroPlugins::setPluginInfo( EInfoProgramaInterface *obj )
        Setea el objeto de plugin de informacion
 */
void ERegistroPlugins::setPluginInfo( EInfoProgramaInterface *obj )
{
 _pluginInfo = obj;
}


/*!
    \fn ERegistroPlugins::setPluginEmail( EInterfazEmail *obj )
 */
void ERegistroPlugins::setPluginEmail( EInterfazEmail *obj )
{
  _pluginEmail = obj;
}


/*!
    \fn ERegistroPlugins::existePlugin( const QString &nombre )
 */
bool ERegistroPlugins::existePlugin( const QString &nombre )
{
 return _plugins->contains( nombre );
}
