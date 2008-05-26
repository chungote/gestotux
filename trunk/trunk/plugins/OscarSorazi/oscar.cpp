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
#include "oscar.h"

#include "../aCarCorr/einformeinterface.h"
#include <QSqlQuery>

// Habilita los dueños


QStackedWidget *Oscar::_formCen = 0;
QSettings *Oscar::_pref = 0;
QHash<QString, EInformeInterface *> *Oscar::_plugins = 0;


QIcon Oscar::iconoPrograma() const
{
 return QIcon();
}

QString Oscar::companeros()
{
 return "Exequiel Saavedra <gandhalf@gmail.com> \n Pruebas y graficos";
}

QString Oscar::directorioActualizaciones() const
{
 return "oscar";
}

QString Oscar::directorioBackup() const
{
 return "oscar";
}

QString Oscar::empresa() const
{
 return "Oscar Sorazi";
}

QString Oscar::nombrePrograma() const
{
 return "Oscar Sorazi";
}

QList< QAction * > Oscar::accionesBarra() const
{
  return _acciones;
}

QString Oscar::nombre() const
{
 return "oscarsoraiz";
}

QWidgetList Oscar::formsPreferencias()
{
 return QWidgetList();
}

bool Oscar::inicializar(QStackedWidget* formCen, QSettings* pref)
{
  _formCen = formCen;
 _pref = pref;
 _acciones.clear();

 ActCategoria = new QAction( "Ver Categorias", this );
 ActCategoria->setIcon( QIcon( ":/imagenes/categoria.png" ) );
 ActCategoria->setStatusTip( "Muestra el listado de categorias de caravanas" );
 ActCategoria->setToolTip( "Muestra las categorias ( Ctrl + u )" );
 ActCategoria->setShortcut( QKeySequence( "Ctrl+u" ) );
 connect( ActCategoria, SIGNAL( triggered() ), this, SLOT( verCategorias() ) );
 
 ActEstablecimiento = new QAction( "Ver Establecimientos", this );
 ActEstablecimiento->setIcon( QIcon( ":/imagenes/establecimientos.png" ) );
 ActEstablecimiento->setStatusTip( "Muestra el listado de establecimientos" );
 ActEstablecimiento->setToolTip( "Muestra los establecimientos ( Ctrl + e )" );
 ActEstablecimiento->setShortcut( QKeySequence( "Ctrl+e" ) );
 connect( ActEstablecimiento, SIGNAL( triggered() ), this, SLOT( verEstablecimientos() ) );

 ActAgregarCompra = new QAction( "Agregar compra", this );
 ActAgregarCompra->setIcon( QIcon( ":/imagenes/add.png" ) );
 ActAgregarCompra->setStatusTip( "Agrega una nueva compra" );
 ActAgregarCompra->setToolTip( "Agrega una nueva compra" );
 connect( ActAgregarCompra, SIGNAL( triggered() ), this, SLOT( agregarCompra() ) );

 ActAgregarVenta = new QAction( "Nueva venta", this );
 ActAgregarVenta->setIcon( QIcon( ":/imagenes/add.png" ) );
 ActAgregarVenta->setToolTip( "Agregar nueva venta de animales" );
 connect( ActAgregarVenta, SIGNAL( triggered() ), this, SLOT( hacerVenta() ) );

 ActAgregarMudanza = new QAction( "Nuevo Traslado", this );
 ActAgregarMudanza->setIcon( QIcon( ":/imagenes/add.png" ) );
 ActAgregarMudanza->setToolTip( "Agrega un nuevo tri de mudanza" );
 connect( ActAgregarMudanza, SIGNAL( triggered() ), this, SLOT( hacerMudanza() ) );

 ActAgregarStock = new QAction( "Ingreso x stock", this );
 ActAgregarStock->setIcon( QIcon( ":/imagenes/add.png" ) );
 ActAgregarStock->setToolTip( "Agregar Caravanas a la existencia" );
 connect( ActAgregarStock, SIGNAL( triggered() ), this, SLOT( agregarStock() ) );

 ActDuenos = new QAction( "Dueños", this );
 ActDuenos->setToolTip( "Muestra el listado de personas que estan como dueños" );
 connect( ActDuenos, SIGNAL( triggered() ), this, SLOT( mostrarDuenos() ) );

 ActModificarTri = new QAction( "Modificar Tri", this );
 ActModificarTri->setToolTip( "Permite modificar un numero especifico de tri" );
 connect( ActModificarTri, SIGNAL( triggered() ), this, SLOT( modificarTri() ) );

 _acciones.append( ActAgregarVenta );
 _acciones.append( ActAgregarCompra );
 _acciones.append( ActAgregarMudanza );
 _acciones.append( ActAgregarStock );
 _acciones.append( ActDuenos );

 cargarPluginsInformes();
 return verificarTablas();
}

