#ifndef MCOBROSERVICIOCLIENTESERVICIO_H
#define MCOBROSERVICIOCLIENTESERVICIO_H

#include <QObject>

class MCobroServicioClientePeriodo : public QObject
{
    Q_OBJECT
public:
    explicit MCobroServicioClientePeriodo(QObject *parent = 0);

    static bool agregarCobro( const int id_cobro_servicio, const int id_servicio, const int id_cliente, const int id_factura );
    static bool setearIDCtaCte( const int id_cobro_servicio, const int id_servicio, const int id_cliente, const int id_op_ctacte );
    static double buscarNoPagados( const int id_cliente, const int id_servicio, const int id_cobro_servicio );
    static bool verificarIdFactura( const int id_factura );
    static bool colocarComoPagado( const int id_factura );

};

#endif // MCOBROSERVICIOCLIENTESERVICIO_H
