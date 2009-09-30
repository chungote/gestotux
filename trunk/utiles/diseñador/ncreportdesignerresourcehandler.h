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
#ifndef NCREPORTDESIGNERFILEHANDLER_H
#define NCREPORTDESIGNERFILEHANDLER_H

#include <QString>
#include <QColor>
#include <QTextStream>

class NCReportDesignerWidget;
class NCReportDesignerDesignArea;
class NCReportDesignerDocument;
class NCReportDesignerSection;
class QObject;
class QWidget;
class QDomElement;
class Measurement;
class QIODevice;

class NCReportDesignerResourceHandler
{
public:
    NCReportDesignerResourceHandler();
    ~NCReportDesignerResourceHandler();

	bool load( QIODevice *file );
	QString copy();

	bool save( const QString& filename);
	bool save( QIODevice* );
	void paste( const QString &cb, QWidget *parent );
	void setDesignArea( NCReportDesignerDesignArea* da );
	void setSection( NCReportDesignerSection* se );
	void setDocument( NCReportDesignerDocument* doc ) { document = doc; }
	void setMeasurement( Measurement* mmnt ) { m = mmnt; }

	static QString makeIndent( int indent );
	static QString entitize( const QString &s, bool isAttrib = FALSE );

	QString lastLoadError();
	void removeXMLComments( QString& );
private:
	NCReportDesignerDesignArea *designArea;
	NCReportDesignerDocument *document;
	NCReportDesignerSection *section;
	bool copying, pasting;
	Measurement* m;
	int pasteOffset;
	int errorline, errorcol;
	QString loadErrorMsg;

	QColor stringToColor( const QString & );
	QString colorToString( const QColor& );

	bool loadReportOptions( QDomElement& e );
	bool loadQueries( QDomElement& e );
	bool loadVariables( QDomElement& e );
	bool loadPageHeader( QDomElement& e );
	bool loadPageFooter( QDomElement& e );
	bool loadGroups( QDomElement& e );
	bool loadDetail( QDomElement& e );
	/*!Load iteration of a section containing widgets*/
	bool loadSectionWidgets( QDomElement &e );
	void loadWidget( QDomElement &e, NCReportDesignerWidget *w );

	void saveElement( QObject *obj, QTextStream &ts, int indent );
	void saveWidget( NCReportDesignerWidget *w, QTextStream & ts, int indent );
	void saveWidgetsOfSection( NCReportDesignerSection *s, QTextStream &ts, int indent );

	void setWidgetOptimalSizeForFont( NCReportDesignerWidget *w, bool setWidth, bool setHeight );
};

#endif
