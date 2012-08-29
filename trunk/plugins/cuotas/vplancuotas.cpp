#include "vplancuotas.h"

#include "formsimularcuotas.h"
#include "mvplancuota.h"

/* CONSULTA MODELO
 *SELECT CONCAT( '# ', pc.id_plan_cuota ) AS plan_cuota,
             c.razon_social AS cliente,
             CONCAT( ( SELECT SUM( ic2.id_plan_cuota ) FROM item_cuota AS ic2 WHERE ic2.id_plan_cuota = pc.id_plan_cuota AND ic2.fecha_pago IS NULL ),
                            ( SELECT SUM( ic2.id_plan_cuota ) FROM item_cuota AS ic2 WHERE ic2.id_plan_cuota = pc.id_plan_cuota AND ic2.fecha_pago ) ) AS cuotas,
            ( SELECT SUM( ic2.monto ) FROM item_cuota AS ic2 WHERE ic2.id_plan_cuota = pc.id_plan_cuota AND ic2.fecha_pago IS NULL ) AS total_faltante,
             ( SELECT MAX( ic2.fecha_pago ) FROM item_cuota AS ic2 WHERE ic2.id_plan_cuota = pc.id_plan_cuota AND ic2.fecha_pago IS NOT NULL ) AS ultimo_pago,
             ( SELECT MIN( ic2.fecha_vencimiento ) FROM item_cuota AS ic2 WHERE ic2.id_plan_cuota = pc.id_plan_cuota AND ic2.fecha_pago IS NULL ) AS proximo_pago
FROM plan_cuota AS pc,
           item_cuota AS ic,
           clientes AS c,
           factura AS f
WHERE ic.id_plan_cuota = pc.id_plan_cuota
 AND pc.id_factura = f.id_factura
 AND c.id = f.id_cliente
 *
 **/



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

    modelo = new MVPlanCuota( this );
    vista->setModel( modelo );

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
