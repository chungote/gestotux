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
#ifndef NCREPORTDESIGNERWIDGET_H
#define NCREPORTDESIGNERWIDGET_H

/**
	@author Norbert Szabo <nszabo@helta.hu>
*/

#include "ncreportdesignersizehandler.h"

#include <QWidget>
#include <QColor>
#include <QPixmap>
#include <QTextStream>

class NCReportDesignerDesignArea;

class WProperty
{
public:
	enum fillStyles { transparent=0, filled };

	WProperty() {
		_posX=0; _posY=0; _height=0; _width=0;
		fontName=QString::null;
		fontSize=10;
		fontWeight = QFont::Normal;

		fontItalic=false;
		fontUnderline=false;
		fontStrikeOut=false;
		alignmentH=Qt::AlignLeft;
		alignmentV=Qt::AlignTop;
		wordbreak=false;
		forecolor = QColor(0,0,0);
		lineColor = QColor(0,0,0);
		fillColor = QColor(255,255,255);
		backcolor = QColor(255,255,255);
	//text = "";
	//displayValue = "";
		rotation=0;
		lineWidth = 1;
		lineStyle = Qt::SolidLine;
		fillStyle = transparent;

		numDigitNo =-1;
		numSeparation =FALSE;
		numSeparator =' ';
		numDigitPoint='.';
		numBlankIfZero = FALSE;
		isRichText=false;
		dynamicHeight=false;
		loadFromFile=false;
	}
	~WProperty() {}
	WProperty(const WProperty &p ) {
		*this = p;
	}
	void operator=(const WProperty &p ) {
		//qDebug( "set WProperty value..." );
		_posX = p._posX;
		_posY=p._posY;
		_height=p._height;
		_width=p._width;
		fontName=p.fontName;
		fontSize=p.fontSize;
		fontWeight = p.fontWeight;
		fontItalic=p.fontItalic;
		fontUnderline=p.fontUnderline;
		fontStrikeOut=p.fontStrikeOut;
		alignmentH=p.alignmentH;
		alignmentV=p.alignmentV;
		wordbreak=p.wordbreak;
		forecolor = p.forecolor;
		lineColor = p.lineColor;
		fillColor = p.fillColor;
		backcolor = p.backcolor;
		text = p.text;
		displayValue = p.displayValue;
		rotation=p.rotation;
		lineWidth = p.lineWidth;
		lineStyle = p.lineStyle;
		fillStyle = p.fillStyle;
		type = p.type;
		ftype = p.ftype;
		resource = p.resource;

		numDigitNo =p.numDigitNo;
		numSeparation =p.numSeparation;
		numSeparator =p.numSeparator;
		numDigitPoint=p.numDigitPoint;
		numBlankIfZero =p.numBlankIfZero;
		numFormat = p.numFormat;
		dateFormat = p.dateFormat;
		embedString = p.embedString;
		callFunction = p.callFunction;
		lookupClass = p.lookupClass;
		isRichText = p.isRichText;
		dynamicHeight = p.dynamicHeight;
		loadFromFile = p.loadFromFile;
	}

	double _posX, _posY, _width, _height;
	QColor lineColor;
	QColor fillColor;
	QColor forecolor;
	QColor backcolor;
	Qt::PenStyle lineStyle;
	fillStyles fillStyle;
	QString printWhen;
	QString fontName;
	int fontSize;
	int fontWeight;
	int lineWidth;
	int rotation;
	bool fontItalic, fontStrikeOut, fontUnderline;
	Qt::AlignmentFlag alignmentH;
	Qt::AlignmentFlag alignmentV;
	bool wordbreak;
	QString text;
	QString displayValue;
	QString type, ftype;
	QString resource;	// image

	int numDigitNo;
	bool numSeparation;
	char numSeparator;
	char numDigitPoint;
	bool numBlankIfZero;
	QString numFormat;
	QString dateFormat;

	QString embedString;
	QString callFunction;
	QString lookupClass;
	bool isRichText;
	bool dynamicHeight;
	bool loadFromFile;
};


