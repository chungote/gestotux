CREATE TABLE IF NOT EXISTS "main"."recibos" ("id_recibo" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL  UNIQUE , "id_cliente" INTEGER NOT NULL , "fecha_pago" DATETIME NOT NULL  DEFAULT CURRENT_TIME, "texto" TEXT, "precio" FLOAT NOT NULL  DEFAULT 0, "cancelado" BOOL NOT NULL  DEFAULT 0, "pagado" BOOL NOT NULL  DEFAULT 1, "serie" INTEGER NOT NULL, "numero" INTEGER NOT NULL, "id_caja" INTEGER DEFAULT NULL )