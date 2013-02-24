CREATE TABLE IF NOT EXISTS "tecnico" ("id_tecnico" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "razon_social" TEXT NOT NULL  UNIQUE , "habilitado" BOOL NOT NULL  DEFAULT 0 );
CREATE TABLE IF NOT EXISTS "tipo_operacion_orden_trabajo" ( "id_tipo_operacion_orden_trabajo" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "nombre" TEXT NOT NULL UNIQUE );
INSERT OR IGNORE INTO sqlite_sequence VALUES ( 'tecnico', '1' );
INSERT OR IGNORE INTO sqlite_sequence VALUES ( 'tipo_operacion_orden_trabajo', '1' );