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
#include "ncreportdesignerdocument.h"
#include "ncreportdesignerdesignarea.h"
#include "ncreportdesignerwindow.h"
#include "ncreportdesignerresourcehandler.h"


#include <QLabel>
#include <QPainter>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QStyle>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QScrollArea>

#define RULERWEIGHT	28
#define DEFAULT_PAGE_WIDTH	210.0

///////////////////////////////////
// Workplace
///////////////////////////////////
NCReportDesignerDocument::NCReportDesignerDocument( NCReportDesignerWindow *main, QWidget *parent, const char* name, Qt::WindowFlags wflags )
	: QWidget( parent, wflags )
{
	this->setObjectName( name );
	mainwindow = main;
	sectionNextGroupAfter = 0;
	modified = FALSE;

	QGridLayout *grid = new QGridLayout( this );
	grid->setMargin(0);
	grid->setSpacing(0);

/*	rulertop = new NCReportDesignerRuler( Qt::Horizontal, this );
	rulertop->setScaleStartPoint( RULERWEIGHT );
	grid->addWidget( rulertop, 0,1 );*/

	//QScrollArea *sa = new QScrollArea( this );
	//sa->setBackgroundRole(QPalette::Dark);
	//--------------------------------------------
	// Measurement
	//--------------------------------------------
	msrment = new Measurement();
	//rulerleft->setMeasurement( msrment );

	sv = new QScrollArea( this );
	QPalette p = sv->widget()->palette();
	p.setColor( QPalette::Background, QColor( 160,160,160) );
	sv->widget()->setPalette( p );
	//sv->setMargins(0,0,0,0);

	sectioncontainer = new QWidget( sv->widget() );
	laySC = new QVBoxLayout( sectioncontainer );
	laySC->setMargin(0);
	laySC->setSpacing(0);
	sectioncontainer->resize(640,480);
	sectioncontainer->move( 0, RULERWEIGHT );
	//sectioncontainer->resize( msrment->measureToPixel( 210.0 ), 480 );

	//--------------------------------------------
	// Add top ruler
	//--------------------------------------------
	rulertop = new NCReportDesignerRuler( Qt::Horizontal, sectioncontainer );
	rulertop->setScaleStartPoint( RULERWEIGHT );
	rulertop->setMeasurement( msrment );
	laySC->addWidget( rulertop );

	//--------------------------------------------
	// Test sections
	//--------------------------------------------


	//laySC->addStretch( 5 );

	//sect1->setFixedSize( msrment->measureToPixel( 210.0 ), 50 );	//test


	sv->setWidget( sectioncontainer );
	//sv->addChild(sectioncontainer,0,0);
	grid->addWidget( sv, 1,1 );
	//grid->addWidget( sectioncontainer, 1,1 );
	connect( this, SIGNAL(destroyed()), main, SLOT(refreshTools()) );
}

// NCReportDesignerDocument::NCReportDesignerDocument( QWidget* parent, const char* name, int wflags )
// 	: QMainWindow( parent, name, wflags )
// {
// 	mmovie = 0;
// 	medit = new QTextEdit( this );
// 	setFocusProxy( medit );
// 	setCentralWidget( medit );
// }

NCReportDesignerDocument::~NCReportDesignerDocument()
{
	delete msrment;
}

void NCReportDesignerDocument::closeEvent( QCloseEvent *e )
{
	if ( isModified() ) {
		switch( QMessageBox::warning( this, "Save Changes",
				tr("Save changes to %1?").arg( windowTitle() ),
				tr("Yes"), tr("No"), tr("Cancel") ) ) {
					case 0:
					{
						save();
						if ( !filename.isEmpty() )
							e->accept();
						else
							e->ignore();
					}
					break;
					case 1:
						e->accept();
						break;
					default:
						e->ignore();
						break;
				}
	} else {
		e->accept();
	}
}

