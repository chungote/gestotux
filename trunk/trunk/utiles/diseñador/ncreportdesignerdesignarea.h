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
#ifndef NCREPORTDESIGNERDESIGNAREA_H
#define NCREPORTDESIGNERDESIGNAREA_H

#include "ncreportdesignercommand.h"

/*
#include <qwidget.h>
#include <qpixmap.h>
#include <qmap.h>
//#include <qhash.h>
#include <qlist.h>*/

#include <QWidget>
#include <QHash>
#include <QList>

class NCReportDesignerWindow;
class NCReportDesignerSection;
class NCReportDesignerDocument;
class NCReportDesignerWidget;
//class NCReportDesignerCommandHistory;
class QLabel;
class QObject;
class QTimer;
class Selection;
class Measurement;

class NCReportDesignerDesignArea : public QWidget
{
	Q_OBJECT
public:
	NCReportDesignerDesignArea( NCReportDesignerWindow *mw, QWidget *parent, const char* name, Qt::WFlags f = 0 );
	NCReportDesignerDesignArea( QWidget *parent,  const char* name, Qt::WFlags f = 0 );
	~NCReportDesignerDesignArea();

	enum Tools { PointerTool=0, InsertObject };

	void init();
	virtual void setMainWindow( NCReportDesignerWindow *w );

	virtual QPoint grid() const;
	virtual QPoint gridPoint( const QPoint &p );

	virtual NCReportDesignerCommandHistory* commandHistory();

	virtual void undo();
	virtual void redo();
	virtual QString copy();
	virtual void paste( const QString &cb, QWidget *parent );
	virtual void lowerWidgets();
	virtual void raiseWidgets();
	/*
	virtual void layoutHorizontal();
	virtual void layoutVertical();
	virtual void layoutHorizontalSplit();
	virtual void layoutVerticalSplit();
	virtual void layoutGrid();
	*/

	virtual void selectWidget( QObject *w, bool select = TRUE );
	virtual void selectAll();
	virtual void updateSelection( QWidget *w );
	virtual void raiseSelection( QWidget *w );
	virtual void repaintSelection( QWidget *w );
	virtual void clearSelection( bool changePropertyDisplay = TRUE );
	virtual void selectWidgets();
	bool isWidgetSelected( QObject *w );

	virtual void emitSelectionChanged();


	virtual QWidgetList widgets();
	virtual QWidgetList selectedWidgets() const;

	virtual QWidget *designerWidget( QObject *o ) const;

	virtual void handleContextMenu( QContextMenuEvent *e, QWidget *w );
	virtual void handleMousePress( QMouseEvent *e, QWidget *w );
	virtual void handleMouseRelease( QMouseEvent *e, QWidget *w );
	virtual void handleMouseDblClick( QMouseEvent *e, QWidget *w );
	virtual void handleMouseMove( QMouseEvent *e, QWidget *w );
	virtual void handleKeyPress( QKeyEvent *e, QWidget *w );
	virtual void handleKeyRelease( QKeyEvent *e, QWidget *w );

	virtual void updateUndoInfo();

	virtual NCReportDesignerWindow *mainWindow() const { return mwindow; }

	bool checkCustomWidgets();
	virtual void insertWidget( QWidget *w, bool checkName = FALSE );
	virtual void removeWidget( QWidget *w );
	virtual void deleteWidgets();
	virtual void editAdjustSize();
	virtual void editConnections();
	virtual void alignWidgets( Qt::AlignmentFlag );

	virtual void runWidgetSettingsDialog( NCReportDesignerWidget*, bool init = FALSE );

	virtual int numSelectedWidgets() const;
	virtual int numVisibleWidgets() const;

	virtual QWidget *currentWidget() const { return propertyWidget && propertyWidget->isWidgetType() ? (QWidget*)propertyWidget : 0; } // #####
	//virtual bool unify( QObject *w, QString &s, bool changeIt );

	virtual QPoint mapToForm( const QWidget* w, const QPoint&  ) const;
	virtual QLabel *sizePreview() const;
	virtual QSize sizeHint () const;

	bool isMainContainer( QObject *w ) const;
	bool isCentralWidget( QObject *w ) const;
	QWidget *mainContainer() const { return mContainer; }
	void setMainContainer( QWidget *w );

	//void paintGrid( QWidget *w, QPaintEvent *e );
	void paintGrid( QPainter& p );
	void checkGeometry( QRect &r );


