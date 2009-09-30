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
#include "ncreportdesignerwindow.h"
#include "ncreportdesignerdocument.h"
#include "ncreportdesignerdesignarea.h"
#include "ncaboutdialog.h"
#include "diaquery.h"
#include "diagroup.h"
#include "diavariable.h"
#include "diapage.h"

#include "globals.h"

#include <QWorkspace>
#include <QStatusBar>
#include <QToolBar>
#include <QAction>
#include <QKeySequence>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>


NCReportDesignerWindow::NCReportDesignerWindow()
: QMainWindow()
{
	setObjectName( tr("NCReport designer") );
	setAttribute( Qt::WA_DeleteOnClose, true );
	setWindowTitle( REPORTDESIGNER_NAME " " REPORTDESIGNER_VERSION );
	setWindowIcon( QIcon( ":/imagenes/ncreport.png" ) );
	initToolBars();
	initMenus();

	ws = new QWorkspace( this );
	ws->setScrollBarsEnabled( TRUE );
	setCentralWidget( ws );

	currtool = lasttool = Pointer;
	refreshTools();

	statusBar()->showMessage( "Ready", 2000 );
	sGrid = false;
	snGrid = true;
	setGrid( QPoint(6,6) );
	//grd =

	refreshTools();
	connect( ws, SIGNAL(windowActivated(QWidget*)), this, SLOT(refreshTools()) );
}


NCReportDesignerWindow::~NCReportDesignerWindow()
{
}

