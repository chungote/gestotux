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
#include "diavariable.h"
#include "reportvariablelistview.h"
#include "ncreportdesignerdocument.h"

/*
#include <qvariant.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>*/


/*
 *  Constructs a diaVariable as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
diaVariable::diaVariable( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "diaVariable" );
    diaVariableLayout = new QHBoxLayout( this, 6, 6, "diaVariableLayout");

    layLeft = new QVBoxLayout( 0, 0, 6, "layLeft");

    gbVar = new QGroupBox( this, "gbVar" );
    gbVar->setColumnLayout(0, Qt::Vertical );
    gbVar->layout()->setSpacing( 6 );
    gbVar->layout()->setMargin( 6 );
    gbVarLayout = new QGridLayout( gbVar->layout() );
    gbVarLayout->setAlignment( Qt::AlignTop );

    comboFunc = new QComboBox( FALSE, gbVar, "comboFunc" );

    gbVarLayout->addWidget( comboFunc, 0, 3 );

    lblType = new QLabel( gbVar, "lblType" );

    gbVarLayout->addWidget( lblType, 1, 2 );

    lblField = new QLabel( gbVar, "lblField" );

    gbVarLayout->addWidget( lblField, 1, 0 );

    lblFunc = new QLabel( gbVar, "lblFunc" );

    gbVarLayout->addWidget( lblFunc, 0, 2 );

    comboType = new QComboBox( FALSE, gbVar, "comboType" );

    gbVarLayout->addWidget( comboType, 1, 3 );

    leField = new QLineEdit( gbVar, "leField" );

    gbVarLayout->addWidget( leField, 1, 1 );

    lblName = new QLabel( gbVar, "lblName" );

    gbVarLayout->addWidget( lblName, 0, 0 );

    leName = new QLineEdit( gbVar, "leName" );

    gbVarLayout->addWidget( leName, 0, 1 );
    layLeft->addWidget( gbVar );

    listVars = new ReportVariableListView( this, "listVars" );
    layLeft->addWidget( listVars );
    diaVariableLayout->addLayout( layLeft );

    layBtn = new QVBoxLayout( 0, 0, 6, "layBtn");

    btnNew = new QPushButton( this, "btnNew" );
    layBtn->addWidget( btnNew );

    btnDelete = new QPushButton( this, "btnDelete" );
    layBtn->addWidget( btnDelete );
    spBtn = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layBtn->addItem( spBtn );

    btnOK = new QPushButton( this, "btnOK" );
    layBtn->addWidget( btnOK );

    btnCancel = new QPushButton( this, "btnCancel" );
    layBtn->addWidget( btnCancel );
    diaVariableLayout->addLayout( layBtn );
    languageChange();
    resize( QSize(539, 315).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( btnOK, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( btnCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
	connect( btnNew, SIGNAL( clicked() ), this, SLOT( newVariable() ) );
	connect( btnDelete, SIGNAL( clicked() ), this, SLOT( removeVariable() ) );

	connect( leName, SIGNAL(textChanged(const QString&)), this, SLOT(_change_name(const QString&)) );
	connect( leField, SIGNAL(textChanged(const QString&)), this, SLOT(_change_field(const QString&)) );
	connect( comboFunc, SIGNAL(activated(const QString&)), this, SLOT(_change_function(const QString&)) );
	connect( comboType, SIGNAL(activated(const QString&)), this, SLOT(_change_datatype(const QString&)) );

	connect( listVars, SIGNAL(currentChanged(QListViewItem*)), this, SLOT(_change_listView(QListViewItem*)) );

    // tab order
    setTabOrder( leName, leField );
    setTabOrder( leField, comboFunc );
    setTabOrder( comboFunc, comboType );
    setTabOrder( comboType, listVars );
    setTabOrder( listVars, btnNew );
    setTabOrder( btnNew, btnDelete );
    setTabOrder( btnDelete, btnOK );
    setTabOrder( btnOK, btnCancel );

	refreshForm( FALSE );
}

/*
 *  Destroys the object and frees any allocated resources
 */
