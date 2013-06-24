#include "vequipamiento.h"

#include "mequipamiento.h"
#include "formequipamiento.h"

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

void VEquipamiento::agregar( bool )
{
    qWarning( "No implementado" );
    FormEquipamiento *f = new FormEquipamiento();
    f->setearModeloEquipamiento( qobject_cast<MEquipamiento *>( this->modelo ) );
    f->setearAgregar();
    emit agregarVentana( f );
}

void VEquipamiento::modificar()
{ qWarning( "No implementado" ); }

void VEquipamiento::eliminar()
{ qWarning( "No implementado" ); }
