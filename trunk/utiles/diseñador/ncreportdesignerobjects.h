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
#ifndef NCREPORTDESIGNEROBJECTS_H
#define NCREPORTDESIGNEROBJECTS_H

#include <qwidget.h>

class NCReportDesignerObject : public QWidget
{
public:
	NCReportDesignerObject( QWidget* parent, const char* name );
	virtual ~NCReportDesignerObject();

protected:
	virtual void paintEvent( QPaintEvent *e );
	virtual void mousePressEvent ( QMouseEvent *e ); 
	virtual void mouseReleaseEvent ( QMouseEvent *e ); 
	virtual void mouseDoubleClickEvent ( QMouseEvent *e ); 
	virtual void mouseMoveEvent ( QMouseEvent *e ); 
};

class obj_Label : public NCReportDesignerObject
{
public:
	obj_Label( QWidget* parent, const char* name );
	~obj_Label();
};

#endif
