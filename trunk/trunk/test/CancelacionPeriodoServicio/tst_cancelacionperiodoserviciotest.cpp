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
    void initTestCase(); // will be called before the first testfunction is executed
    void cleanupTestCase(); // will be called after the last testfunction was executed
    void init(); // will be called before each testfunction is executed
    void cleanup(); // will be called after every testfunction
    void testCancelarPeriodoServicio();
    void testCancelarPeriodoServicio_data();
};

CancelacionPeriodoServicioTest::CancelacionPeriodoServicioTest()
{
}

void CancelacionPeriodoServicioTest::initTestCase()
{
    // Tablas vacias que voy a necesitar en cada test
    this->generarTabla( "servicios" );
    this->generarTabla( "periodo_servicio" );
    this->generarTabla( "cobro_periodo_servicio" );
    this->generarTabla( "recibos" );
    this->generarTabla( "factura" );
}

void CancelacionPeriodoServicioTest::cleanupTestCase()
{
    this->borrarTabla( "servicios" );
    this->borrarTabla( "periodo_servicio" );
    this->borrarTabla( "cobro_periodo_servicio" );
    this->borrarTabla( "recibos" );
    this->borrarTabla( "factura" );
}

void CancelacionPeriodoServicioTest::init()
{
    this->iniciarTabla( "servicios" );
    this->iniciarTabla( "periodo_servicio" );
    this->iniciarTabla( "cobro_periodo_servicio" );
    this->iniciarTabla( "recibos" );
    this->iniciarTabla( "factura" );
}

void CancelacionPeriodoServicioTest::cleanup()
{
    this->borrarTabla( "servicios" );
    this->borrarTabla( "periodo_servicio" );
    this->borrarTabla( "cobro_periodo_servicio" );
    this->borrarTabla( "recibos" );
    this->borrarTabla( "factura" );
}

void CancelacionPeriodoServicioTest::testCancelarPeriodoServicio()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

void CancelacionPeriodoServicioTest::testCancelarPeriodoServicio_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

QTEST_MAIN(CancelacionPeriodoServicioTest)

#include "tst_cancelacionperiodoserviciotest.moc"
