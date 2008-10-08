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
#include <QMessageBox>
#include "gestotux.h"
#include "preferencias.h"
#include "eenviobackup.h"
#include "esplash.h"
#include "emysql.h"

#define NOMBRE_CONEXION "gestotux"

FILE *debug;

 void myMessageOutput(QtMsgType type, const char *msg)
 {
     switch (type) {
     case QtDebugMsg:
         fprintf(debug, "Debug: %s\n", msg);
	 fflush(debug);
         break;
     case QtWarningMsg:
	QMessageBox::warning( 0, "Warning de aplicacion", msg );
	fprintf(debug, "warning: %s\n", msg);
	 fflush(debug);
        break;
     case QtCriticalMsg:
	QMessageBox::critical( 0, "Error Critico", msg );
	fprintf(debug, "critico: %s\n", msg);
	 fflush(debug);
        break;
     case QtFatalMsg:
         fprintf( debug, "Fatal: %s\n", msg);
	 fflush(debug);
         QMessageBox::critical( 0, "¡¡¡¡¡¡FATAL!!!!!!", msg );
         abort();
     }
 }

int main(int argc, char *argv[])
{
      Q_INIT_RESOURCE(gestotux);
	debug = fopen( "debug.txt", "w" );
	fseek( debug, 0, 0 );
	qInstallMsgHandler(myMessageOutput);
      QApplication app(argc, argv);
      // Muestro el splash
      ESplash splash;
      splash.show();
      splash.showMessage( "Cargando propiedades locales" );
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
       app.setStyleSheet( app.styleSheet().append( "QProgressBar:horizontal { border: 1px solid gray; border-radius: 6px; background: white; padding: 0px; text-align: center; } QProgressBar::chunk:horizontal { background: qlineargradient(x1: 0, y1: 0.5, x2: 1, y2: 0.5, stop: 0 blue, stop: 1 cyan); }" ) );
      }
      // Preferencias Idiomaticas
      QLocale locale( QLocale::Spanish, QLocale::Argentina );
      QLocale::setDefault( locale );

      splash.showMessage( "Cargando Traduccion" );
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
      splash.showMessage( "Cargando Base de datos" );
      // Chequeo la Base de Datos
      QSqlDatabase DB;
      /////////////////////////////////////////////////////////////////////////////////////////////////////////
      // Cargo el driver que este disponible, usando db interna y no se fuerza a usar mysql
      /////////////////////////////////////////////////////////////////////////////////////////////////////////
      if( DB.isDriverAvailable( "QSQLITE" ) == true && p->value( "noForzarMysql", true ).toBool() && p->value( "dbInterna", true ).toBool() )
      {
       QFile *base = new QFile( "gestotux.database" );
       if( !base->open( QIODevice::ReadOnly ) )
       {
	 qDebug( "-------------------------------------------------" );
	 qDebug( "El archivo de Base de datos no existe!");
	 qDebug( "-------------------------------------------------" );
		DB = QSqlDatabase::addDatabase("QSQLITE");
		DB.setDatabaseName( "gestotux.database" );
       		if( !DB.open() )
       		{
			qDebug( "Ultimo error: " + DB.lastError().text().toLocal8Bit() );
			abort();
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
	delete base;
        DB = QSqlDatabase::addDatabase("QSQLITE");
        DB.setDatabaseName("gestotux.database");
       	if( !DB.open() )
        {
     		qDebug( "Ultimo error: " + DB.lastError().text().toLocal8Bit() );
		abort();
        }
        /// FIN SQLITE
       }
       // si existe el driver y esta autorizado usar db externa o se quiere usar si o si la db mysql
       else if( (DB.isDriverAvailable( "QMYSQL" ) == true && p->value( "dbExterna", false ).toBool() ) || !p->value( "noForzarMysql", true ).toBool() )
       {
	 qWarning( "Usando mysql" );
	 EMysql dialogo;
	 dialogo.setDb( &DB );
	 if( dialogo.exec() )
	 {
		qDebug( "Base de datos abierta correctamente" );
         }
	 else
         {
		qWarning( "No se puede continuar sin la base de datos. Se saldra del programa" );
		exit(0);
         }
       }
       else
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
       ////////////////////////////////////////////////////////////////////////////////////////////////////
       // Inicia codigo general
       ////////////////////////////////////////////////////////////////////////////////////////////////////
       // Chequeo si existen las tablas, llegado este punto la base de datos debe estar abierta
       QStringList tablas = DB.tables( QSql::Tables );
       if( tablas.isEmpty() )
       {
		// Es la primera vez que se arranca el programa
		qDebug( "No existen tablas en la base de datos." );
		// Cada plugin debe inicializar sus propias tablas
       }
       else
       {
		qDebug( "Base de datos abierta" );
       }
       // Fin de arranque de la base de datos
	splash.showMessage( "Base de datos Abierta correctamente" );
	gestotux * mw = new gestotux();
 	splash.showMessage( "Cargando Ventana Principal" );
	mw->show();
	// Salir del programa cuando se cierren todas las ventanas
	app.connect( &app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()) );
 	splash.showMessage( "Listo." );
	if ( !p->value( "splash", false ).toBool() )
	{
 		splash.hide();
		//qDebug( "Ventana de splash cerrar" );
	}
        p->endGroup();
	p->endGroup();
	// Inicio el hilo de envio del backup
	EEnvioBackup envios( &app );
	envios.start( QThread::IdlePriority );
	mw->inicializar();
	if( p->value( "maximizado", true ).toBool() )
	{
		//qDebug( "Ventana maximizada" );
		mw->showMaximized();
	}
      return app.exec();
}
