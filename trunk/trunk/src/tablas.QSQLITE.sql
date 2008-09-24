BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS clientes (id INTEGER PRIMARY KEY AUTOINCREMENT, apellido TEXT NOT NULL, nombre TEXT NOT NULL, direccion TEXT, telefono TEXT );
INSERT INTO sqlite_sequence VALUES ( 'clientes', '0' );


