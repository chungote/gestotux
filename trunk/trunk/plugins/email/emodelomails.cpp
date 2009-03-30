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
#include "emodelomails.h"
#include "mail.h"
#include "eservidoremail.h"
#include "eemail.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>

EModeloMails::EModeloMails(QObject *parent)
 : QSqlTableModel(parent)
{
 setTable( "emails" );
 setHeaderData( 1, Qt::Horizontal, "#ID" );
 /// @todo ver que parte de los emails se debe guardar
 this->setEditStrategy( QSqlTableModel::OnManualSubmit );
}


EModeloMails::~EModeloMails()
{
}


/*!
    \fn EModeloMails::takeFirst()
 */
Mail * EModeloMails::takeFirst()
{
    /// @todo carga el primer email de la lista y lo elimina de la cola
 this->select();
 QSqlRecord primero = this->record( 0 );
 Mail *mail = EEmail::instancia()->email();
 mail->setIdentificadorUnico( QUuid( primero.value("id_unico" ).toString() ) );
 EServidorEmail servidor;
 mail->setHeader( servidor.de(),
			primero.value( "para" ).toString(),
			primero.value( "bcc" ).toString(),
			primero.value( "cc" ).toString(),
			primero.value( "asunto" ).toString()
		);
 mail->setMessageBody( primero.value( "cuerpo" ).toString() );
 mail->setContentType( primero.value( "content-type" ).toString() );
 this->removeRow( 0 );
 this->submit();
 return mail;
}


/*!
    \fn EModeloMails::size()
 */
int EModeloMails::size()
{
 QSqlQuery cola( "SELECT COUNT( id_email ) FROM emails" );
 if( cola.next() )
 {
  return cola.record().value(0).toInt();
 }
 else
 {
  qDebug( "Error al contar los emails en la cola" );
  qDebug( qPrintable( cola.lastError().text() ) );
  return 0;
 }
}


/*!
    \fn EModeloMails::emailEnviado( Mail *mail )
 */
void EModeloMails::emailEnviado( Mail *mail )
{
    /// @todo Eliminar el email que esta para mandar segun el uuid
}


/*!
    \fn EModeloMails::append( Mail *mail )
 */
void EModeloMails::append( Mail *mail )
{
 QSqlRecord encolar = record();
 encolar.remove(0);
 encolar.setValue( "id_unico", mail->identificadorUnico().toString() );
 encolar.setValue( "para", mail->to() );
 encolar.setValue( "bcc", mail->bcc() );
 encolar.setValue( "cc", mail->cc() );
 encolar.setValue( "asunto", mail->subject() );
 encolar.setValue( "cuerpo", mail->messageBody() );
 encolar.setValue( "content-type", mail->contentType() );
 // Por ahora sin adjuntos
 //encolar.setValue( "
 if( this->insertRecord( -1, encolar ) )
 {
  emit nuevoMail();
  qDebug( "Email encolado correctamente" );
  return;
 }
 else
 {
  qDebug( "Error al agregar el email: no se enviara" );
  return;
 }
}
