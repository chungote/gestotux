BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS ventas ( id INTEGER PRIMARY KEY AUTOINCREMENT, fecha TEXT );
CREATE TABLE IF NOT EXISTS ventas_productos ( id INTEGER PRIMARY KEY AUTOINCREMENT, id_venta NUMERIC , id_producto NUMERIC , precio NUMERIC , cantidad NUMERIC );
CREATE TABLE IF NOT EXISTS lista_precio ( id_lista_precio INTEGER PRIMARY KEY AUTOINCREMENT, nombre TEXT, descripcion TEXT, recargo NUMERIC, habilitado NUMERIC DEFAULT 1 );
INSERT OR IGNORE INTO sqlite_sequence VALUES ( 'ventas_productos', '1');
INSERT OR IGNORE INTO sqlite_sequence VALUES ( 'ventas', '1' );
INSERT OR IGNORE INTO sqlite_sequence VALUES ( 'lista_precio', '1' );
COMMIT;