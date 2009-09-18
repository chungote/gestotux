/***************************************************************************
 *   Copyright (C) 2006 by Szabó Norbert   *
 *   nszabo@helta.hu   *
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
#ifndef NCREPORTDESIGNERDOCUMENT_H
#define NCREPORTDESIGNERDOCUMENT_H

#include "measurement.h"

#include <QFrame>
#include <QWidget>
#include <QHash>
#include <QMap>
#include <QPixmap>
/*
#include <qwidget.h>
#include <qframe.h>
#include <qdict.h>
#include <qpixmap.h>*/

/**
	@author Norbert Szabo <nszabo@helta.hu>
 */

class QLabel;
class NCReportDesignerWindow;
class NCReportDesignerDesignArea;
class NCReportDesignerRuler;
class NCReportDesignerSection;
class ReportQuery;
class ReportVariable;
class QVBoxLayout;
class QScrollView;
class Measurement;



/*!
Resizer bar between sections
*/
class NCReportDesignerResizeBar : public QWidget
{
	Q_OBJECT
public:
	NCReportDesignerResizeBar( QWidget * parent = 0 );
	virtual ~NCReportDesignerResizeBar();

signals:
	void barDragged(int d);

protected:
	virtual void paintEvent( QPaintEvent* );
	void mouseMoveEvent(QMouseEvent * e);
};

/*!
Ruler
 */
class NCReportDesignerRuler : public QWidget
{
	Q_OBJECT
public:
	//enum Direction { Horizontal, Vertical };
	//enum Measure { Metric, English }

	NCReportDesignerRuler( Qt::Orientation ori, QWidget *parent = 0 );
	~NCReportDesignerRuler();
	void setMeasurement( Measurement* msr ) { m = msr; }
	void setScaleStartPoint( int p );

	//void setMeasurementType( Measure );

public slots:
/*	void setZoomLevel( double );
	void changeZoomLevelBy( double );*/

protected:
	virtual void paintEvent( QPaintEvent* );
private:
	int scStart;
	NCReportDesignerResizeBar *rbar;
	Qt::Orientation orient;
	//Measurement::Measure msr;
	Measurement *m;
// 	double zoomlevel;
};


class NCReportDesignerSectionTitle : public QWidget
{
public:
	NCReportDesignerSectionTitle( QWidget * parent, const char* name=0 );
	virtual ~NCReportDesignerSectionTitle();

	void setText(const QString& t) { text = t; }
	void setPixmap( const QPixmap& p ) { pm = p; }
protected:
	virtual void paintEvent( QPaintEvent* );
private:
	int topMargin;
	QPixmap pm;
	QString text;
};

class NCReportDesignerSection : public QWidget
{
	Q_OBJECT
public:
	enum SectionType { PageHeader, PageFooter, GroupHeader, GroupFooter, Detail };

	NCReportDesignerSection( NCReportDesignerWindow * mwin,  QWidget * parent, const QString& cap, const char* name=0 );
	NCReportDesignerSection( SectionType t, NCReportDesignerWindow * mwin, QWidget * parent, const QString& cap, const char* name=0 );
	virtual ~NCReportDesignerSection();

	void setType( SectionType t );
	void setTitle(const QString & s, const QPixmap& );
	void setTitle(const QString & s );
	NCReportDesignerDesignArea *designArea();
	NCReportDesignerRuler* leftRuler() { return ruler; }
	void setMeasurement( Measurement* msr );
	void setGroupSettings( const QString & expr, const QString & rvars );
	void setWidth( double dw );
	void setHeight( double dh );
	void setFooterSection( NCReportDesignerSection* );
	NCReportDesignerSection *getFooterSection();
	NCReportDesignerSectionTitle *Title();

protected slots:
	void resizeBarDragged(int d);

protected:
	NCReportDesignerSectionTitle *title;
	NCReportDesignerWindow* mainwindow;
	/*!The footer pair (pointer) of this section*/
	NCReportDesignerSection *footerSection;
	QFrame *titleFrame;
	//QLabel *lblTitle;
	SectionType type;
	NCReportDesignerRuler* ruler;
	NCReportDesignerDesignArea *designarea;
	NCReportDesignerResizeBar *rbar;
	Measurement *m;
	QString caption;
	// group properties
	QString groupExpr;
	QString resetVars;

	void init();

	//ReportGridOptions * grid;
};

class ReportQuery
{
public:
	ReportQuery()
	{
		master = false;
	}
	ReportQuery( const QString & ali, const QString & qry )
	{
		alias = ali;
		queryString =qry;
		queryString.replace( '\t',"");
		master = false;
	}

	void setQuery( const QString & ali, const QString & qry, bool m=false )
	{
		alias = ali;
		queryString =qry;
		master = m;
	}

	QString queryString;
	QString alias;
	bool master;
};


