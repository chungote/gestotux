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
#include "evisorinforme.h"

QStackedWidget *EVisorInforme::_formCen = 0;
QSettings *EVisorInforme::_pref = 0;


QList< QAction * > EVisorInforme::accionesBarra() const
{
 return QList<QAction*>();
}

QString EVisorInforme::nombre() const
{
 return "visorInformes";
}

QWidgetList EVisorInforme::formsPreferencias()
{
 ///@todo Hacer formulario de preferencias
}

bool EVisorInforme::inicializar(QStackedWidget* formCen, QSettings* pref)
{
 _formCen = formCen;
 _pref = pref;
 // Cargo el plugin pero no muestro nada hasta que no sea necesario
 
 // Inicializo las acciones para el menu
 ActAgrandarZoom = new QAction( "Aumentar", this );
 ActAgrandarZoom->setIcon( QIcon( ":/imagenes/agrandar.png" ) );
 ActAgrandarZoom->setStatusTip( "Aumenta la cantidad de zoom" );

 ActDisminuirZoom = new QAction( "Achicar", this );
 ActDisminuirZoom->setIcon( QIcon( ":/imagenes/achicar.png" ) );
 ActDisminuirZoom->setStatusTip( "Disminuye la cantidad de zoom" );

 ActImprimir = new QAction( "Imprimir", this );
 ActImprimir->setIcon( QIcon( ":/imagenes/imprimir.png" ) );
 ActImprimir->setStatusTip( "Imprime el documento actual" );

 ActAjustarAVista = new QAction( "Ajustar a la vista" , this );
 ActAjustarAVista->setIcon( QIcon( ":/imagenes/ajustar.png" ) );
 ActAjustarAVista->setStatusTip( "Ajusta la vista para el ancho de la ventana" );

 ActAjustarAAncho = new QAction( "Ajustar al ancho", this );
 ActAjustarAAncho->setIcon( QIcon( ":/imagenes/ajustarancho.png" ) );
 ActAjustarAAncho->setStatusTip( "Ajusta el zoom al ancho de la pagina" ); 

 return true;
}

bool EVisorInforme::verificarTablas()
{
 return true;
}

double EVisorInforme::version() const
{
 return 0.1;
}

int EVisorInforme::tipo() const
{
 return EPlugin::comun;
}

void EVisorInforme::crearMenu(QMenuBar* m)
{
 _menu = m->addMenu( "Ver" );
 _menu->addAction( ActAjustarAVista );
 _menu->addAction( ActAjustarAAncho );
 _menu->addSeparator();
 _menu->addAction( ActAgrandarZoom );
 _menu->addAction( ActDisminuirZoom );
 _menu->setVisible( false );
 return;
}

QStackedWidget *EVisorInforme::tabs()
{
 return _formCen;
}

QSettings *EVisorInforme::pref()
{
 return _pref;
}


#include <QPrinter>
#include <QPrintPreviewWidget>

/*!
    \fn EVisorInforme::crearVisor()
 */
QPrinter * EVisorInforme::crearVisor()
{
 // Creo la impresora con las propiedades definidas en la configuracion
 QPrinter *impresora = new QPrinter();
 if( _pref->value( "informes/orientacion", QPrinter::Portrait ) == QPrinter::Portrait )
 { impresora->setOrientation( QPrinter::Portrait ); }
 else
 { impresora->setOrientation( QPrinter::Landscape ); }
 //impresora->setPageSize( _pref->value( "informes/tam", QPrinter::A4 ) );
 impresora->setFullPage( _pref->value( "informes/completo", true ).toBool() );
 formulario = new QPrintPreviewWidget( impresora, _formCen );
 // Conecto las señales de los menus al formulario 
 connect( ActAgrandarZoom, SIGNAL( triggered() ), formulario, SLOT( zoomIn() ) );
 connect( ActDisminuirZoom, SIGNAL( triggered() ), formulario, SLOT( zoomOut() ) );
 connect( ActAjustarAAncho, SIGNAL( triggered() ), formulario, SLOT( fitToWidth() ) );
 connect( ActAjustarAVista, SIGNAL( triggered() ), formulario, SLOT( fitToView() ) );
 _formCen->setCurrentWidget( _formCen->widget( _formCen->addWidget( formulario ) ) );
 _menu->setVisible( true );
 return impresora;
}

Q_EXPORT_PLUGIN2( einforme, EVisorInforme );
