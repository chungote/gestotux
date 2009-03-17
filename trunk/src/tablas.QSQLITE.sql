BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS clientes (id INTEGER PRIMARY KEY AUTOINCREMENT, apellido TEXT NOT NULL, nombre TEXT NOT NULL, direccion TEXT, telefono TEXT );
CREATE TABLE IF NOT EXISTS servidores_email ( "id_server" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "nombre" TEXT NOT NULL, "direccion" TEXT NOT NULL, "puerto" INTEGER, "usuario" TEXT NOT NULL, "pass" TEXT NOT NULL, "predeterminado" INTEGER NOT NULL DEFAULT (0) );
INSERT INTO sqlite_sequence VALUES ( 'clientes', '1' );
INSERT INTO sqlite_sequence VALUES ( 'servidores_email', '1' );


