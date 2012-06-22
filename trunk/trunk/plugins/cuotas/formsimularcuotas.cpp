#include "formsimularcuotas.h"

#include "msimularcuotas.h"
#include "eactcerrar.h"
#include "preferencias.h"

FormSimularCuotas::FormSimularCuotas(QWidget *parent) :
EVentana(parent), Ui::FormSimularCuotasBase()
{
    setupUi(this);
    setWindowTitle( "Simulador de cuotas" );

    ActSimular = new QAction( this );
    ActSimular->setText( "Simular" );
    ActSimular->setStatusTip( "Simula los pagos según los datos ingresados" );
    //ActSimular->setIcon( QIcon( ":/imagenes/" ) );
    connect( ActSimular, SIGNAL( triggered() ), this, SLOT( simular() ) );

    ActImprimir = new QAction( this );
    ActImprimir->setText( "Imprimir" );
    ActImprimir->setText( QString::fromUtf8( "Imprime la simulación actual" ) );
    ActImprimir->setIcon( QIcon( ":/imagenes/impresora.png" ) );
    connect( ActImprimir, SIGNAL( triggered() ), this, SLOT( imprimir() ) );

    ActPdf = new QAction( this );
    ActPdf->setText( "PDF" );
    ActPdf->setStatusTip( "Convierte a PDF la simulacion actual" );
    ActPdf->setIcon( QIcon( ":/imagenes/acroread.png" ) );
    connect( ActPdf, SIGNAL( triggered() ), this, SLOT( pdf() ) );

    modelo = new MSimularCuotas( this );

    connect( DSBEntrega, SIGNAL( valueChanged( double ) ), this, SLOT( cambioEntrega( double ) ) );
    connect( DSBImporte, SIGNAL( valueChanged( double ) ), this, SLOT( cambioImporte( double ) ) );
    connect( DSBInteres, SIGNAL( valueChanged( double ) ), this, SLOT( cambioInteres( double ) ) );

    connect( SBCantidad, SIGNAL( valueChanged( int ) ), this, SLOT( cambioCantidad( int ) ) );

    connect( CBPeriodo , SIGNAL( currentIndexChanged( int ) ), this, SLOT( cambioPeriodo( int ) ) );

    connect( DEInicio, SIGNAL( dateChanged( QDate ) ), this, SLOT( cambioFechaInicio( QDate ) ) );

    CBPeriodo->insertItem( MSimularCuotas::Semanal      , "Semanal"       );
    CBPeriodo->insertItem( MSimularCuotas::Quincenal    , "Quincenal"     );
    CBPeriodo->insertItem( MSimularCuotas::Mensual      , "Mensual"       );
    CBPeriodo->insertItem( MSimularCuotas::Bimensual    , "Bimensual"     );
    CBPeriodo->insertItem( MSimularCuotas::Trimestral   , "Trimestral"    );
    CBPeriodo->insertItem( MSimularCuotas::Cuatrimestral, "Cuatrimestral" );
    CBPeriodo->insertItem( MSimularCuotas::Semestral    , "Semestral"     );
    CBPeriodo->insertItem( MSimularCuotas::Anual        , "Anual"         );

    DEInicio->setDate( QDate::currentDate() );

    preferencias *p = preferencias::getInstancia();
    p->inicio();
    p->beginGroup( "Preferencias" );
    p->beginGroup( "Cuotas" );
    CBPeriodo->setCurrentIndex( p->value( "id-periodo", 2 ).toInt() );
    DSBInteres->setValue( p->value( "interes", 10.00 ).toDouble() );
    //CkBInicioPeriodo->setChecked( p->value( "inicio-periodo", false ).toBool() );
    p->endGroup();
    p->endGroup();
    p = 0;

    addAction( ActSimular );
    addAction( new EActCerrar( this ) );
}

void FormSimularCuotas::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
        case QEvent::LanguageChange:
            retranslateUi(this);
            break;
        default:
            break;
    }
}

/*!
 * \fn FormSimularCuotas::simular()
 * Genera todos los datos para la simulación
 */
void FormSimularCuotas::simular()
{
    DSBTotal->setValue( DSBImporte->value() - DSBEntrega->value() );
    modelo->setImporte    ( DSBTotal->value()   );
    modelo->setCuotas     ( SBCantidad->value() );
    modelo->setPeriodo    ( (MSimularCuotas::Periodo) CBPeriodo->currentIndex() );
    modelo->setInteres    ( DSBInteres->value() );
    modelo->setFechaInicio( DEInicio->date()    );
    TVSimulacion->setModel( modelo );
}

/*!
 * \fn FormSimularCuotas::imprimir()
 *
 */
void FormSimularCuotas::imprimir()
{}

/*!
 * \fn FormSimularCuotas::pdf()
 *
 */
void FormSimularCuotas::pdf()
{}

/*!
 * \fn FormSimularCuotas::confirmar()
 *
 */
void FormSimularCuotas::confirmar()
{}

/*!
 * \fn FormSimularCuotas::cambioEntrega( double cant )
 *
 */
void FormSimularCuotas::cambioEntrega( double )
{
    DSBTotal->setValue( DSBImporte->value() - DSBEntrega->value() );
    modelo->setImporte( DSBTotal->value() );
    modelo->regenerar();
}

/*!
 * \fn FormSimularCuotas::cambioImporte( double cantidad )
 */
void FormSimularCuotas::cambioImporte( double )
{
    DSBTotal->setValue( DSBImporte->value() - DSBEntrega->value() );
    modelo->setImporte( DSBTotal->value() );
    modelo->regenerar();
    TVSimulacion->update();
}

/*!
 * \fn FormSimularCuotas::cambioInteres( double cantidad )
 */
void FormSimularCuotas::cambioInteres( double cantidad )
{
    modelo->setInteres( cantidad );
    modelo->regenerar();
    TVSimulacion->update();
}

/*!
 * \fn FormSimularCuotas::cambioCantidad( int cantidad )
 */
void FormSimularCuotas::cambioCantidad( int cantidad )
{
    modelo->setCuotas( cantidad );
    modelo->regenerar();
    TVSimulacion->update();
}

void FormSimularCuotas::cambioPeriodo( MSimularCuotas::Periodo idx )
{
    modelo->setPeriodo( idx );
    modelo->regenerar();
    TVSimulacion->update();
}

void FormSimularCuotas::cambioFechaInicio( QDate fecha )
{
    modelo->setFechaInicio( fecha );
    modelo->regenerar();
}
