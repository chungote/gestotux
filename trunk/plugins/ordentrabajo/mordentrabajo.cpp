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
 * \brief MOrdenTrabajo::cambiarTecnico
 * Cambia el tecnico de una orden de trabajo.
 * \param id_orden_trabajo Identificador de orden de trabajo
 * \param id_tecnico identificador del técnico.
 * \return Verdadero si el cambio fue correcto.
 */
bool MOrdenTrabajo::cambiarTecnico(const int id_orden_trabajo, const int id_tecnico)
{
    QSqlQuery cola;
    if( cola.exec( QString( "UPDATE orden_trabajo SET id_tecnico = %1 WHERE id_orden = %2" ).arg( id_tecnico ).arg( id_orden_trabajo ) ) ) {
        return true;
    } else {
        qDebug() << "Error al intentar ejecutar la cola de averiguación de datos de una orden de trabajo";
        qDebug() << cola.lastError().text();
        qDebug() << cola.lastQuery();
    }
    return false;
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

/*!
 * \brief MOrdenTrabajo::agregarOrdenTrabajo
 * Agrega una nueva orden de trabajo con los parametros indicados
 * \param id_cliente Identificador del cliente
 * \param id_equipamiento Identificador del equipamiento
 * \param id_tecnico Identificador del técnico
 * \param requerente Nombre del requerente
 * \param ingresante Nombre del ingresante
 * \param fecha_ingreso Fecha de ingreso de la orden
 * \param fecha_devolucion Fecha de posible devolucion
 * \param causa_ingreso Causa del ingreso
 * \return ID de al nueva orden de trabajo o -1 si hubo algún error
 */
int MOrdenTrabajo::agregarOrdenTrabajo(const int id_cliente, const int id_equipamiento, const int id_tecnico, QString requerente, QString ingresante, QDateTime fecha_ingreso, QDateTime fecha_devolucion, QString causa_ingreso)
{
}


