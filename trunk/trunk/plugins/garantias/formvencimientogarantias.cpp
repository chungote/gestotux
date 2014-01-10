#include "formvencimientogarantias.h"

#include <QDate>

#include "eactcerrar.h"

FormVencimientoGarantias::FormVencimientoGarantias(QWidget *parent) :
QWidget(parent)
{
    setupUi(this);
    this->setWindowTitle( "Vencimientos de Garantias" );
    this->setWindowIcon( QIcon( ":/imagenes/garantia_vencimiento.png" ) );

    mgarantias = new MVGarantias( this );

    TVVencimientos->setModel( mgarantias );

    connect( DEFecha, SIGNAL( dateChanged( QDate ) ), this, SLOT( cambioFecha( QDate ) ) );

    DEFecha->setDate( QDate::currentDate() );

    ActCerrar = new EActCerrar( this );

    addAction( ActCerrar );

}

/*!
 * \brief FormVencimientoGarantias::cambioFecha
 * \param fecha
 */
void FormVencimientoGarantias::cambioFecha( QDate fecha )
{
    mgarantias->setFilter( QString( " fecha_fin <= %1" ).arg( fecha.toString( "Y-m-d" ) ) );
    mgarantias->select();
}

/*!
 * \brief FormVencimientoGarantias::changeEvent
 * \param e
 */
void FormVencimientoGarantias::changeEvent(QEvent *e)
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
