CREATE TABLE IF NOT EXISTS categoria (id INTEGER PRIMARY KEY AUTOINCREMENT, nombre TEXT, descripcion TEXT, "tipo" INTEGER  NOT NULL  DEFAULT (1));
CREATE TABLE IF NOT EXISTS gastos ( id INTEGER PRIMARY KEY AUTOINCREMENT, id_categoria INTEGER, descripcion TEXT, costo INTEGER, fecha TEXT );
INSERT OR IGNORE INTO "sqlite_sequence" VALUES( 'categoria', '1' );
INSERT OR IGNORE INTO "sqlite_sequence" VALUES( 'gastos', '1' );