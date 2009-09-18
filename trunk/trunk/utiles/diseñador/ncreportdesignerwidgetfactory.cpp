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
#include "ncreportdesignerwidgetfactory.h"
#include "ncreportdesignerwidget.h"
#include "ncreportdesignerwindow.h"
//#include "ncreportdesignerdesignarea.h"
#include "globals.h"

#include <QLineEdit>
#include <QLabel>
#include <QDom>


QWidget *NCReportDesignerWidgetFactory::create( int id, QWidget *parent, const char *name, bool init, const QRect *r )
{
	QString n = className( id );
	if ( n.isNull() )
		return 0;

	QWidget *w = 0;
	//QString str = "report_widget"; //WidgetDatabase::createWidgetName( id );
	const char *s = n.latin1();
	w = createWidget( n, parent, name ? name : s, init, r );
	if ( !w )
		return 0;
	//MetaDataBase::addEntry( w );

	//if ( !defaultProperties->contains( id ) )
	//	saveDefaultProperties( w, id );
	//if ( !changedProperties->contains( id ) )
	//	saveChangedProperties( w, id );

	return w;
}

QWidget * NCReportDesignerWidgetFactory::create( const QDomElement &e, QWidget * parent, const char * name, bool init, const QRect * r )
{
	QString nm;	// = className( tagname );

	if ( e.tagName() == "line" ) {
		if ( e.attribute( "fromY" )==e.attribute( "toY" ) ) nm ="LineH";
		else  nm ="LineV";
	} else if ( e.tagName() == "label" ) nm="Label";
	else if ( e.tagName() == "field" ) nm="Field";
	else if ( e.tagName() == "rectangle" ) nm="Rectangle";
	else if ( e.tagName() == "ellipse" || e.tagName() == "circle" ) nm="Circle";
	else if ( e.tagName() == "pixmap" || e.tagName() == "image" ) nm="Image";
	else if ( e.tagName() == "image" ) nm="Image";

	QWidget *w = 0;
	const char *s = nm.latin1();
	w = createWidget( nm, parent, name ? name : s, init, r );
	if ( !w )
		return 0;

	return w;
}

QString NCReportDesignerWidgetFactory::className( int id )
{
	QString nm;
	switch( id ) {
		case NCReportDesignerWindow::Label: nm = "Label"; break;
		case NCReportDesignerWindow::Field: nm = "Field"; break;
		case NCReportDesignerWindow::Rectangle: nm = "Rectangle"; break;
		case NCReportDesignerWindow::LineH: nm = "LineH"; break;
		case NCReportDesignerWindow::LineV: nm = "LineV"; break;
		case NCReportDesignerWindow::Circle: nm = "Circle"; break;
		case NCReportDesignerWindow::Image: nm = "Image"; break;
	}
	return nm;
}

QString NCReportDesignerWidgetFactory::className( const QString & )
{
	return QString::null;
}


QWidget* NCReportDesignerWidgetFactory::createWidget( const QString &className, QWidget *parent, const char *name,
		bool init, const QRect *r )
{
	NCReportDesignerDesignArea *pa = (NCReportDesignerDesignArea*)parent;
	NCReportDesignerWidget *w = 0;

#ifdef REPORTDESIGNER_DEBUG
	QTime t;
	t.start();
#endif

	if ( className == "Label" ) {
		w = new dw_Label( pa, name );
	}
	else if ( className == "Field" ) {
		w = new dw_Field( pa, name );
	}
	else if ( className == "LineH" ) {
		w = new dw_Line( Qt::Horizontal, pa, name );
	}
	else if ( className == "LineV" ) {
		w = new dw_Line( Qt::Vertical, pa, name );
	}
	else if ( className == "Rectangle" ) {
		w = new dw_Rectangle( pa, name );
	}
	else if ( className == "Circle" ) {
		w = new dw_Circle( pa, name );
	}
	else if ( className == "Image" ) {
		w = new dw_Image( pa, name );
	}


#ifdef REPORTDESIGNER_DEBUG
	qDebug("createWidget(%s): %i", className.latin1(), t.elapsed() );
#endif

	return w;
}

// const char* NCReportDesignerWidgetFactory::classNameOf( QObject* o )
// {
// 	if ( o->isA( "PropertyObject" ) )
// 		return o->className();
//
// 	if ( ::qt_cast<QDesignerTabWidget*>(o) )
// 		return "QTabWidget";
// 	else if ( ::qt_cast<QDesignerWidgetStack*>(o) )
// 		return "QWidgetStack";
//
//     return o->className();
// }





