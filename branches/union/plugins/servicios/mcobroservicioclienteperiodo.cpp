#include "mcobroservicioclienteperiodo.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

MCobroServicioClientePeriodo::MCobroServicioClientePeriodo(QObject *parent) :
    QObject(parent) {
}

/*!
 * \fn MCobroServicioClientePeriodo::agregarCobro( const int id_periodo_servicio, const int id_servicio, const int id_cliente, const int id_factura )
 * Genera una nueva entrada en cobro de un serivicio a un cliente con la factura correspondiente.
 * Si esta activo el plugin HiComp utilizarà un recibo
 * \param id_periodo_servicio Identificador del periodo del servicio
 * \param id_servicio Identificador del servicio
 * \param id_cliente Identificador del cliente
 * \param id_factura Identificador del comprobante
 * \returns Verdadero si se pudo agregar, falso en caso contrario.
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
 * Setea el ID de el registro de cuenta corriente para un cobro de un servicio a un cliente en un periodo determinado.
 * \param id_periodo_servicio Identificador del periodo del servicio
 * \param id_servicio Identificador del servicio
 * \param id_cliente Identificador del cliente
 * \param id_op_ctacte Identificador del movimiento de cuenta corriente.
 * \returns Verdadero si se pudo setear, falso en caso contrario.
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
/*!
 * \fn MCobroServicioClientePeriodo::buscarNoPagados( const int id_cliente, const int id_servicio, const int id_periodo_servicio )
 * Busca el total de todo lo no pagado para el cliente respecto a un servicio en un periodo.
 * \param id_cliente Identificador del cliente.
 * \param id_servicio identificador del servicio
 * \param id_periodo_servicio Identificador del periodo del servicio.
 * \return Sumatoria de todos los registros encontrados respectoa los parametros pasados.
 */
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
        qDebug( cola.lastError().text().toLocal8Bit() );
        return -1;
    }

}

/*!
 * \fn MCobroServicioClientePeriodo::verificarIdFactura( const int id_factura )
 * Verifica si existe algun id_factura que corresponda con el parametro pasado. Si la factura corresponde a un servicio devuelve true.
 * \param id_factura Identificador de factura
 * \returns verdadero si corresponde a un cobro de servicio.
 */
bool MCobroServicioClientePeriodo::verificarIdFactura( const int id_factura ) {
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT COUNT( id_factura ) FROM cobro_servicio_cliente_periodo WHERE id_factura = %1" ).arg( id_factura ) ) ) {
        if( cola.next() ) {
            if( cola.record().value(0).toInt() > 0 ) {
                return true;
            }
        } else {
            qDebug( "MCobroServicioClientePeriodo::verificarIdFactura::Error de next en la cola" );
            qDebug( cola.lastError().text().toLocal8Bit() );
        }
    } else {
        qDebug( "MCobroServicioClientePeriodo::verificarIdFactura::Error de exec en la cola" );
        qDebug( cola.lastError().text().toLocal8Bit() );
    }
    return false;
}

/*!
 * \fn MCobroServicioClientePeriodo::colocarComoPagado( const int id_factura, const int id_recibo )
 * Coloca como pagado el registro de cobro de servicio correspondiente a la factura pasada como parametro con el recibo pasado como parametro
 * \param id_factura Identificador de factura.
 * \param id_recibo Identificador del recibo que paga esta factura
 * \returns verdadero si se pudo realizar el cambio.
 */
bool MCobroServicioClientePeriodo::colocarComoPagado( const int id_factura, const int id_recibo ) {
    QSqlQuery cola;
    if( cola.exec( QString( "UPDATE FROM cobro_servicio_cliente_periodo SET id_recibo = %1 WHERE id_factura = %2 LIMIT 1" ).arg( id_recibo ).arg( id_factura ) ) ) {
        return true;
    } else {
        qDebug( "MCobroServicioClientePeriodo::colocarComoPagado::Error al intentar colocar como pagado un cobro de servicio. Error de exec." );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
        return false;
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
    FOREIGN KEY ( id_factura ) REFERENCES `factura`( id_factura ), // Eso no se hace cuando esta presente el plugin de HiComp
    FOREIGN KEY ( id_ctacte ) REFERENCES `item_ctacte`(id_op_ctacte),
    FOREIGN KEY ( id_recibo ) REFERENCES `recibos`( id_recibo ),
    PRIMARY KEY ( id_periodo_servicio, id_servicio, id_cliente )
) ENGINE = InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
*/