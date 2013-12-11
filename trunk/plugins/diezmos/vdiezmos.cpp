#include "vdiezmos.h"

#include <QTableView>
#include "mdiezmos.h"

VDiezmos::VDiezmos( QWidget *parent ) :
EVLista(parent)
{
    setObjectName( "visor_diezmos" );
    setWindowTitle( "Diezmos" );
    //setWindowIcon( QIcon( ":/imagenes/diezmos.png" ) );

    modelo = new MDiezmos( this );

    vista->setModel( modelo );
    modelo->select();

    vista->hideColumn( 0 );
    vista->hideColumn( modelo->fieldIndex( "id_referencia" ) );

    addAction( ActCerrar );
}
