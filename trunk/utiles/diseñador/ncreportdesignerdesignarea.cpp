/***************************************************************************
 *   Copyright (C) 2006 by Szab√≥ Norbert   *
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
#include "ncreportdesignerdesignarea.h"
#include "ncreportdesignerwindow.h"
#include "ncreportdesignerdocument.h"
#include "ncreportdesignersizehandler.h"
#include "ncreportdesignerwidgetfactory.h"
#include "ncreportdesignerwidget.h"
#include "ncreportdesignerresourcehandler.h"
#include "ncreportdesignerwidgetsetdialog.h"

//#include <stdlib.h>
#include <QEvent>
#include <QPainter>
#include <QPen>
#include <QLabel>
#include <QTimer>
#include <QApplication>
#include <QLayout>
#include <QSpinBox>
#include <QStatusBar>
#include <QMessageBox>
#include <QMenu>
#include <QPushButton>
#include <QWidget>
#include <QSplitter>
#include <QBitmap>
#include <QCloseEvent>

/*#include <qsizegrip.h>

#include <qwhatsthis.h>
#include <qmetaobject.h>
#include <qtooltip.h>
//#include <qcloseevent.h>
#include <qpixmapcache.h>*/



static void setCursorToAll( const QCursor &c, QWidget *start )
{
 ///@todo Ver esto!
	start->setCursor( c );
	/*QObjectList *l = (QObjectList*)start->children();
	if ( l ) {
		for ( QObject *o = l->first(); o; o = l->next() ) {
			if ( o->isWidgetType() && !::qt_cast<SizeHandler*>(o) )
				setCursorToAll( c, ( (QWidget*)o ) );
		}
	}*/
}

static void restoreCursors( QWidget *start, NCReportDesignerDesignArea *area )
{
	if ( area->widgets().contains( start ) )
		start->setCursor( Qt::ArrowCursor );
		//start->setCursor( MetaDataBase::cursor( start ) );
	else
		start->setCursor( Qt::ArrowCursor );

	QWidgetList l = start->findChildren<QWidget *>();
	if ( !l.isEmpty() ) {
		foreach( QWidget *o, l )
		{
			if ( o->isWidgetType() && !qobject_cast<SizeHandler*>(o) )
				restoreCursors( o, area );
		}
	}
}


/*!
  \class NCReportDesignerDesignArea NCReportDesignerDesignArea.h
  \brief edit workplace section for the designer

  The NCReportDesignerDesignArea is the widget which is used as editor for forms. It
  handles inserting, deleting, moving, resizing, etc. of widgets.

  Normally multiple NCReportDesignerDesignAreas are used at the same time in the
  Designer. So each NCReportDesignerDesignArea has its own undo/redo buffer, etc.

  For handling the events of the child widgets (moving, etc.) the
  handleMousePress(), etc. functions are called from the application
  event filter which is implemented in MainWindow::eventFilter().
 */

NCReportDesignerDesignArea::NCReportDesignerDesignArea( NCReportDesignerWindow *mw, QWidget *parent, const char* name, Qt::WFlags f )
	: QWidget( parent, f ), mwindow( mw ), commands( 100 ), pixInline( TRUE ), pixProject( FALSE )
{
 	this->setObjectName( name );
	init();
	initSlots();
}

NCReportDesignerDesignArea::NCReportDesignerDesignArea( QWidget *parent,  const char* name, Qt::WFlags f )
	: QWidget( parent, f ), mwindow( 0 ), commands( 100 ), pixInline( TRUE )
{
	this->setObjectName( name );
	init();
}

void NCReportDesignerDesignArea::init()
{
	propertyWidget = 0;
	toolFixed = FALSE;
	checkedSelectionsForMove = FALSE;
	mContainer = 0;
	startWidget = endWidget = 0;
	currTool = PointerTool;
	unclippedPainter = 0;
	widgetPressed = FALSE;
	drawRubber = FALSE;
	//setFocusPolicy( ClickFocus );
	sizePreviewLabel = 0;
	/*
	checkSelectionsTimer = new QTimer( this, "checkSelectionsTimer" );
	connect( checkSelectionsTimer, SIGNAL( timeout() ), this, SLOT( invalidCheckedSelections() ) );
	updatePropertiesTimer = new QTimer( this );
	connect( updatePropertiesTimer, SIGNAL( timeout() ), this, SLOT( updatePropertiesTimerDone() ) );
	showPropertiesTimer = new QTimer( this );
	connect( showPropertiesTimer, SIGNAL( timeout() ), this, SLOT( showPropertiesTimerDone() ) );
	selectionChangedTimer = new QTimer( this );
	connect( selectionChangedTimer, SIGNAL( timeout() ), this, SLOT( selectionChangedTimerDone() ) );
	windowsRepaintWorkaroundTimer = new QTimer( this );
	connect( windowsRepaintWorkaroundTimer, SIGNAL( timeout() ), this, SLOT( windowsRepaintWorkaroundTimerTimeout() ) );
	*/
	insertParent = 0;
	/*
	connect( &commands, SIGNAL( undoRedoChanged( bool, bool, const QString &, const QString & ) ),
			  this, SIGNAL( undoRedoChanged( bool, bool, const QString &, const QString & ) ) );
	*/
	propShowBlocked = FALSE;

	//setIcon( QPixmap::fromMimeSource( "designer_form.png" ) );

	//connect( &commands, SIGNAL( modificationChanged( bool ) ), this, SLOT( modificationChanged( bool ) ) );
	buffer = 0;
	color1 = QColor( 128,128,128);
	propertyWidget = 0;
	targetContainer = 0;
	hadOwnPalette = FALSE;
	hasLayoutFunc = FALSE;

	this->setBackgroundRole( QPalette::Base );
	sizePreview();

	setFocusPolicy( Qt::StrongFocus );
	//setSizePolicy( QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed) );
}

QSize NCReportDesignerDesignArea::sizeHint() const
{
	//return QSize( width(), height() );
	return QWidget::sizeHint();
}

void NCReportDesignerDesignArea::setMainWindow( NCReportDesignerWindow *w )
{
	mwindow = w;
	initSlots();
}

void NCReportDesignerDesignArea::initSlots()
{
}

NCReportDesignerDesignArea::~NCReportDesignerDesignArea()
{
	/*
	if ( MainWindow::self && MainWindow::self->objectHierarchy()->NCReportDesignerDesignArea() == this )
		MainWindow::self->objectHierarchy()->setNCReportDesignerDesignArea( 0, 0 );

	MetaDataBase::clear( this );
	*/
}

void NCReportDesignerDesignArea::closeEvent( QCloseEvent *e )
{
	e->accept();
}


