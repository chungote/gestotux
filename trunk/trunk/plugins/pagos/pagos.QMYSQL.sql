CREATE TABLE IF NOT EXISTS `recibos` ( `id_recibo` int(10) NOT NULL AUTO_INCREMENT, `id_cliente` bigint REFERENCES clientes(id), `fecha_pago` datetime NOT NULL, `texto` tinyblob DEFAULT NULL, `precio` double(15,4) DEFAULT NULL, `cancelado` tinyint NOT NULL DEFAULT 0, `pagado` tinyint NOT NULL DEFAULT 1, PRIMARY KEY (`id_recibo`) ) ENGINE=InnoDB;