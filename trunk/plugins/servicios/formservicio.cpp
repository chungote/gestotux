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
#include <QDataWidgetMapper>

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
        _modificando = false;
        _id_servicio = -1;

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

        QAction *ActRecargos = new QAction( this );
        ActRecargos->setText( "Recargos" );
        connect( ActRecargos, SIGNAL( triggered() ), this, SLOT( agregarRecargo() ) );

        addAction( new EActGuardar( this ) );
        addAction( ActRecargos );
        addAction( new EActCerrar( this ) );

        connect( CkBBaja, SIGNAL( toggled( bool ) ), this, SLOT( cambiarBaja( bool ) ) );
        DEFechaBaja->setEnabled( CkBBaja->isChecked() );

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
 if( _modificando ) {
     if( CkBBaja->isChecked() ) {
         _mapa->addMapping( DEFechaBaja, modelo->fieldIndex( "fecha_baja" ) );
     }
     if( _mapa->submit() ) {
         QMessageBox::information( this, "Correcto", "El servicio fue modificado correctamente" );
         // Veo la modificacion del precio?
         this->close();
         return;
     } else {
         qDebug( "Error, no se pudo hacer submit del mapa" );
         qDebug( this->modelo->lastError().text().toLocal8Bit() );
     }
 } else {
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
             this->close();
             return;
         } else {
             QMessageBox::information( this, "Incorrecto", "El servicio <b>NO</b> pudo ser dado de alta" );
             qDebug( QString( "Error de modelo: %1").arg( modelo->lastError().text() ).toLocal8Bit() );
             return;
         }
 }
}


/*!
    \fn FormServicio::cambiarBaja( bool estado )
        Slot llamado para habilitar y deshabilitar el selector de fecha de cuando fue dado de baja
 */
void FormServicio::cambiarBaja( bool estado )
{  DEFechaBaja->setEnabled( estado ); }


#include "formrecargos.h"
/*!
    \fn FormServicio::agregarRecargo()
    Abre la ventana para agregar un recargo
 */
void FormServicio::agregarRecargo()
{
    if ( _modificando ) {
        FormRecargos *f = new FormRecargos( this );
        f->setearId( this->_id_servicio );
        emit agregarVentana( f );
        return;
    } else {
        QMessageBox::information( this, "No se puede", "No se puede agregar un recargo ya que todavía no ha sido dado de alta el servicio. \n Esto es necesario para mantener la consistencia de los datos" );
        return;
    }

}

/*!
 * \fn FormServicio::setearId( const int id_servicio, const QModelIndex indice )
 * Coloca el formulario en modo de edicion y carga los datos para que sean modificados.
 * \param id_servicio Identificador del servicio a cargar
 * \param indice Indice de la vista para pasar al mapa
 */
void FormServicio::setearId( const int id_servicio, const QModelIndex indice )
{
    qWarning( "Esta parte todavia no ha sido programada. \n Se mostrara el formulario pero no podra hacer nada con el." );
    disconnect( this, SLOT( guardar() ) );
    this->_modificando = true;

    _mapa = new QDataWidgetMapper();
    _mapa->setOrientation( Qt::Horizontal );
    _mapa->setModel( this->modelo );
    _mapa->setSubmitPolicy( QDataWidgetMapper::ManualSubmit );

    _mapa->addMapping( LENombre, modelo->fieldIndex( "nombre" ) );
    _mapa->addMapping( TEDescripcion, modelo->fieldIndex( "descripcion" ) );
    _mapa->addMapping( DEFechaAlta, modelo->fieldIndex( "fecha_alta" ) );
    _mapa->addMapping( dSBPrecioBase, modelo->fieldIndex( "precio_base" ) );
    _mapa->addMapping( CBPeriodo, modelo->fieldIndex( "periodo" ), "itemData" ); /// @todo Probar que estas propiedades anden
    _mapa->addMapping( CBMetodoIncompleto, modelo->fieldIndex( "forma_incompleto" ), "itemData" ); /// @todo Probar que estas propiedades anden
    _mapa->addMapping( CBInicioCobro, modelo->fieldIndex( "inicio_cobro" ), "itemData"); /// @todo Probar que estas propiedades anden

    // Busco el indice
    this->_id_servicio = id_servicio;
    if( indice.isValid() ) {
        _mapa->setCurrentModelIndex( indice );
    } else {
        qWarning( "El indice pasado es invalido!" );
        abort();
    }
}
