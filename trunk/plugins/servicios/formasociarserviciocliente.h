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

#ifndef FORMASOCIARSERVICIOCLIENTE_H
#define FORMASOCIARSERVICIOCLIENTE_H

#include <QDialog>
#include "ui_FormAsociarBase.h"
#include <QDate>

class FormAsociarServicioCliente : public QDialog, private Ui::Dialog
{
  Q_OBJECT

public:
enum tipoForm {
 Todo, // Muestra todos los campos
 Cliente, // Muestra la lista de clientes para asociar a un servicio
 Servicio, // Muestra el servicio al que se debe asociar un cliente
 SoloFecha
}_tipo;

  FormAsociarServicioCliente(QWidget* parent = 0, tipoForm tipo = Todo, Qt::WFlags fl = 0 );
  ~FormAsociarServicioCliente();
    int idCliente();
    int idServicio();
    QDate fecha();
    void setFecha( QDate fecha );
    void setIdCliente( int id_cliente );
    void setIdServicio( int id_servicio );

public slots:
    int exec();

private slots:
    void reject();
    void accept();

private:
        int _id_cliente;
        int _id_servicio;
        QDate _fecha;
        bool _agregado;

};

#endif

