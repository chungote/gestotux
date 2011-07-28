CREATE TABLE IF NOT EXISTS `categoria_gastos` (  `id_categoria_gastos` bigint NOT NULL auto_increment, `nombre` tinytext NOT NULL, `descripcion` text default NULL, PRIMARY KEY  (`id_categoria_gastos`) ) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE TABLE IF NOT EXISTS `gastos` ( `id_gasto` bigint NOT NULL AUTO_INCREMENT ,  `id_categoria` int( 11 ) NOT NULL REFERENCES categoria_gastos( id_categoria_gastos ) ON DELETE RESTRICT,  `descripcion` tinytext NOT NULL,  `costo` double NOT NULL DEFAULT 0.0, `fecha` date NOT NULL, `id_caja` bigint DEFAULT NULL REFERENCES movimiento_caja( id_movimiento ),  PRIMARY KEY ( `id_gasto` ) ) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;