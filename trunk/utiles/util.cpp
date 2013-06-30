#include "util.h"

#include <QString>
#include <QSqlDatabase>
#include <QDate>
#include <QDateTime>

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

/*!
 * \brief Util::formateoFechas
 *  Devuelve el formato correcto para fechas sql en comparaciones sql según la base de datos
 * \param fecha Fecha a convertir
 * \return String con el formateo correcto
 * \return
 */
QString Util::formateoFechas( QDate fecha ) {
    if( QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).driverName() == "QSQLITE" ) {

        return fecha.toString( Qt::ISODate );

    } else if( QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).driverName() == "QMYSQL" ) {
        ///@TODO Verificar si esto se cumple o hay que agregar un DATE()
        return fecha.toString( Qt::ISODate );

    } else {
        qDebug( "Driver desconocido" );
        return fecha.toString( Qt::ISODate );
    }
}

/*!
 * \brief Util::formateoFechas
 *  Devuelve el formato correcto para fechas sql en comparaciones sql según la base de datos
 * \param fecha Fecha a convertir
 * \return String con el formateo correcto
 */
QString Util::formateoFechas( QDateTime fecha )
{
    if( QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).driverName() == "QSQLITE" ) {

        return fecha.toString( Qt::ISODate );

    } else if( QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).driverName() == "QMYSQL" ) {
        ///@TODO Verificar si esto se cumple o hay que agregar un DATE()
        return fecha.toString( Qt::ISODate );

    } else {
        qDebug( "Driver desconocido" );
        return fecha.toString( Qt::ISODate );
    }
}