void NCReportDesignerWindow::initToolBars( )
{
	////////////////
	// File tools
	////////////////
	fileTools = new QToolBar( "file operations", this );
	addToolBar( Qt::TopToolBarArea, fileTools );

	act_file_new = new QAction( this );
	act_file_new->setText( tr("New") );
	act_file_new->setStatusTip( tr("New report") );
	act_file_new->setIcon( QIcon( ":/imagenes/filenew.png" ) );
	act_file_new->setToolTip( tr("New report document") );
	act_file_new->setShortcut( QKeySequence( "Ctrl+N" ) );
	fileTools->addAction( act_file_new );
	connect( act_file_new, SIGNAL( activated() ), this, SLOT( newDoc() ) );

	act_file_open = new QAction( this );
	act_file_open->setText( tr("Open") );
	act_file_open->setStatusTip( tr("Open report...") );
	act_file_open->setIcon( QIcon( ":/imagenes/fileopen.png" ) );
	act_file_open->setToolTip( tr("Open report document") );
	act_file_open->setShortcut( QKeySequence( "Ctrl+O" ) );
	fileTools->addAction( act_file_open );
	connect( act_file_open, SIGNAL( activated() ), this, SLOT( load() ) );

	act_file_save = new QAction( this );
	act_file_save->setText( tr("Open") );
	act_file_save->setStatusTip( tr("Save report") );
	act_file_save->setIcon( QIcon( ":/imagenes/filesave.png" ) );
	act_file_save->setToolTip( tr("Save report document") );
	act_file_save->setShortcut( QKeySequence( "Ctrl+S" ) );
	fileTools->addAction( act_file_save );
	connect( act_file_save, SIGNAL( activated() ), this, SLOT( save() ) );

	////////////////
	// Edit tools
	////////////////
	editTools = new QToolBar( tr("Edit functions"), this );
	addToolBar(Qt::TopToolBarArea, editTools);

	act_edit_undo = new QAction( this );
	act_edit_undo->setText( tr("Undo") );
	act_edit_undo->setStatusTip( tr("Undo") );
	act_edit_undo->setIcon( QIcon( ":/imagenes/undo.png" ) );
	act_edit_undo->setToolTip( tr("Undo last action") );
	act_edit_undo->setShortcut( QKeySequence( "Ctrl+Z" ) );
	editTools->addAction( act_edit_undo );
	connect( act_edit_undo, SIGNAL( activated() ), this, SLOT( _undo() ) );

	act_edit_redo = new QAction( this );
	act_edit_redo->setText( tr("Redo") );
	act_edit_redo->setStatusTip( tr("Redo") );
	act_edit_redo->setIcon( QIcon( ":/imagenes/redo.png" ) );
	act_edit_redo->setToolTip( tr("Redo last undo") );
	act_edit_redo->setShortcut( QKeySequence( "Ctrl+Y" ) );
	editTools->addAction( act_edit_redo );
	connect( act_edit_redo, SIGNAL( activated() ), this, SLOT( _redo() ) );

	editTools->addSeparator();

	act_edit_copy = new QAction( this );
	act_edit_copy->setText( tr("Copy") );
	act_edit_copy->setStatusTip( tr("Copy") );
	act_edit_copy->setIcon( QIcon( ":/imagenes/editcopy.png" ) );
	act_edit_copy->setToolTip( tr("Copy") );
	act_edit_copy->setShortcut( QKeySequence( "Ctrl+C" ) );
	editTools->addAction( act_edit_copy );
	connect( act_edit_copy, SIGNAL( activated() ), this, SLOT( _copy() ) );

	act_edit_cut = new QAction( this );
	act_edit_cut->setText( tr("Cut") );
	act_edit_cut->setStatusTip( tr("Cut") );
	act_edit_cut->setIcon( QIcon( ":/imagenes/editcut.png" ) );
	act_edit_cut->setToolTip( tr("Cut") );
	act_edit_cut->setShortcut( QKeySequence( "Ctrl+X" ) );
	editTools->addAction( act_edit_cut );
	connect( act_edit_cut, SIGNAL( activated() ), this, SLOT( _cut() ) );

	act_edit_paste = new QAction( this );
	act_edit_paste->setText( tr("Paste") );
	act_edit_paste->setStatusTip( tr("Paste") );
	act_edit_paste->setIcon( QIcon( ":/imagenes/editpaste.png" ) );
	act_edit_paste->setToolTip( tr("Paste") );
	act_edit_paste->setShortcut( QKeySequence( "Ctrl+V" ) );
	editTools->addAction( act_edit_paste );
	connect( act_edit_paste, SIGNAL( activated() ), this, SLOT( _paste() ) );

	act_edit_delete = new QAction( this );
	act_edit_delete->setText( tr("Delete") );
	act_edit_delete->setStatusTip( tr("Delete selected objects") );
	act_edit_delete->setIcon( QIcon( ":/imagenes/editdelete.png" ) );
	act_edit_delete->setToolTip( tr("Delete selected objects") );
	//act_edit_delete->setShortcut( QKeySequence( "Ctrl+Key_V );
	editTools->addAction( act_edit_delete );
	connect( act_edit_delete, SIGNAL( activated() ), this, SLOT( _delete() ) );

	editTools->addSeparator();

	act_edit_zoomIn = new QAction( this );
	act_edit_zoomIn->setText( tr("Zoom+") );
	act_edit_zoomIn->setStatusTip( tr("Zoom in") );
	act_edit_zoomIn->setIcon( QIcon( ":/imagenes/zoom_in.png" ) );
	act_edit_zoomIn->setToolTip( tr("Zoom in") );
	//act_edit_zoomIn->setShortcut( QKeySequence( "Ctrl+Key_V );
	editTools->addAction( act_edit_zoomIn );
	connect( act_edit_zoomIn, SIGNAL( activated() ), this, SLOT( _zoomIn() ) );

	act_edit_zoomOut = new QAction( this );
	act_edit_zoomOut->setText( tr("Zoom-") );
	act_edit_zoomOut->setStatusTip( tr("Zoom out") );
	act_edit_zoomOut->setIcon( QIcon( ":/imagenes/zoom_out.png" ) );
	act_edit_zoomOut->setToolTip( tr("Zoom out") );
	//act_edit_zoomIn->setShortcut( QKeySequence( "Ctrl+Key_V );
	editTools->addAction( act_edit_zoomOut );
	connect( act_edit_zoomOut, SIGNAL( activated() ), this, SLOT( _zoomOut() ) );

	////////////////
	// Object tools
	////////////////
	objTools = new QToolBar( tr("Tool functions"), this );
	addToolBar( Qt::TopToolBarArea, objTools );

	QActionGroup objetos( objTools );
	objetos.setExclusive( true );

	act_tool_pointer = new QAction( this );
	act_tool_pointer->setText( tr("Pointer") );
	act_tool_pointer->setStatusTip( tr("Pointer mode") );
	act_tool_pointer->setIcon( QIcon( ":/imagenes/cursor.png" ) );
	act_tool_pointer->setToolTip( tr("Set to pointer mode") );
	act_tool_pointer->setCheckable( true );
	objetos.addAction( act_tool_pointer );
	editTools->addAction( act_tool_pointer );
	connect( act_tool_pointer, SIGNAL( activated() ), this, SLOT( activate_Pointer() ) );

	act_tool_label = new QAction( this );
	act_tool_label->setText( tr("Label") );
	act_tool_label->setStatusTip( tr("Insert Label") );
	act_tool_label->setIcon( QIcon( ":/imagenes/label.png" ) );
	act_tool_label->setToolTip( tr("Label object") );
	act_tool_label->setCheckable(true);
	editTools->addAction( act_tool_label );
	objetos.addAction( act_tool_label );
	connect( act_tool_label, SIGNAL( activated() ), this, SLOT( activate_Label() ) );

	act_tool_field = new QAction( this );
	act_tool_field->setText( tr("Field") );
	act_tool_field->setStatusTip( tr("Insert SQL field") );
	act_tool_field->setIcon( QIcon( ":/imagenes/textfield.png" ) );
	act_tool_field->setToolTip( tr("Insert sql field") );
	act_tool_field->setCheckable(true);
	editTools->addAction( act_tool_field );
	objetos.addAction( act_tool_field );
	connect( act_tool_field, SIGNAL( activated() ), this, SLOT( activate_Field() ) );

	act_tool_lineH = new QAction( this );
	act_tool_lineH->setText( tr("H.Line") );
	act_tool_lineH->setStatusTip( tr("Insert horizontal line") );
	act_tool_lineH->setIcon( QIcon( ":/imagenes/shape_lineh.png" ) );
	act_tool_lineH->setToolTip( tr("Insert horizontal line") );
	act_tool_lineH->setCheckable(true);
	editTools->addAction( act_tool_lineH );
	objetos.addAction( act_tool_lineH );
	connect( act_tool_lineH, SIGNAL( activated() ), this, SLOT( activate_LineH() ) );

	act_tool_lineV = new QAction( this );
	act_tool_lineV->setText( tr("V.Line") );
	act_tool_lineV->setStatusTip( tr("Insert vertical line") );
	act_tool_lineV->setIcon( QIcon( ":/imagenes/shape_linev.png" ) );
	act_tool_lineV->setToolTip( tr("Insert vertical line") );
	act_tool_lineV->setCheckable(true);
	editTools->addAction( act_tool_lineV );
	objetos.addAction( act_tool_lineV );
	connect( act_tool_lineV, SIGNAL( activated() ), this, SLOT( activate_LineV() ) );

	act_tool_rect = new QAction( this );
	act_tool_rect->setText( tr("Rectangle") );
	act_tool_rect->setStatusTip( tr("Insert rectangle") );
	act_tool_rect->setIcon( QIcon( ":/imagenes/shape_square.png" ) );
	act_tool_rect->setToolTip( tr("Insert rectangle") );
	act_tool_rect->setCheckable(true);
	editTools->addAction( act_tool_rect );
	connect( act_tool_rect, SIGNAL( activated() ), this, SLOT( activate_Rect() ) );

	act_tool_circ = new QAction( this );
	act_tool_circ->setText( tr("Ellipse") );
	act_tool_circ->setStatusTip( tr("Insert ellipse") );
	act_tool_circ->setIcon( QIcon( ":/imagenes/shape_circ.png" ) );
	act_tool_circ->setToolTip( tr("Insert ellipse") );
	act_tool_circ->setCheckable(true);
	editTools->addAction( act_tool_circ );
	connect( act_tool_circ, SIGNAL( activated() ), this, SLOT( activate_Circ() ) );

	act_tool_img = new QAction( this );
	act_tool_img->setText( tr("Image") );
	act_tool_img->setStatusTip( tr("Insert image") );
	act_tool_img->setIcon( QIcon( ":/imagenes/image.png" ) );
	act_tool_img->setToolTip( tr("Insert image") );
	act_tool_img->setCheckable(true);
	editTools->addAction( act_tool_img );
	connect( act_tool_img, SIGNAL( activated() ), this, SLOT( activate_Img() ) );

	//--------------------------
	// ALIGNMENT
	//--------------------------
	act_align_back = new QAction( this );
	act_align_back->setText( tr("Back") );
	act_align_back->setStatusTip( tr("Move to back") );
	act_align_back->setIcon( QIcon( ":/imagenes/shape_move_back.png" ) );
	act_align_back->setToolTip( tr("Move to back") );
	connect( act_align_back, SIGNAL( activated() ), this, SLOT( alignBack() ) );

	act_align_front = new QAction( this );
	act_align_front->setText( tr("Front") );
	act_align_front->setStatusTip( tr("Move to front") );
	act_align_front->setIcon( QIcon( ":/imagenes/shape_move_front.png" ) );
	act_align_front->setToolTip( tr("Move to front") );
	connect( act_align_front, SIGNAL( activated() ), this, SLOT( alignFront() ) );

	act_align_backward = new QAction( this );
	act_align_backward->setText( tr("Backwards") );
	act_align_backward->setStatusTip( tr("Move backwards") );
	act_align_backward->setIcon( QIcon( ":/imagenes/shape_move_backwards.png" ) );
	act_align_backward->setToolTip( tr("Move backwards") );
	connect( act_align_backward, SIGNAL( activated() ), this, SLOT( alignBackward() ) );

	act_align_forward = new QAction( this );
	act_align_forward->setText( tr("Forwards") );
	act_align_forward->setStatusTip( tr("Move forwards") );
	act_align_forward->setIcon( QIcon( ":/imagenes/shape_move_forwards.png" ) );
	act_align_forward->setToolTip( tr("Move forwards") );
	connect( act_align_forward, SIGNAL( activated() ), this, SLOT( alignForward() ) );

	act_align_left = new QAction( this );
	act_align_left->setText( tr("Align left") );
	act_align_left->setStatusTip( tr("Align left") );
	act_align_left->setIcon( QIcon( ":/imagenes/shape_align_left.png" ) );
	act_align_left->setToolTip( tr("Align left") );
	connect( act_align_left, SIGNAL( activated() ), this, SLOT( alignLeft() ) );

	act_align_right = new QAction( this );
	act_align_right->setText( tr("Align right") );
	act_align_right->setStatusTip( tr("Align right") );
	act_align_right->setIcon( QIcon( ":/imagenes/shape_align_right.png" ) );
	act_align_right->setToolTip( tr("Align right") );
	connect( act_align_right, SIGNAL( activated() ), this, SLOT( alignRight() ) );

	act_align_hcenter = new QAction( this );
	act_align_hcenter->setText( tr("Center") );
	act_align_hcenter->setStatusTip( tr("Center horizontally") );
	act_align_hcenter->setIcon( QIcon( ":/imagenes/shape_align_middle.png" ) );
	act_align_hcenter->setToolTip( tr("Center horizontally") );
	connect( act_align_hcenter, SIGNAL( activated() ), this, SLOT( alignHCenter() ) );

	act_align_vcenter = new QAction( this );
	act_align_vcenter->setText( tr("V.Center") );
	act_align_vcenter->setStatusTip( tr("Center vertically") );
	act_align_vcenter->setIcon( QIcon( ":/imagenes/shape_align_center.png" ) );
	act_align_vcenter->setToolTip( tr("Center vertically") );
	connect( act_align_vcenter, SIGNAL( activated() ), this, SLOT( alignVCenter() ) );

	act_align_top = new QAction( this );
	act_align_top->setText( tr("Top") );
	act_align_top->setStatusTip( tr("Align to top") );
	act_align_top->setIcon( QIcon( ":/imagenes/shape_align_top.png" ) );
	act_align_top->setToolTip( tr("Align to top") );
	connect( act_align_top, SIGNAL( activated() ), this, SLOT( alignTop() ) );

	act_align_bottom = new QAction( this );
	act_align_bottom->setText( tr("Bottom") );
	act_align_bottom->setStatusTip( tr("Align to bottom") );
	act_align_bottom->setIcon( QIcon( ":/imagenes/shape_align_bottom.png" ) );
	act_align_bottom->setToolTip( tr("Align to bottom") );
	connect( act_align_bottom, SIGNAL( activated() ), this, SLOT( alignBottom() ) );

	act_view_grid = new QAction( this );
	act_view_grid->setText( tr("Snap to grid") );
	act_view_grid->setStatusTip( tr("Snap to grid") );
	act_view_grid->setCheckable( true );
	connect( act_view_grid, SLOT( triggered() ), this, SLOT( slotSnapToGrid() ) );

	act_view_showgrid = new QAction( this );
	act_view_showgrid->setText( tr("Show grid") );
	act_view_showgrid->setStatusTip( tr("Show grid") );
	act_view_showgrid->setCheckable( true );
	connect( act_view_grid, SLOT( triggered() ), this, SLOT( slotShowGrid() ) );

	act_cascade = new QAction( this );
	act_cascade->setText( tr( "&Cascade" ) );
	connect( act_cascade, SIGNAL( triggered() ), this, SLOT(cascade() ) );

	act_tile = new QAction( tr( "&Tile" ), this );
	connect( act_tile, SIGNAL( triggered() ), this , SLOT( tile() ) );
	act_htile = new QAction( tr( "Tile &Horizontally" ), this );
	connect( act_htile, SIGNAL( triggered() ), this,  SLOT(tileHorizontal() ) );
}

