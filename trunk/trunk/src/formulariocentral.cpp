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
#include "formulariocentral.h"

#include "visorrecibo.h"
#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QPrinter>
#include <QFileDialog>
#include "gestotux.h"
#include <QToolBar>
#include <QPrintDialog>
#include "preferencias.h"

FormularioCentral::FormularioCentral( QWidget *parent )
 : QTabWidget( parent )
{
 setTabPosition( QTabWidget::North );
 setTabShape( QTabWidget::Rounded );
 setUsesScrollButtons( true );
 connect( this, SIGNAL( currentChanged( int ) ), this, SLOT( cambioWidget( int ) ) );
}


FormularioCentral::~FormularioCentral()
{
}



void FormularioCentral::agregarRecibo( visorRecibo* visor )
{
 int idret = this->addTab( visor, visor->nombre() );
 if( idret == this->currentIndex() )
 {
  emit currentChanged( idret );
 }
}


void FormularioCentral::agregarRecibo( int idDB )
{
 visorRecibo *v = new visorRecibo( this );
 v->verRecibo( idDB );
 agregarRecibo( v );
}


void FormularioCentral::cerrarActivo()
{
 gestotux::barraAcciones()->clear();
 if( this->count() != 0 )
 {
   this->removeTab( this->currentIndex() );
 }
 if( count() > 0 )
 {
  gestotux::barraAcciones()->addActions( currentWidget()->actions() );
 }
}

QString FormularioCentral::nombreActual()
{
 return this->tabText( this->currentIndex() );
}

/*!
    \fn FormularioCentral::agregarVentana( QWidget *ventana )
 */
void FormularioCentral::agregarVentana( QWidget *ventana )
{
 int idret = this->addTab( ventana, ventana->windowTitle() );
 if( idret == this->currentIndex() )
 {
  emit currentChanged( idret );
 }
 this->setCurrentIndex( idret );
}


/*!
    \fn FormularioCentral::imprimirActivo()
 */
void FormularioCentral::imprimirActivo()
{
#ifndef QT_NO_PRINTER
 QPrinter printer( QPrinter::HighResolution );
 QPrintDialog *dialog = new QPrintDialog( &printer, this );
 printer.setOrientation( QPrinter::Landscape );
 dialog->setWindowTitle( "Imprimir" );
 if ( dialog->exec() != QDialog::Accepted )
     return;
 qobject_cast<visorRecibo *>(currentWidget())->recibo()->imprimir(&printer);
#endif
}

void FormularioCentral::aPdfActivo()
{
 #ifndef QT_NO_PRINTER
     QString fileName = QFileDialog::getSaveFileName( this, "Exportar a PDF", QDir::homePath() + QDir::separator() + nombreActual(), "*.pdf");
     if (!fileName.isEmpty()) {
         if (QFileInfo(fileName).suffix().isEmpty())
             fileName.append(".pdf");
         QPrinter printer( QPrinter::HighResolution );
         printer.setOutputFormat( QPrinter::PdfFormat );
         printer.setOrientation( QPrinter::Landscape );
         printer.setOutputFileName( fileName );
         qobject_cast<visorRecibo *>(this->currentWidget())->recibo()->imprimir(&printer);
     }
 #endif
}


/*!
    \fn FormularioCentral::cambioWidget( int id )
 */
void FormularioCentral::cambioWidget( int id )
{
 gestotux::barraAcciones()->clear();
 gestotux::barraAcciones()->addActions( this->widget( id )->actions() );
}
