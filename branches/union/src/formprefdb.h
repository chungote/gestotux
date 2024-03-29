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

#ifndef FORMPREFDB_H
#define FORMPREFDB_H

#include "eventana.h"
#include "formprefhijo.h"
#include "ui_ForPrefDb.h"

/*!
 * \brief Formulario de preferencias de base de datos
 *
 * Clase que realiza el formulario para la configuracion de la db interna o externa segun sea necesario
 * @author Esteban Zeller <tranfuga25s@gmail.com>
 */
class FormPrefDb : public EVentana, public FormPrefHijo, private Ui::FormPrefDbBase
{
  Q_OBJECT

public:
  FormPrefDb(QWidget* parent = 0, Qt::WFlags fl = 0 );
  ~FormPrefDb();
public slots:
    void cargar();
    void guardar();
    void aplicar();

};

#endif