void NCReportDesignerWindow::initMenus()
{
	////////////////
	// File
	////////////////
	mnFile =  menuBar()->addMenu( tr("&File") );

	mnFile->addAction( act_file_new );
	//act_file_new->setWhatsThis( fileOpenText );
	mnFile->addAction( act_file_open );
	mnFile->addAction( act_file_save );
	//act_file_save->setWhatsThis( fileSaveText );

	//act_file_saveAs = new
	mnFile->addAction( tr("Save &As..."), this, SLOT(saveAs()) );

	mnFile->addSeparator();
	mnFile->addAction( tr("&Close"), this, SLOT(closeWindow()), QKeySequence( "Ctrl+W" ) );
	mnFile->addAction( tr("&Quit"), qApp, SLOT(closeAllWindows()),QKeySequence(  "Ctrl+Q" ) );

	////////////////
	// Edit
	////////////////
	mnEdit = menuBar()->addMenu( tr( "&Edit" ) );

	mnEdit->addAction( act_edit_undo );
	mnEdit->addAction( act_edit_redo );
	mnEdit->addSeparator();
	mnEdit->addAction( act_edit_cut );
	mnEdit->addAction( act_edit_copy );
	mnEdit->addAction( act_edit_paste );
	mnEdit->addAction( act_edit_delete );
	mnEdit->addSeparator();
	mnEdit->addAction( tr("Select All"), this, SLOT(selectAll()), QKeySequence( "Ctrl+A" ) );


	////////////////
	// View
	////////////////
	mnView = menuBar()->addMenu( tr("&View") );
///@todo	mnView->setCheckable(TRUE);
	mnView->addAction( act_edit_zoomIn );
	mnView->addAction( act_edit_zoomOut );
	mnView->addSeparator();
	mnView->addAction( act_view_grid );
	mnView->addAction( act_view_showgrid );
	connect( mnView, SIGNAL( aboutToShow() ), this, SLOT( viewMenuAboutToShow() ) );


	////////////////
	// Tools
	////////////////
	mnTools = menuBar()->addMenu( tr("&Tools") );
	mnTools->addAction( act_tool_label );
	mnTools->addAction( act_tool_field );
	mnTools->addAction( act_tool_lineH );
	mnTools->addAction( act_tool_lineV );
	mnTools->addAction( act_tool_rect );
	mnTools->addAction( act_tool_circ );
	mnTools->addAction( act_tool_img );
	mnTools->addSeparator();
	mnTools->addAction( tr("SQL queries..."), this, SLOT(queries()));
	mnTools->addAction( tr("Variables..."), this, SLOT(variables()) );
	mnTools->addAction( tr("Parameters..."), this, SLOT(parameters()) );
	mnTools->addAction( tr("Data grouping..."), this, SLOT(dataGrouping()) );
	mnTools->addAction( tr("Page settings..."), this, SLOT(pageSetup()) );
	mnTools->addSeparator();
	mnTools->addAction( tr("Options..."), this, SLOT(setOptions()));

	////////////////
	// ALIGN
	////////////////
	mnAlign = menuBar()->addMenu( tr("&Align") );
	mnAlign->addAction( act_align_front );
	//mnAlign->addAction( act_align_forward );
	mnAlign->addAction( act_align_back );
	//mnAlign->addAction( act_align_backward );
	mnAlign->addSeparator();
	mnAlign->addAction( act_align_left );
	mnAlign->addAction( act_align_hcenter );
	mnAlign->addAction( act_align_right );
	mnAlign->addAction( act_align_top );
	mnAlign->addAction( act_align_vcenter );
	mnAlign->addAction( act_align_bottom );

	////////////////
	// Windows
	////////////////
	mnWindows = menuBar()->addMenu( tr("&Windows") );
	mnWindows->addAction( act_cascade );
	mnWindows->addAction( act_tile );
	mnWindows->addAction( act_htile );
	mnWindows->addSeparator();
	//mnWindows->setCheckable( TRUE );
	connect( mnWindows, SIGNAL( aboutToShow() ), this, SLOT( windowsMenuAboutToShow() ) );

	////////////////
	// HELP
	////////////////
	menuBar()->addSeparator();
	mnHelp =menuBar()->addMenu( tr("&Help") );

	mnHelp->addAction( tr("&About NCReport"), this, SLOT(about()), QKeySequence( Qt::Key_F1 ) );
	mnHelp->addAction( tr("About &Qt"), this, SLOT(aboutQt()));
	mnHelp->addSeparator();
	mnHelp->addAction( tr("What's &This"), this, SLOT(whatsThis()), QKeySequence( "Shift+F1" ) );

}

