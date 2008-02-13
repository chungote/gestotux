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
#include <QObject>
#include <QtPlugin>
#include <QList>
#include <QAction>
#include "einfoprogramainterface.h"

class HiComp : public QObject, public EInfoProgramaInterface
{
 Q_OBJECT
 Q_INTERFACES(EInfoProgramaInterface)

public:
    QString nombrePrograma() const;
    QIcon iconoPrograma()  const;
    QList<QAction *> accionesBarra() const;
    bool inicializar( QStackedWidget *formCen, QSettings *pref );
    static QStackedWidget *tabs();
    static QSettings *pref();
    QString directorioBackup() const;
    QString directorioActualizaciones() const;
    QWidgetList formsPreferencias();

private:
    QList<QAction *> _acciones;
    static QStackedWidget *_formCen;
    static QSettings *_pref;

public slots:
    void verRecibosAnteriores();
protected slots:
    void nuevoRecibo();
};

#endif
