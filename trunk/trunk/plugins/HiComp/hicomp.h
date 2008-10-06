
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
#ifndef HICOMP_H
#define HICOMP_H

class QString;
class QStackedWidget;
class QMenuBar;
#include <QObject>
#include <QtPlugin>
#include <QList>
#include <QAction>
#include "../../src/einfoprogramainterface.h"
#include "../../src/eplugin.h"

class HiComp : public QObject, EInfoProgramaInterface, EPlugin
{
 Q_OBJECT
 Q_INTERFACES(EInfoProgramaInterface EPlugin)

public:
    QString nombrePrograma() const;
    QIcon iconoPrograma()  const;
    QList<QActionGroup *> accionesBarra();
    bool inicializar( QSettings *pref );
    static QSettings *pref();
    QString directorioBackup() const;
    QString directorioActualizaciones() const;
    QWidgetList formsPreferencias();
    QString nombre() const;
    int tipo() const;
    void crearMenu( QMenuBar *m );
    bool verificarTablas();
    double version() const;
    QString empresa() const;
    QString companeros();
    void crearToolBar( QToolBar *t );

private:
    QList<QAction *> _acciones;
    static QSettings *_pref;

     QAction *ActNuevoRecibo;
     QAction *ActRecibos;

public slots:
    void verRecibosAnteriores();
    void nuevoRecibo();

signals:
	void agregarVentana( QWidget *v );
};

#endif
