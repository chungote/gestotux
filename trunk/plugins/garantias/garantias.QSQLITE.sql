CREATE TABLE IF NOT EXISTS "garantias" ("id_garantia" INTEGER PRIMARY KEY  NOT NULL , "codigo_garantia" VARCHAR(45) NOT NULL, "fecha_inicio" TEXT,"fecha_fin" DATETIME DEFAULT null, "id_cliente" BIGINT(10) NOT NULL , "id_equipamiento" BIGINT(20) NOT NULL ,"id_factura" BIGINT(20) NOT NULL, "fecha_baja" DATE, "razon_baja" TEXT );
CREATE VIEW IF NOT EXISTS "v_garantia_svg" AS SELECT  g.id_garantia AS id_garantia, strftime( '%d', g.fecha_inicio ) AS dia, strftime( '%m', g.fecha_inicio ) AS mes, strftime( '%Y', g.fecha_inicio ) AS ano, g.id_garantia AS numero_garantia, c.razon_social AS razon_social, e.descripcion AS nombre_producto, e.numero_serie AS  numero_serie, e.id_factura_compra AS numero_comprobante, g.fecha_inicio AS fecha_inicio, g.fecha_fin AS fecha_fin  FROM garantias AS g  INNER JOIN clientes AS c ON g.id_cliente = c.id INNER JOIN equipamiento AS e ON g.id_equipamiento = e.id_equipamiento;