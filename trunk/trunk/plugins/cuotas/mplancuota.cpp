#include "mplancuota.h"

#include "mitemplancuota.h"
#include "math.h"

#include <QDate>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlField>

MPlanCuota::MPlanCuota(QObject *parent) :
QSqlTableModel(parent)
{
    setTable( "plan_cuota" );
    setHeaderData( 0, Qt::Horizontal, "#Plan" );
    setHeaderData( 1, Qt::Horizontal, "#Factura" );
    setHeaderData( 2, Qt::Horizontal, "Cantidad" );
    setHeaderData( 3, Qt::Horizontal, "Periodo" );
    setHeaderData( 4, Qt::Horizontal, "Fecha inicio" );
    setHeaderData( 5, Qt::Horizontal, "Entrega inicial" );
    setHeaderData( 6, Qt::Horizontal, "Recargo total" );
}

/*!
 * \fn MPlanCuota::agregarPlanCuota( int id_factura, double cantidad, double interes, int periodo, double entrega )
 * Genera un nuevo plan de cuotas con los datos pasados como parametros
 * \param id_factura Identificador de cliente
 * \param cantidad Importe total a generar en cuotas
 * \param interes Intereses a aplicar
 * \param periodo Tipo de periodo
 * \param entrega Entrega inicial realizada
 * \param fecha_inicio Fecha desde cuando se inicia el plan de cuotas
 * \param id_plan Variable donde se devolverÃ¡ el numero de plan de cuota
 * \param cant_cuotas Cantidad de cuotas en que se dividiÃ³ el pago
 * \returns Verdadero si se pudo generar el plan y sus items
 */
bool MPlanCuota::agregarPlanCuota( int id_factura, double cantidad, double interes, int periodo, double entrega, QDate fecha_inicio, int cant_cuotas, int *id_plan )
{
    // Verifico los parametros
    if( id_factura <= 0 && cantidad <= 0.0 && interes <= 0.0 && periodo <= 0  ) {
        qWarning( "Parametros de plan de cuota incorrecto" );
        return false;
    }

    QSqlRecord rec = this->record();
    rec.setValue( "id_factura", id_factura );
    rec.setValue( "cantidad", cantidad );
    rec.setValue( "periodo", periodo );
    rec.setValue( "fecha_inicio", fecha_inicio );
    rec.setValue( "entrega", entrega );
    rec.setGenerated( rec.indexOf( "id_plan_cuota" ), true );
    if( this->insertRecord( -1, rec ) ) {
        // Genero los items de cuota
        *id_plan = rec.value( "id_plan_cuota" ).toInt();
        // Calculo los valores
        double impcuota = ( cantidad - entrega ) * ( 1 + interes/100 );
        double importe = impcuota/cant_cuotas;
        QDate fecha_venc = fecha_inicio.addDays( diasEnPeriodo( periodo, fecha_inicio ) );
        // Genero los elementos de el plan de cuotas
        for( int i = 0; i < cant_cuotas; i++ ) {
            if( !MItemPlanCuota::agregarItem( *id_plan, i+1, fecha_venc, importe ) ) {
                qDebug( "Error al agregar un item del plan de cuotas" );
                *id_plan = -1;
                return false;
            } else {
                // Actualizo la fecha de la proxima cuota
                fecha_venc.addDays( diasEnPeriodo( periodo, fecha_venc ) );
            }
        }
        return true;
    } else {
        qWarning( "Error al intentar insertar el registro del plan de cuotas" );
        qDebug( "Error al insertrecord de plan_cuota" );
        qDebug( this->lastError().text().toLocal8Bit() );
        qDebug( this->query().lastQuery().toLocal8Bit() );
        return false;
    }
}

/*!
 * \fn MPlanCuota::diasEnPeriodo( const int tipo_periodo, QDate fecha_inicio )
 * Considerando que todos los periodos se ajustan dentro de un aÃ±o, devolverÃ¡ el numero de dÃ­as que tiene el periodo seleccionado en la fecha elegida ( sin parametro fecha actual ) segun la fecha de alta del servicio.
 * En el caso de que sea mensual, se devolverÃ¡ la cantidad de dÃ­as que tiene el mes de fecha_calculo
 * En el caso de que sea bimestral, se devolverÃ¡ la cantidad de dÃ­as que tiene el mes de fecha_calculo mas la cantidad de dÃ­as que tiene el mes siguiente.
 * En el caso de que sea trimestra, se devolverÃ¡ la cantidad de dÃ­as que tiene el mes de fecha_calculo mas la cantidad de dÃ­as que tienen los 2 meses siguientes.
 * @param tipo_periodo Tipo de periodo que estamos considerando
 * @param fecha_inicio Fecha que se desea averiguar el periodo ( predeterminada fecha actual )
 * @return Cantidad de DÃ­as que tiene el periodo que corresponde a la fecha solicitada
 */