void NCReportDesignerWindow::newDoc()
{
	NCReportDesignerDocument* w = _newDoc();
	w->addPageHeader();
	w->addDetail();
	w->addPageFooter();

	if ( ws->windowList().isEmpty() )
		w->showMaximized();
	else
		w->show();

	refreshTools();
}

NCReportDesignerDocument * NCReportDesignerWindow::_newDoc( )
{
	NCReportDesignerDocument* w = new NCReportDesignerDocument( this, ws, 0/*, Qt::WA_DeleteOnClose*/ );
	connect( w, SIGNAL( message(const QString&, int) ), statusBar(), SLOT( message(const QString&, int )) );
	w->setWindowTitle( tr("Documento Nuevo") );
	w->setWindowIcon( QIcon("document.xpm") );

	return w;
}


void NCReportDesignerWindow::load()
{
	QString fn = QFileDialog::getOpenFileName( this, tr( "Abrir archivo" ), QString::null, tr("Report files")+" (*.xml *.txt *.ncr)" );
	if ( !fn.isEmpty() ) {
		NCReportDesignerDocument* w = _newDoc();
		w->setWindowTitle(fn);

		//qApp->processEvents();
		//setUpdatesEnabled(FALSE);
		//setUpdatesEnabled(TRUE);
		if ( w->load( fn ) ) {
			if ( ws->windowList().isEmpty() )
				w->showMaximized();
			else
				w->show();

			refreshTools();
		} else
			delete w;
	}  else {
		statusBar()->showMessage( tr("Loading aborted"), 2000 );
	}

}

