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
#ifndef REPORTVARIABLELISTVIEW_H
#define REPORTVARIABLELISTVIEW_H

#include <qlistview.h>
#include <qmap.h>

class ReportVariable;

class ReportVariableListView : public QListView
{
public:
    ReportVariableListView( QWidget *parent, const char* name );
    ~ReportVariableListView();
	
	void addVariable( const ReportVariable&, bool setCurrent );
	void setCheckable( bool );
	void load( QMap<QString,ReportVariable>& source );
	void updateChecked( const QString& varlist );
	void updateCurrentItem( const ReportVariable& ); 
	void reset();
	QString selectedVarList();
	QString currentVarName();
	
private:
	bool checkable;
	void updateItem( QListViewItem*, const ReportVariable& ); 
	
};

#endif
