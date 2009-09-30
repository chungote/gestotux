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
#include "ncreportdesignerresourcehandler.h"
#include "ncreportdesignerwidget.h"
#include "ncreportdesignerwidgetfactory.h"
#include "ncreportdesignerdesignarea.h"
#include "ncreportdesignerdocument.h"
#include "measurement.h"
#include "globals.h"

#include <QDomElement>
#include <QWidget>
#include <QMessageBox>
#include <QLabel>
#include <QTextCodec>
#include <QDateTime>
#include <QRegExp>

#ifdef Q_WS_WIN
#define	TRIM_DEFAULT_TEXTWIDTH		1
#define	TRIM_DEFAULT_TEXTHEIGHT		0
#else
#define	TRIM_DEFAULT_TEXTWIDTH		7
#define	TRIM_DEFAULT_TEXTHEIGHT		1
#endif

#define CRLF	"\r\n"

//-------------------------------
// NCReportDesignerResourceHandler
//-------------------------------
NCReportDesignerResourceHandler::NCReportDesignerResourceHandler()
{
	designArea = 0;
	pasteOffset = 0;
}


NCReportDesignerResourceHandler::~NCReportDesignerResourceHandler()
{
}


void NCReportDesignerResourceHandler::setDesignArea( NCReportDesignerDesignArea* da )
{
	designArea = da;
}

void NCReportDesignerResourceHandler::setSection( NCReportDesignerSection * se )
{
	section = se;
}


bool NCReportDesignerResourceHandler::load( QIODevice *file )
{
	QDomDocument doc;
	loadErrorMsg = QString::null;
	errorline =0;
	errorcol =0;
#ifdef REPORTDESIGNER_DEBUG
	QTime t;
	t.start();
#endif

	//QTextStream s( file );
	//QString content = s.read();
	//removeXMLComments( content );

	//if ( !doc.setContent( content, &loadErrorMsg, &errorline, &errorcol ) ) {
	if ( !doc.setContent( file, &loadErrorMsg, &errorline, &errorcol ) ) {
		loadErrorMsg = QObject::tr("Parse error in line: %1 column: %2 ").arg(errorline).arg(errorcol)+loadErrorMsg;
		file->close();
		return FALSE;
	}
	file->close();
#ifdef REPORTDESIGNER_DEBUG
	qDebug("File parse time elapsed: %i", t.elapsed() );
#endif
	//uiFileVersion = doc.firstChild().toElement().attribute("version");
	QDomElement report = doc.documentElement();		// root element
	loadReportOptions( report );
	//qApp->processEvents();
	QDomNode node = report.firstChild();
	while ( !node.isNull() ) {
		if ( node.isElement() && node.nodeName() == "queries" ) {
			QDomElement queries = node.toElement();
			loadQueries( queries );
			break;
		}
		node = node.nextSibling();
	}
#ifdef REPORTDESIGNER_DEBUG
	qDebug("Load queries time: %i", t.elapsed() );
#endif

	//qApp->processEvents();
	node = report.firstChild();
	while ( !node.isNull() ) {
		if ( node.isElement() && node.nodeName() == "variables" ) {
			QDomElement variables = node.toElement();
			loadVariables( variables );
			break;
		}
		node = node.nextSibling();
	}
#ifdef REPORTDESIGNER_DEBUG
	qDebug("Load variables time: %i", t.elapsed() );
#endif
	//qApp->processEvents();
	node = report.firstChild();
	while ( !node.isNull() ) {
		if ( node.isElement() && node.nodeName() == "pageHeader" ) {
			QDomElement pageheader = node.toElement();
			loadPageHeader( pageheader );
			break;
		}
		node = node.nextSibling();
	}
#ifdef REPORTDESIGNER_DEBUG
	qDebug("Load page header time: %i", t.elapsed() );
#endif
	node = report.firstChild();
	while ( !node.isNull() ) {
		if ( node.isElement() && node.nodeName() == "detail" ) {
			QDomElement detail = node.toElement();
			loadDetail( detail );
			break;
		}
		node = node.nextSibling();
	}
#ifdef REPORTDESIGNER_DEBUG
	qDebug("Load detail time: %i", t.elapsed() );
#endif
	node = report.firstChild();
	while ( !node.isNull() ) {
		if ( node.isElement() && node.nodeName() == "pageFooter" ) {
			QDomElement pagefooter = node.toElement();
			loadPageFooter( pagefooter );
			break;
		}
		node = node.nextSibling();
	}
#ifdef REPORTDESIGNER_DEBUG
	qDebug("Load page footer time: %i", t.elapsed() );
#endif
	node = report.firstChild();
	while ( !node.isNull() ) {
		if ( node.isElement() && node.nodeName() == "groups" ) {
			QDomElement groups = node.toElement();
			loadGroups( groups );
			break;
		}
		node = node.nextSibling();
	}

	//doc.firstChild().toElement().firstChild().toElement();

#ifdef REPORTDESIGNER_DEBUG
	qDebug("Total load time elapsed: %i", t.elapsed() );
#endif

	return TRUE;
}

QString NCReportDesignerResourceHandler::lastLoadError( )
{
	return loadErrorMsg;
}