void NCReportDesignerDesignArea::paintEvent( QPaintEvent *e )
{
	QWidget::paintEvent(e);
	QPainter p(this);
	paintGrid( p );
	//p.drawLine(width()-1,0,width()-1,height());
	if ( hasFocus() )
		paintFocus( &p, true );
}

void NCReportDesignerDesignArea::paintGrid( QPainter& p )
{
	if ( !mainWindow() || !mainWindow()->showGrid() )
		return;
	p.setPen( color1 );

	for ( int y = 0; y < height(); y += mainWindow()->grid().y()) {
		for ( int x = 0; x < width(); x += mainWindow()->grid().x() )
			p.drawPoint( x, y );

	}
}

// void NCReportDesignerDesignArea::paintGrid( QWidget *w, QPaintEvent *e )
// {
// 	if ( !mainWindow() || !mainWindow()->showGrid() )
// 		return;
// 	QPixmap grid;
// 	QString grid_name;
// 	grid_name.sprintf("NCReportDesignerDesignAreaGrid_%d_%d", mainWindow()->grid().x(), mainWindow()->grid().y());
// 	if( !QPixmapCache::find( grid_name, grid ) ) {
// 		grid = QPixmap( 350 + ( 350 % mainWindow()->grid().x() ), 350 + ( 350 % mainWindow()->grid().y() ) );
// 		//grid.fill( QPalette::Foreground );
// 		grid.fill( colorGroup().color( QColorGroup::Foreground ) );
// 		QBitmap mask( grid.width(), grid.height() );
// 		mask.fill( color0 );
// 		QPainter p( &mask );
// 		p.setPen( color1 );
// 		for ( int y = 0; y < grid.width(); y += mainWindow()->grid().y()) {
// 			for ( int x = 0; x < grid.height(); x += mainWindow()->grid().x() ) {
// 				p.drawPoint( x, y );
// 			}
// 		}
// 		grid.setMask( mask );
// 		QPixmapCache::insert( grid_name, grid );
// 	}
// 	QPainter p( w );
// 	p.setClipRegion( e->rect() );
// 	p.drawTiledPixmap( QRect( 0, 0, width(), height() ), grid );
// }

/*!  For operations like drawing a rubber band or drawing the rect
  when inserting a new widget, a unclipped painter (which draws also
  on child widgets) is needed. This method does all the initialization.
 */

void NCReportDesignerDesignArea::beginUnclippedPainter( bool doNot )
{
	endUnclippedPainter();
	bool unclipped = testAttribute( Qt::WA_PaintUnclipped );
	setAttribute( Qt::WA_PaintUnclipped, true  );
	unclippedPainter = new QPainter;
	unclippedPainter->begin( this );
	if ( !unclipped )
		setAttribute( Qt::WA_PaintUnclipped, false );
	if ( doNot ) {
		unclippedPainter->setPen( QPen( Qt::black, 2 ) );
		unclippedPainter->setCompositionMode( QPainter::CompositionMode_SourceOver );
		//unclippedPainter->setRasterOp( NotROP );
	}

}

/*!
  Gets rid of an open unclipped painter.

  \sa beginUnclippedPainter()
 */

void NCReportDesignerDesignArea::endUnclippedPainter()
{
	if ( unclippedPainter )
		unclippedPainter->end();
	delete unclippedPainter;
	unclippedPainter = 0;
}

QPoint NCReportDesignerDesignArea::gridPoint( const QPoint &p )
{
	return QPoint( ( p.x() / grid().x() ) * grid().x(),
					 ( p.y() / grid().y() ) * grid().y() );
}

void NCReportDesignerDesignArea::insertWidget()
{
	if ( !insertParent )
		return;

	if ( currTool == PointerTool )
		return;

	QWidget *w = NCReportDesignerWidgetFactory::create( mainWindow()->currentTool(), insertParent, 0, TRUE, &currRect );
	if ( !w )
		return;

	//bool useSizeHint = !oldRectValid || ( currRect.width() < 2 && currRect.height() < 2 );
	QString n; //= WidgetDatabase::className( currTool );
	//QString s = w->name();
	//w->setName( s );
	insertWidget( w );
	QRect r( currRect );
	if ( !oldRectValid || ( currRect.width() < 2 && currRect.height() < 2 ) )
		r = QRect( rectAnchor, QSize( 0, 0 ) );

	QPoint p = r.topLeft();
	p = mapToGlobal( p );
	p = insertParent->mapFromGlobal( p );
	r = QRect( p, r.size() );

	if ( r.width() < 2 * grid().x() )
		r.setWidth( 2 * grid().x() );
	if ( r.height() < 2 * grid().y() )
		r.setHeight( 2 * grid().y() );
	/*
	const QObjectList *l = insertParent->children();
	QObjectListIt it( *l );
	QWidgetList lst;
	*/
	if ( !toolFixed )
		mwindow->resetTools();
	else
		setCursorToAll( Qt::CrossCursor, w );

	cmd_InsertCommand *cmd = new cmd_InsertCommand( tr( "Insert %1" ).arg( w->objectName() ), this, w, r );
	commandHistory()->addCommand( cmd );
	cmd->execute();

	NCReportDesignerWidget *dw = (NCReportDesignerWidget*)w;
	if ( dw && dw->initOpenPropDia )
		runWidgetSettingsDialog( dw, TRUE );	// inti mode

}

void NCReportDesignerDesignArea::insertWidget( QWidget *w, bool checkName )
{
	if ( !w )
		return;
	if ( checkName ) {
		QString s = w->objectName();
		w->setObjectName( s );
	}

	//int id = 0; //WidgetDatabase::idFromClassName( WidgetFactory::classNameOf(w) );
	QString tt; //= WidgetDatabase::toolTip( id );
	QString wt; //= WidgetDatabase::whatsThis( id );
	//if ( !wt.isEmpty() && !tt.isEmpty() )
	//	QWhatsThis::add( w, QString("<b>A %1</b><p>%2</p>").arg( tt ).arg( wt ) );

	restoreCursors( w, this );
	//widgets()->insert( w, w );
	w->show();
}

void NCReportDesignerDesignArea::removeWidget( QWidget *w )
{
	widgets().removeOne( w );
}

void NCReportDesignerDesignArea::handleContextMenu( QContextMenuEvent *e, QWidget * )
{
	switch ( currTool ) {
		case PointerTool: {
			e->accept();
			clearSelection();
			//mwindow->popupNCReportDesignerDesignAreaMenu( e->globalPos(), this );
			break;
		}
		default:
			break;
	}
}

