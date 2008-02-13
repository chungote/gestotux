BEGIN TRANSACTION;
CREATE TABLE categoria (id INTEGER PRIMARY KEY, nombre TEXT, descripcion TEXT);

CREATE TABLE clientes (id INTEGER PRIMARY KEY, apellido TEXT, nombre TEXT, direccion TEXT, telefono TEXT);
CREATE TABLE producto (id INTEGER PRIMARY KEY, id_categoria NUMERIC, nombre TEXT, precio_venta NUMERIC, descripcion BLOB, marca TEXT);
CREATE TABLE recibos ( id INTEGER PRIMARY KEY AUTOINCREMENT, cliente TEXT, num_mes INTEGER,  texto TEXT, precio NUMBER, fecha_pago TEXT, contado INTEGER, cuenta_corriente INTEGER  );
CREATE TABLE sqlite_sequence(name,seq);
COMMIT;
