/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   				   *
 *   juiraze@yahoo.com.ar   						   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "FormFacturarServicio.h"
#include "eactcerrar.h"
#include "mservicios.h"
#include "mrecargos.h"
#include "MTempClientesFacturarServicio.h"
#include "dsino.h"
#include <QPair>
#include "mperiodoservicio.h"
#include <QLocale>

FormFacturarServicio::FormFacturarServicio(QWidget *parent) :
EVentana(parent), _id_servicio(0)  {

    setupUi(this);

    this->setWindowTitle( "Facturacion de un servicio" );
    //this->setWindowIcon( QIcon( ":/imagenes/" ) );
    this->setObjectName( "facturaservicios" );

    ActCerrar = new EActCerrar( this );

    ActFacturar = new QAction( this );
    ActFacturar->setText( "Facturar" );
    ActFacturar->setStatusTip( "Factura el servicio con los clientes seleccionados" );
    ActFacturar->setIcon( QIcon( ":/imagenes/" ) );
    connect( ActFacturar, SIGNAL( triggered() ), this, SLOT( facturar() ) );

    this->addAction( ActFacturar );
    this->addAction( ActCerrar );

    // Escondo el progreso
    this->GBProgreso->setVisible( false );
    this->PBCancelar->setText( "Cancelar" );

}

void FormFacturarServicio::changeEvent(QEvent *e)
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
 * \fn FormFacturarServicio::setearServicio( const int id_servicio )
 *  Setea el id de servicio que se desea realizar la facturación
 * \param id_servicio ID del servicio
 */
void FormFacturarServicio::setearServicio(const int id_servicio)
{
    if( id_servicio > 0 ) {
        this->_id_servicio = id_servicio;
        this->cargar_datos_servicio();
    } else {
        qWarning( "Servicios:FormFacturarServicio: Seteando un servicio < o = 0");
        return;
    }
}

/*!
 * \fn FormFacturarServicio::cargar_datos_servicio()
 * Carga los datos de un servicio seleccionado
 */
void FormFacturarServicio::cargar_datos_servicio()
{
    MServicios *m = new MServicios( this );
    this->LNombreServicio->setText( m->getNombreServicio( this->_id_servicio ) );
    this->_precio_base = m->precioBase( this->_id_servicio );
    this->LPrecioBase->setText( QString( "$ %L1" ).arg( this->_precio_base  ) );
    MPeriodoServicio *mp = new MPeriodoServicio();
    this->_periodo = mp->getPeriodoActual( this->_id_servicio );
    this->_ano = mp->getAnoActual( this->_id_servicio );
    QDate fecha_inicio = mp->getFechaInicioPeriodoActual( this->_id_servicio );
    if( fecha_inicio.isValid() ) { qDebug( QString( "Fecha de inicio valida. %1 " ).arg( fecha_inicio.toString() ).toLocal8Bit() ); }
    this->LPeriodo->setText(
        QString( " %1/%2 desde %3 hasta %4 " )
                .arg( this->_periodo )
                .arg( this->_ano )
                .arg( fecha_inicio.toString( Qt::SystemLocaleShortDate ) )
                .arg( mp->obtenerFechaFinPeriodo( this->_id_servicio, fecha_inicio ).toString( Qt::SystemLocaleShortDate) )
    );
    // Cargo los clientes del servicio
    MTempClientesFacturarServicio *mc = new MTempClientesFacturarServicio( this );
    // Cargo los clientes
    this->TVClientes->setModel( mc );
    this->TVClientes->hideColumn( 2 );
    mc->cargarClientesDelServicio( this->_id_servicio );
    this->TVClientes->setItemDelegateForColumn( 0, new DSiNo( this->TVClientes ) );
    this->TVClientes->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
    // Cargo los recargos del servicio
    MRecargos *mr = new MRecargos( this, false );
    mr->setFilter( QString( "id_servicio = %1 " ).arg( this->_id_servicio ) );
    mr->setearPrecioBase( this->_precio_base );
    this->TVRecargos->setModel( mr );
    this->TVRecargos->hideColumn( 0 );
    this->TVRecargos->hideColumn( 1 );
    this->TVRecargos->horizontalHeader()->setResizeMode( QHeaderView::Stretch );
    // Arreglar problema con el item de si o no tamaño.
    mr->select();
}

