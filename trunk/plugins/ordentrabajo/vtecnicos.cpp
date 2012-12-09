#include "vtecnicos.h"

#include "mtecnicos.h"
#include "eactcerrar.h"
#include "dsino.h"

#include <QTableView>

VTecnicos::VTecnicos(QWidget *parent) :
EVLista(parent)
{
    this->setObjectName("VistaTecnicos");
    this->setWindowTitle( "Tecnicos" );
    this->setWindowIcon( QIcon( ":/imagenes/tecnico.png" ) );

    modelo = new MTecnicos( this->vista );
    this->vista->setModel( this->modelo );

    this->vista->hideColumn( 0 ); // Oculta el ID del modelo
    this->vista->setAlternatingRowColors( true );
    this->vista->setSortingEnabled( true );
    this->vista->setItemDelegateForColumn( 2, new DSiNo( this->vista ) ); // Campo Booleano

    ActAgregar->setStatusTip( "Agregar nuevo técnico al sistema" );
    ActModificar->setStatusTip( "Modificar dato de un técnico" );

    this->addAction( ActAgregar );
    this->addAction( ActModificar );
    this->addAction( ActEliminar );
    this->addAction( new EActCerrar( this ) );

    this->modelo->select();
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