bool NCReportDesignerResourceHandler::loadReportOptions( QDomElement & e )
{
	if ( e.hasAttribute("name") ) document->po.reportName = e.attribute("name");
	if ( e.hasAttribute("pageSize") ) document->po.pageSize = e.attribute("pageSize");
	if ( e.hasAttribute("orientation") ) {
		document->po.orient = ( e.attribute("orientation")=="L" ? ReportPageOptions::Landscape : ReportPageOptions::Portrait);
/*		if ( e.attribute("orientation")=="P" )
			document->po.orient = ReportPageOptions::Portrait;
		else if ( e.attribute("orientation")=="L" )
			document->po.orient = ReportPageOptions::Landscape;
		else
			document->po.orient = ReportPageOptions::Portrait;*/
	}
	if ( e.hasAttribute("pageWidth") ) document->po.pageWidth = e.attribute("pageWidth").toDouble();
	if ( e.hasAttribute("pageHeight") ) document->po.pageHeight = e.attribute("pageHeight").toDouble();
	if ( e.hasAttribute("printerMode") ) document->po.printerMode = e.attribute("printerMode");

	if ( e.hasAttribute("topMargin") ) document->po.topMargin = e.attribute("topMargin").toDouble();
	if ( e.hasAttribute("bottomMargin") ) document->po.bottomMargin = e.attribute("bottomMargin").toDouble();
	if ( e.hasAttribute("leftMargin") ) document->po.leftMargin = e.attribute("leftMargin").toDouble();
	if ( e.hasAttribute("rightMargin") ) document->po.rightMargin = e.attribute("rightMargin").toDouble();

	if ( e.hasAttribute("defaultFontName") ) document->po.defaultFontName = e.attribute("defaultFontName");
	if ( e.hasAttribute("defaultFontSize") ) document->po.defaultFontSize = e.attribute("defaultFontSize").toInt();
	if ( e.hasAttribute("backColor") ) document->po.backColor = e.attribute("backColor");
	if ( e.hasAttribute("masterAlias") ) document->po.masterAlias = e.attribute("masterAlias");
	if ( e.hasAttribute("encoding") ) document->po.encoding = e.attribute("encoding");

	if ( e.hasAttribute("dataSource") ) document->po.dataSource = ( e.attribute("dataSource").toUpper()=="TEXT" ? ReportPageOptions::Textfile : ReportPageOptions::Database );
	if ( e.hasAttribute("resourceTextFile") ) document->po.resourceTextFile = e.attribute("resourceTextFile");
	if ( e.hasAttribute("textDataDelimiter") ) document->po.textDataDelimiter = e.attribute("textDataDelimiter");
	if ( e.hasAttribute("textRowFilterRegExp") ) document->po.rowFilterRegExp = e.attribute("textRowFilterRegExp");

	return TRUE;
}

bool NCReportDesignerResourceHandler::loadQueries( QDomElement & e )
{
	QDomNode n = e.firstChild();
	QDomElement de;
	while ( !n.isNull() ) {
		if ( n.isElement() && n.nodeName() == "query" ) {
			de = n.toElement();
			ReportQuery q( de.attribute("alias"), de.text() );
			document->addQuery( q );
		}
		n = n.nextSibling();
	}

	return TRUE;
}

bool NCReportDesignerResourceHandler::loadVariables( QDomElement & e )
{
	QDomNode n = e.firstChild();
	QDomElement de;
	while ( !n.isNull() ) {
		if ( n.isElement() && n.nodeName() == "variable" ) {
			de = n.toElement();
			ReportVariable v( de.attribute("name"), de.attribute("type"), de.attribute("funcType") );
			v.field = de.text();
			document->addVariable( v );
		}
		n = n.nextSibling();
	}
	return TRUE;
}

bool NCReportDesignerResourceHandler::loadPageHeader( QDomElement & e )
{
	NCReportDesignerSection *s = document->addPageHeader();
	setSection( s );
	setDesignArea( s->designArea() );
	document->setPageSize( s );
	//s->setWidth( 210.0 );
	s->setHeight( e.attribute("height").toDouble() );

	return loadSectionWidgets( e );
}

bool NCReportDesignerResourceHandler::loadPageFooter( QDomElement & e )
{
	NCReportDesignerSection *s = document->addPageFooter();
	setSection( s );
	setDesignArea( s->designArea() );
	document->setPageSize( s );
	//s->setWidth( 210.0 );
	s->setHeight( e.attribute("height").toDouble() );

	return loadSectionWidgets( e );
}

bool NCReportDesignerResourceHandler::loadDetail( QDomElement & e )
{
	NCReportDesignerSection *s = document->addDetail();
	setSection( s );
	setDesignArea( s->designArea() );
	document->setPageSize( s );
	//s->setWidth( 210.0 );
	s->setHeight( e.attribute("height").toDouble() );

	return loadSectionWidgets( e );
}


bool NCReportDesignerResourceHandler::loadGroups( QDomElement & e )
{
	QDomNode n = e.firstChild();
	QDomElement gr;
	bool ok = TRUE;
	while ( !n.isNull() ) {
		if ( n.isElement() && n.nodeName() == "group" ) {
			gr = n.toElement();

			ReportGroup group( gr.attribute("name"), gr.attribute("groupExpression"), gr.attribute("resetVariables") );
			document->addGroup( group );	// create whole group

			QDomNode n2 = gr.firstChild();
			while ( !n2.isNull() ) {
				if ( n2.isElement() && n2.nodeName() == "groupHeader" ) {
					QDomElement e0 = n2.toElement();

					// HEADER SETUP
					setSection( group.header );
					setDesignArea( group.header->designArea() );
					document->setPageSize( group.header );
					group.header->setHeight( e0.attribute("height").toDouble() );
					ok = loadSectionWidgets( e0 );
				}
				if ( ok && n2.isElement() && n2.nodeName() == "groupFooter" ) {
					QDomElement e0 = n2.toElement();

					// FOOTER SETUP
					setSection( group.footer );
					setDesignArea( group.footer->designArea() );
					document->setPageSize( group.footer );
					group.footer->setHeight( e0.attribute("height").toDouble() );
					ok = loadSectionWidgets( e0 );
				}
				n2 = n2.nextSibling();
			}
		}
		n = n.nextSibling();
	}

	return ok;
}


