#include "formdetallecuotas.h"

#include "mplancuota.h"
#include "eactcerrar.h"
#include "preferencias.h"
#include "eregistroplugins.h"
#include "einfoprogramainterface.h"

#include <QTextTable>
#include <QTextDocument>
#include <QTextCursor>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrinterInfo>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>

FormDetalleCuotas::FormDetalleCuotas(QWidget *parent) :
EVentana(parent), Ui::FormDetalleCuotasBase()
{
    setupUi(this);
    setWindowTitle( "Simulador de cuotas" );

    ActImprimir = new QAction( this );
    ActImprimir->setText( "Imprimir" );
    ActImprimir->setText( QString::fromUtf8( "Imprimir" ) );
    ActImprimir->setIcon( QIcon( ":/imagenes/impresora.png" ) );
    connect( ActImprimir, SIGNAL( triggered() ), this, SLOT( imprimir() ) );

    ActPdf = new QAction( this );
    ActPdf->setText( "PDF" );
    ActPdf->setStatusTip( "Convierte a PDF la simulacion actual" );
    ActPdf->setIcon( QIcon( ":/imagenes/acroread.png" ) );
    connect( ActPdf, SIGNAL( triggered() ), this, SLOT( pdf() ) );

    ActConfirmar = new QAction( this );
    ActConfirmar->setText( "Confirmar" );
    connect( ActConfirmar, SIGNAL( triggered() ), this, SLOT( confirmar() ) );

    modelo = new MPlanCuota( this );

    CBPeriodo->insertItem( MPlanCuota::Semanal      , "Semanal"       );
    CBPeriodo->insertItem( MPlanCuota::Quincenal    , "Quincenal"     );
    CBPeriodo->insertItem( MPlanCuota::Mensual      , "Mensual"       );
    CBPeriodo->insertItem( MPlanCuota::BiMensual    , "Bimensual"     );
    CBPeriodo->insertItem( MPlanCuota::Trimestral   , "Trimestral"    );
    CBPeriodo->insertItem( MPlanCuota::Cuatrimestral, "Cuatrimestral" );
    CBPeriodo->insertItem( MPlanCuota::Seximestral  , "Semestral"     );
    CBPeriodo->insertItem( MPlanCuota::Anual        , "Anual"         );

    addAction( ActImprimir );
    addAction( ActPdf );
    addAction( new EActCerrar( this ) );
}

FormDetalleCuotas::~FormDetalleCuotas()
{
    if( !documento )
        delete documento;

}

void FormDetalleCuotas::changeEvent(QEvent *e)
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
 * \fn FormDetalleCuotas::imprimir()
 * Imprime el listado de cuotas tal cual se ingresaron en los datos.
 */
void FormDetalleCuotas::imprimir()
{
    this->generaReporte();
    QPrinter *impresora = new QPrinter( QPrinterInfo::defaultPrinter() );
    QPrintDialog *pd = new QPrintDialog( impresora );
    if( pd->exec() == QDialog::Accepted ) {
        documento->print( pd->printer() );
    }
    delete impresora;
    delete pd;
}