bool Oscar::verificarTablas()
{
 QSqlQuery cola;
 if( !cola.exec( "SELECT count(name) FROM sqlite_master WHERE name = 'car_categorias' AND type = 'table'" ) )
 {
  qWarning( "Error al buscar la tabla car_categorias" );
  return false;
 }
 if( !cola.exec( "SELECT count(name) FROM sqlite_master WHERE name = 'car_establecimientos' AND type = 'table'" ) )
 {
  qWarning( "Error al buscar la tabla car_establecimientos" );
  return false;
 }
 if( !cola.exec( "SELECT count(name) FROM sqlite_master WHERE name = 'car_caravana' AND type = 'table'" ) )
 {
  qWarning( "Error al buscar la tabla car_caravana" );
  return false;
 }
 if( !cola.exec( "SELECT count(name) FROM sqlite_master WHERE name = 'car_caravana' AND type = 'table'" ) )
 {
  qWarning( "Error al buscar la tabla car_caravana" );
  return false;
 }
 if( !cola.exec( "SELECT count(name) FROM sqlite_master WHERE name = 'car_tri' AND type = 'table'" ) )
 {
  qWarning( "Error al buscar la tabla car_tri" );
  return false;
 }
 if( !cola.exec( "SELECT count(name) FROM sqlite_master WHERE name = 'car_carv_tri' AND type = 'table'" ) )
 {
  qWarning( "Error al buscar la tabla car_carv_tri" );
  return false;
 }
 if( !cola.exec( "SELECT count(name) FROM sqlite_master WHERE name = 'car_carv_duenos' AND type = 'table'" ) )
 {
  qWarning( "Error al buscar la tabla car_carv_tri" );
  return false;
 }
 return true;
}

double Oscar::version() const
{
 return 0.1;
}

int Oscar::tipo() const
{
 return EPlugin::info;
}

void Oscar::crearMenu(QMenuBar* m)
{
  QMenu *menuHer = m->findChild<QMenu *>( "menuHerramientas" );
 if( menuHer == 0 )
 {
  qDebug( "Error en las baras de menu" );
 }
 else
 { 
  menuHer->addAction( ActEstablecimiento );
  menuHer->addAction( ActCategoria );
  menuHer->addAction( ActDuenos );
  menuHer->addSeparator();
  menuHer->addAction( ActAgregarCompra );
  menuHer->addAction( ActAgregarMudanza );
  menuHer->addAction( ActAgregarVenta );
  menuHer->addAction( ActAgregarStock );
 }
 // Creo el menu de informes
 QMenu *menuInformes = m->addMenu( "Informes" );
 menuInformes->setObjectName( "menuInformes" );
 if( !plugins().isEmpty() )
 {
	foreach( EInformeInterface *p, plugins() )
	{
		p->crearMenu( menuInformes );
	}
 }
}

Q_EXPORT_PLUGIN2( oscarsoraiz , Oscar );

#include "../aCarCorr/vcategorias.h"
void Oscar::verCategorias()
{
 VCategorias *f = new VCategorias( _formCen );
 _formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( f ) ) );
}


#include "../aCarCorr/vestablecimiento.h"
/*!
    \fn Oscar::verEstablecimientos()
 */
void Oscar::verEstablecimientos()
{
  VEstablecimiento *f = new VEstablecimiento( _formCen );
 _formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( f ) ) );
}

