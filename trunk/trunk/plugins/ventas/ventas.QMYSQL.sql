CREATE TABLE IF NOT EXISTS `ventas` ( `id` mediumint(1) NOT NULL auto_increment, `fecha` date NOT NULL, PRIMARY KEY  (`id`) );
CREATE TABLE IF NOT EXISTS `ventas_productos` ( `id` int(1) NOT NULL auto_increment, `id_venta` int(1) REFERENCES `ventas`(`id`), `id_producto` int(1) REFERENCES `producto`(`id`), `precio` decimal(4,0) NOT NULL, `cantidad` decimal(4,0) NOT NULL, PRIMARY KEY  (`id`) );