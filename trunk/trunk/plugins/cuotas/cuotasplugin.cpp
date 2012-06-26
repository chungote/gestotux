#include "cuotasplugin.h"
#include <QMenuBar>
#include <QSqlDatabase>
#include "formprefcaja.h"

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

#include "formprefcuotas.h"

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
 //ActVerCuotas->setIcon( QIcon( ":/imagenes/caja.png" ) );
 connect( ActVerCuotas, SIGNAL( triggered() ), this, SLOT( verCuotas() ) );

 ActGenerarComprobantes = new QAction( this );
 ActGenerarComprobantes->setText( "Ver Estado Caja" );
 ActGenerarComprobantes->setToolTip( "Ver el estado actual de la caja." );
 //ActGenerarComprobantes->setIcon( QIcon( ":/imagenes/cajaestado.png" ) );
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
 /*else if( !tablas.contains( "item_cuota" ) )
 { qDebug( "Error al buscar la tabla item_cuota" ); return false; }*/
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
     /*menuCuotas->addAction( ActVerCuotas );
     menuCuotas->addAction( ActGenerarComprobantes );*/
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
 * \fn CuotasPlugin::generarComprobantes()
 */
void CuotasPlugin::generarComprobantes()
{

}

#include "vplancuotas.h"
/*!
 * \fn CuotasPlugin::verCuotas()
 * Muestra el listado de planes de cuotas activos al momento
 */
void CuotasPlugin::verCuotas()
{ emit agregarVentana( new VPlanCuotas() ); }

/*!
 * \fn CuotasPlugin::emitirVentaEnCuotas( int id_cliente, double total, int id_factura )
 */
void CuotasPlugin::emitirVentaEnCuotas( int id_cliente, double total, int id_factura )
{

}

#include "formsimularcuotas.h"
void CuotasPlugin::simularCuotas()
{ emit agregarVentana( new FormSimularCuotas() ); }

Q_EXPORT_PLUGIN2( Cuotas, CuotasPlugin )