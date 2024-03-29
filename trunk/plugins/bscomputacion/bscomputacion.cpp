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
#include <QAction>
#include <QSqlDatabase>

#include "bscomputacion.h"
#include "EReporte.h"

bool BSComputacion::inicializar()
{
 Q_INIT_RESOURCE(bscomputacion);
 return true;
}

bool BSComputacion::verificarTablas( QStringList /*tablas*/ )
{ return true; }

double BSComputacion::version() const
{ return 0.21; }

int BSComputacion::tipo() const
{
 return EPlugin::info;
}

QList< QActionGroup * > BSComputacion::accionesBarra()
{ return QList<QActionGroup*>(); }

QString BSComputacion::nombre() const
{ return "bscomputacion"; }

QWidgetList BSComputacion::formsPreferencias()
{ return QWidgetList(); }

void BSComputacion::crearMenu( QMenuBar* /*m*/ )
{}

void BSComputacion::crearToolBar(QToolBar* /*t*/)
{}

void BSComputacion::seCierraGestotux()
{ Q_CLEANUP_RESOURCE(bscomputacion); }

QImage BSComputacion::imagenPrograma() const
{ return QImage( ":/imagenes/logoBS.png" ); }

void BSComputacion::reporteParametros(int tipo, QString &nombre, ParameterList &parametros)
{
   /* switch( tipo ) {
        case EReporte::Factura:
        { return "Factura-BS"; break; }
        case EReporte::Recibo:
        { return "Recibo-BS"; break; }
        case EReporte::Presupuesto:
        { return "Presupuesto-BS"; break; }
        case EReporte::AnulacionFactura:
        { return "AnulacionFactura"; break; }
        case EReporte::Remito:
        { return "Remito"; break; }
        default: { return ""; break; }
    }*/
}

QString BSComputacion::nombrePrograma() const { return "BSComputacion"; }

QIcon BSComputacion::iconoPrograma() const
{ return QIcon( ":/imagenes/iconoBS.png" ); }

QString BSComputacion::directorioBackup() const
{ return "bscomputacion"; }

QString BSComputacion::directorioActualizaciones() const
{ return "bscomputacion"; }

QString BSComputacion::empresa() const
{ return "BSComputacion"; }

QString BSComputacion::companeros()
{ return ""; }


bool BSComputacion::publicidad()
{ return false; }

QString BSComputacion::reporte( int tipo )
{
    switch( tipo ) {
        case EReporte::Factura:
        { return "Factura-BS"; break; }
        case EReporte::Recibo:
        { return "Recibo-BS"; break; }
        case EReporte::Presupuesto:
        { return "Presupuesto-BS"; break; }
        case EReporte::AnulacionFactura:
        { return "AnulacionFactura"; break; }
        case EReporte::Remito:
        { return "Remito"; break; }
        default: { return ""; break; }
    }
}

Q_EXPORT_PLUGIN2( bscomputacion, BSComputacion )
