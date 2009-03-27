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
#include "eplugin.h"

#include "prespuesto.h"
#include <QMessageBox>

Presupuesto::Presupuesto(QObject *parent)
 : QObject(parent)
{
 _plugin = 0;
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
     pluginsDir.cd("presupuestos");
     QStringList filtro;
	// Obtengo el nombre del plugin de infoprog actual para cargar el del mismo nombre
#ifdef Q_WS_WIN32
	filtro.append( "*.dll" );
	int pos =  pluginsDir.entryList( filtro, QDir::Files  ).indexOf( preferencias::getInstancia()->value( "Preferencias/general/pluginInfo", "default" ).toString().append( ".dll" ) );
	int pos_def = pluginsDir.entryList( filtro, QDir::Files  ).indexOf( QString( "default" ).append( ".dll" ) );
#endif
#ifdef Q_WS_X11
	filtro.append( "*.so" );
	int pos =  pluginsDir.entryList( filtro, QDir::Files ).indexOf( preferencias::getInstancia()->value( "Preferencias/general/pluginInfo", "default" ).toString().prepend( "lib" ).append( ".so" ) );
	int pos_def = pluginsDir.entryList( filtro, QDir::Files  ).indexOf( QString( "default" ).prepend( "lib" ).append( ".so" ) );
#endif
	if( pos == -1 )
	{
		qCritical( "Error: No existe ningun plugin de presupuestos definidos! Verifique la instalación!" );
		qDebug( pluginsDir.entryList( filtro, QDir::Files ).join( ", " ).toLocal8Bit() );
		pos = pos_def;
        }
	loader->setFileName(  pluginsDir.absoluteFilePath( pluginsDir.entryList( QDir::Files ).at( pos ) )  );
        if( loader->load() )
        {
		_plugin = qobject_cast<EPresupuesto *>(loader->instance());
		_plugin->inicializar();
	}
	else
	{
		qWarning( "Error al cargar el plugin" );
		qWarning( QString( "Error: %1" ).arg( loader->errorString() ).toLocal8Bit() );
	}
	// Fin de la carga del plugin
	if( _plugin != 0 )
	{
		_plugin->regenerar( new QTextDocument() );
	}
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


/*!
    \fn Presupuesto::imprimir( QPainter *pintador )
 */
void Presupuesto::imprimir( QPainter *pintador )
{
    /// @todo implement me
}


/*!
    \fn Presupuesto::esValido()
 */
bool Presupuesto::esValido()
{  return !( _plugin == 0 ); }


QDate Presupuesto::fecha() const
{ return _plugin->fecha(); }


void Presupuesto::setFecha ( const QDate& theValue )
{ _plugin->setFecha( theValue ); }


QString Presupuesto::titulo() const
{ return _plugin->titulo(); }

void Presupuesto::setTitulo ( const QString& theValue )
{  _plugin->setTituloPersonalizado( theValue ); }

double Presupuesto::total() const
{ return _plugin->total(); }

void Presupuesto::setTotal ( double theValue )
{ _plugin->setTotal( theValue ); }

int Presupuesto::id_cliente() const
{return _id_cliente; }

void Presupuesto::setId_cliente ( int theValue )
{ _id_cliente = theValue;}

QString Presupuesto::texto_destinatario() const
{ return _plugin->cliente(); }

void Presupuesto::setTexto_destinatario ( const QString& theValue )
{ _plugin->setCliente( theValue ); }

void Presupuesto::generarDoc( const QTextDocument *docCont )
{
  if( !esValido() )
  { return; }

 _plugin->regenerar( docCont );
}

void Presupuesto::generarTablaProductos( QSqlTableModel *modelo, const QString tituloTabla, const bool cabeceras )
{ _plugin->generarTabla( modelo, tituloTabla, cabeceras ); }

QTextDocument * Presupuesto::previsualizacion()
{
 if( _plugin != 0 )
 { return _plugin->getDocumento(); }
 else
 { return new QTextDocument(); }
}
