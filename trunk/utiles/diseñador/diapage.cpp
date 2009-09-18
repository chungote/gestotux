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
#include "diapage.h"
#include "ncreportdesignerdocument.h"

// #include <qvariant.h>
// #include <qpushbutton.h>
// #include <qgroupbox.h>
// #include <qlineedit.h>
// #include <qlabel.h>
// #include <qcombobox.h>
// #include <qspinbox.h>
// #include <qbuttongroup.h>
// #include <qradiobutton.h>
// #include <qlayout.h>
// #include <qtooltip.h>
// #include <qwhatsthis.h>
// #include <qtabwidget.h>


static const char * const _localenames[] = {
	"Latin1",
	"Big5",
	"Big5-HKSCS",
	"eucJP",
	"eucKR",
	"GB2312",
	"GBK",
	"GB18030",
	"JIS7",
	"Shift-JIS",
	"TSCII",
	"utf8",
	"utf16",
	"KOI8-R",
	"KOI8-U",
	"ISO8859-1",
	"ISO8859-2",
	"ISO8859-3",
	"ISO8859-4",
	"ISO8859-5",
	"ISO8859-6",
	"ISO8859-7",
	"ISO8859-8",
	"ISO8859-9",
	"ISO8859-10",
	"ISO8859-13",
	"ISO8859-14",
	"ISO8859-15",
	"IBM 850",
	"IBM 866",
	"CP874",
	"CP1250",
	"CP1251",
	"CP1252",
	"CP1253",
	"CP1254",
	"CP1255",
	"CP1256",
	"CP1257",
	"CP1258",
	"Apple Roman",
	"TIS-620",
0 };

static const char * const _pagesizes[] = {
	"A4", "B5", "Letter", "Legal", "Executive", "A0","A1","A2","A3","A5","A5M",
	"A6","A7","A8","A9","B0","B1","B10","B2","B3","B4","B6","B7",
	"B8"," B9","C5E","COMM10E","DLE","FOLIO","LEDGER","TABLOID",
0 };

static const char * const _printermodes[] = {
	"screen", "printer", "high", "comp",
0 };

static const char * const _datasources[] = {
	"Database", "Text file",
0 };

static const char * const _txtdelimiters[] = {
	"", "tab", "comma", "semicolon",
0 };

