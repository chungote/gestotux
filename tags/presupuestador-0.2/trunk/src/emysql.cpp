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
#include <QProgressBar>
#include <QTimer>
#include <QMessageBox>
#include "preferencias.h"

EMysql::EMysql(QWidget* parent, Qt::WFlags fl)
: QDialog( parent, fl ), Ui::EMysqlBase()
{
	setupUi(this);
	preferencias *p = preferencias::getInstancia();
	LEUsuario->setText( p->value( "mysql/usuario" ).toString() );
	if( p->contains( "mysql/contra" ) )
	{
		LEContra->setText( p->value( "mysql/contra" ).toString() );
	}
	adjustSize();
	this->setWindowTitle( "Conexion a gestotux");
	this->setWindowIcon( QIcon(":/imagenes/mysql.png" ) );
	LEContra->setEchoMode( QLineEdit::Password );
	connect( PBInterna, SIGNAL( clicked() ), this, SLOT( dbinterna() ) );
	connect( PBConectar, SIGNAL( clicked() ), this, SLOT( accept() ) );
	PBConectar->setDefault( true );
}

EMysql::~EMysql()
{
}

void EMysql::reject()
{
  this->done( Cancelado );
}

void EMysql::accept()
{
  // intento conectar
  preferencias *p = preferencias::getInstancia();
  *_db = QSqlDatabase::addDatabase( "QMYSQL" );
  _db->setHostName( p->value( "mysql/host", "localhost" ).toString() );
  _db->setPort( p->value( "mysql/puerto", 3306).toInt() );
  _db->setDatabaseName( p->value( "mysql/base", "gestotux" ).toString() );
  _db->setUserName( LEUsuario->text() );
  _db->setPassword( LEContra->text() );
  if( _db->open() )
  {
   qDebug( "Conectado con mysql" );
   this->done( Conectado );
  }
  else
  {
   switch( _db->lastError().type() )
   {
	case QSqlError::ConnectionError:
	{
		QMessageBox::information( this, "Error de conexión", "No se ha podido conectar a la base de datos. Verifique que se encuentre disponible y que su usuario y contraseña sean correctas" );
 		_db->removeDatabase( _db->connectionName() );
		break;
	}
	default:
	{
		qDebug( "Error de conección" );
		qWarning( qPrintable( "Ultimo error: -> " + QString::number( _db->lastError().number() ) + "<- - " + _db->lastError().text() ) );
		 _db->removeDatabase( _db->connectionName() );
	}
    }
  }
}



/*!
    \fn EMysql::setDb( QSqlDatabase *db )
 */
void EMysql::setDb( QSqlDatabase *db )
{
 _db = db;
}

/*!
    \fn EMysql::dbinterna()
 */
void EMysql::dbinterna()
{
 this->done( Interna );
}
