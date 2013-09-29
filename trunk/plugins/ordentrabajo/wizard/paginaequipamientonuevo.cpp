#include "paginaequipamientonuevo.h"

#include "ordentrabajowizard.h"

PaginaEquipamientoNuevo::PaginaEquipamientoNuevo(QWidget *parent) :
    QWizardPage(parent)
{
    setupUi( this );

    registerField( "equipamiento.descripcion*", LEDescripcion );
    registerField( "equipamiento.modelo", LEModelo );
    registerField( "equipamiento.marca*", LEMarca );
    registerField( "equipamiento.observaciones", PTEObservaciones );
    registerField( "equipamiento.numeroserie", LENumeroSerie );
}

int PaginaEquipamientoNuevo::nextId() const
{
    return OrdenTrabajoWizard::Pagina_Final;
}

