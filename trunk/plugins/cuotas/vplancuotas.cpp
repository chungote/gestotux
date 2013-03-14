#include "vplancuotas.h"

#include "formsimularcuotas.h"
#include "formdetallecuotas.h"
#include "mvplancuota.h"
#include "DPagoCuota.h"

#include <QMessageBox>

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
    this->setWindowIcon( QIcon( ":/imagenes/cuotas_detalle.png" ) );

    ActSimular = new QAction( this );
    ActSimular->setText( "Simular" );
    ActSimular->setStatusTip( "Simular un plan de cuotas" );
    ActSimular->setIcon( QIcon( ":/imagenes/simular_cuota.png" ) );
    connect( ActSimular, SIGNAL( triggered() ), this, SLOT( simular() ) );

    ActTerminado = new QAction( this );
    ActTerminado->setText( "Terminados" );
    ActTerminado->setCheckable( true );
    //ActTerminado->setIcon( QIcon( ":/imagenes/" ) );
    connect( ActTerminado, SIGNAL( toggled( bool ) ), this, SLOT( cambioTerminado( bool ) ) );

    ActDetalles = new QAction( this );
    ActDetalles->setText( "Detalles" );
    ActDetalles->setStatusTip( "Ver los detalles de un plan de cuotas seleccionado" );
    ActDetalles->setIcon( QIcon( ":/imagenes/cuotas_detalle.png" ) );
    connect( ActDetalles, SIGNAL( triggered() ), this, SLOT( verDetalles() ) );

    ActIngresarPago = new QAction( this );
    ActIngresarPago->setText( "Pago" );
    ActIngresarPago->setIcon( QIcon( ":/imagenes/ingresar_pago.png" ) );
    ActIngresarPago->setStatusTip( "Ingresa un nuevo pago mediante un recibo" );
    connect( ActIngresarPago, SIGNAL( triggered() ), this, SLOT( ingresarPago() ) );

    ActCancelar = new QAction( this );
    ActCancelar->setText( "Cancelar" );
    ActCancelar->setIcon( QIcon( ":/imagenes/cancelar_cuota.png" ) );
    ActCancelar->setStatusTip( "Cancelar un plan de cuotas" );
    connect( ActCancelar, SIGNAL( triggered() ), this, SLOT( cancelar() ) );

    QAction *ActSep = new QAction( this );
    ActSep->setSeparator( true );
    QAction *ActSep2 = new QAction( ActSep );
    ActSep2->setSeparator( true );

    addAction( ActSimular );
    addAction( ActSep );
    addAction( ActDetalles );
    addAction( ActIngresarPago );
    addAction( ActCancelar );
    addAction( ActCerrar );
    addAction( ActSep2 );
    addAction( ActTerminado );
    addAction( ActBuscar );

    modelo = new MVPlanCuota( this );
    vista->setModel( modelo );

    modelo->select();

    agregarFiltroBusqueda( QString::fromUtf8( "Razón Social" ), "cliente LIKE '%%%1%'" );
    habilitarBusqueda();
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
void VPlanCuotas::cambioTerminado( bool e )
{
    if( e ) {
        qWarning( "No implementado filtro todavía" );
        this->modelo->setFilter( "    ic.id_plan_cuota = pc.id_plan_cuota "
                                 "AND pc.id_factura    = f.id_factura "
                                 "AND c.id             = f.id_cliente" );
    } else {
        this->modelo->setFilter( "    ic.id_plan_cuota = pc.id_plan_cuota "
                                 "AND pc.id_factura    = f.id_factura "
                                 "AND c.id             = f.id_cliente" );
    }
    this->modelo->select();
}

/*!
 * \fn VPlanCuotas::verDetalles()
 * Muestra la lista de cuotas del plan y su estado
 */
void VPlanCuotas::verDetalles()
{
    // Busco el plan de cuota seleccionado
    if( this->vista->selectionModel()->selectedRows().isEmpty() ) {
        QMessageBox::warning( this, "Error", "Por favor, seleccione una sola fila para ver su detalle" );
        return;
    }
    QModelIndex idx = this->vista->selectionModel()->selectedRows().first();
    int id_plan = idx.model()->data( idx.model()->index( idx.row(), 0 ), Qt::EditRole ).toInt();
    FormDetalleCuotas *f = new FormDetalleCuotas();
    f->setearIdPlanCuota( id_plan );
    emit agregarVentana( f );
}

/*!
 * \fn VPlanCuotas::cancelar()
 * Cancela un plan o planes de cuota seleccionados
 */
void VPlanCuotas::cancelar()
{
    qWarning( "No implementado" );
}

/*!
 * \fn VPlanCuotas::ingresarPago()
 */
void VPlanCuotas::ingresarPago()
{
    // Busco el plan de cuota seleccionado
    if( this->vista->selectionModel()->selectedRows().isEmpty() ) {
        QMessageBox::warning( this, "Error", "Por favor, seleccione una sola fila para ver su detalle" );
        return;
    }
    QModelIndex idx = this->vista->selectionModel()->selectedRows().first();
    int id_plan_cuota = idx.model()->data( idx.model()->index( idx.row(), 0 ), Qt::EditRole ).toInt();

    DPagoCuota *dialogo = new DPagoCuota( this );
    dialogo->setearPlanCuota( id_plan_cuota );
    dialogo->setearModelo( qobject_cast<MVPlanCuota *>(this->modelo) );
    dialogo->exec();
}
