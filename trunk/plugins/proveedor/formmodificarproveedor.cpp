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
    mapa->addMapping( LERazonSocial, modelo->fieldIndex( "nombre" ) );
    mapa->addMapping( TEDireccion, modelo->fieldIndex( "direccion" ) );
    mapa->addMapping( LECUIT, modelo->fieldIndex( "cuit_cuil" ) );
    mapa->addMapping( LETelFijo, modelo->fieldIndex( "telefono_linea" ) );
    mapa->addMapping( LETelCel, modelo->fieldIndex( "telefono_celular" ) );
    mapa->setSubmitPolicy( QDataWidgetMapper::ManualSubmit );

    this->GBTitulo->setTitle( "Modificar proveedor" );
}

#include <QSqlError>
#include <QMessageBox>
void FormModificarProveedor::guardar()
{
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
