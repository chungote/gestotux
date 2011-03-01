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

#ifndef FORMFACTURARSERVICIO_H
#define FORMFACTURARSERVICIO_H

#include "ui_FormFacturarServicioBase.h"
#include "eventana.h"
class QAction;
class EActCerrar;

class FormFacturarServicio : public EVentana, private Ui::FormFacturarServicio
{
    Q_OBJECT

public:
    explicit FormFacturarServicio(QWidget *parent = 0);
    void setearServicio( const int id_servicio = 0 );

protected:
    void changeEvent(QEvent *e);

private:
    int _id_servicio;
    EActCerrar *ActCerrar;
    QAction *ActFacturar;

    void cargar_datos_servicio();

};

#endif // FORMFACTURARSERVICIO_H