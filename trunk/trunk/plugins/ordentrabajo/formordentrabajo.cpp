#include "formordentrabajo.h"

#include <QDateTime>
#include <QMessageBox>
#include <QInputDialog>
#include <QComboBox>

#include "eactcerrar.h"
#include "eactguardar.h"
#include "mordentrabajo.h"
#include "mtipooperacionordentrabajo.h"
#include "dhistorialordentrabajo.h"

FormOrdenTrabajo::FormOrdenTrabajo( QWidget *parent ) :
EVentana( parent ), FormOrdenTrabajoBase()
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

//    connect( CBCliente, SIGNAL( cambioIdCliente( int ) ), this, SLOT( cambioCliente( int ) ) );
//    connect( CBTecnico, SIGNAL( cambioId( int ) ), this, SLOT( cambioTecnico( int ) ) );

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

    LNumeroOrdenTrabajo->setText( MOrdenTrabajo::numeroComprobanteProximo().aCadena() );
    _modelo_historial_facturacion->mostrarCostosSumados();
}

/*!
 * \brief FormOrdenTrabajo::setearIdOrdenTrabajo
 * \param id_orden_trabajo Identificador de la orden de trabajo a cargar
 */
void FormOrdenTrabajo::setearIdOrdenTrabajo( const int id_orden_trabajo )
{
    if( id_orden_trabajo <= 0 ) { return; }
    _id_orden_trabajo = id_orden_trabajo;

    TBGeneral->setItemEnabled( 2, true );
    TBGeneral->setItemEnabled( 3, true );

    // Cargo los datos
    _modelo_orden->cargarDatos( id_orden_trabajo );
    CBCliente->setearId( _modelo_orden->idCliente() );
    LEIngresante->setText( _modelo_orden->ingresante() );
    LERequerente->setText( _modelo_orden->requerente() );

    CBTecnico->setearId( _modelo_orden->idTecnico() );

    connect( CBCliente, SIGNAL( cambioIdCliente( int ) ), this, SLOT( cambioCliente( int ) ) );
    connect( CBTecnico, SIGNAL( cambioId( int ) ), this, SLOT( cambioTecnico( int ) ) );

    DEFechaDevolucion->setDateTime( _modelo_orden->fechaDevolucion() );
    DTEFechaIngreso->setDateTime( _modelo_orden->fechaIngreso() );

    // Historial de acciones
    _modelo_historial->setearOrdenTrabajo( id_orden_trabajo );
    _modelo_historial->mostrarCostosSumados( false );
    LVHistorial->setModel( _modelo_historial );
    _modelo_historial->select();

    // Modelo del historial de facturación

    _modelo_historial_facturacion->setearOrdenTrabajo( id_orden_trabajo );
    _modelo_historial_facturacion->mostrarCostosSumados( true );
    _modelo_historial_facturacion->setearRelacionTecnico();
    _modelo_historial_facturacion->setearRelacionTipo();
    TVFacturacion->setModel( _modelo_historial_facturacion );
    _modelo_historial_facturacion->select();

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
    // Ingreso el primer equipamiento del cliente
    if( _modelo_equipamiento->existeEquipamientoParaCliente( id_cliente ) ) {
        if( _modelo_equipamiento->cantidadEquipamientoParaCliente( id_cliente ) == 1 ) {
            _modelo_equipamiento->cargarDatos( _modelo_equipamiento->buscarIdEquipamientoSegunCliente( id_cliente ) );
            cargarDatosEquipamiento();
        } else {
            /// @TODO: Mostrar las opciones para elegir el equipamiento
        }
    }
}

/*!
 * \brief FormOrdenTrabajo::cambioTecnico
 * Slot llamado cuando se cambia el técnico de la orden de trabajo
 * \param id_tecnico
 */
void FormOrdenTrabajo::cambioTecnico( int id_tecnico )
{
    if( id_tecnico <= 0 ) { return; }

    bool ok = false;
    QString razon = QInputDialog::getText( this,
                                           QString::fromUtf8( "Dato necesario" ),
                                           QString::fromUtf8( "Ingrese razón de cambio de técnico" ),
                                           QLineEdit::Normal,
                                           QString(),
                                           &ok );
    if( ok && !razon.isEmpty() ) {
        // Busco el técnico actual
        int id_tecnico_actual = _modelo_orden->idTecnico();
        if( _modelo_historial->agregarHistorial( _id_orden_trabajo,
                                                 QDateTime::currentDateTime(),
                                                 QString( "Cambio de técnico responsable. Razón: %1" ).arg( razon ),
                                                 0.0,
                                                 MTipoOperacionOrdenTrabajo::CambioTecnico,
                                                 id_tecnico_actual )
            && _modelo_orden->cambiarTecnico( _id_orden_trabajo, id_tecnico ) ) {
            QMessageBox::information( this, "Correcto", QString::fromUtf8( "El técnico fue cambiado correctamente" ) );
            return;
        }
    }

}

/*!
 * \brief FormOrdenTrabajo::cerrarOrden
 */