void NCReportDesignerDesignArea::handleMousePress( QMouseEvent *e, QWidget *w )
{
	checkedSelectionsForMove = FALSE;
	//checkSelectionsTimer->stop();
	if ( !hasFocus() )
		setFocus();

	switch ( currTool ) {
		case PointerTool:
			if ( w == this ) {
				if ( e->button() == Qt::LeftButton ) { // left button: start rubber selection and show NCReportDesignerDesignArea properties
					drawRubber = TRUE;
					if ( !( ( e->modifiers() &   Qt::ControlModifier ) || ( e->modifiers() &   Qt::ShiftModifier ) ) ) {
						clearSelection( FALSE );
						//QObject *opw = propertyWidget;
						//propertyWidget = mainContainer();
						//if ( opw->isWidgetType() )
						//	repaintSelection( (QWidget*)opw );
					}
					currRect = QRect( 0, 0, -1, -1 );
					startRectDraw( mapFromGlobal( e->globalPos() ), e->globalPos(), this, Rubber );

				}
			} else {
				//w->raise();	// elıtÈrbe hoz
				if ( ( e->modifiers() &   Qt::ControlModifier ) ) { // with control pressed, always start rubber band selection
					drawRubber = TRUE;
					currRect = QRect( 0, 0, -1, -1 );
					startRectDraw( mapFromGlobal( e->globalPos() ), e->globalPos(), this, Rubber );
					break;
				}
				bool sel = isWidgetSelected( w );
				if ( !( ( e->modifiers() &   Qt::ControlModifier ) || ( e->modifiers() &   Qt::ShiftModifier ) ) ) { // control not pressed...
					if ( !sel ) { // ...and widget no selectted: unselect all
						clearSelection( FALSE );
					} else { // ...widget selected
						QWidgetList l = w->findChildren<QWidget *>();
						//setPropertyShowingBlocked( TRUE );
						foreach( QWidget *o, l ) {
							if ( insertedWidgets.values().contains( o ) )
								selectWidget( o, FALSE );
						}
						//setPropertyShowingBlocked( FALSE );
					}
					qApp->processEvents();
				}
				if ( ( ( e->modifiers() &   Qt::ControlModifier ) || ( e->modifiers() &   Qt::ShiftModifier ) ) && sel && e->button() == Qt::LeftButton ) { // control pressed and selected, unselect widget
					selectWidget( w, FALSE );
					break;
				}
				//raiseChildSelections( w ); // raise selections and select widget
				selectWidget( w );
				if ( e->button() == Qt::LeftButton ) { // left button: store original geometry and more as the widget might start moving
					widgetPressed = TRUE;
					widgetGeom = QRect( w->pos(), w->size() );
					oldPressPos = w->mapFromGlobal( e->globalPos() );
					origPressPos = oldPressPos;
					checkedSelectionsForMove = FALSE;
					moving.clear();
					/*
					if ( w->parentWidget() && !isMainContainer( w->parentWidget() ) && !isCentralWidget( w->parentWidget() ) ) {
						targetContainer = w->parentWidget();
						hadOwnPalette = w->parentWidget()->ownPalette();
						restorePalette = w->parentWidget()->palette();
					}
					*/
				}


			}
			break;
		default: // any insert widget tool
				if ( e->button() == Qt::LeftButton ) {
					insertParent = this;	//WidgetFactory::containerOfWidget( mainContainer() ); // default parent for new widget is the NCReportDesignerDesignArea
					startRectDraw( w->mapFromGlobal( e->globalPos() ), e->globalPos(), w, Insert );
				}
				break;
	}

}

void NCReportDesignerDesignArea::handleMouseDblClick( QMouseEvent *, QWidget *w )
{
	if ( w == this )
		return;

	NCReportDesignerWidget *dw = (NCReportDesignerWidget*)w;


	switch ( currTool ) {
		case PointerTool: {

			// open property dialog
			runWidgetSettingsDialog( dw );

			break;
		}

		default:
/*			if ( !WidgetFactory::isPassiveInteractor( w ) &&
						   ( isMainContainer( w ) || w == this ) )
				mainWindow()->editSource();*/
			break;
	}
}

void NCReportDesignerDesignArea::handleMouseMove( QMouseEvent *e, QWidget *w )
{
	if ( ( e->modifiers() & Qt::LeftButton ) != Qt::LeftButton )
		return;

	//QWidget *newendWidget = endWidget, *oldendWidget = endWidget, *wid;
	//bool drawRecRect;
	switch ( currTool ) {
		case PointerTool:
			if ( widgetPressed && allowMove( w ) ) { // we are prepated for a move
				// calc correct position
				QPoint pos = w->mapFromGlobal( e->globalPos() );

				// calc move distance and store it
				QPoint d = oldPressPos - pos;
				if ( qAbs( d.x() ) < grid().x() )
					d.setX( 0 );
				if ( qAbs( d.y() ) < grid().y() )
					d.setY( 0 );
				if ( d.x() == 0 )
					pos.setX( oldPressPos.x() );
				if ( d.y() == 0 )
					pos.setY( oldPressPos.y() );
				oldPressPos = pos;

				// snap to grid
				int x = widgetGeom.x() - d.x();
				widgetGeom.setX( x );
				x = ( x / grid().x() ) * grid().x();
				int y = widgetGeom.y() - d.y();
				widgetGeom.setY( y );
				y = ( y / grid().y() ) * grid().y();
				QPoint p = w->pos();

				if ( x - p.x() != 0 || y - p.y() != 0 ) { // if we actually have to move
					if ( !checkedSelectionsForMove ) { // if not checked yet, check if the correct widget are selected...
						if ( !isWidgetSelected( w ) ) {	// and unselect others. Only siblings can be moved at the same time
							//setPropertyShowingBlocked( TRUE );
							selectWidget( w );
							//setPropertyShowingBlocked( FALSE );
						}
						checkSelectionsForMove( w );
					}

				// check whether we would have to reparent the selection and highlight the possible new parent container
					QMap<QWidget*, QPoint>::iterator it = moving.begin();
					//QWidget* wa = containerAt( e->globalPos(), it.key() );
				// finally move the selected widgets and show/update preview label
					moveSelectedWidgets( x - p.x(), y - p.y() );
					//sizePreviewLabel->setText( tr( "%1/%2" ).arg( w->pos().x() ).arg( w->pos().y() ) );
					sizePreviewLabel->setText( m->pixelPosToMeasureCaption( w->pos().x(), w->pos().y() ) );

					sizePreviewLabel->adjustSize();
					QRect lg( mapFromGlobal( e->globalPos() ) + QPoint( 16, 16 ), sizePreviewLabel->size() );
					//checkGeometry( lg );
					sizePreviewLabel->setGeometry( lg );
					sizePreviewLabel->raise();
					sizePreviewLabel->show();
					#if defined(Q_WS_WIN32)
						//windowsRepaintWorkaroundTimer->start( 100, TRUE );
					#endif
				} else { // if we don't need to move, do some indication
					QRect lg( mapFromGlobal( e->globalPos() ) + QPoint( 16, 16 ), sizePreviewLabel->size() );
					//checkGeometry( lg );
					sizePreviewLabel->move( lg.x(), lg.y() );
				}

				oldPressPos += ( p - w->pos() );
			} else if ( drawRubber ) { // draw rubber if we are in rubber-selection mode
				continueRectDraw( mapFromGlobal( e->globalPos() ), e->globalPos(), this, Rubber );
			}
			break;
		default:
			if ( insertParent ) // draw insert rect
				continueRectDraw( w->mapFromGlobal( e->globalPos() ), e->globalPos(), w, Insert );
			break;
	}

}


