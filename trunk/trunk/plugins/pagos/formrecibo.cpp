#include "formrecibo.h"

#include "mpagos.h"
#include "eactcerrar.h"
#include "eactimprimir.h"
#include "eactpdf.h"
#include "EReporte.h"

FormRecibo::FormRecibo(QWidget *parent) :
EVentana(parent)
{
    setupUi(this);

    EActImprimir *ActImprimir = new EActImprimir( this );
    connect( ActImprimir, SIGNAL( triggered() ), this, SLOT( imprimir() ) );

    EActPdf *ActPdf = new EActPdf( this );
    connect( ActPdf, SIGNAL( triggered() ), this, SLOT( aPdf() ) );

    addAction( ActImprimir );
    addAction( ActPdf );
    addAction( new EActCerrar( this ) );

    CBCliente->setInsertPolicy( QComboBox::NoInsert );
    CBCliente->setEditable( false );
    TETexto->setReadOnly( true );
    DEFecha->setReadOnly( true );
    dSBTotal->setReadOnly( true );
    dSBDeuda->setVisible( false );
    dSBPagado->setVisible( false );

    _id_actual = -1;
}

void FormRecibo::setId(int id)
{
    if( id <= 0 )
        return;

    _id_actual = id;
    cargarDatos();
}

void FormRecibo::changeEvent(QEvent *e)
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

void FormRecibo::cargarDatos()
{
    MPagos *d = new MPagos( this, false );
    d->setearId( _id_actual );
    LNumero->setText( LNumero->text().append( "<b>" ).append( d->buscarNumeroComprobantePorId( _id_actual ).aCadena() ).append( "<b>" ) );
    DEFecha->setDate( d->getFecha() );
    CBCliente->setearId( d->getIdCliente() );
    TETexto->setText( d->getTexto() );
    dSBTotal->setValue( d->getTotal() );
    MPagos::FormaPago fp = d->getFormaPago();
    switch( fp ) {
        case MPagos::Efectivo:
        {
            RBContado->setChecked( true );
            break;
        }
        case MPagos::SinPagar:
        {
            RBLuego->setChecked( true );
            break;
        }
        case MPagos::Otro:
        {
            RBotro->setChecked( true );
            break;
        }
    }
    delete d;
}

void FormRecibo::aPdf() {
    if( _id_actual > 0 ) {
        EReporte *rep = new EReporte( 0 );
        rep->recibo();
        ParameterList lista;
        lista.append( "id_recibo", _id_actual );
        rep->hacer( lista );
        delete rep;
    }
}

void FormRecibo::imprimir() {
    if( _id_actual > 0 ) {
        EReporte *rep = new EReporte( 0 );
        rep->recibo();
        ParameterList lista;
        lista.append( "id_recibo", _id_actual );
        rep->hacerPDF( lista, QString( "Recibo #%1" ).arg( MPagos::buscarNumeroComprobantePorId( _id_actual ).aCadena() ) );
        delete rep;
    }
}
