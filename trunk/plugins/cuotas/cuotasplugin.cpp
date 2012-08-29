#include "cuotasplugin.h"

#include <QMenuBar>
#include <QSqlDatabase>

#include "vplancuotas.h"
#include "formprefcaja.h"
#include "formsimularcuotas.h"
#include "formprefcuotas.h"

/*!
    \fn CuotasPlugin::accionesBarra()
 */
QList<QActionGroup *> CuotasPlugin::accionesBarra()
{ return QList<QActionGroup *>(); }

/*!
    \fn CuotasPlugin::nombre() const
    Devuelve el nombre del plugin
 */
QString CuotasPlugin::nombre() const
{ return "cuotas"; }

/*!
    \fn CuotasPlugin::formsPreferencias()
    Muestra el formulario de preferencias de las cuotas.
 */
QWidgetList CuotasPlugin::formsPreferencias()
{
 QWidgetList lista;
 lista.append( new FormPrefCuotas() );
 return lista;
}

/*!
    \fn CuotasPlugin::inicializar()
 */
bool CuotasPlugin::inicializar()
{
 Q_INIT_RESOURCE(cuotas);

 ActVerCuotas = new QAction( this );
 ActVerCuotas->setText( "Cuotas Activas" );
 ActVerCuotas->setToolTip( "Ver el listado de los planes de cuotas que hay en el sistema." );
 //ActVerCuotas->setIcon( QIcon( ":/imagenes/.png" ) );
 connect( ActVerCuotas, SIGNAL( triggered() ), this, SLOT( verCuotas() ) );

 ActGenerarComprobantes = new QAction( this );
 ActGenerarComprobantes->setText( "Generar cuotas" );
 ActGenerarComprobantes->setToolTip( "Genera los comprobantes de cuotas correspondientes." );
 //ActGenerarComprobantes->setIcon( QIcon( ":/imagenes/.png" ) );
 connect( ActGenerarComprobantes, SIGNAL( triggered() ), this, SLOT( generarComprobantes() ) );

 ActSimular = new QAction( this );
 ActSimular->setText( "Simular Cuotas" );
 ActSimular->setStatusTip( "Abre el simulador de cuotas" );
 connect( ActSimular, SIGNAL( triggered() ), this, SLOT( simularCuotas() ) );

 return true;
}


/*!
    \fn CuotasPlugin::verificarTablas( QStringList tablas )
    Verifica que existan las tablas del plugin de cajas
    \param tablas listado de tablas
    \return Falso si falta alguna.
 */
bool CuotasPlugin::verificarTablas( QStringList tablas )
{
 if( !tablas.contains( "plan_cuota" ) )
 { qDebug( "Error al buscar la tabla plan_cuota" ); return false; }
 else if( !tablas.contains( "item_cuota" ) )
 { qDebug( "Error al buscar la tabla item_cuota" ); return false; }
 return true;
}

/*!
    \fn CuotasPlugin::tipo() const
 */
int CuotasPlugin::tipo() const
{ return EPlugin::comun; }


/*!
    \fn CuotasPlugin::crearMenu( QMenuBar *m )
 */
void CuotasPlugin::crearMenu( QMenuBar *m )
{
     QMenu *menuCuotas = m->addMenu( "Cuotas" );
     menuCuotas->addAction( ActVerCuotas );
     menuCuotas->addAction( ActGenerarComprobantes );
     menuCuotas->addAction( ActSimular );
}


/*!
    \fn CuotasPlugin::version() const
        Devuelve la version del plugin
 */
double CuotasPlugin::version() const
{ return 0.01; }

/*!
    \fn CuotasPlugin::crearToolBar( QToolBar *t )
 */
void CuotasPlugin::crearToolBar( QToolBar */*t*/ )
{ return; }

/*!
    \fn CuotasPlugin::seCierraGestotux()
 */
void CuotasPlugin::seCierraGestotux()
{ Q_CLEANUP_RESOURCE(cuotas); return; }

/*!
 * \fn CuotasPlugin::emitirPlanCuota( int id_cliente, double total )
 * Prepara la ventana para generar un plan de cuotas segun los datos pasados de la cuota.
 * \param id_cliente Identificador del cliente al cual se les emitirá el plan de cuotas
 * \param total Total a pagar
 */
void CuotasPlugin::emitirPlanCuota(int id_cliente, double total)
{
    FormSimularCuotas *f = new FormSimularCuotas();
    f->setearIdCliente( id_cliente );
    f->setearTotal( total );
    connect( f, SIGNAL( emitirIdPlanCuota( int ) ), this, SIGNAL( emitirPlanCuotaId( int ) ) );
    emit agregarVentana( f );
}

/*!
 * \brief CuotasPlugin::planCuotasSetearIdFactura
 * Slot llamado para cuando se ha echo el plan de cuotas pero no se asocio con ninguna factura, este metodo genera la asociación.
 * \param id_plan_cuota Identificador del plan de cuotas sobre el cual se asociará la factura correspondiente
 * \param id_factura Identificador de la factura para ese plan de cuotas
 */
void CuotasPlugin::planCuotasSetearIdFactura(int id_plan_cuota, int id_factura)
{
    MPlanCuota::asociarConFactura( id_plan_cuota, id_factura );
}

/*!
 * \fn CuotasPlugin::generarComprobantes()
 */
void CuotasPlugin::generarComprobantes()
{}

/*!
 * \fn CuotasPlugin::verCuotas()
 * Muestra el listado de planes de cuotas activos al momento
 */
void CuotasPlugin::verCuotas()
{ emit agregarVentana( new VPlanCuotas() ); }

void CuotasPlugin::simularCuotas()
{ emit agregarVentana( new FormSimularCuotas() ); }

Q_EXPORT_PLUGIN2( Cuotas, CuotasPlugin )