bool NCReportDesignerResourceHandler::loadSectionWidgets( QDomElement & e )
{
	pasteOffset = 0;
	if ( !designArea )
		return FALSE;

	QDomNode n = e.firstChild();
	QDomElement widgetelement; // = e.firstChild().toElement();

#ifdef REPORTDESIGNER_DEBUG
	QTime t;
	t.start();
#endif
	while ( !n.isNull() ) {

		if ( n.nodeType() == QDomNode::ElementNode ) {

			widgetelement = n.toElement();

			QWidget *w = NCReportDesignerWidgetFactory::create( widgetelement, designArea, 0, FALSE );
#ifdef REPORTDESIGNER_DEBUG
	qDebug("NCReportDesignerWidgetFactory::create() time: %i", t.elapsed() );
#endif
			if ( w ) {

				NCReportDesignerWidget *dw =0;
				if ( qobject_cast<NCReportDesignerWidget*>(w) != 0 )
					dw = qobject_cast<NCReportDesignerWidget*>(w);

#ifdef REPORTDESIGNER_DEBUG
	qDebug("loadWidget before time: %i", t.elapsed() );
#endif
				loadWidget( widgetelement, dw );
				w->show();
				designArea->widgets().insert( designArea->widgets().indexOf( w ) , w );
#ifdef REPORTDESIGNER_DEBUG
	qDebug("loadWidget after time: %i", t.elapsed() );
#endif
			}
		}
		n = n.nextSibling();
		//widgetelement = widgetelement.nextSibling().toElement();
	}
#ifdef REPORTDESIGNER_DEBUG
	qDebug("loadSectionWidgets time: %i", t.elapsed() );
#endif
	return TRUE;
}

#include  <QTextStream>
QString NCReportDesignerResourceHandler::copy( )
{
	if ( !designArea )
		return QString::null;

	copying = TRUE;
	QString s;
	QTextStream ts( &s );

	ts << "<NCREPORT-SELECTION>" << CRLF;
	QWidgetList widgets = designArea->selectedWidgets();
	QWidgetList tmp( widgets );
	foreach( QWidget *w, widgets ) {
		if( qobject_cast<NCReportDesignerWidget*>(w) != 0 )
			break;
		NCReportDesignerWidget *dw = qobject_cast<NCReportDesignerWidget*>(w);
		saveWidget( dw, ts, 1 );
	}
	ts << "</NCREPORT-SELECTION>" << CRLF;

	return s;
}

bool NCReportDesignerResourceHandler::save( const QString & )
{
	return true;
}

