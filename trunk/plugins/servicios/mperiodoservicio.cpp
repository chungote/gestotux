#include <QDate>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include "mservicios.h"
#include "mperiodoservicio.h"
#include "math.h"

MPeriodoServicio::MPeriodoServicio(QObject *parent) :
    QSqlRelationalTableModel(parent) {
    inicializar();
}


void MPeriodoServicio::inicializar() {
    setTable( "periodo_servicio" );
    setHeaderData( 0, Qt::Horizontal, "#ID" );
    setHeaderData( 1, Qt::Horizontal, "#Servicio" );
    setHeaderData( 2, Qt::Horizontal, "Fecha" );
    setHeaderData( 3, Qt::Horizontal, "Periodo" );
    setHeaderData( 4, Qt::Horizontal, "Año" );
    setHeaderData( 5, Qt::Horizontal, "Fecha de Inicio" );
    setHeaderData( 6, Qt::Horizontal, "Fecha de Fin" );
}

void MPeriodoServicio::relacionar() {
    setRelation( 1, QSqlRelation( "id_servicio", "servicios", "nombre" ) );
}

/*!
 * \fn MPeriodoServicio::agregarPeriodoServicio( const int id_servicio, const int periodo, const int ano )
 * Agrega el registro de que se realizo el cobro de un servicio identificado mediante la factura en un periodo del servicio.
 * @param id_servicio Identificador del servicio a facturar
 * @param periodo Numero de periodo dentro del año
 * @param ano Año del cobro
 * @return Verdadero si se pudo agregar
 */
int MPeriodoServicio::agregarPeriodoServicio( const int id_servicio, const int periodo, const int ano )
{
 QSqlQuery cola;
 cola.prepare( "INSERT INTO periodo_servicio( id_servicio, periodo, ano, fecha_inicio, fecha_fin ) VALUES( :id_servicio, :periodo, :ano, :fecha_inicio, :fecha_fin )" );
 cola.bindValue( ":id_servicio", id_servicio );
 cola.bindValue( ":periodo", periodo );
 cola.bindValue( ":ano", ano );
 // Calculo las fechas
 QDate fecha_inicio = ultimaFechaDeServicio( id_servicio );
 if( !fecha_inicio.isValid() ) {
     return -1;
 }
 QDate fecha_fin = obtenerFechaFinPeriodo( id_servicio, fecha_inicio );
 cola.bindValue( ":fecha_inicio", fecha_inicio );
 cola.bindValue( ":fecha_fin", fecha_fin );
 //cola.bindValue( ":fecha", fecha_generado ); Este lo genera solo la base de datos mysql
 if( cola.exec() ) {
     return true;
 } else {
     qDebug( "Servicios::MPeriodoServicio::agregarPeriodoServicio - Error al intentar agregar el periodo de un servicio ( exec )" );
     qDebug( QString( cola.lastError().text() ).toLocal8Bit() );
     return -1;
 }
}

/*!
 * \fn MPeriodoServicio::ultimaFechaDeServicio( const int id_servicio )
 * Devuelve la ultima fecha en que se realizo un registro de periodo de servicio. Si no existe fecha registrada hasta ese momento, retorna el día de ayer.
 * \param id_servicio Identificador del servicio
 * \return QDate con la fecha, si hubo un error, retorna una fecha invalida
 */
QDate MPeriodoServicio::ultimaFechaDeServicio( const int id_servicio ) {
  QSqlQuery cola;
  if( cola.exec( QString( "SELECT MAX( fecha_fin ) FROM periodo_servicio WHERE id_servicio = %1" ).arg( id_servicio ) ) ) {
      if( cola.next() ) {
          return cola.record().value(0).toDate();
      } else {
          qDebug( "Servicios::MPeriodoServicio::ultimaFechaDeServicio : Error al hacer next en la cola -  Se tomará la fecha de hoy" );
          qDebug( cola.lastError().text().toLocal8Bit() );
          qDebug( cola.lastQuery().toLocal8Bit() );
          return QDate::currentDate().addDays( -1 );
      }
  } else {
      qDebug( "Servicios::MPeriodoServicio::ultimaFechaDeServicio : Error al hacer next en la cola -  Se tomará la fecha de hoy" );
      qDebug( cola.lastError().text().toLocal8Bit() );
      qDebug( cola.lastQuery().toLocal8Bit() );
      return QDate();
  }
}

