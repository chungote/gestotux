#include "formprefcuotas.h"

#include "preferencias.h"
#include "msimularcuotas.h"

FormPrefCuotas::FormPrefCuotas( QWidget *parent ) :
    FormPrefCuotasBase(), FormPrefHijo()
{
    this->setParent( parent );
    setupUi(this);
    this->setWindowTitle( "Cuotas" );
    //this->setWindowIcon( QIcon( ":/imagenes/" ) );

    CBPeriodo->insertItem( MSimularCuotas::Semanal      , "Semanal"       );
    CBPeriodo->insertItem( MSimularCuotas::Quincenal    , "Quincenal"     );
    CBPeriodo->insertItem( MSimularCuotas::Mensual      , "Mensual"       );
    CBPeriodo->insertItem( MSimularCuotas::Bimensual    , "Bimensual"     );
    CBPeriodo->insertItem( MSimularCuotas::Trimestral   , "Trimestral"    );
    CBPeriodo->insertItem( MSimularCuotas::Cuatrimestral, "Cuatrimestral" );
    CBPeriodo->insertItem( MSimularCuotas::Semestral    , "Semestral"     );
    CBPeriodo->insertItem( MSimularCuotas::Anual        , "Anual"         );
}

void FormPrefCuotas::changeEvent(QEvent *e)
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

void FormPrefCuotas::cargar()
{
 preferencias *p = preferencias::getInstancia();
 p->inicio();
 p->beginGroup( "Preferencias" );
 p->beginGroup( "Cuotas" );
 CBPeriodo->setCurrentIndex( p->value( "id-periodo", 2 ).toInt() );
 dSBInteres->setValue( p->value( "interes", 10.00 ).toDouble() );
 CkBInicioPeriodo->setChecked( p->value( "inicio-periodo", false ).toBool() );
 p->endGroup();
 p->endGroup();
 p = 0;
}

void FormPrefCuotas::aplicar()
{

}

void FormPrefCuotas::guardar()
{
    preferencias *p = preferencias::getInstancia();
    p->inicio();
    p->beginGroup( "Preferencias" );
    p->beginGroup( "Cuotas" );
    p->setValue( "id-periodo", CBPeriodo->currentIndex() );
    p->setValue( "interes", dSBInteres->value() );
    p->setValue( "inicio-periodo", CkBInicioPeriodo->isChecked() );
    p->endGroup();
    p->endGroup();
    p = 0;
}
