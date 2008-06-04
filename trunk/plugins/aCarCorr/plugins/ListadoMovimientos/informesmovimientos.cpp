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
#include "informesmovimientos.h"

#include <QAction>
#include <QMenu>
#include "formfiltro.h"
#include <QStackedWidget>
#include "erenderizadorinforme.h"
#include "einforme.h"

#include "../../../../utiles/evisorinformes.h"

QString InformesMovimientos::nombre() const
{
 return "informesMovimientos";
}

bool InformesMovimientos::inicializar()
{

 ActInformeFiltroTotal = new QAction( "Personalizado...", this );
 connect( ActInformeFiltroTotal, SIGNAL( triggered() ), this, SLOT( informeCompleto() ) );

 cargarArchivoEstilo();

 return true;
}

double InformesMovimientos::version() const
{
 return 0.1;
}

void InformesMovimientos::crearMenu(QMenu* m)
{
 m->addAction( ActInformeFiltroTotal );
}

Q_EXPORT_PLUGIN2(movimientos, InformesMovimientos );


/*!
    \fn InformesMovimientos::informeCompleto()
	Genera el fomulario de filtro y genera el visor de informes y el informe
 */
void InformesMovimientos::informeCompleto()
{
 FormFiltro *f = new FormFiltro();
 if( f->exec() == QDialog::Accepted )
 {
	// Genero un nuevo informe
	EVisorInformes *fa = new EVisorInformes();
	// Genero los contenidos del informe
	ERenderizadorInforme *render = new ERenderizadorInforme( this );
	render->setPropiedades( f );
	// lo muestro
	render->documento()->setDefaultStyleSheet( _estilo );
	render->hacerInforme();
	connect( fa, SIGNAL( paintRequested ( QPrinter * ) ), render, SLOT( imprimir( QPrinter * ) ) );
	render->cerrarDialogo();
	emit agregarVentana( fa );
 }
}


/*!
    \fn InformesMovimientos::cargarArchivoEstilo()
	Carga la hoja CSS de estilo. Primero busca en la carpeta plugins/informes/estilo.css y si no lo encuentra utiliza la hoja de estilo embebida
 */
void InformesMovimientos::cargarArchivoEstilo()
{
 QString nombre;
 if( QFile::exists( QApplication::applicationFilePath() + "/plugins/informes/estilo.css" ) )
 {
  nombre = QApplication::applicationFilePath() + "/plugins/informes/estilo.css";
 }
 else
 {
  nombre = ":/informes/estlioinforme.css";
 }
 archivoEstilo = new QFile( nombre );
 if( !archivoEstilo->open( QIODevice::ReadOnly ) )
 {
  qDebug( "Error al abrir el archivo de estilo" );
  return;
 }
 _estilo = archivoEstilo->readAll();
 archivoEstilo->close();
 delete( archivoEstilo );
 archivoEstilo = 0;
}
