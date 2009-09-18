/****************************************************************************
** Form implementation generated from reading ui file 'ncreportdesignerwidgetsetdialogui.ui'
**
** Created: k aug 22 11:50:39 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "ncreportdesignerwidgetsetdialogui.h"
#include "nccolorcombo.h"

#include <QVariant>
#include <QPushButton>
#include <QTabWidget>
#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QSpinbox>
#include <QCheckBox>
#include <QRadioButton>

/*
#include <qbuttongroup.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>*/

/*
 *  Constructs a NCReportDesignerWidgetSetDialogUI as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
NCReportDesignerWidgetSetDialogUI::NCReportDesignerWidgetSetDialogUI( QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl )
    : QDialog( parent, fl )
{
    if ( !name )
	name = "setdialog";
    this->setObjectName( name );
    this->setModal( modal );
    setSizeGripEnabled( TRUE );
    setdialogLayout = new QVBoxLayout( this, 6, 6, "setdialogLayout");

    tab = new QTabWidget( this, "tab" );

    pageData = new QWidget( tab, "pageData" );
    pageDataLayout = new QVBoxLayout( pageData, 6, 6, "pageDataLayout");

    lblLabel = new QLabel( pageData, "lblLabel" );
    pageDataLayout->addWidget( lblLabel );

    textLabel = new QTextEdit( pageData, "textLabel" );
	textLabel->setTextFormat( Qt::PlainText );
    pageDataLayout->addWidget( textLabel );

    layDSGrid = new QGridLayout( 0, 1, 1, 0, 6, "layDSGrid");

    lblSrcType = new QLabel( pageData, "lblSrcType" );
    layDSGrid->addWidget( lblSrcType, 0, 0 );
    comboDSource = new QComboBox( FALSE, pageData, "comboDSource" );
    comboDSource->setMaximumSize( QSize( 120, 32767 ) );
    layDSGrid->addWidget( comboDSource, 0, 1 );


    lblSrc = new QLabel( pageData, "lblSrc" );
    layDSGrid->addWidget( lblSrc, 1, 0 );
    leSource = new QLineEdit( pageData, "leSource" );
    layDSGrid->addWidget( leSource, 1, 1 );

	lblPWhen = new QLabel( pageData, "lblPWhen" );
    layDSGrid->addWidget( lblPWhen, 2, 0 );
    lePrintWhen = new QLineEdit( pageData, "lePrintWhen" );
    layDSGrid->addWidget( lePrintWhen, 2, 1 );

    lblEmbed = new QLabel( pageData, "lblEmbed" );
    layDSGrid->addWidget( lblEmbed, 3, 0 );
    leEmbed = new QLineEdit( pageData, "leEmbed" );
    layDSGrid->addWidget( leEmbed, 3, 1 );

    lblFunc = new QLabel( pageData, "lblFunc" );
    layDSGrid->addWidget( lblFunc, 4, 0 );
    leFunction = new QLineEdit( pageData, "leFunction" );
    layDSGrid->addWidget( leFunction, 4, 1 );

    lblLookup = new QLabel( pageData, "lblLookup" );
    layDSGrid->addWidget( lblLookup, 5, 0 );
    leLookup = new QLineEdit( pageData, "leLookup" );
    layDSGrid->addWidget( leLookup, 5, 1 );

	pageDataLayout->addLayout( layDSGrid );

    spacerDS = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    pageDataLayout->addItem( spacerDS );
    tab->insertTab( pageData, QString::fromLatin1("") );

    TabPage = new QWidget( tab, "TabPage" );
    TabPageLayout = new QVBoxLayout( TabPage, 6, 6, "TabPageLayout");

    layout42 = new QHBoxLayout( 0, 0, 6, "layout42");

    lblType = new QLabel( TabPage, "lblType" );
    layout42->addWidget( lblType );

    comboType = new QComboBox( FALSE, TabPage, "comboType" );
    layout42->addWidget( comboType );
    spDataType = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layout42->addItem( spDataType );
    TabPageLayout->addLayout( layout42 );

    gbNumFormat = new QGroupBox( TabPage, "gbNumFormat" );
    gbNumFormat->setColumnLayout(0, Qt::Vertical );
    gbNumFormat->layout()->setSpacing( 6 );
    gbNumFormat->layout()->setMargin( 6 );
    gbNumFormatLayout = new QGridLayout( gbNumFormat->layout() );
    gbNumFormatLayout->setAlignment( Qt::AlignTop );

    lblNumFormat = new QLabel( gbNumFormat, "lblNumFormat" );

    gbNumFormatLayout->addWidget( lblNumFormat, 0, 0 );

    leNumFormat = new QLineEdit( gbNumFormat, "leNumFormat" );
    leNumFormat->setMaximumSize( QSize( 100, 32767 ) );

    gbNumFormatLayout->addMultiCellWidget( leNumFormat, 0, 0, 1, 3 );

    lblNoDec = new QLabel( gbNumFormat, "lblNoDec" );

    gbNumFormatLayout->addMultiCellWidget( lblNoDec, 2, 2, 0, 1 );

    spDec = new QSpinBox( gbNumFormat, "spDec" );
    spDec->setMaxValue( 18 );
    spDec->setMinValue( -1 );
    spDec->setValue( -1 );

    gbNumFormatLayout->addWidget( spDec, 2, 2 );

    lblDecPoint = new QLabel( gbNumFormat, "lblDecPoint" );

    gbNumFormatLayout->addWidget( lblDecPoint, 2, 3 );

    leDecPoint = new QLineEdit( gbNumFormat, "leDecPoint" );
    leDecPoint->setMaximumSize( QSize( 30, 32767 ) );

    gbNumFormatLayout->addWidget( leDecPoint, 2, 4 );

    leSeparator = new QLineEdit( gbNumFormat, "leSeparator" );
    leSeparator->setMaximumSize( QSize( 30, 32767 ) );

    gbNumFormatLayout->addWidget( leSeparator, 3, 4 );

    lblSetSymb = new QLabel( gbNumFormat, "lblSetSymb" );

    gbNumFormatLayout->addWidget( lblSetSymb, 3, 3 );

    cbBlankIfZero = new QCheckBox( gbNumFormat, "cbBlankIfZero" );

    gbNumFormatLayout->addMultiCellWidget( cbBlankIfZero, 4, 4, 0, 4 );

    cbThousandSep = new QCheckBox( gbNumFormat, "cbThousandSep" );

    gbNumFormatLayout->addMultiCellWidget( cbThousandSep, 3, 3, 0, 2 );

    lblHelpNumF = new QLabel( gbNumFormat, "lblHelpNumF" );
    lblHelpNumF->setAlignment( int( QLabel::WordBreak | QLabel::AlignVCenter ) );

    gbNumFormatLayout->addMultiCellWidget( lblHelpNumF, 1, 1, 0, 4 );
    TabPageLayout->addWidget( gbNumFormat );

    gbDateFormat = new QGroupBox( TabPage, "gbDateFormat" );
    gbDateFormat->setColumnLayout(0, Qt::Vertical );
    gbDateFormat->layout()->setSpacing( 6 );
    gbDateFormat->layout()->setMargin( 6 );
    gbDateFormatLayout = new QHBoxLayout( gbDateFormat->layout() );
    gbDateFormatLayout->setAlignment( Qt::AlignTop );

    lblDateFmt = new QLabel( gbDateFormat, "lblDateFmt" );
    gbDateFormatLayout->addWidget( lblDateFmt );

    leDateFormat = new QLineEdit( gbDateFormat, "leDateFormat" );
    leDateFormat->setMaximumSize( QSize( 140, 32767 ) );
    gbDateFormatLayout->addWidget( leDateFormat );
    spDF = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    gbDateFormatLayout->addItem( spDF );
    TabPageLayout->addWidget( gbDateFormat );
    spDataF = new QSpacerItem( 20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding );
    TabPageLayout->addItem( spDataF );
    tab->insertTab( TabPage, QString::fromLatin1("") );

    pageTxt = new QWidget( tab, "pageTxt" );
    pageTxtLayout = new QVBoxLayout( pageTxt, 6, 6, "pageTxtLayout");

    layFont1 = new QHBoxLayout( 0, 0, 6, "layFont1");

    layFontIn = new QGridLayout( 0, 1, 1, 0, 6, "layFontIn");

    comboColor = new NCColorCombo( pageTxt, "comboColor" );
    comboColor->setMinimumSize( QSize( 60, 0 ) );

    layFontIn->addMultiCellWidget( comboColor, 1, 1, 3, 4 );

    btnSelFont = new QPushButton( pageTxt, "btnSelFont" );
    btnSelFont->setMaximumSize( QSize( 25, 32767 ) );

    layFontIn->addWidget( btnSelFont, 0, 4 );

    lblFont = new QLabel( pageTxt, "lblFont" );

    layFontIn->addWidget( lblFont, 0, 0 );

    comboFontSize = new QComboBox( FALSE, pageTxt, "comboFontSize" );
    comboFontSize->setMinimumSize( QSize( 80, 0 ) );
    comboFontSize->setEditable( TRUE );

    layFontIn->addWidget( comboFontSize, 1, 1 );

    leFont = new QLineEdit( pageTxt, "leFont" );

    layFontIn->addMultiCellWidget( leFont, 0, 0, 1, 3 );

    lblTxtColor = new QLabel( pageTxt, "lblTxtColor" );

    layFontIn->addWidget( lblTxtColor, 1, 2 );

    lblFontSize = new QLabel( pageTxt, "lblFontSize" );

    layFontIn->addWidget( lblFontSize, 1, 0 );
    layFont1->addLayout( layFontIn );

    lblSample = new QLabel( pageTxt, "lblSample" );
    lblSample->setFrameShape( QLabel::Box );
	lblSample->setFixedSize( QSize(120,40) );
    layFont1->addWidget( lblSample );
    pageTxtLayout->addLayout( layFont1 );

    layCb = new QHBoxLayout( 0, 0, 6, "layCb");

    cbBold = new QCheckBox( pageTxt, "cbBold" );
    layCb->addWidget( cbBold );

    cbItalic = new QCheckBox( pageTxt, "cbItalic" );
    layCb->addWidget( cbItalic );

    cbUnderline = new QCheckBox( pageTxt, "cbUnderline" );
    layCb->addWidget( cbUnderline );

    cbStrikeout = new QCheckBox( pageTxt, "cbStrikeout" );
    layCb->addWidget( cbStrikeout );
    spacerCb = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layCb->addItem( spacerCb );
    pageTxtLayout->addLayout( layCb );

    layRadio = new QHBoxLayout( 0, 0, 6, "layRadio");

    bgHAlign = new QButtonGroup( pageTxt, "bgHAlign" );
    bgHAlign->setColumnLayout(0, Qt::Vertical );
    bgHAlign->layout()->setSpacing( 6 );
    bgHAlign->layout()->setMargin( 6 );
    bgHAlignLayout = new QHBoxLayout( bgHAlign->layout() );
    bgHAlignLayout->setAlignment( Qt::AlignTop );

    radioLeft = new QRadioButton( bgHAlign, "radioLeft" );
    radioLeft->setChecked( TRUE );
    bgHAlignLayout->addWidget( radioLeft );

    radioCenter = new QRadioButton( bgHAlign, "radioCenter" );
    bgHAlignLayout->addWidget( radioCenter );

    radioRight = new QRadioButton( bgHAlign, "radioRight" );
    bgHAlignLayout->addWidget( radioRight );
    layRadio->addWidget( bgHAlign );

    bgVAlign = new QButtonGroup( pageTxt, "bgVAlign" );
    bgVAlign->setColumnLayout(0, Qt::Vertical );
    bgVAlign->layout()->setSpacing( 6 );
    bgVAlign->layout()->setMargin( 6 );
    bgVAlignLayout = new QHBoxLayout( bgVAlign->layout() );
    bgVAlignLayout->setAlignment( Qt::AlignTop );

    radioTop = new QRadioButton( bgVAlign, "radioTop" );
    radioTop->setChecked( TRUE );
    bgVAlignLayout->addWidget( radioTop );

    radioMid = new QRadioButton( bgVAlign, "radioMid" );
    bgVAlignLayout->addWidget( radioMid );

    radioBottom = new QRadioButton( bgVAlign, "radioBottom" );
    bgVAlignLayout->addWidget( radioBottom );
    layRadio->addWidget( bgVAlign );
    pageTxtLayout->addLayout( layRadio );

    cbWordBreak = new QCheckBox( pageTxt, "cbWordBreak" );
    pageTxtLayout->addWidget( cbWordBreak );
    cbRichText = new QCheckBox( pageTxt, "cbRichText" );
    pageTxtLayout->addWidget( cbRichText );
    cbDynamicHeight = new QCheckBox( pageTxt, "cbDynamicHeight" );
    pageTxtLayout->addWidget( cbDynamicHeight );
    cbLoadFromFile = new QCheckBox( pageTxt, "cbLoadFromFile" );
    pageTxtLayout->addWidget( cbLoadFromFile );

    layRot = new QHBoxLayout( 0, 0, 6, "layRot");

    lblRotat = new QLabel( pageTxt, "lblRotat" );
    layRot->addWidget( lblRotat );

    spinRotation = new QSpinBox( pageTxt, "spinRotation" );
    layRot->addWidget( spinRotation );
    spacerRot = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layRot->addItem( spacerRot );
    pageTxtLayout->addLayout( layRot );
    spacerTextPage = new QSpacerItem( 20, 46, QSizePolicy::Minimum, QSizePolicy::Expanding );
    pageTxtLayout->addItem( spacerTextPage );
    tab->insertTab( pageTxt, QString::fromLatin1("") );

    pageLine = new QWidget( tab, "pageLine" );
    pageLineLayout = new QVBoxLayout( pageLine, 6, 6, "pageLineLayout");

    layLin1 = new QHBoxLayout( 0, 0, 6, "layLin1");

    bgBackM = new QButtonGroup( pageLine, "bgBackM" );
    bgBackM->setColumnLayout(0, Qt::Vertical );
    bgBackM->layout()->setSpacing( 6 );
    bgBackM->layout()->setMargin( 6 );
    bgBackMLayout = new QHBoxLayout( bgBackM->layout() );
    bgBackMLayout->setAlignment( Qt::AlignTop );

    radioTransp = new QRadioButton( bgBackM, "radioTransp" );
    bgBackMLayout->addWidget( radioTransp );

    radioFill = new QRadioButton( bgBackM, "radioFill" );
    bgBackMLayout->addWidget( radioFill );
    layLin1->addWidget( bgBackM );
    spacerBM = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layLin1->addItem( spacerBM );
    pageLineLayout->addLayout( layLin1 );

    layLin2 = new QHBoxLayout( 0, 0, 6, "layLin2");

    layout11 = new QGridLayout( 0, 1, 1, 0, 6, "layout11");

    lblFillcol = new QLabel( pageLine, "lblFillcol" );

    layout11->addWidget( lblFillcol, 1, 2 );

    comboLineStyle = new QComboBox( FALSE, pageLine, "comboLineStyle" );

    layout11->addWidget( comboLineStyle, 1, 1 );

    comboColorF = new NCColorCombo( pageLine, "comboColorF" );
    comboColorF->setMinimumSize( QSize( 60, 0 ) );

    layout11->addWidget( comboColorF, 1, 3 );

    lblLinesty = new QLabel( pageLine, "lblLinesty" );

    layout11->addWidget( lblLinesty, 1, 0 );

    lblLinecol = new QLabel( pageLine, "lblLinecol" );

    layout11->addWidget( lblLinecol, 0, 2 );

    spinLineWidth = new QSpinBox( pageLine, "spinLineWidth" );

    layout11->addWidget( spinLineWidth, 0, 1 );

    comboColorL = new NCColorCombo( pageLine, "comboColorL" );
    comboColorL->setMinimumSize( QSize( 60, 0 ) );

    layout11->addWidget( comboColorL, 0, 3 );

    lblLinew = new QLabel( pageLine, "lblLinew" );

    layout11->addWidget( lblLinew, 0, 0 );
    layLin2->addLayout( layout11 );
    spacerLineS = new QSpacerItem( 100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layLin2->addItem( spacerLineS );
    pageLineLayout->addLayout( layLin2 );
    spacerPageLine = new QSpacerItem( 20, 80, QSizePolicy::Minimum, QSizePolicy::Expanding );
    pageLineLayout->addItem( spacerPageLine );
    tab->insertTab( pageLine, QString::fromLatin1("") );
    setdialogLayout->addWidget( tab );

    layBtn = new QHBoxLayout( 0, 0, 6, "layBtn");
    spacerBtn = new QSpacerItem( 160, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layBtn->addItem( spacerBtn );

    buttonApply = new QPushButton( this, "buttonApply" );
    layBtn->addWidget( buttonApply );
    spacerBtn2 = new QSpacerItem( 20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    layBtn->addItem( spacerBtn2 );

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setAutoDefault( TRUE );
    buttonOk->setDefault( TRUE );
    layBtn->addWidget( buttonOk );

    buttonCancel = new QPushButton( this, "buttonCancel" );
    buttonCancel->setAutoDefault( TRUE );
    layBtn->addWidget( buttonCancel );
    setdialogLayout->addLayout( layBtn );
    languageChange();
    resize( QSize(497, 374).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( cbBold, SIGNAL( toggled(bool) ), this, SLOT( fontBoldChanged(bool) ) );
    connect( cbItalic, SIGNAL( toggled(bool) ), this, SLOT( fontItalicChanged(bool) ) );
    connect( cbUnderline, SIGNAL( toggled(bool) ), this, SLOT( fontUnderlineChanged(bool) ) );
    connect( cbStrikeout, SIGNAL( toggled(bool) ), this, SLOT( fontStrikeChanged(bool) ) );
    connect( leFont, SIGNAL( textChanged(const QString&) ), this, SLOT( fontStyleChanged(const QString&) ) );
    connect( comboFontSize, SIGNAL( textChanged(const QString&) ), this, SLOT( fontSizeChanged(const QString&) ) );
    connect( bgHAlign, SIGNAL( clicked(int) ), this, SLOT( alignHChanged(int) ) );
    connect( bgVAlign, SIGNAL( clicked(int) ), this, SLOT( alignVChanged(int) ) );
    connect( bgBackM, SIGNAL( clicked(int) ), this, SLOT( backModeChanged(int) ) );
    connect( buttonApply, SIGNAL( clicked() ), this, SLOT( applyOptions() ) );
    connect( btnSelFont, SIGNAL( clicked() ), this, SLOT( selectFont() ) );
    connect( comboType, SIGNAL( activated(int) ), this, SLOT( changedDataType(int) ) );

    // tab order
    setTabOrder( tab, textLabel );
    setTabOrder( textLabel, comboDSource );
    setTabOrder( comboDSource, leSource );
    setTabOrder( leSource, lePrintWhen );
    setTabOrder( lePrintWhen, leEmbed );
    setTabOrder( leEmbed, leFunction );
    setTabOrder( leFunction, comboType );
    setTabOrder( comboType, leNumFormat );
    setTabOrder( leNumFormat, spDec );
    setTabOrder( spDec, leDecPoint );
    setTabOrder( leDecPoint, cbThousandSep );
    setTabOrder( cbThousandSep, leSeparator );
    setTabOrder( leSeparator, cbBlankIfZero );
    setTabOrder( cbBlankIfZero, leDateFormat );
    setTabOrder( leDateFormat, leFont );
    setTabOrder( leFont, btnSelFont );
    setTabOrder( btnSelFont, comboFontSize );
    setTabOrder( comboFontSize, cbBold );
    setTabOrder( cbBold, cbItalic );
    setTabOrder( cbItalic, cbUnderline );
    setTabOrder( cbUnderline, cbStrikeout );
    setTabOrder( cbStrikeout, radioLeft );
    setTabOrder( radioLeft, radioTop );
    setTabOrder( radioTop, cbWordBreak );
    setTabOrder( cbWordBreak, cbRichText );
    setTabOrder( cbRichText, cbDynamicHeight );
    setTabOrder( cbDynamicHeight, cbLoadFromFile );
    setTabOrder( cbLoadFromFile, spinRotation );
    setTabOrder( spinRotation, buttonApply );
    setTabOrder( buttonApply, buttonOk );
    setTabOrder( buttonOk, buttonCancel );
    setTabOrder( buttonCancel, radioTransp );
    setTabOrder( radioTransp, radioFill );
    setTabOrder( radioFill, spinLineWidth );
    setTabOrder( spinLineWidth, comboLineStyle );
    setTabOrder( comboLineStyle, radioCenter );
    setTabOrder( radioCenter, radioRight );
    setTabOrder( radioRight, radioMid );
    setTabOrder( radioMid, radioBottom );
}

/*
 *  Destroys the object and frees any allocated resources
 */
