#include "FormVerificarRecargos.h"

#include <QAction>
#include <QIcon>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDatabase>

#include "eactcerrar.h"


FormVerificarRecargos::FormVerificarRecargos(QWidget *parent) :
 EVentana( parent )
{
    setupUi(this);
    setObjectName( "verificarRecargos" );
    setWindowTitle( "Verificar Recargos" );

    // Reseteo las barras y demases
    PrBServicios->setValue( 0 );
    PrBRecargos->setValue( 0 );
    PrBClientes->setValue( 0 );

    DSBDeudas->setValue( 0.0 );

    LNDeudores->display( 0 );
    LNTotalProcesado->display( 0 );
    LNTotal->display( 0 );

    LNombreServicio->setText( "" );
    LPrecioBase->setText( "" );
    LPeriodo->setText( "" );

    LDiasPasados->setText( "" );
    LSobrecargo->setText( "" );

    ActIniciar = new QAction( this );
    ActIniciar->setText( "Iniciar" );
    ActIniciar->setIcon( QIcon( ":/imagenes/next.png" ) );
    connect( ActIniciar, SIGNAL( triggered() ), this, SLOT( iniciar() ) );

    ActDetener = new QAction( this );
    ActDetener->setText( "Detener" );
    ActDetener->setIcon( QIcon( ":/imagenes/stop.png" ) );
    ActDetener->setVisible( false );
    connect( ActDetener, SIGNAL( triggered() ), this, SLOT( detener() ) );

    addAction( ActIniciar );
    addAction( ActDetener );
    addAction( new EActCerrar( this ) );

    _detener = false;
    cant_servicios = 0;

}

void FormVerificarRecargos::changeEvent(QEvent *e)
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

#include "mservicios.h"
#include "mperiodoservicio.h"
#include "mrecargos.h"
#include "mrecargoshechos.h"

