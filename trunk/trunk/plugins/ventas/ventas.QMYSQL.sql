CREATE TABLE IF NOT EXISTS `factura` (
  `id_factura` bigint(20) NOT NULL AUTO_INCREMENT,
  `id_cliente` bigint(20) NOT NULL,
  `fecha` datetime NOT NULL,
  `id_forma_pago` int(1) NOT NULL,
  `serie` bigint(20) NOT NULL,
  `numero` bigint(20) NOT NULL,
  PRIMARY KEY (`id_factura`),
  UNIQUE KEY `factura-serie-numero` (`serie`,`numero`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE TABLE IF NOT EXISTS `ventas` ( `id_factura` BIGINT NOT NULL auto_increment, `fecha` date NOT NULL, PRIMARY KEY  (`id`) )  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE TABLE IF NOT EXISTS `ventas_productos` ( `id` BIGINT NOT NULL auto_increment, `id_venta` BIGINT REFERENCES `ventas`(`id`), `id_producto` BIGINT REFERENCES `producto`(`id`), `precio` decimal(4,0) NOT NULL, `cantidad` decimal NOT NULL, PRIMARY KEY  (`id`) )  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;