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
#include "diaquery.h"
#include "ncreportdesignerdocument.h"
/*
#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlistbox.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qmessagebox.h>*/

/*
 *  Constructs a diaQuery as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
diaQuery::diaQuery( QWidget* parent, const char* name, bool modal, Qt::WFlags fl )
    : QDialog( parent, modal, fl )
{
    if ( !name )
	setObjectName( "query_editor" );
    else
        setObjectName( name );
    query_editorLayout = new QVBoxLayout( this, 6, 6, "query_editorLayout");

    layUp = new QHBoxLayout( 0, 0, 6, "layUp");
	layUp->setResizeMode( QLayout::Minimum );

    layLeft = new QVBoxLayout( 0, 0, 6, "layLeft");

    layName = new QHBoxLayout( 0, 0, 6, "layName");

    lblName = new QLabel( this, "lblName" );
    layName->addWidget( lblName );

    leName = new QLineEdit( this, "leName" );
    layName->addWidget( leName );
    layLeft->addLayout( layName );

    listQuery = new QListBox( this, "listQuery" );
    listQuery->setMinimumSize( QSize( 0, 130 ) );
    listQuery->setMaximumSize( QSize( 32767, 80 ) );
    layLeft->addWidget( listQuery );

    textLabel2 = new QLabel( this, "textLabel2" );
    layLeft->addWidget( textLabel2 );
    layUp->addLayout( layLeft );

    layBtn = new QVBoxLayout( 0, 0, 6, "layBtn");

    btnAdd = new QPushButton( this, "btnAdd" );
    layBtn->addWidget( btnAdd );

    btnRemove = new QPushButton( this, "btnRemove" );
    layBtn->addWidget( btnRemove );

    btnRename = new QPushButton( this, "btnRename" );
    layBtn->addWidget( btnRename );

    btnUp = new QPushButton( this, "btnUp" );
    layBtn->addWidget( btnUp );
    spBtn = new QSpacerItem( 20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding );
    layBtn->addItem( spBtn );

    btnClose = new QPushButton( this, "btnClose" );
    layBtn->addWidget( btnClose );
    layUp->addLayout( layBtn );
    query_editorLayout->addLayout( layUp );

    editQuery = new QTextEdit( this, "editQuery" );
	editQuery->setMinimumHeight( 220 );
	editQuery->setFamily( "Courier" );
    query_editorLayout->addWidget( editQuery );
    languageChange();
    resize( QSize(598, 343).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( btnAdd, SIGNAL( clicked() ), this, SLOT( addQuery() ) );
    connect( btnRemove, SIGNAL( clicked() ), this, SLOT( removeQuery() ) );
    connect( btnRename, SIGNAL( clicked() ), this, SLOT( renameQuery() ) );
    connect( btnUp, SIGNAL( clicked() ), this, SLOT( moveUp() ) );
    connect( btnClose, SIGNAL( clicked() ), this, SLOT( close() ) );

	connect( listQuery, SIGNAL( currentChanged(QListBoxItem *)), this, SLOT(currentChanged( QListBoxItem *)) );
	connect( editQuery, SIGNAL( textChanged()), this, SLOT(qryChanged()) );

}

/*
 *  Destroys the object and frees any allocated resources
 */
diaQuery::~diaQuery()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void diaQuery::languageChange()
{
    setCaption( tr( "Query editor" ) );
    lblName->setText( tr( "Query alias name" ) );
    listQuery->clear();
    listQuery->insertItem( tr( "New Item" ) );
    textLabel2->setText( tr( "SQL query:" ) );
    btnAdd->setText( tr( "Add" ) );
    btnRemove->setText( tr( "Remove" ) );
    btnRename->setText( tr( "Rename" ) );
    btnUp->setText( tr( "Set master" ) );
    btnClose->setText( tr( "Close" ) );
}

void diaQuery::addQuery()
{
	bool ok = TRUE;
	QString val = leName->text().lower();
	if ( val.isEmpty() )
		return;

	for ( int i=0; i<listQuery->count(); ++i ) {
		if ( listQuery->item(i)->text().lower() == val ) {
			ok = false;
			break;
		}
	}
	if ( !ok ) {
		return;
	}
	listQuery->insertItem( val );
	ReportQuery rq;
	rq.alias = val;
	document->queries[val]= rq;

	QListBoxItem *item = listQuery->findItem( val );
	if ( item ) {
		listQuery->setCurrentItem( item );
	}

	leName->clear();

}

void diaQuery::removeQuery()
{
	int curr = listQuery->currentItem();
	if ( curr<0 )
		return;

	QString key = listQuery->currentText();
	QMessageBox mb( tr("Remove query"),
					tr("Are you sure you want to remove query: %1 ?").arg(key),
					QMessageBox::Question,
					QMessageBox::Yes | QMessageBox::Default,
					QMessageBox::No  | QMessageBox::Escape, 0 );
	if ( mb.exec() == QMessageBox::Yes ) {
		document->queries.remove(key);
		listQuery->removeItem( curr );
	}
}

void diaQuery::moveUp()
{
	int c = listQuery->currentItem();
	if ( c < 1 )
		return;

	QString key = listQuery->currentText();
	//reset
	QMap<QString,ReportQuery>::Iterator it;
	for ( it = document->queries.begin(); it != document->queries.end(); ++it )
		it.data().master = FALSE;
	// set as master
	document->queries[key].master = TRUE;

	QListBoxItem *item = listQuery->item( c );
	listQuery->takeItem( item );
	//listQuery->insertItem( item, c-1 );
	listQuery->insertItem( item, 0 );
	listQuery->setCurrentItem( item );
}

void diaQuery::renameQuery()
{
    qWarning( "diaQuery::renameQuery(): Not implemented yet" );
}

void diaQuery::assignDocument( NCReportDesignerDocument *doc )
{
	listQuery->clear();
	document = doc;
	QMap<QString,ReportQuery>::ConstIterator it;
	for ( it = document->queries.begin(); it != document->queries.end(); ++it ) {
		listQuery->insertItem( it.data().alias );
			//ReportGroup g = it.data();
	}

	bool enable = TRUE;
	if ( listQuery->count()>0 ) {
		listQuery->setCurrentItem(0);
	} else
		enable = FALSE;

	editQuery->setEnabled( enable );
}

void diaQuery::currentChanged( QListBoxItem *item )
{
	if ( !item )
		return;

	if ( document->queries.contains(item->text()) ) {
		QString qry = document->queries[item->text()].queryString;
		qry.replace( '\t', QString::null );
		qry = qry.stripWhiteSpace();
		editQuery->setText( qry );
		editQuery->setEnabled( TRUE );

	} else {
		editQuery->clear();
		editQuery->setEnabled( FALSE );
	}
}

void diaQuery::qryChanged( )
{
	if ( listQuery->currentItem()<0 )
		return;

	QString key = listQuery->currentText();
	document->queries[key].queryString = editQuery->text();
}

