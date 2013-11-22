#include "vordentrabajo.h"

#include "eactcerrar.h"
#include "eactimprimir.h"
#include "eactpdf.h"
#include "mordentrabajo.h"

#include <QTableView>
#include <QMenu>

VOrdenTrabajo::VOrdenTrabajo(QWidget *parent) :
EVLista(parent)
{
    setObjectName( "visor_ordenes_trabajo" );
    setWindowTitle( "Ordenes de trabajo" );
    setWindowIcon( QIcon( ":/imagenes/orden_trabajo.png" ) );

    modelo = new MOrdenTrabajo( this );

    vista->setModel( modelo );
    vista->hideColumn( modelo->fieldIndex( "id_equipamiento" ) );
    modelo->select();

    ActVer = new QAction( this );
    ActVer->setText( "Ver" );
    ActVer->setStatusTip( "Muestra la información de una orden de trabajo" );
    ActVer->setIcon( QIcon( ":/imagenes/detalle_orden_trabajo.png" ) );
    connect( ActVer, SIGNAL( triggered() ), this, SLOT( ver() ) );

    ActAgregar->setIcon( QIcon( ":/imagenes/crear_orden_trabajo.png" ) );

    addAction( ActAgregar );
    addAction( ActVer );
    addAction( ActModificar );
    addAction( ActEliminar );
    addAction( ActImprimir );
    addAction( ActPdf );
    addAction( ActVerTodos );
    addAction( ActCerrar );
}

/*!
 * \brief VOrdenTrabajo::agregar
 * \param autoeliminarid
 */
void VOrdenTrabajo::agregar( bool )
{
}

/*!
 * \brief VOrdenTrabajo::modificar
 */
void VOrdenTrabajo::modificar()
{
}

/*!
 * \brief VOrdenTrabajo::eliminar
 */
void VOrdenTrabajo::eliminar()
{
}

/*!
 * \brief VOrdenTrabajo::ver
 */
void VOrdenTrabajo::ver()
{
}

/*!
 * \brief VOrdenTrabajo::aPdf
 * Manda a pdf la orden de trabajo
 */
void VOrdenTrabajo::aPdf()
{
}

/*!
 * \brief VOrdenTrabajo::imprimir
 * Manda a imprimir la orden de trabajo seleccionada
 */
void VOrdenTrabajo::imprimir()
{
}


/*!
 * \brief VOrdenTrabajo::menuContextual
 * Genera el menu contextual dependiendo de el item seleccionado
 * \param indice Indice seleccionado
 * \param menu Menu a utilizar
 */
void VOrdenTrabajo::menuContextual( const QModelIndex &indice, QMenu *menu )
{
    if( indice.isValid() ) {
        menu->addAction( ActVer );
        menu->addAction( ActModificar );
        menu->addAction( ActEliminar );
        menu->addAction( ActPdf );
        menu->addAction( ActImprimir );
        menu->addSeparator();
    }
    menu->addAction( ActAgregar );
    return;
}
