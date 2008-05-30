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


#include <QtGui>
#include "gestotux.h"
#include <QTextEdit>
#include <QTextStream>
#include <QCloseEvent>
#include <QToolBar>
#include <QMenu>
#include <QStatusBar>
#include <QFileDialog>
#include <QMenuBar>
#include <QDockWidget>
#include <QToolBox>
#include <QSqlDatabase>

#include "reloj.h"
#include "formacercade.h"
#include "vcliente.h"
#include "preferencias.h"
#include "formulariocentral.h"
#include "formpreferencias.h"
#include "ebackup.h"
#include "eplugin.h"
#include "einfoprogramainterface.h"
#include "formactualizacion.h"

#define VERSION_PROGRAMA 0.2

FormularioCentral *gestotux::formCentral = 0;
QToolBar *gestotux::_barraAcciones = 0;
EInfoProgramaInterface *gestotux::_pluginInfo = 0;
QHash<QString, EPlugin *> *gestotux::_plugins = 0;

gestotux::gestotux()
{
// Eliminarse al cerarse
 this->setAttribute( Qt::WA_DeleteOnClose );
 setObjectName( "VentanaPrincipal" );
}

void gestotux::inicializar()
{ 
 cargarPlugins();

 setCentralWidget( formCen() );

 createActions();
 createMenus();
 createToolBar();
 createStatusBar();
 crearReloj();
 bandeja_sistema();

preferencias *p = preferencias::getInstancia();
//p->inicio();
p->beginGroup( "ventanaPrincipal" );
this->restoreState( p->value( "estado", "" ).toByteArray(), 0 );
p->endGroup();

 setWindowIcon( pluginInfo()->iconoPrograma() );
 setWindowTitle( pluginInfo()->nombrePrograma() );
}

void gestotux::closeEvent(QCloseEvent *event)
{
 salir();
 event->accept();
}

void gestotux::createActions()
{
      exitAct = new QAction( "Salir", this);
      exitAct->setStatusTip( "Salir del programa" );
      exitAct->setIcon( QIcon( ":/imagenes/exit.png" ) );
      connect(exitAct, SIGNAL( triggered() ), this, SLOT( close() ) );

      acercade = new QAction( "Acerca de...", this );
      acercade->setStatusTip( "Muestra informacion del programa" );
      connect( acercade, SIGNAL( triggered() ), this, SLOT( acerca() ) );

      ActClientes = new QAction( "Ver Clientes... ", this );
      ActClientes->setStatusTip( "Muestra la lista de clientes" );
      ActClientes->setIcon( QIcon( ":/imagenes/clientes.png" ) );
      connect( ActClientes, SIGNAL( triggered() ), this, SLOT( verClientes() ) );

      ActPreferencias = new QAction ( "Configuracion" , this );
      ActPreferencias->setStatusTip( "Modifica las preferencias de la aplicacion" );
      ActPreferencias->setIcon( QIcon( ":/imagenes/configure.png" ) );
      connect( ActPreferencias, SIGNAL( triggered() ), this, SLOT( verPreferencias() ) );

      ActBackup = new QAction( "Backup", this );
      ActBackup->setStatusTip( "Genera y retaura backups del programa" );
      ActBackup->setIcon( QIcon( ":/imagenes/backup.png" ) );
      connect( ActBackup, SIGNAL( triggered() ), this, SLOT( verBackup() ) );

	ActActualizar = new QAction( "Actualizar", this );
 	ActActualizar->setIcon( QIcon( ":/imagenes/actualizar.png" ) );
 	ActActualizar->setStatusTip( "Actualiza la aplicacion " );
 	connect( ActActualizar, SIGNAL( triggered() ), this, SLOT( verActualizacion() ) );
}

void gestotux::createMenus()
{
 fileMenu = menuBar()->addMenu( "&Archivo" );
 fileMenu->setObjectName( "menuArchivo" );
 fileMenu->addAction( ActActualizar );
 fileMenu->addSeparator();
 fileMenu->addAction( exitAct );

 menuHer = menuBar()->addMenu( "&Herramientas" );
 menuHer->setObjectName( "menuHerramientas" );
 menuHer->addAction( ActClientes );

 foreach( EPlugin *plug , plugins() )
 {
  //qDebug( QString("Creando menu de %1" ).arg( plug->nombre() ).toLocal8Bit() );
  plug->crearMenu( menuBar() );
 }

 menuHer->addSeparator();
 menuHer->addAction( ActBackup );
 menuHer->addAction( ActPreferencias );

 menuAyuda = menuBar()->addMenu( "A&yuda" );
 menuAyuda->setObjectName( "menuAyuda" );
 menuAyuda->addAction( acercade );
}

void gestotux::createStatusBar()
{
      statusBar()->showMessage( "Listo" );
}

gestotux::~gestotux()
{

}

/*!
    \fn presupuestador::salir()
    Guarda la configuracion general y de la ventana y cierra la base de datos
 */
void gestotux::salir()
{
 preferencias *p = preferencias::getInstancia();
 p->sync();
 //p->inicio();
 p->beginGroup( "ventanaPrincipal" );
 p->setValue( "estado", saveState( 0 ) );
 p->endGroup();

 QSqlDatabase DB = QSqlDatabase::database();
 DB.close();
 DB.removeDatabase( "gestotux.database" );
 close();
}

