#include "formfacturacionemitida.h"

#include "mservicios.h"
#include "mperiodoservicio.h"
#include "eactcerrar.h"
#include "EReporte.h"
#include "eregistroplugins.h"

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>

FormFacturacionEmitida::FormFacturacionEmitida(QWidget *parent) :
    EVentana(parent)
{
    setupUi(this);
    setObjectName( "visor-facturacion-servicio" );
    setWindowTitle( QString::fromUtf8( "Facturación emitida de servicio" ) );

    // Cargo los servicios
    CBServicio->setearTabla( "servicios" );
    CBServicio->setearCampoId( "id_servicio" );
    CBServicio->setearCampoTexto( "nombre" );

    CBPeriodo->setearTabla( "periodo_servicio" );
    CBPeriodo->setearCampoId( "id_periodo_servicio" );
    if( QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).driverName() == "QMYSQL" ) {
        CBPeriodo->setearCampoTexto( "CONCAT( periodo, '/', ano )" );
    } else {
        CBPeriodo->setearCampoTexto( " periodo || '/' || ano " );
    }

    mdeudor = new QSqlQueryModel( this );
    mpagado = new QSqlQueryModel( this );

    mdeudor->setHeaderData( 0, Qt::Horizontal, QString::fromUtf8( "Razón Social" ) );
    mdeudor->setHeaderData( 1, Qt::Horizontal, "Importe" );

    mpagado->setHeaderData( 0, Qt::Horizontal, QString::fromUtf8( "Razón Social" ) );
    mpagado->setHeaderData( 1, Qt::Horizontal, "Importe" );

    TVDeudor->setModel( mdeudor );
    TVDeudor->setAlternatingRowColors( true );
    TVDeudor->setSortingEnabled( true );
    TVDeudor->setSelectionMode( QAbstractItemView::SingleSelection );
    TVDeudor->setSelectionBehavior( QAbstractItemView::SelectRows );
    TVDeudor->horizontalHeader()->setResizeMode( QHeaderView::ResizeToContents );
    TVDeudor->horizontalHeader()->setResizeMode( 0, QHeaderView::Stretch );
    TVDeudor->setTextElideMode( Qt::ElideRight );

    TVPagada->setModel( mpagado );
    TVPagada->setSelectionMode( QAbstractItemView::SingleSelection );
    TVPagada->setSelectionBehavior( QAbstractItemView::SelectRows );
    TVPagada->horizontalHeader()->setResizeMode( QHeaderView::ResizeToContents );
    TVPagada->horizontalHeader()->setResizeMode( 0, QHeaderView::Stretch );
    TVPagada->setTextElideMode( Qt::ElideRight );
    TVPagada->setAlternatingRowColors( true );
    TVPagada->setSortingEnabled( true );

    connect( CBServicio, SIGNAL( cambioId( int ) ), this, SLOT( cambioServicio( int ) ) );
    connect( CBPeriodo , SIGNAL( cambioId( int ) ), this, SLOT( cambioPeriodo(  int ) ) );

    ActVerPagado = new QAction( this );
    ActVerPagado->setCheckable( true );
    ActVerPagado->setChecked( false );
    ActVerPagado->setText( "Ver pagados" );
    connect( ActVerPagado, SIGNAL( toggled( bool ) ), this, SLOT( cambioHabilitadoPagados( bool ) ) );

    ActListadoGeneral = new QAction( this );
    ActListadoGeneral->setText( "Listado Deudores" );
    ActListadoGeneral->setIcon( QIcon( ":/imagenes/imprimir.png" ) );
    ActListadoGeneral->setStatusTip( "Imprime un listado de todos los deudores de todos los periodos del servicio seleccionado" );
    connect( ActListadoGeneral, SIGNAL( triggered() ), this, SLOT( imprimirListadoGeneral() ) );

    ActListadoGeneralPDF = new QAction( this );
    ActListadoGeneralPDF->setText( "Listado Deudores" );
    ActListadoGeneralPDF->setIcon( QIcon( ":/imagenes/acroread.png" ) );
    ActListadoGeneralPDF->setStatusTip( "Imprime un listado de todos los deudores de todos los periodos del servicio seleccionado" );
    connect( ActListadoGeneralPDF, SIGNAL( triggered() ), this, SLOT( imprimirListadoGeneralPDF() ) );

    GBPagado->setVisible( ActVerPagado->isChecked() );

    addAction( ActListadoGeneral );
    addAction( ActListadoGeneralPDF );
    addAction( ActVerPagado );
    addAction( new EActCerrar( this ) );
}

void FormFacturacionEmitida::setearIdServicio( const int id_servicio )
{
    _id_servicio = id_servicio;
    CBServicio->setearId( id_servicio );
    CBPeriodo->setearFiltro( QString( " WHERE id_servicio = %1" ).arg( _id_servicio ) );
}

void FormFacturacionEmitida::setearIdPeriodo( const int id_periodo )
{
    _id_periodo_servicio = id_periodo;
    CBPeriodo->setearId( id_periodo );
    cargarDatos();
}