/*!
 * \fn MPeriodoSerivicio::obtenerFechaFinPeriodo( const int id_servicio, const QDate fecha_inicio )
 * Obtiene la fecha de fin del periodo dado un serivicio determinado y la fecha de inicio pasada como parametro
 * \param id_servicio Servicio en cuestion
 * \param fecha_inicio Fecha desde la cual calcular el periodo
 * \return Fecha de fin o una fecha invalida si hubo error
 */
QDate MPeriodoServicio::obtenerFechaFinPeriodo( const int id_servicio, const QDate fecha_inicio ) {
    MServicios::Periodo p = MServicios::obtenerPeriodo( id_servicio );
    if( p != MServicios::Invalido ) {
        return fecha_inicio.addDays( diasEnPeriodo( p, fecha_inicio ) );
    }
    return QDate();
}

/*!
 * \fn MPeriodoServicio::diasEnPeriodoServicio( const int id_periodo, QDate fecha_calculo )
 * Considerando que todos los periodos se ajustan dentro de un año, devolverá el numero de días que tiene el periodo del servicio seleccionado en la fecha elegida ( sin parametro fecha actual ) segun la fecha de alta del servicio.
 * En el caso de que sea mensual, se devolverá la cantidad de días que tiene el mes de fecha_calculo
 * En el caso de que sea bimestral, se devolverá la cantidad de días que tiene el mes de fecha_calculo mas la cantidad de días que tiene el mes siguiente.
 * En el caso de que sea trimestra, se devolverá la cantidad de días que tiene el mes de fecha_calculo mas la cantidad de días que tienen los 2 meses siguientes.
 * @param id_servicio Identificador del servicio
 * @param fecha_calculo Fecha que se desea averiguar el periodo ( predeterminada fecha actual )
 * @return Cantidad de Días que tiene el periodo que corresponde a la fecha solicitada
 */
int MPeriodoServicio::diasEnPeriodoServicio( const int id_servicio, QDate fecha_calculo ) {
    int tipo = MServicios::obtenerPeriodo( id_servicio );
    return diasEnPeriodo( tipo, fecha_calculo );
}


/*!
 * \fn MPeriodoServicio::diasEnPeriodo( const int id_periodo, QDate fecha_calculo )
 * Considerando que todos los periodos se ajustan dentro de un año, devolverá el numero de días que tiene el periodo seleccionado en la fecha elegida ( sin parametro fecha actual ) segun la fecha de alta del servicio.
 * En el caso de que sea mensual, se devolverá la cantidad de días que tiene el mes de fecha_calculo
 * En el caso de que sea bimestral, se devolverá la cantidad de días que tiene el mes de fecha_calculo mas la cantidad de días que tiene el mes siguiente.
 * En el caso de que sea trimestra, se devolverá la cantidad de días que tiene el mes de fecha_calculo mas la cantidad de días que tienen los 2 meses siguientes.
 * @param id_periodo Tipo de periodo que estamos considerando
 * @param fecha_calculo Fecha que se desea averiguar el periodo ( predeterminada fecha actual )
 * @return Cantidad de Días que tiene el periodo que corresponde a la fecha solicitada
 */
