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