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
#include "ncreportdesignerwidgetsetdialog.h"
#include "ncreportdesignerwidget.h"
#include "ncreportdesignerdocument.h"
#include "nccolorcombo.h"

#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QFontDialog>
#include <QButtonGroup>
#include <QGroupBox>


NCReportDesignerWidgetSetDialog::NCReportDesignerWidgetSetDialog( NCReportDesignerWidget *dwidget, QWidget* parent, NCReportDesignerDocument *doc,
		const char* name, bool modal, Qt::WindowFlags fl)
: Ui_NCReportDesignDialogBase(), QDialog( parent, fl )
{
	this->setObjectName( name );
	this->setModal( modal );
	dw = dwidget;
	document = doc;
	init();

	changedDataType(0);

	loadOptions();
	p = 0;	// no property
}

NCReportDesignerWidgetSetDialog::~NCReportDesignerWidgetSetDialog()
{
}

void NCReportDesignerWidgetSetDialog::setWidget( NCReportDesignerWidget *w )
{
	dw = w;
}

void NCReportDesignerWidgetSetDialog::setSaveToProperty( WProperty * prop )
{
	p = prop;
}

void NCReportDesignerWidgetSetDialog::setDocument( NCReportDesignerDocument *doc )
{
	document = doc;
}

void NCReportDesignerWidgetSetDialog::loadOptions( )
{
	//---------------------
	// DATA SOURCE
	//---------------------
	int idx=0;
	if ( dw->wtype == NCReportDesignerWidget::Label ) {
		textLabel->setText( dw->p.text );
		leSource->setEnabled( FALSE );
		pageLine->setEnabled( FALSE );
		comboDSource->setEnabled( FALSE );
		textLabel->setFocus();
		textLabel->selectAll();
	} else if ( dw->wtype == NCReportDesignerWidget::Field ) {

		leSource->setText( dw->p.text );
		leEmbed->setText( dw->p.embedString );
		leFunction->setText( dw->p.callFunction );
		leLookup->setText( dw->p.lookupClass );
		textLabel->setEnabled( FALSE );
		pageLine->setEnabled( FALSE );

		if ( dw->p.ftype == "none" || dw->p.ftype.isEmpty() ) idx = 0;
		else if ( dw->p.ftype == "sql" ) idx = 1;
		else if ( dw->p.ftype == "par" ) idx = 2;
		else if ( dw->p.ftype == "var" ) idx = 3;
		else if ( dw->p.ftype == "sys" ) idx = 4;
		else if ( dw->p.ftype == "lookup" ) idx = 5;
		else if ( dw->p.ftype == "text" ) idx = 6;
		comboDSource->setCurrentIndex( idx );

		if ( dw->p.type == "text" ) idx = 0;
		else if ( dw->p.type == "numeric" ) idx = 1;
		else if ( dw->p.type == "date" ) idx = 2;
		else if ( dw->p.type.isEmpty() ) idx = 0;
		comboType->setCurrentIndex( idx );

		changedDataType( idx );
		//---------------------
		// FORMAT
		//---------------------
		leNumFormat->setText( dw->p.numFormat );
		leDateFormat->setText( dw->p.dateFormat );
		spDec->setValue( dw->p.numDigitNo );
		leDecPoint->setText( QString("%1").arg(dw->p.numDigitPoint) );
		leSeparator->setText( QString("%1").arg(dw->p.numSeparator) );
		cbThousandSep->setChecked( dw->p.numSeparation );
		cbBlankIfZero->setChecked( dw->p.numBlankIfZero );


		leSource->setFocus();
		leSource->selectAll();
	}
	lePrintWhen->setText( dw->p.printWhen );

	if ( dw->wtype == NCReportDesignerWidget::Label || dw->wtype == NCReportDesignerWidget::Field ) {
		//---------------------
		// TEXT STYLE
		//---------------------
		QString s = dw->p.fontName;
		if ( s == document->po.defaultFontName )
			s = QString::null;

		leFont->setText( dw->p.fontName );
		comboFontSize->setEditText( QString::number(dw->p.fontSize) );
		//comboColor->setColor( dw->p.forecolor );
	/*	idx=1;
		switch ( dw->p.fontWeight ) {
			case QFont::Light: idx=0; break;
			case QFont::Normal: idx=1; break;
			case QFont::DemiBold: idx=2; break;
			case QFont::Bold: idx=3; break;
			case QFont::Black: idx=4; break;
		}*/
		cbBold->setChecked( dw->p.fontWeight==QFont::Bold );


		cbItalic->setChecked( dw->p.fontItalic );
		cbUnderline->setChecked( dw->p.fontUnderline );
		cbStrikeout->setChecked( dw->p.fontStrikeOut );
		idx = 0;
		switch ( dw->p.alignmentH ) {
			case Qt::AlignLeft: idx=0; radioLeft->setChecked(true); break;
			case Qt::AlignHCenter: idx=1; radioCenter->setChecked( true ); break;
			case Qt::AlignRight: idx=2; radioRight->setChecked( true ); break;
			default: idx=0;
		}
		switch ( dw->p.alignmentV ) {
			case Qt::AlignTop: idx=0; radioTop->setChecked( true ); break;
			case Qt::AlignVCenter: idx=1; radioMid->setChecked( true ); break;
			case Qt::AlignBottom: idx=2; radioBottom->setChecked( true ); break;
			default: idx=0;
		}

		cbWordBreak->setChecked( dw->p.wordbreak );
		spinRotation->setValue( dw->p.rotation );
		cbRichText->setChecked( dw->p.isRichText );
		cbDynamicHeight->setChecked( dw->p.dynamicHeight );
		cbLoadFromFile->setChecked( dw->p.loadFromFile );

		alignVChanged(0);
	}
	if ( dw->wtype == NCReportDesignerWidget::Line ||
			dw->wtype == NCReportDesignerWidget::Rectangle
			|| dw->wtype == NCReportDesignerWidget::Circle ) {

		//---------------------
		// LINE/RECTANGLE STYLE
		//---------------------

		textLabel->setEnabled( FALSE );
		leSource->setEnabled( FALSE );
		comboDSource->setEnabled( FALSE );
		TabPage->setCurrentIndex( 3 );
		TabPage->removeTab(TabPage->indexOf(TabPage)); //TabPage->hide(); //setEnabled( FALSE );
		TabPage->removeTab(TabPage->indexOf(pageTxt)); //pageTxt->hide(); //setEnabled( FALSE );


		radioTransp->setChecked( dw->p.fillStyle == WProperty::transparent ? false : true );
		spinLineWidth->setValue( dw->p.lineWidth );
		idx =0;
		switch ( dw->p.lineStyle ) {
			case Qt::SolidLine: idx=0; break;
			case Qt::DashLine: idx=1; break;
			case Qt::DotLine: idx=2; break;
			case Qt::DashDotLine: idx=3; break;
			case Qt::DashDotDotLine: idx=4; break;
			case Qt::NoPen: idx=5; break;
			default: idx=0;
		}
		comboLineStyle->setCurrentIndex(idx);
		comboColorL->setColor( dw->p.lineColor );
		comboColorF->setColor( dw->p.fillColor );
	}
	if ( dw->wtype == NCReportDesignerWidget::Image ) {
		//---------------------
		// IMAGE/PIXMAP
		//---------------------

		textLabel->setEnabled( FALSE );
		//leSource->setEnabled( FALSE );
		comboDSource->setEnabled( FALSE );
		TabPage->setEnabled( FALSE );
		TabPage->removeTab(TabPage->indexOf(pageTxt)); //pageTxt->hide(); //setEnabled( FALSE );
		TabPage->removeTab(TabPage->indexOf(pageLine)); //pageLine->hide(); //setEnabled( FALSE );

		leSource->setText( dw->p.resource.isEmpty() ? dw->p.text : dw->p.resource );
		leSource->setFocus();
		leSource->selectAll();

	}

}


