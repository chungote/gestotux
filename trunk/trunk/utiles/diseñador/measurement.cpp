/***************************************************************************
 *   Copyright (C) 2006 by Norbert Szabo                                   *
 *   nszabo@helta.hu                                                       *
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
#include "measurement.h"

/*#include <qapplication.h>*/

#define SCREENDPI	72.0
#define TRIMFACTOR	1.3

Measurement::Measurement( )
{
	zoomlevel = 1.0;
	msr = Metric;
}

Measurement::~ Measurement( )
{
}

void Measurement::setMeasure( Measure m ) { msr = m; }

void Measurement::setZoomLevel( double z )
{
	zoomlevel = z;
	if ( zoomlevel > 10.0 )
		zoomlevel = 10.0;
	if ( zoomlevel < 1.0 )
		zoomlevel = 1.0;
}

void Measurement::changeZoomLevelBy( double z )
{
	zoomlevel+=z;
	setZoomLevel( zoomlevel );
}

int Measurement::measureToPixel( double m )
{
	double d;
	if ( msr == Metric )
		d = m * SCREENDPI/25.4*TRIMFACTOR*zoomlevel;		// 1 mm in pixel
	else
		d = m * SCREENDPI/10.0*TRIMFACTOR*zoomlevel;		// 0.1 inch in pixel

	return qRound( d );
}

double Measurement::pixelToMeasure( int p )
{
	double d;
	if ( msr == Metric )
		d = p*25.4/SCREENDPI/TRIMFACTOR;
	else
		d = p*10.0/SCREENDPI/TRIMFACTOR;

	return d;
}

double Measurement::zoomLevel( ) const
{
	return zoomlevel;
}

Measurement::Measure Measurement::measure( ) const
{
	return msr;
}

double Measurement::measureUnit( ) const
{
	if ( msr == Metric )
		return SCREENDPI/25.4*TRIMFACTOR*zoomlevel;		// 1 mm in pixel
	else
		return SCREENDPI/10.0*TRIMFACTOR*zoomlevel;		// 0.1 inch in pixel
}

QString Measurement::pixelToMeasureCaption( int p )
{
	QString s;
	if ( msr == Metric ) {
		s.setNum( pixelToMeasure( p ), 'f',3);
		s+=" mm";
	} else {
		s.setNum( pixelToMeasure( p )*10.0, 'f',3);
		s+=" inch";
	}
	return s;
}

QString Measurement::pixelSizeToMeasureCaption( int w, int h )
{
	return "W: "+pixelToMeasureCaption( w )+" H: "+pixelToMeasureCaption( h );
}

QString Measurement::pixelPosToMeasureCaption( int x, int y )
{
	return "X: "+pixelToMeasureCaption( x )+" Y: "+pixelToMeasureCaption( y );
}

QString Measurement::pixelToMeasureStr( int p, int decimals )
{
	QString s;
	if ( msr == Metric )
		s.setNum( pixelToMeasure( p ), 'f', decimals);
	else
		s.setNum( pixelToMeasure( p )*10.0, 'f', decimals);

	return s;
}


