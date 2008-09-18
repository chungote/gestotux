BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS categoria (id INTEGER PRIMARY KEY AUTOINCREMENT, nombre TEXT, descripcion TEXT);
CREATE TABLE IF NOT EXISTS clientes (id INTEGER PRIMARY KEY AUTOINCREMENT, apellido TEXT NOT NULL, nombre TEXT NOT NULL, direccion TEXT, telefono TEXT );
CREATE TABLE IF NOT EXISTS producto (id INTEGER PRIMARY KEY AUTOINCREMENT, id_categoria NUMERIC, nombre TEXT, precio_venta NUMERIC, descripcion BLOB, marca TEXT);
CREATE TABLE IF NOT EXISTS recibos ( id INTEGER PRIMARY KEY AUTOINCREMENT, cliente TEXT, num_mes INTEGER,  texto TEXT, precio NUMBER, fecha_pago TEXT, contado INTEGER, cuenta_corriente INTEGER  );
CREATE TABLE IF NOT EXISTS presupuestos_productos ( id INTEGER PRIMARY KEY AUTOINCREMENT, id_presupuesto INTEGER NOT NULL, id_producto INTEGER NOT NULL, cantidad NUMERIC );
CREATE TABLE IF NOT EXISTS presupuestos ( id INTEGER PRIMARY KEY AUTOINCREMENT,id_cliente INTEGER NULL, destinatario TEXT NULL, fecha TEXT NOT NULL, total NUMERIC, contenido BLOB );
CREATE TABLE IF NOT EXISTS car_categorias ( id_categoria INTEGER PRIMARY KEY AUTOINCREMENT, nombre TEXT NOT NULL, especial INTEGER NULL DEFAULT '0' );
CREATE TABLE IF NOT EXISTS car_establecimientos ( id_establecimiento INTEGER PRIMARY KEY AUTOINCREMENT, nombre TEXT NOT NULL, respma TEXT NOT NULL );
CREATE TABLE IF NOT EXISTS car_caravana ( id_caravana INTEGER PRIMARY KEY AUTOINCREMENT, codigo TEXT NOT NULL UNIQUE );
CREATE TABLE IF NOT EXISTS car_tri( id_tri INTEGER PRIMARY KEY AUTOINCREMENT, dta TEXT NOT NULL, razon NUMERIC NOT NULL, guia TEXT NULL, fecha TEXT NOT NULL, id_categoria NUMERIC NOT NULL, id_estab_destino NUMERIC, id_estab_origen NUMERIC, id_comprador NUMERIC, id_vendedor NUMERIC, cantidad_caravanas INTEGER DEFAULT 0 );
CREATE TABLE IF NOT EXISTS car_carv_tri( id_caravana INTEGER, id_tri, PRIMARY KEY( id_caravana, id_tri ) );
CREATE TABLE IF NOT EXISTS car_carv_duenos ( id_caravana INTEGER, id_cliente INTEGER, fecha_inicio TEXT NOT NULL, fecha_fin TEXT, PRIMARY KEY( id_caravana, id_cliente ) );
INSERT INTO sqlite_sequence VALUES ( 'car_tri', '0' );
INSERT INTO sqlite_sequence VALUES ( 'car_categorias', '0' );
INSERT INTO sqlite_sequence VALUES ( 'car_establecimientos', '0' );
INSERT INTO sqlite_sequence VALUES ( 'car_caravana', '0' );
INSERT INTO sqlite_sequence VALUES ( 'car_carav_tri', '0' );
INSERT INTO sqlite_sequence VALUES ( 'categoria', '0' );
INSERT INTO sqlite_sequence VALUES ( 'clientes', '0' );
INSERT INTO sqlite_sequence VALUES ( 'producto', '0' );
INSERT INTO sqlite_sequence VALUES ( 'recibos', '0' );