void NCReportDesignerDesignArea::handleMouseRelease( QMouseEvent *e, QWidget *w )
{
	if ( e->button() != Qt::LeftButton )
		return;

	switch ( currTool ) {
		case PointerTool:
			if ( widgetPressed && allowMove( w ) ) { // we moved the widget
				sizePreviewLabel->hide();
				if ( moving.isEmpty() || w->pos() == *moving.find(w) )
					break;

				QWidgetList widgets; // collect the widgets and its old and new positions which have been moved
				QList<QPoint> oldPos, newPos;
				QMap<QWidget*,QPoint>::iterator it = moving.begin();
				for ( it = moving.begin(); it != moving.end(); ++it ) {
					widgets.append( it.key() );
					oldPos.append( *it );
					newPos.append( it.key()->pos() );
				}
				// add move command, don't execute it, this is just a summary of the operations we did during the move-event handling
				commandHistory()->addCommand( new cmd_MoveCommand( tr( "Move" ), this, widgets, oldPos, newPos, insertParent, insertParent ) );
				document->setModified( TRUE );

			} else if ( drawRubber ) { // we were drawing a rubber selection
				endRectDraw(); // get rid of the rectangle
				blockSignals( TRUE );
				selectWidgets(); // select widgets which intersect the rect
				blockSignals( FALSE );
				emitSelectionChanged(); // inform about selection changes
			}
			break;
		default: // any insert widget tool is active
			if ( insertParent ) { // we should insert the new widget now
				endRectDraw();
				insertWidget(); // insert report widget
			}
			break;
	}
	widgetPressed = FALSE;
	drawRubber = FALSE;
	insertParent = 0;
	delete buffer;
	buffer = 0;
}


void NCReportDesignerDesignArea::handleKeyPress( QKeyEvent *e, QWidget *w )
{
	e->ignore();
	//checkSelectionsTimer->stop();
	//if ( !checkedSelectionsForMove && ( e->key() == Key_Left ||	 e->key() == Key_Right ||  e->key() == Key_Up ||  e->key() == Key_Down ) && propertyWidget->isWidgetType() )
	//	checkSelectionsForMove( (QWidget*)propertyWidget );
	//checkSelectionsTimer->start( 1000, TRUE );
	if ( e->key() == Qt::Key_Left || e->key() == Qt::Key_Right || e->key() == Qt::Key_Up || e->key() == Qt::Key_Down ) {
		QWidgetList widgets;
		QList<QPoint> oldPos, newPos;
		foreach( Selection s, selections ) {
			if ( s.isUsed() ) {
				int dx = 0, dy = 0;
				bool control = e->modifiers() & Qt::ControlModifier;

				switch ( e->key() ) {
					case Qt::Key_Left: {
						e->accept();
						if ( control )
							dx = -1;
						else
							dx = -grid().x();
					} break;
					case Qt::Key_Right: {
						e->accept();
						if ( control )
							dx = 1;
						else
							dx = grid().x();
					} break;
					case Qt::Key_Up: {
						e->accept();
						if ( control )
							dy = -1;
						else
							dy = -grid().y();
					} break;
					case Qt::Key_Down: {
						e->accept();
						if ( control )
							dy = 1;
						else
							dy = grid().y();
					} break;
					default:
						break;
				}

				widgets.append( s.widget() );
				oldPos.append( s.widget()->pos() );
				newPos.append( s.widget()->pos() + QPoint( dx, dy ) );
			}
		}
		if ( !widgets.isEmpty() ) {
			cmd_MoveCommand *cmd = new cmd_MoveCommand( tr( "Move" ), this, widgets, oldPos, newPos, 0, 0 );
			commandHistory()->addCommand( cmd, TRUE );
			cmd->execute();
		}
	} else if ( e->key() == Qt::Key_Delete ) {
		deleteWidgets();
	}
	if ( !e->isAccepted() ) {
		QWidgetList l = this->findChildren<QWidget *>();
		if ( l.isEmpty() )
			return;
		if ( l.contains( w ) != -1 )
			e->accept();
	}

}

void NCReportDesignerDesignArea::handleKeyRelease( QKeyEvent *e, QWidget * )
{
	e->ignore();
}

void NCReportDesignerDesignArea::selectWidget( QObject *o, bool select )
{
	if ( !o->isWidgetType() )
		return;

	QWidget *w = (QWidget*)o;
	if ( select ) {
/*		QObject *opw = propertyWidget;
		propertyWidget = w;
		if ( opw->isWidgetType() )
			repaintSelection( (QWidget*)opw );*/
		Selection *s = usedSelections.find( w ).value();
		if ( s ) {
			s->show();
			return;
		}

		foreach( Selection s2,  selections ) {
			if ( !s2.isUsed() ) {
				s = &s2;
			}
		}
		/*if ( !s ) {
			s = new Selection( this, usedSelections );
			selections.append( s );
		}*/

		s->setWidget( w );
		emitSelectionChanged();
	} else {
		Selection *s = usedSelections.find( w ).value();
		if ( s )
			s->setWidget( 0 );
/*		QObject *opw = propertyWidget;
		if ( !usedSelections.isEmpty() )
			propertyWidget = Q3PtrDictIterator<WidgetSelection>( usedSelections ).current()->widget();
		else
			propertyWidget = mainContainer();
		if ( opw->isWidgetType() )
			repaintSelection( (QWidget*)opw );
		if ( !isPropertyShowingBlocked() )
			emitShowProperties( propertyWidget );*/
		emitSelectionChanged();
	}

}

QPoint NCReportDesignerDesignArea::grid() const
{
	if ( !mainWindow() || !mainWindow()->snapGrid() )
		return QPoint( 1, 1 );
	return mainWindow()->grid();
}

void NCReportDesignerDesignArea::updateSelection( QWidget *w )
{
	Selection *s = usedSelections[ w ];
	if ( !w->isVisibleTo( this ) )
		selectWidget( w, FALSE );
	else if ( s )
		s->updateGeometry();
}

void NCReportDesignerDesignArea::raiseSelection( QWidget *w )
{
	Selection *s = usedSelections[ w ];
	if ( s )
		s->show();
}

