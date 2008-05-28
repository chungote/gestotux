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
#ifndef EVISORINFORME_H
#define EVISORINFORME_H

#include "../../src/eplugin.h"
#include <QObject>
class QMenu;
class QAction;
class QPrintPreviewWidget;
class QAction;

/**
Clase que permite ver un informe generado.

	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class EVisorInforme : public QObject, public EPlugin
{
Q_OBJECT
Q_INTERFACES( EPlugin )
public:
    QList<QAction *> accionesBarra() const;
    QString nombre() const;
    QWidgetList formsPreferencias();
    bool inicializar(QStackedWidget* formCen, QSettings* pref);
    bool verificarTablas();
    double version() const;
    int tipo() const;
    void crearMenu(QMenuBar* m);
    static QStackedWidget *tabs();
    static QSettings *pref();
    QPrinter * crearVisor();

private:
    static QStackedWidget *_formCen;
    static QSettings *_pref;
    QMenu *_menu;
    QPrintPreviewWidget *formulario;

	QAction *ActAjustarAVista;
	QAction *ActAjustarAAncho;
	QAction *ActImprimir;
	QAction *ActAgrandarZoom;
	QAction *ActDisminuirZoom;
	
};

#endif
