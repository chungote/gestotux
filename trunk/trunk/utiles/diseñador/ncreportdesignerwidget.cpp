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
#include "ncreportdesignerwidget.h"
#include "ncreportdesignerdesignarea.h"

#include <QKeyEvent>
#include <QPainter>
#include <QPen>

NCReportDesignerWidget::NCReportDesignerWidget( NCReportDesignerDesignArea* parent, const char* name )
	: QWidget( parent, name )
{
	area = parent;
	etype = "widget";
	wtype = Unknown;
	objectname = name;
	initOpenPropDia = FALSE;	// initially open property dialog

	d_selectType = Selection::Full;

	//---------------------------
	// designer properties
	//---------------------------
	useSize = FALSE;
	usePointFromTo = FALSE;
	useLineWidth = FALSE;
	useFontSize = FALSE;
	useFontWeight = FALSE;
	useFontName = FALSE;
	useFontItalic = FALSE;
	useFontStrikeOut = FALSE;
	useFontUnderline = FALSE;
	useAlignment = FALSE;
	useWordBreak = FALSE;
	useText = FALSE;
	useDisplayValue = FALSE;
	usePrintWhen = FALSE;
	useRotation = FALSE;
	useLineColor = FALSE;
	useFillColor = FALSE;
	useForeColor = FALSE;
	useBackColor = FALSE;
	useLineStyle = FALSE;
	useFillStyle = FALSE;
	useFType = FALSE;
	useType = FALSE;
	useResource = FALSE;
	useDataFormat = FALSE;
	useCallFunction = FALSE;
	useEmbedString = FALSE;


	setSizePolicy( QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed) );
}


NCReportDesignerWidget::~NCReportDesignerWidget()
{
}

WProperty & NCReportDesignerWidget::prop( )
{
	return p;
}

QSize NCReportDesignerWidget::sizeHint( ) const
{
	//return QSize( 80,21 );
	//return QWidget::sizeHint( );
	return defaultSize;
}

QSize NCReportDesignerWidget::minimumSizeHint( ) const
{
	//return defaultSize;
	return QWidget::minimumSizeHint( );
	//return QSize(_width, _height);
}

void NCReportDesignerWidget::mousePressEvent( QMouseEvent * e )
{
	area->handleMousePress( e, this );
}
void NCReportDesignerWidget::mouseMoveEvent( QMouseEvent * e )
{
	area->handleMouseMove( e, this );
}
void NCReportDesignerWidget::mouseReleaseEvent( QMouseEvent * e )
{
	area->handleMouseRelease( e, this );
}
void NCReportDesignerWidget::mouseDoubleClickEvent( QMouseEvent * e )
{
	area->handleMouseDblClick( e, this );
}

void NCReportDesignerWidget::keyPressEvent( QKeyEvent * e )
{
	e->ignore();
	//area->handleKeyPress( e, this );
}
void NCReportDesignerWidget::keyReleaseEvent( QKeyEvent * e )
{
	e->ignore();
	//area->handleKeyRelease( e, this );
}

void NCReportDesignerWidget::updateWidget( )
{
	repaint();
}


// void NCReportDesignerWidget::save( QTextStream & ts )
// {
// 	//save myself to xml.
// }
//
// void NCReportDesignerWidget::saveProperties( QTextStream & ts )
// {
// }

//////////////
// LABEL
//////////////
dw_Label::dw_Label( NCReportDesignerDesignArea * parent, const char * name ) : NCReportDesignerWidget( parent, name )
{
	wtype = Label;
	tagname = "label";

	useSize = TRUE;
	useText = TRUE;
	useFontName = TRUE;
	useFontSize = TRUE;
	useFontWeight = TRUE;
	useFontItalic = TRUE;
	useFontUnderline = TRUE;
	useFontStrikeOut = TRUE;
	useForeColor = TRUE;
	useAlignment = TRUE;
	usePrintWhen = TRUE;
	useWordBreak = TRUE;
	useRichText = TRUE;
	useLoadFromFile = TRUE;

	borderColor = QColor(128,128,128);
	initOpenPropDia = TRUE;

	//_width = 60.0;
	//_height = 16.0;
	defaultSize = QSize( 60, 18 );
	resize( defaultSize );
	//setMinimumSize( QSize(_width, _height) );
	setPaletteBackgroundColor( Qt::white );
	p.text = "Label";
	drawborder = FALSE;
}

dw_Label::~ dw_Label( )
{
}

