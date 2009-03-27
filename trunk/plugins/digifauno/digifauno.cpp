/***************************************************************************
 *   Copyright (C) 2006 by Esteban Zeller & Daniel Sequeira		   *
 *   juiraze@yahoo.com.ar  - daniels@hotmail.com			   *
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

#include <QSqlDatabase>
#include "digifauno.h"
#include "preferencias.h"
#include "vduenos.h"
#include "formagregarmasctoa.h"
#include "formagregarservicio.h"
#include "vmascota.h"
#include "eresumen.h"
#include "formlistapeluqueria.h"

/*!
    \fn DigiFauno::duenos()
 */
void DigiFauno::duenos()
{ emit agregarVentana( new VDuenos() ); }

/*!
    \fn DigiFauno::agregarMascota()
 */
void DigiFauno::agregarMascota()
{ emit agregarVentana( new FormAgregarMascota() ); }


/*!
    \fn DigiFauno::agregarServicioPeluqueria()
 */
void DigiFauno::agregarServicioPeluqueria()
{  emit agregarVentana( new FormAgregarServicio() ); }


/*!
    \fn DigiFauno::mascotas()
 */
void DigiFauno::mascotas()
{ emit agregarVentana( new VMascota() ); }


/*!
    \fn DigiFauno::resumenDiario()
 */
void DigiFauno::resumenDiario()
{ emit agregarVentana( new EResumen( 0, EResumen::diario ) ); }


/*!
    \fn DigiFauno::resumenMensual()
 */
void DigiFauno::resumenMensual()
{ emit agregarVentana( new EResumen( 0, EResumen::mensual ) );  }


/*!
    \fn DigiFauno::resumenAnual()
 */
void DigiFauno::resumenAnual()
{ emit agregarVentana( new EResumen( 0, EResumen::anual ) ); }


/*!
    \fn DigiFauno::resumen_semanal()
 */
void DigiFauno::resumen_semanal()
{ emit agregarVentana( new EResumen( 0, EResumen::semanal ) ); }

/*!
    \fn DigiFauno::ver_peluqueria()
 */
void DigiFauno::ver_peluqueria()
{ emit agregarVentana( new FormListaPeluqueria() ); }

/*!
    \fn DigiFauno::nombre() const
 */
QString DigiFauno::nombre() const
{ return "digifauno"; }


/*!
    \fn DigiFauno::version() const
 */
double DigiFauno::version() const
{ return 0.4; }


/*!
    \fn DigiFauno::inicializar()
 */
bool DigiFauno::inicializar()
{
 Q_INIT_RESOURCE(embebido);
 _acciones.clear();
 // Acciones estandar
 ////////////////////////////////
 // Muestra los miembros
 ////////////////////////////////
 ActDuenos = new QAction( "Dueños", this );
 ActDuenos->setStatusTip( "Muestra todos los dueños" );
 ActDuenos->setIcon( QIcon( ":/imagenes/duenos.png" ) );
 connect( ActDuenos, SIGNAL( triggered() ), this, SLOT( duenos() ) );
 /////////////////////////////////////////////
 // Muestra el formulario de agregar mascotas
 /////////////////////////////////////////////
 ActAgregarMascota = new QAction( "Agregar Mascota", this );
 ActAgregarMascota->setStatusTip( "Agrega una nueva mascota" );
 connect( ActAgregarMascota, SIGNAL( triggered() ), this, SLOT( agregarMascota() ) );
 /////////////////////////////////////
 // Muestra la lista de mascotas
 /////////////////////////////////////
 ActMascotas = new QAction( "Ver Mascotas", this );
 ActMascotas->setStatusTip( "Ver todas las mascotas y sus dueños" );
 ActMascotas->setIcon( QIcon( ":/imagenes/mascotas.gif" ) );
 connect( ActMascotas, SIGNAL( triggered() ), this, SLOT( mascotas() ) );
 /////////////////////////////////////
 // Muestra los servicios de peluqueria
 /////////////////////////////////////
 ActPeluqueria = new QAction( "Servicios", this );
 ActPeluqueria->setIcon( QIcon( ":/imagenes/pelu.gif" ) );
 ActPeluqueria->setStatusTip( "Muestra todos los servicios prestados" );
 connect( ActPeluqueria, SIGNAL( triggered() ), this, SLOT( ver_peluqueria() ) );

 ActNuevoServicio = new QAction( "Agregar Nueva Servicio", this );
 ActNuevoServicio->setIcon( QIcon( ":/imagenes/pelu.gif" ) );
 connect( ActNuevoServicio, SIGNAL( triggered() ), this, SLOT( agregarServicioPeluqueria() ) );

 ActResumenDiario = new QAction( "Resumen Diario", this );
 ActResumenDiario->setIcon( QIcon(":/imagenes/diario.png" ) );
 connect( ActResumenDiario, SIGNAL( triggered() ), this, SLOT( resumenDiario() ) );

 ActResumenMensual = new QAction( "Resumen Mensual", this );
 ActResumenMensual->setIcon( QIcon( ":/imagenes/semanal.png" ) );
 connect( ActResumenMensual, SIGNAL( triggered() ), this, SLOT( resumenMensual() ) );

 ActResumenAnual = new QAction( "Resumen Anual", this );
 connect( ActResumenAnual, SIGNAL( triggered() ), this, SLOT( resumenAnual() ) );

 ActResumenEntreFechas = new QAction( "Resumen entre fechas ", this );
 ActResumenEntreFechas->setStatusTip( "Realiza un resumen entre fechas" );
 connect( ActResumenEntreFechas, SIGNAL( triggered() ), this, SLOT( resumenEntreFechas() ) );

 return true;
}


