/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   				   *
 *   juiraze@yahoo.com.ar   						   *
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
#ifndef CUENTACORRIENTEPLUGIN_H
#define CUENTACORRIENTEPLUGIN_H

#include <QObject>
#include "eplugin.h"
#include <QtPlugin>

/**
 * \brief Plugin de cuentas corriente
 *
 * Plugin que tiene el control de las cuentas corrientes en el programa
 *
 *	@author Esteban Zeller <juiraze@yahoo.com.ar>
 */
class CuentaCorrientePlugin : public QObject, public EPlugin
{
Q_OBJECT
Q_INTERFACES( EPlugin )
public:
    bool inicializar();
    bool verificarTablas();
    double version() const;
    int tipo() const;
    QList< QActionGroup * > accionesBarra();
    QString nombre() const;
    QWidgetList formsPreferencias();
    void crearMenu(QMenuBar* m);
    void crearToolBar(QToolBar* t);
    QAction *botonPantallaInicial() { return ActCuentasCorrientes; }

signals:
    void agregarVentana(QWidget* v);
        void agregarDockWidget(Qt::DockWidgetArea area, QDockWidget *ventana);

public slots:
    void seCierraGestotux();
    void verCuentasCorrientes();

private:
    QAction *ActCuentasCorrientes;

};

#endif
