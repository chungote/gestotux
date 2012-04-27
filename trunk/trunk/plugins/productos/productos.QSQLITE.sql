CREATE TABLE IF NOT EXISTS producto (id INTEGER PRIMARY KEY AUTOINCREMENT, id_categoria NUMERIC, codigo TEXT NOT NULL, nombre TEXT NOT NULL, precio_costo NUMERIC NULL, precio_venta NUMERIC, descripcion BLOB, marca TEXT, stock NUMERIC DEFAULT NULL, habilitado NUMERIC NOT NULL DEFAULT 1, modelo TEXT NULL );
CREATE TABLE IF NOT EXISTS categoria_producto (id INTEGER PRIMARY KEY AUTOINCREMENT, nombre TEXT, descripcion TEXT );
INSERT INTO sqlite_sequence VALUES ( 'categoria_producto', '0' );
INSERT INTO sqlite_sequence VALUES ( 'producto', '0' );