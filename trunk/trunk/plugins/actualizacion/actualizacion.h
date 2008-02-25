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
#include "eactualizacion.h"
#include <QMenuBar>
#include <QString>
#include <QHash>

/**
	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class actualizacion : public QObject, EPlugin, EActualizacion
{
Q_OBJECT
Q_INTERFACES(EPlugin EActualizacion)

public:
    static QStackedWidget *tabs();
    static QSettings *pref();
    bool inicializar( QStackedWidget *formCen, QSettings *pref );
    QList<QAction *> accionesBarra() const;
    int tipo() const;
    QString nombre() const;
    QWidgetList formsPreferencias();
    void crearMenu( QMenuBar *m );
    void verificarTablas();
    double version() const;
    void plugs( QHash<QString, EPlugin *> *plugs );
    void versionPrograma( double ver );

private:
	QHash<QString, EPlugin *> *_plugs;
	double _versionGeneral;
	QList<QAction *> _acciones;
	static QStackedWidget *_formCen;
	static QSettings *_pref;
	QAction *ActActualizar;

public slots:
    void verForm();
};

#endif