bool NCReportDesignerResourceHandler::save( QIODevice *f )
{
	QTextStream t( f );
	t.setCodec( QTextCodec::codecForName( document->po.encoding.toLatin1() ) );

	t << "<?xml version=\"1.0\" encoding=\"" << document->po.encoding << "\"?>" << CRLF;
	t << "<NCReport" << CRLF;
	t << makeIndent(1) << "name=\"" << document->po.reportName << "\"" << CRLF;
	t << makeIndent(1) << "dataSource=\"" << (document->po.dataSource == ReportPageOptions::Database ? "DB" : "text") << "\"" << CRLF;

	if ( document->po.dataSource == ReportPageOptions::Textfile ) {
		t << makeIndent(1) << "resourceTextFile=\"" << document->po.resourceTextFile << "\"" << CRLF;
		t << makeIndent(1) << "textDataDelimiter=\"" << document->po.textDataDelimiter << "\"" << CRLF;
		t << makeIndent(1) << "textRowFilterRegExp=\"" << document->po.rowFilterRegExp << "\"" << CRLF;
	}

	t << makeIndent(1) << "encoding=\"" << document->po.encoding << "\"" << CRLF;
	t << makeIndent(1) << "pageSize=\"" << document->po.pageSize << "\"" << CRLF;
	t << makeIndent(1) << "orientation=\"" << (document->po.orient == ReportPageOptions::Portrait ? 'P' : 'L') << "\"" << CRLF;
	t << makeIndent(1) << "printerMode=\"" << document->po.printerMode << "\"" << CRLF;
	//t << makeIndent(1) << "columnCount=\"" << document->name << "\"" << CRLF;
	t << makeIndent(1) << "topMargin=\"" << document->po.topMargin << "\"" << CRLF;
	t << makeIndent(1) << "bottomMargin=\"" << document->po.bottomMargin << "\"" << CRLF;
	t << makeIndent(1) << "leftMargin=\"" << document->po.leftMargin << "\"" << CRLF;
	t << makeIndent(1) << "rightMargin=\"" << document->po.rightMargin << "\"" << CRLF;
	t << makeIndent(1) << "defaultFontName=\"" << document->po.defaultFontName << "\"" << CRLF;
	t << makeIndent(1) << "defaultFontSize=\"" << document->po.defaultFontSize << "\"" << CRLF;
	t << makeIndent(1) << "backcolor=\"" << document->po.backColor << "\"" << CRLF;
	t << makeIndent(1) << "masterAlias=\"" << document->po.masterAlias << "\"" << CRLF;
	t << makeIndent(1) << ">" << CRLF;
	t << makeIndent(1) << CRLF;
	t << "<queries>" << CRLF;
	{
		QMap<QString,ReportQuery>::ConstIterator it;
		for ( it = document->queries.begin(); it != document->queries.end(); ++it ) {
			t << makeIndent(1) << "<query alias=\"" << it.value().alias << "\">" << CRLF;
			t << makeIndent(2) << entitize(it.value().queryString, FALSE) << CRLF;
			t << makeIndent(1) << "</query>" << CRLF;
		}
	}
	t << "</queries>" << CRLF;
	t << "<variables>" << CRLF;
	{
		QMap<QString,ReportVariable>::ConstIterator it;
		for ( it = document->variables.begin(); it != document->variables.end(); ++it ) {
			t << makeIndent(1) << "<variable name=\"" << it.value().name << "\"";
			t << " type=\"" << it.value().type << "\"";
			t << " funcType=\"" << it.value().funcType << "\"";
			t << ">";
			t << it.value().field;
			t << "</variable>" << CRLF;
		}
	}
	t << "</variables>" << CRLF;
	//--------------------------------
	// page header
	//--------------------------------
	NCReportDesignerSection *s = document->sections["pheader"];
	t << "<pageHeader";
	t << " height=\"" << m->pixelToMeasure( s->designArea()->height() ) << "\"";
	t << ">" << CRLF;
	saveWidgetsOfSection( s, t, 1 );
	t << "</pageHeader>" << CRLF;
	//--------------------------------
	// page footer
	//--------------------------------
	s = document->sections["pfooter"];
	t << "<pageFooter";
	t << " height=\"" << m->pixelToMeasure( s->designArea()->height() ) << "\"";
	t << ">" << CRLF;
	saveWidgetsOfSection( s, t, 1 );
	t << "</pageFooter>" << CRLF;
	//--------------------------------
	// groups
	//--------------------------------
	t << "<groups>" << CRLF;
	{
		QMap<QString,ReportGroup>::ConstIterator it;
		for ( it = document->groups.begin(); it != document->groups.end(); ++it ) {
			//ReportGroup g = it.data();

			t << makeIndent(1) << "<group name=\"" << it.value().name << "\"";
			t << " groupExpression=\"" << it.value().groupExpression << "\"";
			t << " resetVariables=\"" << it.value().resetVariables << "\"";
			t << ">" << CRLF;
			// ------ GROUP HEADER
			s = it.value().header;
			t << makeIndent(2) << "<groupHeader";
			t << " height=\"" << m->pixelToMeasure( s->designArea()->height() ) << "\"";
			t << ">" << CRLF;
			saveWidgetsOfSection( s, t, 3 );
			t << makeIndent(2) << "</groupHeader>" << CRLF;
			// ------ GROUP FOOTER
			s = it.value().footer;
			t << makeIndent(2) << "<groupFooter";
			t << " height=\"" << m->pixelToMeasure( s->designArea()->height() ) << "\"";
			t << ">" << CRLF;
			saveWidgetsOfSection( s, t, 3 );
			t << makeIndent(2) << "</groupFooter>" << CRLF;
			// --------------------
			t << makeIndent(1) << "</group>" << CRLF;
		}
	}
	t << "</groups>" << CRLF;

	//--------------------------------
	// detail
	//--------------------------------
	s = document->sections["detail"];
	t << "<detail";
	t << " height=\"" << m->pixelToMeasure( s->designArea()->height() ) << "\"";
	t << ">" << CRLF;
	saveWidgetsOfSection( s, t, 1 );
	t << "</detail>" << CRLF;


	// FOOTER
	t << "</NCReport>" << CRLF;


	return true;
}

void NCReportDesignerResourceHandler::saveWidgetsOfSection( NCReportDesignerSection *s, QTextStream &ts, int indent )
{
	QWidgetList l = s->designArea()->findChildren<QWidget*>();
	//QObjectList *l = s->designArea()->queryList( "NCReportDesignerWidget" );
	if ( !l.isEmpty() ) {
		foreach( QWidget *o, l ) {
			NCReportDesignerWidget *dw = qobject_cast<NCReportDesignerWidget*>(o);
			if ( o->isVisible() )
				saveWidget( dw, ts, indent );
		}
	}
}


void NCReportDesignerResourceHandler::saveElement( QObject * , QTextStream &, int )
{
/*	if ( obj && obj->isWidgetType() && ( (QWidget*)obj )->isHidden() )
		return;

	if ( !::qt_cast<NCReportDesignerWidget*>(obj) )
		return;*/
}

