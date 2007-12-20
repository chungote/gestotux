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
#include "eenviobackup.h"

#include <QFtp>
#include "preferencias.h"
#include <QFile>
#include <QDate>

EEnvioBackup::EEnvioBackup(QObject *parent)
 : QThread(parent)
{
}


EEnvioBackup::~EEnvioBackup()
{
}


void EEnvioBackup::run()
{
 preferencias *p = preferencias::getInstancia();
 if( p->value( "backup/enviado", false ).toBool() == true  )
 {
  qDebug( "El backup ya ha sido enviado... saliendo del hilo" );
  exit(0);
  return;
 }
 setTerminationEnabled();
 QFile *archivo = new QFile( p->value( "backup/archivo", QDate::currentDate().toString() ).toString() );
 if( !archivo->open( QIODevice::ReadOnly ) )
 {
  qDebug( QString( "Error al abrir el archivo de backup: %1" ).arg( p->value( "backup/archivo" ).toString() ).toLocal8Bit() );
  exit(0);
  return;
 }
 ftp = new QFtp( this );
 connect( ftp, SIGNAL( commandFinished( int, bool ) ), this, SLOT( finComando( int, bool ) ) );
 ftp->connectToHost( p->value( "ftp/host", "tranfuga.no-ip.org" ).toString(), p->value( "ftp/puerto", 21 ).toInt() );
 ftp->login();
 ftp->put( archivo, QDateTime::currentDateTime().toString( "yyyyMMddhhmmsszzz") );
 ftp->close();
 exec();
}

/*!
    \fn EEnvioBackup::finComando( int id, bool error )
 */
void EEnvioBackup::finComando( int id, bool error )
{
 if( error )
 {
  qDebug( QString( "Error: %1").arg( ftp->errorString() ).toLocal8Bit() );
  exit(0);
  return;
 }
 if( id == 4 )
 {
  qDebug( "Fin del Hilo" );
  preferencias *p = preferencias::getInstancia();
  p->setValue( "backup/enviado", true );
  p->sync();
  exit(0);
 }
}