bool NCReportDesignerDocument::load( const QString& fn )
{
	filename  = fn;
	QFile f( filename );
	if ( !f.open( QFile::ReadOnly ) )
		return FALSE;

	NCReportDesignerResourceHandler r;
	r.setDocument( this );
	r.setMeasurement( msrment );
	qApp->setOverrideCursor( QCursor( Qt::WaitCursor) );
	//setUpdatesEnabled( FALSE );
	bool ok =  r.load( &f );
	//setUpdatesEnabled( TRUE );
	qApp->restoreOverrideCursor();

	if ( ok ) {
		setWindowTitle( filename );
		emit message( QString("Loaded document %1").arg(filename), 2000 );
	} else {
		emit message( r.lastLoadError(), 2000 );
		QMessageBox::warning( this, tr("Load error"), r.lastLoadError() );
	}
	return ok;
}

void NCReportDesignerDocument::save()
{
	if ( filename.isEmpty() ) {
		saveAs();
		return;
	}

	QString text;	// = medit->text();
	QFile f( filename );
	if ( !f.open( QFile::WriteOnly ) ) {
		emit message( QString("Could not write to %1").arg(filename),
					  2000 );
		return;
	}

	qApp->setOverrideCursor( QCursor( Qt::WaitCursor) );
	NCReportDesignerResourceHandler r;
	r.setDocument( this );
	r.setMeasurement( msrment );
	bool ok =  r.save( &f );
	f.close();
	qApp->restoreOverrideCursor();

	if ( ok ) {
		setWindowTitle( filename );
		emit message( tr( "File %1 saved" ).arg( filename ), 2000 );
		setModified( FALSE );
	} else {
		QMessageBox::warning( this, tr("Save error"), tr("Could not save file %1!").arg(filename) );
	}

}

void NCReportDesignerDocument::saveAs()
{
	QString fn = QFileDialog::getSaveFileName( this, tr( "Save as" ), filename  );
	if ( !fn.isEmpty() ) {
		if ( !fn.contains('.') )
			fn+=".xml";
		filename = fn;
		save();
	} else {
		emit message( tr("Saving aborted"), 2000 );
	}
}

void NCReportDesignerDocument::setModified( bool set )
{
	modified = set;
	emit documentModified();
}

bool NCReportDesignerDocument::isModified( )
{
	return modified;
}

Measurement * NCReportDesignerDocument::measurement( )
{
	return msrment;
}

double NCReportDesignerDocument::defaultPageWidth( )
{
	return DEFAULT_PAGE_WIDTH - po.leftMargin - po.rightMargin;
}

NCReportDesignerDesignArea * NCReportDesignerDocument::activeDesignArea( )
{
	foreach( NCReportDesignerSection *it, sections.values() ) {
		if ( it->designArea()->hasFocus() )
			return it->designArea();
	}
	return 0;
}

void NCReportDesignerDocument::setPageWidth( double pwidth )
{
	foreach( NCReportDesignerSection *it, sections.values() ) {
		it->setWidth( pwidth - po.leftMargin - po.rightMargin );
	}
}

void NCReportDesignerDocument::updateSections()
{
	foreach( NCReportDesignerSection *it, sections.values() ) {
		it->update();
	}
}

NCReportDesignerSection* NCReportDesignerDocument::addSection( NCReportDesignerSection::SectionType st, const QString & sname, const QString& caption, double pWidth, double pHeight, QWidget* after )
{
	NCReportDesignerSection *s =0;
	const char* n = sname.toLatin1();
	int wIndex =-1;
	if ( after )
		wIndex = laySC->indexOf( after )+1;

	s = new NCReportDesignerSection( st, mainwindow, sectioncontainer, caption, n );
	s->setMeasurement( msrment );
	s->designArea()->setParentDocument( this );
	s->designArea()->setParentSection( s );
	s->setWidth( pWidth );
	s->setHeight( pHeight );
	//s->designArea()->setFixedWidth( msrment->measureToPixel( pWidth ) );	// initial (fixed) width
	//s->designArea()->setMinimumHeight( msrment->measureToPixel(pHeight) );	// initial height
	connect( mainwindow, SIGNAL(currentToolChanged()), s->designArea(), SLOT(toolChanged()) );
	laySC->insertWidget( wIndex, s );
	sections.insert( sname, s );

	return s;
}


