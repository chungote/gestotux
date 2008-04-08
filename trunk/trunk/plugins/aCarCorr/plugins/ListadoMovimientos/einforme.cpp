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
#include "einforme.h"

#include <QMenu>
#include <QAction>
#include <QPrinter>
#include <QPrintDialog>

EInforme::EInforme(QWidget *parent)
 : QTextEdit(parent)
{
 // Propiedades
 this->setAcceptRichText( true );
 this->setLineWrapMode( QTextEdit::WidgetWidth );
 this->setReadOnly( true );
 this->setAttribute( Qt::WA_DeleteOnClose );
 
 // Acciones
 ActCerrar = new QAction( "Cerrar", this );
 ActCerrar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
 connect( ActCerrar, SIGNAL( triggered() ), this, SLOT( close() ) );
 
 ActImprimir = new QAction( "Imprimir", this );
 ActImprimir->setIcon( QIcon( ":/imagenes/impresora.png" ) );
 connect( ActImprimir, SIGNAL( triggered() ), this, SLOT( imprimir() ) );

 addAction( ActImprimir );
 addAction( ActCerrar );
}


EInforme::~EInforme()
{
}


QMenu* EInforme::createStandardContextMenu()
{
    QMenu *menu = QTextEdit::createStandardContextMenu();
    menu->addSeparator();
    menu->addAction( ActImprimir );
    menu->addAction( ActCerrar );
    return menu;
}



/*!
    \fn EInforme::imprimir()
 */
void EInforme::imprimir()
{
   // Veo la impresora
#ifndef QT_NO_PRINTER
 QPrinter printer( QPrinter::HighResolution );
 #ifdef QT_WS_WIN
  printer.setOutputFormat(QPrinter::NativeFormat);
 #endif
 QPrintDialog *dialog = new QPrintDialog( &printer, this );
 dialog->setWindowTitle( "Imprimir" );
 if ( dialog->exec() != QDialog::Accepted )
 { return; }
 // veo que quiere imprimir
 document()->print( &printer );
#endif
}