void NCReportDesignerResourceHandler::paste( const QString &cb, QWidget *parent )
{
	if ( !designArea )
		return;

	pasteOffset = designArea->grid().x();
	//pasteOffset = 2;

	pasting = TRUE;
	QDomDocument doc;
	QString errorMsg;
	int errorLine;
	bool ok = doc.setContent( cb, TRUE, &errorMsg, &errorLine );

	if ( !ok ) {
		QMessageBox::warning( 0, QObject::tr("Designer error"), QObject::tr("Paste error occured. Cannot parse copied information.")+'\n'
				+errorMsg );
		return;
	}

	QDomElement widgetelement = doc.firstChild().toElement().firstChild().toElement();
	QWidgetList widgets;
	designArea->clearSelection( FALSE );

	/*
	<rectangle posX="0" posY="14" height="6" lineWidth="1" roundValue="8" lineColor="#0000FF"></rectangle>
	<label fontSize="8" posX="1" posY="15" alignmentH="left" forecolor="#0000FF">No.</label>
	<label fontSize="8" posX="7" posY="15" alignmentH="left" forecolor="#0000FF">Product no.</label>
	<label fontSize="8" posX="31" posY="15" alignmentH="left" forecolor="#0000FF">Product name</label>
	<label fontSize="8" posX="101" posY="15" alignmentH="right" width="19" forecolor="#0000FF">List price</label>
	<label fontSize="8" posX="121" posY="15" alignmentH="right" width="19" forecolor="#0000FF">Price II.</label>
	<label fontSize="8" posX="141" posY="15" alignmentH="right" width="19" forecolor="#0000FF">Price III.</label>
	<label fontSize="8" posX="161" posY="15" alignmentH="right" width="19" forecolor="#0000FF">Price IV.</label>

	*/
	//designArea->setPropertyShowingBlocked( TRUE );
	while ( !widgetelement.isNull() ) {

		//QWidget *w = (QWidget*)createObject( widgetelement, parent, 0 );
		QWidget *w = NCReportDesignerWidgetFactory::create( widgetelement, parent, 0, FALSE );
		if ( !w )
			continue;

		NCReportDesignerWidget *dw =0;
		if ( qobject_cast<NCReportDesignerWidget*>(w) != 0 )
			dw = qobject_cast<NCReportDesignerWidget*>(w);

		loadWidget( widgetelement, dw );
		widgets.append( w );

/*		int x = w->x() + designArea->grid().x();
		int y = w->y() + designArea->grid().y();
		if ( w->x() + dw->width() > parent->width() )
			x = QMAX( 0, parent->width() - w->width() );
		if ( w->y() + w->height() > parent->height() )
			y = QMAX( 0, parent->height() - w->height() );
		if ( x != w->x() || y != w->y() )
			w->move( x, y );*/

		widgetelement = widgetelement.nextSibling().toElement();
	}
	//designArea->setPropertyShowingBlocked( FALSE );
	//designArea->emitShowProperties();

	cmd_PasteCommand *cmd = new cmd_PasteCommand( QObject::tr( "Paste" ), designArea, widgets );
	designArea->commandHistory()->addCommand( cmd );
	cmd->execute();
}


