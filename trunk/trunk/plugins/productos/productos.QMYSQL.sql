CREATE TABLE IF NOT EXISTS `producto` ( `id` bigint(1) NOT NULL auto_increment, `id_categoria` int(1) NOT NULL, `nombre` tinytext NOT NULL, `precio_venta` decimal(10,4) NOT NULL, `descripcion` tinytext, `marca` tinytext, PRIMARY KEY  (`id`) ) ENGINE=MyISAM DEFAULT CHARSET=latin1;
CREATE TABLE IF NOT EXISTS `categoria_producto` ( `id` int(10) NOT NULL auto_increment, `nombre` varchar(100) NOT NULL, `descripcion` varchar(200) default NULL, `tipo` int(1) NOT NULL, PRIMARY KEY  (`id`) ) ENGINE=MyISAM DEFAULT CHARSET=latin1;