CREATE  TABLE IF NOT EXISTS `equipamiento` ( `id_equipamiento` BIGINT(20) NOT NULL AUTO_INCREMENT , `descripcion` TINYTEXT CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NOT NULL , `marca` TINYTEXT CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NULL DEFAULT NULL , `modelo` TINYTEXT CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NULL DEFAULT NULL , `numero_serie` TINYTEXT CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NULL DEFAULT NULL , `fecha_compra` DATETIME NULL DEFAULT NULL , `fecha_vencimiento` DATE NULL DEFAULT NULL , `id_factura_compra` BIGINT(20) NULL DEFAULT NULL , `id_cliente` BIGINT(10) NOT NULL , `cantidad_elementos` INT NOT NULL DEFAULT 1 , `fecha_baja` DATETIME NULL , `razon_baja` TINYTEXT NULL , PRIMARY KEY (`id_equipamiento`) , INDEX `id_factura` (`id_factura_compra` ASC) , INDEX `fk_equipamiento_clientes1_idx` ( `id_cliente` ASC ), CONSTRAINT `equipamiento_ibfk_1` FOREIGN KEY (`id_factura_compra` ) REFERENCES `gestotux`.`factura` (`id_factura` ), CONSTRAINT `fk_equipamiento_clientes1` FOREIGN KEY (`id_cliente` ) REFERENCES `gestotux`.`clientes` (`id` ) ON DELETE NO ACTION ON UPDATE NO ACTION ) ENGINE = InnoDB DEFAULT CHARACTER SET = utf8 COLLATE = utf8_spanish_ci;
CREATE  TABLE IF NOT EXISTS `orden_trabajo` ( `id_orden_trabajo` BIGINT(20) NOT NULL AUTO_INCREMENT ,  `cliente_id` BIGINT(20) NOT NULL , `fecha_ingreso` DATETIME NOT NULL , `requerente` TINYTEXT CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NOT NULL , `ingresante` TINYTEXT CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NULL DEFAULT NULL , `fecha_vencimiento` DATE NULL DEFAULT NULL , `fecha_devolucion` DATETIME NULL DEFAULT NULL , `id_equipamiento` BIGINT(20) NOT NULL , `id_factura` BIGINT(20) NOT NULL, `id_tecnico` BIGINT(20) NOT NULL, `causa_ingreso` tinytext NOT NULL DEFAULT '', PRIMARY KEY (`id_orden_trabajo`) , INDEX `fk_orden_trabajo_equipamiento1_idx` (`id_equipamiento` ASC) , INDEX `fk_orden_trabajo_factura1_idx` (`id_factura` ASC) , CONSTRAINT `fk_orden_trabajo_equipamiento1` FOREIGN KEY (`id_equipamiento` ) REFERENCES `gestotux`.`equipamiento` (`id_equipamiento` ) ON DELETE NO ACTION ON UPDATE NO ACTION, CONSTRAINT `fk_orden_trabajo_factura1` FOREIGN KEY (`id_factura` ) REFERENCES `gestotux`.`factura` (`id_factura` ) ON DELETE NO ACTION ON UPDATE NO ACTION ) ENGINE = InnoDB DEFAULT CHARACTER SET = utf8 COLLATE = utf8_spanish_ci;
CREATE  TABLE IF NOT EXISTS `tecnico` ( `id_tecnico` BIGINT(20) NOT NULL AUTO_INCREMENT , `razon_social` TINYTEXT CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NOT NULL , `habilitado` TINYINT(1) NOT NULL DEFAULT '0' , `fecha_ingreso` DATETIME NULL DEFAULT NOW() , PRIMARY KEY (`id_tecnico`) ) ENGINE = InnoDB AUTO_INCREMENT = 2 DEFAULT CHARACTER SET = utf8 COLLATE = utf8_spanish_ci;
CREATE  TABLE IF NOT EXISTS `tipo_operacion_orden_trabajo` (  `id_tipo_operacion_orden_trabajo` INT(11) NOT NULL AUTO_INCREMENT , `nombre` TINYTEXT CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NOT NULL , PRIMARY KEY (`id_tipo_operacion_orden_trabajo`) ) ENGINE = InnoDB DEFAULT CHARACTER SET = utf8 COLLATE = utf8_spanish_ci;
CREATE  TABLE IF NOT EXISTS `operacion_orden_trabajo` ( `id_operacion` BIGINT(20) NOT NULL AUTO_INCREMENT , `id_orden_trabajo` BIGINT(20) NOT NULL , `fecha_hora` DATETIME NOT NULL , `descripcion` TINYTEXT CHARACTER SET 'utf8' COLLATE 'utf8_spanish_ci' NOT NULL , `tipo_operacion` INT(11) NOT NULL , `id_tecnico` BIGINT(20) NOT NULL , `id_tipo_operacion_orden_trabajo` INT(11) NOT NULL , `costo` DOUBLE NULL DEFAULT 0.0 , PRIMARY KEY (`id_operacion`) , INDEX `id_orden_trabajo` (`id_orden_trabajo` ASC) , INDEX `fk_tecnico_idx` (`id_tecnico` ASC) , INDEX `fk_operacion_orden_trabajo_tipo_operacion_orden_trabajo1_idx` (`id_tipo_operacion_orden_trabajo` ASC) , CONSTRAINT `operacion_orden_trabajo_orden_trabajo` FOREIGN KEY (`id_orden_trabajo` ) REFERENCES `gestotux`.`orden_trabajo` (`id_orden_trabajo` ) ON DELETE RESTRICT ON UPDATE RESTRICT, CONSTRAINT `fk_operacion_orden_trabajo_tecnico` FOREIGN KEY (`id_tecnico` ) REFERENCES `gestotux`.`tecnico` (`id_tecnico` ) ON DELETE NO ACTION ON UPDATE NO ACTION, CONSTRAINT `fk_operacion_orden_trabajo_tipo_operacion_orden_trabajo1` FOREIGN KEY (`id_tipo_operacion_orden_trabajo` ) REFERENCES `gestotux`.`tipo_operacion_orden_trabajo` (`id_tipo_operacion_orden_trabajo` ) ON DELETE NO ACTION ON UPDATE NO ACTION ) ENGINE = InnoDB DEFAULT CHARACTER SET = utf8 COLLATE = utf8_spanish_ci;