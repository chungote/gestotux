#include "balancegeneral.h"
#include "EReporte.h"

Q_EXPORT_PLUGIN2( balance, BalanceGeneral )

double BalanceGeneral::version() const
{ return 1.0; }

QString BalanceGeneral::nombre() const
{ return "BalanceGeneral"; }

bool BalanceGeneral::inicializar()
{
    ActResumen = new QAction( this );
    ActResumen->setText( "Balance general" );
    ActResumen->setToolTip( "Genera un balance general de todo el sistema" );
    connect( ActResumen, SIGNAL( triggered() ), this, SLOT( hacerResumen() ) );

    return true;
}

void BalanceGeneral::hacerMenu( QMenu *m )
{
    m->addAction( ActResumen );
}

void BalanceGeneral::hacerResumen()
{
    EReporte *rep = new EReporte( this );
    rep->especial( "BalanceGeneral", ParameterList() );
    rep->hacer();
}