void NCReportDesignerWindow::save()
{
	NCReportDesignerDocument* m = currentDoc();
	if ( m )
		m->save();
}


void NCReportDesignerWindow::saveAs()
{
	NCReportDesignerDocument* m = currentDoc();
	if ( m )
		m->saveAs();
}


void NCReportDesignerWindow::print()
{
}


void NCReportDesignerWindow::closeWindow()
{
	NCReportDesignerDocument* m = currentDoc();
	if ( m ) {
		m->close();
		refreshTools();
	}
}

void NCReportDesignerWindow::about()
{
	NCAboutDialog *dia = new NCAboutDialog( this, "aboutdia", TRUE );
	dia->setName( REPORTDESIGNER_NAME " " REPORTDESIGNER_VERSION );
	dia->setAbout( REPORTDESIGNER_ABOUT );
	dia->setAuthor( REPORTDESIGNER_AUTHOR );
	dia->setLicence( REPORTDESIGNER_LICENSE );
	dia->setWindowIcon( QIcon( ":/imagenes/ncreport.png") );

	dia->exec();

	delete dia;

}


void NCReportDesignerWindow::aboutQt()
{
	QMessageBox::aboutQt( this, "About Qt" );
}

void NCReportDesignerWindow::windowsMenuAboutToShow()
{
	mnWindows->clear();
	if ( ws->windowList().isEmpty() ) {
		act_cascade->setEnabled( false );
		act_tile->setEnabled( false );
		act_htile->setEnabled( false );
	} else {
		act_cascade->setEnabled( true );
		act_tile->setEnabled( true );
		act_htile->setEnabled( true );

	}
	///@todo Generar estas ventanas dinamicamente
	/*QWidgetList windows = ws->windowList();
	for ( int i = 0; i < int(windows.count()); ++i ) {
		int id = mnWindows->addAction(windows.at(i)->windowTitle(),
										 this, SLOT( windowsMenuActivated( int ) ) );
		mnWindows->setItemParameter( id, i );
		mnWindows->setItemChecked( id, ws->activeWindow() == windows.at(i) );
	}*/
}

