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
#include "edsbprecio.h"

#include <QLatin1Char>
#include <QKeyEvent>

EDSBPrecio::EDSBPrecio(QWidget *parent)
 : QDoubleSpinBox( parent )
{
 setPrefix( "$ " );
}


EDSBPrecio::~EDSBPrecio()
{
}

/*!
    \fn EDSBPrecio::keyReleaseEvent ( QKeyEvent * event )
 */
void EDSBPrecio::keyReleaseEvent( QKeyEvent * event )
{
 switch( event->key() )
 {
   qDebug( QString( "Tecla: %1, texto: %2" ).arg( event->key() ).arg( event->text()).toLocal8Bit() );
     case Qt::Key_0:
     case Qt::Key_1:
     case Qt::Key_2:
     case Qt::Key_3:
     case Qt::Key_4:
     case Qt::Key_5:
     case Qt::Key_6:
     case Qt::Key_7:
     case Qt::Key_8:
     case Qt::Key_9:
     case Qt::Key_Comma:
     case Qt::Key_Period:
     {
       QString valor_anterior = QDoubleSpinBox::text();
       if( event->key() == Qt::Key_Comma || event->key() == Qt::Key_Period )
       {
        valor_anterior.append( "." );
       }
       else
       {
        valor_anterior.append( event->text() );
       }
       QDoubleSpinBox::valueFromText( valor_anterior );
       break;
     }
     default:
     {
       QDoubleSpinBox::keyReleaseEvent( event );
       break;
     }
   }
}