void NCReportDesignerResourceHandler::loadWidget( QDomElement & e, NCReportDesignerWidget * w )
{
	double _fromX=0,_toX =0,_fromY=0,_toY=0;

	if ( e.hasAttribute("ftype") ) w->p.ftype = e.attribute("ftype");
	if ( e.hasAttribute("type") ) w->p.type = e.attribute("type");
	if ( e.hasAttribute("printWhen") ) w->p.printWhen = e.attribute("printWhen");
	if ( e.hasAttribute("embedString") ) w->p.embedString = e.attribute("embedString");
	if ( e.hasAttribute("callFunction") ) w->p.callFunction = e.attribute("callFunction");
	if ( e.hasAttribute("lookupClass") ) w->p.lookupClass = e.attribute("lookupClass");

	if ( e.hasAttribute("numDigitNo") ) w->p.numDigitNo = e.attribute("numDigitNo").toInt();
	if ( e.hasAttribute("numSeparation") ) w->p.numSeparation = (e.attribute("numSeparation")=="true");
	if ( e.hasAttribute("numSeparator") ) w->p.numSeparator = e.attribute("numSeparator").at(0).toLatin1();
	if ( e.hasAttribute("numDigitPoint") ) w->p.numDigitPoint = e.attribute("numDigitPoint").at(0).toLatin1();
	if ( e.hasAttribute("numBlankIfZero") ) w->p.numBlankIfZero = (e.attribute("numBlankIfZero")=="true");
	if ( e.hasAttribute("numFormat") ) w->p.numFormat = e.attribute("numFormat");
	if ( e.hasAttribute("dateFormat") ) w->p.dateFormat = e.attribute("dateFormat");

	if ( e.hasAttribute("posX") ) w->p._posX = e.attribute("posX").toDouble();
	if ( e.hasAttribute("posY") ) w->p._posY = e.attribute("posY").toDouble();
	if ( e.hasAttribute("fromX") ) _fromX = e.attribute("fromX").toDouble();
	if ( e.hasAttribute("fromY") ) _fromY = e.attribute("fromY").toDouble();
	if ( e.hasAttribute("toX") ) _toX = e.attribute("toX").toDouble();
	if ( e.hasAttribute("toY") ) _toY = e.attribute("toY").toDouble();
	if ( e.hasAttribute("width") ) w->p._width = e.attribute("width").toDouble();
	if ( e.hasAttribute("height") ) w->p._height = e.attribute("height").toDouble();
	if ( e.hasAttribute("fontName") ) w->p.fontName = e.attribute("fontName");
	if ( e.hasAttribute("fontSize") ) w->p.fontSize = e.attribute("fontSize").toInt();
	if ( e.hasAttribute("fontWeight") ) {
		QFont::Weight we = QFont::Normal;
		QString att = e.attribute("fontWeight");
		if (att == "light")
			we = QFont::Light;
		else if (att == "normal")
			we = QFont::Normal;
		else if (att == "demibold")
			we = QFont::DemiBold;
		else if (att == "bold")
			we = QFont::Bold;
		else if (att == "black")
			we = QFont::Black;
		w->p.fontWeight = we;
	}
	if ( e.hasAttribute("fontItalic") ) w->p.fontItalic = (e.attribute("fontItalic")=="true");
	if ( e.hasAttribute("fontUnderline") ) w->p.fontUnderline = (e.attribute("fontUnderline")=="true");
	if ( e.hasAttribute("fontStrikeOut") ) w->p.fontStrikeOut = (e.attribute("fontStrikeOut")=="true");
	if ( e.hasAttribute("rotation") ) w->p.rotation = e.attribute("rotation").toInt();
	if ( e.hasAttribute("alignmentH") ) {
		Qt::AlignmentFlag al = Qt::AlignLeft;
		QString att = e.attribute("alignmentH");
		if (att == "left")
			al = Qt::AlignLeft;
		else if (att == "right")
			al = Qt::AlignRight;
		else if (att == "center")
			al = Qt::AlignHCenter;

		w->p.alignmentH = al;
	}
	if ( e.hasAttribute("alignmentV") ) {
		Qt::AlignmentFlag al= Qt::AlignVCenter;
		QString att = e.attribute("alignmentV");

		if (att == "top")
			al = Qt::AlignTop;
		else if (att == "bottom")
			al = Qt::AlignBottom;
		else if (att == "center")
			al = Qt::AlignVCenter;
		w->p.alignmentV = al;
	}
	if ( e.hasAttribute("wordbreak") ) w->p.wordbreak = (e.attribute("wordbreak")=="true");
	if ( e.hasAttribute("richText") ) w->p.isRichText = (e.attribute("richText")=="true");
	if ( e.hasAttribute("dynamicHeight") ) w->p.dynamicHeight = (e.attribute("dynamicHeight")=="true");
	if ( e.hasAttribute("loadFromFile") ) w->p.loadFromFile = (e.attribute("loadFromFile")=="true");
	if ( e.hasAttribute("forecolor") ) w->p.forecolor = colorToString(e.attribute("forecolor"));
	if ( e.hasAttribute("backcolor") ) w->p.forecolor = colorToString(e.attribute("backcolor"));
	if ( e.hasAttribute("fillColor") ) w->p.fillColor = colorToString(e.attribute("fillColor"));
	if ( e.hasAttribute("lineColor") ) w->p.lineColor = colorToString(e.attribute("lineColor"));
	if ( e.hasAttribute("lineWidth") ) w->p.lineWidth = e.attribute("lineWidth").toInt();
	if ( e.hasAttribute("lineStyle") ) {
		Qt::PenStyle ps = Qt::SolidLine;
		QString ls = e.attribute("lineStyle");

		if (ls == "solid")
			ps = Qt::SolidLine;
		else if (ls == "dash")
			ps = Qt::DashLine;
		else if (ls == "dot")
			ps = Qt::DotLine;
		else if (ls == "dashdotdot")
			ps = Qt::DashDotDotLine;
		else if (ls == "dashdot")
			ps = Qt::DashDotLine;
		else if (ls == "nopen")
			ps = Qt::NoPen;

		w->p.lineStyle = ps;
	}
	if ( e.hasAttribute("fillStyle") ) {
		w->p.fillStyle = WProperty::transparent;
		if ( e.attribute("fillStyle") == "filled" )
			w->p.fillStyle = WProperty::filled;
	}
	if ( e.hasAttribute("resource") ) {
		// image resource
		w->p.resource = e.attribute("resource");
	}
	if ( w->p.fontName.isEmpty() && !document->po.defaultFontName.isEmpty() )
		w->p.fontName = document->po.defaultFontName;

	w->p.text = e.text();

	//------------------------
	// Geometry settings
	//------------------------
	QRect r;
	int coordX = m->measureToPixel( w->p._posX )+pasteOffset;
	int coordY = m->measureToPixel( w->p._posY )+pasteOffset;
/*	if ( pasteOffset == -1 ) {
		// copy - paste to the topleft corner
		coordX = 0;
		coordY = 0;
	}*/

	if ( e.tagName() == "line" ) {
		r.setTopLeft( QPoint( m->measureToPixel(_fromX)+pasteOffset, m->measureToPixel(_fromY)+pasteOffset ) );
		//r.setX( coordX );
		//r.setY( coordY );
		if ( _fromY==_toY ) {	// horizontal
			w->setMaximumHeight( w->p.lineWidth );
			r.setHeight( w->p.lineWidth );
			r.setWidth( m->measureToPixel(_toX-_fromX) );
		} else {
			w->setMaximumWidth( w->p.lineWidth );
			r.setWidth( w->p.lineWidth );
			r.setHeight( m->measureToPixel(_toY-_fromY) );
		}
	} else if ( e.tagName() == "label" || e.tagName() == "field" ) {

		if ( w->p._width<=0 || w->p._height<=0 )
			setWidgetOptimalSizeForFont( w, w->p._width<=0, w->p._height<=0 );

		r.setRect( coordX, coordY, m->measureToPixel( w->p._width ), m->measureToPixel( w->p._height ) );

	} else if ( e.tagName() == "rectangle" || e.tagName() == "ellipse" ) {
		int wi = 0;
		if ( w->p._width<=0 )
			wi = designArea->width();
		else
			wi = m->measureToPixel( w->p._width );

		r.setRect( coordX, coordY, wi, m->measureToPixel( w->p._height ) );

	} else if ( e.tagName() == "pixmap" || e.tagName() == "image" ) {
		r.setRect( coordX, coordY, m->measureToPixel( w->p._width ), m->measureToPixel( w->p._height ) );
	} else
		r.setRect( coordX, coordY, m->measureToPixel( w->p._width ), m->measureToPixel( w->p._height ) );

	//designArea->checkGeometry( r );
	w->setGeometry( r );
}

