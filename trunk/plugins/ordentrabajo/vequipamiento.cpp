#include "vequipamiento.h"

#include "mequipamiento.h"
#include "formequipamiento.h"

#include <QTableView>

VEquipamiento::VEquipamiento(QWidget *parent) :
EVLista( parent )
{
    this->setObjectName( "VisorEquipamiento" );
    this->setWindowTitle( "Equipamientos" );
    this->setWindowIcon( QIcon( ":/imagenes/equipamiento.png" ) );

    this->modelo = new MEquipamiento( this );
    this->vista->setModel( this->modelo );
    this->vista->setSelectionBehavior( QAbstractItemView::SelectRows );
    this->vista->setAlternatingRowColors( true );
    this->vista->hideColumn( modelo->fieldIndex( "id_equipamiento" ) );
    this->vista->hideColumn( modelo->fieldIndex( "num_serie" ) );
    this->vista->hideColumn( modelo->fieldIndex( "fecha_baja" ) );
    this->vista->hideColumn( modelo->fieldIndex( "razon_baja" ) );
    this->vista->hideColumn( modelo->fieldIndex( "fecha_compra" ) );
    this->vista->hideColumn( modelo->fieldIndex( "modelo" ) );
    this->vista->hideColumn( modelo->fieldIndex( "marca" ) );
    this->vista->setSortingEnabled( true );
    this->modelo->select();

    addAction( ActAgregar );
    addAction( ActModificar );
    addAction( ActEliminar );
    addAction( ActCerrar );
}

void VEquipamiento::agregar( bool )
{
    FormEquipamiento *f = new FormEquipamiento();
    f->setearModeloEquipamiento( qobject_cast<MEquipamiento *>( this->modelo ) );
    f->setearAgregar( true );
    emit agregarVentana( f );
}

void VEquipamiento::modificar()
{ qWarning( "No implementado" ); }

void VEquipamiento::eliminar()
{ qWarning( "No implementado" ); }
