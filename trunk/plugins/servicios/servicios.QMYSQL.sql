CREATE TABLE `servicios` (
  `id_servicio` bigint(1) NOT NULL auto_increment,
  `nombre` tinytext NOT NULL,
  `fecha_alta` date NOT NULL,
  `fecha_baja` date NULL,
  `precio_base` double(10,3) NOT NULL,
  `periodo` int(10) NOT NULL,
  `dia_cobro` int(10) NOT NULL,
  `forma_incompleto` int(10) NOT NULL,
  PRIMARY KEY  (`id_servicio`)
);
CREATE TABLE `servicios_cliente` (
  `id_servicio` bigint(1) NOT NULL auto_increment,
  `id_cliente` tinytext NOT NULL,
  `fecha_alta` date NOT NULL,
  `fecha_baja` date NULL,
  PRIMARY KEY  (`id_servicio`, `id_cliente` )
);
CREATE TABLE `recargos` (
  `id_recargo` bigint(1) NOT NULL auto_increment,
  `id_servicio` bigint(1) NOT NULL,
  `cant_dias` int(1) NOT NULL,
  `porcentaje` double(2,2) default NULL,
  `recargo` double(10,3) default NULL,
  PRIMARY KEY  (`id_recargo`)
);