int MPlanCuota::diasEnPeriodo( const int tipo_periodo, QDate fecha_calculo )
{
    switch( tipo_periodo )
    {
        case MPlanCuota::Semanal:
        {
            // Semanal -> La semana siempre tiene 7 dias independientemente del dÃ­a del mes
            /// \todo Corte anual Â¿Considerarlo? ( cuando la semana no esta completa un aÃ±o )
            return 7;
        }
        case MPlanCuota::Quincenal:
        {
            // Quincenal -> se considera como "medio mes"
            if( floor( fecha_calculo.daysInMonth() / 2 ) > fecha_calculo.day() ) {
                // Segunda quincena
                QDate f1(floor( fecha_calculo.daysInMonth() / 2 ), fecha_calculo.month(), fecha_calculo.year() );
                QDate f2(  fecha_calculo.year(), fecha_calculo.month(),fecha_calculo.daysInMonth() );
                return f1.daysTo( f2 ) - 1;
            } else {
                // Primera quincena
                QDate f1( fecha_calculo.year(), fecha_calculo.month(), 1 );
                QDate f2( fecha_calculo.year(), fecha_calculo.month(), floor( fecha_calculo.daysInMonth() / 2 ) );
                return f1.daysTo( f2 ) - 1;
            }
        }
        case MPlanCuota::Mensual:
        {
            // Mensual
            // Verificar el mes del periodo y devolver la cantidad de di­as
            return QDate( fecha_calculo.year(), fecha_calculo.month(), 1 ).daysInMonth();
            // Eso se encarga automaticamnete de los aÃ±os bisiestos
        }
        case MPlanCuota::BiMensual:
        {
            // BiMensual
            // Siempre voy a pedir estos datos al inicio del periodo
            QDate f1( fecha_calculo.year(), fecha_calculo.month(), 1 );
            QDate f2 = f1.addMonths(1);
            QDate f3( f2.year(), f2.month(),f2.daysInMonth() );
            return f1.daysTo( f3 ) - 1;
        }
        case MPlanCuota::Trimestral:
        {
            // Trimensual
            // Siempre voy a pedir estos datos al inicio del periodo
            QDate f1( fecha_calculo.year(), fecha_calculo.month(), 1 );
            QDate f2 = f1.addMonths(2);
            QDate f3( f2.year(), f2.month(), f2.daysInMonth() );
            return f1.daysTo( f3 ) - 1;
        }
        case MPlanCuota::Cuatrimestral:
        {
            // Cuatrimestral
            // Siempre voy a pedir estos datos al inicio del periodo
            QDate f1( fecha_calculo.year(), fecha_calculo.month(), 1 );
            QDate f2 = f1.addMonths(3);
            QDate f3( f2.year(), f2.month(), f2.daysInMonth() );
            return f1.daysTo( f3 ) -1 ;
        }
        case MPlanCuota::Seximestral:
        {
            //Seximestral
            // Siempre voy a pedir estos datos al inicio del periodo
            QDate f1( fecha_calculo.year(), fecha_calculo.month(), 1 );
            QDate f2 = f1.addMonths(5);
            QDate f3(  f2.year(), f2.month(), f2.daysInMonth() );
            return f1.daysTo( f3 ) - 1 ;
        }
        case MPlanCuota::Anual:
        {
            // Como consideramos los servicios con base en 1 aÃ±o, siempre es periodo 1
            return fecha_calculo.daysInYear() -1 ;
        }
        default:
        { return 0; }
    }
}

/*!
 * \brief MPlanCuota::asociarConFactura
 * \param id_plan Plan al cual asociar el identificador de factura
 * \param id_factura Identificador de la factura al cual pertenece
 */
void MPlanCuota::asociarConFactura(int id_plan, int id_factura)
{
    QSqlQuery cola;
    if( cola.exec( QString( "UPDATE cuotas SET id_factura = %2 WHERE id_plan_cuota = %1" ).arg( id_factura ).arg( id_plan ) ) ) {
        qDebug( "Plan de cuotas actualizado correctamente" );
    } else {
        qWarning( "No se pudo asociar la cuota" );
        qDebug( "Error al ejecutar la cola de actualziaciÃ³n de id de factura en el plan  de cuotas" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
    }
}
