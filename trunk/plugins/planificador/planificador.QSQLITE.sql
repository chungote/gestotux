CREATE  TABLE "main"."calendarios" ("id_calendario" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "nombre" TEXT NOT NULL , "color" TEXT, "clave" TEXT NOT NULL );
CREATE  TABLE "main"."citas" ("id_cita" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "asunto" TEXT NOT NULL , "lugar" TEXT, "descripcion" TEXT, "inicio" DATETIME NOT NULL , "fin" DATETIME NOT NULL , "calendario_id" INTEGER NOT NULL );
