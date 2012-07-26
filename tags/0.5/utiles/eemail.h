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
#ifndef EEMAIL_H
#define EEMAIL_H

#include <QObject>
#include "mail.h"

/**
 * \brief Puente para plugin de email
Clase intermedia que sirve de intermediario entre el plugin de email ( si es cargado ) y los demas plugins

	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class EEmail : public QObject
{
Q_OBJECT
public:
    EEmail( QObject *parent = 0 );
    ~EEmail();
    static EEmail * instancia();
    void enviarEmail( Mail *email );
    static Mail * email();
    void testear();

private:
    static EEmail *_instancia;

signals:
	void enviar( Mail *email );

};

#endif
