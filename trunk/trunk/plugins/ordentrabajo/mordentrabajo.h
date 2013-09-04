#ifndef MORDENTRABAJO_H
#define MORDENTRABAJO_H

#include <QSqlRelationalTableModel>
#include "NumeroComprobante.h"
#include <QSqlRecord>
#include <QDateTime>

class MOrdenTrabajo : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    MOrdenTrabajo( QObject *parent = 0 );
    static bool tieneDatosRelacionados( const int id_orden_trabajo );

    static NumeroComprobante numeroComprobanteProximo();
    static NumeroComprobante numeroComprobanteSegunId( const int id_orden );
    static int idSegunNumeroComprobante( NumeroComprobante num );

    int obtenerIdEquipamientoSegunId( const int id_orden );

    void cargarDatos( const int id_orden );
    int idCliente() { return _data.value("id_cliente").toInt(); }
    int idTecnico() { return _data.value("id_tecnico").toInt(); }
    QString requerente() { return _data.value( "requerente" ).toString(); }
    QString ingresante() { return _data.value( "ingresante" ).toString(); }
    QDateTime fechaDevolucion() { return _data.value("fecha_devolucion").toDateTime(); }
    QDateTime fechaIngreso() { return _data.value("fecha_ingreso").toDateTime(); }

private:
    QSqlRecord _data;
    int _id_orden_trabajo;
};

#endif // MORDENTRABAJO_H
