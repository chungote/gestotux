#include "paginaequipamientoexistente.h"

#include "mequipamiento.h"
#include "ordentrabajowizard.h"

PaginaEquipamientoExistente::PaginaEquipamientoExistente(QWidget *parent) :
    QWizardPage(parent)
{
    setupUi(this);

    registerField( "equipamiento.id_equipamiento", TVEquipamientos );

    MEquipamiento *modelo = new MEquipamiento( TVEquipamientos );
    TVEquipamientos->setModel( modelo );
    TVEquipamientos->hideColumn( 0 );
    modelo->setFilter( QString( " id_cliente = %1 " ).arg( this->field("id_cliente").toInt() ) );
    modelo->select();
}

int PaginaEquipamientoExistente::nextId() const
{
    return OrdenTrabajoWizard::Pagina_Final;
}

