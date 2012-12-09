#include "vtecnicos.h"

#include "mtecnicos.h"
#include "eactcerrar.h"

#include <QTableView>

VTecnicos::VTecnicos(QWidget *parent) :
EVLista(parent)
{
    this->setObjectName("VistaTecnicos");
    this->setWindowTitle( "Tecnicos" );
    this->setWindowIcon( QIcon( ":/imagenes/tecnico.png" ) );

    modelo = new MTecnicos();
    vista->setModel( modelo );

    modelo->select();

    ActAgregar->setStatusTip( "Agregar nuevo técnico al sistema" );
    ActModificar->setStatusTip( "Modificar dato de un técnico" );

    this->addAction( ActAgregar );
    this->addAction( ActModificar );
    this->addAction( ActEliminar );
    this->addAction( new EActCerrar( this ) );
}

/*!
 * \fn VTecnicos::agregar()
 * Agrega un nuevo tecnico a la lista
 */
void VTecnicos::agregar(){
    qWarning( "No Implementado todavía" );
}

/*!
 * \fn VTecnicos::modificar()
 * Modifica el técnico que esté seleccionado
 **/
void VTecnicos::modificar()
{ qWarning( "No Implementado todavía" ); }

/*!
 * \fn VTecnicos::eliminar()
 * Verifica si se puede eliminar un tecnico
 */
void VTecnicos::eliminar()
{ qWarning( "No implementado todavía" ); }