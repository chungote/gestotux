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
#include "diagroup.h"
#include "ncreportdesignerdocument.h"
#include "reportvariablelistview.h"

// #include <qvariant.h>
// #include <qpushbutton.h>
// #include <qlistbox.h>
// #include <qbuttongroup.h>
// #include <qlabel.h>
// #include <qlineedit.h>
// #include <qheader.h>
// #include <qlistview.h>
// #include <qlayout.h>
// #include <qtooltip.h>
// #include <qwhatsthis.h>
// #include <qimage.h>
// #include <qpixmap.h>
// #include <qmessagebox.h>

diaGroup::diaGroup( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
	: QDialog( parent, modal, fl )
{
    if ( !name )
	setObjectName( "diaGroup" );
    else
        setObjectName( name );

	currItem = 0;

    diaGroupLayout = new QVBoxLayout( this, 6, 6, "diaGroupLayout");

    layGroup = new QHBoxLayout( 0, 0, 6, "layGroup");

    listGroups = new QListBox( this, "listGroups" );
    listGroups->setMaximumSize( QSize( 150, 32767 ) );
    layGroup->addWidget( listGroups );

    layGB = new QVBoxLayout( 0, 0, 6, "layGB");

    btnNew = new QPushButton( this, "btnNew" );
	btnNew->setAutoDefault( FALSE );
    layGB->addWidget( btnNew );

    btnRemove = new QPushButton( this, "btnRemove" );
	btnRemove->setAutoDefault( FALSE );
	layGB->addWidget( btnRemove );
    spGB = new QSpacerItem( 20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layGB->addItem( spGB );

    btnUp = new QPushButton( this, "btnUp" );
	btnUp->setAutoDefault( FALSE );
	layGB->addWidget( btnUp );

    btnDown = new QPushButton( this, "btnDown" );
	btnDown->setAutoDefault( FALSE );
	layGB->addWidget( btnDown );
    layGroup->addLayout( layGB );

    bgGroup = new QButtonGroup( this, "bgGroup" );
    bgGroup->setColumnLayout(0, Qt::Vertical );
    bgGroup->layout()->setSpacing( 6 );
    bgGroup->layout()->setMargin( 6 );
    bgGroupLayout = new QVBoxLayout( bgGroup->layout() );
    bgGroupLayout->setAlignment( Qt::AlignTop );

    layNames = new QGridLayout( 0, 1, 1, 0, 6, "layNames");

    lblName = new QLabel( bgGroup, "lblName" );

    layNames->addWidget( lblName, 0, 0 );

    lblExp = new QLabel( bgGroup, "lblExp" );

    layNames->addWidget( lblExp, 1, 0 );

    leExpr = new QLineEdit( bgGroup, "leExpr" );

    layNames->addWidget( leExpr, 1, 1 );

    leName = new QLineEdit( bgGroup, "leName" );

    layNames->addWidget( leName, 0, 1 );
    bgGroupLayout->addLayout( layNames );

    lblVars = new QLabel( bgGroup, "lblVars" );
    bgGroupLayout->addWidget( lblVars );

	listVars = new ReportVariableListView( bgGroup, "listVars" );
	listVars->setCheckable( TRUE );
    bgGroupLayout->addWidget( listVars );
    layGroup->addWidget( bgGroup );
    diaGroupLayout->addLayout( layGroup );

    layBtn = new QHBoxLayout( 0, 0, 6, "layBtn");
    spButt = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    layBtn->addItem( spButt );

    btnApply = new QPushButton( this, "btnApply" );
    layBtn->addWidget( btnApply );

    btnOK = new QPushButton( this, "btnOK" );
    layBtn->addWidget( btnOK );

    btnCancel = new QPushButton( this, "btnCancel" );
    layBtn->addWidget( btnCancel );
    diaGroupLayout->addLayout( layBtn );
    languageChange();
    resize( QSize(580, 351).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( btnCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( btnOK, SIGNAL( clicked() ), this, SLOT( accept() ) );
	connect( btnApply, SIGNAL( clicked() ), this, SLOT( applyGroupSettings() ) );
	connect( btnNew, SIGNAL( clicked() ), this, SLOT( newGroup() ) );
    connect( btnRemove, SIGNAL( clicked() ), this, SLOT( removeGroup() ) );
    connect( btnUp, SIGNAL( clicked() ), this, SLOT( moveUp() ) );
    connect( btnDown, SIGNAL( clicked() ), this, SLOT( moveDown() ) );
    connect( listGroups, SIGNAL( currentChanged(QListBoxItem*) ), this, SLOT( groupChanged(QListBoxItem*) ) );

	//connect( leName, SIGNAL(lostFocus()), this, SLOT(groupNameChanged()) );
	connect( leName, SIGNAL(textChanged(const QString&)), this, SLOT(_changed_name(const QString&)) );
	connect( leExpr, SIGNAL(textChanged(const QString&)), this, SLOT(_changed_expr(const QString&)) );
	connect( listVars, SIGNAL(clicked(QListViewItem*)), this, SLOT(_changed_resetvars(QListViewItem*)) );

    // tab order
	setTabOrder( listGroups, btnNew );
	setTabOrder( btnNew, btnRemove );
	setTabOrder( btnRemove, btnUp );
	setTabOrder( btnUp, btnDown );
	setTabOrder( btnDown, leName );
	setTabOrder( leName, leExpr );
	setTabOrder( leExpr, listVars );
	setTabOrder( listVars, btnApply );
	setTabOrder( btnApply, btnOK );
	setTabOrder( btnOK, btnCancel );

	refreshForm( FALSE );
}

/*
 *  Destroys the object and frees any allocated resources
 */
diaGroup::~diaGroup()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void diaGroup::languageChange()
{
    setCaption( tr( "Group settings" ) );
    listGroups->clear();
    listGroups->insertItem( tr( "New Item" ) );
    btnNew->setText( tr( "New group" ) );
    btnRemove->setText( tr( "Remove group" ) );
    btnUp->setText( tr( "Level up" ) );
    btnDown->setText( tr( "Level down" ) );
    bgGroup->setTitle( tr( "Group settings" ) );
    lblName->setText( tr( "Group name" ) );
	lblExp->setText( tr( "Group expression (field)" ) );
    lblVars->setText( tr( "Reset variables" ) );
    listVars->header()->setLabel( 0, tr( "Variable" ) );
    listVars->clear();
    //QListViewItem * item = new QListViewItem( listVars, 0 );
    //item->setText( 0, tr( "variable" ) );

    btnApply->setText( tr( "Apply" ) );
    btnOK->setText( tr( "OK" ) );
    btnCancel->setText( tr( "Cancel" ) );
}

void diaGroup::newGroup( )
{
	clearWidgets();
	refreshForm( TRUE );


	QString gname = tr("<New group>");

	listGroups->insertItem( gname );
	// same as currItem?
	QListBoxItem *item = listGroups->findItem( gname );
	if (!item)
		return;
	currItem = item;
	listGroups->setCurrentItem( item );
	ReportGroup g;
	g.name = gname;
	groups[gname] = g;

	setLineEditValue( leName, gname );
	leName->selectAll();
	leName->setFocus();
}

void diaGroup::removeGroup( )
{
	if ( !currItem )
		return;

	groups.remove( currItem->text() );
	listGroups->removeItem( listGroups->currentItem() );
}

void diaGroup::moveUp( )
{
}

void diaGroup::moveDown( )
{
}

void diaGroup::groupChanged( QListBoxItem *item )
{
	if ( !item )
		return;

	currItem = item;

	QString name = item->text();
	if ( groups.contains(name) ) {

		//leName->setText( document->groups[name].name );
		setLineEditValue( leName, name );
		setLineEditValue( leExpr, groups[name].groupExpression );
		listVars->updateChecked( groups[name].resetVariables );

	} else {
		//clearWidgets();
	}
}

void diaGroup::clearWidgets( )
{
	setLineEditValue( leName, "" );
	setLineEditValue( leExpr, "" );
	listVars->reset();
}

void diaGroup::refreshForm( bool enable )
{
	//bool enabled = (currItem!=0);
	leName->setEnabled( enable );
	leExpr->setEnabled( enable );
	listVars->setEnabled( enable );
}


/*
	if ( !currItem )
	return;
	QListBoxItem *item = listGroups->findItem( n );
	if ( item ) {
		if ( item == currItem ) { //same as before
			return;
		} else {
			//leName->setText( oldn );
			//return;
		}
	}
*/

void diaGroup::_changed_name( const QString & name )
{
	//listGroups->currentItem();
	groupDataChange( listGroups->currentText(), name, TRUE, FALSE, FALSE );
}

void diaGroup::_changed_expr( const QString & )
{
	groupDataChange( leName->text(), leName->text(), FALSE, TRUE, FALSE );
}

void diaGroup::_changed_resetvars( QListViewItem * item )
{
	//QCheckList
	groupDataChange( leName->text(), leName->text(), FALSE, FALSE, TRUE );
}


void diaGroup::groupDataChange( const QString& gname_old, const QString& gname_new,
								bool changeName, bool changeExpr, bool changeReset )
{
	//bool newname = ( gname_old != gname_new );
	ReportGroup g = groups[gname_old];

	if ( changeName ) {
		groups.remove(gname_old);
	}
	//g.name
	if ( changeName )
		g.name = gname_new;
	if ( changeExpr )
		g.groupExpression = leExpr->text();
	if ( changeReset )
		g.resetVariables = listVars->selectedVarList();

	groups[gname_new]=g;

	if ( changeName && currItem )
		listGroups->changeItem( gname_new, listGroups->index(currItem) );


	listGroups->blockSignals( TRUE );
	if ( changeName )
		listGroups->sort();
	listGroups->blockSignals( FALSE );
}

void diaGroup::assignDocument( NCReportDesignerDocument *doc )
{
	listGroups->clear();
	document = doc;
	// load from map
	groups = doc->groups;	// copy map

	QMap<QString,ReportGroup>::ConstIterator it;
	for ( it = doc->groups.begin(); it != doc->groups.end(); ++it )
		listGroups->insertItem( it.data().name );

	listVars->load( doc->variables );	// load variables

	if ( listGroups->count()>0 ) {
		listGroups->setCurrentItem(0);
		refreshForm( TRUE );
	}

}

void diaGroup::setLineEditValue( QLineEdit *le, const QString & value )
{
	le->blockSignals(TRUE);
	le->setText( value );
	le->blockSignals(FALSE);
}

void diaGroup::applyGroupSettings( )
{
	// iterate groups ( ordered by qmap key alias groupname )
	QMap<QString,ReportGroup>::ConstIterator it_dia;
	QMap<QString,ReportGroup>::Iterator it_real;

	it_dia = groups.begin();
	it_real = document->groups.begin();
	int cnt=0;
	while ( it_dia != groups.end() ) {
		cnt++;
		if ( it_real != document->groups.end() ) {
			// have pair
			it_real.data().groupExpression = it_dia.data().groupExpression;
			it_real.data().resetVariables = it_dia.data().resetVariables;

			it_real.data().header->setTitle( tr("Group header")+": "+it_dia.data().name );
			it_real.data().header->Title()->update();
			it_real.data().footer->setTitle( tr("Group footer")+": "+it_dia.data().name );
			it_real.data().footer->Title()->update();

			++it_real;
		} else {
			ReportGroup g( it_dia.data().name, it_dia.data().groupExpression, it_dia.data().resetVariables );
			document->addGroup( g );
			g.header->show();
			g.footer->show();
		}
		++it_dia;
	}
	if ( groups.count() < document->groups.count() ) {
		// Delete if more than at dialog
		QStringList deleteLst;
		QMap<QString,ReportGroup>::ConstIterator it;
		int cnt_del =0;
		for ( it = document->groups.begin(); it != document->groups.end(); ++it ) {
			cnt_del++;
			if (cnt_del>cnt)
				deleteLst.append( it.data().name );	// mark for delete
		}
		for ( QStringList::Iterator it = deleteLst.begin(); it != deleteLst.end(); ++it ) {

			QMessageBox mb( tr("Remove group"),
							tr("Are you sure you want to remove group \"%1\" with all of it's contents?").arg(*it),
							QMessageBox::Question,
							QMessageBox::Yes | QMessageBox::Default,
							QMessageBox::No  | QMessageBox::Escape, 0 );
			if ( mb.exec() == QMessageBox::Yes )
				document->removeGroup( *it );	// remove group

		}


	}


	//for ( it = groups.begin(); it != groups.end(); ++it ) {
}




