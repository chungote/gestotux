CREATE TABLE IF NOT EXISTS `servicios` ( `id_servicio` bigint NOT NULL auto_increment, `nombre` tinytext NOT NULL, `fecha_alta` date NOT NULL,  `fecha_baja` date NULL,  `precio_base` double NOT NULL,  `periodo` int NOT NULL,  `dia_cobro` int NOT NULL,  `forma_incompleto` int NOT NULL,  PRIMARY KEY  (`id_servicio`) ) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE TABLE IF NOT EXISTS `servicios_clientes` ( `id_servicio` bigint REFERENCES servicios(id_servicio), `id_cliente` bigint(1) REFERENCES clientes(id), `fecha_alta` DATETIME NOT NULL, `fecha_baja` DATETIME NULL, PRIMARY KEY  (`id_servicio`, `id_cliente` )) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE TABLE IF NOT EXISTS `recargos` ( `id_recargo` bigint NOT NULL AUTO_INCREMENT, `id_servicio` bigint NOT NULL,  `cant_dias` int NOT NULL,  `porcentaje` double(4,2) DEFAULT NULL,  `recargo` double DEFAULT NULL,  PRIMARY KEY (`id_recargo`) ) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE TABLE IF NOT EXISTS `periodo_servicio` (
    `id_periodo_servicio` BIGINT NOT NULL AUTO_INCREMENT,
    `id_servicio` BIGINT NOT NULL,
    `fecha` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `periodo` INT NOT NULL,
    `ano` YEAR NOT NULL,
    `fecha_inicio` DATE NOT NULL,
    `fecha_fin` DATE NOT NULL,
    FOREIGN KEY ( id_servicio ) REFERENCES `servicios`( id_servicio ),
    PRIMARY KEY ( id_cobro_servicio )
) ENGINE = InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE TABLE IF NOT EXISTS `cobro_servicio_cliente_periodo` (
    `id_periodo_servicio` BIGINT NOT NULL,
    `id_servicio` BIGINT NOT NULL,
    `id_cliente` BIGINT NOT NULL,
    `id_factura` BIGINT NOT NULL,
    `id_recibo` BIGINT DEFAULT NULL,
    `id_ctacte` BIGINT DEFAULT NULL,
    FOREIGN KEY ( id_periodo_servicio ) REFERENCES `periodo_servicio`( id_periodo_servicio ),
    FOREIGN KEY ( id_servicio, id_cliente ) REFERENCES `servicios_clientes`( id_servicio, id_cliente ),
    FOREIGN KEY ( id_factura ) REFERENCES `factura`( id_factura ),
    FOREIGN KEY ( id_ctacte ) REFERENCES `item_ctacte`(id_op_ctacte),
    FOREIGN KEY ( id_recibo ) REFERENCES `recibos`( id_recibo ),
    PRIMARY KEY ( id_periodo_servicio, id_servicio, id_cliente )
) ENGINE = InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE TABLE IF NOT EXISTS `recargo_cobro_servicio_servicio_cliente` (
    `id_periodo_servicio` BIGINT NOT NULL,
    `id_servicio BIGINT NOT NULL,
    `id_cliente` BIGINT NOT NULL,
    `id_recargo` BIGINT NOT NULL,
    `fecha_generado` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    `texto_detalle` TEXT NOT NULL,
    `precio` DOUBLE NOT NULL,
    `id_ctacte` BIGINT NOT NULL,
    `id_recibo` BIGINT,
    FOREIGN KEY ( id_periodo_servicio, id_servicio_cliente ) REFERENCES `periodo_servicio`( id_periodo_servicio, id_servicio_cliente ),
    FOREIGN KEY ( id_recargo ) REFERENCES `recargos`( id_recargo ),
    FOREIGN KEY ( id_ctacte ) REFERENCES `item_ctacte`( id_op_ctacte ),
    FOREIGN KEY ( id_recibo ) REFERENCES `recibos`( id_recibo ),
    PRIMARY KEY ( id_cobro_servicio, id_servicio, id_cliente, id_recargo )
) ENGINE = InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;