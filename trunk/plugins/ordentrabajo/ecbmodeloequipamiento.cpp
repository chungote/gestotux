#include "ecbmodeloequipamiento.h"

ECBModeloEquipamiento::ECBModeloEquipamiento( QWidget *parent ) :
ECBTabla(parent)
{
    this->setObjectName("CBModelosEquipamiento");
    this->setearTabla( "equipamiento" );
    this->setearCampoId( "DISTINCT modelo" );
    this->setearCampoTexto( "DISTINCT modelo" );
    this->setearCampoOrden( "DISTINCT modelo" );
}
