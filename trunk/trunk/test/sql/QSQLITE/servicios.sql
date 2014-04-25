CREATE TABLE IF NOT EXISTS "servicios" ("id_servicio" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "nombre" TEXT NOT NULL , "descripcion" TEXT, "fecha_alta" DATETIME NOT NULL , "fecha_baja" DATETIME, "precio_base" DOUBLE NOT NULL , "periodo" INTEGER NOT NULL , "dia_cobro" INTEGER NOT NULL , "forma_incompleto" INTEGER NOT NULL );