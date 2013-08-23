#include "vordentrabajo.h"

VOrdenTrabajo::VOrdenTrabajo(QWidget *parent) :
EVLista(parent)
{
    this->setObjectName( "visor_ordenes_trabajo" );
    this->setWindowTitle( "Ordenes de trabajo" );
    this->setWindowIcon( QIcon( ":/imagenes/ordentrabajo.png" ) );
}
