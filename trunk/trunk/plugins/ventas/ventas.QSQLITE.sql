CREATE TABLE IF NOT EXISTS factura ( "id_factura" INTEGER PRIMARY KEY autoincrement, "id_cliente" INTEGER NOT NULL, "fecha" TEXT NOT NULL, "id_forma_pago" INTEGER NOT NULL, "serie" INTEGER NOT NULL, "numero" INTEGER NOT NULL, "total" NUMERIC NOT NULL, "id_ctate" NUMERIC NULL, "id_mov_caja" NUMERIC NULL, "anulada" NUMERIC NULL, "razon" TEXT NULL, "fecha_cancelada" TEXT NULL );
CREATE TABLE IF NOT EXISTS item_factura ( "id_item_factura" INTEGER PRIMARY KEY autoincrement, "id_factura" INTEGER NOT NULL, "cantidad" DOUBLE NOT NULL, "texto" TEXT NOT NULL, "precio_unitario" DOUBLE NOT NULL, "id_producto" INTEGER NULL );
INSERT OR IGNORE INTO sqlite_sequence VALUES ( 'factura', '1');
INSERT OR IGNORE INTO sqlite_sequence VALUES ( 'item_factura', '1' );
CREATE VIEW `v_facturas` AS SELECT f.id_factura, f.serie + '-' + f.numero AS NumSerie, c.razon_social AS cliente, f.fecha AS fecha, f.id_forma_pago, f.total AS precio FROM `factura` AS f, `clientes` AS c WHERE f.id_cliente = c.id;