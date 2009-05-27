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
#ifndef EREGISTROPLUGINS_H
#define EREGISTROPLUGINS_H

#include <QObject>
#include <QMap>
#include "eplugin.h"
#include <QList>
#include <QHash>

class EInfoProgramaInterface;
class EInterfazEmail;

/**
Clase que mantiene la lista de plugins y los muestra en un formulario de preferencias

	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class ERegistroPlugins : public QObject
{
Q_OBJECT
public:
    ERegistroPlugins(QWidget *parent = 0);
    static EInfoProgramaInterface *pluginInfo();
    static QList<EPlugin *> plugins();
    static EInterfazEmail *pluginEmail();
    static QHash<QString, EPlugin *> *pluginsHash();
    ~ERegistroPlugins();
    void agregarPlugin( EPlugin *obj );
    EPlugin *plugin( const QString &nombre );
    void setPluginInfo( EInfoProgramaInterface *obj );
    static ERegistroPlugins *getInstancia();
    void setPluginEmail( EInterfazEmail *obj );

private:
	static QHash<QString, EPlugin *> *_plugins;
	static EInfoProgramaInterface *_pluginInfo;
	static EInterfazEmail *_pluginEmail;
	static ERegistroPlugins *instance;
};

#endif
