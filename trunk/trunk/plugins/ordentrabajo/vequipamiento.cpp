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

    addAction( ActCerrar );
}
