#include "reportescuotas.h"
#include "EReporte.h"

#include <QDate>
#include <QMessageBox>
#include <QInputDialog>

/*!
 * \brief ReportesCuotas::version
 * \return
 */
double ReportesCuotas::version() const
{ return 0.1; }

/*!
 * \brief ReportesCuotas::nombre
 * \return
 */
QString ReportesCuotas::nombre() const
{ return "ReportesCuotas"; }

/*!
 * \brief ReportesCuotas::inicializar
 * \return
 */
bool ReportesCuotas::inicializar()
{
    ActResumenCuotasDeudaHistorica = new QAction( this );
    ActResumenCuotasDeudaHistorica->setText( "Deuda historica" );
    ActResumenCuotasDeudaHistorica->setStatusTip( "Muestra un resumen de los estados de todas las cuotas" );
    ActResumenCuotasDeudaHistorica->setIcon( QIcon( ":/imagenes/resumen_cuotas.png" ) );
    connect( ActResumenCuotasDeudaHistorica, SIGNAL( triggered() ), this, SLOT( resumenCuotasDeudaHistorica() ) );

    ActResumenCuotasMes = new QAction( this );
    ActResumenCuotasMes->setText( "Deuda en mes" );
    ActResumenCuotasMes->setStatusTip( "Muestra el resumen de las cuotas del mes" );
    connect( ActResumenCuotasMes, SIGNAL( triggered() ), this, SLOT( resumenCuotasMes() ) );

    ActResumenCuotasCliente = new QAction( this );
    ActResumenCuotasCliente->setText( "Deuda por cliente" );
    ActResumenCuotasCliente->setStatusTip( "Muestra las deudas de un cliente especifico" );
    connect( ActResumenCuotasCliente, SIGNAL( triggered() ), this, SLOT( resumenCuotasCliente() ) );

    return true;
}

/*!
 * \brief ReportesCuotas::hacerMenu
 * \param m
 */
void ReportesCuotas::hacerMenu( QMenu *m )
{
    QMenu *menu = m->addMenu( "Cuotas" );
    menu->addAction( ActResumenCuotasDeudaHistorica );
    menu->addAction( ActResumenCuotasMes );
    menu->addAction( ActResumenCuotasCliente );
}

/*!
 * \brief ReportesCuotas::resumenCuotasDeudaHistorica
 */
void ReportesCuotas::resumenCuotasDeudaHistorica()
{
    QMessageBox::information( 0, "Error", "No implementado" );
    return;
    /// @TODO Implementar el reporte de cuotas historicas
    EReporte *rep = new EReporte( 0 );
    rep->especial( "cuotashistoricas", ParameterList() );
    rep->hacerPDF( ParameterList(), QString( "DeudasCuotasAl" ).arg( QDate::currentDate().toString( Qt::LocaleDate ) ) );
    delete rep;
}

/*!
 * \brief ReportesCuotas::resumenCuotasMes
 */
void ReportesCuotas::resumenCuotasMes()
{
    QMessageBox::information( 0, "Error", "No implementado" );
    return;
    /// @TODO Implementar reporte de Deuodas de cuotas según mes.
    bool ok = false;
    QStringList meses;
    QString mes = QInputDialog::getItem( 0, "Elija el mes", "Elija el mes:", meses, QDate::currentDate().month(), false, &ok );
    if( ok ) {
        EReporte *rep = new EReporte( 0 );
        ParameterList lista;
        lista.append( Parameter( "mes", meses.indexOf( mes ) ) );
        rep->especial( "deudascuotasmes", lista );
        rep->hacerPDF( ParameterList(), QString( "DeudasCuotasAl" ).arg( QDate::currentDate().toString( Qt::LocaleDate ) ) );
        delete rep;
    }
}

/*!
 * \brief ReportesCuotas::resumenCuotasCliente
 */
void ReportesCuotas::resumenCuotasCliente()
{
    QMessageBox::information( 0, "Error", "No implementado" );
    return;
    /// @TODO Implementar reporte de deuda segun cliente
    EReporte *rep = new EReporte( 0 );
    int id_cliente = 1;
    ParameterList lista;
    lista.append( "id_cliente", id_cliente );
    rep->especial( "deudascuotascliente", lista );
    rep->hacerPDF( ParameterList(), QString( "DeudasCuotasAl" ).arg( QDate::currentDate().toString( Qt::LocaleDate ) ) );
    delete rep;
}

Q_EXPORT_PLUGIN2( reportescuotas, ReportesCuotas )