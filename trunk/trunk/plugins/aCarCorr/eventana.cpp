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
#include "preferencias.h"
//#include "ayudante.h"

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
 preferencias *p = preferencias::getInstancia();
 p->beginGroup( "Ventanas" );
 p->beginGroup( nombre_ventana );
 this->resize( p->value( "tam", QSize( 600, 600 ) ).toSize() );
 this->move( p->value( "pos", QPoint( 0, 0 ) ).toPoint() );
 if( p->value( "maximizada" ).toBool() )
 {
  this->setWindowState( Qt::WindowMaximized );
 }
 p->endGroup();
 p->endGroup();
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
    \fn EVentana::closeEvent ( QCloseEvent * event )
    Antes de cerrase a si misma guarda las preferencias de las ventanas en la configuracion para que queden del mismo tamaño al abrirse nuevamente
	@param event Evento a procesar
 */
void EVentana::closeEvent( QCloseEvent * event )
{
 if ( !nombre_ventana.isEmpty() )
 {
	preferencias *p = preferencias::getInstancia();
	p->inicio();
	p->beginGroup( "Ventanas" );
	p->beginGroup( nombre_ventana );
	p->setValue( "tam"       , size() );
	p->setValue( "pos"       , pos() );
	p->setValue( "maximizada", !this->isMaximized() );
	p->endGroup();
	p->endGroup();
	//qDebug( QString("Guardadas preferencias de ventana %1").arg( nombre_ventana ).toLocal8Bit() );
 }
 QWidget::closeEvent( event );
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
