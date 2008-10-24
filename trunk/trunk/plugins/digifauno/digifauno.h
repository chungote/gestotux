/***************************************************************************
 *   Copyright (C) 2006 by Esteban Zeller & Daniel Sequeira		   *
 *   juiraze@yahoo.com.ar  - daniels@hotmail.com			   *
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

#ifndef DIGIFAUNO_H
#define DIGIFAUNO_H

#include <QtPlugin>
#include <QObject>
#include "../../src/einfoprogramainterface.h"
#include "../../src/eplugin.h"

/*!
 * \class DigiFauno
 * \short Ventana principal
 *
 * Clase que maneja la ventana principal del programa
 */

class DigiFauno : public QObject, public EInfoProgramaInterface, public EPlugin
{
      Q_OBJECT
      Q_INTERFACES( EPlugin EInfoProgramaInterface )
public:
    bool inicializar( QSettings *pref );
    QString nombre() const;
    double version() const;
    bool verificarTablas();
    QList<QActionGroup *> accionesBarra();
    QString directorioActualizaciones() const;
    QString directorioBackup() const;
    QString nombrePrograma() const;
    QWidgetList formsPreferencias();
    void crearMenu( QMenuBar* m );
    QIcon iconoPrograma() const;
    QString empresa() const;
    QString companeros();
    int tipo() const;
    void crearToolBar( QToolBar *t );
    bool publicidad() { return true; }

signals:
    void agregarVentana( QWidget *ventana );

private:
    QAction *ActSalir;
    QAction *ActPreferencias;
    QAction *ActAcerca;
    QAction *ActAyuda;
    QAction *separatorAct;
    QAction *ActBackup;
    QAction *ActDuenos;
    QAction *ActProveedores;
    QAction *ActMascotas;
    QAction *ActGastos;
    QAction *ActPeluqueria;
    QAction *ActVentas;
    QAction *ActNuevoServicio;
    QAction *ActAgregarVentas;
    QAction *ActAgregarCompra;
    QAction *ActAgregarMascota;
    QAction *ActAgregarGasto;
    QAction *ActResumenDiario;
    QAction *ActResumenMensual;
    QAction *ActResumenAnual;
    QAction *ActResumenEntreFechas;

   QActionGroup *peluqueria;
   QActionGroup *ventas;
   QActionGroup *compras;
   QActionGroup *resumen;

private:
    QList<QAction *> _acciones;
    static QSettings *_pref;

public slots:
    void agregarVenta();
    void proveedores();
    void duenos();
    void agregarMascota();
    void agregarServicioPeluqueria();
    void mascotas();
    void resumenDiario();
    void agregarCompra();
    void resumenMensual();
    void resumenAnual();
    void agregarGasto();
    void ver_gastos();
    void resumen_semanal();
    void ver_peluqueria();
    void ver_compras();
    void resumenEntreFechas();


};

#endif
