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
#include "reportvariablelistview.h"
#include "ncreportdesignerdocument.h"


ReportVariableListView::ReportVariableListView( QWidget *parent, const char* name )
	: QListView( parent, name )
{
	checkable = FALSE;
	addColumn( tr("Name") );
	addColumn( tr("Field") );
	addColumn( tr("F.type") );
	addColumn( tr("Type") );
	setAllColumnsShowFocus( TRUE );
}

ReportVariableListView::~ReportVariableListView() {}

void ReportVariableListView::load( QMap<QString,ReportVariable> & source )
{
	QMap<QString,ReportVariable>::ConstIterator it;
	for ( it = source.begin(); it != source.end(); ++it )
		addVariable( it.data(), FALSE );
	
	//setCurrentItem( lastItem() );
}

void ReportVariableListView::setCheckable( bool set )
{
	checkable = set;
}

QString ReportVariableListView::selectedVarList( )
{
	if ( !checkable )
		return QString::null;
	
	QCheckListItem* citem =0;
	QString vars;			
	QListViewItemIterator it( this );
	while ( it.current() ) {
		citem = (QCheckListItem*)it.current();
		if ( citem->isOn() )
			vars+=citem->text(0)+",";
		++it;
	}
	
	vars.truncate( vars.length()-1 );
	
	return vars;
}

void ReportVariableListView::updateChecked( const QString & varlist )
{
	if ( !checkable )
		return;
	
	reset();
	QStringList lst( QStringList::split( ",", varlist ) );
	QStringList::Iterator it = lst.begin();
	QListViewItem *item=0;
	for ( ; it != lst.end(); ++it ) {
		item = findItem( *it, 0 );
		if ( item )
			((QCheckListItem*)item)->setOn( TRUE );
	}
}

void ReportVariableListView::reset( )
{
	if ( !checkable )
		return;
	
	QListViewItemIterator it( this );
	while ( it.current() ) {
		((QCheckListItem*)it.current())->setOn( FALSE );
		++it;
	}
}

void ReportVariableListView::updateCurrentItem( const ReportVariable &v )
{
	QListViewItem *item = currentItem();
	if ( !item )
		return;
	updateItem( item, v );
}

QString ReportVariableListView::currentVarName( )
{
	QListViewItem *item = currentItem();
	if ( !item )
		return QString::null;
	return item->text(0);
}

void ReportVariableListView::addVariable( const ReportVariable &v, bool setCurrent )
{
	QListViewItem *item;
	if (checkable)
		item = new QCheckListItem( this, "", QCheckListItem::CheckBox );
	else		
		item = new QListViewItem( this );
	updateItem( item, v );
	if( setCurrent )
		setCurrentItem( item );
}

void ReportVariableListView::updateItem( QListViewItem *item, const ReportVariable &v )
{
	item->setText(0, v.name );
	item->setText(1, v.field );
	item->setText(2, v.funcType );
	item->setText(3, v.type );					   
}