/*$SPECIALIZATION$*/
void NCReportDesignerWidgetSetDialog::backModeChanged(int)
{
}

void NCReportDesignerWidgetSetDialog::alignHChanged(int i)
{
	alignVChanged( i );
}

void NCReportDesignerWidgetSetDialog::alignVChanged( int )
{
        /*
	int h = bgHAlign->checkedId();
	int v = bgVAlign->checkedId();
	Qt::AlignmentFlag fh,fv;
	//int fh,fv;
	switch (h) {
		case 0: fh = Qt::AlignLeft; break;
		case 1: fh = Qt::AlignHCenter; break;
		case 2: fh = Qt::AlignRight; break;
		default: fh = Qt::AlignLeft;
	}
	switch (v) {
		case 0: fv = Qt::AlignTop; break;
		case 1: fv = Qt::AlignVCenter; break;
		case 2: fv = Qt::AlignBottom; break;
		default: fv = Qt::AlignTop;
	}

	//lblSample->setAlignment( fh | fv );
	lblSample->setAlignment( fh | fv );*/
}


void NCReportDesignerWidgetSetDialog::fontStrikeChanged( bool )
{
}

void NCReportDesignerWidgetSetDialog::fontUnderlineChanged( bool )
{
}

void NCReportDesignerWidgetSetDialog::fontItalicChanged( bool )
{
}

void NCReportDesignerWidgetSetDialog::fontBoldChanged( bool )
{
}

void NCReportDesignerWidgetSetDialog::fontColorChanged(const QString&)
{
}

void NCReportDesignerWidgetSetDialog::fontSizeChanged(const QString&)
{
}

void NCReportDesignerWidgetSetDialog::fontStyleChanged(const QString&)
{
}

void NCReportDesignerWidgetSetDialog::applyOptions()
{
	saveSettings();
	dw->updateWidget();
}


void NCReportDesignerWidgetSetDialog::init( )
{
	//buttonOk->setShortcut(QKeySequence( "CTRL+Enter" ) );

}

