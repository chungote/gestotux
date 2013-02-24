CREATE TABLE IF NOT EXISTS "tecnico" ("id_tecnico" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "razon_social" TEXT NOT NULL  UNIQUE , "habilitado" BOOL NOT NULL  DEFAULT 0 );
CREATE TABLE IF NOT EXISTS "tipo_operacion_orden_trabajo" ( "id_tipo_operacion_orden_trabajo" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "nombre" TEXT NOT NULL UNIQUE );
CREATE TABLE IF NOT EXISTS "equipamiento" ( "id_equipamiento" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, "descripcion" TEXT NOT NULL, "marca" TEXT NULL DEFAULT NULL, "modelo" TEXT NULL DEFAULT NULL, "numero_serie" TEXT NULL DEFAULT NULL, "fecha_compra" TEXT DEFAULT NULL, "fecha_vencimiento" TEXT DEFAULT NULL, "id_factura" INTEGER DEFAULT NULL );
INSERT OR IGNORE INTO sqlite_sequence VALUES ( 'tecnico', '1' );
INSERT OR IGNORE INTO sqlite_sequence VALUES ( 'tipo_operacion_orden_trabajo', '1' );
INSERT OR IGNORE INTO sqlite_sequence VALUES ( 'equipamiento', '1' );