class NCReportDesignerWidget : public QWidget
{
 Q_OBJECT
public:
	NCReportDesignerWidget( NCReportDesignerDesignArea* parent, const char* name=0 );
    ~NCReportDesignerWidget();

	enum WidgetType { Label=0, Field, Line, Rectangle, Circle, Image, Unknown };

	WidgetType wtype;
	QString etype;
	QString objectname;
	QString tagname;
	QSize defaultSize;

	Selection::SelectionType d_selectType;
	WProperty p;
	WProperty& prop();

	// designer props.
	Qt::Orientation orient;
	bool useSize;
	bool usePointFromTo;
	bool useLineWidth;
	bool useFontSize;
	bool useFontWeight;
	bool useFontName;
	bool useFontItalic;
	bool useFontStrikeOut;
	bool useFontUnderline;
	bool useAlignment;
	bool useWordBreak;
	bool useText;
	bool useDisplayValue;
	bool usePrintWhen;
	bool useRotation;
	bool useLineColor;
	bool useFillColor;
	bool useForeColor;
	bool useBackColor;
	bool useLineStyle;
	bool useFillStyle;
	bool useFType;
	bool useType;
	bool useResource;
	bool useDataFormat;
	bool useCallFunction;
	bool useEmbedString;
	bool useRichText;
	bool useDynamicHeight;
	bool useLoadFromFile;

	bool initOpenPropDia;

	virtual QSize sizeHint() const;
	virtual QSize minimumSizeHint() const;
	virtual void updateWidget();
	//virtual void save( QTextStream &ts );

protected:
	NCReportDesignerDesignArea *area;
//	virtual void paintEvent( QPaintEvent* e );
	//void saveProperties( QTextStream &ts );

	virtual void mousePressEvent(QMouseEvent * e );
	virtual void mouseMoveEvent(QMouseEvent * e );
	virtual void mouseReleaseEvent(QMouseEvent * e );
	virtual void mouseDoubleClickEvent(QMouseEvent * e );
	virtual void keyPressEvent( QKeyEvent * e );
	virtual void keyReleaseEvent( QKeyEvent * e );

};

/*!
NCReport label object
*/
class  dw_Label : public NCReportDesignerWidget
{
public:
	dw_Label( NCReportDesignerDesignArea* parent, const char* name=0 );
	~dw_Label();
protected:
	QColor borderColor;
	bool drawborder;

	virtual void paintEvent( QPaintEvent* e );

};

/*!
NCReport field object
 */
class  dw_Field : public dw_Label
{
public:
	dw_Field( NCReportDesignerDesignArea* parent, const char* name=0 );
	~dw_Field();
protected:
	virtual void paintEvent( QPaintEvent* e );

};

/*!
NCReport label object
 */
class  dw_Line : public NCReportDesignerWidget
{
public:
	dw_Line( Qt::Orientation ori, NCReportDesignerDesignArea* parent, const char* name=0 );
	~dw_Line();

	void updateWidget();

protected:
	virtual void paintEvent( QPaintEvent* e );
	virtual void updateMask();

};

/*!
NCReport rectangle object
 */
class  dw_Rectangle : public NCReportDesignerWidget
{
public:
	dw_Rectangle( NCReportDesignerDesignArea* parent, const char* name=0 );
	~dw_Rectangle();
	void updateWidget();
protected:
	int margin;

	virtual void paintEvent( QPaintEvent* e );
	virtual void updateMask();
};


/*!
NCReport circle object
 */
class  dw_Circle : public NCReportDesignerWidget
{
public:
	dw_Circle( NCReportDesignerDesignArea* parent, const char* name=0 );
	~dw_Circle();
protected:
	virtual void paintEvent( QPaintEvent* e );
	virtual void updateMask();
};


/*!
NCReport field object
 */
class  dw_Image : public NCReportDesignerWidget
{
public:
	dw_Image( NCReportDesignerDesignArea* parent, const char* name=0 );
	~dw_Image();

	void updateWidget();

protected:
	QPixmap pm;

	virtual void paintEvent( QPaintEvent* e );

};


#endif
