#include "vrecibosimpagos.h"

VRecibosImpagos::VRecibosImpagos(QWidget *parent) :
EVLista( parent )
{
    this->setWindowTitle( "Recibos Impagos" );
    this->setWindowIcon( QIcon( ":/imagenes/recibos.png" ) );
    this->setObjectName( "recibos_impagos" );
}