int MPeriodoServicio::diasEnPeriodo( const int tipo_periodo, QDate fecha_calculo )
{
    // Cuidado con los mensuales! ( feb en año bisiesto )
    switch( tipo_periodo )
    {
        case MServicios::Semanal:
        {
            // Semanal -> La semana siempre tiene 7 dias independientemente del día del mes
            // Corte anual ¿Considerarlo? ( cuando la semana no esta completa un año )
            return 7;
        }
        case MServicios::Quincenal:
        {
            // Quincenal -> se considera como "medio mes"
            // Verificar caso de febrero y meses con 30 o 31 días
            return 14;
        }
        case MServicios::Mensual:
        {
            // Mensual
            // Verificar el mes del periodo y devolver la cantidad de días
            return QDate( 1, fecha_calculo.month(), fecha_calculo.year() ).daysInMonth() - 1;
            // Eso se encarga automaticamnete de los años bisiestos
        }
        case MServicios::BiMensual:
        {
            // BiMensual
            // Siempre voy a pedir estos datos al inicio del periodo
            QDate f1( 0, fecha_calculo.month(), fecha_calculo.year() );
            QDate f2 = f1.addMonths(1);
            QDate f3( f2.daysInMonth(), f2.month(), f2.year() );
            return f1.daysTo( f3 ) - 1;
        }
        case MServicios::Trimestral:
        {
            // Trimensual
            // Siempre voy a pedir estos datos al inicio del periodo
            QDate f1( 0, fecha_calculo.month(), fecha_calculo.year() );
            QDate f2 = f1.addMonths(2);
            QDate f3( f2.daysInMonth(), f2.month(), f2.year() );
            return f1.daysTo( f3 );
        }
        case MServicios::Cuatrimestral:
        {
            // Cuatrimestral
            // Siempre voy a pedir estos datos al inicio del periodo
            QDate f1( 0, fecha_calculo.month(), fecha_calculo.year() );
            QDate f2 = f1.addMonths(3);
            QDate f3( f2.daysInMonth(), f2.month(), f2.year() );
            return f1.daysTo( f3 );
        }
        case MServicios::Seximestral:
        {
            //Seximestral
            // Siempre voy a pedir estos datos al inicio del periodo
            QDate f1( 0, fecha_calculo.month(), fecha_calculo.year() );
            QDate f2 = f1.addMonths(5);
            QDate f3( f2.daysInMonth(), f2.month(), f2.year() );
            return f1.daysTo( f3 );
        }
        case MServicios::Anual:
        {
            // Como consideramos los servicios con base en 1 año, siempre es periodo 1
            return fecha_calculo.daysInYear();
        }
        default:
        { return 0; }
    }
}

/*!
 * \fn MPeriodoServicio::getPeriodoActual( const int id_servicio )
 * Devuelve el numero de periodo correspondiente al servicio a facturar de acuerdo con los ultimos datos dados
 * \param id_servicio Identificador del servicio
 * \returns identificador dentro del numero de periodos o -1 si hubo un error.
 */
int MPeriodoServicio::getPeriodoActual( const int id_servicio ) {
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT periodo, fecha_fin FROM periodo_servicio WHERE id_servicio = %1 ORDER BY fecha_fin LIMIT 1" ).arg( id_servicio ) ) ) {
        if( cola.next() ) {
            return cola.record().value(0).toInt();
        } else {
            // No hay ningun registro todavía - Es el primer periodo a registrar
            QDate fecha_alta_servicio = MServicios::getFechaAlta( id_servicio );
            qDebug( QString( "Fecha alta Servicio: %1 " ).arg( fecha_alta_servicio.toString() ).toLocal8Bit() );
            QDate hoy = QDate::currentDate();
            qDebug( QString( "Fecha hoy: %1 " ).arg( hoy.toString() ).toLocal8Bit() );
            int cant_dias_periodo = diasEnPeriodoServicio( id_servicio, hoy );
            qDebug( QString( "cantidad días periodo: %1 " ).arg( cant_dias_periodo ).toLocal8Bit() );
            // Calculo
            int t = fecha_alta_servicio.daysTo( hoy );
            qDebug( QString( "t: %1 " ).arg( t ).toLocal8Bit() );
            double u = t/cant_dias_periodo;
            qDebug( QString( "u: %1 " ).arg( u ).toLocal8Bit() );
            return floor( u );
        }
    } else {
        qDebug( "Servicios::MPeriodoServicio::getPeriodoActual: Error en el exec de la cola actual" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
        return -1;
    }
}

