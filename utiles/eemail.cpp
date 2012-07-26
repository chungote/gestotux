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
#include "eemail.h"

EEmail *EEmail::_instancia = 0;

EEmail::EEmail(QObject *parent)
 : QObject(parent)
{
    this->setObjectName( "_email" );
}


EEmail::~EEmail()
{
}


/*!
    \fn EEmail::email()
 */
Mail * EEmail::email()
{
 Mail *email = new Mail();
#ifdef Q_WS_WIN
 email->setEncoding( "ISO-8859-2" );
#endif
 email->setContentTransferEncoding( "quoted-printable" );
 return email;
}


/*!
    \fn EEmail::enviarEmail( Mail *email )
 */
void EEmail::enviarEmail( Mail *email )
{
 emit enviar( email );
}


/*!
    \fn EEmail::instancia()
 */
EEmail* EEmail::instancia()
{
 if( _instancia == 0 )
 {
  _instancia = new EEmail();
 }
 return _instancia;
}


/*!
    \fn EEmail::testear()
 */
void EEmail::testear()
{
 Mail *em = this->email();
 em->setHeader( "esteban.zeller@gmail.com", "esteban.zeller@gmail.com", "", "", "Asunto de prueba" );
 em->setContentType( "text/plain" );
 em->setMessageBody( "Intento de ver si el mensaje puede ser enviado desde el nuevo sistema de email del gestotux" );
 this->enviarEmail( em );
}