void NCReportDesignerDocument::removeSection( const QString & sname )
{
	NCReportDesignerSection *s = sections[sname];
	if ( s ) {
		s->hide();
		sections.remove(sname);
		delete s;
	}
}

void NCReportDesignerDocument::addQuery( const ReportQuery & q )
{
	queries[q.alias]=q;
}

void NCReportDesignerDocument::removeQuery( const QString & alias )
{
	queries.remove(alias);
}

void NCReportDesignerDocument::addVariable( const ReportVariable & var )
{
	variables[var.name] = var;
}

void NCReportDesignerDocument::removeVariable( const QString & varname )
{
	variables.remove(varname);
}
void NCReportDesignerDocument::addGroup( ReportGroup & group )
{
	// Header
	group.header = addSection( NCReportDesignerSection::GroupHeader, group.name+"_h", tr("Group header")+": "+group.name,
											  defaultPageWidth(), 15.0, sectionNextGroupAfter );
	sectionNextGroupAfter = group.header; // save as last g.header

	// Footer
	group.footer = addSection( NCReportDesignerSection::GroupFooter, group.name+"_f", tr("Group footer")+": "+group.name,
											  defaultPageWidth(), 15.0, sections["detail"] );
	group.header->setFooterSection( group.footer );	// save link to footer

	groups[group.name] = group;
	// returns the header

}
void NCReportDesignerDocument::removeGroup( const QString & gname )
{
	ReportGroup group = groups[gname];
	if ( group.name.isEmpty() )
		return;

	delete group.header;
	delete group.footer;

	groups.remove(gname);
	if ( groups.empty() )
		return;

	QMap<QString,ReportGroup>::ConstIterator it;
	it = groups.end();
	it--;
	sectionNextGroupAfter = it.value().header;		// last header
}

void NCReportDesignerDocument::updateGroup( const ReportGroup &g )
{
}

NCReportDesignerSection* NCReportDesignerDocument::addPageHeader()
{
	NCReportDesignerSection *s = addSection( NCReportDesignerSection::PageHeader, "pheader", tr("Page header"), defaultPageWidth(), 15.0 );
	sectionNextGroupAfter = s;
	return s;
}
NCReportDesignerSection* NCReportDesignerDocument::addPageFooter()
{
	NCReportDesignerSection *s = addSection( NCReportDesignerSection::PageFooter, "pfooter", tr("Page footer"), defaultPageWidth(), 15.0 );
	sections["pheader"]->setFooterSection( s );
	return s;
}
NCReportDesignerSection* NCReportDesignerDocument::addDetail()
{
	NCReportDesignerSection *s = addSection( NCReportDesignerSection::Detail, "detail", tr("Detail"), defaultPageWidth(), 8.0 );
	return s;
}

NCReportDesignerSection* NCReportDesignerDocument::sectionByName( const QString& name )
{
	return sections.value( name );
}


