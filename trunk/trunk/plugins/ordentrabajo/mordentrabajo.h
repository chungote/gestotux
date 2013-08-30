#ifndef MORDENTRABAJO_H
#define MORDENTRABAJO_H

#include <QSqlRelationalTableModel>
#include "NumeroComprobante.h"

class MOrdenTrabajo : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    MOrdenTrabajo( QObject *parent = 0 );
    static bool tieneDatosRelacionados( const int id_orden_trabajo );

    static NumeroComprobante numeroComprobanteProximo();
    static NumeroComprobante numeroComprobanteSegunId( const int id_orden );
    static int idSegunNumeroComprobante( NumeroComprobante num );
};

#endif // MORDENTRABAJO_H
