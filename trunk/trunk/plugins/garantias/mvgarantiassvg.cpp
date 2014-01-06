#include "mvgarantiassvg.h"

#include <QSqlRecord>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

MVGarantiasSvg::MVGarantiasSvg(QObject *parent) :
    QSqlTableModel(parent)
{
    setTable( "v_garantia_svg" );
}

QSqlRecord MVGarantiasSvg::obtenerRegistro(const int id_garantia)
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT * FROM %2 WHERE id_garantia = %1" ).arg( id_garantia ).arg( tableName() ) ) ) {
        return cola.record();
    } else {
        qWarning() << "Error al ejecutar la cola de baja de garantia";
        qDebug() << cola.lastError().text();
        qDebug() << cola.lastQuery();
    }
    return QSqlRecord();
}
