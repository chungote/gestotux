#ifndef MHISTORIALORDENTRABAJO_H
#define MHISTORIALORDENTRABAJO_H

#include <QSqlRelationalTableModel>

class MHistorialOrdenTrabajo : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    MHistorialOrdenTrabajo( QObject *parent = 0 );
    
};

#endif // MHISTORIALORDENTRABAJO_H
