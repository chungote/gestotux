CREATE TABLE IF NOT EXISTS `orden_trabajo` (
  `id_orden_trabajo` bigint(20) NOT NULL AUTO_INCREMENT,
  `cliente_id` bigint(20) NOT NULL,
  `fecha_ingreso` datetime NOT NULL,
  `requerente` tinytext COLLATE utf8_spanish_ci NOT NULL,
  `ingresante` tinytext COLLATE utf8_spanish_ci,
  `fecha_vencimiento` date DEFAULT NULL,
  `fecha_devolucion` datetime DEFAULT NULL,
  PRIMARY KEY (`id_orden_trabajo`),
  FOREIGN KEY (`cliente_id`) REFERENCES `clientes`(`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE TABLE IF NOT EXISTS `tecnico` (
    `id_tecnico` bigint(20) NOT NULL AUTO_INCREMENT,
    `razon_social` tinytext NOT NULL,
    `habilitado` boolean NOT NULL DEFAULT 0,
    PRIMARY KEY (`id_tecnico`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE TABLE IF NOT EXISTS `equipamiento` (
    `id_equipamiento` bigint(20) NOT NULL AUTO_INCREMENT,
    `descripcion` tinytext NOT NULL,
    `marca` tinytext NULL DEFAULT NULL,
    `modelo` tinytext NULL DEFAULT NULL,
    `numero_serie` tinytext NULL DEFAULT NULL,
    `fecha_compra` datetime DEFAULT NULL,
    `fecha_vencimiento` date DEFAULT NULL,
    `id_factura` bigint(20) DEFAULT NULL,
    PRIMARY KEY (`id_equipamiento`),
    FOREIGN KEY (`id_factura`) REFERENCES `factura`(`id_factura`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE TABLE IF NOT EXISTS `tipo_operacion_orden_trabajo` (
    `id_tipo_operacion_orden_trabajo` int(11) NOT NULL AUTO_INCREMENT,
    `nombre` tinytext NOT NULL,
    PRIMARY KEY (`id_tipo_operacion_orden_trabajo`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE TABLE IF NOT EXISTS `operacion_orden_trabajo` (
    `id_operacion` bigint(20) NOT NULL AUTO_INCREMENT,
    `id_orden_trabajo` bigint(20) NOT NULL,
    `fecha_hora` datetime NOT NULL,
    `descripcion` tinytext NOT NULL,
    `tipo_operacion` int(11) NOT NULL,
    PRIMARY KEY (`id_operacion`),
    FOREIGN KEY (`id_orden_trabajo`) REFERENCES `orden_trabajo`(`id_orden_trabajo`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;