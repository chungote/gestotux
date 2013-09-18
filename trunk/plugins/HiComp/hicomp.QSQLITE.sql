CREATE VIEW IF NOT EXISTS "v_recibos_impagos" AS SELECT r.id_recibo AS id_recibo, substr( '0000000000' || r.serie, -5, 5 ) || '-' || substr( '0000000000' || r.numero, -5, 5 ) AS NumSerie, c.razon_social AS razon_social, r.fecha_pago AS fecha_pago, r.precio AS precio, r.cancelado AS cancelado FROM `recibos` AS r, clientes AS c WHERE r.id_cliente = c.id AND r.forma_pago = 0 AND pagado IN ( 'false', 0 );