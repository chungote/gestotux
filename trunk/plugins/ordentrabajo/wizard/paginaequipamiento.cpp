#include "paginaequipamiento.h"

#include "ordentrabajowizard.h"

PaginaEquipamiento::PaginaEquipamiento(QWidget *parent) :
    QWizardPage(parent)
{
    setupUi(this);

    // Busco si se paso por la info de nuevo cliente
    if( wizard()->hasVisitedPage( OrdenTrabajoWizard::Pagina_ClienteNuevo ) ) {
        RBExistente->setEnabled( false );
        RBNuevo->setChecked( true );
    } else {
        // Buscar si el cliente actual tiene algún equipamiento
        /// @TODO: Buscar la existencia de un equipamiento según cliente
        if( !true ) {
            RBExistente->setEnabled( false );
            RBNuevo->setChecked( true );
        }
    }

    registerField( "equipamiento.existe", RBExistente );
    registerField( "equipamiento.nuevo", RBNuevo );
}

int PaginaEquipamiento::nextId()
{
    if( RBExistente->isChecked() ) {
        return OrdenTrabajoWizard::Pagina_EquipamientoExistente;
    } else {
        return OrdenTrabajoWizard::Pagina_EquipamientoNuevo;
    }
}