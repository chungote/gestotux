#include "mequipamiento.h"

#include <QDate>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>

MEquipamiento::MEquipamiento(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
    setTable( "equipamiento" );
    setHeaderData(  0, Qt::Horizontal, "#ID"               );
    setHeaderData(  1, Qt::Horizontal, "Descripcion"       );
    setHeaderData(  2, Qt::Horizontal, "Marca"             );
    setHeaderData(  3, Qt::Horizontal, "Modelo"            );
    setHeaderData(  4, Qt::Horizontal, "#Serie"            );
    setHeaderData(  5, Qt::Horizontal, "Fecha de Compra"   );
    setHeaderData(  6, Qt::Horizontal, "Fecha Vencimiento" );
    setHeaderData(  7, Qt::Horizontal, "#Factura"          );
    setHeaderData(  8, Qt::Horizontal, "#Cliente"          );
    setHeaderData(  9, Qt::Horizontal, "Bultos"            );
    setHeaderData( 10, Qt::Horizontal, "Fecha de baja"     );
    setHeaderData( 11, Qt::Horizontal, "Razon de baja"     );
}

/*!
 * \brief MEquipamiento::data
 * \param item
 * \param role
 * \return
 */
QVariant MEquipamiento::data(const QModelIndex &item, int role) const
{
    switch( item.column() ) {
        case 5:
        case 6:
        case 10:
        {
            if( role == Qt::DisplayRole ) {
                return QSqlRelationalTableModel::data( item, role ).toDate().toString( Qt::LocaleDate );
                break;
            } else if ( role == Qt::UserRole && item.column() == 10 ) {
                QDate temp = QSqlRelationalTableModel::data( item, role ).toDate();
                if( temp.isValid() ) { return true;  } else { return false;  }
            }
        }
    }
    return QSqlRelationalTableModel::data( item, role );
}

/*!
 * \brief MEquipamiento::tieneDatosRelacionados
 * Busca si el elemento posee alguna relación con los otros datos de las tablas.
 * \param id_equipamiento Identificador del equipamiento
 * \return Verdadero si hay alguna relacion
 */
bool MEquipamiento::tieneDatosRelacionados( const int /* id_equipamiento */ )
{ return false; } // Los datos relacionados deberán ser eliminados si se elimina un equipamiento

/*!
 * \brief MEquipamiento::eliminarConRelacionados
 * \param id_equipamiento
 * \return
 */
bool MEquipamiento::eliminarConRelacionados( const int id_equipamiento )
{ return false; }

/*!
 * \brief MEquipamiento::darBaja
 * \param id_equipamiento
 * \param razon
 * \param fecha
 * \return
 */
bool MEquipamiento::darDeBaja( const int id_equipamiento, const QString razon, QDateTime fechahora )
{ return false;
}

/*!
 * \brief MEquipamiento::darReAlta
 * \param id_equipamiento
 * \param razon
 * \param fechahora
 * \return
 */
bool MEquipamiento::darReAlta( const int id_equipamiento, const QString razon, QDateTime fechahora )
{ return false;
}



/*!
 * \brief MEquipamiento::flags
 * \return
 */
Qt::ItemFlags MEquipamiento::flags( const QModelIndex & ) const
{
    return Qt::ItemFlags( !Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
}

/*!
 * \brief MEquipamiento::existe
 * \param id_equipamiento
 * \return
 */
bool MEquipamiento::existe( const int id_equipamiento )
{
    QSqlQuery cola;
    if( cola.exec( QString() ) ) {
        if( cola.next() ) {
            if( cola.record().value(0).toInt() > 0 ) {
                return true;
            } else {
                return false;
            }
        } else {
            qDebug() << "Error al hacer next en la cola de averiguación de existencia de equipamiento";
        }
    } else {
        qDebug() << "Error al ejecutar la cola de averiguación de existencia de equipamiento";
    }
    qDebug() << cola.lastError().text();
    qDebug() << cola.lastQuery();
    return false;
}

/*!
 * \brief MEquipamiento::cargarDatos
 * \param id_equipamiento
 */
void MEquipamiento::cargarDatos( const int id_equipamiento )
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT * FROM equipamiento WHERE id_equipamiento = %1" ).arg( id_equipamiento ) ) ) {
        if( cola.next() ) {
            this->_datos = cola.record();
        } else {
            qDebug() << "Error al obtener los datos del ID de equipamiento indicado";
        }
    } else {
        qDebug() << "Error al ejecutar la cola de averiguación de datos de equipamiento";
        qDebug() << cola.lastError().text();
        qDebug() << cola.lastQuery();
    }
    return;
}

/*!
 * \brief MEquipamiento::enGarantia
 * \return
 */
bool MEquipamiento::enGarantia()
{
    /// @TODO ver esto!
}
