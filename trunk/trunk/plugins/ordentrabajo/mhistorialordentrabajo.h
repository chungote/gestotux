#ifndef MHISTORIALORDENTRABAJO_H
#define MHISTORIALORDENTRABAJO_H

#include <QSqlRelationalTableModel>
#include <QHash>
#include <QDateTime>

class MHistorialOrdenTrabajo : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    MHistorialOrdenTrabajo( QObject *parent = 0 );
    ~MHistorialOrdenTrabajo();
    QVariant data( const QModelIndex &item, int role ) const;
    
    static bool agregarHistorial( const int id_orden_trabajo, QDateTime fecha_hora, QString descripcion, double costo, const int tipo_operacion, const int id_tecnico );

    void setearOrdenTrabajo( const int id_orden_trabajo );
    void mostrarCostosSumados();

private:
    bool _mostrar_suma_costos;
    QMap<int,double> *_sumas;
    int _id_orden_trabajo;
};

#endif // MHISTORIALORDENTRABAJO_H
