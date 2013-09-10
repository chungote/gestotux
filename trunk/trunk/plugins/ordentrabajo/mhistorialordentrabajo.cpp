#include "mhistorialordentrabajo.h"

MHistorialOrdenTrabajo::MHistorialOrdenTrabajo(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
    setTable( "operacion_orden_trabajo" );
    setHeaderData( 0, Qt::Horizontal, "#ID Operacion" );
    setHeaderData( 1, Qt::Horizontal, "#ID Orden Trabajo" );
    setHeaderData( 2, Qt::Horizontal, "Fecha de operacion" );
    setHeaderData( 3, Qt::Horizontal, "Descripcion" );
    setHeaderData( 4, Qt::Horizontal, "#tipo_operacion" );
    setHeaderData( 5, Qt::Horizontal, "#Tecnico" );
    setHeaderData( 6, Qt::Horizontal, "Costo" );
    setHeaderData( 7, Qt::Horizontal, "Sumatoria" );
    _id_orden_trabajo = 0;
    _mostrar_suma_costos = false;
    _sumas = new QMap<int, double>();
}

MHistorialOrdenTrabajo::~MHistorialOrdenTrabajo()
{
    delete _sumas;
    _sumas=0;
}

/*!
 * \brief MHistorialOrdenTrabajo::data
 * \param item
 * \param role
 * \return
 */
QVariant MHistorialOrdenTrabajo::data(const QModelIndex &item, int role) const
{
    if( _mostrar_suma_costos ) {
        switch( item.column() ) {
            case 7: {
                if( role == Qt::DisplayRole ) {
                    if( item.row() != 0 ) {
                        double nuevo = _sumas->value( item.row() - 1 );
                        nuevo += data( index( item.row(), 6 ), Qt::EditRole ).toDouble();
                        _sumas->insert( item.row(), nuevo );
                    } else {
                        _sumas->insert( item.row(), data( index( item.row(), 6 ), Qt::EditRole ).toDouble() );
                    }
                    return QString( "$ %L1" ).arg( _sumas->value( item.row() ), 10, 'f', 2 );
                } else if( role == Qt::EditRole ) {
                    return _sumas->value( item.row() );
                }
                break;
            }
            default:
            { break; }
        }
    }
    switch( item.column() ) {
        case 2: {
            switch( role ) {
                case Qt::DisplayRole:
                {
                    return QSqlRelationalTableModel::data( item, role ).toDate().toString( Qt::LocaleDate );
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
 * \brief MHistorialOrdenTrabajo::agregarHistorial
 * \param id_orden_trabajo
 * \param fecha_hora
 * \param descripcion
 * \param costo
 * \param tipo_operacion
 * \param id_tecnico
 * \return
 */
bool MHistorialOrdenTrabajo::agregarHistorial(const int id_orden_trabajo, QDateTime fecha_hora, QString descripcion, double costo, const int tipo_operacion, const int id_tecnico)
{
    return false;
    /// @TODO implementar esto!
}

/*!
 * \brief MHistorialOrdenTrabajo::setearOrdenTrabajo
 * \param id_orden_trabajo
 */
void MHistorialOrdenTrabajo::setearOrdenTrabajo(const int id_orden_trabajo)
{
    if( id_orden_trabajo <= 0 ) {
        return;
    }
    _id_orden_trabajo = id_orden_trabajo;
    setFilter( QString( " id_orden_trabajo = %1" ).arg( id_orden_trabajo ) );
    this->select();
}

/*!
 * \brief MHistorialOrdenTrabajo::mostrarCostosSumados
 */
void MHistorialOrdenTrabajo::mostrarCostosSumados()
{
    _mostrar_suma_costos = !_mostrar_suma_costos;
}