void NCReportDesignerResourceHandler::setWidgetOptimalSizeForFont( NCReportDesignerWidget *w, bool setWidth, bool setHeight )
{
	QFont f;
	if ( w->p.fontName.isEmpty() )
		f.setFamily( w->p.fontName );

	if ( w->p.fontSize == 0 )
		f.setPointSize( 10 );
	else
		f.setPointSize( w->p.fontSize );

	f.setWeight( w->p.fontWeight );
	f.setItalic( w->p.fontItalic );
	f.setUnderline( w->p.fontUnderline );
	f.setStrikeOut( w->p.fontStrikeOut );
	QFontMetrics fm(f);
	if ( setWidth )
		w->p._width = m->pixelToMeasure( fm.width( w->p.text )+ TRIM_DEFAULT_TEXTWIDTH );
	if ( setHeight )
		w->p._height = m->pixelToMeasure( fm.height() + TRIM_DEFAULT_TEXTHEIGHT );

}

void NCReportDesignerResourceHandler::saveWidget( NCReportDesignerWidget *w, QTextStream & ts, int indent )
{
	//Measurement *m = designArea->measurement();

	//const char qm='\"';
	// tag
	ts << makeIndent( indent ) << "<" << w->tagname;
	// properties

	if ( w->useFType )
		ts << " ftype=\"" << w->p.ftype << "\"";
	if ( w->useType &&  w->p.type!="text")
		ts << " type=\"" << w->p.type << "\"";
	if ( w->useSize )
		ts << " posX=\"" << m->pixelToMeasureStr(w->x()) << "\" posY=\"" << m->pixelToMeasureStr(w->y()) << "\" width=\"" << m->pixelToMeasureStr(w->width()) << "\" height=\"" << m->pixelToMeasureStr(w->height()) << "\"";
	if ( w->usePointFromTo ) {
		if ( w->orient == Qt::Horizontal )
			ts << " fromX=\"" << m->pixelToMeasureStr(w->x()) << "\" fromY=\"" << m->pixelToMeasureStr(w->y()) << "\" toX=\"" << m->pixelToMeasureStr(w->x()+w->width()) << "\" toY=\"" << m->pixelToMeasureStr(w->y()) << "\"";
		else
			ts << " fromX=\"" << m->pixelToMeasureStr(w->x()) << "\" fromY=\"" << m->pixelToMeasureStr(w->y()) << "\" toX=\"" << m->pixelToMeasureStr(w->x()) << "\" toY=\"" << m->pixelToMeasureStr(w->y()+w->height()) << "\"";
	}
	if ( w->useLineWidth )
		ts << " lineWidth=\"" << w->p.lineWidth << "\"";
	if ( w->useLineStyle ) {
		QString ls;
		switch ( w->p.lineStyle ) {
			case Qt::SolidLine: ls="solid"; break;
			case Qt::DashLine: ls="dash"; break;
			case Qt::DotLine: ls="dot"; break;
			case Qt::DashDotLine: ls="dashdot"; break;
			case Qt::DashDotDotLine: ls="dashdotdot"; break;
			case Qt::NoPen: ls="nopen"; break;
			default: ls="";
		}
		ts << " lineStyle=\"" << ls << "\"";
	}
	if ( w->useFontSize && w->p.fontSize != document->po.defaultFontSize )
		ts << " fontSize=\"" << w->p.fontSize << "\"";
	if ( w->useFontWeight && w->p.fontWeight==QFont::Bold ) {
		ts << " fontWeight=\"bold\"";
	}
	if ( w->useFontName && !w->p.fontName.isEmpty() && w->p.fontName != document->po.defaultFontName )
		ts << " fontName=\"" << w->p.fontName << "\"";
	if ( w->useFontItalic && w->p.fontItalic )
		ts << " fontItalic=\"" << (w->p.fontItalic ? "true" : "false") << "\"";
	if ( w->useFontStrikeOut && w->p.fontStrikeOut )
		ts << " fontStrikeOut=\"" << (w->p.fontStrikeOut ? "true" : "false") << "\"";
	if ( w->useFontUnderline && w->p.fontUnderline )
		ts << " fontUnderline=\"" << (w->p.fontUnderline ? "true" : "false") << "\"";
	if ( w->useAlignment ) {
		QString s;
		if ( w->p.alignmentH != Qt::AlignLeft ) {
			switch ( w->p.alignmentH ) {
				case Qt::AlignLeft: s="left"; break;
				case Qt::AlignRight: s="right"; break;
				case Qt::AlignHCenter: s="center"; break;
				default: break;
			}
			ts << " alignmentH=\"" << s << "\"";
		}
		if ( w->p.alignmentV != Qt::AlignTop ) {
			switch ( w->p.alignmentV ) {
				case Qt::AlignTop: s="top"; break;
				case Qt::AlignBottom: s="bottom"; break;
				case Qt::AlignVCenter: s="center"; break;
				default: break;
			}
			ts << " alignmentV=\"" << s << "\"";
		}
	}
	if ( w->useWordBreak && w->p.wordbreak )
		ts << " wordbreak=\"" << (w->p.wordbreak ? "true" : "false") << "\"";
	if ( w->useRichText && w->p.isRichText )
		ts << " richText=\"" << (w->p.isRichText ? "true" : "false") << "\"";
	if ( w->useDynamicHeight && w->p.dynamicHeight )
		ts << " dynamicHeight=\"" << (w->p.dynamicHeight ? "true" : "false") << "\"";
	if ( w->useLoadFromFile && w->p.loadFromFile )
		ts << " loadFromFile=\"" << (w->p.loadFromFile ? "true" : "false") << "\"";
	//if ( useText )
	//	ts << " text=\"" << text << "\"";
	if ( w->usePrintWhen && !w->p.printWhen.isEmpty() )
		ts << " printWhen=\"" << w->p.printWhen << "\"";
	if ( w->useRotation && w->p.rotation>0 )
		ts << " rotation=\"" << w->p.rotation << "\"";
	if ( w->useLineColor )
		ts << " lineColor=\"" << colorToString(w->p.lineColor) << "\"";
	if ( w->useFillColor )
		ts << " fillColor=\"" << colorToString(w->p.fillColor) << "\"";
	if ( w->useForeColor )
		ts << " forecolor=\"" << colorToString(w->p.forecolor) << "\"";
	if ( w->useBackColor )
		ts << " backcolor=\"" << colorToString(w->p.backcolor) << "\"";
	if ( w->useFillStyle )
		ts << " fillStyle=\"" << (w->p.fillStyle==WProperty::transparent ? "transparent" : "filled") << "\"";
	if ( w->useResource )
		ts << " resource=\"" << w->p.resource << "\"";

	if ( w->useDataFormat && w->p.type == "numeric" ) {
		if ( w->p.numBlankIfZero )
			ts << " numBlankIfZero=\"" << "true" << "\"";
		if ( w->p.numDigitNo >= 0 )
			ts << " numDigitNo=\"" << w->p.numDigitNo << "\"";
		if ( w->p.numSeparation )
			ts << " numSeparation=\"" << "true" << "\"";
		if ( w->p.numSeparator != ' ' )
			ts << " numSeparator=\"" << w->p.numSeparator << "\"";
		if ( w->p.numDigitPoint != '.' )
			ts << " numDigitPoint=\"" << w->p.numDigitPoint << "\"";
		if ( !w->p.numFormat.isEmpty() )
			ts << " numFormat=\"" << w->p.numFormat << "\"";
	}
	if ( w->useDataFormat && !w->p.dateFormat.isEmpty() )
		ts << " dateFormat=\"" << w->p.dateFormat << "\"";
	if ( !w->p.embedString.isEmpty() )
		ts << " embedString=\"" << w->p.embedString << "\"";
	if ( !w->p.callFunction.isEmpty() )
		ts << " callFunction=\"" << w->p.callFunction << "\"";
	if ( !w->p.lookupClass.isEmpty() )
		ts << " lookupClass=\"" << w->p.lookupClass << "\"";

	// tag end
	ts << ">";
	if ( w->useText ) {
		//if ( w->p.text.isEmpty() )
		//	ts << w->p.resource;	// pixmap/image
		//else
		ts << entitize( w->p.text );
	}
	ts << "</" << w->tagname << ">\r\n" ;
}





