BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS clientes ( "id" INTEGER PRIMARY KEY autoincrement, "razon_social" TEXT NOT NULL,"nombre" TEXT NOT NULL,"segundo" TEXT DEFAULT null,"apellido" TEXT DEFAULT null, "calle" TEXT DEFAULT null, "numero" INTEGER DEFAULT null, "piso" INTEGER DEFAULT null,"depto" INTEGER DEFAULT null,"ciudad" TEXT DEFAULT null,"codigo_postal" TEXT DEFAULT null, "provincia" TEXT DEFAULT null,"pais" TEXT DEFAULT null,"tel_fijo" TEXT DEFAULT null,"tel_celular" TEXT DEFAULT null,"fax" TEXT DEFAULT null,"email" TEXT DEFAULT null, "comprobante_email" INTEGER DEFAULT 1 );
INSERT INTO sqlite_sequence VALUES ( 'clientes', '1' );
COMMIT;

