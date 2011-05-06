CREATE TABLE IF NOT EXISTS `presupuestos` (
  `id_presupuesto` bigint NOT NULL AUTO_INCREMENT,
  `id_cliente` bigint REFERENCES clientes(id),
  `destinatario` text DEFAULT NULL,
  `fecha` datetime DEFAULT CURRENT_TIMESTAMP,
  `total` decimal NOT NULL,
  `serie` bigint NOT NULL,
  `numero` bigint NOT NULL,
  PRIMARY KEY (`id_presupuesto`),
  UNIQUE KEY `presupuesto-serie-numero` (`serie`,`numero`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE TABLE IF NOT EXISTS `presupuesto_items` (
  `id_presupuesto_item` bigint NOT NULL,
  `id_presupuesto` bigint,
  `cantidad` double NOT NULL,
  `texto` text NOT NULL,
  `precio_unitario` double NOT NULL,
  `id_producto` bigint NULL,
  PRIMARY KEY (`id_presupuesto_item`, `id_presupuesto` )
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;