void NCReportDesignerWindow::viewMenuAboutToShow( )
{
	act_view_grid->setChecked( true );
	act_view_showgrid->setChecked( true );
}

void NCReportDesignerWindow::windowsMenuActivated( int id )
{
	QWidget* w = ws->windowList().at( id );
	if ( w )
		w->showNormal();
	w->setFocus();
}

void NCReportDesignerWindow::tileHorizontal()
{
    // primitive horizontal tiling
	QWidgetList windows = ws->windowList();
	if ( !windows.count() )
		return;

	int heightForEach = ws->height() / windows.count();
	int y = 0;
	for ( int i = 0; i < int(windows.count()); ++i ) {
		QWidget *window = windows.at(i);
		if ( window->windowState() == Qt::WindowMaximized ) {
	    // prevent flicker
			window->hide();
			window->showNormal();
		}
		int preferredHeight = window->minimumHeight()+window->parentWidget()->baseSize().height();
		int actHeight = qMax(heightForEach, preferredHeight);

		window->parentWidget()->setGeometry( 0, y, ws->width(), actHeight );
		y += actHeight;
	}
}

void NCReportDesignerWindow::_undo( )
{
	if ( !currentDoc() ) return;
	NCReportDesignerDesignArea *da = currentDoc()->activeDesignArea();
	if ( !da ) return;
	da->undo();
}

void NCReportDesignerWindow::_redo( )
{
	if ( !currentDoc() ) return;
	NCReportDesignerDesignArea *da = currentDoc()->activeDesignArea();
	if ( !da ) return;
	da->redo();
}

void NCReportDesignerWindow::_copy( )
{
	if ( !currentDoc() ) return;
	NCReportDesignerDesignArea *da = currentDoc()->activeDesignArea();
	if ( !da ) return;

	copyStr = da->copy();
	//if ( !copyStr.isEmpty() )
	//	qApp->clipboard()->setText( copyStr );
}

void NCReportDesignerWindow::_paste( )
{
	if ( !currentDoc() ) return;
	NCReportDesignerDesignArea *da = currentDoc()->activeDesignArea();
	if ( !da ) return;

	da->paste( copyStr, da );
}

void NCReportDesignerWindow::_cut( )
{
	if ( !currentDoc() ) return;
	NCReportDesignerDesignArea *da = currentDoc()->activeDesignArea();
	if ( !da ) return;

	_copy();
	da->deleteWidgets();
}

void NCReportDesignerWindow::_delete( )
{
	if ( !currentDoc() ) return;
	NCReportDesignerDesignArea *da = currentDoc()->activeDesignArea();
	if ( !da ) return;

	da->deleteWidgets();
}

void NCReportDesignerWindow::_zoomIn( )
{
	if ( !currentDoc() ) return;
	currentDoc()->measurement()->changeZoomLevelBy( 0.2 );
	currentDoc()->rulerTop()->update();
}

void NCReportDesignerWindow::_zoomOut( )
{
	if ( !currentDoc() ) return;
	currentDoc()->measurement()->changeZoomLevelBy( -0.2 );
	currentDoc()->rulerTop()->update();
}


void NCReportDesignerWindow::closeEvent( QCloseEvent *e )
{
	QWidgetList windows = ws->windowList();
	if ( windows.count() ) {
		for ( int i = 0; i < int(windows.count()); ++i ) {
			QWidget *window = windows.at( i );
			if ( !window->close() ) {
				e->ignore();
				return;
			}
		}
	}

	QMainWindow::closeEvent( e );
}

NCReportDesignerDocument * NCReportDesignerWindow::currentDoc( )
{
	return (NCReportDesignerDocument*)ws->activeWindow();
}


void NCReportDesignerWindow::activate_Pointer()
{
	currtool = Pointer;
	refreshTools();
}
void NCReportDesignerWindow::activate_Label()
{
	currtool = Label;
	refreshTools();
	insertObject();
}
void NCReportDesignerWindow::activate_Field()
{
	currtool = Field;
	refreshTools();
	insertObject();
}
void NCReportDesignerWindow::activate_Rect()
{
	currtool = Rectangle;
	refreshTools();
	insertObject();
}
void NCReportDesignerWindow::activate_Circ()
{
	currtool = Circle;
	refreshTools();
	insertObject();
}
void NCReportDesignerWindow::activate_Img()
{
	currtool = Image;
	refreshTools();
	insertObject();
}
void NCReportDesignerWindow::activate_LineH()
{
	currtool = LineH;
	refreshTools();
	insertObject();
}
void NCReportDesignerWindow::activate_LineV()
{
	currtool = LineV;
	refreshTools();
	insertObject();
}

