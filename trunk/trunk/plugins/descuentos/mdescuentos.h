#ifndef MDESCUENTOS_H
#define MDESCUENTOS_H

#include <QSqlTableModel>

class MDescuentos : public QSqlTableModel
{
    Q_OBJECT
public:
    enum Tipo {
        Invalido = 0,
        Presupuesto = 1,
        Factura = 2
    };

    MDescuentos( QObject *parent = 0 );
    bool agregarDescuento( Tipo t, int id_comprobante, QString texto, double porcentaje );
    
};

#endif // MDESCUENTOS_H
