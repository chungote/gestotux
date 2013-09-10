#include "mgarantias.h"

MGarantias::MGarantias(QObject *parent) :
    QSqlRelationalTableModel(parent)
{
    setTable("garantias");
    setHeaderData( 0, Qt::Horizontal, "#Garantia" );

}
