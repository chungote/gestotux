CREATE TABLE IF NOT EXISTS proveedor ( id INTEGER PRIMARY KEY AUTOINCREMENT, nombre TEXT NOT NULL UNIQUE, direccion BLOB, email TEXT, fax TEXT, telefono_celular TEXT, telefono_linea TEXT, cuit_cuil TEXT NULL UNIQUE );
INSERT OR IGNORE INTO "sqlite_sequence" VALUES( 'proveedor', '0' );