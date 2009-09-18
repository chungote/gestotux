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
#include "ncreportdesignersizehandler.h"
#include "ncreportdesignerdesignarea.h"
#include "ncreportdesignerdocument.h"
#include "ncreportdesignerwidget.h"
#include "measurement.h"

#include <QVariant>
#include <QPainter>
#include <QApplication>
#include <QLabel>
#include <QMouseEvent>

#define	SIZEHANDLERSIZE		4

SizeHandler::SizeHandler( NCReportDesignerDesignArea *parent, Direction d, Selection *s )
	: QWidget( parent )
{
	active = TRUE;
	setBackgroundRole( active ? QPalette::Text : QPalette::Dark );
	//setPaletteBackgroundColor( Qt::blue );

	setFixedSize( SIZEHANDLERSIZE, SIZEHANDLERSIZE );
	widget = 0;
	dir =d ;
	setMouseTracking( FALSE );
	da = parent;
	sel = s;
	updateCursor();
	//qDebug("SizeHandler created.");
}

SizeHandler::~ SizeHandler( )
{
	//qDebug("SizeHandler destroyed.");
}

void SizeHandler::updateCursor()
{
	if ( !active ) {
		setCursor( QCursor( Qt::ArrowCursor) );
		return;
	}

	switch ( dir ) {
		case LeftTop:
			setCursor( Qt::SizeFDiagCursor );
			break;
		case Top:
			setCursor( Qt::SizeVerCursor );
			break;
		case RightTop:
			setCursor( Qt::SizeBDiagCursor );
			break;
		case Right:
			setCursor( Qt::SizeHorCursor );
			break;
		case RightBottom:
			setCursor( Qt::SizeFDiagCursor );
			break;
		case Bottom:
			setCursor( Qt::SizeVerCursor );
			break;
		case LeftBottom:
			setCursor( Qt::SizeBDiagCursor );
			break;
		case Left:
			setCursor( Qt::SizeHorCursor );
			break;
	}
}

void SizeHandler::setActive( bool a )
{
	active = a;
	setBackgroundRole( active ? QPalette::Text : QPalette::Dark );

	updateCursor();
}

void SizeHandler::setWidget( QWidget *w )
{
	widget = w;
}

void SizeHandler::paintEvent( QPaintEvent * )
{
	if ( ( (NCReportDesignerDesignArea*)parentWidget() )->currentWidget() != widget )
		return;
	QPainter p( this );
	QPen pen( Qt::black, 0, Qt::SolidLine );
	if ( active )
		p.setPen( Qt::blue );
	else
		p.setPen( Qt::black );
	p.drawRect( 0, 0, width(), height() );
}

void SizeHandler::mousePressEvent( QMouseEvent *e )
{
	if ( !widget || e->button() != Qt::LeftButton || !active )
		return;
	oldPressPos = e->pos();
	geom = origGeom = QRect( widget->pos(), widget->size() );
}

