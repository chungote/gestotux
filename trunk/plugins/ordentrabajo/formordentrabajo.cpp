#include "formordentrabajo.h"

#include <QDateTime>
#include <QMessageBox>

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

    _modelo_equipamiento = new MEquipamiento( this );
    _modelo_historial = new MHistorialOrdenTrabajo( this );
    _modelo_historial_facturacion = new MHistorialOrdenTrabajo( this );
    _modelo_orden = new MOrdenTrabajo( this );

    if( agregar ) {
        // Deshabilito los datos de historial y facturacion.
        TBGeneral->setItemEnabled( 2, false );
        TBGeneral->setItemEnabled( 3, false );
        // Coloco el proximo numero de comprobante.
        LNumeroOrdenTrabajo->setText( MOrdenTrabajo::numeroComprobanteProximo().aCadena() );
    } else {
        _modelo_historial_facturacion->mostrarCostosSumados();
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

    // Cargo los datos
    _modelo_orden->cargarDatos( id_orden_trabajo );
    CBCliente->setearId( _modelo_orden->idCliente() );
    LEIngresante->setText( _modelo_orden->ingresante() );
    LERequerente->setText( _modelo_orden->requerente() );
    CBTecnico->setearId( _modelo_orden->idTecnico() );
    DEFechaDevolucion->setDateTime( _modelo_orden->fechaDevolucion() );
    DTEFechaIngreso->setDateTime( _modelo_orden->fechaIngreso() );

    // Historial de acciones
    _modelo_historial->setearOrdenTrabajo( id_orden_trabajo );
    LVHistorial->setModel( _modelo_historial );

    // Modelo del historial de facturación
    _modelo_historial_facturacion->setearOrdenTrabajo( id_orden_trabajo );
    TVFacturacion->setModel( _modelo_historial_facturacion );

    // Datos del equipamiento
    int id_equipamiento = _modelo_orden->obtenerIdEquipamientoSegunId( id_orden_trabajo );
    if( !_modelo_equipamiento->existe( id_equipamiento ) ) {
        QMessageBox::critical( this, "Error", "El equipamiento relacionado no existe!" );
        return;
    }
    _modelo_equipamiento->cargarDatos( id_equipamiento );
    cargarDatosEquipamiento();

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
        // Ingreso el primer equipamiento del cliente
        if( _modelo_equipamiento->existeEquipamientoParaCliente( id_cliente ) ) {
            if( _modelo_equipamiento->cantidadEquipamientoParaCliente( id_cliente ) == 1 ) {
                _modelo_equipamiento->cargarDatos( _modelo_equipamiento->buscarIdEquipamientoSegunCliente( id_cliente ) );
                cargarDatosEquipamiento();
            } else {
                /// @TODO: Mostrar las opciones para elegir el equipamiento
            }
        }
    } else {
        /// @TODO: Agregar registro de cambio de cliente asignado
    }
}

/*!
 * \brief FormOrdenTrabajo::cambioTecnico
 * \param id_tecnico
 */
void FormOrdenTrabajo::cambioTecnico( int id_tecnico )
{
    if( id_tecnico <= 0 ) { return; }
    if( !_agregando ) {
        /// @TODO: Agregar registro de cambio de técnico.
    }
}

/*!
 * \brief FormOrdenTrabajo::cerrarOrden
 */
void FormOrdenTrabajo::cerrarOrden()
{
    /// @TODO: Agregar cierre de orden
}

/*!
 * \brief FormOrdenTrabajo::devolverCliente
 */
void FormOrdenTrabajo::devolverCliente()
{
    /// @TODO: Agregar devolución al cliente
}

/*!
 * \brief FormOrdenTrabajo::agregarFacturacion
 */
void FormOrdenTrabajo::agregarFacturacion()
{
    /// @TODO: Agregar facturación parcial
}

/*!
 * \brief FormOrdenTrabajo::eliminarFacturacion
 */
void FormOrdenTrabajo::eliminarFacturacion()
{
    /// @TODO: Agregar eliminar facturacion
}

/*!
 * \brief FormOrdenTrabajo::agregarHistorial
 */
void FormOrdenTrabajo::agregarHistorial()
{
    /// @TODO: Agregar agregar historial cualquiera
}

/*!
 * \brief FormOrdenTrabajo::eliminarHistorial
 */
void FormOrdenTrabajo::eliminarHistorial()
{
    /// @TODO: Agregar eliminar Historial
}

/*!
 * \brief FormOrdenTrabajo::facturarOrden
 */
void FormOrdenTrabajo::facturarOrden()
{
    /// @TODO: Agregar facturar orden
}

/*!
 * \brief FormOrdenTrabajo::imprimir
 */
void FormOrdenTrabajo::imprimir()
{
    /// @TODO: Agregar impresion de orden de trabajo
}

/*!
 * \brief FormOrdenTrabajo::pdf
 */
void FormOrdenTrabajo::pdf()
{
    /// @TODO: Agregar creación de pdf de la orden de trabajo
}

/*!
 * \brief FormOrdenTrabajo::cancelar
 */
void FormOrdenTrabajo::cancelar()
{
    /// @TODO: Agregar cancelación de la orden de trabajo
}

/*!
 * \brief FormOrdenTrabajo::guardar
 */
void FormOrdenTrabajo::guardar()
{
    /// @TODO: Agregar guardado de la orden de trabajo
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

/*!
 * \brief FormOrdenTrabajo::cargarDatosEquipamiento
 */
void FormOrdenTrabajo::cargarDatosEquipamiento()
{
    LEEquipamientoDescripcion->setText( _modelo_equipamiento->descripcion() );
    //CBEquipamientoMarca->setCurrentText( _modelo_equipamiento->marca() ); /// @TODO Ver como resolver esto
    LEEquipamientoModelo->setText( _modelo_equipamiento->modelo() );
    LEEquipamientoNumeroSerie->setText( _modelo_equipamiento->numeroSerie() );
    PTEEquipamientoObservaciones->setPlainText( _modelo_equipamiento->observaciones() );
    CkBEquipamientoGarantia->setChecked( _modelo_equipamiento->enGarantia() );
}

