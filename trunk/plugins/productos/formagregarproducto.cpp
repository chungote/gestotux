#include "formagregarproducto.h"
#include "preferencias.h"
#include <QMessageBox>
#include "mproductos.h"

FormAgregarProducto::FormAgregarProducto(QWidget *parent) :
  QDialog( parent ), Ui::FormProductoBase()
{
    setupUi( this );
    setAttribute( Qt::WA_DeleteOnClose );
    setObjectName( "FormAgregarProducto" );
    setWindowTitle( "Agregar nuevo producto" );

    connect( DSBCosto, SIGNAL( valueChanged( double ) ), this, SLOT( cambioPrecioCosto( double ) ) );
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Solicito la categoria del producto si esta habilitado
    if( ! preferencias::getInstancia()->value( "Preferencias/Productos/categorias" ).toBool() )
    {
      this->LCategoria->setVisible( false );
      this->CBCategoria->setVisible( false );
        _categorias = false;
    } else {
        // Cargo las cateogrías que haya
        _categorias = true;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Solicito la descripcion si esta habilitado
    if( ! preferencias::getInstancia()->value( "Preferencias/Productos/descripcion" ).toBool() )
    {
        this->LDescripcion->setVisible( false );
        this->LEDescripcion->setVisible( false );
        _descripcion = false;
    } else { _descripcion = true; }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Solicito la marca del producto si esta habilitado
    if( ! preferencias::getInstancia()->value( "Preferencias/Productos/marcas" ).toBool() )
    {
        this->LMarca->setVisible( false );
        this->LEMarca->setVisible( false );
        _marcas = false;
    } else {
        // cargo el autocompletado de las marcas
        _marcas = true;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Solicito el stock del producto si esta habilitado
    if( ! preferencias::getInstancia()->value( "Preferencias/Productos/stock" ).toBool() ) {
       this->LStock->setVisible( false );
       this->SBStock->setVisible( false );
        _stock = false;
    } else { _stock = false; }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Solicito el modelo si esta habilitado
    if( ! preferencias::getInstancia()->value( "Preferencias/Productos/modelo" ).toBool() ) {
        this->LModelo->setVisible( false );
        this->LEModelo->setVisible( false );
        _modelo = false;
    } else { _modelo = true; }
    /// Cargo el recargo para hacer los calculos sin tener que consultarlo todas las veces
    _recargo = preferencias::getInstancia()->value( "Preferencias/Productos/ganancia", 10.0 ).toDouble();
}

void FormAgregarProducto::cambioPrecioCosto( double precio ) {
    this->DSBVenta->setValue( ( 1.00 + ( _recargo / 100 ) ) * precio );
}

void FormAgregarProducto::accept() {
    // Verificaciones de estado correcto
    if( this->LECodigo->text().isEmpty() ) {
        QMessageBox::warning( this, "Error", QString::fromUtf8("El código del producto no puede ser nulo. Por favor, ingrese un código para el producto" ) );
        return;
    }
    if( this->LENombre->text().isEmpty() ) {
        QMessageBox::warning( this, "Error", QString::fromUtf8("El nombre del producto no puede ser nulo. Por favor, ingrese un nombre para el producto" ) );
        return;
    }
/*    if( this->LEDescripcion->text().isEmpty() && _descripcion ) {
        QMessageBox::warning( this, "Error", QString::fromUtf8("La descripción del producto no puede ser nula. Por favor, ingrese una descripción para el producto" ) );
        return;
    }
    if( this->LEMarca->text().isEmpty() && _descripcion ) {
        QMessageBox::warning( this, "Error", QString::fromUtf8( "El código del producto no puede ser nulo. Por favor, ingrese un código para el producto" ) );
        return;
    }*/
    if( this->CBCategoria->currentIndex() == 0 && _categorias ) {
        QMessageBox::warning( this, "Error", QString::fromUtf8("La categoría del producto no puede ser nula. Por favor, seleccióne una categoría para el producto" ) );
        return;
    }
    if( this->DSBCosto->value() <= 0 ) {
        QMessageBox::warning( this, "Error", QString::fromUtf8( "El precio de costo del producto no puede ser cero. Por favor, ingrese un precio de costo para el producto" ) );
        return;
    }
    if( this->DSBVenta->value() <= 0 ) {
        QMessageBox::warning( this, "Error", QString::fromUtf8("El precio de venta del producto no puede ser nulo. Por favor, ingrese un precio de venta para el producto" ) );
        return;
    }
    // Dar de alta con stock cero?
    if( this->SBStock->value() == 0 && _stock ) {
        QMessageBox::warning( this, "Error", QString::fromUtf8( "El stock inicial del producto no puede ser nulo. Por favor, ingrese un stock inicial para el producto" ) );
        return;
    }
    // Todos los datos pasaron bien luego de este punto
    if( MProductos::agregarProducto(
                this->LECodigo->text(),
                this->LENombre->text(),
                this->DSBCosto->value(),
                this->DSBVenta->value(),
                this->SBStock->value(),
                this->CBCategoria->model()->data( this->CBCategoria->model()->index( this->CBCategoria->currentIndex(), 0 ), Qt::EditRole ).toInt(),
                this->LEDescripcion->text(),
                this->LEMarca->text(),
                this->LEModelo->text() ) ) {
        QMessageBox::information( this, "Correcto",QString::fromUtf8("El producto se agregó correctamente" ) );
        QDialog::accept();
        return;
    } else {
        QMessageBox::warning( this, "Erroneo", "No se pudo agregar el producto." );
        return;
    }
}
