#include "mdescuentostipo.h"

MDescuentosTipo::MDescuentosTipo( QObject *parent )
: QSqlTableModel( parent )

{
    setTable( "tipo_descuento" );
    setHeaderData( 0, Qt::Horizontal, "#ID" );
    setHeaderData( 1, Qt::Horizontal, "Codigo" );
    setHeaderData( 2, Qt::Horizontal, "Nombre" );
    setHeaderData( 3, Qt::Horizontal, "Porcentaje" );
}

QVariant MDescuentosTipo::data( const QModelIndex &idx, int role ) const
{
    if( !idx.isValid() ) {
        return QVariant();
    }

    switch( idx.column() ) {
        case 3:
        {
            return QString( "%L1 %" ).arg( QSqlTableModel::data( idx, role ).toDouble() );
            break;
        }
        default:
        {
            return QSqlTableModel::data( idx, role );
            break;
        }
    }

}

Qt::ItemFlags MDescuentosTipo::flags( const QModelIndex & ) const
{
  return QFlags<Qt::ItemFlag>( Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable );
}