#include "../aCarCorr/formagregar.h"
/*!
    \fn Oscar::agregarCompra()
 */
void Oscar::agregarCompra()
{
  FormAgregar *f = new FormAgregar( _formCen );
 _formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( f ) ) );
}

#include "../aCarCorr/formmudanza.h"
/*!
    \fn Oscar::hacerMovimiento()
 */
void Oscar::hacerMovimiento()
{
 FormMudanza *f = new FormMudanza( _formCen );
 _formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( f ) ) );
}

#include "../aCarCorr/formventa.h"
/*!
    \fn Oscar::hacerVenta()
 */
void Oscar::hacerVenta()
{
 FormVenta *f = new FormVenta( _formCen );
 _formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( f ) ) );
}


#include "../aCarCorr/formmudanza.h"
/*!
    \fn Oscar::hacerMudanza()
 */
void Oscar::hacerMudanza()
{
 FormMudanza *f = new FormMudanza( _formCen );
 _formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( f ) ) );
}


#include <QDir>
void Oscar::cargarPluginsInformes()
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
     pluginsDir.cd("informes");

	_plugins = new QHash<QString, EInformeInterface *>();
#ifdef Q_WS_WIN32
	QStringList filtro;
	filtro.append( "*.dll" );
     foreach( QString fileName, pluginsDir.entryList( filtro, QDir::Files ) )
     {
#endif
#ifdef Q_WS_X11
     foreach( QString fileName, pluginsDir.entryList( QDir::Files ) )
     {
#endif
	loader->setFileName( pluginsDir.absoluteFilePath( fileName ) );
        if( loader->load() )
        {
		EInformeInterface *plug = qobject_cast<EInformeInterface *>( loader->instance() );
		// Genero ahora el visor de informe
		if( plug->inicializar( _formCen ) )
		{
			_plugins->insert( plug->nombre(), plug );
			qDebug( QString( "Cargando Plugin: %1" ).arg( pluginsDir.absoluteFilePath( fileName )).toLocal8Bit() );
			// Registro en las preferencias el plugin
			///@todo Registrar el plugin en las preferencias
		}
		else
		{
			qWarning( QString( "Error de inicializacion en el plug in %1" ).arg( plug->nombre() ).toLocal8Bit() );
		}
	}
	else
	{
		qWarning( QString( "Error al cargar el plugin. Error: %1" ).arg( loader->errorString() ).toLocal8Bit() );
	}
	// Fin de la carga del plugin
  }
}


/*!
    \fn Oscar::plugins()
 */
QList<EInformeInterface *> Oscar::plugins()
{
 if( _plugins == 0 )
 {
  QList<EInformeInterface *> lista;
  return lista;
 }
 else
 {
  return _plugins->values();
 }
}


#include "vduenos.h"
void Oscar::mostrarDuenos()
{
 VDuenos *f = new VDuenos( _formCen );
 _formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( f ) ) );
}

#include "../aCarCorr/formstock.h"
void Oscar::agregarStock()
{
 FormStock *f = new FormStock( _formCen );
 _formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( f ) ) );
}


#include <QSqlRecord>
#include <QInputDialog>
#include "../aCarCorr/formmodificartri.h"
void Oscar::modificarTri()
{
 // Pregunto que numero de tri quiere modificar
 bool ok;
 QStringList lista;
 QSqlQuery cola( "SELECT id_tri FROM car_tri" );
 while( cola.next() )
 {
  lista.append( cola.record().value(0).toString() );
 }
 QString id_tri = QInputDialog::getItem( 0, tr("Elija el tri"), tr("# Tri :"), lista, 0, false, &ok );
 if( !id_tri.isNull() && ok )
 {
  // Cargo el formulario con el tri que corresponda
  if( cola.exec( QString( "SELECT razon FROM car_tri WHERE id_tri = '%1'" ).arg( id_tri ) ) )
  {
   FormModificarTri *f = new FormModificarTri( _formCen, cola.record().value(0).toInt(), id_tri.toInt() );
   _formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( f ) ) );
   return;
  }
 }
 else
 {
  return;
 }
}
