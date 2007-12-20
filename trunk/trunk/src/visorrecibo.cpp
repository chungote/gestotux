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
#include "visorrecibo.h"
#include "gestotux.h"

visorRecibo::visorRecibo(QWidget *parent)
 : QSvgWidget( parent )
{
 rec = new Recibo( this );

 ActImprimir = new QAction( "Imprimir", this );
 ActImprimir->setIcon( QIcon( ":/imagenes/impresora.png" ) );
 ActImprimir->setStatusTip( "Imprime el recibo actual" );
 connect( ActImprimir, SIGNAL( triggered() ), gestotux::formCen(), SLOT( imprimirActivo() ) );

 ActCerrar = new QAction( "Cerrar", this );
 ActCerrar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
 ActCerrar->setStatusTip( "Cierra esta ventana" );
 connect( ActCerrar, SIGNAL( triggered() ), gestotux::formCen(), SLOT( cerrarActivo() ) );

 ActPdf = new QAction( "Guardar a PDF", this );
 ActPdf->setStatusTip( "Guarda el contenido de la pestaña actual a un archivo pdf" );
 ActPdf->setIcon( QIcon( ":/imagenes/acroread.png" ) );
 connect( ActPdf, SIGNAL( triggered() ), gestotux::formCen(), SLOT( aPdfActivo() ) );

 addAction( ActCerrar );
 addAction( ActPdf );
 addAction( ActImprimir );
}


visorRecibo::~visorRecibo()
{
}


QString visorRecibo::nombre()
{
 if( rec == 0 )
 {
  return "Desconocido";
 }
 else
 {
  return rec->titulo();
 }
}


/*!
    \fn visorRecibo::recibo()
 */
Recibo * visorRecibo::recibo()
{
  return rec;
}


/*!
    \fn visorRecibo::verRecibo( int idDB )
 */
void visorRecibo::verRecibo( int idDB )
{
  rec->cargarRegistro( idDB );
  load( rec->obtenerByteArray() );
}

