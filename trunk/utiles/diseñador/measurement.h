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
#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QString>

/*!
	Measurement counting class. The base units: 1.0 mm OR 0.1 inch
*/
class Measurement
{
public:
	Measurement();
	~Measurement();

	enum Measure { Metric, English };

	void setMeasure( Measure );
	void setZoomLevel( double );
	void changeZoomLevelBy( double );
	/*!
	Converts measurment length to pixel (integer)
	*/
	int measureToPixel( double m );
	/*!
	Converts pixel to specified double measurment length.
	 */
	double pixelToMeasure( int p );
	/*!
	Returns pixel to specified double measurment length in caption.
	 */
	QString pixelToMeasureCaption( int p );
	QString pixelToMeasureStr( int p, int decimals = 3 );
	QString pixelSizeToMeasureCaption( int w, int h );
	QString pixelPosToMeasureCaption( int x, int y );
	/*! Returns 1 mm/0.1 inch in pixel. This pixel is in double value */
	double measureUnit() const;

	double zoomLevel() const;
	Measurement::Measure measure() const;

private:
	Measure msr;
	double zoomlevel;

};

#endif