void NCReportDesignerWidgetSetDialog::saveSettings( )
{
	if (!p)
		return;

	if ( dw->wtype == NCReportDesignerWidget::Label ) {
		p->text = textLabel->toPlainText();
	} else if ( dw->wtype == NCReportDesignerWidget::Field ) {

		p->text = leSource->text();
		p->embedString = leEmbed->text();
		p->callFunction = leFunction->text();

		switch( comboDSource->currentIndex() ) {
			case 0: p->ftype=QString::null; break;
			case 1: p->ftype="sql"; break;
			case 2: p->ftype="par"; break;
			case 3: p->ftype="var"; break;
			case 4: p->ftype="sys"; break;
			case 5: p->ftype="lookup"; break;
			case 6: p->ftype="text"; break;
		}
		switch( comboType->currentIndex() ) {
			case 0: p->type=QString::null; break;
			case 1: p->type="numeric"; break;
			case 2: p->type="date"; break;
		}

		if ( !leSource->text().isEmpty() && comboDSource->currentIndex() == 0 )
			p->ftype="sql";

	}
	p->printWhen = lePrintWhen->text();

	if ( dw->wtype == NCReportDesignerWidget::Label || dw->wtype == NCReportDesignerWidget::Field ) {
		//---------------------
		// TEXT STYLE
		//---------------------
		p->fontName = leFont->text();
		if ( p->fontName.isEmpty() && !document->po.defaultFontName.isEmpty() )
			p->fontName = document->po.defaultFontName;

		p->fontSize = comboFontSize->currentText().toInt();
		//if ( document->po.defaultFontSize > p->fontSize

		p->forecolor = comboColor->color();
		p->fontWeight = ( cbBold->isChecked() ? QFont::Bold : QFont::Normal );
		p->fontItalic = cbItalic->isChecked();
		p->fontUnderline = cbUnderline->isChecked();
		p->fontStrikeOut = cbStrikeout->isChecked();
		if( radioLeft->isChecked() ) { p->alignmentH = Qt::AlignLeft; }
		if( radioCenter->isChecked() ) { p->alignmentH = Qt::AlignHCenter; }
		if( radioRight->isChecked() ) { p->alignmentH = Qt::AlignRight; }

		if( radioTop->isChecked() ) { p->alignmentV = Qt::AlignTop; }
		if( radioMid->isChecked() ) { p->alignmentV = Qt::AlignVCenter; }
		if( radioBottom->isChecked() ) { p->alignmentV = Qt::AlignBottom; }
		p->wordbreak = cbWordBreak->isChecked();

		//---------------------
		// FORMAT
		//---------------------
		dw->p.numFormat = leNumFormat->text();
		dw->p.dateFormat = leDateFormat->text();
		dw->p.numDigitNo = spDec->value();
		dw->p.numDigitPoint = leDecPoint->text().at(0).toLatin1();
		dw->p.numSeparator = leSeparator->text().at(0).toLatin1();
		dw->p.numSeparation = cbThousandSep->isChecked();
		dw->p.numBlankIfZero = cbBlankIfZero->isChecked();
		dw->p.isRichText = cbRichText->isChecked();
		dw->p.dynamicHeight = cbDynamicHeight->isChecked();
		dw->p.loadFromFile = cbLoadFromFile->isChecked();

	}
	if ( dw->wtype == NCReportDesignerWidget::Line || dw->wtype == NCReportDesignerWidget::Rectangle || dw->wtype == NCReportDesignerWidget::Circle ) {
		//---------------------
		// LINE/RECTANGLE STYLE
		//---------------------
		if ( dw->wtype == NCReportDesignerWidget::Rectangle )
			p->fillStyle = ( radioTransp->isChecked() ? WProperty::transparent : WProperty::filled );
		p->lineWidth = spinLineWidth->value();
		switch ( comboLineStyle->currentIndex() ) {
			case 0: p->lineStyle = Qt::SolidLine; break;
			case 1: p->lineStyle = Qt::DashLine; break;
			case 2: p->lineStyle = Qt::DotLine; break;
			case 3: p->lineStyle = Qt::DashDotLine; break;
			case 4: p->lineStyle = Qt::DashDotDotLine; break;
			case 5: p->lineStyle = Qt::NoPen; break;
		}
		p->lineColor = comboColorL->color();
		p->fillColor = comboColorF->color();
	}
	if ( dw->wtype == NCReportDesignerWidget::Image ) {
		p->resource = leSource->text();
	}


}

void NCReportDesignerWidgetSetDialog::selectFont( )
{
	bool ok;
	QFont font = QFontDialog::getFont( &ok, QFont( leFont->text(), comboFontSize->currentText().toInt() ), this );
	if ( ok ) {
        // font is set to the font the user selected
		leFont->setText( font.family() );
		comboFontSize->setEditText( QString::number(font.pointSize()) );
		cbBold->setChecked( font.bold() );
		cbItalic->setChecked( font.italic() );
		cbStrikeout->setChecked( font.strikeOut() );
	} else {
	}
}

void NCReportDesignerWidgetSetDialog::changedDataType( int idx )
{
	bool isnum = FALSE;
	bool isdate = FALSE;
	switch (idx) {
		case 1: isnum = TRUE; break;
		case 2: isdate = TRUE; break;
	}
	gbNumFormat->setEnabled(isnum);
	gbDateFormat->setEnabled(isdate);

}






