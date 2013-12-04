#include "dagregargarantia.h"

#include <QMessageBox>

DAgregarGarantia::DAgregarGarantia( QWidget *parent ) :
QDialog( parent )
{
    setupUi(this);
    setWindowTitle( "Agegar nueva garantía" );
    setWindowIcon( QIcon( ":/imagenes/agregargarantia.png" ) );

    _id_cliente = -1;
    _id_comprobante = -1;
    _id_producto = -1;
    _nombre_producto = QString();

    connect( CBCliente, SIGNAL( cambioIdCliente( int ) ), this, SLOT( buscarEquipamientos( int ) ) );
    connect( CBEquipamiento, SIGNAL( cambioId( int ) ), this, SLOT( buscarFactura( int ) ) );

}

/*!
 * \brief DAgregarGarantia::setearIdComprontante
 * \param id_comprobante
 */
void DAgregarGarantia::setearIdComprontante( const int id_comprobante )
{
    _id_comprobante = id_comprobante;
    LEFactura->setText( QString( "#%1").arg( id_comprobante ) );
}

/*!
 * \brief DAgregarGarantia::setearIdProducto
 * \param id_producto
 */
void DAgregarGarantia::setearIdProducto( const int id_producto )
{
    if( id_producto > 0 ) {
        _id_producto = id_producto;
    }
}

/*!
 * \brief DAgregarGarantia::setearNombreProducto
 * \param nombre_producto
 */
void DAgregarGarantia::setearNombreProducto( const QString nombre_producto )
{
    if( !nombre_producto.isEmpty() ) {
        _nombre_producto = nombre_producto;
        CBEquipamiento->insertItem( 0, nombre_producto );
    }
}

/*!
 * \brief DAgregarGarantia::setearIdCliente
 * \param id_cliente
 */
void DAgregarGarantia::setearIdCliente( const int id_cliente )
{
}

/*!
 * \brief DAgregarGarantia::setearIdComprobante
 * \param id_comprobante
 */
void DAgregarGarantia::setearIdComprobante( const int id_comprobante )
{
}

/*!
 * \brief DAgregarGarantia::accept
 */
void DAgregarGarantia::accept()
{
    if( _id_cliente == -1 || _id_comprobante == -1 || _id_producto == -1 || _nombre_producto.isEmpty() ) {
        QMessageBox::warning( this, "Error", QString::fromUtf8( "No se setearon correctamente los datos" ) );
    }
    return;
    QDialog::accept();
}

void DAgregarGarantia::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

/*!
 * \brief DAgregarGarantia::buscarEquipamientos
 * Genera la lista de equipamientos posibles para el cliente seleccionado
 * \param id_cliente Identificador del cliente
 */
void DAgregarGarantia::buscarEquipamientos( int id_cliente )
{
    /// @TODO: Agregar busqueda y filtrado de equipamientos
}

/*!
 * \brief DAgregarGarantia::buscarFactura
 * Busca si existe el identificador de equipamiento y si tiene factura de compra
 * \param id_equipamiento Identificador de equipamiento
 */
void DAgregarGarantia::buscarFactura( int id_equipamiento )
{
    /// @TODO: Agregar busqueda de fecha de compra y comproante para el equipamiento.
}