void NCReportDesignerDesignArea::repaintSelection( QWidget *w )
{
	Selection *s = usedSelections[ w ];
	if ( s )
		s->update();
}

void NCReportDesignerDesignArea::clearSelection( bool )
{
	QHashIterator<QWidget*,Selection*> it( usedSelections );
	while ( it.hasNext() ) {
		it.next();
		it.value()->setWidget( 0, FALSE );
	}
/*	Q3PtrDictIterator<Selection> it( usedSelections );
	for ( ; it.current(); ++it )
		it.current()->setWidget( 0, FALSE );*/

	usedSelections.clear();
	emitSelectionChanged();

}

void NCReportDesignerDesignArea::startRectDraw( const QPoint &p, const QPoint &global, QWidget *, RectType t )
{
	QPoint pos( p );
	pos = mapFromGlobal( global );
	oldRectValid = FALSE;
	beginUnclippedPainter( TRUE );
	if ( t == Rubber ) {
		QPen pen( Qt::black, 0, Qt::DotLine );
		unclippedPainter->setPen( pen );
	}
	if ( t == Insert )
		rectAnchor = gridPoint( pos );
	else if ( t == Rubber )
		rectAnchor = pos;
	currRect = QRect( rectAnchor, QPoint( 0, 0 ) );
	if ( t == Insert )
		drawSizePreview( pos, tr("Use Size Hint") );
}

void NCReportDesignerDesignArea::continueRectDraw( const QPoint &p, const QPoint &global, QWidget *, RectType t )
{
	QPoint pos =p;
	pos = mapFromGlobal( global );
	QPoint p2;
	if ( t == Insert )
		p2 = gridPoint( pos );
	else if ( t == Rubber )
		p2 = pos;
	QRect r( rectAnchor, p2 );
	r = r.normalized();

	if ( currRect == r ) {
		QString t = tr( "%1/%2" );
		t = t.arg( r.width() - 1 ).arg( r.height() - 1 );
		drawSizePreview( pos, t );
		return;
	}

	if ( oldRectValid )
		unclippedPainter->drawRect( currRect );
	if ( r.width() > 1 || r.height() > 1 ) {
		oldRectValid = TRUE;
		currRect = r;
		if ( t == Insert ) {
			QString t = tr( "%1/%2" );
			t = t.arg( r.width() - 1 ).arg( r.height() - 1 );
			drawSizePreview( pos, t );
		}
		unclippedPainter->setClipRegion( QRegion( rect() ).subtract( QRect( sizePreviewPos, sizePreviewPixmap.size() ) ) );
		unclippedPainter->drawRect( currRect );
		unclippedPainter->setClipping( FALSE );
	} else {
		oldRectValid = FALSE;
		if ( t == Insert )
			drawSizePreview( pos, tr("Use Size Hint") );
	}
}

void NCReportDesignerDesignArea::endRectDraw()
{
	if ( !unclippedPainter )
		return;

	if ( oldRectValid )
		unclippedPainter->drawRect( currRect );
	drawSizePreview( QPoint(-1,-1), QString::null );
	endUnclippedPainter();
}

void NCReportDesignerDesignArea::selectWidgets()
{
	QWidgetList l = this->findChildren<QWidget *>();
	if ( !l.empty() ) {
		foreach( QWidget *o, l )
		{
			if ( o->isVisibleTo( this ) && insertedWidgets[ o ] ) {
			//if (::qt_cast<NCReportDesignerWidget*>(o) ) {
				QPoint p = o->mapToGlobal( QPoint(0,0) );
				p = mapFromGlobal( p );
				QRect r( p, o->size() );
				if ( r.intersects( currRect ) && !r.contains( currRect ) )
					selectWidget( o );
			}
		}
	}
	emitSelectionChanged();
}

bool NCReportDesignerDesignArea::isWidgetSelected( QObject *w )
{
	if ( w->isWidgetType() )
		return usedSelections.keys().contains( (QWidget*)w ) != 0;
	return FALSE; // #### do stuff for QObjects
}

void NCReportDesignerDesignArea::moveSelectedWidgets( int dx, int dy )
{
	foreach( Selection *s, usedSelections )
	{
		QWidget *w = s->widget();
		w->move( w->x() + dx, w->y() + dy );
		s->updateGeometry();
		//updateChildSelections( w );
	}
}

void NCReportDesignerDesignArea::checkSelectionsForMove( QWidget * )
{
	checkedSelectionsForMove = TRUE;

	///@todo Ojo con esto
//	QObjectList *l = queryList( "QWidget", 0, FALSE, FALSE );
	QWidgetList l = this->findChildren<QWidget*>();
	moving.clear();
	if ( !l.empty() ) {


		/*Q3PtrDictIterator<Selection> it( usedSelections );
		Selection *sel;
		while ( ( sel = it.current() ) != 0 ) {
			//if ( it.current()->widget() == mainContainer() )
			//if ( it.current()->widget() == this )
			//	continue;
			++it;
			if ( l->find( sel->widget() ) == -1 ) {
				sel->setWidget( 0 );
			} else {
				moving.insert( sel->widget(), sel->widget()->pos() );
				//sel->widget()->raise();
				//raiseChildSelections( sel->widget() );
				//raiseSelection( sel->widget() );
			}
		}*/
	}
}

void NCReportDesignerDesignArea::deleteWidgets()
{
	QWidgetList widgets = usedSelections.keys();

	if ( widgets.isEmpty() )
		return;

	cmd_DeleteCommand *cmd = new cmd_DeleteCommand( tr("Delete"), this, widgets );
	commandHistory()->addCommand( cmd );
	cmd->execute();
}

void NCReportDesignerDesignArea::editAdjustSize()
{
}

