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
#include "email.h"

#include "formprefemail.h"
#include "eservidoremail.h"
#include "smtp.h"
#include "eemail.h"

#include <QSqlDatabase>
#include <QLabel>

bool Email::inicializar()
{
 // Iniciailizo el hilo de ejecucion que se conecta al servidor
 EServidorEmail *datosServer = new EServidorEmail();

 enviador = new Smtp(	datosServer->usuario(),
                        datosServer->password(),
                        datosServer->direccion(),
                        this,
                        QSqlDatabase::cloneDatabase( QSqlDatabase::database(), "correo" ) );
 delete datosServer;
 // La cola la mantiene el mismo objecto
 _etiqueta = new QLabel();
 // Conecto las señales para cambiar la etiqueta de estado
 connect( enviador, SIGNAL( status( const QString& ) ), this, SLOT( cambioEstado( const QString& ) ) );
 connect( EEmail::instancia(), SIGNAL( enviar( Mail * ) ), enviador, SLOT( queueMail( Mail * ) ) );
 return true;
}

bool Email::verificarTablas()
{
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "servidores_email" ) )
 { qWarning( "Error al buscar la tabla servidores_email" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "emails" ) )
 { qWarning( "Error al buscar la tabla emails" ); return false; }
 return true;
}

double Email::version() const
{
 return 0.1;
}

int Email::tipo() const
{
 return EPlugin::email;
}

QList< QActionGroup * > Email::accionesBarra()
{
 return QList<QActionGroup *>();
}

QString Email::nombre() const
{
 return "email";
}

QWidgetList Email::formsPreferencias()
{
 QWidgetList lista;
 lista.append( new FormPrefEmail() );
 return lista;
}

void Email::crearMenu(QMenuBar* m)
{}

void Email::crearToolBar(QToolBar* t)
{}

/*!
    \fn Email::seCierraGestotux()
 */
void Email::seCierraGestotux()
{
 disconnect( enviador, SIGNAL( status( const QString& ) ), this, SLOT( cambioEstado( const QString& ) ) );
 // matar el hilo de ejecucion....
 enviador->terminarEjecucion();
 enviador->terminate();
 qDebug( "Cerrado plugin email" );
 return;
}

/*!
    \fn Email::cambioEstado( const QString &texto )
    Cambia la etiqueta de la barra de estado donde se indica el estado de envio de emails.
    @param texto Texto a colocar en la etiqueta
 */
void Email::cambioEstado( const QString &texto )
{
 if( _etiqueta->isVisible() )
 {
  _etiqueta->setText( texto );
  _etiqueta->adjustSize();
 }
}

Q_EXPORT_PLUGIN2( email, Email );


/*!
    \fn Email::statusBarWidget()
    Devuelve la etiqueta que se va a colocar en la barra de estado al enviar emails.
    @return QLabel para agregar en la barra de estado.
 */
QWidget * Email::statusBarWidget()
{
 return _etiqueta;
}
