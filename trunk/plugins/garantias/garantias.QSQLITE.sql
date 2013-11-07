CREATE TABLE IF NOT EXISTS "garantias" ( "id_garantia" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, "fecha_inicio" TEXT NULL, "fecha_fin" DATETIME NULL, "id_cliente" INTEGER NOT NULL, "id_equipamiento" INTEGER NOT NULL, "id_factura" INTEGER NOT NULL, "codigo_garantia" TEXT NULL );