void NCReportDesignerDesignArea::alignWidgets( Qt::AlignmentFlag af )
{
/*	checkSelectionsForMove( 0 );
	if ( moving.isEmpty() || w->pos() == *moving.find(w) )
		break;

	QWidgetList widgets; // collect the widgets and its old and new positions which have been moved
	QList<QPoint> oldPos, newPos;
	QMapConstIterator<QWidget*,QPoint> it = moving.begin();
	for ( it = moving.begin(); it != moving.end(); ++it ) {
		widgets.append( it.key() );
		oldPos.append( *it );
		newPos.append( it.key()->pos() );
	}*/

	QWidgetList widgets;
	QList<QPoint> oldPos, newPos;
	int cnt =0;
	QWidget *baseWidget = 0;
	QList<Selection *> it = usedSelections.values();
	int nx=0,ny=0;
	QPoint npos(0,0);
	foreach( Selection *s, it ) {
		QWidget *sw = s->widget();
		if ( cnt == 0 ) { // base widget
			baseWidget = sw;
		}
		switch ( af ) {
			case Qt::AlignTop: {
				nx = sw->pos().x(); 	// original x coord
				ny = baseWidget->pos().y();
				break;
			}
			case Qt::AlignBottom: {
				nx = sw->pos().x(); 	// original x coord
				ny = baseWidget->pos().y()+baseWidget->height() - sw->height();
				break;
			}
			case Qt::AlignLeft: {
				nx = baseWidget->pos().x();
				ny = sw->y();
				break;
			}
			case Qt::AlignRight: {
				nx = baseWidget->pos().x() + baseWidget->width() - sw->width();
				ny = sw->y();
				break;
			}
			case Qt::AlignHCenter: {
				nx = sw->pos().x(); 	// original x coord
				ny = baseWidget->pos().y() + baseWidget->height()/2 - sw->height()/2;
				break;
			}
			case Qt::AlignVCenter: {
				nx = baseWidget->pos().x() + baseWidget->width()/2 - sw->width()/2;
				ny = sw->pos().y(); 	// original y coord
				break;
			}
			default: break;
		}
		if ( cnt>0 ) {	// move only non 'base' widgets
			oldPos.append( sw->pos() );
			newPos.append( QPoint( nx,ny ) );
			widgets.append( sw );
		}
		cnt++;
	}

	if ( widgets.isEmpty() )
		return;

	// add move command, don't execute it, this is just a summary of the operations we did during the move-event handling
	cmd_MoveCommand *cmd = new cmd_MoveCommand( tr( "Align" ), this, widgets, oldPos, newPos, 0, 0 );
	commandHistory()->addCommand( cmd, TRUE );
	cmd->execute();

	//commandHistory()->addCommand( new cmd_MoveCommand( tr( "Align" ), this, widgets, oldPos, newPos, this, this ) );

}

QWidgetList NCReportDesignerDesignArea::selectedWidgets() const
{
	return usedSelections.keys();
}


void NCReportDesignerDesignArea::widgetChanged( QObject *w )
{
	if ( w->isWidgetType() )
		updateSelection( (QWidget*)w );
    // ########## do QObject stuff
}

QLabel *NCReportDesignerDesignArea::sizePreview() const
{
	if ( !sizePreviewLabel ) {
		( (NCReportDesignerDesignArea*)this )->sizePreviewLabel = new QLabel( (NCReportDesignerDesignArea*)this, Qt::WindowStaysOnTopHint );
		( (NCReportDesignerDesignArea*)this )->sizePreviewLabel->hide();
		//( (NCReportDesignerDesignArea*)this )->sizePreviewLabel->setBackgroundColor( QColor( 255, 255, 128 ) );
		( (NCReportDesignerDesignArea*)this )->sizePreviewLabel->setFrameStyle( QFrame::Plain | QFrame::Box );
	}
	return sizePreviewLabel;
}

void NCReportDesignerDesignArea::invalidCheckedSelections()
{
	checkedSelectionsForMove = FALSE;
}

void NCReportDesignerDesignArea::checkGeometry( QRect &r )
{
	if ( !rect().contains( r ) ) {
		if ( r.left() < rect().left() )
			r.moveTopLeft( QPoint( 0, r.top() ) );
		if ( r.right() > rect().right()  )
			r.moveBottomRight( QPoint( rect().right(), r.bottom() ) );
		if ( r.top() < rect().top() )
			r.moveTopLeft( QPoint( r.left(), rect().top() ) );
		if ( r.bottom() > rect().bottom()  )
			r.moveBottomRight( QPoint( r.right(), rect().bottom() ) );
	}
}

void NCReportDesignerDesignArea::focusInEvent( QFocusEvent * )
{
	QPainter p( this );
	paintFocus( &p, true );
}

void NCReportDesignerDesignArea::focusOutEvent( QFocusEvent * )
{
	QPainter p( this );
	paintFocus( &p, false );
	//clearSelection();

/*	if ( propertyWidget && !isMainContainer( propertyWidget ) && !isWidgetSelected( propertyWidget ) ) {
		QObject *opw = propertyWidget;
		propertyWidget = mainContainer();
		if ( opw->isWidgetType() )
			repaintSelection( (QWidget*)opw );
	}*/
}

void NCReportDesignerDesignArea::resizeEvent( QResizeEvent * )
{
/*	QWidget::resizeEvent( e );
	if ( isVisible() )
		formFile()->setModified( TRUE, FormFile::WNCReportDesignerDesignArea );

#if defined(Q_WS_WIN32)
    windowsRepaintWorkaroundTimer->start( 100, TRUE );
#endif
}

void NCReportDesignerDesignArea::windowsRepaintWorkaroundTimerTimeout()
{
#if defined(Q_WS_WIN32)
    QObjectList *l = queryList( "QWidget" );
    for ( QObject *o = l->first(); o; o = l->next() ) {
		flickerfree_update( (QWidget*)o );
	}
	flickerfree_update( this );
	delete l;
#endif*/
}

QWidgetList NCReportDesignerDesignArea::widgets()
{
 	return insertedWidgets.values();
}

QWidget *NCReportDesignerDesignArea::designerWidget( QObject * ) const
{
/*	if ( !o || !o->isWidgetType() )
		return 0;
	QWidget *w = (QWidget*)o;
	while ( w && !isMainContainer( w ) && !insertedWidgets[ (void*)w ] || isCentralWidget( w ) )
		w = (QWidget*)w->parent();
	return w;*/
	return 0;
}


void NCReportDesignerDesignArea::emitSelectionChanged()
{
/*	selectionChangedTimer->stop();
	selectionChangedTimer->start( 0, TRUE );*/
}

void NCReportDesignerDesignArea::updatePropertiesTimerDone()
{
/*	if ( propertyWidget && mainWindow()->NCReportDesignerDesignArea() == this )
		emit updateProperties( propertyWidget );*/
}

void NCReportDesignerDesignArea::showPropertiesTimerDone()
{
/*	if ( propertyWidget && mainWindow()->NCReportDesignerDesignArea() == this )
		emit showProperties( propertyWidget );*/
}

void NCReportDesignerDesignArea::selectionChangedTimerDone()
{
	emit selectionChanged();
}

void NCReportDesignerDesignArea::toolChanged()
{
	toolFixed = FALSE;
	int t = mwindow->currentTool();
	if ( currTool == t )//&& t != ORDER_TOOL )
		return;

    // tool cleanup
	switch ( currTool ) {
		case PointerTool:
			break;
		default:
			if ( insertParent )
				endRectDraw();
			break;
	}

	startWidget = endWidget = 0;
	widgetPressed = FALSE;
	drawRubber = FALSE;
	insertParent = 0;
	delete buffer;
	buffer = 0;

	currTool = t;

	if ( hasFocus() )
		clearSelection( FALSE );

	mainWindow()->statusBar()->clearMessage();

    // tool setup
	switch ( currTool ) {
		case PointerTool:
			restoreCursors( this, this );
			break;
		default:
			mainWindow()->statusBar()->showMessage( tr( "Click on the form to insert a %1..." ).arg( "xxx" ) );
			setCursorToAll( Qt::CrossCursor, this );
			//if ( mainWindow()->NCReportDesignerDesignArea() == this )
			//	emitShowProperties( mainContainer() );
			break;
	}
}

