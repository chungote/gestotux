#include "mgarantias.h"

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

