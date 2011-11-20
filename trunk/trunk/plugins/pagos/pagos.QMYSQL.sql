CREATE TABLE IF NOT EXISTS `recibos` ( `id_recibo` bigint(20) NOT NULL AUTO_INCREMENT, `id_cliente` bigint(20) REFERENCES clientes(id), `fecha_pago` datetime NOT NULL, `texto` tinyblob, `precio` double(15,4) DEFAULT NULL, `forma_pago` int(11) NOT NULL, `cancelado` tinyint(4) NOT NULL DEFAULT '0', `pagado` tinyint(4) NOT NULL DEFAULT '1', `serie` int(11) NOT NULL, `numero` int(11) NOT NULL, `id_caja` bigint(20) DEFAULT NULL, razon_cancelacion tinytext DEFAULT NULL, fechahora_cancelacion DATETIME DEFAULT NULL, PRIMARY KEY (`id_recibo`), UNIQUE KEY `numero_recibo` (`serie`,`numero`) ) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE VIEW `v_recibos` AS SELECT r.id_recibo AS id_recibo,  CONCAT( CONCAT( LPAD( r.serie, 5, 0 ) , '-' ) , LPAD( r.numero, 5, 0 ) ) AS NumSerie, c.razon_social AS razon_social, r.fecha_pago AS fecha_pago, r.precio AS precio, r.forma_pago AS forma_pago, r.pagado AS pagado, r.cancelado AS cancelado FROM `recibos` AS r, clientes AS c WHERE r.id_cliente = c.id;