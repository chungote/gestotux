CREATE TABLE IF NOT EXISTS `factura` ( `id_factura` bigint NOT NULL AUTO_INCREMENT, `id_cliente` bigint NULL,`fecha` datetime NOT NULL,   `id_forma_pago` int(1) NOT NULL, `serie` bigint(20) NOT NULL, `numero` bigint(20) NOT NULL, `total` DOUBLE NOT NULL,  `id_ctacte` bigint(20) NULL,    `id_mov_caja` bigint(20) NULL, `anulada` tinyint(1) NOT NULL, `razon` text COLLATE utf8_spanish_ci, `fecha_cancelada` datetime DEFAULT NULL, PRIMARY KEY (`id_factura`),     UNIQUE KEY `factura-serie-numero` (`serie`,`numero`),     FOREIGN KEY (`id_cliente`) REFERENCES `clientes`( `id` ),     FOREIGN KEY (`id_ctacte`) REFERENCES `item_ctacte`( `id_op_ctacte` ),     FOREIGN KEY (`id_mov_caja`) REFERENCES `movimiento_caja`( `id_movimiento` )) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE TABLE IF NOT EXISTS `item_factura` ( `id_item_factura` bigint(20) NOT NULL, `id_factura` bigint(20) NOT NULL,    `cantidad` double NOT NULL,    `texto` text NOT NULL,    `precio_unitario` double NOT NULL,    `id_producto` bigint NULL,     PRIMARY KEY (`id_item_factura`, `id_factura` ), FOREIGN KEY (`id_factura`) REFERENCES factura( id_factura ) ) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE VIEW `v_facturas` AS SELECT f.id_factura, CONCAT( CONCAT( LPAD( f.serie, 5, 0 ) , '-' ) , LPAD( f.numero, 5, 0 ) ) AS NumSerie, c.razon_social AS cliente, f.fecha AS fecha, f.id_forma_pago, f.total AS precio, f.anulada AS anulada FROM `factura` AS f, `clientes` AS c WHERE f.id_cliente = c.id;