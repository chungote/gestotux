/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   *
 *   juiraze@yahoo.com.ar   *
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
#ifndef ACTUALIZACION_H
#define ACTUALIZACION_H

#include <QWidget>
#include "eplugin.h"

/**
	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class actualizacion : public QObject, EPlugin
{
Q_OBJECT
Q_INTERFACES(EPlugin)

public:
    static QStackedWidget *tabs();
    static QSettings *pref();
    bool inicializar( QStackedWidget *formCen, QSettings *pref );
    QList<QAction *> accionesBarra() const;
    int tipo();
    QString nombre();
    QWidgetList formsPreferencias();

private:
	QList<QAction *> _acciones;
	static QStackedWidget *_formCen;
	static QSettings *_pref;

public slots:
    void verForm();
};

#endif
