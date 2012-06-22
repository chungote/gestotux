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

    addAction( ActSimular );
    addAction( ActCerrar );
}

/*!
 * \fn VPlanCuotas::simular()
 * Muestra la ventana de simular cuotas
 */
void VPlanCuotas::simular()
{ emit agregarVentana( new FormSimularCuotas() ); }
