#include "mdiezmos.h"

#include <QDate>

MDiezmos::MDiezmos(QObject *parent) :
    QSqlTableModel(parent)
{
    setTable( "diezmos" );
    setHeaderData( 0, Qt::Horizontal, "#Id" );
    setHeaderData( 1, Qt::Horizontal, "Fecha" );
    setHeaderData( 2, Qt::Horizontal, "Descripcion" );
    setHeaderData( 3, Qt::Horizontal, "A dar" );
    setHeaderData( 4, Qt::Horizontal, "Diezmado" );
    setHeaderData( 5, Qt::Horizontal, "#Referencia" );
    setHeaderData( 6, Qt::Horizontal, "Saldo" );
}

/*!
 * \brief MDiezmos::columnCount
 * \param parent
 * \return
 */
int MDiezmos::columnCount(const QModelIndex &parent) const
{
    return QSqlTableModel::columnCount( parent ) + 1;
}

/*!
 * \brief MDiezmos::data
 * \param idx
 * \param role
 * \return
 */
QVariant MDiezmos::data(const QModelIndex &idx, int role) const
{
    switch( idx.column() ) {
        case 1:
        {
            switch( role ) {
                case Qt::DisplayRole: {
                    return QSqlTableModel::data( idx, role ).toDate().toString( Qt::SystemLocaleShortDate );
                    break;
                }
                default: {break;}
            }
            break;
        }
        case 3:
        case 4:
        {
            switch( role ) {
                case Qt::DisplayRole:
                {
                    double valor = QSqlTableModel::data( idx, role ).toDouble();
                    recalcularSaldos( valor, idx.row(), idx.column() );
                    return QString( "$ %L1").arg( valor, 10, 'f', 2 );
                    break;
                }
                default: { break; }
            }
            break;
        }
        case 6:
        {
            switch( role ) {
                case Qt::DisplayRole:
                {
                    return QString( "$ %L1" ).arg( saldos.at( idx.row() ), 10, 'f', 2 );
                    break;
                }
                default: { break; }
            }
            break;
        }
        default: { break; }
    }
    return QSqlTableModel::data( idx, role );
}

/*!
 * \brief MDiezmos::recalcularSaldos
 */
void MDiezmos::recalcularSaldos( const double valor, const int fila, const int columna ) const
{

}
