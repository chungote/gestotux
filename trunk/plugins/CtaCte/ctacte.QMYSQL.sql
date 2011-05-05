CREATE TABLE IF NOT EXISTS `ctacte` (  `numero_cuenta` bigint(20) NOT NULL auto_increment,  `id_cliente` bigint(20) default NULL, `fecha_alta` date NOT NULL, `fecha_baja` date default NULL, `saldo` double default NULL, `limite` double(20,4) default NULL,  PRIMARY KEY  (`numero_cuenta`)) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE TABLE IF NOT EXISTS `item_ctacte` ( `id_op_ctacte` bigint(6) NOT NULL auto_increment, `fecha` datetime NOT NULL, `id_referencia` bigint(20) NOT NULL, `tipo_op` tinytext NOT NULL, `descripcion` tinytext, `debe` decimal(12,3) default NULL, `haber` decimal(12,3) default NULL, `id_ctacte` bigint(20) default NULL, `numero_comprobante` tinytext, PRIMARY KEY  (`id_op_ctacte`)) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;