#include "formfacturacionemitida.h"

#include "mservicios.h"
#include "mperiodoservicio.h"
#include "eactcerrar.h"

#include <QSqlQueryModel>
#include <QMessageBox>

FormFacturacionEmitida::FormFacturacionEmitida(QWidget *parent) :
    EVentana(parent)
{
    setupUi(this);
    setObjectName( "visor-facturacion-servicio" );
    setWindowTitle( "Facturación emitida de servicio" );

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

    TVDeudor->setModel( mdeudor );
    TVPagada->setModel( mpagado );

    connect( CBServicio, SIGNAL( cambioId( int ) ), this, SLOT( cambioServicio( int ) ) );
    connect( CBPeriodo , SIGNAL( cambioId( int ) ), this, SLOT( cambioPeriodo(  int ) ) );

    addAction( new EActCerrar( this ) );
}

void FormFacturacionEmitida::setearIdServicio( const int id_servicio )
{
    _id_servicio = id_servicio;
    //qDebug( QString( "Seteado id_servicio = %1" ).arg( id_servicio ).toLocal8Bit() );
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
    CBPeriodo->setearId( _id_periodo_servicio );
    cargarDatos();
}

void FormFacturacionEmitida::cargarDatos()
{
    mdeudor->setQuery( QString( "SELECT "
                                /*" cscp.id_periodo_servicio,"
                                " cscp.id_cliente, "
                                " cscp.id_factura, "*/
                                " c.razon_social, "
                                " f.total "
                                "FROM `cobro_servicio_cliente_periodo` AS cscp, `clientes` AS c, `factura` AS f"
                                "WHERE cscp.id_cliente = c.id "
                                " AND cscp.id_factura = f.id_factura "
                                " AND cscp.id_servicio = %1 "
                                " AND cscp.id_periodo_servicio = %2 "
                                " AND cscp.id_recibo IS NULL" ).arg( _id_servicio ).arg( _id_periodo_servicio ) );
   mpagado->setQuery( QString( "SELECT "
                                /*" cscp.id_periodo_servicio,"
                                " cscp.id_cliente, "
                                " cscp.id_factura, "*/
                                " c.razon_social, "
                                " f.total "
                                "FROM `cobro_servicio_cliente_periodo` AS cscp, `clientes` AS c, `factura` AS f"
                                "WHERE cscp.id_cliente = c.id "
                                " AND cscp.id_factura = f.id_factura "
                                " AND cscp.id_servicio = %1 "
                                " AND cscp.id_periodo_servicio = %2 "
                                " AND cscp.id_recibo IS NOT NULL" ).arg( _id_servicio ).arg( _id_periodo_servicio ) );
}