void NCReportDesignerDocument::setPageSize(NCReportDesignerSection *sect )
{
	double w=0,h=0;
	if ( po.pageSize == "A0" ) {
		w = 841.0; h = 1189.0;
	}
	else if ( po.pageSize == "A1" ) {
		w = 594.0; h = 841.0;
	}
	else if ( po.pageSize == "A2" ) {
		w = 420.0; h = 594.0;
	}
	else if ( po.pageSize == "A3" ) {
		w = 297.0; h = 420.0;
	}
	else if ( po.pageSize == "A4" ) {
		w = 210.0; h = 297.0;
	}
	else if ( po.pageSize == "A5M" ) {
		// half A4 = A5
		w = 210.0; h = 148.0;
	}
	else if ( po.pageSize == "A5" ) {
		w = 148.0; h = 210.0;
	}
	else if ( po.pageSize == "A6" ) {
		w = 105.0; h = 148.0;
	}
	else if ( po.pageSize == "A7" ) {
		w = 74.0; h = 105.0;
	}
	else if ( po.pageSize == "A8" ) {
		w = 52.0; h = 74.0;
	}
	else if ( po.pageSize == "A9" ) {
		w = 37.0; h = 52.0;
	}
	else if ( po.pageSize == "B0" ) {
		w = 1030.0; h = 1456.0;
	}
	else if ( po.pageSize == "B1" ) {
		w = 728.0; h = 1030.0;
	}
	else if ( po.pageSize == "B10" ) {
		w = 32.0; h = 45.0;
	}
	else if ( po.pageSize == "B2" ) {
		w = 515.0; h = 728.0;
	}
	else if ( po.pageSize == "B3" ) {
		w = 364.0; h = 515.0;
	}
	else if ( po.pageSize == "B4" ) {
		w = 257.0; h = 364.0;
	}
	else if ( po.pageSize == "B5" ) {
		w = 182.0; h = 257.0;
	}
	else if ( po.pageSize == "B6" ) {
		w = 128.0; h = 182.0;
	}
	else if ( po.pageSize == "B7" ) {
		w = 91.0; h = 128.0;
	}
	else if ( po.pageSize == "B8" ) {
		w = 64.0; h = 91.0;
	}
	else if ( po.pageSize == "B9" ) {
		w = 45.0; h = 764.0;
	}
	else if ( po.pageSize == "C5E" ) {
		w = 163.0; h = 229.0;
	}
	else if ( po.pageSize == "COMM10E" ) {
		w = 105.0; h = 241.0;
	}
	else if ( po.pageSize == "DLE" ) {
		w = 110.0; h = 220.0;
	}
	else if ( po.pageSize == "EXECUTIVE" ) {
		w = 191.0; h = 254.0;
	}
	else if ( po.pageSize == "FOLIO" ) {
		w = 210.0; h = 330.0;
	}
	else if ( po.pageSize == "LEDGER" ) {
		w = 432.0; h = 279.0;
	}
	else if ( po.pageSize == "LEGAL" ) {
		w = 216.0; h = 356.0;
	}
	else if ( po.pageSize == "LETTER" ) {
		w = 216.0; h = 279.0;
	}
	else if ( po.pageSize == "TABLOID" ) {
		w = 279.0; h = 432.0;
	}

	if ( po.orient == ReportPageOptions::Landscape ) {
		//change width/heigt
		double _w = w;
		w = h;
		h = _w;
	}

	if ( sect ) {// set size for only a section
		sect->setWidth( w - po.leftMargin - po.rightMargin );
	} else { // set size for whole document
		setPageWidth( w );
	}
}











///////////////////////////////////
// Ruler
///////////////////////////////////

NCReportDesignerRuler::NCReportDesignerRuler( Qt::Orientation ori, QWidget * parent )
	: QWidget( parent )
{
	//zoomlevel = 1.0;
	orient = ori;
	m = 0;
	scStart = 0;
	const int rulerH = RULERWEIGHT;
	//setPalette( QPalette( Qt::white ) );
	//setBackgroundRole( QPalette::Base );
	//setFrameStyle( StyledPanel | Raised );
	//setFrameStyle( QFrame::Panel | QFrame::Raised);

	if ( orient == Qt::Horizontal ) {
		setMinimumHeight(rulerH);
		setMaximumHeight(rulerH);
	} else {
		setMinimumWidth(rulerH);
		setMaximumWidth(rulerH);
	}
	resize(rulerH,rulerH);
}

NCReportDesignerRuler::~ NCReportDesignerRuler( )
{
}