class ReportVariable
{
public:
	ReportVariable()
	{
	}
	ReportVariable( const QString & _name, const QString & _type, const QString & _ftype )
	{
		name = _name;
		type = _type;
		funcType = _ftype;
	}
	QString name;
	QString type;
	QString funcType;
	QString field;
};


class ReportGroup
{
public:
	ReportGroup()
	{
		header =NULL;
		footer =NULL;
	}
	ReportGroup( const QString & _name, const QString & gexp, const QString & resetvars )
	{
		name = _name;
		groupExpression = gexp;
		resetVariables = resetvars;
	}
	void operator=(const ReportGroup &g )
	{
		name = g.name;
		groupExpression = g.groupExpression;
		resetVariables = g.resetVariables;
		header = g.header;
		footer = g.footer;
	}

	QString name;
	QString groupExpression;
	QString resetVariables;
	NCReportDesignerSection *header;
	NCReportDesignerSection *footer;
};

class ReportPageOptions
{
public:
	enum Orientation { Portrait, Landscape };
	enum DataSource { Database, Textfile };

	ReportPageOptions() {
		encoding = "utf8";
		reportName="unnamed";
		pageSize = "A4";
		pageWidth = 210.0;
		pageHeight = 0.0;
		printerMode = "normal";
		columnCount = 0;
		topMargin = 20.0;
		bottomMargin = 20.0;
		leftMargin=20.0;
		rightMargin=20.0;
	//defaultFontName = "Arial";
		defaultFontSize =10;
		backColor = "#FFFFFF";
		orient = Portrait;
		dataSource = Database;
	}

	QString encoding;
	QString reportName;
	QString pageSize;
	double pageWidth, pageHeight;
	QString printerMode;
	int columnCount;
	double topMargin, bottomMargin, leftMargin, rightMargin;
	QString defaultFontName;
	int defaultFontSize;
	QString backColor;
	QString masterAlias;
	Orientation orient;

	DataSource dataSource;
	QString resourceTextFile;
	QString textDataDelimiter;
	QString rowFilterRegExp;
};

/*!
	Designer document.
 */
class NCReportDesignerDocument : public QWidget
{
Q_OBJECT
public:
	NCReportDesignerDocument( NCReportDesignerWindow *main, QWidget *parent = 0, const char* name=0, int wflags =0 );
	~NCReportDesignerDocument();

	enum RulerPos { Top, Left };

	//NCReportDesignerSection *section() { return sect1; }
	NCReportDesignerRuler *rulerTop() { return rulertop; }
	NCReportDesignerRuler *rulerLeft() { return rulerleft; }
	QWidget* sectionContainer() { return sectioncontainer; }
	QVBoxLayout* sectionContainerLayout() { return laySC; }
	Measurement *measurement();
	NCReportDesignerDesignArea *activeDesignArea();
	NCReportDesignerSection* addSection( NCReportDesignerSection::SectionType,
										 const QString& sname, const QString& caption,
										 double pWidth=210.0, double pHeight=8.0, QWidget* after=0 );
	NCReportDesignerSection* sectionByName( const QString& );
	void removeSection( const QString& sname );
	void addQuery( const ReportQuery& );
	void removeQuery( const QString& alias );
	void addVariable( const ReportVariable& );
	void removeVariable( const QString& varname );
	void addGroup( ReportGroup& );
	void removeGroup( const QString& gname );
	void updateGroup( const ReportGroup& );
	/*!Set width in mm/inch */
	void setPageWidth( double pwidth );
	void setPageSize( NCReportDesignerSection *sect=0 );
	void updateSections();

	bool load( const QString& fn );
	void save();
	void saveAs();
	void setModified(bool);
	bool isModified();
	double defaultPageWidth();

	NCReportDesignerSection* addPageHeader();
	NCReportDesignerSection* addPageFooter();
	NCReportDesignerSection* addDetail();

	friend class NCReportDesignerResourceHandler;
	friend class diaQuery;
	friend class diaGroup;
	friend class diaVariable;
	friend class diaPage;
	friend class NCReportDesignerWidgetSetDialog;

signals:
	void message(const QString&, int );
	void documentModified();

protected:
	QHash<QString,NCReportDesignerSection> sections;
	/*!Map of queries*/
	QMap<QString,ReportQuery> queries;
	/*!Map of variables*/
	QMap<QString,ReportVariable> variables;
	/*!Map of groups*/
	QMap<QString,ReportGroup> groups;
	//NCReportDesignerSection *sect1, *sect2, *sect3;
	NCReportDesignerRuler *rulertop, *rulerleft;
	QWidget *sectioncontainer;
	QScrollView *sv;
	QVBoxLayout *laySC;
	QString filename;
	NCReportDesignerWindow *mainwindow;
	Measurement *msrment;
	/*!Save the section pointer which after the group insertion must be done*/
	NCReportDesignerSection *sectionNextGroupAfter;

	void closeEvent( QCloseEvent *e );
private:
	// page properties
	ReportPageOptions po;
	bool modified;

};


#endif
