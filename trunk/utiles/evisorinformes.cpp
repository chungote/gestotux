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
#include "evisorinformes.h"
#include "eactcerrar.h"
#include "eactimprimir.h"

EVisorInformes::EVisorInformes(QWidget *parent)
 : QPrintPreviewWidget(parent)
{
 setAttribute( Qt::WA_DeleteOnClose );

 // Inicializo el formualrio y creo las acciones
 EActCerrar *ActCerrar = new EActCerrar( this );
 connect( ActCerrar, SIGNAL( triggered() ), this, SLOT( close() ) );
 addAction(ActCerrar);

 EActImprimir *ActImprimir = new EActImprimir( this );
 ActImprimir->setStatusTip( "Imprime el reporte actual" );
 connect( ActImprimir, SIGNAL( triggered() ), this, SLOT( print() ) );
 addAction(ActImprimir);

 QAction *ActPrimera = new QAction( this );
 ActPrimera->setIcon( QIcon( ":/imagenes/primera.png" ) );
 ActPrimera->setStatusTip( "Salta a la primer pagina" );
 connect( ActPrimera, SIGNAL( triggered() ), this, SLOT( primerPagina() ) );
 addAction( ActPrimera );

 QAction *ActAnterior = new QAction( "", this );
 ActAnterior->setIcon( QIcon( ":/imagenes/anterior.png" ) );
 ActAnterior->setStatusTip( "Salta a la pagina anterior" );
 connect( ActAnterior, SIGNAL( triggered() ), this, SLOT( anterior() ) );
 addAction( ActAnterior );

 QAction *ActSiguiente = new QAction( this );
 ActSiguiente->setIcon( QIcon( ":/imagenes/siguiente.png" ) );
 ActSiguiente->setStatusTip( "Salta a la pagina siguiente" );
 connect( ActSiguiente, SIGNAL( triggered() ), this, SLOT( siguiente() ) );
 addAction( ActSiguiente );

 QAction *ActUltima = new QAction( this );
 ActUltima->setIcon( QIcon( ":/imagenes/ultima.png" ) );
 ActUltima->setStatusTip( "Salta a la ultima hoja" );
 connect( ActUltima, SIGNAL( triggered() ), this, SLOT( ultimaPagina() ) );
 addAction( ActUltima );

 QAction *ActAgrandar = new QAction( this );
 ActAgrandar->setIcon( QIcon( ":/imagenes/agrandar.png" ) );
 ActAgrandar->setStatusTip( "Aumenta el zoom" );
 connect( ActAgrandar, SIGNAL( triggered() ), this, SLOT( zoomIn() ) );
 addAction( ActAgrandar );

 QAction *ActAchicar = new QAction( this );
 ActAchicar->setIcon( QIcon( ":/imagenes/achicar.png" ) );
 ActAchicar->setStatusTip( "Disminuye el zoom" );
 connect( ActAchicar, SIGNAL( triggered() ), this, SLOT( zoomOut() ) );
 addAction( ActAchicar );

 QAction *ActAjustarAncho = new QAction( this );
 ActAjustarAncho->setIcon( QIcon( ":/imagenes/ajustarancho.png" ) );
 ActAjustarAncho->setStatusTip( "Ajusta el zoom para que se vea todo el ancho de la hoja" );
 connect( ActAjustarAncho, SIGNAL(triggered()), this, SLOT( fitToWidth() ) );
 addAction( ActAjustarAncho );

 QAction *ActAjustarHoja = new QAction( this );
 ActAjustarHoja->setIcon( QIcon(":/imagenes/ajustarpagina.png") );
 ActAjustarHoja->setStatusTip( "Ajusta el zomm para que la hoja entre en la ventana" );
 connect( ActAjustarHoja, SIGNAL( triggered() ), this, SLOT( fitInView() ) );
 addAction( ActAjustarHoja );
}


EVisorInformes::~EVisorInformes()
{
}




/*!
    \fn EVisorInformes::primerPagina()
 */
void EVisorInformes::primerPagina()
{
 this->setCurrentPage( 1 );
}


/*!
    \fn EVisorInformes::anterior()
 */
void EVisorInformes::anterior()
{
 this->setCurrentPage( this->currentPage() - 1 );
}


/*!
    \fn EVisorInformes::ultimaPagina()
 */
void EVisorInformes::ultimaPagina()
{
 this->setCurrentPage( this->numPages() );
}


/*!
    \fn EVisorInformes::siguiente()
 */
void EVisorInformes::siguiente()
{
 this->setCurrentPage( this->currentPage() + 1 );
}
