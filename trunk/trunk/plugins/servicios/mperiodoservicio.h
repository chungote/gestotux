#ifndef MPERIODOSERVICIO_H
#define MPERIODOSERVICIO_H

//#include <QSqlRelationalTableModel>
#include <QObject>
#include <QDate>

/*!
  \brief Clase para administrar los periodos de los servicios

  Clase que permite la administración y calculos sobre y desde los periodos de los servicios
  \author Esteban Zeller <tranfuga25s@gmail.com>
  \date
 */
class MPeriodoServicio : /*public QSqlRelationalTableModel*/ public QObject
{
    Q_OBJECT
public:
    explicit MPeriodoServicio(QObject *parent = 0);
    /*void inicializar();
    void relacionar();*/
    static int agregarPeriodoServicio( const int id_servicio, const int periodo, const int ano, const QDate fecha_inicio, const QDate fecha_fin );
    static QDate ultimaFechaDeServicio( const int id_servicio );
    static QDate obtenerFechaFinPeriodo( const int id_servicio, const QDate fecha_inicio );
    int agregarPeriodoAFacturarNuevo( const int id_servicio );
    int getPeriodoActual( const int id_servicio );
    int getAnoActual( const int id_servicio );
    QDate getFechaInicioPeriodoActual( const int id_servicio );

private:
    static int diasEnPeriodo( const int id_servicio, const QDate fecha_inicio );
    static int diasEnPeriodoServicio( const int tipo_periodo, QDate fecha_calculo );
    QDate getFechaInicioPeriodo( const int id_servicio, const int periodo, const int ano );
    QDate getUltimaFecha( const int id_servicio );
    int getUltimoPeriodo( const int id_servicio );
    QDate generarFechaInicioPeriodo( const int id_servicio, const int periodo, const int ano );
};

#endif // MPERIODOSERVICIO_H
