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

#include "FormPantallaInicial.h"
#include "eregistroplugins.h"
#include <QPaintEngine>
#include "credencialesplugin.h"

FormPantallaInicial::FormPantallaInicial(QWidget *parent) :
    EVentana(parent)
{
    setupUi(this);
    this->setObjectName( "inicio" );
    this->setWindowTitle( "Inicio" );
    this->setWindowIcon( QIcon( ":/imagenes/inicio.png" ) );

    // Seteo los iconos
    // Generales
/*    TBBackup->setIcon( QIcon( ":/imagenes/backup.png" ) );
    connect( TBBackup, SIGNAL( clicked() ), this, SLOT( backup() ) );

    TBPreferencias->setIcon( QIcon( ":/imagenes/configure.png" ) );
    connect( TBPreferencias, SIGNAL( clicked() ), this, SLOT( preferencias() ) );*/

    connect( TBCredenciales, SIGNAL(clicked()), this, SLOT(verCredenciales()));
    connect( TBNuevaCredencial, SIGNAL(clicked()), this, SLOT(crearcredencial()));
    connect( TBEquipos, SIGNAL(clicked()), this, SLOT(verEquipos()));

}

void FormPantallaInicial::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}


#include "DCredencial.h"
#include <QInputDialog>
#include <QSqlRecord>
#include "mequipos.h"
void FormPantallaInicial::crearcredencial()
{
    QStringList lista; QList<int> ids;
    MEquipos *m = new MEquipos();
    m->select();
    for( int i = 0; i<m->rowCount(); i++ ) {
        lista.append( m->record(i).value(1).toString() );
        ids.append( m->record(i).value(0).toInt() );
    }
    delete m;
    bool ok = false;
    QString equipo = QInputDialog::getItem( 0, "Elija el equipo contrario", "Equipo", lista, 0, false, &ok );
    if( ok ) {
        DCredencial *d = new DCredencial();
        emit agregarVentana( d );
        d->setearEquipo( ids.at( lista.indexOf( equipo ) ), equipo );
    }
}

#include "vequipos.h"
void FormPantallaInicial::verEquipos()
{ emit agregarVentana( new VEquipos() ); }

#include "vcredenciales.h"
void FormPantallaInicial::verCredenciales()
{ emit agregarVentana( new VCredenciales() ); }
