CREATE TABLE IF NOT EXISTS compras ( id INTEGER PRIMARY KEY AUTOINCREMENT,id_proveedor NUMERIC NOT NULL, fecha TEXT NOT NULL, total NUMERIC NOT NULL, id_caja NUMERIC NULL, "contado" BOOL NOT NULL  DEFAULT 1 );
CREATE TABLE IF NOT EXISTS compras_productos ( id INTEGER PRIMARY KEY AUTOINCREMENT, id_compra NUMERIC , id_producto NUMERIC  , precio_compra NUMERIC , cantidad NUMERIC  );
INSERT OR IGNORE INTO "sqlite_sequence" VALUES( 'compras', '1' );
INSERT OR IGNORE INTO "sqlite_sequence" VALUES( 'compras_productos', '1' );