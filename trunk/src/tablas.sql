BEGIN TRANSACTION;
CREATE TABLE categoria (id INTEGER PRIMARY KEY AUTOINCREMENT, nombre TEXT, descripcion TEXT);
CREATE TABLE clientes (id INTEGER PRIMARY KEY AUTOINCREMENT, apellido TEXT, nombre TEXT, direccion TEXT, telefono TEXT);
CREATE TABLE producto (id INTEGER PRIMARY KEY AUTOINCREMENT, id_categoria NUMERIC, nombre TEXT, precio_venta NUMERIC, descripcion BLOB, marca TEXT);
CREATE TABLE recibos ( id INTEGER PRIMARY KEY AUTOINCREMENT, cliente TEXT, num_mes INTEGER,  texto TEXT, precio NUMBER, fecha_pago TEXT, contado INTEGER, cuenta_corriente INTEGER  );
CREATE TABLE car_categorias ( id_categoria INTEGER  PRIMARY KEY AUTOINCREMENT,  nombre TEXT )
COMMIT;