void SizeHandler::mouseMoveEvent( QMouseEvent *e )
{
	//if ( !widget || ( e->button() & Qt::LeftButton ) != Qt::LeftButton || !active )
	//if ( !widget || e->button() != Qt::LeftButton || !active ) {
	//qDebug( "mouseMoveEvent. e->button()=%i, e->state=%i, widget=%p, active=%i", e->button(), e->state(), widget, active );
	//qDebug( "Qt::LeftButton = %i", Qt::LeftButton );


	if ( !widget || !active ) {
		return;
	}


	QPoint rp = mapFromGlobal( e->globalPos() );
	QPoint d = oldPressPos - rp;
	oldPressPos = rp;
	QPoint checkPos = widget->parentWidget()->mapFromGlobal( e->globalPos() );
	QRect pr = widget->parentWidget()->rect();

    // ##### move code around a bit to reduce duplicated code here
	switch ( dir ) {
		case LeftTop: {
			if ( checkPos.x() > pr.width() - 2 * width() || checkPos.y() > pr.height() - 2 * height() )
				return;
			int w = geom.width() + d.x();
			geom.setWidth( w );
			w = ( w / da->grid().x() ) * da->grid().x();
			int h = geom.height() + d.y();
			geom.setHeight( h );
			h = ( h / da->grid().y() ) * da->grid().y();
			int dx = widget->width() - w;
			int dy = widget->height() - h;
			trySetGeometry( widget, widget->x() + dx, widget->y() + dy, w, h );
		} break;
		case Top: {
			if ( checkPos.y() > pr.height() - 2 * height() )
				return;
			int h = geom.height() + d.y();
			geom.setHeight( h );
			h = ( h / da->grid().y() ) * da->grid().y();
			int dy = widget->height() - h;
			trySetGeometry( widget, widget->x(), widget->y() + dy, widget->width(), h );
		} break;
		case RightTop: {
			if ( checkPos.x() < 2 * width() || checkPos.y() > pr.height() - 2 * height() )
				return;
			int h = geom.height() + d.y();
			geom.setHeight( h );
			h = ( h / da->grid().y() ) * da->grid().y();
			int dy = widget->height() - h;
			int w = geom.width() - d.x();
			geom.setWidth( w );
			w = ( w / da->grid().x() ) * da->grid().x();
			trySetGeometry( widget, widget->x(), widget->y() + dy, w, h );
		} break;
		case Right: {
			if ( checkPos.x() < 2 * width() )
				return;
			int w = geom.width() - d.x();
			geom.setWidth( w );
			w = ( w / da->grid().x() ) * da->grid().x();
			tryResize( widget, w, widget->height() );
		} break;
		case RightBottom: {
			if ( checkPos.x() < 2 * width() || checkPos.y() < 2 * height() )
				return;
			int w = geom.width() - d.x();
			geom.setWidth( w );
			w = ( w / da->grid().x() ) * da->grid().x();
			int h = geom.height() - d.y();
			geom.setHeight( h );
			h = ( h / da->grid().y() ) * da->grid().y();
			tryResize( widget, w, h );
		} break;
		case Bottom: {
			if ( checkPos.y() < 2 * height() )
				return;
			int h = geom.height() - d.y();
			geom.setHeight( h );
			h = ( h / da->grid().y() ) * da->grid().y();
			tryResize( widget, widget->width(), h );
		} break;
		case LeftBottom: {
			if ( checkPos.x() > pr.width() - 2 * width() || checkPos.y() < 2 * height() )
				return;
			int w = geom.width() + d.x();
			geom.setWidth( w );
			w = ( w / da->grid().x() ) * da->grid().x();
			int dx = widget->width() - w;
			int h = geom.height() - d.y();
			geom.setHeight( h );
			h = ( h / da->grid().y() ) * da->grid().y();
			trySetGeometry( widget, widget->x() + dx, widget->y(), w, h );
		} break;
		case Left: {
			if ( checkPos.x() > pr.width() - 2 * width() )
				return;
			int w = geom.width() + d.x();
			geom.setWidth( w );
			w = ( w / da->grid().x() ) * da->grid().x();
			int dx = widget->width() - w;
			trySetGeometry( widget, widget->x() + dx, widget->y(), w, widget->height() );
		} break;
	}

	QPoint p = pos();
	sel->updateGeometry();
	oldPressPos += ( p - pos() );

	//da->sizePreview()->setText( tr( "%1/%2" ).arg( widget->width() ).arg( widget->height() ) );
	da->sizePreview()->setText( da->measurement()->pixelSizeToMeasureCaption( widget->width(), widget->height() ));
	da->sizePreview()->adjustSize();
	QRect lg( da->mapFromGlobal( e->globalPos() ) + QPoint( 16, 16 ),
			  da->sizePreview()->size() );
	//da->checkGeometry( lg );
	da->sizePreview()->setGeometry( lg );
	da->sizePreview()->show();
	da->sizePreview()->raise();

	//if ( WidgetFactory::layoutType( widget ) != WidgetFactory::NoLayout )
	//	da->updateChildSelections( widget );
}

void SizeHandler::mouseReleaseEvent( QMouseEvent *e )
{
	if ( e->button() != Qt::LeftButton || !active )
		return;

	da->sizePreview()->hide();
	if ( geom != widget->geometry() ) {
		da->commandHistory()->addCommand( new cmd_ResizeCommand( tr( "Resize" ),
					da, widget, origGeom, widget->geometry() ) );
		da->parentDocument()->setModified( TRUE );
	}
	//da->emitUpdateProperties( widget );
}

void SizeHandler::trySetGeometry( QWidget *w, int x, int y, int width, int height )
{
	// noci
	//QRect r( x,y,width,height);
	//da->checkGeometry( r );
	//w->setGeometry( r );
	//return;

	int minw = qMax( w->minimumSizeHint().width(), w->minimumSize().width() );
	minw = qMax( minw, 2 * da->grid().x() );
	int minh = qMax( w->minimumSizeHint().height(), w->minimumSize().height() );
	minh = qMax( minh, 2 * da->grid().y() );

	if ( sel->selectType() == Selection::Full && ( qMax( minw, width ) > w->maximumWidth() || qMax( minh, height ) > w->maximumHeight() ) )
		return;
	if ( sel->selectType() != Selection::Vertical && qMax( minw, width ) > w->maximumWidth() )
		return;
	if ( sel->selectType() != Selection::Horizontal && qMax( minh, height ) > w->maximumHeight() )
		return;

	if ( width < minw && x != w->x() )
		x -= minw - width;
	if ( height < minh && y != w->y() )
		y -= minh - height;
	w->setGeometry( x, y, qMax( minw, width ), qMax( minh, height ) );
}

