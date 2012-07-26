#include "vplancuotas.h"

#include "formsimularcuotas.h"

VPlanCuotas::VPlanCuotas(QWidget *parent) :
 EVLista(parent)
{
    this->setObjectName( "visorplancuotas" );
    this->setWindowTitle( "Planes de cuota activos" );
    this->setWindowIcon( QIcon( ":/imagenes/cuotas.png" ) );

    ActSimular = new QAction( this );
    ActSimular->setText( "Simular" );
    connect( ActSimular, SIGNAL( triggered() ), this, SLOT( simular() ) );

    ActTerminado = new QAction( this );
    ActTerminado->setText( "Terminados" );
    ActTerminado->setCheckable( true );
    //ActTerminado->setIcon( QIcon( ":/imagenes/" ) );
    connect( ActTerminado, SIGNAL( toggled( bool ) ), this, SLOT( cambioTerminado( bool ) ) );

    ActDetalles = new QAction( this );
    ActDetalles->setText( "Detalles" );
    //ActDetalles->setIcon( QIcon( ":/imagenes/" ) );
    connect( ActDetalles, SIGNAL( triggered() ), this, SLOT( verDetalles() ) );

    QAction *ActSep = new QAction( this );
    ActSep->setSeparator( true );

    addAction( ActSimular );
    addAction( ActCerrar );
    addAction( ActSep );
    addAction( ActTerminado );
}

/*!
 * \fn VPlanCuotas::simular()
 * Muestra la ventana de simular cuotas
 */
void VPlanCuotas::simular()
{ emit agregarVentana( new FormSimularCuotas() ); }

/*!
 * \fn VPlanCuotas::cambioTerminado( bool e )
 * Muestra los planes terminados en la lista de planes
 * \param e Estado de la accion
 */
void VPlanCuotas::cambioTerminado( bool )
{
}

/*!
 * \fn VPlanCuotas::verDetalles()
 * Muestra la lista de cuotas del plan y su estado
 */
void VPlanCuotas::verDetalles()
{
}
