CREATE TABLE IF NOT EXISTS producto (id INTEGER PRIMARY KEY AUTOINCREMENT, id_categoria NUMERIC, nombre TEXT, precio_venta NUMERIC, descripcion BLOB, marca TEXT);
CREATE TABLE IF NOT EXISTS categoria_producto (id INTEGER PRIMARY KEY AUTOINCREMENT, nombre TEXT, descripcion TEXT, tipo NUMERIC );
INSERT INTO sqlite_sequence VALUES ( 'categoria', '0' );
INSERT INTO sqlite_sequence VALUES ( 'producto', '0' );