/*!
    \fn DigiFauno::verificarTablas()
 */
bool DigiFauno::verificarTablas()
{
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "mascota" ) )
 { qWarning( "Error al buscar la tabla mascota" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "dueno" ) )
 { qWarning( "Error al buscar la tabla dueno" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "peluqueria" ) )
 { qWarning( "Error al buscar la tabla peluqueria" ); return false; }
 return true;
}

#include <QActionGroup>
/*!
    \fn DigiFauno::accionesBarra()
 */
QList<QActionGroup *> DigiFauno::accionesBarra()
{
 QList<QActionGroup *> lista;
 /////////////////////////////////////////////////////////////
 // Peluqueria
 peluqueria = new QActionGroup( this );
 peluqueria->setObjectName( "peluqueria" );
 peluqueria->setProperty( "icono", ":/imagenes/pelu.gif" );
 peluqueria->setProperty( "titulo", "Peluqueria Canina" );
 peluqueria->addAction( ActNuevoServicio );
 peluqueria->addAction( ActAgregarMascota );
 peluqueria->addAction( ActMascotas );
 peluqueria->addAction( ActDuenos );
 lista.append( peluqueria );
 //////////////////////////////////////////////////////////////
 // Resumenes
 resumen = new QActionGroup( this );
 resumen->setObjectName( "resumen" );
 resumen->setProperty( "icono", ":/imagenes/resumenes.png" );
 resumen->setProperty( "titulo", "Resumenes" );
 resumen->addAction( ActResumenDiario );
 resumen->addAction( ActResumenMensual );
 resumen->addAction( ActResumenAnual );
 resumen->addAction( ActResumenEntreFechas );
 lista.append( resumen );

 return lista;
}


/*!
    \fn DigiFauno::directorioActualizaciones() const
 */
QString DigiFauno::directorioActualizaciones() const
{ return "digifauno"; }


/*!
    \fn DigiFauno::directorioBackup() const

 */
QString DigiFauno::directorioBackup() const
{ return "digifauno"; }


/*!
    \fn DigiFauno::nombrePrograma() const
	Devuelve el nombre del programa
	@return Nombre del programa
 */
QString DigiFauno::nombrePrograma() const
{  return "Digifauno  -  " + QString::number( version() ); }


#include "formprefopciones.h"
/*!
    \fn DigiFauno::formsPreferencias()
	Devuleve la lista de formularios de configuración para el programa
	@return QWidgetList con los formularios
 */
QWidgetList DigiFauno::formsPreferencias()
{
  QWidgetList lista;
  lista.append( new FormPrefOpciones() );
  return lista;
}


/*!
    \fn DigiFauno::crearMenu( QMenuBar* m )
	Agrega las acciones al menu del programa
	@param m Barra del menu principal
 */
void DigiFauno::crearMenu( QMenuBar* m )
{
QMenu *menuHerramientas = m->findChild<QMenu *>( "menuHerramientas" );
 if( menuHerramientas == 0 )
 {
  qDebug( "Error en las baras de menu" );
 }
 else
 {
  menuHerramientas->addAction( ActDuenos );
  menuHerramientas->addAction( ActMascotas );
  menuHerramientas->addAction( ActPeluqueria );
 }
}


/*!
    \fn DigiFauno::iconoPrograma() const
	Devuelve el icono del programa
	@return Icono del programa
 */
QIcon DigiFauno::iconoPrograma() const
{ return QIcon( ":/imagenes/icono.png" ); }


/*!
    \fn DigiFauno::empresa() const
	Devuelve el nombre de la empresa qu a  la que fue realizado el programa
	@return Nombre de la empresa
 */
QString DigiFauno::empresa() const
{ return "Veterinaria \"El Fauno\""; }


/*!
    \fn DigiFauno::companeros()
	Devuelve el socio que trabajo conmigo
	@return Nombre del socio
 */
QString DigiFauno::companeros()
{ return "Daniel Sequeira"; }


/*!
    \fn DigiFauno::tipo() const
	Devuelve el tipo de plugin que es EPlugin::info
 	@return EPlugin::info
 */
int DigiFauno::tipo() const
{ return EPlugin::info; }

Q_EXPORT_PLUGIN2( adigifauno, DigiFauno );


/*!
    \fn DigiFauno::crearToolBar()
 */
void DigiFauno::crearToolBar( QToolBar *t )
{  t->addActions( _acciones ); }


/*!
    \fn DigiFauno::resumenEntreFechas()
        Muestra el formulario de crear resumenes entre fechas
 */
void DigiFauno::resumenEntreFechas()
{ emit agregarVentana( new EResumen( 0, EResumen::entrefechas ) ); }

/*!
    \fn DigiFauno::seCierraGestotux()
 */
void DigiFauno::seCierraGestotux()
{
 Q_CLEANUP_RESOURCE(embebido);
}
