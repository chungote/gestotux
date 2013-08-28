#include "madelantosimularcuotas.h"

MAdelantoSimularCuotas::MAdelantoSimularCuotas( QObject *parent ) :
MSimularCuotas( parent )
{
    adelantos = new QHash<int,double>();
}

MAdelantoSimularCuotas::~MAdelantoSimularCuotas()
{
    delete adelantos;
    adelantos=0;
}

void MAdelantoSimularCuotas::regenerar()
{
    adelantos->clear();
    MSimularCuotas::regenerar();
    double temp = _adelanto;
    double cuota = data( index( cantidad-1, 2 ), Qt::EditRole ).toDouble();
    for( int i=cantidad-1; i>=0; i-- ) {
        if( temp > 0.0 ) {
            temp-=cuota;
        }
        adelantos->insert( i, temp );
    }
    emit dataChanged( index( 0, 5 ), index( rowCount(), 5 ) );
}

int MAdelantoSimularCuotas::columnCount( const QModelIndex & ) const
{
    return MSimularCuotas::columnCount()+1;
}

QVariant MAdelantoSimularCuotas::data(const QModelIndex &index, int role) const
{
    if( index.column() == 5 ) {
        switch( role ) {
            case Qt::DisplayRole: {
                return QString( "$ %L1" ).arg( adelantos->value( index.row() ), 10, 'f', 2 );
                break;
            }
            case Qt::EditRole:
            {
                return adelantos->value( index.row() );
                break;
            }
            case Qt::TextAlignmentRole: {
                return int( Qt::AlignRight | Qt::AlignVCenter );
                break;
            }
        }
    }
    return MSimularCuotas::data( index, role );
}

QVariant MAdelantoSimularCuotas::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( section == 5 && orientation == Qt::Horizontal && role == Qt::DisplayRole ) {
        return "Con adelanto";
    }
    return MSimularCuotas::headerData( section, orientation, role );
}
