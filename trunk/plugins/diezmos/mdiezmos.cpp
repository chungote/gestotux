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
    saldos = new QVector<double>();
}

MDiezmos::~MDiezmos()
{
    delete saldos;
    saldos = 0;
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
                    double nuevo_saldo = 0.0;
                    if( idx.row() > 1 ) {
                     nuevo_saldo = saldos->at( idx.row() -1 );
                    }
                    nuevo_saldo -= data( index( idx.row(), fieldIndex( "haber" ) ), Qt::EditRole ).toDouble();
                    nuevo_saldo += data( index( idx.row(), fieldIndex( "debe" ) ), Qt::EditRole ).toDouble();
                    int pos = idx.row();
                    this->saldos->insert( pos, nuevo_saldo );
                    return QString( "$ %L1" ).arg( saldos->at( pos ), 10, 'f', 2 );
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
