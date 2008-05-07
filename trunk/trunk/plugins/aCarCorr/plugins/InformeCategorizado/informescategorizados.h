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
#ifndef INFORMESCATEGORIZADOS_H
#define INFORMESCATEGORIZADOS_H

#include <QObject>
#include <QtPlugin>
#include <einformeinterface.h>

/**
	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class InformesCategorizados : public QObject, public EInformeInterface
{
Q_OBJECT
Q_INTERFACES(EInformeInterface)
public:
    QString nombre() const;
    bool inicializar(QStackedWidget* form);
    double version() const;
    void crearMenu(QMenu* m);
    bool impresionPersonalizada() const;
    void imprimir();
private:
	static QStackedWidget *_formCen;
};

#endif