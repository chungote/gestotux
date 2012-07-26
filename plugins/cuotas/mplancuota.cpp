#include "mplancuota.h"

#include <QDate>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>

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
 * \returns Verdadero si se pudo generar el plan y sus items
 */
bool MPlanCuota::agregarPlanCuota( int id_factura, double cantidad, double interes, int periodo, double entrega, QDate fecha_inicio )
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
    if( this->insertRecord( -1, rec ) ) {
        // ¿Genero los items de cuota?
        return true;
    } else {
        qWarning( "Error al intentar insertar el registro del plan de cuotas" );
        qDebug( "Error al insertrecord de plan_cuota" );
        qDebug( this->lastError().text().toLocal8Bit() );
        qDebug( this->query().lastQuery().toLocal8Bit() );
        return false;
    }


}
