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
#include "einfoprogramainterface.h"

FormularioCentral *gestotux::formCentral = 0;
QToolBar *gestotux::_barraAcciones = 0;
EInfoProgramaInterface *gestotux::_plugin = 0;

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
 p->inicio();
 p->beginGroup( "ventanaPrincipal" );
 this->restoreState( p->value( "estado", "" ).toByteArray(), 0 );
 p->endGroup();

 setWindowIcon( plugin()->iconoPrograma() );
 setWindowTitle( plugin()->nombrePrograma() );
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

      /*ActRecibosAnteriores = new QAction( "Ver Recibos Emitidos", this );
      ActRecibosAnteriores->setStatusTip( "Muestra la lista de recibos emitidos" );
      ActRecibosAnteriores->setIcon( QIcon( ":/imagenes/anteriores.png" ) );
      connect( ActRecibosAnteriores, SIGNAL( triggered() ), this, SLOT( verRecibos() ) );

      ActNuevoRecibo = new QAction( "Nuevo recibo", this );
      ActNuevoRecibo->setStatusTip( "Crea un nuevo recibo" );
      ActNuevoRecibo->setIcon( QIcon( ":/imagenes/nuevo.png" ) );
      connect( ActNuevoRecibo, SIGNAL( triggered() ), this, SLOT( nuevoRecibo() ) ); */

      ActPreferencias = new QAction ( "Configuracion" , this );
      ActPreferencias->setStatusTip( "Modifica las preferencias de la aplicacion" );
      ActPreferencias->setIcon( QIcon( ":/imagenes/configure.png" ) );
      connect( ActPreferencias, SIGNAL( triggered() ), this, SLOT( verPreferencias() ) );

      ActBackup = new QAction( "Backup", this );
      ActBackup->setStatusTip( "Genera y retaura backups del programa" );
      ActBackup->setIcon( QIcon( ":/imagenes/backup.png" ) );
      connect( ActBackup, SIGNAL( triggered() ), this, SLOT( verBackup() ) );
}

void gestotux::createMenus()
{
      fileMenu = menuBar()->addMenu( "&Archivo" );
      fileMenu->addAction( acercade );
      fileMenu->addSeparator();
      fileMenu->addAction( exitAct );

      QMenu *menuHer = menuBar()->addMenu( "&Herramientas" );
      menuHer->addAction( ActPreferencias );
      menuHer->addAction( ActBackup );
      menuHer->addSeparator();
      menuHer->addAction( ActClientes );
//       menuHer->addAction( ActRecibosAnteriores );

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
 p->inicio();
 p->beginGroup( "ventanaPrincipal" );
 p->setValue( "estado", saveState( 0 ) );
 p->endGroup();
 p->sync();
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
{
  VCliente *f = new VCliente( this );
  formCen()->addTab( f, f->objectName() );
}


/*
void gestotux::verRecibos()
{
 VRecibos *f = new VRecibos( this );
 formCen()->agregarVentana( f );
}
*/

void gestotux::createToolBar()
{
 tb = new QToolBar( "Barra de Herramientas", this );
 tb->setObjectName( "BarraPrincipal" );
 this->addToolBar( tb );
 tb->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
 tb->addActions( plugin()->accionesBarra() );
 tb->addAction( ActClientes );
//  tb->addAction( ActRecibosAnteriores );
//  tb->addAction( ActNuevoRecibo );
 tb->addAction( ActBackup );
 tb->addAction( ActPreferencias );

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


/*
void gestotux::nuevoRecibo()
{
 FormAgregarRecibo *f = new FormAgregarRecibo( formCen() );
 formCen()->agregarVentana( f );
}
*/

void gestotux::verPreferencias()
{
  FormPreferencias *p = new FormPreferencias( this );
  formCen()->addTab( p, p->objectName() );
}


void gestotux::verBackup()
{
  Ebackup *f = new Ebackup( this );
  formCen()->addTab( f, f->objectName() );
}


void gestotux::bandeja_sistema()
{
 preferencias *p = preferencias::getInstancia();
 p->inicio();
 p->beginGroup( "Preferencias" );
 p->beginGroup( "General" );
 if( p->value( "icono_bandeja" ).toBool() == true )
 {
   if( QSystemTrayIcon::isSystemTrayAvailable() )
   {
    iconoBandeja = new QSystemTrayIcon( this );
    QMenu *menu = new QMenu( this );
    menu->addAction( exitAct );
    iconoBandeja->setIcon( plugin()->iconoPrograma() );
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

     foreach( QString fileName, pluginsDir.entryList( QDir::Files ) )
     {
	loader.setFileName(  pluginsDir.absoluteFilePath( fileName )  );
         if( loader.load() )
         {
		_plugin = qobject_cast<EInfoProgramaInterface *>( loader.instance() );
		if( _plugin->inicializar( formCen() ) )
		{
			qDebug( QString( "Cargando Plugin: %1" ).arg( fileName ).toLocal8Bit() );
			return true;
		}
		else
		{
			qWarning( "Error de inicializacion en el plug in" );
			return false;
		}
	 }
	 else
	 {
		qWarning( "Error al cargar el plugin" );
		qWarning( QString( "Error: %1" ).arg( loader.errorString() ).toLocal8Bit() );
		return false;
	 }
     }
}

EInfoProgramaInterface *gestotux::plugin()
{
 if( _plugin != 0 )
 {
  return _plugin;
 }
 else
 {
  qWarning( "Llamando al plugin antes de cargarlo" );
  abort();
 }
}
