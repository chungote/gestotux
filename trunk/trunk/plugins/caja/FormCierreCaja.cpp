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

#include "FormCierreCaja.h"
#include "ui_FormCierreCajaBase.h"

#include "mcajas.h"
#include "preferencias.h"

#include <QMessageBox>

FormCierreCaja::FormCierreCaja(QWidget *parent) :
    EVentana(parent),
    ui(new Ui::FormCierreCaja)
{
    ui->setupUi(this);
    this->setObjectName( "cierre_caja" );
    this->setWindowTitle( "Cierre de Caja" );

    ui->PBConfirmar->setIcon( QIcon( ":/imagenes/aplicar.png" ) );
    ui->PBCancelar->setIcon( QIcon( ":/imagenes/stop.png" ) );

    ui->CBCaja->setModel( new MCajas( ui->CBCaja ) );
    ui->CBCaja->setModelColumn( 1 );
    connect( ui->CBCaja, SIGNAL( currentIndexChanged(int) ), this, SLOT( cambioCaja(int ) ) );
    qobject_cast<QSqlTableModel *>(ui->CBCaja->model())->select();

}

FormCierreCaja::~FormCierreCaja()
{
    delete ui;
}

void FormCierreCaja::changeEvent(QEvent *e)
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

void FormCierreCaja::cambioCaja( int num )
{
    int num_caja = ui->CBCaja->model()->data( ui->CBCaja->model()->index( num, 0 ), Qt::DisplayRole ).toInt();
    ui->dSBComputado->setValue( MCajas::saldo( num_caja ) );
}

void FormCierreCaja::hacerCierre()
{
    // Verifico que concuerden los saldos
    if( ( ui->dSBComputado->value() != ui->dSBSumado->value() ) && ( preferencias::getInstancia()->value( "Preferencias/Caja/no-cierre-dif", false ).toBool() ) )
    {
        QMessageBox::critical( this, "Error", "Los Saldos no coinciden" );
        return;
    }
    MCajas *caja = qobject_cast<MCajas *>(ui->CBCaja->model());
    int id_caja = ui->CBCaja->model()->data( ui->CBCaja->model()->index( ui->CBCaja->currentIndex(), 0 ), Qt::DisplayRole ).toInt();
    if( caja->hacerCierre( id_caja, QDateTime::currentDateTime(), ui->dSBComputado->value() ) ) {
        QMessageBox::information( this, "Correcto", "El cierre se realizo correctamente" );
        if( ( ui->CkBResumen->checkState() == Qt::Checked ) || ( preferencias::getInstancia()->value( "Preferencias/Caja/siempre-resumen", false ).toBool() ) ) {
            ///@todo Agregar sistema para hacer el resumen
        }
        this->close();
        return;
    } else {
        QMessageBox::warning( this, "Error", "El cierre no se pudo realizar correctamente" );
        return;
    }
}
