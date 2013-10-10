#include "paginacliente.h"

#include <QVBoxLayout>

#include "mclientes.h"
#include "ordentrabajowizard.h"

PaginaCliente::PaginaCliente(QWidget *parent) :
    QWizardPage(parent)
{
    setTitle( "Seleccione el cliente");
    //setPixmap( QWizard::WatermarkPixmap, QPixmap( ":/images/watermark.png" ) );

    arriba = new QLabel( this );
    arriba->setText( "Este dialogo le ayudará en la creación de una nueva orden de trabajo. <br />Por favor, seleccione un cliente." );
    arriba->setWordWrap(true);

    CBClientes = new ECBClientes( this );
    CBClientes->setEditable( true );

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(arriba);
    layout->addWidget(CBClientes);
    setLayout(layout);

    // Asocio el valor con el identificador del cliente
    registerField( "cliente.id_cliente", CBClientes );
}

/*!
 * \brief PaginaCliente::nextId
 * \return
 */
int PaginaCliente::nextId() const
{
    if( MClientes::existe( CBClientes->currentText(), QString() ) ) {
        return OrdenTrabajoWizard::Pagina_Equipamiento;
    } else {
        return OrdenTrabajoWizard::Pagina_ClienteNuevo;
    }
}