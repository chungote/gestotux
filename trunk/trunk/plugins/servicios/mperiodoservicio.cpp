#include <QDate>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include "mservicios.h"
#include "mperiodoservicio.h"
#include "math.h"
#include <QMessageBox>

MPeriodoServicio::MPeriodoServicio(QObject *parent) :
    QObject(parent) {
    //inicializar();
}

/*
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

*/

/*!
 * \fn MPeriodoServicio::agregarPeriodoServicio( const int id_servicio, const int periodo, const int ano, const QDate fecha_inicio, const QDate fecha_fin )
 * Agrega el registro de que se realizo el cobro de un servicio identificado mediante la factura en un periodo del servicio.
 * \param id_servicio Identificador del servicio a facturar
 * \param periodo Numero de periodo dentro del año
 * \param ano Año del cobro
 * \param fecha_inicio Fecha de inicio del periodo
 * \param fecha_fin Fecha de fin del periodo
 * \return Identificador de id_periodo_servicio o -1 si hubo un error.
 */
int MPeriodoServicio::agregarPeriodoServicio( const int id_servicio, const int periodo, const int ano, const QDate fecha_inicio, const QDate fecha_fin )
{
 QSqlQuery cola;
 cola.prepare( "INSERT INTO periodo_servicio( id_servicio, periodo, ano, fecha_inicio, fecha_fin ) VALUES( :id_servicio, :periodo, :ano, :fecha_inicio, :fecha_fin )" );
 cola.bindValue( ":id_servicio", id_servicio );
 cola.bindValue( ":periodo", periodo );
 cola.bindValue( ":ano", ano );
 cola.bindValue( ":fecha_inicio", fecha_inicio );
 cola.bindValue( ":fecha_fin", fecha_fin );
 //cola.bindValue( ":fecha", fecha_generado ); Este lo genera solo la base de datos mysql
 if( cola.exec() ) {
     return cola.lastInsertId().toInt();
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
 * \fn MPeriodoServicio::obtenerFechaFinPeriodo( const int id_servicio, const QDate fecha_inicio )
 * Obtiene la fecha de fin del periodo dado un serivicio determinado y la fecha de inicio pasada como parametro
 * \param id_servicio Servicio en cuestion
 * \param fecha_inicio Fecha desde la cual calcular el periodo
 * \return Fecha de fin o una fecha invalida si hubo error
 */
QDate MPeriodoServicio::obtenerFechaFinPeriodo( const int id_servicio, const QDate fecha_inicio ) {
    MServicios::Periodo p = MServicios::obtenerPeriodo( id_servicio );
    if( p != MServicios::Invalido ) {
        return fecha_inicio.addDays( diasEnPeriodo( p, fecha_inicio ) - 1 );
    }
    return QDate();
}

/*!
 * \fn MPeriodoServicio::diasEnPeriodoServicio( const int id_servicio, QDate fecha_calculo )
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
 * \fn MPeriodoServicio::diasEnPeriodo( const int tipo_periodo, QDate fecha_calculo )
 * Considerando que todos los periodos se ajustan dentro de un año, devolverá el numero de días que tiene el periodo seleccionado en la fecha elegida ( sin parametro fecha actual ) segun la fecha de alta del servicio.
 * En el caso de que sea mensual, se devolverá la cantidad de días que tiene el mes de fecha_calculo
 * En el caso de que sea bimestral, se devolverá la cantidad de días que tiene el mes de fecha_calculo mas la cantidad de días que tiene el mes siguiente.
 * En el caso de que sea trimestra, se devolverá la cantidad de días que tiene el mes de fecha_calculo mas la cantidad de días que tienen los 2 meses siguientes.
 * @param tipo_periodo Tipo de periodo que estamos considerando
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
            /// \todo Corte anual ¿Considerarlo? ( cuando la semana no esta completa un año )
            return 7;
        }
        case MServicios::Quincenal:
        {
            // Quincenal -> se considera como "medio mes"
            /// \todo Verificar caso de febrero y meses con 30 o 31 días
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
            return f1.daysTo( f3 ) - 1;
        }
        case MServicios::Cuatrimestral:
        {
            // Cuatrimestral
            // Siempre voy a pedir estos datos al inicio del periodo
            QDate f1( 0, fecha_calculo.month(), fecha_calculo.year() );
            QDate f2 = f1.addMonths(3);
            QDate f3( f2.daysInMonth(), f2.month(), f2.year() );
            return f1.daysTo( f3 ) -1 ;
        }
        case MServicios::Seximestral:
        {
            //Seximestral
            // Siempre voy a pedir estos datos al inicio del periodo
            QDate f1( 0, fecha_calculo.month(), fecha_calculo.year() );
            QDate f2 = f1.addMonths(5);
            QDate f3( f2.daysInMonth(), f2.month(), f2.year() );
            return f1.daysTo( f3 ) - 1 ;
        }
        case MServicios::Anual:
        {
            // Como consideramos los servicios con base en 1 año, siempre es periodo 1
            return fecha_calculo.daysInYear() -1 ;
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
            QDate hoy = QDate::currentDate();
            int cant_dias_periodo = diasEnPeriodoServicio( id_servicio, hoy );
            // Calculo
            int t = fecha_alta_servicio.daysTo( hoy );
            double u = t/cant_dias_periodo;
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
            return MPeriodoServicio::generarFechaInicioPeriodo( id_servicio, MPeriodoServicio::getPeriodoActual( id_servicio ), QDate::currentDate().year() );
        }
    } else {
        qDebug( "Servicios::MPeriodoServicio::getFechaInicioPeriodoActual: Error en el exec de la cola actual" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
        return QDate();
    }
}

/*!
 * \fn MPeriodoServicio::agregarPeriodoAFacturarNuevo( const int id_servicio )
 * Agrega un nuevo periodo a la lista de periodos de un servicio contolando que los datos sean correctos.
 * @param id_servicio Identificador del servicio que se desea
 * @returns Identificador del periodo del servicio o -1 si hubo un error
 */
int MPeriodoServicio::agregarPeriodoAFacturarNuevo( const int id_servicio ) {
    // Busca el proximo periodo a facturar y lo agrega devolviendo el id agregado
    // Busco si existe un periodo anterior
    int periodo = this->getPeriodoActual( id_servicio );
    int ano = this->getAnoActual( id_servicio );
    QDate fecha_inicio = this->getFechaInicioPeriodo( id_servicio, periodo, ano );
    QDate fecha_fin = this->obtenerFechaFinPeriodo( id_servicio, fecha_inicio );
    // Verifico
    QDate fecha_ultimo_periodo = this->getUltimaFecha( id_servicio );
    if( fecha_ultimo_periodo.isValid() ) {
        if( fecha_ultimo_periodo >= fecha_inicio ) {
            qDebug( "Error - La fecha de inicio del periodo es anterior a la fecha de fin del periodo anterior." );
            QMessageBox::warning( 0, "Control", "Ya existe un periodo que esta incluido en el periodo que intenta facturar. <br /> Seguramente ya facturo este periodo de este servicio" );
            return -1;
        }
    } else {
        qDebug( "Atencion - La ulima fecha de inicio del periodo no existe - se utilizara la generica." );
    }
    int ultimo_periodo = this->getUltimoPeriodo( id_servicio );
    if( ultimo_periodo != -1 && ultimo_periodo >= periodo ) {
        qDebug( "Error- El numero de periodo es invalido o igual que el periodo que se facturara." );
        return -1;
    }
    return this->agregarPeriodoServicio( id_servicio, periodo, ano, fecha_inicio, fecha_fin );
}


/*!
 * \fn MPeriodoServicio::getFechaInicioPeriodo( const int id_servicio, const int periodo, const int ano )
 * Devuelve la fecha de inicio del periodo solicitado
 * @param id_servicio ID del servicio elegido
 * @param periodo Periodo elegido a solicitar la fecha
 * @param ano Año solicitado
 * @returns Fecha de inicio del periodo solicitado o una fecha invalida si hubo un error.
 */
QDate MPeriodoServicio::getFechaInicioPeriodo( const int id_servicio, const int periodo, const int ano ) {
    // Busco si existe en la base de datos
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT fecha_inicio FROM periodo_servicio WHERE id_servicio = %1 AND periodo = %2 AND ano = %3" ).arg( id_servicio ).arg( periodo ).arg( ano ) ) ) {
        if( cola.next() ) {
            return cola.record().value(0).toDate();
        } else {
            // Genero la fecha ya que no existe en la base de datos
            return generarFechaInicioPeriodo( id_servicio, periodo, ano );
        }
    } else {
        qDebug( "Error al ejecutar la cola de obtención de fecha de inicio de un periodo para un servicio" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
        return QDate();
    }
    return QDate();
}

/*!
 * \fn MPeriodoServicio::getUltimaFecha( const int id_servicio )
 * Devuelve la ultima fecha de fin del servicio solicitado
 * @param id_servicio ID del servicio elegido
 * @returns Ultima fecha o una fecha invalida si no existe o hubo un error.
 */
QDate MPeriodoServicio::getUltimaFecha( const int id_servicio ) {
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT fecha_fin, periodo, ano FROM periodo_servicio WHERE id_servicio = %1 ORDER BY ano DESC, periodo DESC LIMIT 1" ).arg( id_servicio ) ) ) {
        if( cola.next() ) {
            return cola.record().value(0).toDate();
        } else {
            // No existe una fecha
            qDebug( "No existe una fecha de ultimo periodo de servicio elegido." );
            return QDate();
        }
    } else {
        qDebug( "Error al ejecutar la cola de obtención de fecha de inicio de un periodo para un servicio" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
        return QDate();
    }
    return QDate();
}

/*!
 * \fn MPeriodoServicio::generarFechaInicioPeriodo( const int id_servicio, const int periodo, const int ano )
 * Devuelve la fecha teorica del inicio del periodo segun el servicio solicitado
 * @param id_servicio ID del servicio elegido
 * @param periodo numero de periodo del servicio en el año elegido
 * @param ano Año elegido
 * @returns Fecha de inicio o fecha invalida si hubo un error.
 */
QDate MPeriodoServicio::generarFechaInicioPeriodo( const int id_servicio, const int periodo, const int ano ) {
    QDate fecha = QDate();
    switch( MServicios::obtenerPeriodo( id_servicio ) ) {
        case MServicios::Semanal:
        {
            fecha = QDate( ano, 1, 1 ).addMonths( floor( ( periodo - 1 ) / 4 ) );
            int dias_mes = fecha.daysInMonth();
            if( ( ( periodo - 1 ) % 4 ) !=  0 ) {
                fecha.addDays( -1 * floor( dias_mes / 4 ) );
            }
            break;
        }
        case MServicios::Quincenal:
        {

            fecha = QDate( ano, 1, 1 ).addMonths( floor( ( periodo - 1 ) / 2 ) );
            int dias_mes = fecha.daysInMonth();
            if( ( ( periodo - 1 ) % 2 ) !=  0 ) {
                fecha.addDays( -1 * floor( dias_mes / 2 ) );
            }
            break;
        }
        case MServicios::Mensual:
        {
            fecha = QDate( ano, 1, 1 ).addMonths( ( periodo - 1 ) );
            break;
        }
        case MServicios::BiMensual:
        {
            fecha = QDate( ano, 1, 1 ).addMonths( ( periodo - 1 ) * 2 );
            break;
        }
        case MServicios::Trimestral:
        {
            fecha = QDate( ano, 1, 1 ).addMonths( ( periodo - 1 ) * 3 );
            break;
        }
        case MServicios::Cuatrimestral:
        {
            fecha = QDate( ano, 1, 1 ).addMonths( ( periodo - 1 ) * 4 );
            break;
        }
        case MServicios::Seximestral:
        {
            fecha = QDate( ano, 1, 1 ).addMonths( ( periodo - 1 ) * 6 );
            break;
        }
        case MServicios::Anual:
        {
            if( periodo > 1 ) { qDebug( "Periodo > 1 para tipo de periodo anual. Erroneo. Corregido." ); }
            fecha = QDate( ano, QDate::currentDate().month(), 1 ); break;
        }
        default: { qDebug( "Tipo de Periodo invalido" ); return QDate(); break; }
    }
    // Chequeo que la fecha de inicio del servicio sea menor que la buscada
    QDate fecha_inicio_servicio = MServicios::getFechaAlta( id_servicio );
    if( fecha_inicio_servicio > fecha ) {
        qDebug( "Error - la fecha de inicio buscada es menor a la del servicio." );
        fecha = fecha_inicio_servicio;
    }
    return fecha;
}


/*!
 * \fn MPeriodoServicio::getUltimoPeriodo( const int id_servicio )
 * Busca el ultimo periodo facturado para el servicio solicitado
 * \param id_servicio Identificador del servicio
 * \returns Numero de periodo o -1 si hubo error o no existe.
 */
int MPeriodoServicio::getUltimoPeriodo(const int id_servicio) {
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT fecha_fin, periodo, ano FROM periodo_servicio WHERE id_servicio = %1 ORDER BY ano DESC, periodo DESC LIMIT 1" ).arg( id_servicio ) ) ) {
        if( cola.next() ) {
            return cola.record().value(1).toInt();
        } else {
            // No existe una fecha
            qDebug( "No existe un ultimo numero de periodo del servicio elegido." );
            return -1;
        }
    } else {
        qDebug( "Error al ejecutar la cola de obtención de ultimo periodo para un servicio" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
        return -1;
    }
    return -1;
}
