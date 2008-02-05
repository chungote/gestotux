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
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>

visorRecibo::visorRecibo(QWidget *parent)
 : QSvgWidget( parent )
{
 this->setAttribute(  Qt::WA_DeleteOnClose );
 rec = new Recibo( this );

 ActImprimir = new QAction( "Imprimir", this );
 ActImprimir->setIcon( QIcon( ":/imagenes/impresora.png" ) );
 ActImprimir->setStatusTip( "Imprime el recibo actual" );
 connect( ActImprimir, SIGNAL( triggered() ), this, SLOT( imprimir() ) );

 ActCerrar = new QAction( "Cerrar", this );
 ActCerrar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
 ActCerrar->setStatusTip( "Cierra esta ventana" );
 connect( ActCerrar, SIGNAL( triggered() ), this, SLOT( close() ) );

 ActPdf = new QAction( "Guardar a PDF", this );
 ActPdf->setStatusTip( "Guarda el contenido de la pestaña actual a un archivo pdf" );
 ActPdf->setIcon( QIcon( ":/imagenes/acroread.png" ) );
 connect( ActPdf, SIGNAL( triggered() ), this, SLOT( aPdf() ) );

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



/*!
    \fn visorRecibo::imprimir()
 */
void visorRecibo::imprimir()
{
 #ifndef QT_NO_PRINTER
 QPrinter printer( QPrinter::HighResolution );
 #ifdef QT_WS_WIN
  printer.setOutputFormat(QPrinter::NativeFormat);
 #endif
 printer.setOrientation( QPrinter::Landscape );
 QPrintDialog *dialog = new QPrintDialog( &printer, this );
 dialog->setWindowTitle( "Imprimir" );
 if ( dialog->exec() != QDialog::Accepted )
 { return; }
 
 QPainter pintor;
 pintor.begin( &printer );
 rec->imprimir( &pintor );
 pintor.end();
#endif
}


/*!
    \fn visorRecibo::aPdf()
 */
void visorRecibo::aPdf()
{
 #ifndef QT_NO_PRINTER
     QString fileName = QFileDialog::getSaveFileName( this, "Exportar a PDF",
			 QDir::homePath() +
			 QDir::separator() +
			 rec->titulo(),
			 "*.pdf");
     if (!fileName.isEmpty()) {
         if (QFileInfo(fileName).suffix().isEmpty())
             fileName.append(".pdf");
         QPrinter printer( QPrinter::HighResolution );
         printer.setOutputFormat( QPrinter::PdfFormat );
         printer.setOrientation( QPrinter::Landscape );
         printer.setOutputFileName( fileName );

	 // seteo el pintador
 	 QPainter pintador;
	 pintador.begin( &printer );
         rec->imprimir( &pintador );
	 pintador.end();
     }
 #endif
}
