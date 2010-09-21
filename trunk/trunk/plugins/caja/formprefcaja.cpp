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

#include "formprefcaja.h"
#include "ui_formprefcajabase.h"
#include "preferencias.h"

FormPrefCaja::FormPrefCaja(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormPrefCaja)
{
    ui->setupUi(this);
    this->setObjectName( "preferencias_caja" );
    this->setWindowTitle( "Caja" );
    this->setWindowIcon( QIcon( ":/imagenes/caja.png" ) );
}

FormPrefCaja::~FormPrefCaja()
{
    delete ui;
}

void FormPrefCaja::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FormPrefCaja::aplicar()
{
 this->guardar();
}

void FormPrefCaja::cargar()
{
    preferencias *p = preferencias::getInstancia();
    p->beginGroup( "Preferencias");
    p->beginGroup( "Caja" );
    ui->CkBResumen->setChecked( p->value( "siempre-resumen", false  ).toBool() );
    ui->CkBNoGastos->setChecked( p->value( "gastos-sinfondo", true ).toBool() );
    ui->RBAjuste->setChecked( p->value( "autoajuste", true ).toBool() );
    ui->RBDiferencia->setChecked( p->value( "no-cierre-dif", false ).toBool() );
    p->endGroup();
    p->endGroup();
}

void FormPrefCaja::guardar()
{
    preferencias *p = preferencias::getInstancia();
    p->beginGroup( "Preferencias");
    p->beginGroup( "Caja" );
    p->setValue( "siempre-resumen", ui->CkBResumen->checkState() );
    p->setValue( "gastos-sinfondo" , ui->CkBNoGastos->checkState() );
    p->setValue( "autoajuste", ui->RBAjuste->isChecked() );
    p->setValue( "no-cierre-dif", ui->RBDiferencia->isChecked() );
    p->endGroup();
    p->endGroup();
}