void NCReportDesignerRuler::paintEvent( QPaintEvent * )
{
	if ( !m )
		return;

	QPainter p( this );
	double incr = 5.00000;
	const double lheight_long = 6.0;
	const double lheight_short = 3.0;
	double h =0.0;
	int counter=0;

	incr = m->measureUnit();

/*	if ( msr == Metric )
		incr = 72.0/25.4*TRIMFACTOR*zoomlevel;
	else
		incr = 7.2*TRIMFACTOR*zoomlevel;*/

	p.setPen(Qt::black);
	QFont f;
#ifdef Q_WS_WIN
	//f.setFamily("MS Sans Serif");
	f.setPixelSize( 8 );
#else
	f.setPixelSize( 8 );
#endif
	QString lbl;
	QFontMetrics fm( f );
	p.setFont( f );

	int to = ( orient == Qt::Horizontal ? width() : height() );
	bool stick = true;
	for ( double r=0.0 ; r< to; r+=incr ) {
		if ( counter%5 == 0 ) {
			h = lheight_long;
			stick = true;
		} else {
			h = lheight_short;
			stick = false;
		}

		if ( counter%10 == 0 ) {
			h = 10.0;
			lbl.setNum( counter/10 );
			if ( orient == Qt::Horizontal )
				p.drawText( qRound(scStart + r-fm.width(lbl)/2), 21, lbl );
			else
				p.drawText( 11, qRound(scStart + 10+r-fm.height()/2), lbl );
		}

		if ( orient == Qt::Horizontal ) {
			//QLineF line( r, 0.0, r, h );
			//p.drawLine( line );
			if ( stick ) p.drawLine( scStart + qRound(r), 0, scStart + qRound(r), (int)h );
		} else {
			//QLineF line( 0.0, r, h, r );
			//p.drawLine( line );
			if ( stick ) p.drawLine( 0, scStart + qRound(r), (int)h, scStart + qRound(r) );
		}
		counter++;
	}

	if ( orient == Qt::Horizontal )
		p.drawLine( 0,0,width(),0 );
	else
		p.drawLine( 0, 0, 0, height() );
	//p.drawRect( 0,0,width(),height() );

}

void NCReportDesignerRuler::setScaleStartPoint( int p )
{
	scStart = p;
}



///////////////////////////////////
// Resizer Bar
///////////////////////////////////
NCReportDesignerResizeBar::NCReportDesignerResizeBar( QWidget * parent )
	: QWidget( parent )
{
	//setFrameStyle( WinPanel | Raised);
	setMinimumHeight(7);
	setMaximumHeight(7);
	setCursor( QCursor( Qt::SizeVerCursor) );
	resize(7,7);
	//setBackgroundRole(QPalette::Button);
}

NCReportDesignerResizeBar::~ NCReportDesignerResizeBar( )
{
}

void NCReportDesignerResizeBar::mouseMoveEvent(QMouseEvent * e)
{
	e->accept();
    //qDebug("%d", e->y());
	emit barDragged(e->y());
}

void NCReportDesignerResizeBar::paintEvent( QPaintEvent * )
{
	QPainter p( this );
	style()->drawControl( QStyle::CE_Splitter, 0, &p, this );
}


///////////////////////////////////
// Designer section
///////////////////////////////////
NCReportDesignerSection::NCReportDesignerSection( NCReportDesignerWindow * mwin, QWidget * parent, const QString& cap, const char* name )
	: QWidget( parent )
{
	setObjectName( name );
	mainwindow = mwin;
	caption = cap;
	init();
}

NCReportDesignerSection::NCReportDesignerSection( SectionType t, NCReportDesignerWindow * mwin, QWidget * parent, const QString& cap, const char * name )
	: QWidget( parent )
{
	setObjectName( name );
	type = t;
	mainwindow = mwin;
	caption = cap;
	init();
}

NCReportDesignerSection::~ NCReportDesignerSection( )
{
}

void NCReportDesignerSection::init( )
{
	QVBoxLayout *layout = new QVBoxLayout( this );
	layout->setMargin(0);
	layout->setSpacing(0);
	footerSection = 0;
	//layout->setSizeConstraint( QLayout::SetNoConstraint );

/*	title = new QLabel( tr("Title"), this );
	title->setFrameStyle( QFrame::WinPanel | QFrame::Raised);*/

	title = new NCReportDesignerSectionTitle( this, "title" );
	//title->setText( tr("Section:")+" "+caption );
	title->setText( caption );
	layout->addWidget(title);
	//title->setMaximumHeight( 18 );
	//title->setBackgroundRole(QPalette::Button);

	QHBoxLayout *layMS = new QHBoxLayout();
	layMS->setMargin(0);
	layMS->setSpacing(0);

	ruler = new NCReportDesignerRuler( Qt::Vertical, this );
	designarea = new NCReportDesignerDesignArea( mainwindow, this, "designarea", 0 );
	layMS->addWidget( ruler );
	layMS->addWidget( designarea );
	//designarea->setMinimumSize( QSize(640, 5) );

	// resizer bar
	rbar = new NCReportDesignerResizeBar( this );
	connect( rbar, SIGNAL(barDragged(int)), this, SLOT(resizeBarDragged(int) ) );
	layout->addWidget(rbar);

	//setLayout(layout);

	//////////////////////
	//setMaximumWidth( qRound(72.0/25.4*210*TRIMFACTOR) );	//test
	//resize( qRound(72.0/25.4*210*TRIMFACTOR), 10 );	//test
}

