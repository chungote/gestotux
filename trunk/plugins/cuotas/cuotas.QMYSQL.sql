CREATE TABLE IF NOT EXISTS `plan_cuota` ( `id_plan_cuota` BIGINT NOT NULL AUTO_INCREMENT, `id_factura` BIGINT NOT NULL, `cantidad_cuotas` INT NOT NULL DEFAULT 2, `tipo_periodo` INT NOT NULL DEFAULT 0, `fecha_inicio` DATETIME NOT NULL, `entrega_inicial` DOUBLE( 20,3 ) NOT NULL, `recargo` DOUBLE( 20, 4 ) NOT NULL,  PRIMARY KEY (`id_plan_cuota`), FOREIGN KEY (`id_factura`) REFERENCES `factura`(`id_factura`) ) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE TABLE IF NOT EXISTS `item_cuota` ( `id_item_cuota` BIGINT NOT NULL AUTO_INCREMENT, `id_plan_cuota` BIGINT NOT NULL, `num_cuota` INT NOT NULL, `monto` DOUBLE(20,3) NOT NULL, `fecha_vencimiento` DATE NOT NULL, `fecha_pago` DATE NOT NULL, `id_recibo` BIGINT NULL DEFAULT NULL, PRIMARY KEY (`id_item_cuota`), FOREIGN KEY (`id_plan_cuota`) REFERENCES `plan_cuota`(`id_plan_cuota`), FOREIGN KEY (`id_recibo`) REFERENCES `recibos`(`id_recibo`) ) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE VIEW `v_plan_cuota` AS SELECT  pc.id_plan_cuota AS `plan_cuota`, cc.razon_social AS `cliente`, CONCAT( CONCAT( ( SELECT COUNT(ic.id_item_cuota) FROM item_cuota as ic WHERE ic.id_plan_cuota = pc.id_plan_cuota),  '/' ), pc.cantidad_cuotas ) AS `progreso`, pc.cantidad_cuotas - ( SELECT COUNT(ic.id_item_cuota) FROM item_cuota as ic WHERE ic.id_plan_cuota = pc.id_plan_cuota) AS `faltantes`, ( SELECT MAX(ic.fecha_pago) FROM item_cuota as ic WHERE ic.id_plan_cuota = pc.id_plan_cuota AND id_recibo IS NOT NULL LIMIT 1 ) AS `ultimo_pago`, ( SELECT MIN(ic.fecha_vencimiento) FROM item_cuota as ic WHERE ic.id_plan_cuota = pc.id_plan_cuota AND id_recibo IS NULL LIMIT 1 ) AS `proximo_pago` FROM  `plan_cuota` AS pc,  `clientes` AS cc, `factura` AS f WHERE pc.id_factura = f.id_factura AND f.id_cliente = cc.id;