void NCReportDesignerDesignArea::showOrderIndicators()
{
}

void NCReportDesignerDesignArea::hideOrderIndicators()
{
}

void NCReportDesignerDesignArea::updateOrderIndicators()
{
}

void NCReportDesignerDesignArea::repositionOrderIndicators()
{
}


void NCReportDesignerDesignArea::updateUndoInfo()
{
// 	commandHistory()->emitUndoRedo();
}

bool NCReportDesignerDesignArea::checkCustomWidgets()
{
	return TRUE;
}


int NCReportDesignerDesignArea::numSelectedWidgets() const
{
	return usedSelections.count();
}

void NCReportDesignerDesignArea::lowerWidgets()
{
	QWidgetList widgets = usedSelections.keys();
	cmd_LowerCommand *cmd = new cmd_LowerCommand( tr( "Lower" ), this, widgets );
	cmd->execute();
	commandHistory()->addCommand( cmd );
}


void NCReportDesignerDesignArea::raiseWidgets()
{
	QWidgetList widgets = usedSelections.keys();
	cmd_RaiseCommand *cmd = new cmd_RaiseCommand( tr( "Raise" ), this, widgets );
	cmd->execute();
	commandHistory()->addCommand( cmd );
}

QString NCReportDesignerDesignArea::copy()
{
	NCReportDesignerResourceHandler resource;
	resource.setDocument( document );
	resource.setDesignArea( this );
	resource.setMeasurement( m );
	return resource.copy();
}

void NCReportDesignerDesignArea::paste( const QString &cb, QWidget *parent )
{
	NCReportDesignerResourceHandler resource;
	resource.setDocument( document );
	resource.setDesignArea( this );
	resource.setMeasurement( m );
	resource.paste( cb, parent );
}

void NCReportDesignerDesignArea::selectAll()
{
	checkedSelectionsForMove = FALSE;
	blockSignals( TRUE );
	QList<QWidget *> l = this->findChildren<QWidget *>();
	if ( !l.isEmpty() ) {
		foreach( QWidget *o, l ) {
			if ( o->isVisibleTo( this ) && insertedWidgets[o] ) {
				selectWidget( o );
			}
		}
		//delete l;
	}

	blockSignals( FALSE );
	emitSelectionChanged();
}




int NCReportDesignerDesignArea::numVisibleWidgets() const
{
/*	Q3PtrDictIterator<QWidget> it( insertedWidgets );
	int visible = 0;
	for ( ; it.current(); ++it ) {
		if ( it.current()->isVisibleTo( (NCReportDesignerDesignArea*)this ) )
			visible++;
	}
	return visible;*/
	return 0;
}


bool NCReportDesignerDesignArea::allowMove( QWidget * )
{
/*	w = w->parentWidget();
	while ( w ) {
		if ( ( isMainContainer( w ) || insertedWidgets.find( w ) ) && WidgetFactory::layoutType( w ) == WidgetFactory::NoLayout )
			return TRUE;
		w = w->parentWidget();
	}*/

	return TRUE;
}


void NCReportDesignerDesignArea::editConnections()
{
/*	buffer = 0;
	if ( !startWidget || !endWidget )
		return;

	ConnectionDialog dlg( mwindow );
	mainWindow()->statusBar()->message( tr( "Edit connections...") );
	dlg.addConnection( startWidget, endWidget, QString::null, QString::null );
	QTimer::singleShot( 0, &dlg, SLOT(ensureConnectionVisible()) );
	dlg.exec();*/
}

void NCReportDesignerDesignArea::saveBackground()
{
/*	if ( buffer )
		delete buffer;
	buffer = new QPixmap( width(), height() );
	*buffer = QPixmap::grabWindow( winId() );*/
}

void NCReportDesignerDesignArea::restoreConnectionLine()
{
/*	if (!unclippedPainter || !buffer) // designer will occasionally crash if buffer is not tested to be non-zero
		return;

	int a =qAbs( startPos.x() - currentPos.x() );
	int b = qAbs( startPos.y() - currentPos.y() );
	QRect r( startPos, currentPos );

	if ( a < 32 || b < 32 ) { // special case: vertical or horizontal line
		r = r.normalized();
		unclippedPainter->drawPixmap( r.x() - 2, r.y() - 2, *buffer,
									  r.x() - 2, r.y() - 2, r.width() + 4, r.height() + 4 );
		return;
	}

	if ( a <= 0 )
		a = 1;
	if ( b <= 0 )
		b = 1;
	int w, h;
	if ( b > a ) {
		h = 64;
		w = ( a * h ) / b;
	} else {
		w = 64;
		h = ( b * w ) / a;
	}

	int dx = 2 * w / 3;
	int dy = 2 * h / 3;
	QPoint p( startPos );

	if ( r.x() > r.right() ) {
		dx = dx * -1;
		p.setX( p.x() - 64 );
		r.moveBy( -64, 0 );
	}
	if ( r.y() > r.bottom() ) {
		dy = dy * -1;
		p.setY( p.y() - 64 );
		r.moveBy( 0, -64 );
	}

	w = h = 64;
	r = r.normalized();
	while ( r.contains( p ) ) {
		unclippedPainter->drawPixmap( p, *buffer, QRect( p, QSize( w, h ) ) );
		unclippedPainter->setPen( Qt::red );
		p.setX( p.x() + dx );
		p.setY( p.y() + dy );
	}

	unclippedPainter->drawPixmap( startPos.x() - 10, startPos.y() - 10, *buffer,
								  startPos.x() - 10, startPos.y() - 10, 20, 20 );*/
}

void NCReportDesignerDesignArea::restoreRect( const QRect &rect )
{
	if (!unclippedPainter || !buffer)
		return;

	QRect r( rect );
	r = r.normalized();

	r = QRect( r.x() + 2, r.y() + 2, r.width() - 4, r.height() - 4 );

	unclippedPainter->drawPixmap( r.x() - 2, r.y() - 2, *buffer, r.x() - 2, r.y() - 2, r.width() + 4, 4 );
	unclippedPainter->drawPixmap( r.x() - 2, r.y() - 2, *buffer, r.x() - 2, r.y() - 2, 4, r.height() + 4 );
	unclippedPainter->drawPixmap( r.x() - 2, r.y() + r.height() - 3, *buffer, r.x() - 2, r.y() + r.height() - 3, r.width() + 4, 5 );
	unclippedPainter->drawPixmap( r.x() + r.width() - 2, r.y(), *buffer, r.x() + r.width() - 2, r.y(), 4, r.height() + 4 );
}

