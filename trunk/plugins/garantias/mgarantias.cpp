#include "mgarantias.h"

#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

MGarantias::MGarantias(QObject *parent) :
QSqlRelationalTableModel(parent)
{
    setTable("garantias");
    setHeaderData( 0, Qt::Horizontal, "#Garantia" );
    setHeaderData( 1, Qt::Horizontal, "Fecha de Inicio" );
    setHeaderData( 2, Qt::Horizontal, "Fecha de Fin" );
    setHeaderData( 3, Qt::Horizontal, "#Cliente" );
    setHeaderData( 4, Qt::Horizontal, "#Equipamiento" );
    setHeaderData( 5, Qt::Horizontal, "#Factura" );
    setHeaderData( 6, Qt::Horizontal, "#Codigo" );
}

void MGarantias::relacionar()
{
    setRelation( 3, QSqlRelation( "cliente", "id", "razon_social" ) );
    setRelation( 4, QSqlRelation( "equipamiento", "id_equipamiento", "Descripcion" ) );
}

QVariant MGarantias::data( const QModelIndex &item, int role ) const
{
    switch( item.column() ) {
        case 1:
        case 2:
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
