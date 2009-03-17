BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS clientes (id INTEGER PRIMARY KEY AUTOINCREMENT, apellido TEXT NOT NULL, nombre TEXT NOT NULL, direccion TEXT, telefono TEXT );
CREATE TABLE IF NOT EXISTS `autos` ( `patente` TEXT PRIMARY KEY, `id_dueno` INTEGER REFERENCES `clientes`(`id`), `marca` text NOT NULL, `modelo` text, `ano` TEXT default NULL, `color` text );
CREATE TABLE IF NOT EXISTS `presupuesto` ( `id_presupuesto` INTEGER PRIMARY KEY AUTOINCREMENT, `fecha` TEXT NOT NULL, `kilometraje` INTEGER NOT NULL, `id_auto` TEXT REFERENCES `autos`(`patente`), `total` NUMERIC NOT NULL,`titulo` text, `memo` text, `contenido` blob, `creado` text NOT NULL, `modificado` TEXT , `imprimir` INTEGER, `email` INTEGER );
INSERT INTO "sqlite_sequence" VALUES('presupuesto',1);
INSERT INTO "sqlite_sequence" VALUES('clientes',1);
COMMIT;