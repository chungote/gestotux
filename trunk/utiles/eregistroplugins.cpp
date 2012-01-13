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
#include <QApplication>

ERegistroPluginsDatos::ERegistroPluginsDatos()
{
 _plugins = new QHash<QString, EPlugin *>();
 _pluginInfo = 0;
 _pluginEmail = 0;
 qDebug( "Datos de ERegistroPlugin Creados" );
}

ERegistroPlugins *ERegistroPlugins::instance = 0;

ERegistroPlugins::ERegistroPlugins( QObject */*parent*/ )
{
    datos = new ERegistroPluginsDatos;
    qDebug( "ERegistroPlugins construido" );
}


ERegistroPlugins::~ERegistroPlugins()
{
}

/*!
 * \fn ERegistroPlugins::getInstancia()
 * Devuelve una instancia unica de este objeto
 */
ERegistroPlugins* ERegistroPlugins::getInstancia()
{
 if (instance==0)
 {
  instance = new ERegistroPlugins();
 }
 return instance;
}

/*!
 * \fn ERegistroPlugins::pluginInfo()
 * Devuelve un puntero al plugin de EInfoProgramaInterface que esta activo.
 */
EInfoProgramaInterface *ERegistroPlugins::pluginInfo()
{
 if( datos->_pluginInfo != 0 )
 {
     return datos->_pluginInfo;
 }
 else
 {
  qWarning( "Llamando al pluginInfo antes de cargarlo" );
  abort();
 }
}


/*!
 * \fn ERegistroPlugins::plugins()
 * Devuelve el listado de punteros a los plugins que se encuentran cargados como un QList
 */
QList<EPlugin *> ERegistroPlugins::pluginsPunteros()
{
  return datos->_plugins->values();
}

/*!
 * \fn ERegistroPlugins::plugins()
 * Devuelve el listado de punteros a los plugins que se encuentran cargados como un QList
 */
QStringList ERegistroPlugins::plugins()
{
    return datos->_plugins->keys();
}

/*!
 *   \fn ERegistroPlugins::pluginsHash()
 * Devuelve un listado de los plugins que estan cargados con un Hash <nombre, puntero>
 */
QHash<QString, EPlugin *> *ERegistroPlugins::pluginsHash()
{ return datos->_plugins; }

/*!
 * \fn ERegistroPlugins::pluginEmail()
 * Devuelve el puntero al plugin de email activo
 */
EInterfazEmail *ERegistroPlugins::pluginEmail()
{
 return datos->_pluginEmail;
}


/*!
 * \fn ERegistroPlugins::agregarPlugin( EPlugin *obj )
 * Agrega el plugin pasado como parametro a la lista interna
 */
void ERegistroPlugins::agregarPlugin( EPlugin *obj )
{
 datos->_plugins->insert( obj->nombre(),obj );
}


/*!
 * \fn ERegistroPlugins::plugin( const QString &nombre )
 * Devuelve el objeto referenciante al plugin con ese nombre
 */
EPlugin* ERegistroPlugins::plugin( const QString &nombre )
{
 return datos->_plugins->value( nombre );
}


/*!
 * \fn ERegistroPlugins::setPluginInfo( EInfoProgramaInterface *obj )
 * Setea el objeto de plugin de informacion
 */
void ERegistroPlugins::setPluginInfo( EInfoProgramaInterface *obj )
{
 qDebug( QString( "Seteando plugin de Info cliente: %1" ).arg( obj->nombrePrograma() ).toLocal8Bit() );
 datos->_pluginInfo = obj;
}


/*!
 * \fn ERegistroPlugins::setPluginEmail( EInterfazEmail *obj )
 * Setea el objeto de plugin de email
 */
void ERegistroPlugins::setPluginEmail( EInterfazEmail *obj )
{
    datos->_pluginEmail = obj;
}

/*!
 * \fn ERegistroPlugins::existePlugin( const QString &nombre )
 * Verifica la existencia de un plugin especifico en los plugins cargados
 * \return Verdadero si existe, Falso en caso contrario.
 */
bool ERegistroPlugins::existePlugin( const QString &nombre )
{
 return datos->_plugins->contains( nombre );
}

/*!
 * \fn ERegistroPlugins::existePluginExterno( const QString &nombre )
 * Verifica la existencia de un plugin especifico en los plugins cargados
 * \return Verdadero si existe, Falso en caso contrario.
 */
bool ERegistroPlugins::existePluginExterno( const QString &nombre )
{
    return datos->_plugins->contains( nombre );
}

/*!
 * \fn ERegistroPlugins::pluginInfoSeteado()
 * Devuelve si esta seteado el plugin de informacion del programa
 */
bool ERegistroPlugins::pluginInfoSeteado()
{
    if( datos->_pluginInfo == 0 )
    {
        return false;
    }
    else
    {
        return true;
    }
}