/*!
 * \fn MPeriodoServicio::getAnoActual( const int id_servicio )
 * Devuelve el numero de año correspondiente al servicio a facturar de acuerdo con los ultimos datos dados
 * \param id_servicio Identificador del servicio
 * \returns identificador del año o -1 si hubo un error.
 */
int MPeriodoServicio::getAnoActual( const int id_servicio ) {
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT ano, fecha_fin FROM periodo_servicio WHERE id_servicio = %1 ORDER BY fecha_fin DESC LIMIT 1" ).arg( id_servicio ) ) ) {
        if( cola.next() ) {
            return cola.record().value(0).toInt();
        } else {
            // No hay ningun registro todavía - Es el primer periodo a registrar
            //qDebug( "Devolviendo el año actual - Ningun registro anterior" );
            return QDate::currentDate().year();
        }
    } else {
        qDebug( "Servicios::MPeriodoServicio::getPeriodoActual: Error en el exec de la cola actual" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
        return -1;
    }
}

/*!
 * \fn MPeriodoServicio::getFechaInicioPeriodoActual( const int id_servicio )
 * Devuelve la fecha de inicio del periodo correspondiente al servicio a facturar de acuerdo con los ultimos datos dados
 * \param id_servicio Identificador del servicio
 * \returns identificador del año o -1 si hubo un error.
 */
QDate MPeriodoServicio::getFechaInicioPeriodoActual( const int id_servicio ) {
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT fecha_inicio, fecha_fin FROM periodo_servicio WHERE id_servicio = %1 ORDER BY fecha_fin DESC LIMIT 1" ).arg( id_servicio ) ) ) {
        if( cola.next() ) {
            return cola.record().value(0).toDate();
        } else {
            // No hay ningun registro todavía - Es el primer periodo a registrar
            switch( MServicios::obtenerPeriodo( id_servicio ) ) {
                case MServicios::Semanal: {
                    return QDate::currentDate().addDays( - (QDate::currentDate().dayOfWeek() - 1 ) );
                    break;
                }
                case MServicios::Quincenal: {
                    return QDate::currentDate().addDays( - ( QDate::currentDate().dayOfWeek() - 1) ).addDays( diasEnPeriodo( id_servicio, QDate::currentDate() ) );
                    break;
                }
                case MServicios::Mensual:
                case MServicios::BiMensual:
                case MServicios::Trimestral:
                case MServicios::Cuatrimestral:
                case MServicios::Seximestral:
                case MServicios::Anual:
                {
                    return QDate( QDate::currentDate().year(), QDate::currentDate().month(), 1 ); break;
                }
                default: { qDebug( "Periodo invalido" ); return QDate(); break; }
            }
            qDebug( "Periodo Invalido" );
            return QDate();
        }
    } else {
        qDebug( "Servicios::MPeriodoServicio::getFechaInicioPeriodoActual: Error en el exec de la cola actual" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
        return QDate();
    }
}

/*!
 * \fn MServicios::getCantidadDiasPeriodo( const int id_servicio, const QDate fecha_calculo )
 * Devuelve la cantidad de días en el periodo del servicio solicitado. Utilitaria.
 * @param id_servicio Identificador del servicio al cual se le quiere saber la cantidad de días.
 * @param fecha_calculo utilizado para referencia en @MSercicios::getCantidadDiasEnPeriodo
 * @return Cantidad de días en el periodo del servicio
 */
/*
int MServicios::getCantidadDiasPeriodo( const int id_servicio, const QDate fecha_calculo )
{
    QSqlQuery cola( QString( "SELECT periodo FROM servicios WHERE id_servicio = %2" ).arg( id_servicio ) );
    if( cola.exec() ) {
        if( cola.next() ) {
            return getDiasEnPeriodo( cola.record().value(0).toInt(), fecha_calculo );
        } else {
            qDebug( "Servicios:MServicios:Error al buscar la fecha de alta del periodo y su periodo -> next" );
            return -1;
        }
    } else {
        qDebug( "Servicios:MServicios:Error al buscar la fecha de alta del periodo y su periodo  -> exec" );
        return -1;
    }
}*/