void NCReportDesignerDesignArea::drawConnectionLine()
{
	if ( !unclippedPainter )
		return;

	unclippedPainter->setPen( QPen( Qt::white, 2 ) );
	unclippedPainter->drawLine( startPos, currentPos );
	if ( validForBuddy )
		unclippedPainter->setPen( QPen( Qt::darkRed, 1 ) );
	else
		unclippedPainter->setPen( QPen( Qt::darkCyan, 1 ) );
	unclippedPainter->drawLine( startPos, currentPos );

	if ( validForBuddy )
		unclippedPainter->setPen( QPen( Qt::darkGreen, 1 ) );
	else
		unclippedPainter->setPen( QPen( Qt::magenta, 1 ) );
	if ( startWidget ) {
		QWidget *s = (QWidget*)startWidget;
		QPoint p = mapToForm( s, QPoint(0,0) );
		unclippedPainter->drawRect( QRect( p + QPoint( 2, 2 ), s->size() - QSize( 4, 4 ) ) );
	}
	if ( endWidget ) {
		QWidget *e = (QWidget*)endWidget;
		QPoint p = mapToForm( e, QPoint(0,0) );
		unclippedPainter->drawRect( QRect( p + QPoint( 2, 2 ), e->size() - QSize( 4, 4 ) ) );
	}
}



void NCReportDesignerDesignArea::visibilityChanged()
{
	updateOrderIndicators();
	repositionOrderIndicators();
}


/*!
  Maps \a pos in \a w's coordinates to the form's coordinate system.

  This is the equivalent to mapFromGlobal(w->mapToGlobal(pos) ) but
  avoids the two roundtrips to the X-Server on Unix/X11.
 */
QPoint NCReportDesignerDesignArea::mapToForm( const QWidget* w, const QPoint&  pos ) const
{
	QPoint p = pos;
	const QWidget* i = w;
	while ( i && !i->isTopLevel() && !isMainContainer( (QWidget*)i ) ) {
		p = i->mapToParent( p );
		i = i->parentWidget();
	}
	return mapFromGlobal( w->mapToGlobal( pos ) );
}


/*
static int widgetDepth( QWidget *w )
{
	int d = -1;
	while ( w && !w->isTopLevel() ) {
		d++;
		w = w->parentWidget();
	}

	return d;
}

static bool isChildOf( QWidget *c, QWidget *p )
{
	while ( c && !c->isTopLevel() ) {
		if ( c == p )
			return TRUE;
		c = c->parentWidget();
	}
	return FALSE;
}
*/

bool NCReportDesignerDesignArea::isMainContainer( QObject *w ) const
{
	return w && w->isWidgetType() && ( w == (QWidget*)this || w == mainContainer() );
}

void NCReportDesignerDesignArea::setMainContainer( QWidget *w )
{
	bool resetPropertyWidget = isMainContainer( propertyWidget );
	if ( mContainer )
		insertedWidgets.remove( mContainer );
	if ( propertyWidget == mContainer )
		propertyWidget = 0;
	delete mContainer;
	mContainer = w;
	insertedWidgets.insert( mContainer, mContainer );
	delete layout();
	QHBoxLayout *l = new QHBoxLayout( this );
	l->addWidget( w );
	if ( resetPropertyWidget ) {
		QObject *opw = propertyWidget;
		propertyWidget = mContainer;
		if ( opw && opw->isWidgetType() )
			repaintSelection( (QWidget*)opw );
	}
}


void NCReportDesignerDesignArea::setActiveObject( QObject *o )
{
	//emitShowProperties( o );
	propertyWidget = o;
}


void NCReportDesignerDesignArea::drawSizePreview( const QPoint &pos, const QString& text )
{
	unclippedPainter->save();
	unclippedPainter->setPen( QPen( this->palette().foreground(), 1  ));
	// Reemplazo de la funcion en Qt4
	unclippedPainter->setCompositionMode( QPainter::CompositionMode_SourceOver );
	//unclippedPainter->setRasterOp( CopyROP );
	if ( !sizePreviewPixmap.isNull() )
		unclippedPainter->drawPixmap( sizePreviewPos, sizePreviewPixmap );
	if ( text.isNull() ) {
		sizePreviewPixmap = QPixmap(); // set null again
		unclippedPainter->restore();
		return;
	}
	QRect r  =  fontMetrics().boundingRect( 0, 0, 0, 0, Qt::AlignCenter, text );
	r = QRect( pos + QPoint( 10, 10 ), r.size() + QSize( 5, 5 ) );

	checkGeometry( r );

	sizePreviewPos = r.topLeft();
	sizePreviewPixmap = QPixmap::grabWindow( winId(), r.x(), r.y(), r.width(), r.height() );
	unclippedPainter->setBrush( QColor( 255, 255, 128 ) );
	unclippedPainter->drawRect( r );
	//unclippedPainter->drawEllipse( r );
	unclippedPainter->drawText( r, Qt::AlignCenter, text );
	unclippedPainter->restore();
}

void NCReportDesignerDesignArea::undo()
{
	commandHistory()->undo();
}

void NCReportDesignerDesignArea::redo()
{
	commandHistory()->redo();
}


NCReportDesignerCommandHistory *NCReportDesignerDesignArea::commandHistory()
{
	return &commands;
}

void NCReportDesignerDesignArea::paintFocus( QPainter *p, bool focusOn )
{
	if ( focusOn ) {
		QPen pen( Qt::blue, 0, Qt::DotLine );
		p->setPen( pen );
	}
	else
		p->setPen( this->backgroundRole()/*  backgroundColor()*/ );

	p->drawRect( 0,0,width(), height());
}

void NCReportDesignerDesignArea::runWidgetSettingsDialog( NCReportDesignerWidget *w, bool init )
{
	WProperty p_old( w->p );
	//WProperty p_new;

	NCReportDesignerWidgetSetDialog *dia = new NCReportDesignerWidgetSetDialog( w, this, document, "wdialog", TRUE );
	dia->setSaveToProperty( &(w->p) );

	switch (dia->exec()) {
		case QDialog::Accepted: {
			if (init) {	// at init mode don't need to call set command
				dia->saveSettings();
				w->updateWidget();
				break;
			}

			dia->saveSettings();
			WProperty p_new( w->p );
			cmd_SetPropertyCommand *cmd = new cmd_SetPropertyCommand( tr( "Set property" ), this, w, p_old, p_new );
			commandHistory()->addCommand( cmd );
			cmd->execute();

			break;
		}
	}
	delete dia;
}




