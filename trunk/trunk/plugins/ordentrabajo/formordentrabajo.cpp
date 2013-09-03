#include "formordentrabajo.h"

#include <QDateTime>

#include "eactcerrar.h"
#include "eactguardar.h"
#include "mordentrabajo.h"

FormOrdenTrabajo::FormOrdenTrabajo( bool agregar, QWidget *parent ) :
    EVentana( parent ), FormOrdenTrabajoBase(), _agregando(agregar)
{
    setupUi(this);

    this->setWindowTitle( "Orden de Trabajo" );
    this->setWindowIcon( QIcon( ":/imagenes/orden_trabajo.png" ) );
    this->setObjectName( "orden_trabajo" );

    ActCerrarOrden = new QAction( this );
    ActCerrarOrden->setText( "Cerrar" );
    ActCerrarOrden->setStatusTip( "Cierra la orden de trabajo actual" );
    ActCerrarOrden->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
    connect( ActCerrarOrden, SIGNAL( triggered() ), this, SLOT( cerrarOrden() ) );

    ActDevolverCliente = new QAction( this );
    ActDevolverCliente->setText( "Devolver" );
    ActDevolverCliente->setStatusTip( "Devolver el trabajo al cliente" );
    ActDevolverCliente->setIcon( QIcon( ":/imagenes/devolver_cliente.png" ) );
    connect( ActDevolverCliente, SIGNAL( triggered() ), this, SLOT( devolverCliente() ) );

    // Pongo la fecha de hoy
    DTEFechaIngreso->setDateTime( QDateTime::currentDateTime() );
    DEFechaDevolucion->setDate( QDate::currentDate().addDays( 2 ) );

    connect( CBCliente, SIGNAL( cambioIdCliente( int ) ), this, SLOT( cambioCliente( int ) ) );
    connect( CBTecnico, SIGNAL( cambioId( int ) ), this, SLOT( cambioTecnico( int ) ) );

    PBAgregarFacturacion->setIcon( QIcon( ":/imagenes/add.png" ) );
    connect( PBAgregarFacturacion, SIGNAL( clicked() ), this, SLOT( agregarFacturacion() ) );

    PBEliminarFacturacion->setIcon( QIcon( ":/imagenes/eliminar.png" ) );
    connect( PBEliminarFacturacion, SIGNAL( clicked() ), this, SLOT( eliminarFacturacion() ) );

    PBFacturar->setIcon( QIcon( ":/imagenes/facturar_servicio.png" ) );
    connect( PBFacturar, SIGNAL( clicked() ), this, SLOT( facturarOrden() ) );

    PBAgregarHistorial->setIcon( QIcon( ":/imagenes/add.png" ) );
    connect( PBAgregarHistorial, SIGNAL( clicked() ), this, SLOT( agregarHistorial() ) );

    PBEliminarHistorial->setIcon( QIcon( ":/imagenes/eliminar.png" ) );
    connect( PBEliminarHistorial, SIGNAL( clicked() ), this, SLOT( eliminarHistorial() ) );

    PBCerrarOrden->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
    connect( PBCerrarOrden, SIGNAL( clicked() ), this, SLOT( cerrarOrden() ) );

    addAction( new EActGuardar( this ) );
    addAction( new EActCerrar( this ) );

    if( agregar ) {
        // Deshabilito los datos de historial y facturacion.
        TBGeneral->setItemEnabled( 2, false );
        TBGeneral->setItemEnabled( 3, false );
        // Coloco el proximo numero de comprobante.
        LNumeroOrdenTrabajo->setText( MOrdenTrabajo::numeroComprobanteProximo().aCadena() );
    }
}

/*!
 * \brief FormOrdenTrabajo::setearIdOrdenTrabajo
 * \param id_orden_trabajo
 */
void FormOrdenTrabajo::setearIdOrdenTrabajo( const int id_orden_trabajo )
{
    _agregando = false;
    TBGeneral->setItemEnabled( 2, true );
    TBGeneral->setItemEnabled( 3, true );
    /// @TODO agregar carga de datos
    /// @TODO Agregar carga de historial
    /// @TODO Agregar carga de historial de facturacion
    /// @TODO Agregar carga de datos de equipamiento
}

/**
 * @brief FormOrdenTrabajo::cambioCliente
 * Slot llamado cada vez que se cambia el cliente
 * @param id_cliente ID del cliente
 */
void FormOrdenTrabajo::cambioCliente( int id_cliente )
{
    if( id_cliente <= 0 ) { return; }
    if( _agregando ) {
        /// @TODO Si está agregando, cargar el Equipamiento que exista para el cliente ( si es solo uno )
    } else {
        /// @TODO Agregar registro de cambio de cliente asignado
    }
}

/*!
 * \brief FormOrdenTrabajo::cambioTecnico
 * \param id_tecnico
 */
void FormOrdenTrabajo::cambioTecnico( int id_tecnico )
{
    if( id_tecnico <= 0 ) { return; }
    if( _agregando ) {

    } else {
        /// @TODO Agregar registro de cambio de técnico.
    }
}

/*!
 * \brief FormOrdenTrabajo::cerrarOrden
 */
void FormOrdenTrabajo::cerrarOrden()
{

}

/*!
 * \brief FormOrdenTrabajo::devolverCliente
 */
void FormOrdenTrabajo::devolverCliente()
{

}

/*!
 * \brief FormOrdenTrabajo::agregarFacturacion
 */
void FormOrdenTrabajo::agregarFacturacion()
{
}

/*!
 * \brief FormOrdenTrabajo::eliminarFacturacion
 */
void FormOrdenTrabajo::eliminarFacturacion()
{
}

/*!
 * \brief FormOrdenTrabajo::agregarHistorial
 */
void FormOrdenTrabajo::agregarHistorial()
{
}

/*!
 * \brief FormOrdenTrabajo::eliminarHistorial
 */
void FormOrdenTrabajo::eliminarHistorial()
{
}

/*!
 * \brief FormOrdenTrabajo::facturarOrden
 */
void FormOrdenTrabajo::facturarOrden()
{
}

/*!
 * \brief FormOrdenTrabajo::imprimir
 */
void FormOrdenTrabajo::imprimir()
{
}

/*!
 * \brief FormOrdenTrabajo::pdf
 */
void FormOrdenTrabajo::pdf()
{
}

/*!
 * \brief FormOrdenTrabajo::cancelar
 */
void FormOrdenTrabajo::cancelar()
{
}

/*!
 * \brief FormOrdenTrabajo::guardar
 */
void FormOrdenTrabajo::guardar()
{
}

void FormOrdenTrabajo::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