void dw_Label::paintEvent( QPaintEvent * )
{
	QPainter pa( this );


	QFont f;
	if ( !p.fontName.isEmpty() )
		f.setFamily( p.fontName );

	f.setPointSize( p.fontSize );
	f.setWeight( p.fontWeight );
	f.setItalic( p.fontItalic );
	f.setUnderline( p.fontUnderline );
	f.setStrikeOut( p.fontStrikeOut );
	pa.setFont( f );
	//QFontMetrics fm = p.fontMetrics();
	// automatic size
	//int auto_w = fm.width( text );
	//int auto_h = fm.height();

	QPen pen( p.forecolor );
	pa.setPen( pen );
	int aflag = p.alignmentH | p.alignmentV;
	if ( p.wordbreak )
		aflag = aflag | Qt::WordBreak;

	if (p.rotation !=0) {
		pa.save();
		pa.rotate( p.rotation );
	}

	pa.drawText( 0,0, width()-1,height()/*-2*/, aflag, p.text );

	if (p.rotation !=0) {
		pa.restore();
	}

	pen.setColor( borderColor );
	pen.setStyle( Qt::SolidLine );
	pa.setPen( pen );
	//p.setBrush( Qt:white );
	if ( drawborder )
		pa.drawRect( 0,0,width(),height());

}

//////////////
// FIELD
//////////////
dw_Field::dw_Field( NCReportDesignerDesignArea * parent, const char * name )
	: dw_Label( parent, name )
{
	wtype = Field;
	tagname = "field";
	borderColor = QColor( 255,0,0 );
	p.text = "Field";
	p.ftype = "sql";
	setPaletteBackgroundColor( QColor(255,220,220) );
	drawborder = TRUE;
	useFType = TRUE;
	useType = TRUE;
	useDataFormat = TRUE;
	useDynamicHeight = TRUE;

}

dw_Field::~ dw_Field( )
{
}

void dw_Field::paintEvent( QPaintEvent * e )
{
	dw_Label::paintEvent( e );
}

//////////////
// LINE
//////////////
dw_Line::dw_Line( Orientation ori, NCReportDesignerDesignArea * parent, const char * name ) : NCReportDesignerWidget( parent, name )
{
	wtype = Line;
	tagname = "line";

	usePointFromTo = TRUE;
	useLineWidth = TRUE;
	useLineStyle = TRUE;
	useLineColor = TRUE;
	//useSize = TRUE;
	//useFillColor = TRUE;
	//useFillStyle = TRUE;
	usePrintWhen = TRUE;

	orient = ori;
	//_width = 50.0;
	//_height = 5.0;
	//lineWidth = 0;

	if ( ori == Horizontal ) {
		defaultSize = QSize(36,p.lineWidth);
		d_selectType = Selection::Horizontal;
		setMaximumHeight( p.lineWidth );
	} else {
		defaultSize = QSize(p.lineWidth,36);
		d_selectType = Selection::Vertical;
		setMaximumWidth( p.lineWidth );
	}
	resize( defaultSize );

	setAutoMask( TRUE );
}

dw_Line::~ dw_Line( )
{
}

void dw_Line::updateWidget( )
{
	if ( orient == Horizontal ) {
		setMaximumHeight( p.lineWidth );
		resize( width(), p.lineWidth );
	} else {
		setMaximumWidth( p.lineWidth );
		resize( p.lineWidth, height() );
	}
	repaint();
}

void dw_Line::paintEvent( QPaintEvent * )
{
	QPainter pa( this );
	//p.setBackgroundMode(Qt::TransparentMode);

	QPen pen( p.lineColor, p.lineWidth, p.lineStyle );
	pa.setPen( pen );

	if ( orient == Horizontal )
		pa.drawLine( 0, height()/2, width(), height()/2);
	else
		pa.drawLine( width()/2, 0, width()/2, height());

/*	if ( orient == Horizontal )
		pa.drawLine( 0, 0, width(), 0 );
	else
		pa.drawLine( 0, 0, 0, height());*/
}

void dw_Line::updateMask()
{
	//QRegion r( rect() );
	//r = r.subtract( QRect(1, 0, width() - 2, base - amplitude ) );
	//( QRect(0,(height()-lineWidth)/2-2,width(), lineWidth+4) );

/*	if ( orient == Horizontal ) {
		r = QRegion( QRect(0, (height()-lineWidth)/2, width(), lineWidth) );
	} else {
		r = QRegion( QRect( (width()-lineWidth)/2, 0, lineWidth, height() ));
	}*/

/*	QRegion r;
	if ( orient == Horizontal ) {
		r = QRegion( QRect(0, 0, width(), lineWidth) );
	} else {
		r = QRegion( QRect( 0, 0, lineWidth, height() ) );
	}
	setMask( r );*/
}

//////////////
// RECTANGLE
//////////////
dw_Rectangle::dw_Rectangle( NCReportDesignerDesignArea * parent, const char * name )
	: NCReportDesignerWidget( parent, name )
{
	wtype = Rectangle;
	tagname = "rectangle";

	usePointFromTo = FALSE;
	useLineWidth = TRUE;
	useLineStyle = TRUE;
	useSize = TRUE;
	useFillColor = TRUE;
	useLineColor = TRUE;
	useFillStyle = TRUE;
	usePrintWhen = TRUE;

	//p.fillStyle = transparent;
	//p.lineWidth = 1;
	margin =0;
	defaultSize = QSize(16,16);
	resize( defaultSize );

}

dw_Rectangle::~ dw_Rectangle( )
{
}

