#include "mitemfactura.h"

MItemFactura::MItemFactura(QObject *parent) :
    QSqlRelationalTableModel(parent) {
    inicializar();
    relacionar();
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
