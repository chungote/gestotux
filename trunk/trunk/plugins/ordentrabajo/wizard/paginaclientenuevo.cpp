#include "paginaclientenuevo.h"

#include "ordentrabajowizard.h"
#include "mestadofiscal.h"

PaginaClienteNuevo::PaginaClienteNuevo( QWidget *parent ) :
QWizardPage( parent )
{
    setupUi(this);

    connect( LENombre, SIGNAL( textChanged( QString ) ), this, SLOT( rehacerRazonSocial( QString ) ) );
    connect( LEApellido, SIGNAL( textChanged( QString ) ), this, SLOT( rehacerRazonSocial( QString ) ) );

    registerField( "cliente.razonsocial*", LERazonSocial );
    registerField( "cliente.nombre", LENombre );
    registerField( "cliente.apellido", LEApellido );
    registerField( "cliente.direccion*", LEDireccion );
    registerField( "cliente.inscripcion", CBInscripcion );
    registerField( "cliente.telefono", LETelefono );

    CBInscripcion->setModel( new MEstadoFiscal( CBInscripcion ) );
}

int PaginaClienteNuevo::nextId() const
{
    return OrdenTrabajoWizard::Pagina_Equipamiento;
}

void PaginaClienteNuevo::rehacerRazonSocial( QString )
{
    LERazonSocial->setText( LEApellido->text() + ", " + LENombre->text() );
}
