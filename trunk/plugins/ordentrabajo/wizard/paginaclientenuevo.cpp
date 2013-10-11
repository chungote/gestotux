#include "paginaclientenuevo.h"

#include "ordentrabajowizard.h"
#include "mestadofiscal.h"
#include "preferencias.h"
#include "paginacliente.h"

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

    // Cargo los datos del combo box de la pagina anterior
    LERazonSocial->setText( qobject_cast<PaginaCliente *>(wizard()->page( OrdenTrabajoWizard::Pagina_Cliente ))->clienteIngresado() );

    // Cargo los datos predeterminados
    preferencias *p = preferencias::getInstancia();
    p->inicio(); p->beginGroup( "Preferencias" ); p->beginGroup( "Clientes" );
    CBInscripcion->setCurrentIndex( p->value( "estado-fiscal" ).toInt() );
    p->endGroup(); p->endGroup(); p=0;
}

int PaginaClienteNuevo::nextId() const
{
    return OrdenTrabajoWizard::Pagina_Equipamiento;
}

void PaginaClienteNuevo::rehacerRazonSocial( QString )
{
    LERazonSocial->setText( LEApellido->text() + ", " + LENombre->text() );
}
