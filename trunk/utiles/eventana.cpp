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
#include "eventana.h"

#include <QString>
#include <QMdiSubWindow>
#include <QIcon>

EVentana::EVentana( QWidget *padre )
 : QWidget()
{
 this->padre = padre;
 setAttribute( Qt::WA_DeleteOnClose );
}

EVentana::~EVentana()
{
}


/*!
    \fn EVentana::keyPressEvent( QKeyEvent *event )
    Implementacion de autobusqueda del archivo de ayuda al presionar la tecla F1 en la ventana.
    @param event Evento de tecla a procesar
 */
void EVentana::keyPressEvent( QKeyEvent *event )
{
 if (  event->key() ==  Qt::Key_F1 )
 {
  if( nombre_archivo_ayuda != "" )
  {
   event->accept();
/*   Ayudante a( this );
   a.mostrar();
   a.setear_archivo( nombre_archivo_ayuda );*/
  }
  else
  {
   event->ignore();
  }
 }
 else
 {
	QWidget::keyPressEvent( event );
 }
}


/*!
    \fn EVentana::setNombreVentana( QString texto )
    Setea el nombre de la ventana, carga las ultmas dimesiones de configuracion y pone el titulo de ventana deseado.
	@param texto Texto que se desea colocar a la ventana en su titulo
 */
void EVentana::setNombreVentana( QString texto )
{
 this->setWindowTitle( texto );
}


/*!
    \fn EVentana::get_nombre_ventana()
     @return Devulve el nombre de la ventana, para agregar generalmente en el menu de ventanas
 */
QString EVentana::get_nombre_ventana()
{
  return(nombre_ventana);
}

/*!
    \fn EVentana::ayuda()
 	A Implementar en futuro
	Abre la ayuda para poder el html señalado por nombre_archivo_ayuda;
 */
void EVentana::ayuda()
{
    /// @todo implementar slot de ayuda
}


/*!
    \fn EVentana::closeEvent( QCloseEvent *e )
 */
void EVentana::closeEvent( QCloseEvent *e )
{
 QWidget::closeEvent( e );
}
