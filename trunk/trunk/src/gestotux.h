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
#ifndef GESTOTUX_H
#define GESTOTUX_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QSystemTrayIcon>
#include <QDir>
#include <QPluginLoader>
#include "formulariocentral.h"

class QAction;
class QMenu;
class barraAbajo;
class barraLateral;
class QToolBar;
class EInfoProgramaInterface;

class gestotux:public QMainWindow
{
      Q_OBJECT
public:
      gestotux();
      ~gestotux();
      void inicializar();
      static FormularioCentral *formCentral;
      static EInfoProgramaInterface *_plugin;
      static EInfoProgramaInterface *plugin();
      static FormularioCentral *formCen();
      static QToolBar *barraAcciones();
      static QToolBar *_barraAcciones;

protected:
      void closeEvent(QCloseEvent *event);

protected slots:
    void salir();
    void acerca();

private:
      void createActions();
      void createMenus();
      void createStatusBar();
      void createToolBar();
      void crearReloj();
      void bandeja_sistema();

      barraLateral *barra;
      barraAbajo *barraA;

      QToolBar *tb;


      QMenu *fileMenu;
      QMenu *editMenu;
      QMenu *helpMenu;

      QAction *ActClientes;
//       QAction *ActRecibosAnteriores;
      QAction *exitAct;
      QAction *acercade;
      QAction *ActCerrar;
      QAction *ActPdf;
      QAction *ActImprimir;
//       QAction *ActNuevoRecibo;
      QAction *ActPreferencias;
      QAction *ActBackup;

      QSystemTrayIcon * iconoBandeja;

public slots:
    void verClientes();
//     void verRecibos();
//     void nuevoRecibo();
    void verPreferencias();
    void verBackup();

private slots:
    void ocultar_mostrar( QSystemTrayIcon::ActivationReason razon );

private:
    bool cargarPlugins();
    QDir pluginsDir;
    QPluginLoader loader;
};

#endif