#include "mdescuentos.h"

#include <QSqlRecord>

MDescuentos::MDescuentos(QObject *parent) :
QSqlTableModel(parent)
{
    setTable( "descuentos" );
    setHeaderData( 0, Qt::Horizontal, "#ID" );
    setHeaderData( 1, Qt::Horizontal, "Texto" );
    setHeaderData( 2, Qt::Horizontal, "Porcentaje" );
}

bool MDescuentos::agregarDescuento( Tipo t, int id_comprobante, QString texto, double porcentaje ) {
    if( t == Invalido )
        return false;
    if( id_comprobante == 0 || texto.isEmpty() || porcentaje <= 0.0 )
        return false;

    QSqlRecord r = this->record();
    r.setValue( "texto", texto );
    r.setValue( "cantidad", porcentaje );
    if( this->insertRecord( -1, r ) ) {
        // Busco el ID
        int id_descuento = r.value( "id_descuento" ).toInt();
        if( id_descuento <= 0 ) {
            qWarning( "Error al obtener el id del descuento agregado" );
            return false;
        }
        this->setTable( "descuentos_comprobante" );
        QSqlRecord dc = this->record();
        dc.setValue( "id_descuento", id_descuento );
        dc.setValue( "id_comprobante", id_comprobante );
        dc.setValue( "tipo", t );
        if( !this->insertRecord( -1, dc ) ) {
            qWarning( "Error al insertar el registro de asociacion con el comprobante de un descuento" );
            return false;
        } else {
            this->setTable( "descuentos" );
        }
    } else {
        qWarning( "Error al insertar el registro de edscuento" );
        return false;
    }
    return true;
}
