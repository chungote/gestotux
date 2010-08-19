CREATE  TABLE "main"."caja" ("id_caja" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "nombre" TEXT NOT NULL , "fecha_alta" DATETIME NOT NULL , "saldo" DOUBLE NOT NULL )
CREATE  TABLE "main"."movimiento_caja" ("id_movimiento" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "fecha_hora" DATETIME NOT NULL  DEFAULT CURRENT_TIME, "debe" DOUBLE NOT NULL  DEFAULT 0, "haber" DOUBLE NOT NULL  DEFAULT 0, "razon" TEXT NOT NULL , "responsable" TEXT NOT NULL )