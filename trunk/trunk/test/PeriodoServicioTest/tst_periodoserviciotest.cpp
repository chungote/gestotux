#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include "../../plugins/servicios/mperiodoservicio.h"
#include <QSqlDatabase>
#include <QDir>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>

class PeriodoServicioTest : public QObject
{
    Q_OBJECT
    
public:
    PeriodoServicioTest();
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCalcularPeriodo();
    void testCalcularPeriodo_data();
};

PeriodoServicioTest::PeriodoServicioTest()
{
}

void PeriodoServicioTest::initTestCase()
{
    QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName( "../../bin/gestotux.database" );
    if( !DB.open() )
    {
        qDebug( "Ultimo error: " + DB.lastError().text().toLocal8Bit() );
        abort();
    } else {
        qDebug( "Base de datos SQLite abierta correctamente" );
    }
}

void PeriodoServicioTest::cleanupTestCase()
{
    QSqlDatabase::database().close();
    QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
}

void PeriodoServicioTest::testCalcularPeriodo()
{
    QFETCH( int, mes );
    QFETCH( QDate, fi );
    QFETCH( QDate, ff );
    QDate fecha;
    fecha.setDate( fi.year(), mes, 1 );
    QCOMPARE( fi, fecha );
    fecha.setDate( fecha.year(), fecha.month(), fecha.daysInMonth() );
    QCOMPARE( ff, fecha );
}

void PeriodoServicioTest::testCalcularPeriodo_data()
{
    /// @todo Hacer este test para todos los periodos de servicio
    int ano = QDate::currentDate().year();
    QSqlQuery cola( "SELECT id FROM servicios" );
    MPeriodoServicio *mp = new MPeriodoServicio();
    QTest::addColumn<int>( "id_servicio");
    QTest::addColumn<int>( "mes" );
    QTest::addColumn<QDate>( "fi" );
    QTest::addColumn<QDate>( "ff" );
    while( cola.next() ) {
        int id_servicio = cola.record().value(0).toInt();
        for( int i=1; i<=12; i++ ) {
            QDate fi = mp->generarFechaInicioPeriodo( id_servicio, i, ano+1 );
            QTest::newRow( QString::number( i ).toAscii() )<< id_servicio <<  i << fi << mp->obtenerFechaFinPeriodo( id_servicio, fi );
        }
    }
    delete mp;
}

QTEST_MAIN(PeriodoServicioTest)

#include "tst_periodoserviciotest.moc"
