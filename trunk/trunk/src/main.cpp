/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   				   *
 *   juiraze@yahoo.com.ar   						   *
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
#include "eemail.h"
#include "eplugin.h"
#include "einfoprogramainterface.h"
#include "einterfazemail.h"
#include <QPluginLoader>
#include "formulariocentral.h"
#include "eregistroplugins.h"

#define NOMBRE_CONEXION "gestotux"

FILE *debug;
/*!
 * /fn myMessageOutput( QtMsgType type, const char *msg )
 * Función de salida personalizada para redireccionar la salida de la aplicación al archivo debug.txt y mantener un registro de todas las cosas que suceden dentro del programa.
 * @param type Tipo de salida.
 * @param msg Mensaje de salida.
 */
 void myMessageOutput(QtMsgType type, const char *msg)
 {
     switch (type) {
         case QtDebugMsg:
            fprintf(debug, "Debug: %s\n", msg);
            fflush(debug);
            break;
         case QtWarningMsg:
            #ifdef GESTOTUX_DESARROLLO
            QMessageBox::warning( 0, "Warning de aplicacion", msg );
            #endif
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


/*!
 * \fn hacerTablas( QString nombrePlug )
 * Función auxiliar que irve para generar las tablas al inicializar la aplicacion o cuando se inicializa un nuevo plugin.
 * Busca dentro los recursos embebidos, dentro de la carpeta sql, el archivo <plugin>.<driversql>.sql
 * @param nombrePlug Nombre del plugin que se intenta inicializar sus datos.
 * @return si se pudo crear la tabla o si existio algun error al intentar ejecutar la cola de creación.
 */
bool hacerTablas( QString nombrePlug )
{
 if( QFile::exists( ":/sql/"+nombrePlug+"."+QSqlDatabase::database().driverName()+".sql" ) )
 {
        QFile archivo( ":/sql/"+nombrePlug+"."+QSqlDatabase::database().driverName()+".sql" );
        if( archivo.open( QIODevice::ReadOnly | QIODevice::Text ) )
        {
                QStringList cadenas = QString( archivo.readAll() ).split( ";" );
                QString cadena; QSqlQuery cola;
                foreach( cadena, cadenas )
                {
                        qDebug( qPrintable( cadena ) );
                        if( cadena.isEmpty() || cadena.isNull() ) {
                                qDebug( "Cadena vacia, salteandola..." );
                            } else {
                                if( !cola.exec( cadena ) )
                                {
                                        qDebug( qPrintable( cadena ) );
                                        qDebug( qPrintable( "Fallo...." + cola.lastError().text() ) );
                                        return false;
                                }
                                else
                                { qDebug( "Ok" ); }
                            }
                }
                return true;
        }
        else
        {
                qWarning(qPrintable( "Error al abrir el archivo: :/sql/"+nombrePlug+"."+QSqlDatabase::database().driverName()+".sql" ) );
                return false;
        }
 }
 else
 {
  qWarning( qPrintable( "No se pudo generar las tablas del plugin " + nombrePlug + ". No se encontro el archivo: :/sql/"+nombrePlug+"."+QSqlDatabase::database().driverName()+".sql" ) );
  return false;
 }
}


/**
 * \mainpage Documentacion interna de Gestotux
 *
 * Esta es la documentacion interna de gestotux respecto a su estructura de codigo. Si desea conocer mas datos hacerca de el modo de funcionamiento del programa por favor dirijase a http://gestotux.googlecode.com/ para acceder al wiki de el programa.
 */
int main(int argc, char *argv[])
{
      // Inicializa imagenes y archivos internos
      Q_INIT_RESOURCE(gestotux);
      // Maneja la salida del programa
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
      QApplication::setStyle( QStyleFactory::create( p->value( "estilo", "float" ).toString() ) );
      app.setEffectEnabled( Qt::UI_AnimateMenu, true );
      app.setEffectEnabled( Qt::UI_AnimateCombo, true );
      app.setEffectEnabled( Qt::UI_FadeTooltip, true );
      app.setEffectEnabled( Qt::UI_FadeMenu, true );
      if( p->value( "sobreestilo", false ).toBool() )
      {
                QDir dir( QCoreApplication::applicationDirPath() );
                dir.cd( "sobreestilos" );
                dir.cd( p->value( "sobreestilonombre", "" ).toString() );
                QFile file( dir.absoluteFilePath( p->value( "sobreestilonombre", "" ).toString().append( ".qss" ) ) );
                file.open(QFile::ReadOnly);
                QString styleSheet = QLatin1String(file.readAll());
                qApp->setStyleSheet(styleSheet);
      }
      // Preferencias Idiomaticas
      QLocale locale( QLocale::Spanish, QLocale::Argentina );
      QLocale::setDefault( locale );
      splash.showMessage( "Cargando Traduccion" );
      // Cargo las traducciones
      QTranslator tran;
      QDir *directorio = new QDir( QCoreApplication::applicationDirPath() );
      directorio->cd( "traducciones" );
      /*if( tran.load( directorio->absoluteFilePath( "qt_es" ) ) )
      {
        app.installTranslator(&tran);
      }
      else
      {
        qDebug( "Fallo al cargar la traduccion" );
      }*/
      if( tran.load( directorio->absoluteFilePath( "ncreport_es" ) ) )
      { QCoreApplication::instance()->installTranslator(&tran); }
      else
      { qDebug( "Fallo al cargar la traduccion del reporte" ); }
      delete directorio;
      directorio = 0;
      splash.showMessage( "Cargando Base de datos" );
      // Chequeo la Base de Datos
      bool fallosql = false;
      if( ( QSqlDatabase::isDriverAvailable( "QMYSQL" ) == true && p->value( "dbExterna", false ).toBool() ) || !p->value( "noForzarMysql", true ).toBool() )
      {
         //qWarning( "Usando mysql" );
         EMysql dialogo;
         int ret = dialogo.exec();
         switch( ret )
         {
                case EMysql::Conectado:
                {
                        qDebug( "Base de datos abierta correctamente" );
                        fallosql = false;
                        break;
                }
                case EMysql::Cancelado:
                {
                        qWarning( "No se puede continuar sin la base de datos. Se saldra del programa" );
                        exit(0);
                        break;
                }
                case EMysql::Interna:
                {
                        fallosql = true;
                        break;
                }
                default:
                {
                        qWarning( qPrintable( "Retorno desconocido: " + QString::number( ret ) ) );
                        abort();
                        break;
                }
        }
      } else { fallosql = true; }
      /////////////////////////////////////////////////////////////////////////////////////////////////////////
      // Cargo el driver que este disponible, usando db interna y no se fuerza a usar mysql
      /////////////////////////////////////////////////////////////////////////////////////////////////////////
      if( QSqlDatabase::isDriverAvailable( "QSQLITE" ) && fallosql == true )
      {
       QFile *base = new QFile( "gestotux.database" );
       if( !base->open( QIODevice::ReadOnly ) )
       {
         qDebug( "-------------------------------------------------" );
         qDebug( "El archivo de Base de datos no existe!");
         qDebug( "-------------------------------------------------" );
                QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE");
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
        QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE");
        DB.setDatabaseName("gestotux.database");
        if( !DB.open() )
        {
                qDebug( "Ultimo error: " + DB.lastError().text().toLocal8Bit() );
                abort();
        }
        /// FIN SQLITE
       }
       else if( fallosql == true || !QSqlDatabase::database().isValid() )
       {
        // No se puede usar sqlite para el programa
        qDebug( "No se puede encontrar el plug-in para la Base de Datos" );
        QStringList drivers = QSqlDatabase::drivers();
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
       QStringList tablas = QSqlDatabase::database().tables( QSql::Tables );
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
        /////////////////////////////////////////////////////////////////////////////////////////////////
        // Cargo los plugins aca
        /////////////////////////////////////////////////////////////////////////////////////////////////
        // Necesito el formulario principal para algunas cosas
        splash.showMessage( "Cargando Ventana Principal" );
        gestotux * mw = new gestotux();
        ////////////////////////////////////////////////////////
        splash.showMessage( "Cargando plugins" );
        QPluginLoader loader;
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
                QStringList filtro;
        #ifdef Q_WS_WIN32
                filtro.append( "*.dll" );
        #endif
        #ifdef Q_WS_X11
                filtro.append( "*.so" );
        #endif
             foreach( QString fileName, pluginsDir.entryList( filtro, QDir::Files ) )
             {
                loader.setFileName(  pluginsDir.absoluteFilePath( fileName )  );
                 if( loader.load() )
                 {
                        QObject *obj = loader.instance();
                        EPlugin *plug = qobject_cast<EPlugin *>( obj );
                        // veo que tipo es para que al inicializar y cargar plugins dependientes, pueda usarse el valor
                        if( plug->tipo() == EPlugin::info )
                        {
                                ERegistroPlugins::getInstancia()->setPluginInfo( qobject_cast<EInfoProgramaInterface *>(obj) );
                                preferencias::getInstancia()->inicio();
                                preferencias::getInstancia()->setValue( "pluginInfo", plug->nombre() );
                        }
                        else if ( plug->tipo() == EPlugin::email )
                        {
                                ERegistroPlugins::getInstancia()->setPluginEmail( qobject_cast<EInterfazEmail *>(obj) );
                                preferencias::getInstancia()->inicio();
                                preferencias::getInstancia()->setValue( "pluginEmail", plug->nombre() );
                        }
                        if( plug->inicializar() )
                        {
                                QObject::connect( obj, SIGNAL( agregarVentana( QWidget * ) ), mw->formCen(), SLOT( agregarForm( QWidget * ) ) );
                                QObject::connect( obj, SIGNAL( agregarDockWidget( Qt::DockWidgetArea, QDockWidget * ) ), mw, SLOT( agregarDock( Qt::DockWidgetArea, QDockWidget * ) ) );
                                QObject::connect( mw, SIGNAL( saliendoGestotux() ), obj, SLOT( seCierraGestotux() ) );
                                //Verifico sus tablas
                                if( plug->verificarTablas( tablas ) != true )
                                {
                                        // estan cargados los archivo resource cuando cargo el plugin?
                                        if( hacerTablas( plug->nombre() ) )
                                        {
                                                // todo ok
                                                qDebug( "Tablas creadas correctamente" );
                                                // Actualizo la lista de tablas para que incluya las ultimas agregadas
                                                tablas = QSqlDatabase::database().tables();
                                        }
                                        else
                                        {
                                                // No se pudieron cargar las tablas
                                                qWarning( "No se pudo crear la tabla" );
                                                continue;
                                        }
                                }
                                ERegistroPlugins::getInstancia()->agregarPlugin( plug );
                                splash.showMessage( "Cargando plugin "+ plug->nombre() );
                                //////////////////////////////////////////////////////////////////////////////////////
                                /*if( !tran.load(QApplication::applicationDirPath() + QDir::separator() + "traducciones" + QDir::separator() + plug->nombre() ) )
                                {  qDebug( qPrintable( "Error al cargar la traduccion de " + plug->nombre()  ) ); }
                                else {  QCoreApplication::instance()->installTranslator( &tran ); }*/
                                qDebug( QString( "Cargando Plugin: %1" ).arg( pluginsDir.absoluteFilePath( fileName )).toLocal8Bit() );
                        }
                        else
                        {
                                qWarning( QString( "Error de inicializacion en el plug in %1" ).arg( plug->nombre() ).toLocal8Bit() );
                        }
                 }
                 else
                 {
                        qWarning( QString( "Error al cargar el plugin" ).toLocal8Bit() );
                        qWarning( loader.errorString().toLocal8Bit() );
                 }
             }


        /////////////////////////////////////////////////////////////////////////////////////////////////
        if ( !p->value( "splash", false ).toBool() )
        { splash.finish( mw ); }
        mw->show();
        // Salir del programa cuando se cierren todas las ventanas
        app.connect( &app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()) );
        splash.showMessage( "Listo." );
        // Inicio el hilo de envio del backup
        /*EEnvioBackup envios( &app );
        envios.start( QThread::IdlePriority );
        QObject::connect( mw, SIGNAL( saliendoGestotux() ), &envios, SLOT( terminate() ) );*/
        mw->inicializar();
        if( p->value( "maximizado", true ).toBool() )
        { mw->showMaximized(); }
        int ret = app.exec();
        QSqlDatabase::removeDatabase( "qt_sql_default_connection" );
        return ret;
}
