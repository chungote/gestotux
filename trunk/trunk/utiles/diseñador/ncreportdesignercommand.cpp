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
#include "ncreportdesignercommand.h"
#include "ncreportdesignerdesignarea.h"
#include "ncreportdesignerwindow.h"
#include "ncreportdesignerdocument.h"

//#include <qfeatures.h>
#include <QWidget>
/*#include <qmetaobject.h>
#include <qapplication.h>
#include <qlayout.h>
#include <qmessagebox.h>
#include <qlistbox.h>
#include <qiconview.h>
#include <qtextedit.h>
#include <qptrstack.h>
#include <qheader.h>
#include <qsplitter.h>
#include <qaction.h>*/

NCReportDesignerCommandHistory::NCReportDesignerCommandHistory( int s )
    : current( -1 ), steps( s ), savedAt( -1 )
{
    history.setAutoDelete( TRUE );
    modified = FALSE;
    compressedCommand = 0;
}

void NCReportDesignerCommandHistory::addCommand( NCReportDesignerCommand *cmd, bool tryCompress )
{
	if ( tryCompress ) {
		if ( !compressedCommand || compressedCommand->type() != cmd->type() || !compressedCommand->canMerge( cmd ) ) {
			checkCompressedCommand();
			compressedCommand = 0;
		}

		if ( compressedCommand ) {
			compressedCommand->merge( cmd );
			modified = TRUE;
			modificationChanged( modified );
			return;
		}
		compressedCommand = cmd;
	} else {
		checkCompressedCommand();
	}

	if ( current < (int)history.count() - 1 ) {
		if ( current < savedAt )
			savedAt = -2;

		QPtrList<NCReportDesignerCommand> commands;
		commands.setAutoDelete( FALSE );

		for( int i = 0; i <= current; ++i ) {
			commands.insert( i, history.at( 0 ) );
			history.take( 0 );
		}

		commands.append( cmd );
		history.clear();
		history = commands;
		history.setAutoDelete( TRUE );
	} else {
		history.append( cmd );
	}

	if ( (int)history.count() > steps ) {
		savedAt--;
		history.removeFirst();
	} else {
		++current;
	}

	emitUndoRedo();
	modified = TRUE;
	modificationChanged( modified );
}

void NCReportDesignerCommandHistory::undo()
{
	checkCompressedCommand();
	compressedCommand = 0;
	if ( current > -1 ) {
		history.at( current )->unexecute();
		--current;
	}
	emitUndoRedo();
	modified = savedAt != current;
	modificationChanged( modified );
}

void NCReportDesignerCommandHistory::redo()
{
	checkCompressedCommand();
	compressedCommand = 0;
	if ( current > -1 ) {
		if ( current < (int)history.count() - 1 ) {
			++current;
			history.at( current )->execute();
		}
	} else {
		if ( history.count() > 0 ) {
			++current;
			history.at( current )->execute();
		}
	}
	emitUndoRedo();
	modified = savedAt != current;
	modificationChanged( modified );
}

void NCReportDesignerCommandHistory::emitUndoRedo()
{
	NCReportDesignerCommand *undoCmd = 0;
	NCReportDesignerCommand *redoCmd = 0;

	if ( current >= 0 && current < (int)history.count() )
		undoCmd = history.at( current );
	if ( current + 1 >= 0 && current + 1 < (int)history.count() )
		redoCmd = history.at( current + 1 );

	bool ua = (undoCmd != 0);
	QString uc;
	if ( ua )
		uc = undoCmd->name();
	bool ra = (redoCmd != 0);
	QString rc;
	if ( ra )
		rc = redoCmd->name();
	emit undoRedoChanged( ua, ra, uc, rc );
}

void NCReportDesignerCommandHistory::setModified( bool m )
{
    modified = m;
    if ( !modified )
	savedAt = current;
    modificationChanged( modified );
}

bool NCReportDesignerCommandHistory::isModified() const
{
    return modified;
}

void NCReportDesignerCommandHistory::checkCompressedCommand()
{
    if ( compressedCommand && compressedCommand->type() == NCReportDesignerCommand::SetProperty ) {
	NCReportDesignerCommand *c = compressedCommand;
	compressedCommand = 0;
	//if ( !( (SetPropertyCommand*)c )->checkProperty() ) {
	//    history.remove( current );
	//    --current;
	//    emitUndoRedo();
	//}
    }
}

// ------------------------------------------------------------

NCReportDesignerCommand::NCReportDesignerCommand( const QString &n, NCReportDesignerDesignArea *da )
    : cmdName( n ), dArea( da )
{
}

NCReportDesignerCommand::~NCReportDesignerCommand()
{
}

QString NCReportDesignerCommand::name() const
{
    return cmdName;
}

NCReportDesignerDesignArea *NCReportDesignerCommand::designArea() const
{
    return dArea;
}

void NCReportDesignerCommand::merge( NCReportDesignerCommand * )
{
}

bool NCReportDesignerCommand::canMerge( NCReportDesignerCommand * )
{
    return FALSE;
}

