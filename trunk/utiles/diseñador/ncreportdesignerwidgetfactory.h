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
#ifndef NCREPORTDESIGNERWIDGETFACTORY_H
#define NCREPORTDESIGNERWIDGETFACTORY_H

/**
	@author Norbert Szabo <nszabo@helta.hu>
*/

#include <qvariant.h>


class QWidget;
class QDomElement;

class NCReportDesignerWidgetFactory
{
public:
    //NCReportDesignerWidgetFactory();
    //~NCReportDesignerWidgetFactory();
	enum RWType { Label, Field, Line, Rectangle, Circle, Image };

	static QWidget *create( int id, QWidget *parent, const char *name = 0,
							bool init = TRUE, const QRect *rect = 0 );
	static QWidget *create( const QDomElement &e, QWidget *parent, const char *name = 0,
							bool init = TRUE, const QRect *rect = 0 );

	//static const char* classNameOf( QObject* o );
	//static bool hasSpecialEditor( int id, QObject *editorWidget );
	//static bool hasItems( int id, QObject *editorWidget );
	//static void editWidget( int id, QWidget *parent, QWidget *editWidget, FormWindow *fw );

	static QVariant defaultValue( QObject *w, const QString &propName );
	//static QString defaultCurrentItem( QObject *w, const QString &propName );

	//static QVariant property( QObject *w, const char *name );
	static void saveDefaultProperties( QObject *w, int id );
	static void saveChangedProperties( QObject *w, int id );

	static QString defaultSignal( QObject *w );

private:
	static QWidget *createWidget( const QString &className, QWidget *parent, const char *name, bool init,
									const QRect *r = 0 );

	static QString className( int id );
	static QString className( const QString& tagname );
//@todo static QGuardedPtr<QObject> *lastPassiveInteractor;
	static bool lastWasAPassiveInteractor;
};

#endif