diaPage::diaPage( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, modal, fl )
{
    if ( !name )
	setObjectName( "diaPage" );
    else
       setObjectName( name );

    diaPageLayout = new QHBoxLayout( this, 6, 6, "diaPageLayout");
    layLeft = new QVBoxLayout( 0, 0, 6, "layLeft");

	tab = new QTabWidget( this, "tab" );

	layLeft->addWidget( tab );

	pagePage = new QWidget( tab, "pagePage" );
	pageDataSource = new QWidget( tab, "pageDataSource" );

	layPagePage = new QVBoxLayout( pagePage, 6, 6, "layPagePage");
	layPageDataSource = new QVBoxLayout( pageDataSource, 6, 6, "layPageDataSource");

    gbGen = new QGroupBox( pagePage, "gbGen" );
    gbGen->setColumnLayout(0, Qt::Vertical );
    gbGen->layout()->setSpacing( 6 );
    gbGen->layout()->setMargin( 6 );
    gbGenLayout = new QGridLayout( gbGen->layout(), 0,0,3 );
    gbGenLayout->setAlignment( Qt::AlignTop );

    leFont = new QLineEdit( gbGen, "leFont" );

    gbGenLayout->addWidget( leFont, 4, 1 );

    leMasterAlias = new QLineEdit( gbGen, "leMasterAlias" );

    gbGenLayout->addWidget( leMasterAlias, 6, 1 );

    lblEncode = new QLabel( gbGen, "lblEncode" );

    gbGenLayout->addWidget( lblEncode, 1, 0 );

    lblPrintMode = new QLabel( gbGen, "lblPrintMode" );

    gbGenLayout->addWidget( lblPrintMode, 3, 0 );

    comboPrinterMode = new QComboBox( FALSE, gbGen, "comboPrinterMode" );
    comboPrinterMode->setMaximumSize( QSize( 170, 32767 ) );

    gbGenLayout->addWidget( comboPrinterMode, 3, 1 );

    textLabel10 = new QLabel( gbGen, "textLabel10" );

    gbGenLayout->addWidget( textLabel10, 6, 0 );

    lblFont = new QLabel( gbGen, "lblFont" );

    gbGenLayout->addWidget( lblFont, 4, 0 );

    lblPageSize = new QLabel( gbGen, "lblPageSize" );

    gbGenLayout->addWidget( lblPageSize, 2, 0 );

    lblFonstSize = new QLabel( gbGen, "lblFonstSize" );

    gbGenLayout->addWidget( lblFonstSize, 5, 0 );

    lblName = new QLabel( gbGen, "lblName" );

    gbGenLayout->addWidget( lblName, 0, 0 );

    spFontSize = new QSpinBox( gbGen, "spFontSize" );
    spFontSize->setMaximumSize( QSize( 60, 32767 ) );
    spFontSize->setMinValue( 5 );

    gbGenLayout->addWidget( spFontSize, 5, 1 );

    comboEncodings = new QComboBox( FALSE, gbGen, "comboEncodings" );
    comboEncodings->setMaximumSize( QSize( 170, 32767 ) );

    gbGenLayout->addWidget( comboEncodings, 1, 1 );

    comboPageSize = new QComboBox( FALSE, gbGen, "comboPageSize" );
    comboPageSize->setMaximumSize( QSize( 170, 32767 ) );

    gbGenLayout->addWidget( comboPageSize, 2, 1 );

    leName = new QLineEdit( gbGen, "leName" );

    gbGenLayout->addWidget( leName, 0, 1 );

	layPagePage->addWidget( gbGen );

    layMargin = new QHBoxLayout( 0, 0, 6, "layMargin");

    gbMargin = new QGroupBox( pagePage, "gbMargin" );
    gbMargin->setColumnLayout(0, Qt::Vertical );
    gbMargin->layout()->setSpacing( 0 );
    gbMargin->layout()->setMargin( 6 );
    gbMarginLayout = new QGridLayout( gbMargin->layout(),0,0,3 );
    gbMarginLayout->setAlignment( Qt::AlignTop );

    lblLeft = new QLabel( gbMargin, "lblLeft" );

    gbMarginLayout->addWidget( lblLeft, 1, 0 );

    spRight = new QSpinBox( gbMargin, "spRight" );

    gbMarginLayout->addWidget( spRight, 1, 5 );

    lblBottom = new QLabel( gbMargin, "lblBottom" );

    gbMarginLayout->addWidget( lblBottom, 2, 2 );

    spBottom = new QSpinBox( gbMargin, "spBottom" );

    gbMarginLayout->addWidget( spBottom, 2, 3 );

    lblTop = new QLabel( gbMargin, "lblTop" );

    gbMarginLayout->addWidget( lblTop, 0, 2 );

    spTop = new QSpinBox( gbMargin, "spTop" );

    gbMarginLayout->addWidget( spTop, 0, 3 );

    lblRight = new QLabel( gbMargin, "lblRight" );

    gbMarginLayout->addWidget( lblRight, 1, 4 );

    spLeft = new QSpinBox( gbMargin, "spLeft" );

    gbMarginLayout->addWidget( spLeft, 1, 1 );
    layMargin->addWidget( gbMargin );

    gbOrient = new QButtonGroup( pagePage, "gbOrient" );
    gbOrient->setColumnLayout(0, Qt::Vertical );
    gbOrient->layout()->setSpacing( 6 );
    gbOrient->layout()->setMargin( 6 );
    gbOrientLayout = new QVBoxLayout( gbOrient->layout() );
    gbOrientLayout->setAlignment( Qt::AlignTop );

    radioP = new QRadioButton( gbOrient, "radioP" );
    radioP->setChecked( TRUE );
    gbOrientLayout->addWidget( radioP );

    radioL = new QRadioButton( gbOrient, "radioL" );
    gbOrientLayout->addWidget( radioL );
    layMargin->addWidget( gbOrient );
    layPagePage->addLayout( layMargin );


	// Database connection
	layDSTop = new QHBoxLayout( layPageDataSource, 6, "layDSTop");

    lblDataSrc = new QLabel( pageDataSource, "lblDataSrc" );
	layDSTop->addWidget( lblDataSrc );
    comboDataSource = new QComboBox( FALSE, pageDataSource, "comboDataSource" );
    comboDataSource->setMaximumSize( QSize( 170, 32767 ) );
	layDSTop->addWidget( comboDataSource );
	layDSTop->addStretch( 5 );

	gbCon = new QGroupBox( pageDataSource, "gbCon" );
    gbCon->setColumnLayout(0, Qt::Vertical );
    gbCon->layout()->setSpacing( 6 );
    gbCon->layout()->setMargin( 6 );
    gbConLayout = new QGridLayout( gbCon->layout(), 0, 0, 3 );
    gbConLayout->setAlignment( Qt::AlignTop );

    lblHot = new QLabel( gbCon, "lblHot" );
    gbConLayout->addWidget( lblHot, 0, 0 );
    leHost = new QLineEdit( gbCon, "leHost" );
    gbConLayout->addWidget( leHost, 0, 1 );

    lblDB = new QLabel( gbCon, "lblDB" );
    gbConLayout->addWidget( lblDB, 1, 0 );
    leDB = new QLineEdit( gbCon, "leDB" );
    gbConLayout->addWidget( leDB, 1, 1 );

    lblUser = new QLabel( gbCon, "lblUser" );
    gbConLayout->addWidget( lblUser, 2, 0 );
    leUSer = new QLineEdit( gbCon, "leUSer" );
    gbConLayout->addWidget( leUSer, 2, 1 );

    lblPassword = new QLabel( gbCon, "lblPassword" );
    gbConLayout->addWidget( lblPassword, 3, 0 );
	lePassw = new QLineEdit( gbCon, "lePassw" );
    lePassw->setEchoMode( QLineEdit::Password );
    gbConLayout->addWidget( lePassw, 3, 1 );

	layPageDataSource->addWidget( gbCon );


	// TEXT Source
	gbText = new QGroupBox( pageDataSource, "gbText" );
    gbText->setColumnLayout(0, Qt::Vertical );
    gbText->layout()->setSpacing( 6 );
    gbText->layout()->setMargin( 6 );
    gbTextLayout = new QGridLayout( gbText->layout(), 0, 0, 3 );
    gbTextLayout->setAlignment( Qt::AlignTop );

	lblResrcText = new QLabel( gbText, "lblResrcText" );
    gbTextLayout->addWidget( lblResrcText, 0, 0 );
	leResourceText = new QLineEdit( gbText, "leResourceText" );
    gbTextLayout->addWidget( leResourceText, 0, 1 );

	lblTextDataDelim = new QLabel( gbText, "lblTextDataDelim" );
    gbTextLayout->addWidget( lblTextDataDelim, 1, 0 );
	comboDelimiter = new QComboBox( FALSE, gbText, "comboDelimiter" );
    comboDelimiter->setMaximumSize( QSize( 140, 32767 ) );
    gbTextLayout->addWidget( comboDelimiter, 1, 1 );

	lblRowFilter = new QLabel( gbText, "lblRowFilter" );
	gbTextLayout->addWidget( lblRowFilter, 2, 0 );
	leRowFilter = new QLineEdit( gbText, "leRowFilter" );
	gbTextLayout->addWidget( leRowFilter, 2, 1 );

	layPageDataSource->addWidget( gbText );


	//-----------------------------------

	diaPageLayout->addLayout( layLeft );

	tab->addTab( pagePage, tr("General") );
	tab->addTab( pageDataSource, tr("Datasource") );

    layBtn = new QVBoxLayout( 0, 0, 6, "layBtn");

    btnOK = new QPushButton( this, "btnOK" );
    layBtn->addWidget( btnOK );

    btnCancel = new QPushButton( this, "btnCancel" );
    layBtn->addWidget( btnCancel );
    spBtn = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layBtn->addItem( spBtn );
    diaPageLayout->addLayout( layBtn );
    languageChange();
    //resize( QSize(512, 458).expandedTo(minimumSizeHint()) );
	resize( minimumSizeHint() );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( btnOK, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( btnCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );

    // tab order
    setTabOrder( leName, comboEncodings );
    setTabOrder( comboEncodings, comboPageSize );
    setTabOrder( comboPageSize, comboPrinterMode );
    setTabOrder( comboPrinterMode, leFont );
    setTabOrder( leFont, spFontSize );
    setTabOrder( spFontSize, leMasterAlias );
    setTabOrder( leMasterAlias, spTop );
    setTabOrder( spTop, spLeft );
    setTabOrder( spLeft, spRight );
    setTabOrder( spRight, spBottom );
    setTabOrder( spBottom, radioP );
    setTabOrder( radioP, radioL );
    setTabOrder( radioL, leHost );
    setTabOrder( leHost, leDB );
    setTabOrder( leDB, leUSer );
    setTabOrder( leUSer, lePassw );
    setTabOrder( lePassw, btnOK );
    setTabOrder( btnOK, btnCancel );

	initComboBoxes();

	leHost->setEnabled(FALSE);
	leDB->setEnabled(FALSE);
	leUSer->setEnabled(FALSE);
	lePassw->setEnabled(FALSE);
}

/*
 *  Destroys the object and frees any allocated resources
 */
diaPage::~diaPage()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void diaPage::languageChange()
{
    setCaption( tr( "Report settings" ) );
    gbGen->setTitle( tr( "General settings" ) );
    lblEncode->setText( tr( "File encoding" ) );
    lblPrintMode->setText( tr( "Printer mode" ) );
    textLabel10->setText( tr( "Primary query alias" ) );
    lblFont->setText( tr( "Default font name" ) );
    lblPageSize->setText( tr( "Page size" ) );
    lblFonstSize->setText( tr( "Default font size" ) );
    lblName->setText( tr( "Report name" ) );
    gbMargin->setTitle( tr( "Margins" ) );
    lblLeft->setText( tr( "Left" ) );
    lblBottom->setText( tr( "Bottom" ) );
    lblTop->setText( tr( "Top" ) );
    lblRight->setText( tr( "Right" ) );
    gbOrient->setTitle( tr( "Orientation" ) );
    radioP->setText( tr( "Portrait" ) );
    radioL->setText( tr( "Landscape" ) );
    gbCon->setTitle( tr( "Database connection" ) );
    lblHot->setText( tr( "Host" ) );
    lblDB->setText( tr( "Database" ) );
    lblUser->setText( tr( "Username" ) );
    lblPassword->setText( tr( "Password" ) );
    btnOK->setText( tr( "OK" ) );
    btnCancel->setText( tr( "Cancel" ) );

	gbText->setTitle( tr( "Textfile source settings" ) );
	lblDataSrc->setText( tr("Datasource") );
	lblResrcText->setText( tr("Resource text file") );
	lblTextDataDelim->setText( tr("Field delimiter") );
	lblRowFilter->setText( tr("Row filter regexp:") );
}

void diaPage::assignDocument( NCReportDesignerDocument *doc )
{
	document = doc;

	leName->setText(doc->po.reportName);
	comboEncodings->setCurrentText(doc->po.encoding);
	comboPageSize->setCurrentText(doc->po.pageSize);
	comboPrinterMode->setCurrentText(doc->po.printerMode);
	leFont->setText(doc->po.defaultFontName);
	spFontSize->setValue(doc->po.defaultFontSize);
	leMasterAlias->setText(doc->po.masterAlias);
	spTop->setValue(doc->po.topMargin);
	spBottom->setValue(doc->po.bottomMargin);
	spLeft->setValue(doc->po.leftMargin);
	spRight->setValue(doc->po.rightMargin);
	gbOrient->setButton( doc->po.orient == ReportPageOptions::Portrait ? 0 : 1 );

	comboDataSource->setCurrentItem( doc->po.dataSource == ReportPageOptions::Database ? 0 : 1 );
	leResourceText->setText(doc->po.resourceTextFile);
	comboDelimiter->setCurrentText(doc->po.textDataDelimiter);
	leRowFilter->setText( doc->po.rowFilterRegExp );
}

void diaPage::applySettings( )
{
	document->po.reportName = leName->text();
	document->po.encoding = comboEncodings->currentText();
	document->po.pageSize = comboPageSize->currentText();
	document->po.printerMode = comboPrinterMode->currentText();
	document->po.defaultFontName = leFont->text();
	document->po.defaultFontSize = spFontSize->value();
	document->po.masterAlias = leMasterAlias->text();
	document->po.topMargin = spTop->value();
	document->po.bottomMargin = spBottom->value();
	document->po.leftMargin = spLeft->value();
	document->po.rightMargin = spRight->value();
	document->po.orient = ( gbOrient->selectedId() == 0 ? ReportPageOptions::Portrait : ReportPageOptions::Landscape );
	//document->po.columnCount = 1;
	//document->po.backColor = "#FFFFFF";
	//document->po.pageHeight
	//document->po.pageWidth

	document->po.dataSource = ( comboDataSource->currentItem()==0 ? ReportPageOptions::Database : ReportPageOptions::Textfile );
	document->po.resourceTextFile = leResourceText->text();
	document->po.textDataDelimiter = comboDelimiter->currentText();
	document->po.rowFilterRegExp = leRowFilter->text();

	document->setPageSize();
}



void diaPage::initComboBoxes( )
{
	int i=0;
	while ( _localenames[i] ) {
		comboEncodings->insertItem( _localenames[i] );
		++i;
	}
	i=0;
	while ( _pagesizes[i] ) {
		comboPageSize->insertItem( _pagesizes[i] );
		++i;
	}
	i=0;
	while ( _printermodes[i] ) {
		comboPrinterMode->insertItem( _printermodes[i] );
		++i;
	}
	i=0;
	while ( _datasources[i] ) {
		comboDataSource->insertItem( _datasources[i] );
		++i;
	}
	i=0;
	while ( _txtdelimiters[i] ) {
		comboDelimiter->insertItem( _txtdelimiters[i] );
		++i;
	}


}

