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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class NCReportDesignerDocument;

class QTextEdit;
class QToolBar;
class QMenu;
class QWorkspace;
class QMenu;
class QMovie;
class QToolButton;
class QAction;

class NCReportDesignerWindow: public QMainWindow
{
Q_OBJECT
public:
	NCReportDesignerWindow();
	~NCReportDesignerWindow();

	enum ToolType { Pointer=0, Label, Field, LineH, LineV, Rectangle, Circle, Image };

	void setGrid( const QPoint &p );
	void setShowGrid( bool b );
	void setSnapGrid( bool b );
	QPoint grid() const { return grd; }
	bool showGrid() const { return sGrid; }
	bool snapGrid() const { return snGrid; } // && sGrid; }
	NCReportDesignerDocument *currentDoc();
	int currentTool();
public slots:
	void refreshTools();
	void resetTools();
protected:
	void closeEvent( QCloseEvent * );

	void initToolBars();
	void initMenus();
signals:
	void currentToolChanged();

private slots:
	void newDoc();
	void load();
	void save();
	void saveAs();
	void print();
	void closeWindow();
	void tileHorizontal();
	void selectAll();

	void dataGrouping();
	void pageSetup();
	void setOptions();
	void variables();
	void parameters();
	void queries();

	void alignFront();
	void alignBack();
	void alignForward();
	void alignBackward();
	void alignLeft();
	void alignRight();
	void alignHCenter();
	void alignTop();
	void alignBottom();
	void alignVCenter();

	void about();
	void aboutQt();

	void windowsMenuAboutToShow();
	void viewMenuAboutToShow();
	void windowsMenuActivated( int id );
	void slotShowGrid();
	void slotSnapToGrid();

	void _undo();
	void _redo();
	void _copy();
	void _paste();
	void _cut();
	void _delete();
	void _zoomIn();
	void _zoomOut();

	void activate_Pointer();
	void activate_Label();
	void activate_Field();
	void activate_Rect();
	void activate_Circ();
	void activate_Img();
	void activate_LineH();
	void activate_LineV();

private:
	QPrinter *printer;
	QWorkspace* ws;
	QToolBar *fileTools, *editTools, *objTools ;
	QAction *act_tool_pointer;
	QAction *act_tool_label;
	QAction *act_tool_field;
	QAction *act_tool_rect;
	QAction *act_tool_lineH;
	QAction *act_tool_lineV;
	QAction *act_tool_circ;
	QAction *act_tool_img;
	QAction *act_edit_copy;
	QAction *act_edit_paste;
	QAction *act_edit_cut;
	QAction *act_edit_delete;
	QAction *act_edit_undo;
	QAction *act_edit_redo;
	QAction *act_edit_zoomIn;
	QAction *act_edit_zoomOut;
	QAction *act_view_grid;
	QAction *act_view_showgrid;
	//QAction *act_edit_selectAll;
	QAction *act_file_new;
	QAction *act_file_open;
	QAction *act_file_close;
	QAction *act_file_save;
	QAction *act_file_saveAll;

	QAction *act_align_front;
	QAction *act_align_back;
	QAction *act_align_forward;
	QAction *act_align_backward;

	QAction *act_align_left;
	QAction *act_align_right;
	QAction *act_align_hcenter;
	QAction *act_align_vcenter;
	QAction *act_align_top;
	QAction *act_align_bottom;


	//QToolButton *tool_Pointer;
	//QToolButton *tool_Label;
	//QToolButton *tool_Field;
	//QToolButton *tool_Rect;
	//QToolButton *tool_LineH;
	//QToolButton *tool_LineV;
	//QToolButton *tool_Circ;
	//QToolButton *tool_Img;
	QMenu* mnFile;
	QMenu* mnEdit;
	QMenu* mnView;
	QMenu* mnTools;
	QMenu* mnAlign;
	QMenu* mnHelp;
	QMenu* mnWindows;

	QPoint grd;
	bool sGrid, snGrid;
	QString copyStr;

	NCReportDesignerDocument *document;

	NCReportDesignerDocument* _newDoc();
	void insertObject();
	//QAction *zoomPAct;
	//QAction *zoomMAct;
	ToolType currtool, lasttool;

};

#endif
