CREATE TABLE IF NOT EXISTS `recibos` ( `id_recibo` bigint(20) NOT NULL AUTO_INCREMENT, `id_cliente` bigint(20) REFERENCES clientes(id), `fecha_pago` datetime NOT NULL, `texto` tinyblob, `precio` double(15,4) DEFAULT NULL, `cancelado` tinyint(4) NOT NULL DEFAULT '0', `pagado` tinyint(4) NOT NULL DEFAULT '1', `id_caja` bigint(20) REFERENCES movimiento_caja(id_movimiento), PRIMARY KEY (`id_recibo`) ) ENGINE=InnoDB;