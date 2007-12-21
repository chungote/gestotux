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

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSqlDatabase>
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlError>
#include <QDir>
#include <QStyleFactory>
#include <QSplashScreen>
#include <QIcon>
#include <QApplication>
#include "gestotux.h"
#include "preferencias.h"
#include "eenviobackup.h"

int main(int argc, char *argv[])
{
      Q_INIT_RESOURCE(gestotux);
      QApplication app(argc, argv);
      app.setWindowIcon( QIcon( ":/imagenes/icono.png" ) );
      // Muestro el splash
      QPixmap pixmap(":/imagenes/splash.png");
      QSplashScreen *splash = new QSplashScreen(pixmap);
      splash->show();
      splash->showMessage( "Cargando propiedades locales" );
      // Permite que el programa tenga el Look & Feel del escritorio actual
      app.setDesktopSettingsAware( true );
      preferencias *p = preferencias::getInstancia();
      p->beginGroup( "Preferencias" );
      p->beginGroup( "General" );
      QApplication::setStyle( QStyleFactory::create( p->value( "estilo", "CleanLooks" ).toString() ) );
      app.setEffectEnabled( Qt::UI_AnimateMenu, true );
      app.setEffectEnabled( Qt::UI_AnimateCombo, true );
      app.setEffectEnabled( Qt::UI_FadeTooltip, true );
      app.setEffectEnabled( Qt::UI_FadeMenu, true );
      if( p->value( "barra_personalizada", false ).toBool() )
      {
       app.setStyleSheet( app.styleSheet().append( "QProgressBar:horizontal { border: 1px solid gray; border-radius: 6px; background: white; padding: 0px; text-align: center; text-padding: 4px; text-weight: bold; } QProgressBar::chunk:horizontal { background: qlineargradient(x1: 0, y1: 0.5, x2: 1, y2: 0.5, stop: 0 blue, stop: 1 cyan); }" ) );
      }
      // Preferencias Idiomaticas
      QLocale locale( QLocale::Spanish, QLocale::Argentina );
      QLocale::setDefault( locale );

      splash->showMessage( "Cargando Traduccion" );
      // Cargo las traducciones
      QTranslator tran;
      QDir *directorio = new QDir( QCoreApplication::applicationDirPath() );
      directorio->cd( "traducciones" );
      if( tran.load( directorio->absoluteFilePath( "qt_es" ) ) )
      {
        app.installTranslator(&tran);
      }
      else
      {
	qDebug( "Fallo al cargar la traduccion" );
      }
      delete directorio;
	splash->showMessage( "Cargando Base de datos" );
      // Chequeo la Base de Datos
      QSqlDatabase DB;
      if( DB.isDriverAvailable( "QSQLITE" ) == false )
      {
 	// No se puede usar sqlite para el programa
	qDebug( "No se puede encontrar el plug-in para la Base de Datos" );
	QStringList drivers = DB.drivers();
	qDebug( "Lista de Drivers Soportados:" );
	for (int i = 0; i < drivers.size(); ++i)
	{
		qDebug( drivers.at(i).toLocal8Bit() );
	}
	abort();
       }
       QFile *base = new QFile( "gestotux.database" );
       if( !base->open( QIODevice::ReadOnly ) )
       {
	 qDebug( "-------------------------------------------------" );
	 qDebug( "El archivo de Base de datos no existe!");
	 qDebug( "-------------------------------------------------" );
         // El archivo de base de datos no existe
         QFile origen( ":/sql/digifauno.origin" );
 	 if( origen.open( QIODevice::ReadOnly ) )
	 {
		if( !origen.copy( "gestotux.database" ) )
		{
			qDebug( "No se pudo copiar el archivo de datos original" );
	 		qDebug( "-------------------------------------------------" );
			exit(-1);
		}
	 }
	 else
	 {
		qFatal( "No se encuentra el archivo embebido original" );
	 }
	}
	else
	{
		// Aunque exista chequeo que no sea de tam 0
		if( base->size() <= 0 )
		{
			qFatal( "Error! El archivo de db tiene menos o es igual a 0 bytes " );
		}
	}
       DB = QSqlDatabase::addDatabase("QSQLITE");
       DB.setDatabaseName( "gestotux.database" );
       if( !DB.open() )
       {
	qDebug( "Ultimo error: " + DB.lastError().text().toLocal8Bit() );
	abort();
       }
       // Chequeo si existen las tablas
       QStringList tablas = DB.tables();
       if( tablas.isEmpty() )
       {
		qDebug( "No existen tablas en la base de datos. Se copiaran..." );
       }
       else
       {
		qDebug( "Base de datos abierta" );
       }
       // Fin de arranque de la base de datos
	splash->showMessage( "Base de datos Abierta correctamente" );
	gestotux * mw = new gestotux();
	mw->inicializar();
	splash->showMessage( "Cargando Ventana Principal" );
	mw->show();
	if( p->value( "maximizado", false ).toBool() )
	{
		mw->showMaximized();
	}
	// Salir del programa cuando se cierren todas las ventanas
	app.connect( &app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()) );
	splash->showMessage( "Listo." );
	if ( !p->value( "splash", true ).toBool() )
	{
		splash->hide();
		delete splash;
	}
        p->endGroup();
	p->endGroup();
	// Inicio el hilo de envio del backup
	EEnvioBackup *envios = new EEnvioBackup();
	envios->start( QThread::IdlePriority );
      return app.exec();
}