void FormVerificarRecargos::iniciar()
{
 _detener = false;
 l( "Iniciando verificaciones..." );
 ActIniciar->setVisible( false );
 ActDetener->setVisible( true );
 QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).transaction();

 // Busco la cantidad de servicios y los servicios
 QSqlQuery cola;
 l("Buscando cantidad de servicios" );
 if( cola.exec( "SELECT COUNT(id_servicio) FROM servicios WHERE fecha_baja IS NOT NULL" ) ) {
     if( cola.next() ) {
         cant_servicios = cola.record().value(0).toInt();
     } else {
         l( "Error de next al ejecutar la cola de cantidad de servicios para revisar. Posiblemente no exista ningun servicio activo" );
         l( cola.lastError().text() );
         l( cola.lastQuery() );
     }
 } else {
     l( "Error de ejecucion en la cola de cantidad de servicios para revisar. Posiblemente no exista ningun servicio activo" );
     l( cola.lastError().text() );
     l( cola.lastQuery() );
 }

 if( _detener ) { QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback(); return; }
 if( cant_servicios == 0 ) {
     l( "No hay servicios para verificar" );
     ActDetener->setVisible( false );
     _detener = true;
     QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback();
     return;
 }

 l( QString( "%1 servicio(s) encontrados" ).arg( cant_servicios ) );
 PrBServicios->setRange( 0, cant_servicios );
 PrBServicios->setValue( 0 );

 // Coloco los servicios en una lista
 lista_servicios.empty();
 if( cola.exec( "SELECT id_servicio FROM servicios WHERE fecha_baja IS NOT NULL" ) ) {
     while( cola.next() ) {
         lista_servicios.append( cola.record().value(0).toInt() );
     }
 } else {
     l( "Error de ejecucion en la cola de servicios para revisar." );
     l( cola.lastError().text() );
     l( cola.lastQuery() );
     _detener = true;
     ActDetener->setVisible( true );
     QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback();
 }
 if( _detener ) { QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback(); return; }

 // Inicializo este objeto para poder usarlo adentro de los fors
 MPeriodoServicio *mps = new MPeriodoServicio( this );

 for( int serv = 0; serv < cant_servicios; serv++ ) {
    // Cargo los datos
    int id_servicio = lista_servicios.at( serv );

     if( _detener ) { QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback(); return; }

    l( "Cargando datos del servicio" );
    LNombreServicio->setText( MServicios::getNombreServicio( id_servicio ) );
    double precio_base = MServicios::precioBase( id_servicio );
    LPrecioBase->setText( QString( "$ %L1" ).arg( precio_base ) );
    int id_periodo_servicio = mps->getPeriodoActual( id_servicio );
    //LPeriodo->setText(  mps->get );

    // Busco la cantidad de recargos que tiene el servicio
    int cant_recargos = 0;
    if( cola.exec( QString( "SELECT COUNT(id_recargo) FROM recargos WHERE id_servicio = %1" ).arg( id_servicio ) ) ) {
        if( cola.next() ) {
            cant_recargos = cola.record().value(0).toInt();
        } else {
            l( "Error de next al ejecutar la cola de cantidad de servicios para revisar. Posiblemente no exista ningun servicio activo" );
            l( cola.lastError().text() );
            l( cola.lastQuery() );
        }
    } else {
        l( "Error de ejecucion en la cola de cantidad de servicios para revisar. Posiblemente no exista ningun servicio activo" );
        l( cola.lastError().text() );
        l( cola.lastQuery() );
    }
     if( _detener ) { QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback(); return; }
    if( cant_recargos == 0 ) {
        l( "No se encontraron recargos activos para el servicio" );
    } else {
        PrBRecargos->setRange( 0, cant_recargos );
        PrBRecargos->setValue( 0 );
        // Cargo la lista de recargos y cantidad de dias pasados
        QMap<int,int> lista_recargos;
        lista_recargos.empty();
        if( cola.exec( QString( "SELECT id_recargo, cant_dias FROM recargos WHERE id_servicio = %1" ).arg( id_servicio ) ) ) {
            while( cola.next() ) {
                lista_recargos.insert( cola.record().value(0).toInt(), cola.record().value(1).toInt() );
                if( _detener ) { QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback(); return; }
            }
        } else {
            l( "Error de ejecucion en la cola de servicios para revisar." );
            l( cola.lastError().text() );
            l( cola.lastQuery() );
        }
        if( _detener ) { QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback(); return; }
        QDate fecha_inicio = mps->getFechaInicioPeriodoActual( id_servicio );
        QString nombre_servicio = MServicios::getNombreServicio( id_servicio );
        // La lista no puede estar vacia sino el conteo deberia de haber dado 0
        for( QMap<int,int>::iterator recargo = lista_recargos.begin(); recargo != lista_recargos.end(); recargo++ ) {
             if( _detener ) { QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback(); return; }
            // Veo si el recargo es valido para el dia de hoy
            if( fecha_inicio.daysTo( QDate::currentDate() ) > recargo.value() ) {
                // Hay mas cantidad de dias que los minimos - > genero los elementos
                // Busco cada cliente asociado y veo si pago la cuota

                if( cola.exec(
                    QString( "SELECT COUNT( id_cliente ) FROM cobro_servicio_cliente_periodo "
                             " WHERE id_servicio = %1 AND id_periodo_servicio = %2 " ).arg( id_servicio ).arg( id_periodo_servicio ) ) ) {
                    cola.next();
                    int cantidad_clientes = cola.record().value(0).toInt();
                    if( cantidad_clientes == 0 ) {
                        l( "Ningun cliente deudor" );
                        continue;
                    } else {
                        LNTotal->display( cantidad_clientes );
                        PrBClientes->setRange( 0, cantidad_clientes );
                    }
                }
                if( _detener ) { QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback(); return; }
                double costo_recargo = MRecargos::calcularRecargo( recargo.key() );
                if( cola.exec(
                    QString( "SELECT id_cliente FROM cobro_servicio_cliente_periodo "
                             " WHERE id_servicio = %1 AND id_periodo_servicio = %2 "
                             " AND id_recibo IS NULL" ).arg( id_servicio ).arg( id_periodo_servicio ) ) ) {
                    while( cola.next() ) {
                        if( _detener ) { QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback(); return; }
                        // Para cada cliente agrego un recargo
                        if( !MRecargosHechos::agregarRecargo( id_periodo_servicio,
                                                              id_servicio,
                                                              cola.record().value(0).toInt(),
                                                              recargo.key(),
                                                              QDateTime::currentDateTime(),
                                                              QString( "Retraso de pago para %1" ).arg( nombre_servicio ),
                                                              costo_recargo ) ) {
                            l("No se pudo agregar el recargo!!! <-------------");
                        } else {
                            LNDeudores->display( LNDeudores->value() + 1 );
                            DSBDeudas->setValue( DSBDeudas->value() + costo_recargo );
                        }
                        LNTotalProcesado->display( LNTotalProcesado->value() + 1 );
                        PrBClientes->setValue( PrBClientes->value() + 1 );

                    }
                } else {
                    l( "Error al buscar los datos de los clientes que no pagaron!" );
                    l( cola.lastError().text() );
                    l( cola.lastQuery() );
                }
                 if( _detener ) { QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback(); return; }

            } else {
                l( "El recargo considerado todavia no entro en vigencia" );
            }
            PrBRecargos->setValue( PrBRecargos->value() + 1 );
            if( _detener ) { QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback(); return; }
        } // Fin bucle de recargo
        l( "Fin de procesado del recargo del servicio" );
        if( _detener ) { QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback(); return; }
    }
    l( "Fin de procesado del servicio" );
    PrBServicios->setValue( PrBServicios->value() + 1 );
     if( _detener ) { QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).rollback(); return; }
 } // fin for servicios

 ActDetener->setVisible( false );
 _detener = true;
 l( "Terminado!" );
 return;
}

void FormVerificarRecargos::detener()
{
    _detener = true;
    QApplication::processEvents();
}


void FormVerificarRecargos::l( QString cadena )
{
    PTELog->appendPlainText( cadena + "\n" );
}
