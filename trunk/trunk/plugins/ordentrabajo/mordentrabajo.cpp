#include "mordentrabajo.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>


MOrdenTrabajo::MOrdenTrabajo( QObject *parent ) :
QSqlRelationalTableModel( parent )
{
    setTable( "orden_trabajo" );
    setHeaderData( 0, Qt::Horizontal, "#ID" );
    setHeaderData( 1, Qt::Horizontal, "#Cliente" );
    setHeaderData( 2, Qt::Horizontal, "Fecha de Ingreso" );
    setHeaderData( 3, Qt::Horizontal, "Requerente" );
    setHeaderData( 4, Qt::Horizontal, "Ingresante" );
    setHeaderData( 5, Qt::Horizontal, "Fecha de Vencimiento" );
    setHeaderData( 6, Qt::Horizontal, "Fecha de Devolucion" );
    setHeaderData( 7, Qt::Horizontal, "#Equipamiento" );
    setHeaderData( 8, Qt::Horizontal, "#Factura" );
    _id_orden_trabajo = -1;
    _data = QSqlRecord();
}

/*!
 * \brief MOrdenTrabajo::tieneDatosRelacionados
 * \return
 */
bool MOrdenTrabajo::tieneDatosRelacionados( const int /* id_orden_trabajo */ )
{
    // Las ordenes de trabajo implican la eliminacion de todos los datos relacionados ( operacion_orden_trabajo )
    return false;
}

/*!
 * \brief MOrdenTrabajo::numeroComprobanteProximo
 * \return
 */
NumeroComprobante MOrdenTrabajo::numeroComprobanteProximo()
{
    QSqlQuery cola;
    if( cola.exec( "SELECT MAX(id_orden_trabajo) FROM orden_trabajo" ) ) {
        if( cola.next() ) {
            if( cola.record().value(0).toInt() > 0 ) {
                NumeroComprobante temp( 0, 0, 1 );
                temp.deNumero( cola.record().value(0).toInt() );
                temp.siguienteNumero();
                return temp;
            }
        } else {
            return NumeroComprobante( 0, 0, 1 );
        }
    } else {
        qDebug() << "Error al intentar ejecutar la cola de averiguación de numero de comprobante proximo de una orden de trabajo";
        qDebug() << cola.lastError().text();
        qDebug() << cola.lastQuery();
    }
    return NumeroComprobante( 0, -1, -1 );
}

/*!
 * \brief MOrdenTrabajo::numeroComprobanteSegunId
 * \param id_orden
 * \return
 */
NumeroComprobante MOrdenTrabajo::numeroComprobanteSegunId( const int id_orden )
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT id_orden_trabajo FROM orden_trabajo WHERE id_orden = %1" ).arg( id_orden ) ) ) {
        if( cola.next() ) {
            if( cola.record().value(0).toInt() > 0 ) {
                NumeroComprobante temp( 0, 0, 1 );
                temp.deNumero( cola.record().value(0).toInt() );
                return temp;
            }
        } else {
            qDebug() << "Error al intentar hacer next de la cola de averiguación de numero de comprobante de una orden de trabajo";
            qDebug() << cola.lastQuery();
        }
    } else {
        qDebug() << "Error al intentar ejecutar la cola de averiguación de numero de comprobante segun id de una orden de trabajo";
        qDebug() << cola.lastError().text();
        qDebug() << cola.lastQuery();
    }
    return NumeroComprobante( 0, -1, -1 );
}

/*!
 * \brief MOrdenTrabajo::idSegunNumeroComprobante
 * \param num
 * \return
 */
int MOrdenTrabajo::idSegunNumeroComprobante( NumeroComprobante num )
{
    return num.aNumero();
}

/*!
 * \brief MOrdenTrabajo::obtenerIdEquipamientoSegunId
 * Se obtiene el identificador de equiapamiento asociado con la orde pasada como parametro
 * \param id_orden Identificador de la orden
 * \return Identificador del equipamiento o -1 si hubo error
 */
int MOrdenTrabajo::obtenerIdEquipamientoSegunId( const int id_orden )
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT id_equipamiento FROM orden_trabajo WHERE id_orden = %1" ).arg( id_orden ) ) ) {
        if( cola.next() ) {
            if( cola.record().value(0).toInt() > 0 ) {
                return cola.record().value(0).toInt();
            }
        } else {
            qDebug() << "Error al intentar cargar los datos de una orden de trabajo";
            qDebug() << cola.lastQuery();
        }
    } else {
        qDebug() << "Error al intentar ejecutar la cola de averiguación de datos de una orden de trabajo";
        qDebug() << cola.lastError().text();
        qDebug() << cola.lastQuery();
    }
    return -1;
}

/*!
 * \brief MOrdenTrabajo::cargarDatos
 * Carga los datos de una orden de trabajo pasada como parametro.
 * \param id_orden IDentificador de la orden de trabajo a cargar.
 */
void MOrdenTrabajo::cargarDatos( const int id_orden )
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT * FROM orden_trabajo WHERE id_orden = %1" ).arg( id_orden ) ) ) {
        if( cola.next() ) {
            this->_data = cola.record();
            _id_orden_trabajo = id_orden;
        } else {
            qDebug() << "Error al intentar cargar los datos de una orden de trabajo";
            qDebug() << cola.lastQuery();
        }
    } else {
        qDebug() << "Error al intentar ejecutar la cola de averiguación de datos de una orden de trabajo";
        qDebug() << cola.lastError().text();
        qDebug() << cola.lastQuery();
    }
}