NCReportDesignerWidgetSetDialogUI::~NCReportDesignerWidgetSetDialogUI()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void NCReportDesignerWidgetSetDialogUI::languageChange()
{
    setCaption( tr( "Object settings" ) );
    lblLabel->setText( tr( "Label text" ) );
    lblSrc->setText( tr( "Source column or variable" ) );
    lblFunc->setText( tr( "User function" ) );
    lblLookup->setText( tr( "Lookup class name" ) );
    comboDSource->clear();
    comboDSource->insertItem( tr( "None" ) );
    comboDSource->insertItem( tr( "SQL field" ) );
    comboDSource->insertItem( tr( "Parameter" ) );
    comboDSource->insertItem( tr( "Variable" ) );
    comboDSource->insertItem( tr( "System variable" ) );
    comboDSource->insertItem( tr( "Lookup" ) );
    comboDSource->insertItem( tr( "Text" ) );
    lblPWhen->setText( tr( "Print when expression" ) );
    lblSrcType->setText( tr( "Data source type" ) );
    lblEmbed->setText( tr( "Embed result to string (%1)" ) );
    tab->changeTab( pageData, tr( "&Data source" ) );
    lblType->setText( tr( "Base type of data" ) );
    comboType->clear();
    comboType->insertItem( tr( "Text" ) );
    comboType->insertItem( tr( "Numeric" ) );
    comboType->insertItem( tr( "Date" ) );
    gbNumFormat->setTitle( tr( "Number settings" ) );
    lblNumFormat->setText( tr( "Number format code" ) );
    lblNoDec->setText( tr( "Number of decimals" ) );
    spDec->setSpecialValueText( tr( "Auto" ) );
    lblDecPoint->setText( tr( "Decimal point symbol" ) );
    lblSetSymb->setText( tr( "Separator symbol" ) );
    cbBlankIfZero->setText( tr( "Blank if number equals zero" ) );
    cbThousandSep->setText( tr( "Use thousand separation" ) );
    lblHelpNumF->setText( tr( "(Eg.: Old number format: \"%9.2f\" New localized number format: \"%L1;9f2\" )" ) );
    gbDateFormat->setTitle( tr( "Date settings" ) );
    lblDateFmt->setText( tr( "Date format code" ) );
    tab->changeTab( TabPage, tr( "Data &format" ) );
    btnSelFont->setText( tr( "..." ) );
    lblFont->setText( tr( "Font style" ) );
    comboFontSize->clear();
    comboFontSize->insertItem( QString::null );
    comboFontSize->insertItem( tr( "6" ) );
    comboFontSize->insertItem( tr( "8" ) );
    comboFontSize->insertItem( tr( "9" ) );
    comboFontSize->insertItem( tr( "10" ) );
    comboFontSize->insertItem( tr( "11" ) );
    comboFontSize->insertItem( tr( "12" ) );
    comboFontSize->insertItem( tr( "14" ) );
    comboFontSize->insertItem( tr( "16" ) );
    comboFontSize->insertItem( tr( "18" ) );
    comboFontSize->insertItem( tr( "20" ) );
    comboFontSize->insertItem( tr( "22" ) );
    comboFontSize->insertItem( tr( "24" ) );
    comboFontSize->insertItem( tr( "26" ) );
    comboFontSize->insertItem( tr( "28" ) );
    comboFontSize->insertItem( tr( "30" ) );
    comboFontSize->insertItem( tr( "32" ) );
    comboFontSize->insertItem( tr( "72" ) );
    lblTxtColor->setText( tr( "Text color" ) );
    lblFontSize->setText( tr( "Font size" ) );
    lblSample->setText( tr( "Sample text" ) );
    cbBold->setText( tr( "Bold" ) );
    cbBold->setAccel( QKeySequence( QString::null ) );
    cbItalic->setText( tr( "Italic" ) );
    cbItalic->setAccel( QKeySequence( QString::null ) );
    cbUnderline->setText( tr( "&Underline" ) );
    cbUnderline->setAccel( QKeySequence( tr( "Alt+U" ) ) );
    cbStrikeout->setText( tr( "Strikeout" ) );
    bgHAlign->setTitle( tr( "Horizontal alignment" ) );
    radioLeft->setText( tr( "&Left" ) );
    radioCenter->setText( tr( "Ce&nter" ) );
    radioCenter->setAccel( QKeySequence( tr( "Alt+N" ) ) );
    radioRight->setText( tr( "Rig&ht" ) );
    radioRight->setAccel( QKeySequence( tr( "Alt+H" ) ) );
    bgVAlign->setTitle( tr( "Vertical alignment" ) );
    radioTop->setText( tr( "Top" ) );
    radioMid->setText( tr( "Middle" ) );
    radioMid->setAccel( QKeySequence( QString::null ) );
    radioBottom->setText( tr( "Bottom" ) );
    radioBottom->setAccel( QKeySequence( QString::null ) );
    cbWordBreak->setText( tr( "Automatic &wordbreak if text is longer" ) );
    cbWordBreak->setAccel( QKeySequence( tr( "Alt+W" ) ) );
    cbRichText->setText( tr( "Use richtext format" ) );
    cbDynamicHeight->setText( tr( "Dymanic height when in details" ) );
    cbLoadFromFile->setText( tr( "Load text from file" ) );
    lblRotat->setText( tr( "Rotation angle" ) );
    tab->changeTab( pageTxt, tr( "&Text style" ) );
    bgBackM->setTitle( tr( "Background mode" ) );
    radioTransp->setText( tr( "Tra&nsparent" ) );
    radioTransp->setAccel( QKeySequence( tr( "Alt+N" ) ) );
    radioFill->setText( tr( "Fi&lled" ) );
    radioFill->setAccel( QKeySequence( tr( "Alt+L" ) ) );
    lblFillcol->setText( tr( "Fill color" ) );
    comboLineStyle->clear();
    comboLineStyle->insertItem( tr( "Solid" ) );
    comboLineStyle->insertItem( tr( "Dashed" ) );
    comboLineStyle->insertItem( tr( "Dotted" ) );
    comboLineStyle->insertItem( tr( "Dash+dot" ) );
    comboLineStyle->insertItem( tr( "Dash+dot+dot" ) );
    comboLineStyle->insertItem( tr( "None" ) );
    lblLinesty->setText( tr( "Line style" ) );
    lblLinecol->setText( tr( "Line color" ) );
    lblLinew->setText( tr( "Line width" ) );
    tab->changeTab( pageLine, tr( "L&ine/Border style" ) );
    buttonApply->setText( tr( "Appl&y" ) );
    buttonApply->setAccel( QKeySequence( tr( "Alt+Y" ) ) );
    buttonOk->setText( tr( "&OK" ) );
    buttonOk->setAccel( QKeySequence( QString::null ) );
    buttonCancel->setText( tr( "&Cancel" ) );
    buttonCancel->setAccel( QKeySequence( QString::null ) );
}

void NCReportDesignerWidgetSetDialogUI::applyOptions()
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::applyOptions(): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::fontStyleChanged(const QString&)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::fontStyleChanged(const QString&): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::fontSizeChanged(const QString&)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::fontSizeChanged(const QString&): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::fontColorChanged(const QString&)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::fontColorChanged(const QString&): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::fontBoldChanged(bool)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::fontBoldChanged(bool): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::fontItalicChanged(bool)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::fontItalicChanged(bool): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::fontUnderlineChanged(bool)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::fontUnderlineChanged(bool): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::fontStrikeChanged(bool)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::fontStrikeChanged(bool): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::alignHChanged(int)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::alignHChanged(int): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::alignVChanged(int)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::alignVChanged(int): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::backModeChanged(int)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::backModeChanged(int): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::selectFont()
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::selectFont(): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::changedDataType(int)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::changedDataType(int): Not implemented yet" );
}

