#include "mgarantias.h"

#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlDriver>

MGarantias::MGarantias(QObject *parent) :
QSqlRelationalTableModel(parent)
{
    setTable("garantias");
    setHeaderData( 0, Qt::Horizontal, "#ID" );
    setHeaderData( 1, Qt::Horizontal, "#Garantia" );
    setHeaderData( 2, Qt::Horizontal, "Texto" );
    setHeaderData( 3, Qt::Horizontal, "Fecha de Inicio" );
    setHeaderData( 4, Qt::Horizontal, "Fecha de Fin" );
    setHeaderData( 5, Qt::Horizontal, "#Cliente" );
    setHeaderData( 6, Qt::Horizontal, "#Equipamiento" );
    setHeaderData( 7, Qt::Horizontal, "#Factura" );
    setHeaderData( 8, Qt::Horizontal, "#Codigo" );
    setHeaderData( 9, Qt::Horizontal, "Fecha de Baja" );
    setHeaderData( 10, Qt::Horizontal, "Razón de Baja" );
    setHeaderData( 11, Qt::Horizontal, "#Producto" );

}

void MGarantias::relacionar()
{
    setRelation( 4, QSqlRelation( "cliente", "id", "razon_social" ) );
    setRelation( 5, QSqlRelation( "equipamiento", "id_equipamiento", "Descripcion" ) );
}

QVariant MGarantias::data( const QModelIndex &item, int role ) const
{
    switch( item.column() ) {
        case 3:
        case 4:
        case 9:
        {
            switch( role )
            {
                case Qt::DisplayRole:
                {
                    return QSqlRelationalTableModel::data( item, role ).toDate().toString( Qt::SystemLocaleShortDate );
                    break;
                }
                default: { break; }
            }
            break;
        }
        default:
        { break; }
    }
    return QSqlRelationalTableModel::data( item, role );
}

/*!
 * \brief MGarantias::darDeBaja
 * \param id_garantia Identificador de la garantía
 * \param razon Razon de la baja
 * \param fecha Fecha de la baja
 * \return verdadero si se pudo dar de baja correctamente
 */
bool MGarantias::darDeBaja( const int id_garantia, const QString razon, const QDate fecha )
{
    QSqlQuery cola;
    if( !cola.prepare( "UPDATE garantias SET razon = :razon, fecha = :fecha WHERE id_garantia = :id_garantia" ) ) {
        qWarning() << "Error al preparar la cola de baja de garantía";
        qDebug() << cola.lastError().text();
        qDebug() << cola.lastQuery();
        return false;
    }
    cola.bindValue( ":id_garantia", id_garantia );
    cola.bindValue( ":razon", razon );
    cola.bindValue( ":fecha", fecha );
    if( cola.exec() ) {
        return true;
    } else {
        qWarning() << "Error al ejecutar la cola de baja de garantia";
        qDebug() << cola.lastError().text();
        qDebug() << cola.lastQuery();
        return false;
    }
    return false;
}

/*!
 * \brief MGarantias::estaActiva
 * \param id_garantia
 * \return
 */
bool MGarantias::estaActiva( const int id_garantia )
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT fecha_inicio, fecha_fin, fecha_baja FROM %1 WHERE id_garantia = %2" ).arg( this->tableName() ).arg( id_garantia ) ) ) {
        if( cola.next() ) {
            QDate inicio, fin, baja;
            inicio = cola.record().value(0).toDate();
            fin    = cola.record().value(1).toDate();
            baja   = cola.record().value(2).toDate();
            if( baja.isValid() ) {
                return false; // La garantía esta dada de baja
            } else if( inicio.isValid() && fin.isValid() ) {
                if( inicio <= QDate::currentDate() &&
                       fin >= QDate::currentDate() ) {
                    return true;
                } else {
                    return false;
                }
            }
        }else {
            qWarning() << "Error al hacer next en la cola de obtencion de datos para averiguacion de garantia activa";
            qDebug() << cola.lastQuery();
        }
    } else {
        qWarning() << "Error al ejecutar la cola de obtencion de datos para averiguación de garantias activa";
        qDebug() << cola.lastError().text();
        qDebug() << cola.lastQuery();
    }
    return false;
}

/*!
 * \brief MGarantias::eliminar
 * \param id_garantia
 * \return
 */
bool MGarantias::eliminar( const int id_garantia )
{   QSqlQuery cola;
    if( cola.exec( QString( "DELETE FROM garantias WHERE id_garantia = %1" ).arg( id_garantia ) ) ) {
        return true;
    } else {
        qWarning() << "Error al ejecutar la cola de baja de garantia";
        qDebug() << cola.lastError().text();
        qDebug() << cola.lastQuery();
        return false;
    }
    return false;
}

/*!
 * \brief MGarantias::agregarGarantia
 * Agrega una nueva garantía al sistema
 * \param id_cliente Identificación del cliente
 * \param texto_producto Texto del producto o elemento de la garantía
 * \param fecha_inicio Fecha de inicio de la garantia
 * \param fecha_fin Fecha de fin de la garantia
 * \param id_equipamiento Identificador del equipamiento al que pertenece
 * \param id_producto Identificador del producto elegido
 * \param id_factura Identificador de la factura/recibo de emision
 * \return
 */
int MGarantias::agregarGarantia( const int id_cliente, const QString texto_producto, const QDate fecha_inicio, const QDate fecha_fin, const int id_equipamiento, const int id_producto, const int id_factura)
{
    QSqlQuery cola;
    if( !cola.prepare( "INSERT INTO garantias( id_cliente, texto_producto, fecha_inicio, fecha_fin, id_equipamiento, id_factura, id_producto ) "
                       " VALUES ( :id_cliente, :texto_producto, :fecha_inicio, :fecha_fin, :id_equipamiento, :id_factura, :id_producto ) " ) ) {
        qWarning() << "Error al preparar la cola de alta de garantía";
        qDebug() << cola.lastError().text();
        qDebug() << cola.lastQuery();
        return -1;
    }
    cola.bindValue( ":id_cliente"     , id_cliente      );
    cola.bindValue( ":texto_producto" , texto_producto  );
    cola.bindValue( ":fecha_inicio"   , fecha_inicio    );
    cola.bindValue( ":fecha_fin"      , fecha_fin       );
    cola.bindValue( ":id_equipamiento", id_equipamiento );
    cola.bindValue( ":id_factura"     , id_factura      );
    cola.bindValue( ":id_producto"    , id_producto     );
    if( cola.exec() ) {
        if( QSqlDatabase::database().driver()->hasFeature( QSqlDriver::LastInsertId ) ) {
            return cola.lastInsertId().toInt();
        } else {
            qDebug() << "No agregado elemento para cuando el driver no tiene LastInsertedId";
            /// @TODO: Falta agregar esto!
            return -1;
        }
    } else {
        qWarning() << "Error al ejecutar la cola de baja de garantia";
        qDebug() << cola.lastError().text();
        qDebug() << cola.lastQuery();
    }
    return -1;
}
