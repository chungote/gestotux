#include "MVFacturas.h"
#include "MFactura.h"

MVFacturas::MVFacturas(QObject *parent) :
    QSqlTableModel(parent)
{
    this->setTable( "v_facturas" );
    this->setHeaderData( 0, Qt::Horizontal, "id_factura" );
    this->setHeaderData( 1, Qt::Horizontal, "Numero de Comprobante" );
    this->setHeaderData( 2, Qt::Horizontal, "Cliente" );
    this->setHeaderData( 3, Qt::Horizontal, QString::fromUtf8("Fecha de Emisión" ) );
    this->setHeaderData( 4, Qt::Horizontal, "Forma de pago" );
    this->setHeaderData( 5, Qt::Horizontal, "Total" );
    this->setHeaderData( 6, Qt::Horizontal, "Anulada" );
}

/*!
 * \fn MVFacturas::data( const QModelIndex& item, int role ) const
 * Implementacion del metodo de datos para que las enumeraciones se vean como texto
 */
QVariant MVFacturas::data( const QModelIndex& item, int role ) const {
    if( !item.isValid() ) { return QVariant(); }
    switch( role ) {
        case Qt::DisplayRole:
        {
            switch( item.column() ) {
                case 4: // Periodo
                {
                        switch( QSqlTableModel::data( item, role ).toInt() ) {
                            case MFactura::Contado:
                            { return "Contado"; }
                            case MFactura::CuentaCorriente:
                            { return "Cuenta Corriente"; }
                            case MFactura::Cuotas:
                            { return "Cuotas"; }
                            default:
                            { return "Desconocido"; }
                        }
                }
                case 5:
                { return QString( "$ %L1" ).arg( QSqlTableModel::data( item, role ).toDouble() ); }
                default:
                { return QSqlTableModel::data( item, role ); }
            }
        }
        case Qt::TextAlignmentRole:
        {
            switch( item.column() ) {
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                {
                    return int( Qt::AlignCenter | Qt::AlignHCenter );
                }
                default:
                {
                    return QSqlTableModel::data( item, role );
                }
            }
        }
        case Qt::BackgroundColorRole:
        {
            if( this->data( this->index( item.row(), 6 ), Qt::EditRole ).toBool() ) {
                return Qt::gray;
            } else {
                return QSqlTableModel::data( item, role );
            }
            break;
        }
        default:
        { return QSqlTableModel::data( item, role ); }
    }
}

void MVFacturas::verAnuladas( bool sino )
{
    if( sino ) {
        this->setFilter( "anulada != 1" );
        this->select();
    } else {
        this->setFilter( "" );
        this->select();
    }
}
