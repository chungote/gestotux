#include "vgarantias.h"

#include <QTableView>

VGarantias::VGarantias(QWidget *parent) :
    EVLista(parent)
{

    setObjectName( "visor-garantias" );

    modelo = new MGarantias( this );

    vista->setModel( modelo );
    vista->hideColumn( 0 );

    modelo->select();
}