void NCReportDesignerWindow::insertObject()
{
/*	if ( !currentDoc() ) return;
	switch ( currtool ) {
		case Label:
			break;
	}*/

}

void NCReportDesignerWindow::refreshTools( )
{
	bool cd = currentDoc();

	act_align_front->setEnabled(cd);
	act_align_back->setEnabled(cd);
	act_align_forward->setEnabled(cd);
	act_align_backward->setEnabled(cd);

	act_align_left->setEnabled(cd);
	act_align_right->setEnabled(cd);
	act_align_hcenter->setEnabled(cd);
	act_align_vcenter->setEnabled(cd);
	act_align_top->setEnabled(cd);
	act_align_bottom->setEnabled(cd);
	mnTools->actions().at(  1 )->setEnabled( cd );
	mnTools->actions().at(  2 )->setEnabled( cd );
	mnTools->actions().at(  3 )->setEnabled( FALSE );
	mnTools->actions().at(  4 )->setEnabled( cd );
	mnTools->actions().at(  5 )->setEnabled( cd );
	mnTools->actions().at(  6 )->setEnabled( FALSE );

	act_tool_pointer->setEnabled(cd);
	act_tool_label->setEnabled(cd);
	act_tool_field->setEnabled(cd);
	act_tool_rect->setEnabled(cd);
	act_tool_lineH->setEnabled(cd);
	act_tool_lineV->setEnabled(cd);
	act_tool_circ->setEnabled(cd);
	act_tool_img->setEnabled(cd);

	act_edit_copy->setEnabled(cd);
	act_edit_paste->setEnabled(cd);
	act_edit_cut->setEnabled(cd);
	act_edit_delete->setEnabled(cd);
	act_edit_undo->setEnabled(cd);
	act_edit_redo->setEnabled(cd);
	act_edit_zoomIn->setEnabled(FALSE);
	act_edit_zoomOut->setEnabled(FALSE);

	//act_edit_selectAll->setEnabled(cd);
	//act_file_close->setEnabled(cd);
	act_file_save->setEnabled(cd);
	act_file_save->setEnabled(cd);
	//act_file_saveAll->setEnabled(cd);

	mnFile->actions().at( 10 )->setEnabled( cd ); //saveas
	mnFile->actions().at( 11 )->setEnabled( cd ); //close
	//mnView->setItemEnabled( 12, cd ); //quit
	mnEdit->actions().at(  13 )->setEnabled( cd ); //selall

/*	if ( cd ) {
		if ( !objTools->isEnabled() )
			objTools->setEnabled( true );
		if ( !editTools->isEnabled() )
			editTools->setEnabled( true );
	} else  {
		objTools->setEnabled( false );
		editTools->setEnabled( false );

		//return;
	}	*/

	bool _pointer = false;
	bool _label = false;
	bool _field = false;
	bool _image = false;
	bool _lineH = false;
	bool _lineV = false;
	bool _rect = false;
	bool _circ = false;

	if ( cd ) {
		switch ( currtool ) {
			case Pointer: _pointer = true; break;
			case Label: _label = true; break;
			case Field: _field = true; break;
			case Image: _image = true; break;
			case LineH: _lineH = true; break;
			case LineV: _lineV = true; break;
			case Rectangle: _rect = true; break;
			case Circle: _circ = true; break;
		}
	}

	act_tool_pointer->setChecked( _pointer );
	act_tool_label->setChecked( _label );
	act_tool_field->setChecked( _field );
	act_tool_img->setChecked( _image );
	act_tool_lineH->setChecked( _lineH );
	act_tool_lineV->setChecked( _lineV );
	act_tool_rect->setChecked( _rect );
	act_tool_circ->setChecked( _circ );

	if ( _pointer && !act_tool_pointer->isChecked() )
		act_tool_pointer->setChecked( true );

	if ( lasttool != currtool )
		emit currentToolChanged();

	lasttool = currtool;
}


void NCReportDesignerWindow::selectAll()
{
	if ( !currentDoc() ) return;
	NCReportDesignerDesignArea *da = currentDoc()->activeDesignArea();
	if ( !da ) return;

	da->selectAll();
}

int NCReportDesignerWindow::currentTool( )
{
	return currtool;
}

void NCReportDesignerWindow::resetTools( )
{
	activate_Pointer();
	//	tool_Pointer->setChecked( TRUE );
}

void NCReportDesignerWindow::setGrid( const QPoint &p )
{
	if ( p == grd )
		return;
	grd = p;
	QWidgetList windows = ws->windowList();
	foreach( QWidget *w, windows )
	{
		if ( qobject_cast<NCReportDesignerDesignArea*>(w) != 0 )
		qobject_cast<NCReportDesignerDesignArea *>(w)->update();
		//( (NCReportDesignerDesignArea*)w )->mainContainer()->update();
	}
}