// ------------------------------------------------------------

cmd_ResizeCommand::cmd_ResizeCommand( const QString &n, NCReportDesignerDesignArea *da,
			      QWidget *w, const QRect &oldr, const QRect &nr )
    : NCReportDesignerCommand( n, da ), widget( w ), oldRect( oldr ), newRect( nr )
{
}

void cmd_ResizeCommand::execute()
{
    widget->setGeometry( newRect );
    designArea()->updateSelection( widget );
	designArea()->parentDocument()->setModified( TRUE );
    //designArea()->emitUpdateProperties( widget );
	//designArea()->updateChildSelections( widget );
}

void cmd_ResizeCommand::unexecute()
{
    widget->setGeometry( oldRect );
    designArea()->updateSelection( widget );
    //designArea()->emitUpdateProperties( widget );
	//designArea()->updateChildSelections( widget );
}

// ------------------------------------------------------------

cmd_InsertCommand::cmd_InsertCommand( const QString &n, NCReportDesignerDesignArea *da,
			      QWidget *w, const QRect &g )
    : NCReportDesignerCommand( n, da ), widget( w ), geometry( g )
{
}

void cmd_InsertCommand::execute()
{
    if ( geometry.size() == QSize( 0, 0 ) ) {
		widget->move( geometry.topLeft() );
		//widget->adjustSize();
    } else {
		QSize s = widget->size();	//geometry.size().expandedTo( widget->minimumSize() );
		QRect r( geometry.topLeft(), geometry.size().expandedTo( widget->size() ) );
		//s = s.expandedTo( widget->minimumSizeHint() );
		widget->setGeometry( r );
	}
    widget->show();
    designArea()->widgets()->insert( widget, widget );
    designArea()->clearSelection( FALSE );
    designArea()->selectWidget( widget );
	designArea()->parentDocument()->setModified( TRUE );

}

void cmd_InsertCommand::unexecute()
{
    widget->hide();
    designArea()->selectWidget( widget, FALSE );
    designArea()->widgets()->remove( widget );
 }

// ------------------------------------------------------------

cmd_MoveCommand::cmd_MoveCommand( const QString &n, NCReportDesignerDesignArea *da,
			  const QWidgetList &w,
			  const QList<QPoint> op,
			  const QList<QPoint> np,
			  QWidget *opr, QWidget *npr )
    : NCReportDesignerCommand( n, da ), widgets( w ), oldPos( op ), newPos( np ),
      oldParent( opr ), newParent( npr )
{
    widgets.setAutoDelete( FALSE );
}

void cmd_MoveCommand::merge( NCReportDesignerCommand *c )
{
    cmd_MoveCommand *cmd = (cmd_MoveCommand*)c;
    newPos = cmd->newPos;
}

bool cmd_MoveCommand::canMerge( NCReportDesignerCommand *c )
{
	cmd_MoveCommand *cmd = (cmd_MoveCommand*)c;
    return widgets == cmd->widgets;
}


void cmd_MoveCommand::execute()
{
    for ( QWidget *w = widgets.first(); w; w = widgets.next() ) {
	//if ( !w->parentWidget() || WidgetFactory::layoutType( w->parentWidget() ) == WidgetFactory::NoLayout ) {
	    if ( newParent && oldParent && newParent != oldParent ) {
			QPoint pos = newParent->mapFromGlobal( w->mapToGlobal( QPoint( 0,0 ) ) );
			w->reparent( newParent, pos, TRUE );
			designArea()->raiseSelection( w );
			//designArea()->raiseChildSelections( w );
			designArea()->widgetChanged( w );
	    }
	    w->move( newPos[ widgets.at() ] );
		//}
		designArea()->updateSelection( w );
		//designArea()->updateChildSelections( w );
		//designArea()->emitUpdateProperties( w );
    }
	designArea()->parentDocument()->setModified( TRUE );
}

void cmd_MoveCommand::unexecute()
{
    for ( QWidget *w = widgets.first(); w; w = widgets.next() ) {
	//if ( !w->parentWidget() || WidgetFactory::layoutType( w->parentWidget() ) == WidgetFactory::NoLayout ) {
	    if ( newParent && oldParent && newParent != oldParent ) {
		QPoint pos = oldParent->mapFromGlobal( w->mapToGlobal( QPoint( 0,0 ) ) );
		w->reparent( oldParent, pos, TRUE );
		designArea()->raiseSelection( w );
		//designArea()->raiseChildSelections( w );
		designArea()->widgetChanged( w );
	    }
	    w->move( oldPos[ widgets.at() ] );
	//}
	designArea()->updateSelection( w );
	//designArea()->updateChildSelections( w );
	//designArea()->emitUpdateProperties( w );
    }
}

// ------------------------------------------------------------

cmd_DeleteCommand::cmd_DeleteCommand( const QString &n, NCReportDesignerDesignArea *da,
			      const QWidgetList &wl )
    : NCReportDesignerCommand( n, da ), widgets( wl )
{
    widgets.setAutoDelete( FALSE );
    QWidgetList copyOfWidgets = widgets;
    copyOfWidgets.setAutoDelete(FALSE);

}

