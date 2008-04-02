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
#ifndef ADMINCARCORR_H
#define ADMINCARCORR_H

#include <QtPlugin>
#include <eplugin.h>
#include <einfoprogramainterface.h>
#include <einformeinterface.h>
#include <QPluginLoader>

/**
Plugin principal

	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class AdminCarCorr : public QObject, EPlugin, EInfoProgramaInterface
{
 Q_OBJECT
 Q_INTERFACES(EPlugin EInfoProgramaInterface)
public:
    QIcon iconoPrograma() const;
    QString directorioActualizaciones() const;
    QString directorioBackup() const;
    QString nombrePrograma() const;
    QList< QAction * > accionesBarra() const;
    QString nombre() const;
    QWidgetList formsPreferencias();
    bool inicializar(QStackedWidget* formCen, QSettings* pref);
    bool verificarTablas();
    double version() const;
    int tipo() const;
    void crearMenu(QMenuBar* m);
    QList<EInformeInterface *> plugins();

private:
    QList<QAction *> _acciones;
    static QStackedWidget *_formCen;
    static QSettings *_pref;

	QAction *ActEstablecimiento;
	QAction *ActNuevoEstablecimiento;
	QAction *ActCategoria;

	QAction *ActAgregarCompra;
	QAction *ActAgregarVenta;
	QAction *ActAgregarMudanza;

	static QHash<QString, EInformeInterface *> *_plugins;
	QPluginLoader *loader;

protected slots:
    void verCategorias();
    void verEstablecimientos();
    void agregarCompra();
    void hacerMovimiento();
    void hacerVenta();
    void hacerMudanza();

private:
    void cargarPluginsInformes();
};

#endif
