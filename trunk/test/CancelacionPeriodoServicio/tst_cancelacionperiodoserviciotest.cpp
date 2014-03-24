#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include "edatabasetest.h"

class CancelacionPeriodoServicioTest : public QObject, public EDatabaseTest
{
    Q_OBJECT

public:
    CancelacionPeriodoServicioTest();
    
private Q_SLOTS:
    void initTestCase(); //  will be called before the first testfunction is executed
    void cleanupTestCase(); // will be called after the last testfunction was executed
    void init(); // will be called before each testfunction is executed
    void cleanup(); // will be called after every testfunction
    void testCancelarPeriodoServicio();
    void testCancelarPeriodoServicio_data();
};

CancelacionPeriodoServicioTest::CancelacionPeriodoServicioTest()
{
    // Pongo la lista de tablas necesarias
    this->tablas << "servicios" << "periodo_servicio" << "cobro_servicio_cliente_periodo" << "recibos" << "factura";
}

void CancelacionPeriodoServicioTest::initTestCase()
{
    EDatabaseTest::generarTablas();
}

void CancelacionPeriodoServicioTest::cleanupTestCase()
{
    EDatabaseTest::borrarTablas();
}

void CancelacionPeriodoServicioTest::init()
{
    EDatabaseTest::iniciarTablas();
}

void CancelacionPeriodoServicioTest::cleanup()
{
    EDatabaseTest::vaciarTablas();
}

void CancelacionPeriodoServicioTest::testCancelarPeriodoServicio()
{
    QFETCH( int, id_servicio);
    QFETCH( int, id_periodo_servicio );
    QFETCH( bool, resultado );
    QVERIFY( resultado );
}

void CancelacionPeriodoServicioTest::testCancelarPeriodoServicio_data()
{
    QTest::addColumn<int>("id_servicio");
    QTest::addColumn<int>("id_periodo");
    QTest::addColumn<bool>("resultado");
    QTest::newRow("Correcto") << 1 << 1 << true;
}

QTEST_MAIN(CancelacionPeriodoServicioTest)

#include "tst_cancelacionperiodoserviciotest.moc"
