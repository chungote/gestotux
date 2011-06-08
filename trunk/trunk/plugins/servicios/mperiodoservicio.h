#ifndef MPERIODOSERVICIO_H
#define MPERIODOSERVICIO_H

#include <QSqlRelationalTableModel>


/*!
  \brief Clase para administrar los periodos de los servicios

  Clase que permite la administración y calculos sobre y desde los periodos de los servicios
  \author Esteban Zeller <tranfuga25s@gmail.com>
  \date
 */
class MPeriodoServicio : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit MPeriodoServicio(QObject *parent = 0);
    void inicializar();
    void relacionar();
    static int agregarPeriodoServicio( const int id_servicio, const int periodo, const int ano );
    static QDate ultimaFechaDeServicio( const int id_servicio );
    static QDate obtenerFechaFinPeriodo( const int id_servicio, const QDate fecha_inicio );
    int getPeriodoActual( const int id_servicio );
    int getAnoActual( const int id_servicio );
    QDate getFechaInicioPeriodoActual( const int id_servicio );

private:
    static int diasEnPeriodo( const int id_servicio, const QDate fecha_inicio );
    static int diasEnPeriodoServicio( const int id_servicio, QDate fecha_calculo );
};

#endif // MPERIODOSERVICIO_H