QColor NCReportDesignerResourceHandler::stringToColor( const QString &colorstring )
{
	QColor color;
	bool ok;
	colorstring.right(6).toInt( &ok, 16 );
	if ( ok && colorstring.startsWith("#") && colorstring.length() == 7 ) {

		color = QColor( colorstring.mid(1,2).toInt( &ok, 16),
						colorstring.mid(3,2).toInt( &ok, 16),
						colorstring.mid(5,2).toInt( &ok, 16) );

	}
	return color;
}

QString NCReportDesignerResourceHandler::colorToString( const QColor & col )
{
	QString webcol;
	if ( col.isValid() ) {                 // got a file name
		webcol.sprintf( "#%02X%02X%02X", col.red(), col.green(), col.blue() );
	}
	return webcol;
}

QString NCReportDesignerResourceHandler::entitize( const QString & s, bool isAttrib )
{
	QString s2 = s;
	s2 = s2.trimmed();
	s2 = s2.replace( "&", "&amp;" );
	s2 = s2.replace( ">", "&gt;" );
	s2 = s2.replace( "<", "&lt;" );
	if ( isAttrib ) {
		s2 = s2.replace( "\"", "&quot;" );
		s2 = s2.replace( "'", "&apos;" );
	}
	return s2;
}

QString NCReportDesignerResourceHandler::makeIndent( int indent )
{
	QString s;
	s.fill( ' ', indent * 4 );
	return s;
}

void NCReportDesignerResourceHandler::removeXMLComments( QString & doc )
{
	if ( doc.contains("<!--") ==0 )
		return;

	doc.replace( QRegExp("<!--([^<]*)-->"), "" );
}






