#include "mgarantias.h"

#include <QDate>

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
    /// @TODO: Agregar definicion de metodo
}
