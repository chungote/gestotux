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


#include <QDir>
#include <QApplication>
#include <QSqlRecord>
#include <QPainter>
#include <QSqlQuery>
#include <QSqlError>
#include "eplugin.h"

#include "prespuesto.h"
#include <QMessageBox>

Presupuesto::Presupuesto(QObject *parent)
 : QObject(parent)
{
 loader = new QPluginLoader( this );
 // Busco los plugins de presupuestos
 QDir pluginsDir = QDir(qApp->applicationDirPath());

 #if defined(Q_OS_WIN)
     if (pluginsDir.dirName().toLower() == "debug" || pluginsDir.dirName().toLower() == "release")
         pluginsDir.cdUp();
 #elif defined(Q_OS_MAC)
     if (pluginsDir.dirName() == "MacOS") {
         pluginsDir.cdUp();
         pluginsDir.cdUp();
         pluginsDir.cdUp();
     }
 #endif
     pluginsDir.cd("plugins");
     pluginsDir.cd("presupuesto");
#ifdef Q_WS_WIN32
	QStringList filtro;
	filtro.append( "*.dll" );
#endif
	// Obtengo el nombre del plugin de infoprog actual para cargar el del mismo nombre
	int pos =  pluginsDir.entryList( QDir::Files ).indexOf( prespuesto::pref()->value( "pluginInfo", "default" ).toString() );
	if( pos == -1 )
	{
		QMessageBox::critical( 0, "Error", "No existe ningun plugin de presupuestos definidos! Verifique la instalación!" );
		return;
        }
	loader->setFileName(  pluginsDir.absoluteFilePath( pluginsDir.entryList( QDir::Files ).at( pos ) )  );
        if( loader->load() )
        {
		_plugin = qobject_cast<EPresupuesto *>(loader->instance());
		
	}
	else
	{
		qWarning( "Error al cargar el plugin" );
		qWarning( QString( "Error: %1" ).arg( loader->errorString() ).toLocal8Bit() );
	}
	// Fin de la carga del plugin
}


Presupuesto::~Presupuesto()
{
}


/*!
    \fn Presupuesto::registro( int id )
 */
QSqlRecord Presupuesto::registro( int id )
{

 QSqlQuery cola( QString( "SELECT * FROM presupuestos WHERE id = '%1'" ).arg( id ) );
 if( cola.next() )
 {
	return cola.record();
 } 
 else
 {
  qDebug( "Error al buscar el registro de presupuesto" );
  qDebug(  QString( "detalle: %1" ).arg( cola.lastError().text() ).toLocal8Bit() );
  return QSqlRecord();
 }
}


/*!
    \fn Presupuesto::imprimir( QPainter *pintador )
 */
void Presupuesto::imprimir( QPainter *pintador )
{
    /// @todo implement me
}