void FormDetalleCuotas::generaReporte()
{
    documento = new QTextDocument();
    QTextCursor cursor( documento );
    int cant_filas = 3 + SBCantidad->value();
    QTextTable *tabla = cursor.insertTable( cant_filas, 4 );
    QTextTableFormat formatoTabla = tabla->format();
    formatoTabla.setHeaderRowCount( 1 );
    formatoTabla.setWidth( QTextLength( QTextLength::PercentageLength, 100 ) );
    formatoTabla.setBorderStyle( QTextFrameFormat::BorderStyle_Solid );
    formatoTabla.setBorder( 1 );
    formatoTabla.setCellPadding( 3 );
    formatoTabla.setCellSpacing( 0 );
    tabla->setFormat( formatoTabla );
    tabla->cellAt( 0,0 ).firstCursorPosition().insertHtml( "<b> # Cuota</b>" );
    tabla->cellAt( 0,1 ).firstCursorPosition().insertHtml( "<b> Fecha de pago </b>" );
    tabla->cellAt( 0,2 ).firstCursorPosition().insertHtml( "<b> Cuota </b>" );
    tabla->cellAt( 0,3 ).firstCursorPosition().insertHtml( "<b> Subtotal </b>" );

    QTextBlockFormat bfizq = tabla->cellAt( 0, 3 ).firstCursorPosition().blockFormat();
    bfizq.setAlignment( Qt::AlignRight );
    // Ingreso los datos
    double subtotal = DSBImporte->value() * (-1);
    // Importe
    tabla->cellAt( 1, 0 ).firstCursorPosition().insertHtml( " " );
    tabla->cellAt( 1, 1 ).firstCursorPosition().insertHtml( "Importe a pagar en cuotas" );
    tabla->cellAt( 1, 2 ).firstCursorPosition().setBlockFormat( bfizq );
    tabla->cellAt( 1, 2 ).firstCursorPosition().insertHtml( QString( "$ %L1" ).arg( subtotal*(-1), 10, 'f', 2 ) );
    tabla->cellAt( 1, 3 ).firstCursorPosition().setBlockFormat( bfizq );
    tabla->cellAt( 1, 3 ).firstCursorPosition().insertHtml( QString( "$ %L1" ).arg( subtotal, 10, 'f', 2 ) );
    subtotal += DSBEntrega->value();
    tabla->cellAt( 2, 0 ).firstCursorPosition().insertHtml( "" );
    tabla->cellAt( 2, 1 ).firstCursorPosition().insertHtml( "Entrega inicial" );
    tabla->cellAt( 2, 2 ).firstCursorPosition().setBlockFormat( bfizq );
    tabla->cellAt( 2, 2 ).firstCursorPosition().insertHtml( QString( "$ %L1" ).arg( DSBEntrega->value(), 10, 'f', 2 ) );
    tabla->cellAt( 2, 3 ).firstCursorPosition().setBlockFormat( bfizq );
    tabla->cellAt( 2, 3 ).firstCursorPosition().insertHtml( QString( "$ %L1" ).arg( subtotal, 10, 'f', 2 ) );
    subtotal *= ( 1 + DSBInteres->value() / 100 );
    double valor_cuota = ( ( DSBTotal->value() ) * ( 1 + DSBInteres->value() / 100 ) ) / SBCantidad->value();
    QDate fch = DEInicio->date();
    for( int i = 1; i<=SBCantidad->value(); i++ ) {
        tabla->cellAt( i+2, 0 ).firstCursorPosition().insertHtml( QString( "%1" ).arg( i ) );
        tabla->cellAt( i+2, 1 ).firstCursorPosition().insertHtml( QString( "%1" ).arg( fch.toString( Qt::SystemLocaleShortDate ) ) );
        fch.addDays( (i-1)*MPlanCuota::diasEnPeriodo( (MPlanCuota::Periodo) CBPeriodo->currentIndex(), fch ) );
        tabla->cellAt( i+2, 2 ).firstCursorPosition().setBlockFormat( bfizq );
        tabla->cellAt( i+2, 2 ).firstCursorPosition().insertHtml( QString( "$ %L1" ).arg( valor_cuota, 10, 'f', 2 ) );
        subtotal += valor_cuota;
        tabla->cellAt( i+2, 3 ).firstCursorPosition().setBlockFormat( bfizq );
        tabla->cellAt( i+2, 3 ).firstCursorPosition().insertHtml( QString( "$ %L1" ).arg( subtotal, 10, 'f', 2 ) );
    }

    // Firma y aclaracion
    cursor.movePosition( QTextCursor::End );
    cursor.insertBlock();
    cursor.insertBlock();
    cursor.insertBlock();
    cursor.insertBlock();
    cursor.insertBlock();
    cursor.insertText( "Firma del contrayente: ________________________" );
    cursor.insertBlock();
    cursor.insertBlock();
    cursor.insertText( QString::fromUtf8( "Aclaración: ____________________________________________" ) );
    cursor.insertBlock();
    cursor.insertBlock();
    cursor.insertHtml( QString::fromUtf8( "<small>En caso de provocarse un atraso en la fecha de pago de cualquiera de las cuotas, se aplicará el recargo correspondiente tal cual se hace actualmenete con cualquier recibo emitido por nuestra entidad.</small>" ) );

    // Cabecera
    cursor.movePosition( QTextCursor::Start );
    cursor.insertBlock();
    cursor.insertHtml( "<h1>" + ERegistroPlugins::getInstancia()->pluginInfo()->empresa() + "</h1><br />" );
    cursor.insertHtml( "<h2>Plan de cuotas</h2><br /><br />" );
    cursor.insertBlock();
    cursor.insertHtml( QString( "<b>Fecha de Inicio:</b> %1 <br />" ).arg( DEInicio->date().toString( Qt::SystemLocaleLongDate ) ) );
    cursor.insertHtml( QString( "<b>Nombre del cliente:</b> %1 <br />").arg( "Desconocido" ) );
    return;
}

/*!
 * \fn FormDetalleCuotas::pdf()
 * Genera un pdf con las cuotas tal cual se ingresaron en los datos.
 */
void FormDetalleCuotas::pdf()
{
    this->generaReporte();
    QPrinter *imp = new QPrinter( QPrinterInfo::defaultPrinter() );
    imp->setOutputFormat( QPrinter::PdfFormat );
    QString nombreArchivo = QFileDialog::getSaveFileName( this, "Guardar como pdf", QDir::homePath(), "Archivos PDF (*.pdf)" );
    if( !nombreArchivo.isEmpty() )
    {
     // ver que tenga la extension
     imp->setOutputFileName( nombreArchivo );
     documento->print( imp );
    }
    delete imp;
}

/*!
 * \brief FormDetalleCuotas::setearIdPlanCuota
 * Setea el id de cuota correspondiente.
 * \param id Identificador del plan de cuotas
 */
void FormDetalleCuotas::setearIdPlanCuota( int /*id*/ ) {
    qWarning( "Carga de datos no implementada!" );
    // Cargo los datos de la cuota

}
