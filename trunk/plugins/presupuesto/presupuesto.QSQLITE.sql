CREATE TABLE IF NOT EXISTS presupuestos ( id INTEGER PRIMARY KEY AUTOINCREMENT, id_cliente INTEGER NULL, destinatario TEXT NULL, direccion TEXT NULL, fecha TEXT NOT NULL, total NUMERIC, contenido BLOB, serie NUMERIC NOT NULL, numero NUMERIC NOT NULL );
CREATE TABLE IF NOT EXISTS item_presupuesto ( id_item_presupuesto INTEGER PRIMARY KEY AUTOINCREMENT, id_presupuesto INTEGER NOT NULL, cantidad DOUBLE NOT NULL, texto TEXT NOT NULL, precio_unitario DOUBLE NOT NULL, id_producto NUMERIC );