FormularioCentral *gestotux::formCen()
{
 if( gestotux::formCentral == 0 )
 {
  gestotux::formCentral = new FormularioCentral();
 }
 return gestotux::formCentral;
}


/*!
    \fn presupuestador::acerca()
 */
void gestotux::acerca()
{
 FormAcercaDe *f = new FormAcercaDe( this );
 f->adjustSize();
 f->show();
}


/*!
    \fn gestotux::verClientes()
 */
void gestotux::verClientes()
{ formCen()->agregarForm( new VCliente( formCen() ) ); }


void gestotux::createToolBar()
{
 tb = new QToolBar( "Barra de Herramientas", this );
 tb->setObjectName( "BarraPrincipal" );
 this->addToolBar( tb );
 tb->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
 foreach( EPlugin *plug , plugins() )
 {
  tb->addActions( plug->accionesBarra() );
 }
 tb->addAction( ActClientes );

 _barraAcciones = new QToolBar( "Acciones", this );
 _barraAcciones->setObjectName( "BarraAcciones" );
 this->addToolBar( Qt::BottomToolBarArea, _barraAcciones );
 _barraAcciones->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
}


QToolBar* gestotux::barraAcciones()
{
 if( _barraAcciones != 0 )
 {
  return _barraAcciones;
 }
 else
 {
  return 0;
 }
}


/*!
    \fn gestotux::crearReloj()
 */
void gestotux::crearReloj()
{
 QDockWidget *dw = new QDockWidget( "Reloj" , this );
 dw->setObjectName( "reloj" );
 dw->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
 addDockWidget( Qt::RightDockWidgetArea, dw );
 Reloj *r = new Reloj( dw );
 dw->setWidget( r );
}


void gestotux::verPreferencias()
{ formCen()->agregarForm( new FormPreferencias( this ) ); }


void gestotux::verBackup()
{ formCen()->agregarForm( new Ebackup( this ) ); }


void gestotux::bandeja_sistema()
{
 preferencias *p = preferencias::getInstancia();
 //p->inicio();
 p->beginGroup( "Preferencias" );
 p->beginGroup( "General" );
 bool bandeja = p->value( "icono_bandeja", false ).toBool();
 p->endGroup();
 p->endGroup();
 if( bandeja )
 {
   if( QSystemTrayIcon::isSystemTrayAvailable() )
   {
    iconoBandeja = new QSystemTrayIcon( this );
    QMenu *menu = new QMenu( this );
    menu->addAction( exitAct );
    iconoBandeja->setIcon( pluginInfo()->iconoPrograma() );
    iconoBandeja->setToolTip( "Gestotux" );
    iconoBandeja->show();
    connect( iconoBandeja, SIGNAL( activated( QSystemTrayIcon::ActivationReason ) ), this, SLOT( ocultar_mostrar( QSystemTrayIcon::ActivationReason ) ) );
   }
   else
   {
    qDebug( "No se pudo generar el icono en la bandeja del sistema" );
    return;
   }
 }
 else
 {
  //qDebug( "No quiso tener mensaje en la bandeja" );
  return;
 }
}


void gestotux::ocultar_mostrar( QSystemTrayIcon::ActivationReason razon )
{
  switch( razon )
 {
  case QSystemTrayIcon::Trigger:
  case QSystemTrayIcon::MiddleClick:
  case QSystemTrayIcon::DoubleClick:
  {
   if( this->isVisible() )
   {
    this->hide();
   }
   else
   {
    this->show();
   }
  }
 }
}


bool gestotux::cargarPlugins()
{
 pluginsDir = QDir(qApp->applicationDirPath());

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
	
	_plugins = new QHash<QString, EPlugin *>();
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
		if( plug->inicializar( preferencias::getInstancia() ) )
		{
			connect( obj, SIGNAL( agregarVentana( QWidget * ) ), formCen(), SLOT( agregarForm( QWidget * ) ) );
			_plugins->insert( plug->nombre(), plug );
			if( plug->tipo() == EPlugin::info )
			{
				_pluginInfo = qobject_cast<EInfoProgramaInterface *>(obj);
			}
			qDebug( QString( "Cargando Plugin: %1" ).arg( pluginsDir.absoluteFilePath( fileName )).toLocal8Bit() );
		}
		else
		{
			qWarning( QString( "Error de inicializacion en el plug in %1" ).arg( plug->nombre() ).toLocal8Bit() );
		}
	 }
	 else
	 {
		qWarning( QString( "Error al cargar el plugin: %1" ).arg( loader.errorString() ).toLocal8Bit() );
	 }
     }
 return true;
}

EInfoProgramaInterface *gestotux::pluginInfo()
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
    \fn gestotux::plugins()
 */
QList<EPlugin *> gestotux::plugins()
{
  return _plugins->values();
}


/*!
    \fn gestotux::verActualizacion()
 */
void gestotux::verActualizacion()
{ formCen()->agregarForm( new FormActualizacion( formCen() ) ); }


/*!
    \fn gestotux::pluginsHash()
 */
QHash<QString, EPlugin *> *gestotux::pluginsHash()
{ return _plugins; }
