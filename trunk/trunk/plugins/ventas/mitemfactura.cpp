#include "mitemfactura.h"
#include <QSqlQuery>
#include <QSqlError>

MItemFactura::MItemFactura(QObject *parent) :
    QSqlRelationalTableModel(parent) {
    inicializar();
    relacionar();
    _orden = 1;
}

/*
CREATE TABLE IF NOT EXISTS `item_factura` (
  `id_item_factura` bigint NOT NULL,
  `id_factura` bigint REFERENCES factura(id_factura),
  `cantidad` double NOT NULL,
  `texto` text NOT NULL,
  `precio_unitario` double NOT NULL,
  `id_producto` bigint NULL,
  PRIMARY KEY (`id_item_factura`, `id_factura` )
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
*/

void MItemFactura::inicializar() {
  setTable( "item_factura" );
  setHeaderData( 0, Qt::Horizontal, "#Orden" );
  setHeaderData( 1, Qt::Horizontal, "#Factura" );
  setHeaderData( 2, Qt::Horizontal, "Cantidad" );
  setHeaderData( 3, Qt::Horizontal, "Item" );
  setHeaderData( 4, Qt::Horizontal, "Precio Unitario" );
  setHeaderData( 5, Qt::Horizontal, "#Producto" );
}

void MItemFactura::relacionar() {
  setRelation( 1, QSqlRelation( "factura", "id_factura", "serie" ) ); ///@todo Crear una vista para esto
}

/*!
 * \fn MItemFactura::agregarItemFactura( const int id_venta, const double cantidad, const QString texto, const double precio_unitario )
 * Agrega un item de factura para la venta indicada.
 * @param id_venta Clave foranea en la tabla factura.
 * @param cantidad Cantidad del item.
 * @param texto Texto que va a aparecer en el item de la factura.
 * @param precio_unitario Precio unitario del item de la factura.
 * @returns Verdadero si se pudo agregar correctamente.
 */
bool MItemFactura::agregarItemFactura( const int id_venta, const double cantidad, const QString texto, const double precio_unitario ) {
    QSqlQuery cola;
    if( ! cola.prepare( "INSERT INTO item_factura( id_item_factura, id_factura, cantidad, texto, precio_unitario ) VALUES ( :orden, :id_venta, :cantidad, :texto, :precio_unitario );" ) ) {
        qDebug( "Error al intentar preparar la cola de inserción" );
        qDebug( QString( "Error: %1 - %2" ).arg( cola.lastError().number() ).arg( cola.lastError().text() ).toLocal8Bit() );
    }
    ///@todo Si Sqlite verificar que existe presupuesto
    cola.bindValue( ":id_venta", id_venta );
    cola.bindValue( ":cantidad", cantidad );
    cola.bindValue( ":texto", texto );
    cola.bindValue( ":precio_unitario", precio_unitario );
    cola.bindValue( ":orden", _orden );
    if( cola.exec() ) {
        _orden++;
        return true;
    } else {
        qDebug( "Error al intentar insertad valor de item de presupuesto" );
        qDebug( QString( "Error: %1 - %2 - %3" ).arg( cola.lastError().number() ).arg( cola.lastError().text() ).arg( cola.lastQuery() ).toLocal8Bit() );
        return false;
    }


}
