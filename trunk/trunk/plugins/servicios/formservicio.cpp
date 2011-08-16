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
#include "formservicio.h"

#include <QDate>
#include <QMessageBox>
#include <QSqlError>

#include "eactcerrar.h"
#include "eactguardar.h"
#include "mrecargos.h"
#include "edrecargos.h"
#include "mservicios.h"

FormServicio::FormServicio ( MServicios *m, QWidget* parent, Qt::WFlags fl )
: EVentana( parent, fl ), Ui::FormServicioBase(), modelo(0)
{
        setupUi ( this );
        this->setWindowTitle( "Agregar nuevo servicio" );
        this->setWindowIcon( QIcon( ":/imagenes/add.png" ) );

        this->modelo = m;

        // Pongo la fecha de alta en hoy
        DEFechaAlta->setDate( QDate::currentDate() );

        // Coloco los periodos
        CBPeriodo->addItem( "Semanal ( 7 dias )", MServicios::Semanal );
        CBPeriodo->addItem( "Quincenal ( 15 dias )", MServicios::Quincenal );
        CBPeriodo->addItem( "Mensual", MServicios::Mensual );
        CBPeriodo->addItem( "Bi-Mensual", MServicios::BiMensual );
        CBPeriodo->addItem( "Trimestral", MServicios::Trimestral );
        CBPeriodo->addItem( "Cuatrimestral", MServicios::Cuatrimestral );
        CBPeriodo->addItem( "Seximestral", MServicios::Seximestral );
        CBPeriodo->addItem( "Anual", MServicios::Anual );

        // Dias en el mes que se hace el batch de calcular los nuevos importes 1->31 ( cuidado con los meses  28 y 30 )
        for( int i=1; i<=31; i++ )
        { CBInicioCobro->addItem( QString::number( i ), QString::number( i ) ); }

        CBMetodoIncompleto->insertItem( -1, "Division por dias y cobro de dias restantes", MServicios::DiasFaltantes );
        CBMetodoIncompleto->insertItem( -1, "Mes Completo", MServicios::MesCompleto );

        addAction( new EActGuardar( this ) );
        addAction( new EActCerrar( this ) );

        connect( CkBBaja, SIGNAL( toggled( bool ) ), this, SLOT( cambiarBaja( bool ) ) );
        DEFechaBaja->setEnabled( CkBBaja->checkState() );
}

/*!
    \fn FormServicio::guardar()
 */
void FormServicio::guardar()
{
 //Verificacion de si los campos son vacios
 if( LENombre->text().isEmpty() )
 { return; }
 if( !DEFechaAlta->date().isValid() )
 { return; }
 if( dSBPrecioBase->value() <= 0 )
 { return; }
 if( modelo->agregarServicio( LENombre->text(),
                              TEDescripcion->toPlainText(),
                              DEFechaAlta->date(),
                              dSBPrecioBase->value(),
                              CBPeriodo->itemData( CBPeriodo->currentIndex() ).toInt(),
                              CBInicioCobro->itemData( CBInicioCobro->currentIndex() ).toInt(),
                              CBMetodoIncompleto->itemData( CBMetodoIncompleto->currentIndex() ).toInt()
   ) )
 {
     QMessageBox::information( this, "Correcto", "El servicio fue dado de alta correctamente" );
     delete modelo;
     this->close();
     return;
 } else {
     QMessageBox::information( this, "Incorrecto", "El servicio <b>NO</b> pudo ser dado de alta" );
     qDebug( QString( "Error de modelo: %1").arg( modelo->lastError().text() ).toLocal8Bit() );
     delete modelo;
     return;
 }
}


/*!
    \fn FormServicio::cambiarBaja( bool estado )
        Slot llamado para habilitar y deshabilitar el selector de fecha de cuando fue dado de baja
 */
void FormServicio::cambiarBaja( bool estado )
{
    DEFechaBaja->setEnabled( estado );
}


void FormServicio::agregarRecargo()
{
    qWarning( "No implementado todavía" );
}
