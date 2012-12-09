#include "mtecnicos.h"

MTecnicos::MTecnicos(QObject *parent) :
    QSqlTableModel(parent)
{
    setTable( "tecnico" );
    setHeaderData( 0, Qt::Horizontal, "#ID" );
    setHeaderData( 1, Qt::Horizontal, "Razon Social" );
    setHeaderData( 2, Qt::Horizontal, "Habilitado" );
}

/*
 CREATE TABLE IF NOT EXISTS `tecnico` (
    `id_tecnico` bigint(20) NOT NULL AUTO_INCREMENT,
    `razon_social` tinytext NOT NULL,
    `habilitado` boolean NOT NULL,
    PRIMARY KEY (`id_tecnico`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
*/