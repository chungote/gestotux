CREATE TABLE IF NOT EXISTS ctacte ( id_op_ctacte INTEGER PRIMARY KEY AUTOINCREMENT, id_cliente INTEGER NOT NULL, fecha TEXT NOT NULL, nro_comprobante TEXT NOT NULL, descripcion TEXT default NULL,  debe NUMERIC default NULL, haber NUMERIC default NULL );