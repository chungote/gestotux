#include "util.h"

#include <QString>
#include <QSqlDatabase>

QString Util::comparacionSQL( const QString texto )
{
    QString ret( texto );
    ret = ret.toUpper();
    ret = ret.trimmed();
    ret.replace( " ", "" );
    return ret;
}

QString Util::funcionComparacionSQL( const QString nombre_campo )
{

    if( QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).driverName() == "QSQLITE" ) {
        // Devuelvo el grupo de funciones anidadas que cumplan con la función idem a la anterior

        return QString( "upper( trim( replace( %1, ' ', '' ) ) )" ).arg( nombre_campo );

    } else if( QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).driverName() == "QMYSQL" ) {

        return QString( "UPPER( TRIM( REPLACE( %1, ' ', '' ) ) )" ).arg( nombre_campo );

    } else {
        qDebug( "Driver desconocido" );
        return nombre_campo;
    }
}
