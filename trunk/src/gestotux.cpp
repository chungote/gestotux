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
#include "version.h"
#include "eemail.h"
#include "einterfazemail.h"
#include "eregistroplugins.h"
#include "FormPantallaInicial.h"


FormularioCentral *gestotux::formCentral = 0;
QToolBar *gestotux::_barraAcciones = 0;

gestotux::gestotux()
{
 // Eliminarse al cerarse
 this->setAttribute( Qt::WA_DeleteOnClose );
 setObjectName( "VentanaPrincipal" );
}

void gestotux::inicializar()
{
 setCentralWidget( formCen() );

 createActions();
 createToolBar();
 createStatusBar();
 crearReloj();
 crearBarraLateral();
 bandeja_sistema();
 createMenus();
 crearPantallaInicio();

 if( ERegistroPlugins::getInstancia()->pluginEmail() != 0 )
 {
  statusBar()->addPermanentWidget( ERegistroPlugins::getInstancia()->pluginEmail()->statusBarWidget(), -1 );
  EEmail::instancia()->testear();
 }

 setWindowIcon( ERegistroPlugins::pluginInfo()->iconoPrograma() );
 setWindowTitle( ERegistroPlugins::pluginInfo()->nombrePrograma() );

 this->restoreState( preferencias::getInstancia()->value( "Ventanas/Principal/estado" ).toByteArray() );
 this->restoreGeometry( preferencias::getInstancia()->value( "Ventanas/Principal/geometry" ).toByteArray() );
 if( preferencias::getInstancia()->value( "Preferencias/General/maximizado" ).toBool() )
 { this->showMaximized(); }
}

void gestotux::closeEvent( QCloseEvent *event )
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

      ActAyuda = new QAction( "Ayuda", this );
      ActAyuda->setStatusTip( "Muestra la ayuda del programa " );
      ActAyuda->setIcon( QIcon( ":/imagenes/ayuda.png" ) );
      connect( ActAyuda, SIGNAL( triggered() ), this, SLOT( ayuda() ) );

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

        ActRestaurar = new QAction( "Restaurar", this );
        connect( ActRestaurar, SIGNAL( triggered() ), this, SLOT( ocultar_mostrar() ) );
}

/*!
 * @fn gestotux::createMenus()
 * Genera el menu general de la aplicacion, con las acciones predefinidas y agrega los menus que coloque cada plugin.
 */
void gestotux::createMenus()
{
 fileMenu = menuBar()->addMenu( "&Archivo" );
 fileMenu->setObjectName( "menuArchivo" );
 fileMenu->addAction( ActBackup );
 fileMenu->addAction( ActPreferencias );
 fileMenu->addSeparator();
 fileMenu->addAction( ActActualizar );
 fileMenu->addSeparator();
 fileMenu->addAction( exitAct );

 menuHer = menuBar()->addMenu( "&Herramientas" );
 menuHer->setObjectName( "menuHerramientas" );
 menuHer->addAction( ActClientes );

 foreach( EPlugin *plug , ERegistroPlugins::plugins() )
 {
  qDebug( QString("Creando menu de %1" ).arg( plug->nombre() ).toLocal8Bit() );
  plug->crearMenu( menuBar() );
 }

 menuVer = menuBar()->addMenu( "&Ver");
 if( !this->findChildren<QDockWidget*>().isEmpty() )
 {
  QList<QDockWidget*> lista = this->findChildren<QDockWidget*>();
  QDockWidget *dock;
  foreach( dock, lista )
  {
   menuVer->addAction( dock->toggleViewAction() ); ///\todo Revisar actualizacion de este menu
  }
 }

 menuAyuda = menuBar()->addMenu( "A&yuda" );
 menuAyuda->setObjectName( "menuAyuda" );
 menuAyuda->addAction( ActAyuda );
 menuAyuda->addAction( acercade );
}

#include "everificabackup.h"
/*!
 * @fn gestotux::createStatusBar()
 * Genera la barra de estado y agrega el formulario de verificacion de backup.
 */
