#include "formagregarproveedor.h"

#include <QMessageBox>

FormAgregarProveedor::FormAgregarProveedor( MProveedor *m, QWidget *parent) :
    EVentana(parent), Ui::FormProveedorBase()
{
    setupUi(this);
    setObjectName( "agregarproveedor" );
    setWindowTitle( "Agregar Proveedor" );

    addAction( new EActGuardar( this ) );
    addAction( new EActCerrar( this ) );

    this->modelo = m;

    /*mapa = new QDataWidgetMapper( this );
    mapa->addMapping( LERazonSocial, modelo->fieldIndex( "nombre" ) );
    mapa->addMapping( TEDireccion, modelo->fieldIndex( "direccion" ) );
    mapa->addMapping( LECUIT, modelo->fieldIndex( "cuit_cuil" ) );
    mapa->addMapping( LETelFijo, modelo->fieldIndex( "telefono_linea" ) );
    mapa->addMapping( LETelCel, modelo->fieldIndex( "telefono_celular" ) );
    mapa->setSubmitPolicy( QDataWidgetMapper::ManualSubmit );*/

    this->GBTitulo->setTitle( "Agregar nuevo proveedor" );
}

void FormAgregarProveedor::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

#include <QSqlRecord>
#include <QSqlError>
void FormAgregarProveedor::guardar() {
    if( LERazonSocial->text().isEmpty() ) {
        QMessageBox::information( this, "Error", "Por favor, ingrese una razon social para el proveedor" );
        return;
    }
    QSqlRecord rec = this->modelo->record();
    rec.setValue( "nombre", LERazonSocial->text() );
    rec.setValue( "direccion", TEDireccion->toPlainText() );
    rec.setValue( "cuit_cuil", LECUIT->text() );
    rec.setValue( "telefono_linea", LETelFijo->text() );
    rec.setValue( "telefono_celular", LETelCel->text() );
    if( this->modelo->insertRecord( -1, rec ) ) {
        QMessageBox::information( this, "Correcto", QString( "El proveedor %1 se inserto correctamente" ).arg( rec.value( "id" ).toInt() ) );
        this->close();
        return;
    } else {
        qDebug( "Error al insertar el registro" );
        qDebug( this->modelo->lastError().text().toLocal8Bit() );
    }
}