void FormOrdenTrabajo::cerrarOrden()
{
    DHistorialOrdenTrabajo *diag = new DHistorialOrdenTrabajo( this );
    diag->setearModeloHistorial( _modelo_historial );
    diag->setearIdOrdenTrabajo( _id_orden_trabajo );
    diag->setearComoCierre();
    diag->exec();
}

/*!
 * \brief FormOrdenTrabajo::devolverCliente
 */
void FormOrdenTrabajo::devolverCliente()
{
    DHistorialOrdenTrabajo *diag = new DHistorialOrdenTrabajo( this );
    diag->setearModeloHistorial( _modelo_historial );
    diag->setearIdOrdenTrabajo( _id_orden_trabajo );
    diag->setearComoDevolverAlCliente();
    diag->exec();
}

/*!
 * \brief FormOrdenTrabajo::agregarFacturacion
 * Agrega la facturación de algun item a la orden de trabajo a futuro.
 */
void FormOrdenTrabajo::agregarFacturacion()
{
    DHistorialOrdenTrabajo *diag = new DHistorialOrdenTrabajo( this );
    diag->setearModeloHistorial( _modelo_historial );
    diag->setearIdOrdenTrabajo( _id_orden_trabajo );
    diag->setearComoFacturacion();
    diag->exec();
}

/*!
 * \brief FormOrdenTrabajo::eliminarFacturacion
 */
void FormOrdenTrabajo::eliminarFacturacion()
{
    if( TVFacturacion->selectionModel()->selectedRows().size() <= 0 ) {
        QMessageBox::information( this, "Error", "Por favor, seleccione algún elemento del historial para eliminar" );
        return;
    }
    int ret = QMessageBox::question( this,
                                     QString::fromUtf8( "¿Está seguro?" ),
                                     QString::fromUtf8("¿Está seguro que desea eliminar estos %1 elementos?" ).arg( TVFacturacion->selectionModel()->selectedRows().size() ),
                                     QMessageBox::Yes,
                                     QMessageBox::No );
    if( ret == QMessageBox::Yes ) {
        foreach( QModelIndex idx, TVFacturacion->selectionModel()->selectedRows() ) {
            int id_historial = idx.model()->data( idx.model()->index( idx.row(), 0 ), Qt::EditRole ).toInt();
            _modelo_historial_facturacion->eliminarHistorial( id_historial );
        }
    }
}

/*!
 * \brief FormOrdenTrabajo::agregarHistorial
 */
void FormOrdenTrabajo::agregarHistorial()
{
    DHistorialOrdenTrabajo *diag = new DHistorialOrdenTrabajo( this );
    diag->setearModeloHistorial( _modelo_historial );
    diag->setearIdOrdenTrabajo( _id_orden_trabajo );
    diag->setWindowTitle( "Agregar accion al historial" );
    diag->exec();
}

/*!
 * \brief FormOrdenTrabajo::eliminarHistorial
 */
void FormOrdenTrabajo::eliminarHistorial()
{
    if( LVHistorial->selectionModel()->selectedRows().size() <= 0 ) {
        QMessageBox::information( this, "Error", "Por favor, seleccione algún elemento del historial para eliminar" );
        return;
    }
    int ret = QMessageBox::question( this,
                                     QString::fromUtf8( "¿Está seguro?" ),
                                     QString::fromUtf8("¿Está seguro que desea eliminar estos %1 elementos?" ).arg( TVFacturacion->selectionModel()->selectedRows().size() ),
                                     QMessageBox::Yes,
                                     QMessageBox::No );
    if( ret == QMessageBox::Yes ) {
        foreach( QModelIndex idx, TVFacturacion->selectionModel()->selectedRows() ) {
            int id_historial = idx.model()->data( idx.model()->index( idx.row(), 0 ), Qt::EditRole ).toInt();
            _modelo_historial_facturacion->eliminarHistorial( id_historial );
        }
    }
}

/*!
 * \brief FormOrdenTrabajo::facturarOrden
 */
void FormOrdenTrabajo::facturarOrden()
{
  // Se facturará todo el costo que se haya acumulado en la orden de trabajo
  // Se parasará la orden de trabajo a cerrada ( si no lo está ya )
  // y se devolverá al cliente ( si no lo está ya )
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
    DHistorialOrdenTrabajo *diag = new DHistorialOrdenTrabajo( this );
    diag->setearModeloHistorial( _modelo_historial );
    diag->setearIdOrdenTrabajo( _id_orden_trabajo );
    diag->setearComoCancelacion();
    diag->exec();
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
    //CBEquipamientoMarca->setCurrentText( _modelo_equipamiento->marca() );
    LEEquipamientoModelo->setText( _modelo_equipamiento->modelo() );
    LEEquipamientoNumeroSerie->setText( _modelo_equipamiento->numeroSerie() );
    PTEEquipamientoObservaciones->setPlainText( _modelo_equipamiento->observaciones() );
    CkBEquipamientoGarantia->setChecked( _modelo_equipamiento->enGarantia() );
}