void SizeHandler::tryResize( QWidget *w, int width, int height )
{
	int minw = qMax( w->minimumSizeHint().width(), w->minimumSize().width() );
	minw = qMax( minw, 6 );
	int minh = qMax( w->minimumSizeHint().height(), w->minimumSize().height() );
	minh = qMax( minh, 6 );
	w->resize( qMax( minw, width ), qMax( minh, height ) );
	//w->setFixedSize( qMax( minw, width ), qMax( minh, height ) );
}

//////////////////////////////////////////////////////////
// Selection
//////////////////////////////////////////////////////////

Selection::Selection( NCReportDesignerDesignArea *parent, QHash<QWidget*,Selection*> *selDict )
	: selectionDict( selDict )
{
	da = parent;
	selType = Full;
	for ( int i = SizeHandler::LeftTop; i <= SizeHandler::Left; ++i ) {
		handles.insert( i, new SizeHandler( parent, (SizeHandler::Direction)i, this ) );
	}
	hide();
}

void Selection::setWidget( QWidget *w, bool updateDict )
{
	if ( !w ) {
		hide();
		if ( updateDict )
			selectionDict->remove( wid );
		wid = 0;
		return;
	}

	NCReportDesignerWidget *test = qobject_cast<NCReportDesignerWidget*>(w);
	if ( test != 0 ) {
		selType = test->d_selectType;
	}

	wid = w;
	bool active = true; //!wid->parentWidget();  // || WidgetFactory::layoutType( wid->parentWidget() ) == WidgetFactory::NoLayout;
	for ( int i = SizeHandler::LeftTop; i <= SizeHandler::Left; ++i ) {
		SizeHandler *h = handles[ i ];
		if ( h ) {
			h->setWidget( wid );
			h->setActive( active );
		}
	}
	updateGeometry();
	show();
	if ( updateDict )
		selectionDict->insert( w, this );
}

bool Selection::isUsed() const
{
	return wid != 0;
}

void Selection::updateGeometry()
{
	if ( !wid || !wid->parentWidget() )
		return;

	QPoint p = wid->parentWidget()->mapToGlobal( wid->pos() );
	p = da->mapFromGlobal( p );
	QRect r( p, wid->size() );

	int w = SIZEHANDLERSIZE;
	int h = SIZEHANDLERSIZE;

	for ( int i = SizeHandler::LeftTop; i <= SizeHandler::Left; ++i ) {
		SizeHandler *hndl = handles[ i ];
		if ( !hndl )
			continue;
		switch ( i ) {
			case SizeHandler::LeftTop:
				hndl->move( r.x() - w / 2, r.y() - h / 2 );
				break;
			case SizeHandler::Top:
				hndl->move( r.x() + r.width() / 2 - w / 2, r.y() - h / 2 );
				break;
			case SizeHandler::RightTop:
				hndl->move( r.x() + r.width() - w / 2, r.y() - h / 2 );
				break;
			case SizeHandler::Right:
				hndl->move( r.x() + r.width() - w / 2, r.y() + r.height() / 2 - h / 2 );
				break;
			case SizeHandler::RightBottom:
				hndl->move( r.x() + r.width() - w / 2, r.y() + r.height() - h / 2 );
				break;
			case SizeHandler::Bottom:
				hndl->move( r.x() + r.width() / 2 - w / 2, r.y() + r.height() - h / 2 );
				break;
			case SizeHandler::LeftBottom:
				hndl->move( r.x() - w / 2, r.y() + r.height() - h / 2 );
				break;
			case SizeHandler::Left:
				hndl->move( r.x() - w / 2, r.y() + r.height() / 2 - h / 2 );
				break;
			default:
				break;
		}
	}
}

void Selection::hide()
{
	for ( int i = SizeHandler::LeftTop; i <= SizeHandler::Left; ++i ) {
		SizeHandler *h = handles[ i ];
		if ( h )
			h->hide();
	}
}

void Selection::show()
{
	for ( int i = SizeHandler::LeftTop; i <= SizeHandler::Left; ++i ) {
		SizeHandler *h = handles[ i ];
		if ( h ) {
			// Noc.
			if ( selType == Horizontal ) {  // leave hidden needless sizehandlers
				if ( i != SizeHandler::Left && i != SizeHandler::Right )
					continue;
			} else if ( selType == Vertical ) {
				if ( i != SizeHandler::Top && i != SizeHandler::Bottom )
					continue;
			}
			h->show();
			h->raise();
			//h->lower();
		}
	}
}

void Selection::update()
{
	for ( int i = SizeHandler::LeftTop; i <= SizeHandler::Left; ++i ) {
		SizeHandler *h = handles[ i ];
		if ( h )
			h->update();
	}
}

QWidget *Selection::widget() const
{
	return wid;
}

Selection::SelectionType Selection::selectType( )
{
	return selType;
}


