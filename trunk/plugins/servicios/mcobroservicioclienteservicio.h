#ifndef MCOBROSERVICIOCLIENTESERVICIO_H
#define MCOBROSERVICIOCLIENTESERVICIO_H

#include <QSqlRelationalTableModel>

class MCobroServicioClienteServicio : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit MCobroServicioClienteServicio(QObject *parent = 0);

    static bool agregarCobro( const int id_cobro_servicio, const int id_servicio, const int id_cliente, const int id_factura );
    static bool setearIDCtaCte( const int id_cobro_servicio, const int id_servicio, const int id_cliente, const int id_op_ctacte );
    static double buscarNoPagados( const int id_cliente, const int id_servicio, const int id_cobro_servicio );

};

#endif // MCOBROSERVICIOCLIENTESERVICIO_H