	void setToolFixed() { toolFixed = TRUE; }
	void setActiveObject( QObject *o );
	void initSlots();
	void setMeasurement( Measurement* mmnt ) { m = mmnt; }
	Measurement* measurement() { return m; }
	void setParentDocument( NCReportDesignerDocument* d ) { document = d; }
	NCReportDesignerDocument* parentDocument() { return document; }
	void setParentSection( NCReportDesignerSection* s ) { section = s; }
	NCReportDesignerSection* parentSection() { return section; }

public slots:
	virtual void widgetChanged( QObject *w );
	virtual void toolChanged();
	virtual void visibilityChanged();
	//virtual void modificationChanged( bool m );

signals:
	void showProperties( QObject *w );
	void updateProperties( QObject *w );
	void undoRedoChanged( bool undoAvailable, bool redoAvailable,
							const QString &undoCmd, const QString &redoCmd );
	void selectionChanged();
protected:
	virtual void closeEvent( QCloseEvent *e );
	virtual void focusInEvent( QFocusEvent *e );
	virtual void focusOutEvent( QFocusEvent *e );
	virtual void resizeEvent( QResizeEvent *e );
	virtual void paintEvent( QPaintEvent * );
	virtual void paintFocus( QPainter*, bool focusOn );

	virtual void mousePressEvent ( QMouseEvent * e ) { handleMousePress( e, this ); }
	virtual void mouseDoubleClickEvent( QMouseEvent *e ) { handleMouseDblClick( e, this ); }
	//virtual void mouseDoubleClickEvent( QMouseEvent *e ) { handleMouseDblClick( e, mainContainer() ); }
	virtual void mouseMoveEvent( QMouseEvent *e ) { handleMouseMove( e, this ); }
	virtual void mouseReleaseEvent( QMouseEvent *e ) { handleMouseRelease( e, this ); }

	virtual void keyPressEvent( QKeyEvent *e ) { handleKeyPress( e, this ); }
	virtual void keyReleaseEvent( QKeyEvent *e ) { handleKeyRelease( e, this ); }

private:
	enum RectType { Insert, Rubber };

	void beginUnclippedPainter( bool doNot );
	void endUnclippedPainter();
	void drawConnectionLine();
	void drawSizePreview( const QPoint &pos, const QString& text );

	void insertWidget();
	void moveSelectedWidgets( int dx, int dy );

	void startRectDraw( const QPoint &p, const QPoint &global, QWidget *w, RectType t );
	void continueRectDraw( const QPoint &p, const QPoint &global, QWidget *w, RectType t );
	void endRectDraw();

	void checkSelectionsForMove( QWidget *w );

	bool allowMove( QWidget *w );

	void saveBackground();
	void restoreConnectionLine();
	void restoreRect( const QRect &rect ) ;

	void showOrderIndicators();
	void updateOrderIndicators();
	void repositionOrderIndicators();
	void hideOrderIndicators();

	QWidget *containerAt( const QPoint &pos, QWidget *notParentOf );
private slots:
	void invalidCheckedSelections();
	void updatePropertiesTimerDone();
	void showPropertiesTimerDone();
	void selectionChangedTimerDone();
	//void windowsRepaintWorkaroundTimerTimeout();

private:
	Measurement *m;
	NCReportDesignerWindow *mwindow;
	int currTool;
	bool oldRectValid, widgetPressed, drawRubber, checkedSelectionsForMove;
	bool validForBuddy;
	QRect currRect;
	QPoint rectAnchor;
	QPainter *unclippedPainter;
	QPoint sizePreviewPos;
	QPixmap sizePreviewPixmap;
	QColor color0, color1;
	NCReportDesignerSection *section;
	NCReportDesignerDocument *document;

	QList<Selection> selections;
	QHash<QWidget*,Selection*> usedSelections;
	QHash<QWidget*,QWidget*> insertedWidgets;
// 	Q3PtrDict<Selection> usedSelections;
// 	Q3PtrDict<QWidget> insertedWidgets;

	QRect widgetGeom, rubber;
	QPoint oldPressPos, origPressPos;
	NCReportDesignerCommandHistory commands; //CommandHistory commands;
	QMap<QWidget*, QPoint> moving;
	QWidget *insertParent;
	QObject *propertyWidget;
	QLabel *sizePreviewLabel;
	QTimer *checkSelectionsTimer;
	bool propShowBlocked;
	QTimer* updatePropertiesTimer, *showPropertiesTimer, *selectionChangedTimer, *windowsRepaintWorkaroundTimer;
	QPoint startPos, currentPos;
	QWidget *startWidget, *endWidget;
	QPixmap *buffer;
	//QPtrList<OrderIndicator> orderIndicators;
	//QWidgetList orderedWidgets;
	//QWidgetList stackedWidgets;
	QWidget *mContainer;
	bool pixInline, pixProject;
	QString pixLoader;
	bool toolFixed;
	//QPtrList<QAction> actions;
	//Project *proj;
	//DesignerFormWindow *iface;
	QWidget* targetContainer;
	QPalette restorePalette;
	bool hadOwnPalette;
	int defSpacing, defMargin;
	QString spacFunction, margFunction;
	bool hasLayoutFunc;
	bool fake;
};


#endif
