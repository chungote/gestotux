#include "vequipamiento.h"

#include "mequipamiento.h"

#include <QTableView>

VEquipamiento::VEquipamiento(QWidget *parent) :
EVLista( parent )
{
    this->setObjectName( "VisorEquipamiento" );
    this->setWindowTitle( "Equipamientos" );
    //this->setWindowIcon( QIcon( ":/imagenes/equipamiento.png" ) );

    this->modelo = new MEquipamiento( this );
    this->vista->setModel( this->modelo );
    this->modelo->select();

    addAction( ActAgregar );
    addAction( ActModificar );
    addAction( ActEliminar );
    addAction( ActCerrar );
}

void VEquipamiento::agregar(bool autoeliminarid)
{ qWarning( "No implementado" ); }

void VEquipamiento::modificar()
{ qWarning( "No implementado" ); }

void VEquipamiento::eliminar()
{ qWarning( "No implementado" ); }
