#include "mtipooperacionordentrabajo.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
/*
CREATE TABLE IF NOT EXISTS `tipo_operacion_orden_trabajo` (
    `id_tipo_operacion_orden_trabajo` int(11) NOT NULL AUTO_INCREMENT,
    `nombre` tinytext NOT NULL,
    PRIMARY KEY (`id_tipo_operacion_orden_trabajo`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
*/

MTipoOperacionOrdenTrabajo::MTipoOperacionOrdenTrabajo( QObject *parent ) :
QSqlTableModel( parent )
{
    setTable( "tipo_operacion_orden_trabajo" );
    setHeaderData( 0, Qt::Horizontal, "#ID" );
    setHeaderData( 1, Qt::Horizontal, "Nombre del tipo" );
}

bool MTipoOperacionOrdenTrabajo::existe( const QString nombre )
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT COUNT(nombre) FROM tipo_operacion_orden_trabajo WHERE nombre = %1" ).arg( nombre ) ) ) {
        cola.next();
        if( cola.record().value(0).toInt() > 0 ) {
            return true;
        }
    } else {
        qDebug( "Error al ejecutar la cola de contabilidad de cantidad de tipo de ordenes de trabajo en el sistema" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
    }
    return false;
}

bool MTipoOperacionOrdenTrabajo::tieneDatosRelacionados( const int id_tipo )
{
    qDebug( "Buscador de datos relacionados todavía no implementado!" );
    /// @TODO Agregar busqueda de datos relacionados
    return true;
}

bool MTipoOperacionOrdenTrabajo::agregarTipo( const QString nombre )
{
    QSqlRecord r = this->record();
    r.setValue( "nombre", nombre );
    if( this->insertRecord( -1, r ) ) {
        return true;
    }
    return false;
}

bool MTipoOperacionOrdenTrabajo::modificar( const int row, const QString nombre )
{
    QSqlRecord r = this->record( row );
    r.setValue( "nombre", nombre );
    if( this->setRecord( row, r ) ) {
        return true;
    }
    return false;
}