void NCReportDesignerWindow::setShowGrid( bool b )
{
	if ( b == sGrid )
		return;
	sGrid = b;

/*	if ( currentDoc() )
		currentDoc()->updateSections();
	return;*/

	QWidgetList windows = ws->windowList();
	foreach( QWidget *w, windows )
	{
		if ( qobject_cast<NCReportDesignerDesignArea*>(w) != 0 )
			(qobject_cast<NCReportDesignerDesignArea*>(w))->update();
	}
}

void NCReportDesignerWindow::setSnapGrid( bool b )
{
	if ( b == snGrid )
		return;
	snGrid = b;
}

void NCReportDesignerWindow::slotShowGrid( )
{
	bool set = !sGrid;
	setShowGrid( set );
	act_view_showgrid->setChecked( !set );
}

void NCReportDesignerWindow::slotSnapToGrid( )
{
	bool set = !snGrid;
	setSnapGrid( set );
	act_view_grid->setChecked( !set );
}

void NCReportDesignerWindow::dataGrouping( )
{
	if ( !currentDoc() )
		return;
	diaGroup *dia = new diaGroup( this, "diaGroup", TRUE );
	dia->assignDocument( currentDoc() );

	switch (dia->exec()) {
		case QDialog::Accepted: {

			dia->applyGroupSettings();
			//currentDoc()->groups
			//dia->saveSettings();
			break;
		}
	}
	delete dia;
}

void NCReportDesignerWindow::pageSetup( )
{
	if ( !currentDoc() )
		return;
	diaPage *dia = new diaPage( this, "diaPage", TRUE );
	dia->assignDocument( currentDoc() );
	switch (dia->exec()) {
		case QDialog::Accepted: {
			dia->applySettings();
			break;
		}
	}
	delete dia;
}

void NCReportDesignerWindow::setOptions( )
{
}

void NCReportDesignerWindow::variables( )
{
	if ( !currentDoc() )
		return;
	diaVariable *dia = new diaVariable( this, "diaVariable", TRUE );
	dia->assignDocument( currentDoc() );

	switch (dia->exec()) {
		case QDialog::Accepted: {
			dia->applySettings();
			break;
		}
	}
	delete dia;
}

void NCReportDesignerWindow::parameters( )
{
}

void NCReportDesignerWindow::queries( )
{
	if ( !currentDoc() )
		return;
	diaQuery *dia = new diaQuery( this, "diaQuery", TRUE );
	dia->assignDocument( currentDoc() );

	switch (dia->exec()) {
		case QDialog::Accepted: {
			//dia->saveSettings();
			break;
		}
	}
	delete dia;
}

void NCReportDesignerWindow::alignFront( )
{
	if ( !currentDoc() ) return;
	NCReportDesignerDesignArea *da = currentDoc()->activeDesignArea();
	if ( da )
		da->raiseWidgets();
}

void NCReportDesignerWindow::alignBack( )
{
	if ( !currentDoc() ) return;
	NCReportDesignerDesignArea *da = currentDoc()->activeDesignArea();
	if ( da )
		da->lowerWidgets();
}

void NCReportDesignerWindow::alignForward( )
{
	if ( !currentDoc() ) return;
	NCReportDesignerDesignArea *da = currentDoc()->activeDesignArea();
	if ( da )
		da->raiseWidgets();
}

void NCReportDesignerWindow::alignBackward( )
{
	if ( !currentDoc() ) return;
	NCReportDesignerDesignArea *da = currentDoc()->activeDesignArea();
	if ( da )
		da->lowerWidgets();
}

void NCReportDesignerWindow::alignLeft( )
{
	if ( !currentDoc() ) return;
	NCReportDesignerDesignArea *da = currentDoc()->activeDesignArea();
	if ( da )
		da->alignWidgets( Qt::AlignLeft );
}

void NCReportDesignerWindow::alignRight( )
{
	if ( !currentDoc() ) return;
	NCReportDesignerDesignArea *da = currentDoc()->activeDesignArea();
	if ( da )
		da->alignWidgets( Qt::AlignRight );
}

void NCReportDesignerWindow::alignHCenter( )
{
	if ( !currentDoc() ) return;
	NCReportDesignerDesignArea *da = currentDoc()->activeDesignArea();
	if ( da )
		da->alignWidgets( Qt::AlignHCenter );
}

void NCReportDesignerWindow::alignTop( )
{
	if ( !currentDoc() ) return;
	NCReportDesignerDesignArea *da = currentDoc()->activeDesignArea();
	if ( da )
		da->alignWidgets( Qt::AlignTop );
}

void NCReportDesignerWindow::alignVCenter( )
{
	if ( !currentDoc() ) return;
	NCReportDesignerDesignArea *da = currentDoc()->activeDesignArea();
	if ( da )
		da->alignWidgets( Qt::AlignVCenter );
}

void NCReportDesignerWindow::alignBottom( )
{
	if ( !currentDoc() ) return;
	NCReportDesignerDesignArea *da = currentDoc()->activeDesignArea();
	if ( da )
		da->alignWidgets( Qt::AlignBottom );
}



