CREATE TABLE IF NOT EXISTS `ctacte` (  `numero_cuenta` bigint(20) NOT NULL auto_increment,  `id_cliente` bigint(20) NOT NULL, `fecha_alta` date NOT NULL, `fecha_baja` date default NULL, `saldo` double default NULL, `limite` double(20,4) default NULL,  PRIMARY KEY  (`numero_cuenta`), FOREIGN KEY (id_cliente) REFERENCES clientes( id ) ) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE TABLE IF NOT EXISTS `item_ctacte` ( `id_op_ctacte` bigint(6) NOT NULL AUTO_INCREMENT, `fecha` datetime NOT NULL, `id_referencia` bigint(20) NOT NULL, `tipo_op` smallint(6) NOT NULL, `descripcion` tinytext COLLATE utf8_spanish_ci, `debe` decimal(12,3) DEFAULT NULL, `haber` decimal(12,3) DEFAULT NULL, `id_ctacte` bigint(20) NOT NULL, `numero_comprobante` tinytext COLLATE utf8_spanish_ci, PRIMARY KEY (`id_op_ctacte`), FOREIGN KEY (id_ctacte) REFERENCES ctacte(numero_cuenta) ) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;