#include "DPagoCuota.h"

#include "mplancuota.h"

DPagoCuota::DPagoCuota(QWidget *parent) :
QDialog(parent)
{
    setupUi(this);
    this->setWindowTitle( QString::fromUtf8( "Ingresar pago de cuota" ) );
    this->setWindowIcon( QIcon( ":/imagenes/ingresar_pago.png" ) );
    this->setObjectName( "dialogo_pago_cuota" );

    _id_plan_cuota = -1;
    _model = 0;
}

/*!
 * \brief DPagoCuota::setearPlanCuota
 * Setea el identificador del plan de cuota del cual se desea ingresar el pago.
 * \param id_plan_cuota Identificador del plan de cuota
 */
void DPagoCuota::setearPlanCuota( const int id_plan_cuota )
{
    if( id_plan_cuota > 0 )
    {
      this->_id_plan_cuota = id_plan_cuota;
        if( this->_model != 0 )
            this->cargarDatos();
    } else {
        qDebug( "DPagoCuota::setearPlanCuota:: Id plan de cuota incorrecto < 0 " );
    }
}

/*!
 * \brief DPagoCuota::setearModelo
 * Setea el modelo de planes de cuotas que hay que actualizar luego de ingresar el pago
 * \param m Modelo de la clase MVPlanCuota
 */
void DPagoCuota::setearModelo( MVPlanCuota *m )
{
    if( m != 0 ) {
        this->_model = m;
        if( this->_id_plan_cuota > 0 )
            this->cargarDatos();
    } else {
        qDebug( "DPagoCuotas::setearModelo: Puntero a modelo incorrecto" );
    }
}

void DPagoCuota::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
        case QEvent::LanguageChange:
            retranslateUi(this);
            break;
        default:
            break;
    }
}

/*!
 * \brief DPagoCuota::cargarDatos
 * Carga los datos para el sistema.
 */
void DPagoCuota::cargarDatos()
{
    this->LRazonSocial->setText( MPlanCuota::obtenerRazonSocial( this->_id_plan_cuota ) );
    QPair<int,int> estado_cuotas = MPlanCuota::obtenerEstadoCuotas( this->_id_plan_cuota );
    this->LCDNTotal->display( estado_cuotas.first );
    this->LCDNPagadas->display( estado_cuotas.second );
    QPair<double,double> estado_plata = MPlanCuota::obtenerEstadoImportes( this->_id_plan_cuota );
    double porcentaje = ( estado_plata.first * 100 ) / estado_plata.second;
    this->PrBProgreso->setValue( porcentaje );
    this->DSBImporte->setValue( estado_plata.second );
    this->DSBPagado->setValue( estado_plata.first );
}