void dw_Rectangle::paintEvent( QPaintEvent * )
{
	margin = (int)(p.lineWidth/2);
	QPainter pa( this );
	QPen pen( p.lineColor, p.lineWidth, p.lineStyle );
	pa.setPen( pen );

	if ( p.fillStyle == WProperty::filled ) {
		setAutoMask( FALSE );
		pa.setBrush( p.fillColor );
	} else {
		//setAutoMask( TRUE );
		setAutoMask( FALSE );
		pa.setBrush( Qt::white );
	}

	pa.drawRect( margin, margin, width()-margin*2, height()-margin*2 );


/*	if ( p.fillStyle == WProperty::transparent ) {
		if ( p.lineWidth == 0 )
			pa.drawRect( 0, 0, width(), height() );
		else
			pa.drawRect( 0, 0, width(), height() );
			//pa.drawRect( p.lineWidth-1, p.lineWidth-1, width()-(p.lineWidth-1), height()-(p.lineWidth-1) );
	} else
		pa.drawRect( 0, 0, width(), height() );*/
}

void dw_Rectangle::updateMask()
{
	if ( p.fillStyle == WProperty::filled )
		return;

	QRegion r( rect() );
	r = r.subtract( QRect( p.lineWidth, p.lineWidth, width()-margin-p.lineWidth, height()-margin-p.lineWidth ) );

	/*	if ( p.lineWidth == 0 )
		r = r.subtract( QRect( 1, 1, width()-2, height()-2 ) );
	else
		r = r.subtract( QRect( p.lineWidth, p.lineWidth, width()-p.lineWidth*2, height()-p.lineWidth*2 ) );*/
	setMask( r );
}

void dw_Rectangle::updateWidget( )
{
	resize( width(), height() );
	repaint();
}

//////////////
// CIRCLE
//////////////
dw_Circle::dw_Circle( NCReportDesignerDesignArea * parent, const char * name )
	: NCReportDesignerWidget( parent, name )
{
	wtype = Circle;
	tagname = "ellipse";

	usePointFromTo = FALSE;
	useLineWidth = TRUE;
	useLineStyle = TRUE;
	useSize = TRUE;
	useFillColor = TRUE;
	useLineColor = TRUE;
	useFillStyle = TRUE;
	usePrintWhen = TRUE;

	p.fillStyle = WProperty::filled;
	//p.lineWidth = 1;
	defaultSize = QSize(10,10);
	resize( defaultSize );
}

dw_Circle::~ dw_Circle( )
{
}

void dw_Circle::paintEvent( QPaintEvent * )
{
	QPainter pa( this );
	QPen pen( p.lineColor, p.lineWidth, p.lineStyle );
	pa.setPen( pen );

	if ( p.fillStyle == WProperty::filled ) {
		setAutoMask( FALSE );
		pa.setBrush( p.fillColor );
	} else {
		//setAutoMask( TRUE );
		setAutoMask( FALSE );
	}

	if ( p.fillStyle == WProperty::transparent ) {
		if ( p.lineWidth == 0 )
			pa.drawEllipse( 0, 0, width(), height() );
		else
			pa.drawEllipse( 0, 0, width(), height() );
			//pa.drawRect( p.lineWidth-1, p.lineWidth-1, width()-(p.lineWidth-1), height()-(p.lineWidth-1) );
	} else
		pa.drawEllipse( 0, 0, width(), height() );
}

void dw_Circle::updateMask()
{
	if ( p.fillStyle == WProperty::filled )
		return;

	QRegion r( rect(), QRegion::Ellipse );
	if ( p.lineWidth == 0 )
		r = r.subtract( QRect( 1, 1, width()-2, height()-2 ) );
	else
		r = r.subtract( QRect( p.lineWidth, p.lineWidth, width()-p.lineWidth*2, height()-p.lineWidth*2 ) );
	setMask( r );
}



//////////////
// IMAGE
//////////////
dw_Image::dw_Image( NCReportDesignerDesignArea * parent, const char * name )
	: NCReportDesignerWidget( parent, name )
{
	wtype = Image;
	tagname = "pixmap";

	usePrintWhen = TRUE;
	useSize = TRUE;
	useText = TRUE;
	useResource = TRUE;
	initOpenPropDia = TRUE;

	defaultSize = QSize(10,10);
}

dw_Image::~ dw_Image( )
{
}

void dw_Image::paintEvent( QPaintEvent * )
{
	QPainter pa( this );
	if ( pm.isNull() )
		pm.load( p.resource );
		//pm.load( p.resource.isEmpty() ? p.text : p.resource );

	if ( pm.isNull() ) {
		QBrush b( Qt::gray, QBrush::BDiagPattern );
		pa.setBrush( b );
		QPen pen( Qt::gray );
		pa.setPen( pen );
		pa.drawRect( 0, 0, width(), height() );
	} else
		pa.drawPixmap( 0,0, pm, 0, 0, width(), height() );
}

void dw_Image::updateWidget( )
{
	pm.load( p.resource );
	//pm.load( p.resource.isEmpty() ? p.text : p.resource );
	//pm.resize( width(), height() );
	repaint();
}










