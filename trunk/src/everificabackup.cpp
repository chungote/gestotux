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
#include "everificabackup.h"
#include "preferencias.h"
#include <QDate>
#include <QIcon>
#include <QLabel>
#include <QTimer>

EVerificaBackup::EVerificaBackup(QWidget *parent)
 : QPushButton(parent)
{
 this->setToolTip( "Verificación de Backups" );
 tiempo = new QTimer(this);
 tiempo->setInterval( 100000 );
 connect( tiempo, SIGNAL( timeout() ), this, SLOT( verificar() ) );
 tiempo->start();
 this->setFlat(true);
}


EVerificaBackup::~EVerificaBackup()
{
}



/*!
    \fn EVerificaBackup::verificar()
 */
void EVerificaBackup::verificar()
{
 preferencias *p = preferencias::getInstancia();
 p->beginGroup( "backup" );
 QDate fecha = p->value( "fecha", QDate( 1900, 1, 1 ) ).toDate();
 qDebug( qPrintable( "Fecha=" +  fecha.toString("dd/MM/yyyy" ) ) );
 p->endGroup();
 int dif = fecha.daysTo( QDate::currentDate() );
 if( dif > 15 )
 {
  show();
  QIcon icono( ":/imagenes/aviso.png" );
  this->setIcon( icono );
  this->setIconSize( QSize( 16, 16 ) );
  connect( this, SIGNAL( clicked() ), this, SIGNAL( abrirBackups()) );
  this->setToolTip( "El ultimo backup fue echo hace mas de 15 dias.\n Haga click aqui para generar un backup" );
 }
 else
 {
  hide();
 }
}


