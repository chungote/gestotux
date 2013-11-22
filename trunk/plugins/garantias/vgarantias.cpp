#include "vgarantias.h"

#include <QTableView>

VGarantias::VGarantias(QWidget *parent) :
    EVLista(parent)
{

    setObjectName( "visor-garantias" );
    setWindowTitle( QString::fromUtf8( "Garantías activas" ) );
    //setWindowIcon( QIcon( ":/imagenes/garantias.png" ) );

    modelo = new MGarantias( this );

    vista->setModel( modelo );
    vista->hideColumn( 0 );

    modelo->select();
}
