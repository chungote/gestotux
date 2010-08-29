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

#include "FormAgregarCaja.h"
#include "ui_FormAgregarCajaBase.h"

#include "mcajas.h"

FormAgregarCaja::FormAgregarCaja(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormAgregarCaja)
{
    ui->setupUi(this);
    this->setWindowTitle( "Agregar nueva caja" );

    ui->DEFechaAlta->setDate( QDate::currentDate() );
}

FormAgregarCaja::~FormAgregarCaja()
{
    delete ui;
}

void FormAgregarCaja::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}



/*!
 * @fn FormAgregarCaja::accept()
 * Funcion llamada al apretar el boton de aceptar
 */
void FormAgregarCaja::accept()
{
    if( ui->LENombre->text().isEmpty() ) {
        /// @todo Patri: Agregar cartelito de que tiene que poner un nombre
    }
    // Guardo los datos
    /// @todo Patri: Implementar funcion de agregar caja
    this->close();
}
