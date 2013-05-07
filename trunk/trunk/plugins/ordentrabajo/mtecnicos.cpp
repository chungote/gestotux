#include "mtecnicos.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

MTecnicos::MTecnicos(QObject *parent) :
    QSqlTableModel(parent)
{
    setTable( "tecnico" );
    setHeaderData( 0, Qt::Horizontal, "#ID" );
    setHeaderData( 1, Qt::Horizontal, "Razon Social" );
    setHeaderData( 2, Qt::Horizontal, "Habilitado" );
    setEditStrategy( QSqlTableModel::OnFieldChange );
}

bool MTecnicos::existe(const QString nombre)
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT COUNT(razon_social) FROM tecnico WHERE razon_social = %1" ).arg( nombre ) ) ) {
        cola.next();
        if( cola.record().value(0).toInt() > 0 ) {
            return true;
        }
    } else {
        qDebug( "Error al ejecutar la cola de contabilidad de cantidad de tecnicos en el sistema" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
    }
    return false;
}

bool MTecnicos::tieneDatosRelacionados( const int id_tecnico )
{
    /// @todo Implementar esto
    return true;
}

/*
 CREATE TABLE IF NOT EXISTS `tecnico` (
    `id_tecnico` bigint(20) NOT NULL AUTO_INCREMENT,
    `razon_social` tinytext NOT NULL,
    `habilitado` boolean NOT NULL,
    PRIMARY KEY (`id_tecnico`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
*/