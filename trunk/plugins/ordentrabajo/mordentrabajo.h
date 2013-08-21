#ifndef MORDENTRABAJO_H
#define MORDENTRABAJO_H

#include <QSqlRelationalTableModel>

class MOrdenTrabajo : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    MOrdenTrabajo( QObject *parent = 0 );
    static bool tieneDatosRelacionados( const int id_orden_trabajo );
    
};

#endif // MORDENTRABAJO_H
