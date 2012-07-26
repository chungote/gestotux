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


EModeloMails::EModeloMails(QObject *parent, QSqlDatabase db)
 : QSqlTableModel(parent, db)
{
 setTable( "emails" );
 this->setEditStrategy( QSqlTableModel::OnManualSubmit );
 _tamano = -1;
}


EModeloMails::~EModeloMails()
{
}


/*!
    \fn EModeloMails::takeFirst()
 */
Mail * EModeloMails::takeFirst()
{
 mutex.lock();
 //carga el primer email de la lista
 this->select();
 QSqlRecord primero = this->record( 0 );
 Mail *mail = EEmail::instancia()->email();
 mail->setIdentificadorUnico( QUuid( primero.value("id_unico" ).toString() ) );
 EServidorEmail servidor( this, this->database() );
 mail->setHeader( servidor.de(),
			primero.value( "para" ).toString(),
			primero.value( "bcc" ).toString(),
			primero.value( "cc" ).toString(),
			primero.value( "asunto" ).toString()
		);
 mail->setMessageBody( primero.value( "cuerpo" ).toString() );
 mail->setContentType( primero.value( "content_type" ).toString() );
 mutex.unlock();
 return mail;
}


/*!
    \fn EModeloMails::size()
 */
int EModeloMails::size()
{
    mutex.lock();
    if( _tamano == -1 ) {
         QSqlQuery cola;
         if( cola.exec( "SELECT COUNT( id_email ) FROM emails" ) ) {
             if( cola.next() )
             {
              qDebug( QString( "1-cant emails: %1" ).arg( cola.record().value(0).toInt() ).toLocal8Bit() );
              _tamano = cola.record().value(0).toInt();
             }
             else
             {
              qDebug( "Error al contar los emails en la cola" );
              qDebug( qPrintable( cola.lastError().text() ) );
              qDebug( qPrintable( cola.lastQuery() ) );
              _tamano = 0;
             }
         } else {
             qDebug( "Error al ejectura la cola de conteo" );
             qDebug( cola.lastError().text().toLocal8Bit() );
             qDebug( cola.lastQuery().toLocal8Bit() );
             _tamano = -1;
         }
     }
  mutex.unlock();
  return _tamano;
}


/*!
    \fn EModeloMails::append( Mail *mail )
 */
void EModeloMails::append( Mail *mail )
{
 mutex.lock();
 QSqlRecord encolar = this->record();
 encolar.remove(0);
 encolar.setValue( "id_unico", mail->identificadorUnico().toString() );
 encolar.setValue( "para", mail->to() );
 encolar.setValue( "bcc", mail->bcc() );
 encolar.setValue( "cc", mail->cc() );
 encolar.setValue( "asunto", mail->subject() );
 encolar.setValue( "cuerpo", mail->messageBody() );
 encolar.setValue( "content_type", mail->contentType() );
 // Por ahora sin adjuntos
 //encolar.setValue( "
 if( this->insertRecord( -1, encolar ) )
 {
  if( !this->submitAll() )
  {
    qDebug("error en el submit del email" );
    qDebug( qPrintable( this->lastError().text() ) );
  }
  else
  {
   emit nuevoMail();
   qDebug( "Email encolado correctamente" );
   mutex.unlock();
   this->size();
   mutex.lock();
   _tamano++;
  }
 }
 else
 { qDebug( "Error al agregar el email: no se enviara" ); }
 mutex.unlock();
}

/*!
 * \fn EModeloMails::enviado( Mail *mail )
 * Elimina el mensaje en cola identificado por el puntero pasado como parametro
 */
void EModeloMails::enviado(Mail *mail)
{
    // Elimina de la lista el email ingresado
    mutex.lock();
    QString id = mail->identificadorUnico().toString();
    QSqlQuery cola;
    if( !cola.exec( QString( "SELECT id_email, id_unico FROM emails WHERE id_unico = \"%1\"" ).arg( id ) ) ) {
        qDebug( "Error al buscar email por id unica" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
    } else {
        if( cola.next() ) {
            qDebug( cola.lastQuery().toLocal8Bit() );
            int id_email = cola.record().value(0).toInt();
            if( !cola.exec( QString( "DELETE FROM emails WHERE id_email = %1" ).arg( id_email ) ) ) {
                qDebug( "Error al eliminar el email enviado" );
                qDebug( cola.lastError().text().toLocal8Bit() );
                qDebug( cola.lastQuery().toLocal8Bit() );
            }
            qDebug( cola.lastQuery().toLocal8Bit() );
            if( !this->submitAll() ) {
                qDebug( "Error al guardar la cola de emails" );
            } else {
                qDebug( "Email desencolado correctamente..." );
                _tamano--;
            }
        } else {
            qDebug( "No se pudo encontrar el email encolado" );
            qDebug( cola.lastError().text().toLocal8Bit() );
            qDebug( cola.lastQuery().toLocal8Bit() );
        }
    }
    mutex.unlock();
}
