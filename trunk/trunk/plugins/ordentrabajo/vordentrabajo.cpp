#include "vordentrabajo.h"

#include "eactcerrar.h"
#include "mordentrabajo.h"

#include <QTableView>

VOrdenTrabajo::VOrdenTrabajo(QWidget *parent) :
EVLista(parent)
{
    setObjectName( "visor_ordenes_trabajo" );
    setWindowTitle( "Ordenes de trabajo" );
    setWindowIcon( QIcon( ":/imagenes/ordentrabajo.png" ) );

    modelo = new MOrdenTrabajo( this );

    vista->setModel( modelo );
    vista->hideColumn( modelo->fieldIndex( "id_equipamiento" ) );
    modelo->select();

    addAction( new EActCerrar( this ) );

}