diaVariable::~diaVariable()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void diaVariable::languageChange()
{
    setCaption( tr( "Report variables" ) );
    gbVar->setTitle( tr( "Variable settings" ) );

    comboFunc->clear();
    comboFunc->insertItem( tr( "sum" ) );
    comboFunc->insertItem( tr( "count" ) );
    comboFunc->insertItem( tr( "average" ) );

    lblType->setText( tr( "Data type" ) );
    lblField->setText( tr( "SQL field" ) );
    lblFunc->setText( tr( "Function type" ) );

	comboType->clear();
    comboType->insertItem( tr( "numeric" ) );
    comboType->insertItem( tr( "text" ) );
    comboType->insertItem( tr( "date" ) );

	lblName->setText( tr( "Name" ) );
    btnNew->setText( tr( "New variable" ) );
    btnDelete->setText( tr( "Delete" ) );
    btnOK->setText( tr( "OK" ) );
    btnCancel->setText( tr( "Cancel" ) );
}

void diaVariable::_change_name(const QString& )
{
	dataChange( TRUE, FALSE, FALSE, FALSE );
}

void diaVariable::_change_field(const QString&)
{
	dataChange( FALSE, TRUE, FALSE, FALSE );
}

void diaVariable::_change_function(const QString&)
{
	dataChange( FALSE, FALSE, TRUE, FALSE );
}

void diaVariable::_change_datatype(const QString&)
{
	dataChange( FALSE, FALSE, FALSE, TRUE );
}

void diaVariable::_change_listView( QListViewItem * )
{
	QString name = listVars->currentVarName();
	if ( variables.contains(name) ) {
		setLineEditValue( leName, name );
		setLineEditValue( leField, variables[name].field );
		setComboBoxValue( comboFunc, variables[name].funcType );
		setComboBoxValue( comboType, variables[name].type );
	} else {
		//clearWidgets();
	}
}

void diaVariable::newVariable()
{
	clearWidgets();
	refreshForm( TRUE );

	QString name("Var0");

	ReportVariable v;
	v.name = name;
	v.field = "";
	v.funcType = "sum";
	v.type = "numeric";
	variables[name] = v;

	listVars->addVariable( v, TRUE );
	// same as currItem?

	setLineEditValue( leName, name );
	leName->selectAll();
	leName->setFocus();
}

void diaVariable::removeVariable()
{
	QString name = listVars->currentVarName();
	if ( !name.isEmpty() ) {
		if ( listVars->currentItem() )
			delete listVars->currentItem();
		variables.remove( name );
	}
}

void diaVariable::applySettings()
{
	document->variables = variables;	// copy map
}

void diaVariable::setLineEditValue( QLineEdit *le, const QString & value )
{
	le->blockSignals(TRUE);
	le->setText( value );
	le->blockSignals(FALSE);
}

void diaVariable::setComboBoxValue( QComboBox *combo, const QString & value )
{
	combo->blockSignals(TRUE);
	combo->setCurrentText( value );
	combo->blockSignals(FALSE);
}


void diaVariable::assignDocument( NCReportDesignerDocument * doc )
{
	document = doc;
	// load from map
	variables = doc->variables;	// copy map
	listVars->load( variables );	// load variables
	if ( listVars->childCount() >0 )
		refreshForm( TRUE );
	if ( listVars->childCount() == 1 )
		_change_listView( listVars->currentItem() );

}

void diaVariable::refreshForm( bool enable )
{
	leName->setEnabled( enable );
	leField->setEnabled( enable );
	comboFunc->setEnabled( enable );
	comboType->setEnabled( enable );
}

void diaVariable::dataChange( bool changeName, bool changeField, bool changeFunc, bool changeDataType )
{
	QString name_old = listVars->currentVarName();
	QString name_new = leName->text();

	ReportVariable v = variables[name_old];

	if ( changeName ) {
		variables.remove(name_old);
	}
	if ( changeName )
		v.name = name_new;
	if ( changeField )
		v.field = leField->text();
	if ( changeFunc )
		v.funcType = comboFunc->currentText();
	if ( changeDataType )
		v.type = comboType->currentText();

	variables[name_new]=v;

	listVars->updateCurrentItem( v );
}

void diaVariable::clearWidgets( )
{
	setLineEditValue( leName, "" );
	setLineEditValue( leField, "" );
	setComboBoxValue( comboFunc, "sum" );
	setComboBoxValue( comboType, "numeric" );
}