void cmd_DeleteCommand::execute()
{
    for ( QWidget *w = widgets.first(); w; w = widgets.next() ) {
		w->hide();
		QString s = w->name();
		s.prepend( "qt_dead_widget_" );
		w->setName( s );
		designArea()->selectWidget( w, FALSE );
		designArea()->widgets()->remove( w );
	}
	designArea()->parentDocument()->setModified( TRUE );
    //designArea()->setPropertyShowingBlocked( FALSE );
    //designArea()->emitShowProperties();

}

void cmd_DeleteCommand::unexecute()
{
    //designArea()->setPropertyShowingBlocked( TRUE );
    designArea()->clearSelection( FALSE );
    for ( QWidget *w = widgets.first(); w; w = widgets.next() ) {
		w->show();
		QString s = w->name();
		s.remove( 0, QString( "qt_dead_widget_" ).length() );
		w->setName( s );
		designArea()->widgets()->insert( w, w );
		designArea()->selectWidget( w );
	}
    //designArea()->setPropertyShowingBlocked( FALSE );
    //designArea()->emitShowProperties();
}

// ------------------------------------------------------------
cmd_SetPropertyCommand::cmd_SetPropertyCommand( const QString &n, NCReportDesignerDesignArea *da,
		QObject *w, const WProperty &op, const WProperty &np, bool reset )
    		: NCReportDesignerCommand( n, da ), widget( w ),
			oldValue( op ), newValue( np ), wasChanged( TRUE ), isResetCommand( reset )
{
    wasChanged = false;
}


void cmd_SetPropertyCommand::execute()
{
    if ( isResetCommand ) {
    }
	setProperty( newValue );
	designArea()->parentDocument()->setModified( TRUE );

}

void cmd_SetPropertyCommand::unexecute()
{
	if ( !wasChanged ) {}
	if ( isResetCommand ) {}
	setProperty( oldValue );
}

bool cmd_SetPropertyCommand::canMerge( NCReportDesignerCommand *c )
{
	return FALSE;
}

void cmd_SetPropertyCommand::merge( NCReportDesignerCommand *c )
{
}

bool cmd_SetPropertyCommand::checkProperty()
{
	return false;
}

void cmd_SetPropertyCommand::setProperty( const WProperty& value )
{
	if ( !widget )
		return;
	QObject *o = widget;

	NCReportDesignerWidget *dw = (NCReportDesignerWidget*)o;
	dw->p = value;
	dw->updateWidget();
}

// ------------------------------------------------------------
cmd_LowerCommand::cmd_LowerCommand( const QString &name, NCReportDesignerDesignArea *da, const QWidgetList &w )
	: NCReportDesignerCommand( name, da ), widgets( w )
{
}

void cmd_LowerCommand::execute()
{
	for ( QWidget *w = widgets.first(); w; w = widgets.next() ) {
		w->lower();
		designArea()->raiseSelection( w );
	}
	designArea()->parentDocument()->setModified( TRUE );

}

void cmd_LowerCommand::unexecute()
{
	for ( QWidget *w = widgets.first(); w; w = widgets.next() ) {
		w->raise();
		designArea()->raiseSelection( w );
	}
}

// ------------------------------------------------------------

cmd_RaiseCommand::cmd_RaiseCommand( const QString &name, NCReportDesignerDesignArea *da, const QWidgetList &w )
	: NCReportDesignerCommand( name, da ), widgets( w )
{
}

void cmd_RaiseCommand::execute()
{
	for ( QWidget *w = widgets.first(); w; w = widgets.next() ) {
		w->raise();
		designArea()->raiseSelection( w );
	}
	designArea()->parentDocument()->setModified( TRUE );
}

void cmd_RaiseCommand::unexecute()
{
	for ( QWidget *w = widgets.first(); w; w = widgets.next() ) {
		w->lower();
		designArea()->raiseSelection( w );
	}
}


// ------------------------------------------------------------

cmd_PasteCommand::cmd_PasteCommand( const QString &n, NCReportDesignerDesignArea *da, const QWidgetList &w )
	: NCReportDesignerCommand( n, da ), widgets( w )
{
}

void cmd_PasteCommand::execute()
{
	for ( QWidget *w = widgets.first(); w; w = widgets.next() ) {
		w->show();
		designArea()->selectWidget( w );
		designArea()->widgets()->insert( w, w );
		//designArea()->mainWindow()->objectHierarchy()->widgetInserted( w );
	}
	designArea()->parentDocument()->setModified( TRUE );

}

void cmd_PasteCommand::unexecute()
{
	for ( QWidget *w = widgets.first(); w; w = widgets.next() ) {
		w->hide();
		designArea()->selectWidget( w, FALSE );
		designArea()->widgets()->remove( w );
		//designArea()->mainWindow()->objectHierarchy()->widgetRemoved( w );
	}
}




