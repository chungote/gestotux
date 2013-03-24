#include "mplancuota.h"

#include "mitemplancuota.h"
#include "math.h"

#include <QDate>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlField>
#include <QSqlDriver>

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
 * \param cant_cuotas Cantidad de cuotas en que se dividio el pago
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
    rec.setValue( "recargo", interes );
    //rec.setGenerated( rec.indexOf( "id_plan_cuota" ), true );
    if( this->insertRecord( -1, rec ) ) {
        // Genero los items de cuota
        if( QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).driver()->hasFeature( QSqlDriver::LastInsertId ) ) {
           *id_plan =this->query().lastInsertId().toInt();
           //qWarning( QString( "Numero de plan de cuota emitido: %1" ).arg( *id_plan ).toLocal8Bit() );
        } else {
           QSqlQuery cola;
           if( cola.exec( "SELECT MAX( id_plan_cuota ) FROM plan_cuota" ) ) {
               cola.next();
               *id_plan = cola.record().value(0).toInt();
               //qWarning( QString( "Numero de plan de cuota emitido: %1" ).arg( *id_plan ).toLocal8Bit() );
           } else {
               qDebug( "Error de obtencion del id del registro de plan de cuota" );
               qDebug( QString( "Detalles: tipo: %1, errno: %2, descripcion: %3" ).arg( cola.lastError().type() ).arg( cola.lastError().number() ).arg( cola.lastError().text() ).toLocal8Bit() );
               qDebug( cola.lastQuery().toLocal8Bit() );
               return -1;
           }
        }

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
            // Como consideramos los servicios con base en 1 año, siempre es periodo 1
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
void MPlanCuota::asociarConFactura( int id_plan, int id_factura )
{
    if( id_factura <= 0 && id_plan <= 0 ) {
        qWarning( "Numero de factura o plan invalido!" );
        return;
    }
    QSqlQuery cola;
    if( cola.exec( QString( "UPDATE plan_cuota SET id_factura = %1 WHERE id_plan_cuota = %2" ).arg( id_factura ).arg( id_plan ) ) ) {
        qDebug( "Plan de cuotas actualizado correctamente" );
    } else {
        qWarning( "No se pudo asociar el plan de cuotas con la factura recién emitida!" );
        qDebug( "Error al ejecutar la cola de actualziacion de id de factura en el plan  de cuotas" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
    }
}

/*!
 * \brief MPlanCuota::obtenerRazonSocial
 * Devuelve la razón social del cliente asociado con el plan de cuotas pasado como parametro
 * \param id_plan Identificador del plan de cuotas
 * \return Razon social del cliente o nulo si no se encuentra el cliente.
 */
QString MPlanCuota::obtenerRazonSocial( const int id_plan )
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT c.razon_social FROM plan_cuota AS pc, clientes AS c, factura AS f WHERE c.id = f.id_cliente AND f.id_factura = pc.id_factura AND pc.id_plan_cuota = %1" ).arg( id_plan ) ) ) {
        if( cola.next() ) {
            return cola.record().value(0).toString();
        } else {
            qDebug( "Error de next al obtención de razon social de un plan de cuotas" );
            qDebug( cola.lastQuery().toLocal8Bit() );
        }
    } else {
        qDebug( "Error al ejecutar la cola de obtención de razon social de un plan de cuotas" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
    }
    return QString();
}

/*!
 * \brief MPlanCuota::obtenerEstadoCuotas
 * Devuelve el par de datos cantidad_cuotas/cuotas_pagadas de un plan de cuotas.
 * \param id_plan Identificador del plan de cuotas
 * \return los datos o un par -1,-1 si hubo un error.
 */
QPair<int, int> MPlanCuota::obtenerEstadoCuotas( const int id_plan )
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT pc.cantidad_cuotas, COUNT( ic.id_item_cuota ) FROM plan_cuota AS pc, item_cuota AS ic WHERE ic.id_plan_cuota = pc.id_plan_cuota AND pc.id_plan_cuota = %1" ).arg( id_plan ) ) ) {
        if( cola.next() ) {
            return QPair<int,int>( cola.record().value(0).toInt(), cola.record().value(1).toInt() );
        } else {
            qDebug( "Error de next al obtención de cantidad de cuotas de un plan de cuotas" );
            qDebug( cola.lastQuery().toLocal8Bit() );
        }
    } else {
        qDebug( "Error al ejecutar la cola de obtención de cantidad de cuotas de un plan de cuotas" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
    }
    return QPair<int,int>( -1, -1 );
}

/*!
 * \brief MPlanCuota::obtenerEstadoImportes
 * Devuelve el par de datos cantidad pagada/importe total del plan de cuotas
 * \param id_plan Identificador del plan
 * \return importes mencionados o -1.0/-1.0
 */
QPair<double, double> MPlanCuota::obtenerEstadoImportes(const int id_plan)
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT SUM( ic.monto ), f.total FROM plan_cuota AS pc, item_cuota AS ic, factura AS f WHERE ic.id_plan_cuota = pc.id_plan_cuota AND f.id_factura = pc.id_factura AND pc.id_plan_cuota = %1" ).arg( id_plan ) ) ) {
        if( cola.next() ) {
            return QPair<double,double>( cola.record().value(0).toDouble(), cola.record().value(1).toDouble() );
        } else {
            qDebug( "Error de next al obtención de estado financiero de un plan de cuotas" );
            qDebug( cola.lastQuery().toLocal8Bit() );
        }
    } else {
        qDebug( "Error al ejecutar la cola de obtención de estado financiero de un plan de cuotas" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
    }
    return QPair<double,double>( -1.0, -1.0 );
}
