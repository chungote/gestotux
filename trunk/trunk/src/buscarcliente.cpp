#include "buscarcliente.h"

BuscarCliente::BuscarCliente( QWidget *parent, MClientes *m ) :
    QDockWidget(parent)
{
    setupUi(this);
    this->modelo = m;

    CBTipo->insertItem( 0, "Cualquiera" );
    CBTipo->insertItem( 1, "Numero de cliente" );
    CBTipo->insertItem( 2, "Razon social" );
    CBTipo->insertItem( 3, "CUIT/CUIL");

    connect( CBTipo, SIGNAL( currentIndexChanged( int ) ), this, SLOT( cambioTipo( int ) ) );
    connect( LETexto, SIGNAL( returnPressed() ), this, SLOT( cambioTexto() ) );
    connect( PBBorrar, SIGNAL( clicked() ), this, SLOT( borrar() ) );

    this->setWindowTitle( "Buscar clientes" );
}

void BuscarCliente::changeEvent(QEvent *e)
{
    QDockWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    case QEvent::Close:
        borrar();
        break;
    default:
        break;
    }
}


void BuscarCliente::cambioTipo( int indice )
{
    this->_tipo = indice;
    filtrar();
}

void BuscarCliente::cambioTexto()
{
    this->_texto = this->LETexto->text();
    filtrar();
}

void BuscarCliente::filtrar()
{
    switch( _tipo )
    {
        case 0:
        {
            // Cualquier campo
            this->modelo->setFilter( QString(
                    "WHERE razon_social = '%%1%' OR nombre = '%%1%' OR apellido = '%%' OR calle = '%%1%' "
                    " OR numero  = '%%1%' OR piso  = '%%1%' OR depto = '%%1%' OR ciudad = '%%1%' "
                    " OR codigo_postal = '%%1%' OR provincia = '%%1%' OR pais = '%%1%' OR tel_fijo = '%%1%'"
                    " OR tel_celular = '%%1%' OR fax = '%%1%' OR email = '%%1%' OR 'CUIT/CUIL' = '%%1%'"
                    ).arg( this->_texto ) );
            break;
        }
        case 1:
        {
            // Numero de cliente
            this->modelo->setFilter( QString( " numero_cliente = %1" ).arg( this->_texto ) );
            this->modelo->select();
            break;
        }
        case 2:
        {
            // Razon social
            this->modelo->setFilter( QString( " razon_social = '%%1%'" ).arg( this->_texto ) );
            this->modelo->select();
            break;
        }
        case 3:
        {
            // CUIT/CUIL
            this->modelo->setFilter( QString( " `CUIT/CUIL` = %1" ).arg( this->_texto ) );
            this->modelo->select();
            break;
        }
    }
}

void BuscarCliente::borrar()
{
    this->LETexto->clear();
    this->CBTipo->setCurrentIndex( -1 );
    this->modelo->setFilter( "" );
    this->modelo->select();
}
