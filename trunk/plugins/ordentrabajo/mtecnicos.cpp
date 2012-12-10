#include "mtecnicos.h"

#include <QSqlQuery>
#include <QSqlRecord>

MTecnicos::MTecnicos(QObject *parent) :
    QSqlTableModel(parent)
{
    setTable( "tecnico" );
    setHeaderData( 0, Qt::Horizontal, "#ID" );
    setHeaderData( 1, Qt::Horizontal, "Razon Social" );
    setHeaderData( 2, Qt::Horizontal, "Habilitado" );
}

bool MTecnicos::existe(const QString nombre)
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT COUNT(razon_social) FROM tecnico WHERE razon_social = %1" ).arg( nombre ) ) ) {
        cola.next();
        if( cola.record().value(0).toInt() > 0 ) {
            return true;
        }
    }
    return false;
}

/*
 CREATE TABLE IF NOT EXISTS `tecnico` (
    `id_tecnico` bigint(20) NOT NULL AUTO_INCREMENT,
    `razon_social` tinytext NOT NULL,
    `habilitado` boolean NOT NULL,
    PRIMARY KEY (`id_tecnico`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
*/