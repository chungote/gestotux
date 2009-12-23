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
#include "nccolorcombo.h"

#include <qcolordialog.h>
#include <qpainter.h>
#include <qpixmap.h>

#define COLORARRAY_SIZE 17

static QColor *standardPalette = 0;

static void createStandardPalette()
{
    if ( standardPalette )
    return;

    standardPalette = new QColor [COLORARRAY_SIZE];

    int i = 0;

    standardPalette[i++] = Qt::red;
    standardPalette[i++] = Qt::green;
    standardPalette[i++] = Qt::blue;
    standardPalette[i++] = Qt::cyan;
    standardPalette[i++] = Qt::magenta;
    standardPalette[i++] = Qt::yellow;
    standardPalette[i++] = Qt::darkRed;
    standardPalette[i++] = Qt::darkGreen;
    standardPalette[i++] = Qt::darkBlue;
    standardPalette[i++] = Qt::darkCyan;
    standardPalette[i++] = Qt::darkMagenta;
    standardPalette[i++] = Qt::darkYellow;
    standardPalette[i++] = Qt::white;
    standardPalette[i++] = Qt::lightGray;
    standardPalette[i++] = Qt::gray;
    standardPalette[i++] = Qt::darkGray;
    standardPalette[i++] = Qt::black;
}


NCColorCombo::NCColorCombo( QWidget *parent, const char *name )
    : QComboBox( parent )
{
	this->setObjectName( name );
	_showEmptyList=false;

	customColor.setRgb( 255, 255, 255 );
	internalcolor.setRgb( 255, 255, 255 );

	createStandardPalette();

	addColors();

	connect( this, SIGNAL( activated(int) ), SLOT( slotActivated(int) ) );
	connect( this, SIGNAL( highlighted(int) ), SLOT( slotHighlighted(int) ) );
}


NCColorCombo::~NCColorCombo()
{
	//delete d;
}

void NCColorCombo::setColor( const QColor &col )
{
	internalcolor = col;
	_showEmptyList=false;
	addColors();
}


QColor NCColorCombo::color() const {
	return internalcolor;
}

void NCColorCombo::resizeEvent( QResizeEvent *re )
{
    QComboBox::resizeEvent( re );
    addColors();
}

void NCColorCombo::showEmptyList()
{
	_showEmptyList=true;
	addColors();
}

void NCColorCombo::slotActivated( int index )
{
	if ( index == 0 ) {
		QColor c = QColorDialog::getColor( customColor, this );
		if ( c.isValid() ) {
			customColor = c;
			QPainter painter;
			QPen pen;
			QRect rect( 0, 0, width(), QFontMetrics(painter.font()).height()+4);
			QPixmap pixmap( rect.width(), rect.height() );

 			if ( qGray( customColor.rgb() ) < 128 )
 				pen.setColor( Qt::white );
 			else
 				pen.setColor( Qt::black );

			painter.begin( &pixmap );
			QBrush brush( customColor );
			painter.fillRect( rect, brush );
			painter.setPen( pen );
			painter.drawText( 2, QFontMetrics(painter.font()).ascent()+2, tr("Custom...") );
			painter.end();

			this->setItemData( 0, pixmap, Qt::BackgroundColorRole );
			pixmap.detach();
		}

		internalcolor = customColor;
	}
	else
		internalcolor = standardPalette[ index - 1 ];

	emit activated( internalcolor );
}

void NCColorCombo::slotHighlighted( int index )
{
    if ( index == 0 )
        internalcolor = customColor;
    else
        internalcolor = standardPalette[ index - 1 ];

    emit highlighted( internalcolor );
}

void NCColorCombo::addColors()
{
    QPainter painter;
    QPen pen;
    QRect rect( 0, 0, width(), QFontMetrics(painter.font()).height()+4 );
    QPixmap pixmap( rect.width(), rect.height() );
    int i;

    clear();
    if (_showEmptyList) return;

    createStandardPalette();

    for ( i = 0; i < COLORARRAY_SIZE; i++ )
        if ( standardPalette[i] == internalcolor ) break;

    if ( i == COLORARRAY_SIZE )
        customColor = internalcolor;

    if ( qGray( customColor.rgb() ) < 128 )
        pen.setColor( Qt::white );
    else
        pen.setColor( Qt::black );

    painter.begin( &pixmap );
    QBrush brush( customColor );
    painter.fillRect( rect, brush );
    painter.setPen( pen );
    painter.drawText( 2, QFontMetrics(painter.font()).ascent()+2, tr("Custom...") );
    painter.end();

    this->insertItem( -1, "", pixmap );
    pixmap.detach();

    for ( i = 0; i < COLORARRAY_SIZE; i++ )
    {
        painter.begin( &pixmap );
        QBrush brush( standardPalette[i] );
        painter.fillRect( rect, brush );
        painter.end();

        this->insertItem( -1, "", pixmap );
        pixmap.detach();

        if ( standardPalette[i] == internalcolor )
            setCurrentIndex( i + 1 );
    }
}

void NCColorCombo::setWebColor( const QString & colorstring )
{
	QColor color;
	bool ok;
	colorstring.right(6).toInt( &ok, 16 );
	if ( ok && colorstring.startsWith("#") && colorstring.length() == 7 ) {

		color = QColor( colorstring.mid(1,2).toInt( &ok, 16),
						colorstring.mid(3,2).toInt( &ok, 16),
						colorstring.mid(5,2).toInt( &ok, 16) );
		setColor( color );
	}

}

QString NCColorCombo::webColor() const
{
	QString webcol;
	webcol.sprintf( "#%02X%02X%02X", internalcolor.red(), internalcolor.green(), internalcolor.blue() );
	return webcol;
}
