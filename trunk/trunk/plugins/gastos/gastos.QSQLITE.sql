CREATE TABLE IF NOT EXISTS categoria_gastos (id INTEGER PRIMARY KEY AUTOINCREMENT, nombre TEXT, descripcion TEXT );
CREATE TABLE IF NOT EXISTS gastos ( id_gasto INTEGER PRIMARY KEY AUTOINCREMENT, id_categoria INTEGER, descripcion TEXT, costo INTEGER, fecha TEXT, id_caja INTEGER );
INSERT OR IGNORE INTO "sqlite_sequence" VALUES( 'categoria_gastos', '1' );
INSERT OR IGNORE INTO "sqlite_sequence" VALUES( 'gastos', '1' );