CREATE TABLE IF NOT EXISTS `clientes` ( `id` bigint(10) NOT NULL auto_increment, `razon_social` tinytext NOT NULL, `nombre` tinytext, `apellido` tinytext, `calle` tinytext, `numero` int(2) default NULL, `piso` int(2) default NULL, `depto` tinytext, `ciudad` tinytext, `codigo_postal` tinytext, `provincia` tinytext, `pais` tinytext, `tel_fijo` tinytext, `tel_celular` tinytext, `fax` tinytext, `email` tinytext, `comprobante_email` tinyint(1) default '1', `ctacte` tinyint(1) default NULL, `CUIT/CUIL` tinytext default null, PRIMARY KEY  (`id`) ) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
CREATE TABLE IF NOT EXISTS `report` ( `report_id` int(11) NOT NULL AUTO_INCREMENT, `report_name` text, `report_descrip` text NOT NULL, `report_grade` int(11) NOT NULL DEFAULT '0', `report_source` longtext,  PRIMARY KEY (`report_id`) ) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
INSERT INTO `clientes` (`id`, `razon_social`, `nombre` ) VALUES ( 0, 'Consumidor Final', 'Consumidor Final' );