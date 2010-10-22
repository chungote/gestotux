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

#ifndef FORMCLIENTESADHERIDOS_H
#define FORMCLIENTESADHERIDOS_H

#include "eventana.h"

namespace Ui {
    class FormClientesAdheridos;
}
class MServicios;

class FormClientesAdheridos : public EVentana
{
    Q_OBJECT

public:
    explicit FormClientesAdheridos(QWidget *parent = 0);
    ~FormClientesAdheridos();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FormClientesAdheridos *ui;
    MServicios *mservicios;
};

#endif // FORMCLIENTESADHERIDOS_H