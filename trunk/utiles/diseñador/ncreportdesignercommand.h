/***************************************************************************
 *   Copyright (C) 2006 by Szabo Norbert   *
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
#ifndef NCREPORTDESIGNERCOMMAND_H
#define NCREPORTDESIGNERCOMMAND_H

#include "ncreportdesignerwidget.h"

#include <QString>
#include <QVariant>
#include <QObject>
#include <QApplication>
#include <QWidget>
#include <QMap>
#include <QPointer>

#include <QRect>
#include <QListView>
//#include <qiconset.h>

//class Command;
class QWidget;
class NCReportDesignerDesignArea;
class PropertyEditor;
class QListBox;
class QIconView;
class QTable;
class QAction;
class QDesignerToolBar;
class QMainWindow;
class QTextEdit;
struct LanguageInterface;
class QToolBox;



class MenuBarEditor;
class MenuBarEditorItem;
class PopupMenuEditor;
class PopupMenuEditorItem;
class ActionEditor;
class NCReportDesignerDesignArea;

class NCReportDesignerCommand // : public Qt
{
public:
	NCReportDesignerCommand( const QString &n, NCReportDesignerDesignArea *da );
	virtual ~NCReportDesignerCommand();

    enum Type { Resize,	Insert,	Move, Delete, SetProperty, Macro, Lower, Raise, Paste, ChangeOrder };

    QString name() const;

    virtual void execute() = 0;
    virtual void unexecute() = 0;
    virtual Type type() const = 0;
	virtual void merge( NCReportDesignerCommand *c );
	virtual bool canMerge( NCReportDesignerCommand *c );

	NCReportDesignerDesignArea *designArea() const;
private:
    QString cmdName;
	NCReportDesignerDesignArea *dArea;

};

class NCReportDesignerCommandHistory : public QObject
{
    Q_OBJECT

public:
	NCReportDesignerCommandHistory( int s );

    void addCommand( NCReportDesignerCommand *cmd, bool tryCompress = FALSE );
    void undo();
    void redo();

    void emitUndoRedo();

    void setModified( bool m );
    bool isModified() const;

public slots:
    void checkCompressedCommand();

signals:
    void undoRedoChanged( bool undoAvailable, bool redoAvailable, const QString &undoCmd, const QString &redoCmd );
    void modificationChanged( bool m );

private:
	QList<NCReportDesignerCommand *> history;
    int current, steps;
    bool modified;
    int savedAt;
	NCReportDesignerCommand *compressedCommand;

};

class cmd_ResizeCommand : public NCReportDesignerCommand
{
public:
	cmd_ResizeCommand( const QString &n, NCReportDesignerDesignArea *da, QWidget *w, const QRect &oldr, const QRect &nr );

    void execute();
    void unexecute();
    Type type() const { return Resize; }

private:
    QWidget *widget;
    QRect oldRect, newRect;

};

class cmd_InsertCommand : public NCReportDesignerCommand
{
public:
	cmd_InsertCommand( const QString &n, NCReportDesignerDesignArea *da, QWidget *w, const QRect &g );

    void execute();
    void unexecute();
    Type type() const { return Insert; }

private:
    QWidget *widget;
    QRect geometry;

};

class cmd_MoveCommand : public NCReportDesignerCommand
{
public:
	cmd_MoveCommand( const QString &n, NCReportDesignerDesignArea *da,
		 const QWidgetList &w,
		 const QList<QPoint> op,
		 const QList<QPoint> np,
		 QWidget *opr, QWidget *npr );
    void execute();
    void unexecute();
    Type type() const { return Move; }
    void merge( NCReportDesignerCommand *c );
    bool canMerge( NCReportDesignerCommand *c );

private:
    QWidgetList widgets;
    QList<QPoint> oldPos, newPos;
    QWidget *oldParent, *newParent;

};

class cmd_DeleteCommand : public NCReportDesignerCommand
{
public:
	cmd_DeleteCommand( const QString &n, NCReportDesignerDesignArea *da,
		   const QWidgetList &w );
    void execute();
    void unexecute();
    Type type() const { return Delete; }

private:
    QWidgetList widgets;
    //QMap< QWidget*, QValueList<MetaDataBase::Connection> > connections;

};

class cmd_SetPropertyCommand : public NCReportDesignerCommand
{
public:
	cmd_SetPropertyCommand( const QString &n, NCReportDesignerDesignArea *da,
			QObject *w, const WProperty &op, const WProperty &np, bool reset = FALSE );

    void execute();
    void unexecute();
    Type type() const { return SetProperty; }
    void merge( NCReportDesignerCommand *c );
    bool canMerge( NCReportDesignerCommand *c );
    bool checkProperty();

private:
	void setProperty( const WProperty &v );
    QPointer<QObject> widget;
    QString propName;
	WProperty oldValue, newValue;
    bool wasChanged;
    bool isResetCommand;

};



class cmd_LowerCommand : public NCReportDesignerCommand
{
public:
	cmd_LowerCommand( const QString &name, NCReportDesignerDesignArea *da, const QWidgetList &w );

    void execute();
    void unexecute();
    Type type() const { return Lower; }

private:
    QWidgetList widgets;

};

class cmd_RaiseCommand : public NCReportDesignerCommand
{
public:
	cmd_RaiseCommand( const QString &name, NCReportDesignerDesignArea *da, const QWidgetList &w );

    void execute();
    void unexecute();
    Type type() const { return Raise; }

private:
    QWidgetList widgets;

};

class cmd_PasteCommand : public NCReportDesignerCommand
{
public:
	cmd_PasteCommand( const QString &n, NCReportDesignerDesignArea *da, const QWidgetList &w );

    void execute();
    void unexecute();
    Type type() const { return Paste; }

private:
    QWidgetList widgets;

};

class cmd_ChangeOrderCommand : public NCReportDesignerCommand
{
public:
	cmd_ChangeOrderCommand( const QString &n, NCReportDesignerDesignArea *da, const QWidgetList &ol, const QWidgetList &nl );

    void execute();
    void unexecute();
    Type type() const { return ChangeOrder; }
    void merge( NCReportDesignerCommand *c );
    bool canMerge( NCReportDesignerCommand *c );

private:
    QWidgetList oldOrder, newOrder;

};


#endif