void NCReportDesignerSection::setTitle( const QString & s, const QPixmap& pm )
{
	title->setText( s );
	title->setPixmap( pm );
}

void NCReportDesignerSection::setTitle( const QString & s )
{
	title->setText( s );
}

void NCReportDesignerSection::resizeBarDragged( int d )
{
	int h = designarea->height() + d;
	if( h < 1) h = 1;
/*	if(grid->isSnap()) {
		int incr = (int)(grid->yInterval() * dpiY);
		int nh = (h / incr) * incr;
		if(nh == 0) nh = incr;
		h = nh;
	}*/
	designarea->setMinimumHeight(h);
	//designarea->resize(designarea->width(), h);
	//if(canvasview->document()) canvasview->document()->setModified(TRUE);
}


NCReportDesignerDesignArea * NCReportDesignerSection::designArea( )
{
	return designarea;
}


void NCReportDesignerSection::setMeasurement( Measurement* msr )
{
	m = msr;
	ruler->setMeasurement( m );
	designarea->setMeasurement( m );
}

void NCReportDesignerSection::setGroupSettings( const QString & expr, const QString & rvars )
{
	groupExpr = expr;
	resetVars = rvars;
}

void NCReportDesignerSection::setType( SectionType t )
{
	type = t;
}
void NCReportDesignerSection::setWidth( double dw )
{
	int w = m->measureToPixel( dw );
	if ( w != designarea->width() )
		designarea->setFixedWidth( w );
}
void NCReportDesignerSection::setHeight( double dh )
{
	designarea->setMinimumHeight( m->measureToPixel( dh ) );
}

void NCReportDesignerSection::setFooterSection( NCReportDesignerSection *s )
{
	footerSection = s;
}
NCReportDesignerSection * NCReportDesignerSection::getFooterSection( )
{
	return footerSection;
}

NCReportDesignerSectionTitle * NCReportDesignerSection::Title()
{
	return title;
}

//--------------------------------------------
// Title
//--------------------------------------------
NCReportDesignerSectionTitle::NCReportDesignerSectionTitle( QWidget * parent, const char * name )
	: QWidget( parent )
{
	setObjectName( name );
	topMargin = 2;
	//setFrameStyle( QFrame::WinPanel | QFrame::Raised);
	setFixedHeight( 18 );
	pm = QPixmap("images/bullet_arrow_down.png");
}

NCReportDesignerSectionTitle::~ NCReportDesignerSectionTitle( )
{
}

void NCReportDesignerSectionTitle::paintEvent( QPaintEvent * )
{
	QPainter p( this );

	style()->drawControl( QStyle::CE_PushButton, new QStyleOptionButton() , &p, this );

	int tpos = 4;
	if ( !pm.isNull() ) {
		//p.drawPixmap( 4, topMargin, pm );
		p.drawPixmap( 4, 0, pm );
		tpos += pm.width()+4;
	}
	//if ( !text.isEmpty() )
	//p.drawText( tpos, height()-topMargin, text );
	//QRect r = p.boundingRect( tpos, topMargin, width()-tpos, height(), Qt::AlignLeft, text );

	p.drawText( tpos, topMargin, width()-2, height()-2, Qt::AlignLeft | Qt::AlignTop, text );
	//p.drawText( tpos, height()-topMargin, text );
	//p.drawText( tpos, topMargin, text );
}















