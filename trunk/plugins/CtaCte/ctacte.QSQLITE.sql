CREATE TABLE IF NOT EXISTS "ctacte" ("numero_cuenta" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "id_cliente" INTEGER NOT NULL , "fecha_alta" DATETIME NOT NULL  DEFAULT CURRENT_DATE, "fecha_baja" DATETIME, "saldo" DOUBLE NOT NULL  DEFAULT 0, "limite" DOUBLE NOT NULL DEFAULT 1, "suspendida" INTEGER NOT NULL DEFAULT 0 );
CREATE TABLE IF NOT EXISTS "item_ctacte" ("id_op_ctacte" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "fecha" DATETIME NOT NULL  DEFAULT CURRENT_DATE, "id_referencia" INTEGER NOT NULL , "tipo_op" TEXT NOT NULL , "descripcion" TEXT, "debe" DOUBLE, "haber" DOUBLE, "id_ctacte" INTEGER NOT NULL , "numero_comprobante" TEXT);
INSERT OR IGNORE INTO "sqlite_sequence" ( "name", "seq" ) VALUES ( "item_ctacte", 1 );