void FormFacturacionEmitida::changeEvent(QEvent *e)
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

void FormFacturacionEmitida::cambioServicio( int id_servicio )
{
  _id_servicio = id_servicio;
  CBPeriodo->setearFiltro( QString(" WHERE id_servicio = %1" ).arg( _id_servicio ) );
  this->mpagado->clear();
  this->mdeudor->clear();
}

void FormFacturacionEmitida::cambioPeriodo( int id_periodo )
{
    _id_periodo_servicio = id_periodo;
    //CBPeriodo->setearId( _id_periodo_servicio );
    cargarDatos();
}

void FormFacturacionEmitida::cargarDatos()
{
    if( ERegistroPlugins::getInstancia()->existePluginExterno( "hicomp" ) ) {
        mdeudor->setQuery( QString( "SELECT c.razon_social, "
                                    "       r.precio "
                                    "FROM `cobro_servicio_cliente_periodo` AS cscp, `clientes` AS c, `recibos` AS r "
                                    "WHERE cscp.id_cliente = c.id "
                                    "  AND cscp.id_factura = r.id_recibo "
                                    "  AND cscp.id_servicio = %1 "
                                    "  AND cscp.id_periodo_servicio = %2 "
                                    "  AND cscp.id_recibo IS NULL" ).arg( _id_servicio ).arg( _id_periodo_servicio ) );
    } else {
        mdeudor->setQuery( QString( "SELECT c.razon_social, "
                                    "       f.total "
                                    "FROM `cobro_servicio_cliente_periodo` AS cscp, `clientes` AS c, `factura` AS f "
                                    "WHERE cscp.id_cliente = c.id "
                                    "  AND cscp.id_factura = f.id_factura "
                                    "  AND cscp.id_servicio = %1 "
                                    "  AND cscp.id_periodo_servicio = %2 "
                                    "  AND cscp.id_recibo IS NULL" ).arg( _id_servicio ).arg( _id_periodo_servicio ) );
    }
    qDebug( mdeudor->query().lastQuery().toLocal8Bit() );
}

void FormFacturacionEmitida::cambioHabilitadoPagados( bool estado )
{
    if( estado ) {
        GBPagado->setVisible( true );
        if( ERegistroPlugins::getInstancia()->existePluginExterno( "hicomp" ) ) {
            mpagado->setQuery( QString( "SELECT "
                                     " c.razon_social, "
                                     " r.precio "
                                     "FROM `cobro_servicio_cliente_periodo` AS cscp, `clientes` AS c, `recibo` AS r "
                                     "WHERE cscp.id_cliente = c.id "
                                     " AND cscp.id_factura = r.id_recibo "
                                     " AND cscp.id_servicio = %1 "
                                     " AND cscp.id_periodo_servicio = %2 "
                                     " AND cscp.id_recibo IS NOT NULL" ).arg( _id_servicio ).arg( _id_periodo_servicio ) );
        } else {
            mpagado->setQuery( QString( "SELECT "
                                     " c.razon_social, "
                                     " f.total "
                                     "FROM `cobro_servicio_cliente_periodo` AS cscp, `clientes` AS c, `factura` AS f "
                                     "WHERE cscp.id_cliente = c.id "
                                     " AND cscp.id_factura = f.id_factura "
                                     " AND cscp.id_servicio = %1 "
                                     " AND cscp.id_periodo_servicio = %2 "
                                     " AND cscp.id_recibo IS NOT NULL" ).arg( _id_servicio ).arg( _id_periodo_servicio ) );
        }
        qDebug( mpagado->query().lastQuery().toLocal8Bit() );
    } else {
        mpagado->clear();
        GBPagado->setVisible( false );
    }
}

void FormFacturacionEmitida::imprimirListadoGeneral()
{
    // Busco el id que está del servicio
    EReporte *rep = new EReporte( 0 );
    ParameterList lista;
    lista.append( "id_servicio", CBServicio->idActual() );
    if( ERegistroPlugins::getInstancia()->existePluginExterno( "hicomp" ) ) {
        rep->especial( "ListadoDeudoresServiciosHC", lista );
    } else {
        rep->especial( "ListadoDeudoresServicios", lista );
    }
    rep->hacer();
    delete rep;
}

void FormFacturacionEmitida::imprimirListadoGeneralPDF()
{
    // Busco el id que está del servicio
    EReporte *rep = new EReporte( 0 );
    ParameterList lista;
    int id_servicio = CBServicio->idActual();
    lista.append( "id_servicio", id_servicio );
    if( ERegistroPlugins::getInstancia()->existePluginExterno( "hicomp" ) ) {
        rep->especial( "ListadoDeudoresServiciosHC", lista );
    } else {
        rep->especial( "ListadoDeudoresServicios", lista );
    }
    rep->hacerPDF( lista, QString( "Lista Deudores del servicio %1 al %2" ).arg( MServicios::getNombreServicio( id_servicio ) ).arg( QDate::currentDate().toString( Qt::SystemLocaleShortDate ) ) );
    delete rep;
}
