#include "formadelantocuotas.h"

FormAdelantoCuotas::FormAdelantoCuotas( QWidget *parent ) :
FormDetalleCuotas( parent )
{
    GBAdelanto->setVisible( true );
    GBDetalles->setVisible( false );



    connect( DSBImporteAdelanto, SIGNAL( valueChanged( double ) ), this, SLOT( cambioImporte( double ) ) );

    ActConfirmar = new QAction( this );
    ActConfirmar->setText( "Confirmar" );
    ActConfirmar->setStatusTip( "Confirma el adelanto y la modificacion del plan de cuotas" );
    connect( ActConfirmar, SIGNAL( triggered() ), this, SLOT( confirmar() ) );

    addAction( ActConfirmar );
}

void FormAdelantoCuotas::setearIdPlanCuota( int id )
{
    FormDetalleCuotas::setearIdPlanCuota( id );
    modelo_item = new MAdelantoSimularCuotas( this );
    TVSimulacion->setModel( modelo_item );
    modelo_item->setCuotas( SBCantidad->value() );
    modelo_item->setFechaInicio( DEInicio->date() );
    modelo_item->setImporte( DSBImporte->value() );
    modelo_item->setInteres( DSBInteres->value() );
    modelo_item->setPeriodo( (MPlanCuota::Periodo)CBPeriodo->currentIndex() );
    modelo_item->setPagoInicial( DSBEntrega->value() );
    modelo_item->regenerar();
}

/*!
 * \brief FormAdelantoCuotas::cambiarImporte
 * \param importe Importe cambiado
 */
void FormAdelantoCuotas::cambiarImporte( double importe )
{ modelo_item->setearImporteAdelanto( importe ); }

/*!
 * \brief FormAdelantoCuotas::confirmar
 */
void FormAdelantoCuotas::confirmar()
{
    return;
}
