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

FormFacturarServicio::FormFacturarServicio(QWidget *parent) :
EVentana(parent), _id_servicio(0)  {

    setupUi(this);

    this->setWindowTitle( "Facturación de un servicio" );
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
    QPair<QPair<int,int>,QString> ret = m->getPeriodoActual( this->_id_servicio );
    this->_periodo = ret.first.first;
    this->_ano = ret.first.first;
    this->LPeriodo->setText( ret.second );
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
#include "mcobroservicio.h"
#include "../pagos/mpagos.h"
#include "../CtaCte/mitemcuentacorriente.h"
#include "../CtaCte/mcuentacorriente.h"
/*!
 * \fn FormFacturarServicio::facturar()
 * Realiza la facturación efectiva del servicio. El usuario ya acepto el facturar y los datos.
 */
/*void FormFacturarServicio::facturar()
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

    // Inicializo el reporter
    orReport *reporte_recibo = new orReport( "recibo" );
    // Inicializo el modelo  de las facturas
#ifdef GESTOTUX_HICOMP
    MPagos *mr = new MPagos();
#else
    //MFactura *mr = new MFactura();
#endif
    MTempClientesFacturarServicio *mtemp = qobject_cast<MTempClientesFacturarServicio *>(this->TVClientes->model());

    // Inicializo los valores que voy a ir refrescando
    int id_recibo = -1;
    int id_cliente = -1;
    QString nombre_cliente = "";
    QHash<int, int> recibos; // Guarda el paso con el id del recibo guardado

    // Genero la transación en la base de datos ( total )
    QSqlDatabase::database().transaction();
    // Itero por todos los recibos
    for( int i = 0; i<cantidad_total; i++ ) {
        // Veo si el elemento esta para ser facturado
        if( !mtemp->data( mtemp->index( i, 0 ), Qt::EditRole ).toBool() ) {
            qDebug( QString( "Item %1: No se facturara" ).arg( i ).toLocal8Bit() );
            continue;
        }

        // Cargo el dato correspondiente a esa fila
        id_cliente = mtemp->data( mtemp->index( i, 2 ), Qt::DisplayRole ).toInt();
        qDebug( QString( "Item %1-ID Cliente: %2." ).arg( i ).arg( id_cliente ).toLocal8Bit() );
        nombre_cliente = mtemp->data( mtemp->index( i, 1 ), Qt::DisplayRole ).toString();
        qDebug( QString( "Item %1-Nombre Cliente: %2." ).arg( i ).arg( nombre_cliente ).toLocal8Bit() );

        // Paso 1
        // Generar la Factura
        LIndicador->setText( QString( "Generando factura ( %1 de %2 )..." ).arg( cantidad_actual + 1  ).arg( cantidad_total ) );
        id_factura = mr->agregarRecibo( id_cliente,
                                       QDate::currentDate(),
                                       QString( "Recibo por el pago del periodo %1" ).arg( this->LPeriodo->text() ),
                                       this->_precio_base,
                                       false, // No efectivo y no pagado para que quede para despues
                                       false ); // Lo pongo en no pagado
        if( id_recibo <= 0 )
        {
                qWarning( QString( "Error al obtener el id del recibo. Item %1" ).arg( i ).toLocal8Bit() );
                QSqlDatabase::database().rollback();
                abort();
                break;
        } else {
            // Inserto los datos en la tabla correspondiente!
            recibos.insert( i, id_recibo );
        }
        PBProgreso->setValue( PBProgreso->value() + 1 );

        // Paso 2
        // Ponerlo en la cuenta corriente
        LIndicador->setText( QString( "Actualizando cuenta corriente del cliente %1  ( %2 de %3 )..." ).arg( nombre_cliente ).arg( cantidad_actual ).arg( i ) );
        // Busco el id de cuenta corriente
        QString id_ctacte = MCuentaCorriente::obtenerNumeroCuentaCorriente( id_cliente );
        if( !MItemCuentaCorriente::agregarOperacion( id_ctacte,
                                                QString( "%L1" ).arg( id_recibo ),
                                                id_recibo,
                                                MItemCuentaCorriente::Factura,
                                                QDate::currentDate(),
                                                QString( "Cobro del servicio %2 por el periodo %1" ).arg( this->LPeriodo->text() ).arg( this->LNombreServicio->text() ),
                                                this->_precio_base ) )
        {
            // Error al guardar la cuenta corriente
            qWarning( "Error al guardar el item de cuenta corriente" );
            // Cancelo el recibo ?
            QSqlDatabase::database().rollback();
            break;
        }
        PBProgreso->setValue( PBProgreso->value() + 1 );

        // Paso 3 - Guardo el cobro
        // Se hace ultimo para tener todos los ids de los comprobantes.
        if( MCobroServicio::agregarCobro( this->_id_servicio, id_cliente, id_recibo, this->_periodo, this->_ano ) )
        {
            PBProgreso->setValue( PBProgreso->value() + 1 );
        } else {
            qWarning( "Error al intentar agregar el cobro" );
            QSqlDatabase::database().rollback();
            break;
        }
        cantidad_actual++;
        QMessageBox::warning( this, "Atencion!", "bucle terminado" );
    }
    // Guardo todos los datos
    QMessageBox::warning( this, "Atencion!", "Luego de este cartel se hara un rollback!" );
    QSqlDatabase::database().rollback();
    return;
    //QSqlDatabase::database().commit();
    for( int i = 0; i<cantidad_total; i++ ) {
        // Paso 3
        // Imprimir recibo
        // Genero los parametros
        ParameterList lista;
        lista.append( "id_recibo", recibos.take( i ) );
        reporte_recibo->setParamList( lista );
        LIndicador->setText( QString( "Imprimiendo recibo Nº %1 ( %2 de %3 )" ).arg( id_recibo ).arg( cantidad_actual ).arg( i ) );
        PBProgreso->setValue( PBProgreso->value() + 1 );
        reporte_recibo->print( 0, true, false );
        // Actualizo indices y reinicio valores
        cantidad_actual++;
        id_recibo = -1;
        nombre_cliente = "";
    } // Fin for recibos


    // Pregunto si los recibos se imprimieron bien
    int ret = QMessageBox::question( this, "Impresion", "¿Se imprimieron correctamente <b>TODOS</b> los recibos?" );

    if( ret == QMessageBox::Rejected ) {
       // Si no, pregunto que numero de recibo falta y lo mando a imprimir
        ret = true;
        while( ret ) {

            // Pregunto el numero del recibo y doy opcion a cancelar cuando se acabaron
            bool ok = false;
            int ret2 = QInputDialog::getInt( this, "Numero de recibo", "Ingrese el numero del recibo que se imprimio incorrectamente, si no hay mas recibos mal impresos, presione cancelar", 0, 0,2147483647, 1, &ok );
            if( ok == true ) {
                // Ingreso un recibo mal impreso, lo reimprimo
                ParameterList lista;
                lista.append("id_recibo", ret2 );
                reporte_recibo->print( 0, false, false );
            } else {
                // No hay mas recibos fallados
                ret = false;
            }
        }
    }

    // Libero modelos
    delete reporte_recibo;
    delete mr;
    reporte_recibo = 0;
    mr = 0;
    // Cierro el formulario
    this->close();
    return;
}*/
