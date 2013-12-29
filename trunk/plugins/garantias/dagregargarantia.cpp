#include "dagregargarantia.h"

#include <QMessageBox>

#include "mequipamiento.h"
#include "ecbequipamiento.h"
#include "MFactura.h"
#include "preferencias.h"

DAgregarGarantia::DAgregarGarantia( QWidget *parent ) :
QDialog( parent )
{
    setupUi(this);
    setWindowTitle( QString::fromUtf8( "Agegar nueva garantía" ) );
    setWindowIcon( QIcon( ":/imagenes/garantia_agregar.png" ) );

    _id_cliente = -1;
    _id_comprobante = -1;
    _id_producto = -1;
    _nombre_producto = QString();

    connect( CBCliente, SIGNAL( cambioIdCliente( int ) ), this, SLOT( buscarEquipamientos( int ) ) );
    connect( CBEquipamiento, SIGNAL( cambioId( int ) ), this, SLOT( buscarFactura( int ) ) );

    DECompra->setDate( QDate::currentDate() );

    // Permito que se puedan insertar nuevos elementos en el combobox de equipamientos
    //CBEquipamiento->setInsertionPolicy( QComboBox::InsertAlphabetically );

}

/*!
 * \brief DAgregarGarantia::setearIdProducto
 * \param id_producto Identificador del producto
 */
void DAgregarGarantia::setearIdProducto( const int id_producto )
{
    if( id_producto > 0 ) {
        _id_producto = id_producto;
    }
}

/*!
 * \brief DAgregarGarantia::setearNombreProducto
 * \param nombre_producto Nombre del producto
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
 * \param id_cliente Identificador del cliente
 */
void DAgregarGarantia::setearIdCliente( const int id_cliente )
{
    _id_cliente = id_cliente;
    CBCliente->setearId( id_cliente );
}

/*!
 * \brief DAgregarGarantia::setearIdComprobante
 * \param id_comprobante Identificador del Comprobante
 */
void DAgregarGarantia::setearIdComprobante( const int id_comprobante )
{
    _id_comprobante = id_comprobante;
    LEFactura->setText( MFactura::obtenerComprobante( _id_comprobante ).aCadena() );
    DECompra->setDate( MFactura::obtenerFecha( _id_comprobante ) );

    preferencias *p = preferencias::getInstancia();
    p->inicio();
    p->beginGroup( "Preferencias" );
    p->beginGroup( "Garantias" );
    DEFin->setDate( DECompra->date().addMonths( p->value( "duracion_garantia" ).toInt() ) );
    p->endGroup();
    p->endGroup();
    p=0;
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
    _id_cliente = id_cliente;
    if( MEquipamiento::existeEquipamientoParaCliente( id_cliente ) ) {
        /// @TODO: Agregar listado temporal dentro de este elemento para que conserve el producto
        CBEquipamiento->setearFiltro( QString( " WHERE id_cliente = %1" ).arg( id_cliente ), true  );
    } else {
        CBEquipamiento->setEditable( true );
    }

}

/*!
 * \brief DAgregarGarantia::buscarFactura
 * Busca si existe el identificador de equipamiento y si tiene factura de compra
 * \param id_equipamiento Identificador de equipamiento
 */
void DAgregarGarantia::buscarFactura( int id_equipamiento )
{
    if( id_equipamiento <= 0 )
    { return; }

    if( modelo != 0 )
    { modelo = new MEquipamiento( this ); }

    if( !modelo->cargarDatos( id_equipamiento ) ) {
        return;
    }

    setearIdComprobante( modelo->numeroComprobante() );
}
