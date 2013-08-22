#include "mequipamiento.h"

#include <QDate>

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
{ return false; }
// Los datos relacionados deberán ser eliminados si se elimina un equipamiento


/*!
 * \brief MEquipamiento::flags
 * \return
 */
Qt::ItemFlags MEquipamiento::flags( const QModelIndex & ) const
{
    return Qt::ItemFlags( !Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
}
