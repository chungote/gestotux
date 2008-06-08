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
#include "einformeimpresora.h"
#include "preferencias.h"

EInformeImpresora::EInformeImpresora()
 : QPrinter()
{
 preferencias *p = preferencias::getInstancia();
 // Orientacion
 if( p->value( "aCarCorr/informes/orientacion", QPrinter::Landscape ).toInt() == QPrinter::Landscape )
 {
  this->setOrientation( QPrinter::Landscape );
 }
 else
 {
  this->setOrientation( QPrinter::Portrait );
 }
 // Tamaño
 switch( p->value( "aCarCorr/informes/tam", QPrinter::A4 ).toInt() )
 {
	case QPrinter::A1:
	{this->setPageSize( QPrinter::A1 );break;}
	case QPrinter::A2:
	{this->setPageSize( QPrinter::A2 );break;}
	case QPrinter::A3:
	{this->setPageSize( QPrinter::A3 );break;}
	case QPrinter::A4:
	{this->setPageSize( QPrinter::A4 );break;}
	case QPrinter::A5:
	{this->setPageSize( QPrinter::A5 );break;}
	case QPrinter::A6:
	{this->setPageSize( QPrinter::A6 );break;}
	case QPrinter::A7:
	{this->setPageSize( QPrinter::A7 );break;}
	case QPrinter::A8:
	{this->setPageSize( QPrinter::A8 );break;}
	case QPrinter::A9:
	{this->setPageSize( QPrinter::A9 );break;}
	///@todo Terminar de poner los tamaños de hoja que faltan
	default:
	{
		this->setPageSize( QPrinter::A4 );
		break;
	}
 }
 // Margenes
 qreal arriba,abajo,derecha,izquierda;
 int unidad;
 arriba    = p->value( "aCarCorr/informes/margenarriba"   , 150.0 ).toDouble();
 abajo     = p->value( "aCarCorr/informes/margenabajo"    , 150.0 ).toDouble();
 derecha   = p->value( "aCarCorr/informes/margenderecha"  , 150.0 ).toDouble();
 izquierda = p->value( "aCarCorr/informes/margenizquierda", 150.0 ).toDouble();
 unidad    = p->value( "aCarCorr/informes/unidad", QPrinter::Millimeter ).toInt();
 switch( unidad )
 {
  case QPrinter::Millimeter:
  { this->setPageMargins( izquierda, arriba, derecha, abajo, QPrinter::Millimeter ); }
  case QPrinter::DevicePixel:
  { this->setPageMargins( izquierda, arriba, derecha, abajo, QPrinter::DevicePixel ); }
  case QPrinter::Cicero:
  { this->setPageMargins( izquierda, arriba, derecha, abajo, QPrinter::Cicero ); }
  case QPrinter::Didot:
  { this->setPageMargins( izquierda, arriba, derecha, abajo, QPrinter::Didot ); }
  case QPrinter::Point:
  { this->setPageMargins( izquierda, arriba, derecha, abajo, QPrinter::Point ); }
  case QPrinter::Inch:
  { this->setPageMargins( izquierda, arriba, derecha, abajo, QPrinter::Inch ); }
  case QPrinter::Pica:
  { this->setPageMargins( izquierda, arriba, derecha, abajo, QPrinter::Pica ); }
 }
}


EInformeImpresora::~EInformeImpresora()
{
}




/*!
    \fn EInformeImpresora::guardar()
 */
void EInformeImpresora::guardar()
{
 qWarning( "Guardar" );
 preferencias *p = preferencias::getInstancia();
 // Cargar las preferencias a la impresora que las guarda el dialogo mismo
 // Orientacion
 if( this->orientation() == QPrinter::Portrait )
 {
  p->setValue( "aCarCorr/informes/orientacion", QPrinter::Portrait );
 }
 else
 {
  p->setValue( "aCarCorr/informes/orientacion", QPrinter::Landscape );
 }
 // Tamaño
 p->setValue( "aCarCorr/informes/tam", this->pageSize() );
 qreal arriba, abajo, izquierda, derecha;
 Unit unidad;
 this->getPageMargins( &izquierda, &arriba, &derecha, &abajo, unidad );
 p->setValue( "aCarCorr/informes/margenarriba"   , arriba    );
 p->setValue( "aCarCorr/informes/margenabajo"    , abajo     );
 p->setValue( "aCarCorr/informes/margenderecha"  , derecha   );
 p->setValue( "aCarCorr/informes/margenizquierda", izquierda );
 p->setValue( "aCarCorr/informes/unidad", unidad );
}
