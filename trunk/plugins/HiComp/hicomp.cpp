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
#include "hicomp.h"
#include "vrecibos.h"
#include "fprefrecibos.h"
#include "formagregarrecibo.h"

#include <QString>
#include <QIcon>
#include <QAction>
#include <QList>
#include <QTabWidget>
#include <QWidget>

QTabWidget *HiComp::_formCen = 0;
QSettings *HiComp::_pref = 0;

QString HiComp::nombrePrograma()  const
{
 return "HiComp Computacion - 0.1";
}

Q_EXPORT_PLUGIN2(hicomp, HiComp )

QIcon HiComp::iconoPrograma() const
{
 return QIcon( ":/imagenes/icono.png" );
}

/*!
    \fn HiComp::accionesBarra()
 */
QList<QAction *> HiComp::accionesBarra() const
{
 return _acciones;
}


bool HiComp::inicializar( QTabWidget *formCen, QSettings *pref )
{
 _formCen = formCen;
 _pref = pref;
 // Genero las acciones y la lista
 QAction *ActRecibos = new QAction( "Ver Recibos", this );
 ActRecibos->setToolTip( "Ver los recibos emitidos" );
 ActRecibos->setIcon( QIcon( ":/imagenes/anteriores.png" ) );
 connect( ActRecibos, SIGNAL( triggered() ), this, SLOT( verRecibosAnteriores() ) );

 QAction *ActNuevoRecibo = new QAction( "Nuevo Recibo", this );
 ActNuevoRecibo->setToolTip( "Crear un nuevo recibo" );
 ActNuevoRecibo->setIcon( QIcon( ":/imagenes/nuevo.png" ) );
 connect( ActNuevoRecibo, SIGNAL( triggered() ), this, SLOT( nuevoRecibo() ) );

 _acciones.append( ActNuevoRecibo );
 _acciones.append( ActRecibos );

}


void HiComp::verRecibosAnteriores()
{
 VRecibos *f = new VRecibos();
 _formCen->addTab( f, f->windowIcon(), f->objectName()  );
}


QTabWidget *HiComp::tabs()
{
 return _formCen;
}

QSettings *HiComp::pref()
{
 return _pref;
}

QString HiComp::directorioBackup() const
{
  return "HiComp";
}


QString HiComp::directorioActualizaciones() const
{
 return "";
}


/*!
    \fn HiComp::formsPreferencias()
 */
QWidgetList HiComp::formsPreferencias()
{
 QWidgetList lista;
 lista.append( new FPrefRecibos() );
 return lista;
}


/*!
    \fn HiComp::nuevoRecibo()
 */
void HiComp::nuevoRecibo()
{
 FormAgregarRecibo *f = new FormAgregarRecibo();
 _formCen->addTab( f, f->windowIcon(), f->objectName()  );
}