void gestotux::createStatusBar()
{
      statusBar()->showMessage( "Listo" );
        // Coloco el boton de verificacion  en la barra de tareas para que aparezca el icono de aviso de backup
        EVerificaBackup *e = new EVerificaBackup( statusBar() );
        connect( e, SIGNAL( abrirBackups() ), this, SLOT( verBackup() ) );
        statusBar()->addPermanentWidget( e );
}

gestotux::~gestotux()
{
    // Cierro la base de datos
    QSqlDatabase::database().close();
    QSqlDatabase::removeDatabase( QSqlDatabase::database().connectionName() );
}

/*!
    \fn gestotux::salir()
    Guarda la configuracion general y de la ventana y cierra la base de datos
 */
void gestotux::salir()
{
 // Envio señal de que salgo para los plugins que estan escuchando
 emit saliendoGestotux();
 preferencias::getInstancia()->setValue( "Ventanas/Principal/estado", this->saveState( 1 ) );
 preferencias::getInstancia()->setValue( "Ventanas/Principal/geometry", this->geometry() );
 // Guardo el estado de la ventana principal y sincronizo las preferencias para que queden guardas efectivamente
 preferencias::getInstancia()->sync();
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
    \fn gestotux::acerca()
    Muestra la ventana de Acerca de...
 */
void gestotux::acerca()
{
 FormAcercaDe *f = new FormAcercaDe( 0 );
 f->adjustSize();
 f->show();
}


/*!
    \fn gestotux::verClientes()
    Muestra la ventana de clientes
 */
void gestotux::verClientes()
{ formCen()->agregarForm( new VCliente( this ) ); }

/*!
 * @fn gestotux::createToolBar()
 * Genera la barra de herramientas del programa y llama a las funciones de cada plugin para que devuelvan las barra de herramientas suyas
 */
void gestotux::createToolBar()
{
 tb = new QToolBar( "Barra de Herramientas", this );
 tb->setObjectName( "BarraPrincipal" );
 this->addToolBar( tb );
 //tb->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
 foreach( EPlugin *plug , ERegistroPlugins::plugins() )
 {
  plug->crearToolBar( tb );
 }
 tb->addAction( ActClientes );

 _barraAcciones = new QToolBar( "Acciones", this );
 _barraAcciones->setObjectName( "BarraAcciones" );
 this->addToolBar( Qt::RightToolBarArea, _barraAcciones );
 _barraAcciones->setToolButtonStyle( Qt::ToolButtonTextBesideIcon );
 _barraAcciones->setAllowedAreas( Qt::RightToolBarArea | Qt::TopToolBarArea | Qt::BottomToolBarArea );
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

#include <QWebView>

/*!
    \fn gestotux::crearReloj()
    Crea el reloj digital si esta configurado y coloca la publicidad de ser necesario.
 */
void gestotux::crearReloj()
{
 //preferencias::getInstancia()->inicio();
 if( preferencias::getInstancia()->value( "Preferencias/General/reloj", false ).toBool() )
 {
         QDockWidget *dw = new QDockWidget( "Reloj" , this );
         dw->setObjectName( "reloj" );
         dw->setAllowedAreas( Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
         addDockWidget( Qt::LeftDockWidgetArea, dw );
         Reloj *r = new Reloj( dw );
         dw->setWidget( r );
 }
 if( ERegistroPlugins::pluginInfo()->publicidad() )
 {
         QDockWidget *dp = new QDockWidget( "Publicidad", this );
         dp->setObjectName( "publicidad" );
         dp->setAllowedAreas( Qt::BottomDockWidgetArea );
         dp->setFeatures( QDockWidget::NoDockWidgetFeatures );
         addDockWidget( Qt::BottomDockWidgetArea, dp );
         QWebView *vista = new QWebView( dp );
         vista->load( QUrl( "http://tranfuga.no-ip.org/publicidad.html" ) );
         dp->setFixedHeight( 140 );
         vista->show();
         dp->setWidget( vista );
 }
}

/*!
  \fn gestotux::verPreferencias()
  Slot llamado cuando se desea ver la ventana de preferencias
*/
void gestotux::verPreferencias()
{ formCen()->agregarForm( new FormPreferencias( this ) ); }


/*!
  \fn gestotux::verBackup()
  Slot llamado cuando se desea ver la ventana de backups
*/
void gestotux::verBackup()
{ formCen()->agregarForm( new Ebackup( this ) ); }

/*!
  \fn gestotux::bandeja_sistema()
  Funcion que genera el icono y sus sistemas de soporte de la bandeja del sistema.
*/
void gestotux::bandeja_sistema()
{
 if( preferencias::getInstancia()->value( "Preferencias/General/icono_bandeja", false ).toBool() )
 {
   if( QSystemTrayIcon::isSystemTrayAvailable() )
   {
    iconoBandeja = new QSystemTrayIcon( this );
    QMenu *menu = new QMenu( this );
    menu->addAction( ActPreferencias );
    menu->addAction( ActBackup );
    //menu->addAction( ActActualizar );
    menu->addSeparator();
    menu->addAction( ActAyuda );
    menu->addAction( acercade );
    menu->addSeparator();
    menu->addAction( ActRestaurar );
    menu->addAction( exitAct );
    iconoBandeja->setIcon( ERegistroPlugins::pluginInfo()->iconoPrograma() );
    iconoBandeja->setToolTip( this->windowTitle() + " - Gestotux 0.5b" );
    iconoBandeja->show();
    iconoBandeja->setContextMenu( menu );
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

/*!
    \fn gestotux::ocultar_mostrar( QSystemTrayIcon::ActivationReason razon )
    Funcion que es llamada cada vez que se interactua con el icono del sistema.
    @param razon Razon por la cual se genero el evento.
*/
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
   break;
  }
  default:
  { break; }
 }
}


/*!
    \fn gestotux::verActualizacion()
    Slot llamado para mostrar la ventana de actualizaciones.
 */
void gestotux::verActualizacion()
{ formCen()->agregarForm( new FormActualizacion( formCen() ) ); }

#include "eayuda.h"
/*!
 * @fn gestotux::keyPressEvent( QKeyEvent *event )
 * Slot llamado cuando se presiona una tecla en el programa. Si es F1 llama a la ayuda.
 */
void gestotux::keyPressEvent( QKeyEvent *event )
{
 if (  event->key() ==  Qt::Key_F1 )
 {
   // si el pedido llego hasta aca, no hay ninguna ventana abierta???? muestro el indice
   EAyuda *ayuda = EAyuda::instancia();
   ayuda->mostrarIndice();
 }
 else
 { QWidget::keyPressEvent( event ); }
}



/*!
    \fn gestotux::ayuda()
    Slot que es llamado cada vez que se solicita la ayuda. Abre la ventana y muestra el indice.
 */
void gestotux::ayuda()
{
 EAyuda *a = EAyuda::instancia();
 a->mostrarIndice();
}

#include "barralateral.h"
/*!
    \fn gestotux::crearBarraLateral()
    Funcion que crea la barra lateral que contiene los iconos de acceso directo a acciones mas usadas
 */
void gestotux::crearBarraLateral()
{
 BarraLateral *r = new BarraLateral( "Barra Lateral", this );
 addDockWidget( Qt::LeftDockWidgetArea, r );
}


/*!
   \fn gestotux::agregarDock( Qt::DockWidgetArea area, QDockWidget *ventana )
       Metodo que es llamado cuando un plugin desea agregar una ventna tipo Dock en una posicion.
       @param area Area donde se desea colocar la ventana ( Qt::DockWidgetArea )
       @param ventana Ventana que se desea agregar
*/
void gestotux::agregarDock( Qt::DockWidgetArea area, QDockWidget *ventana )
{
    ventana->setParent( this );
    this->addDockWidget( area, ventana );
}

/*!
   \fn gestotux::crearPantallaInicio()
       Metodo llamado para crear la pantalla inicial
*/
void gestotux::crearPantallaInicio()
{
    formCen()->agregarForm( new FormPantallaInicial() );
}
