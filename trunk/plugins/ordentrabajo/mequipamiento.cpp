#include "mequipamiento.h"

/*
CREATE TABLE IF NOT EXISTS `equipamiento` (
    `id_equipamiento` bigint(20) NOT NULL AUTO_INCREMENT,
    `descripcion` tinytext NOT NULL,
    `marca` tinytext NULL DEFAULT NULL,
    `modelo` tinytext NULL DEFAULT NULL,
    `numero_serie` tinytext NULL DEFAULT NULL,
    `fecha_compra` datetime DEFAULT NULL,
    `fecha_vencimiento` date DEFAULT NULL,
    `id_factura` bigint(20) DEFAULT NULL,
    PRIMARY KEY (`id_equipamiento`),
    FOREIGN KEY (`id_factura`) REFERENCES `factura`(`id_factura`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
*/

MEquipamiento::MEquipamiento(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
    setTable( "equipamiento" );
    setHeaderData( 0, Qt::Horizontal, "#ID" );
    setHeaderData( 1, Qt::Horizontal, "Descripcion" );
    setHeaderData( 2, Qt::Horizontal, "Marca" );
    setHeaderData( 3, Qt::Horizontal, "Modelo" );
    setHeaderData( 4, Qt::Horizontal, "#Serie" );
    setHeaderData( 5, Qt::Horizontal, "Fecha de Compra" );
    setHeaderData( 6, Qt::Horizontal, "Fecha Vencimiento" );
    setHeaderData( 7, Qt::Horizontal, "#Factura" );
}

/*!
 * \brief MEquipamiento::tieneDatosRelacionados
 * Busca si el elemento posee alguna relación con los otros datos de las tablas.
 * \param id_equipamiento Identificador del equipamiento
 * \return Verdadero si hay alguna relacion
 */
bool MEquipamiento::tieneDatosRelacionados( const int id_equipamiento )
{
    qDebug( "Busqueda de elementos relacionados a un equipamiento no implementados" );
    /// @TODO Implementar datos relacionados equipamiento
    return true;
}