#include <QLabel>
#include <QMessageBox>
#include <QProgressBar>
#include <QInputDialog>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QHash>
#include "EReporte.h"
#include "../pagos/mpagos.h"
#include "../CtaCte/mitemcuentacorriente.h"
#include "../CtaCte/mcuentacorriente.h"
#include "../ventas/MFactura.h"
#include "../ventas/mitemfactura.h"
#include "mcobroservicioclienteperiodo.h"
#include "mperiodoservicio.h"
/*!
 * \fn FormFacturarServicio::facturar()
 * Realiza la facturación efectiva del servicio. El usuario ya acepto el facturar y los datos.
 */
void FormFacturarServicio::facturar()
{
    // Deshabilito los elementos editables
    this->GBClientes->setEnabled( false );
    this->GBRecargos->setEnabled( false );
    // Genero una barra de progreso y sus botones y demas
    this->GBProgreso->setVisible( true );
    LIndicador->setText( "Iniciando...");
    PBProgreso->setValue( 0 );
    connect( PBCancelar, SIGNAL( clicked() ), this, SLOT( cancelar() ) );
    this->_cancelar = false;

    // Cuento la cantidad de recibos a realizar
    int cantidad_total = qobject_cast<MTempClientesFacturarServicio *>(this->TVClientes->model())->rowCount();
    int cantidad_actual = 0;
    // usar para calcular cantidad de operaciones mostradas x recibo
    int multiplicador_pasos = 4;
    this->PBProgreso->setRange( 0, cantidad_total * multiplicador_pasos );


    // Inicializo el modelo  de las facturas
#ifdef GESTOTUX_HICOMP
    MPagos *mr = new MPagos();
#else
    MFactura *mr = new MFactura();
#endif
    MTempClientesFacturarServicio *mtemp = qobject_cast<MTempClientesFacturarServicio *>(this->TVClientes->model());

    // Inicializo los valores que voy a ir refrescando
    int id_recibo = -1;
    int id_cliente = -1;
    QString nombre_cliente = "";
    QHash<int, int> comprobantes; // Guarda el paso con el id del recibo guardado

    // Genero la transación en la base de datos ( total )
    QSqlDatabase::database().transaction();

    //////////////////////////////////////////////////////////////////////////////
    // Genero los datos de cuando estoy cobrando
    MPeriodoServicio *mp = new MPeriodoServicio();
    int id_periodo_servicio = mp->agregarPeriodoAFacturarNuevo( this->_id_servicio );
    if( id_periodo_servicio == -1 ) {
        qDebug( "El metodo de agregar periodo a facturar nuevo devolvio error." );
        QSqlDatabase::database().rollback();
        return;
    }

    //////////////////////////////////////////////////////////////////////
    // Itero por cada uno de los clientes para este cobro de servicio
    for( int i = 0; i<cantidad_total; i++ ) {
        // Veo si el elemento esta para ser facturado
        if( !mtemp->data( mtemp->index( i, 0 ), Qt::EditRole ).toBool() ) {
            qDebug( QString( "Item %1: No se facturara" ).arg( i ).toLocal8Bit() );
            // Avanzo la cantidad de pasos que sería por facturarle
            PBProgreso->setValue( PBProgreso->value() + multiplicador_pasos );
            continue;
        }
        /// Estos serían los datos de "servicios_clientes"
        // Cargo el dato correspondiente a esa fila
        id_cliente = mtemp->data( mtemp->index( i, 2 ), Qt::DisplayRole ).toInt();
        qDebug( QString( "Item %1-ID Cliente: %2." ).arg( i ).arg( id_cliente ).toLocal8Bit() );
        nombre_cliente = mtemp->data( mtemp->index( i, 1 ), Qt::DisplayRole ).toString();
        qDebug( QString( "Item %1-Nombre Cliente: %2." ).arg( i ).arg( nombre_cliente ).toLocal8Bit() );

        ///////////////////////////////////////////////////////////////////////////////////////////
        // Paso 1 - Genero la factura con los items actuales mas los anteriores segun corresponda /
        ///////////////////////////////////////////////////////////////////////////////////////////
        LIndicador->setText( QString( "Generando factura ( %1 de %2 )..." ).arg( cantidad_actual + 1  ).arg( cantidad_total ) );
        int id_factura = -1;
/*#ifdef GESTOTUX_HICOMP
        id_factura = mr->agregarRecibo( id_cliente,
                                        QDate::currentDate(),
                                        QString( "Recibo por el pago del periodo %1 año %2" ).arg( this->LPeriodo->text() ).arg( this->_ano ),
                                        this->_precio_base,
                                        false, // No efectivo y no pagado para que quede para despues
                                        false );
#elseif*/
        id_factura = mr->agregarFactura( id_cliente,
                                         QDateTime::currentDateTime(),
                                         MFactura::CuentaCorriente,
                                         this->_precio_base );
//#endif
        if( id_factura == -1 ) {
            QMessageBox::warning( this, "Error", "No se pudo generar la factura para el cliente requerido - se cancelara toda la facturacion del servicio" );
            qDebug( "Error al generar la factura - id erroneo" );
            QSqlDatabase::database().rollback();
            return;
        } else {
            // Si se genero correctamente ingreo el id en la cola para impresion luego.
            comprobantes.insert( i, id_factura );
            qDebug( "Comprobante guardado correctamente - agregado a la cola para post impresion" );
            // Genero los items para el comprobante
            MItemFactura *fact = new MItemFactura();
            if( !fact->agregarItemFactura( id_factura,
                                           1,
                                           QString( "Cobro del servicio %1 para el periodo %2 del año %3" ).arg( MServicios::getNombreServicio( this->_id_servicio ) ).arg( this->_periodo ).arg( this->_ano ),
                                           this->_precio_base ) ) {
                qDebug( "Error al intentar agregar el item de factura para el servicio del mes facturado" );
                QSqlDatabase::database().rollback();
                return;
            }


        }
        PBProgreso->setValue( PBProgreso->value() + 1 );
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        // Paso 2 - Genero la entra en cobro-servicio-cliente-servicio con el id de factura correspondiente /
        /////////////////////////////////////////////////////////////////////////////////////////////////////
        if( !MCobroServicioClientePeriodo::agregarCobro( id_periodo_servicio, this->_id_servicio, id_cliente, id_factura ) ) {
            qDebug( "Error al generar la entrada de cobro para un servicio-cliente-cobro" );
            QSqlDatabase::database().rollback();
            return;
        }
        PBProgreso->setValue( PBProgreso->value() + 1 );
        /////////////////////////////////////////////////////////////////
        // Paso 3 - Genero la entrada en la cuenta corriente del cliente
        /////////////////////////////////////////////////////////////////
        return;

        //// @ todo Modificar el metodo de agregar operación para que devuelva el id
        LIndicador->setText( QString( "Actualizando cuenta corriente del cliente %1  ( %2 de %3 )..." ).arg( nombre_cliente ).arg( cantidad_actual ).arg( i ) );
        // Intento agregar el numero de operación
        QString id_ctacte = MCuentaCorriente::obtenerNumeroCuentaCorriente( id_cliente );
        int id_op_ctacte = MItemCuentaCorriente::agregarOperacion( id_ctacte,
                                                                   QString( "%L1" ).arg( id_factura ),
                                                                   id_factura,
                                                                   MItemCuentaCorriente::Factura,
                                                                   QDate::currentDate(),
                                                                   QString( "Cobro del servicio %2 por el periodo %1" ).arg( this->LPeriodo->text() ).arg( this->LNombreServicio->text() ),
                                                                   this->_precio_base );
        if( id_op_ctacte == -1 ) {
            // Error al guardar el  item de cuenta corriente
            qWarning( "Error al guardar el item de cuenta corriente" );
            QSqlDatabase::database().rollback();
            break;
        }
        PBProgreso->setValue( PBProgreso->value() + 1 );
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Paso 4 - Actualizo la entrada en cobro-servicio-cliente-servicio con el  numero de operación de la cuenta corriente /
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if( !MCobroServicioClientePeriodo::setearIDCtaCte( id_periodo_servicio, this->_id_servicio, id_cliente, id_op_ctacte ) ) {
            qDebug( "Error al actualizar el indice de cuenta corriente en el cobro de servicio para el servicio cliente" );
            QSqlDatabase::database().rollback();
            return;
        }
        PBProgreso->setValue( PBProgreso->value() + 1 );
        ///////////////////////////////////////
        // Fin bucle para cada cliente
        ///////////////////////////////////////
        cantidad_actual++;
        QMessageBox::warning( this, "Atencion!", "bucle terminado" );
    }
    // Guardo todos los datos
    QMessageBox::warning( this, "Atencion!", "Luego de este cartel se hara un rollback!" );
    QSqlDatabase::database().rollback();
    return;
    //QSqlDatabase::database().commit();

    // Inicializo el reporter
#ifdef GESTOTUX_HICOMP
    orReport *reporte = new orReport( "recibo" );
#else
    orReport *reporte = new orReport( "factura" );
#endif

    for( int i = 0; i<cantidad_total; i++ ) {
        // Paso 3
        // Imprimir recibo
        // Genero los parametros
        ParameterList lista;
#ifdef GESTOTUX_HICOMP
        lista.append( "id_recibo", comprobantes.take( i ) );
        reporte->setParamList( lista );
        LIndicador->setText( QString( "Imprimiendo recibo Nº %1 ( %2 de %3 )" ).arg( id_recibo ).arg( cantidad_actual ).arg( i ) );
#else
        lista.append( "id_factura", comprobantes.take( i ) );
        reporte->setParamList( lista );
        LIndicador->setText( QString( "Imprimiendo factura Nº %1 ( %2 de %3 )" ).arg( id_recibo ).arg( cantidad_actual ).arg( i ) );
#endif
        PBProgreso->setValue( PBProgreso->value() + 1 );
        reporte->print( 0, true, false );
        // Actualizo indices y reinicio valores
        cantidad_actual++;
        id_recibo = -1;
        nombre_cliente = "";
    } // Fin for recibos


    // Pregunto si los recibos se imprimieron bien
    int ret = QMessageBox::question( this, "Impresion", "¿Se imprimieron correctamente <b>TODOS</b> los comprobantes?" );

    if( ret == QMessageBox::Rejected ) {
       // Si no, pregunto que numero de recibo falta y lo mando a imprimir
        ret = true;
        while( ret ) {

            // Pregunto el numero del recibo y doy opcion a cancelar cuando se acabaron
            bool ok = false;
            int ret2 = QInputDialog::getInt( this, "Numero de recibo", "Ingrese el numero del comprobante que se imprimio incorrectamente, si no hay mas comprobantes mal impresos, presione cancelar", 0, 0,2147483647, 1, &ok );
            if( ok == true ) {
                // Ingreso un recibo mal impreso, lo reimprimo
                ParameterList lista;
#ifdef GESTOTUX_HICOMP
                lista.append( "id_recibo", ret2 );
                reporte->setParamList( lista );
#else
                lista.append( "id_factura", ret2 );
                reporte->setParamList( lista );
#endif
                reporte->print( 0, false, false );
            } else {
                // No hay mas recibos fallados
                ret = false;
            }
        }
    }

    // Libero modelos
    delete reporte;
    delete mr;
    reporte = 0;
    mr = 0;
    // Cierro el formulario
    this->close();
    return;
}
