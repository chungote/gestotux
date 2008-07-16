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
#include "emysql.h"
#include <QSqlDatabase>
#include <QSqlError>
#include "preferencias.h"

EMysql::EMysql(QWidget* parent, Qt::WFlags fl)
: QDialog( parent, fl ), Ui::EMysqlBase()
{
	setupUi(this);
	preferencias *p = preferencias::getInstancia();
	LEHost->setText( p->value( "mysql/host" ).toString() );
	LEUsuario->setText( p->value( "mysql/usuario" ).toString() );
	LEBaseDatos->setText( p->value( "mysql/base", "gestotux" ).toString() );
	adjustSize();
}

EMysql::~EMysql()
{
}

void EMysql::reject()
{
  QDialog::reject();
}

void EMysql::accept()
{
  // intento conectar
  *_db = QSqlDatabase::addDatabase( "QMYSQL" );
  _db->setHostName( LEHost->text() );
  _db->setDatabaseName( LEBaseDatos->text() );
  _db->setUserName( LEUsuario->text() );
  _db->setPassword( LEContra->text() );
  if( _db->open() )
  {
   preferencias *p = preferencias::getInstancia();
   p->setValue( "mysql/base", LEBaseDatos->text() );
   p->setValue( "mysql/usuario", LEUsuario->text() );
   p->setValue( "mysql/host", LEHost->text() );
   QDialog::accept();
  }
  else
  {
   qWarning( "Ultimo error: " + _db->lastError().text().toLocal8Bit() );
   _db->removeDatabase( _db->connectionName() );
  }
}



/*!
    \fn EMysql::setDb( QSqlDatabase db )
 */
void EMysql::setDb( QSqlDatabase *db )
{
 _db = db;
}
