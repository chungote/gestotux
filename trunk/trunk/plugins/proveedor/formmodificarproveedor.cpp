#include "formmodificarproveedor.h"

#include "eactcerrar.h"
#include "eactguardar.h"

FormModificarProveedor::FormModificarProveedor( MProveedor *m, QWidget *parent) :
    EVentana(parent), Ui::FormProveedorBase()
{
    setupUi(this);
    setObjectName( "agregarproveedor" );
    setWindowTitle( "Modificar Proveedor" );

    addAction( new EActGuardar( this ) );
    addAction( new EActCerrar( this ) );

    this->modelo = m;

    mapa = new QDataWidgetMapper( this );
    mapa->setModel( this->modelo );
    mapa->setOrientation( Qt::Horizontal );
    mapa->addMapping( LERazonSocial, modelo->fieldIndex( "nombre" ) );
    mapa->addMapping( TEDireccion, modelo->fieldIndex( "direccion" ) );
    mapa->addMapping( LECUIT, modelo->fieldIndex( "cuit_cuil" ) );
    mapa->addMapping( LETelFijo, modelo->fieldIndex( "telefono_linea" ) );
    mapa->addMapping( LETelCel, modelo->fieldIndex( "telefono_celular" ) );
    mapa->addMapping( LEFax, modelo->fieldIndex( "fax" ) );
    mapa->addMapping( LEEmail, modelo->fieldIndex( "email" ) );
    mapa->setSubmitPolicy( QDataWidgetMapper::ManualSubmit );

    this->GBTitulo->setTitle( "Modificar proveedor" );
}

#include <QSqlError>
#include <QMessageBox>
void FormModificarProveedor::guardar()
{
    if( LERazonSocial->text().isEmpty() ) {
        QMessageBox::information( this, "Error", "Por favor, ingrese una razon social para el proveedor" );
        return;
    }
    // Verifico el Cuit
    if( !LECUIT->verificar() ) {
        QMessageBox::information( this, "Error", "Por favor, ingrese una razon CUIT/CUIL valido para el proveedor" );
        return;
    }
    if( mapa->submit() ) {
        QMessageBox::information( this, "Correcto", "Datos guardados correctamente" );
        this->close();
        return;
    } else {
        qDebug( "Error al intentar guardar los datos" );
        qDebug( this->modelo->lastError().text().toLocal8Bit() );
        return;
    }
}

void FormModificarProveedor::setearItem( const int id )
{
    if( id >= 0 )
    {  this->mapa->setCurrentIndex( id ); qDebug( QString( "%1" ).arg( id ).toLocal8Bit() );   }
    else
    { qDebug( QString( "%1" ).arg( id ).toLocal8Bit() ); }
}
