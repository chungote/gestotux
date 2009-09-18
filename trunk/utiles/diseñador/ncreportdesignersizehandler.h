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
#ifndef SELECTION_H
#define SELECTION_H

#include <QWidget>
#include <QHash>

class NCReportDesignerDesignArea;
class Selection;

class SizeHandler : public QWidget
{
	Q_OBJECT
public:
	enum Direction { LeftTop, Top, RightTop, Right, RightBottom, Bottom, LeftBottom, Left };

	SizeHandler( NCReportDesignerDesignArea *parent, Direction d, Selection *s );
	~SizeHandler();
	void setWidget( QWidget *w );
	void setActive( bool a );
	void updateCursor();

	void setEnabled( bool ) {}
protected:
	void paintEvent( QPaintEvent *e );
	void mousePressEvent( QMouseEvent *e );
	void mouseMoveEvent( QMouseEvent *e );
	void mouseReleaseEvent( QMouseEvent *e );

private:
	void trySetGeometry( QWidget *w, int x, int y, int width, int height );
	void tryResize( QWidget *w, int width, int height );

private:
	QWidget *widget;
	Direction dir;
	QPoint oldPressPos;
	NCReportDesignerDesignArea *da;
	Selection *sel;
	QRect geom, origGeom;
	bool active;

};

class Selection
{
public:
	Selection( NCReportDesignerDesignArea *parent, QHash<QWidget *, Selection*> *selDict );

	enum SelectionType { Full, Horizontal, Vertical };

	void setWidget( QWidget *w, bool updateDict = TRUE );
	bool isUsed() const;

	void updateGeometry();
	void hide();
	void show();
	void update();
	SelectionType selectType();

	QWidget *widget() const;
protected:
	QHash<int,SizeHandler*> handles;
	QWidget *wid;
	NCReportDesignerDesignArea *da;
	SelectionType selType;
	QHash<QWidget*,Selection*> *selectionDict;

};


#endif
