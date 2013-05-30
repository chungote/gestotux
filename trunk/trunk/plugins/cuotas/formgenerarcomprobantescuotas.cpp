#include "formgenerarcomprobantescuotas.h"

#include "eactcerrar.h"

FormGenerarComprobantesCuotas::FormGenerarComprobantesCuotas( QWidget *parent ) :
    EVentana( parent )
{
    setupUi(this);
    this->setWindowTitle( "Generar comprobantes de cuotas" );
    //this->setWindowIcon( QIcon( ":/imagenes/nada.png" ) );

    this->GBProgreso->setVisible( false );

    // Inicializo el modelo de las cuotas
    modelo = new MGenerarCuotas( this );

    // Conecto los totales y demás
    connect( modelo, SIGNAL( cambioTotal( double ) ), DSBTotal, SLOT( setValue( double ) ) );
    connect( modelo, SIGNAL( cambioCantidad( int ) ), LCDNCantidad, SLOT( display( int ) ) );
    connect( modelo, SIGNAL( comprobantes( QPair<NumeroComprobante *, NumeroComprobante *> ) ), this, SLOT( cambioComprobantes( QPair<NumeroComprobante *, NumeroComprobante *> ) ) );

    TVVista->setModel( modelo );

    addAction( new EActCerrar( this ) );
}

void FormGenerarComprobantesCuotas::changeEvent(QEvent *e)
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

/**
 * @brief FormGenerarComprobantesCuotas::cambioComprobantes
 * Coloca el numero de comprobantes en la etiqueta informativa correspondiente
 * @param nums Par de Numeros de Comprobante a generar
 */
void FormGenerarComprobantesCuotas::cambioComprobantes( QPair<NumeroComprobante *,NumeroComprobante *> nums)
{
    LComprobantes->setText( QString( "Emitiendo comprobantes número: %1 al %2" ).arg( nums.first->aCadena() ).arg( nums.second->aCadena() ) );
}
