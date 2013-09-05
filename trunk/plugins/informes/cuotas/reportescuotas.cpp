#include "reportescuotas.h"
#include "EReporte.h"

#include <QDate>
#include <QMessageBox>

double ReportesCuotas::version() const
{ return 0.1; }

QString ReportesCuotas::nombre() const
{ return "ReportesCuotas"; }

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

void ReportesCuotas::hacerMenu( QMenu *m )
{
    QMenu *menu = m->addMenu( "Cuotas" );
    menu->addAction( ActResumenCuotasDeudaHistorica );
    menu->addAction( ActResumenCuotasMes );
    menu->addAction( ActResumenCuotasCliente );
}

void ReportesCuotas::resumenCuotasDeudaHistorica()
{
    QMessageBox::information( 0, "Error", "No implementado" );
}

void ReportesCuotas::resumenCuotasMes()
{
    QMessageBox::information( 0, "Error", "No implementado" );
}

void ReportesCuotas::resumenCuotasCliente()
{
    QMessageBox::information( 0, "Error", "No implementado" );
}

Q_EXPORT_PLUGIN2( reportescuotas, ReportesCuotas )