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

#ifndef FORMACTUALIZACION_H
#define FORMACTUALIZACION_H

#include <QWidget>
#include "ui_FormActualizacionBase.h"

class QFtp;

class FormActualizacion : public QWidget, private Ui::FormActualizacionBase
{
  Q_OBJECT

public:
  FormActualizacion(QWidget* parent = 0, Qt::WFlags fl = 0 );
  ~FormActualizacion();

protected slots:
    void iniciar();
    void detener();
    void cambioEstado( int estado );
    void inicio( int id );
    void terminado( int comando, bool  error );

private:
	bool _continuar_actualizando;
	QFtp *ftp;
public slots:
    void finComando( int comando, bool error );
private slots:
    void analizarGeneral();
};

#endif
