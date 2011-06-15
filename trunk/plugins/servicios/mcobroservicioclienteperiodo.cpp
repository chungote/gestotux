#include "mcobroservicioclienteperiodo.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

MCobroServicioClientePeriodo::MCobroServicioClientePeriodo(QObject *parent) :
    QObject(parent) {
}

/*!
 * \fn MCobroServicioClientePeriodo::agregarCobro( const int id_periodo_servicio, const int id_servicio, const int id_cliente )
 */
bool MCobroServicioClientePeriodo::agregarCobro( const int id_periodo_servicio, const int id_servicio, const int id_cliente, const int id_factura ) {
    QSqlQuery cola;
    cola.prepare( "INSERT INTO cobro_servicio_cliente_periodo( id_periodo_servicio, id_servicio, id_cliente, id_factura, id_ctacte, id_recibo ) VALUES ( :id_periodo_servicio, :id_servicio, :id_cliente, :id_factura, :id_ctacte, :id_recibo )" );
    cola.bindValue( ":id_periodo_servicio", id_periodo_servicio );
    cola.bindValue( ":id_cliente", id_cliente );
    cola.bindValue( ":id_servicio", id_servicio );
    cola.bindValue( ":id_factura", id_factura );
    cola.bindValue( ":id_ctacte", QVariant() );
    cola.bindValue( ":id_recibo", QVariant() );
    if( cola.exec() ) {
        return true;
    } else {
        qDebug( "Servicios::MCobroServicioClientePeriodo::agregarCobro - Error al intentar agregar el cobro de un servicio para un cliente( exec )" );
        qDebug( QString( cola.lastError().text() ).toLocal8Bit() );
        return false;
    }
}

/*!
 * \fn MCobroServicioClientePeriodo::setearIDCtaCte( const int id_periodo_servicio, const int id_servicio, const int id_cliente, const int id_op_ctacte )
 */
bool MCobroServicioClientePeriodo::setearIDCtaCte( const int id_periodo_servicio, const int id_servicio, const int id_cliente, const int id_op_ctacte ) {
    QSqlQuery cola;
    if( cola.exec(
                QString( "UPDATE cobro_servicio_cliente_periodo SET id_ctacte = %1 WHERE id_periodo_servicio = %2 AND id_servicio = %4 AND id_cliente = %3" ).
                arg( id_op_ctacte ).arg( id_periodo_servicio ).arg( id_cliente ).arg( id_servicio )
        ) ) {
        return true;
    } else {
        qDebug( "Servicios::MCobroServicioClientePeriodo::agregarCobro - Error al intentar asetear el id de operacion de cuenta corriente en el cobro de un servicio para un cliente( exec )" );
        qDebug( QString( cola.lastError().text() ).toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
        return false;
    }
}

#include "mitemcuentacorriente.h"
#include <QSqlRecord>
#include <QSqlError>

double MCobroServicioClientePeriodo::buscarNoPagados( const int id_cliente, const int id_servicio, const int id_periodo_servicio ) {
    double ret = 0;
    QSqlQuery cola;
    cola.prepare( "SELECT id_op_ctacte FROM cobro_servicio_cliente_periodo WHERE id_periodo_servicio = :id_periodo_servicio AND id_servicio = :id_servicio AND id_cliente = :id_cliente AND id_recibo = NUL" );
    cola.bindValue( ":id_periodo_servicio", id_periodo_servicio );
    cola.bindValue( ":id_cliente", id_cliente );
    cola.bindValue( ":id_servicio", id_servicio );
    if( cola.exec() ) {
        // cada registro devuelto es un id de item de cuenta corriente -  sumo sus importes
        while( cola.next() ) {
            ret += MItemCuentaCorriente::valorOperacion( cola.record().value(0).toInt() );
        }
        return ret;
    } else {
        qDebug( "Servicios::MCobroServicioClienteServicio::buscarNoPagados - Error al intentar buscar los ids de operaciones en ctacte de los items no pagados" );
        qDebug( QString( cola.lastError().text() ).toLocal8Bit() );
        return -1;
    }

}

/*
CREATE TABLE IF NOT EXISTS `cobro_servicio_cliente_periodo` (
    `id_periodo_servicio` BIGINT NOT NULL,
    `id_servicio` BIGINT NOT NULL,
    `id_cliente` BIGINT NOT NULL,
    `id_factura` BIGINT NOT NULL,
    `id_recibo` BIGINT DEFAULT NULL,
    `id_ctacte` BIGINT NOT NULL,
    FOREIGN KEY ( id_periodo_servicio ) REFERENCES `periodo_servicio`( id_periodo_servicio ),
    FOREIGN KEY ( id_servicio, id_cliente ) REFERENCES `servicios_clientes`( id_servicio, id_cliente ),
    FOREIGN KEY ( id_factura ) REFERENCES `factura`( id_factura ),
    FOREIGN KEY ( id_ctacte ) REFERENCES `item_ctacte`(id_op_ctacte),
    FOREIGN KEY ( id_recibo ) REFERENCES `recibos`( id_recibo ),
    PRIMARY KEY ( id_periodo_servicio, id_servicio, id_cliente )
) ENGINE = InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
*/