#include "dhistorialordentrabajo.h"
#include "ui_dhistorialordentrabajo.h"

#include "mtipooperacionordentrabajo.h"

DHistorialOrdenTrabajo::DHistorialOrdenTrabajo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DHistorialOrdenTrabajoBase)
{
    ui->setupUi( this );

    ui->DTEFechaHora->setDateTime( QDateTime::currentDateTime() );
    // ui->DTEFechaHora->setMaximumDate( );
}

DHistorialOrdenTrabajo::~DHistorialOrdenTrabajo()
{
    delete ui;
}

/*!
 * \brief DHistorialOrdenTrabajo::setearComoCancelacion
 * Setea el dialogo para cancelar la orden de trabajo
 */
void DHistorialOrdenTrabajo::setearComoCancelacion()
{
    ui->CBTipo->setearId( MTipoOperacionOrdenTrabajo::Cancelacion );
    ui->CBTipo->setEditable( false );
    ui->CBTipo->setEnabled( false );
    ui->CBTecnico->setVisible( false );
    ui->LTecnico->setVisible( false );
    setWindowTitle( "Cancelar Orden" );
}

/*!
 * \brief DHistorialOrdenTrabajo::setearComoFacturacion
 */
void DHistorialOrdenTrabajo::setearComoFacturacion()
{
    ui->CBTipo->setearId( MTipoOperacionOrdenTrabajo::Facturacion );
    ui->CBTipo->setEditable( false );
    ui->CBTipo->setEnabled( false );
    ui->CBTecnico->setVisible( false );
    ui->LTecnico->setVisible( false );
    setWindowTitle( "Facturar item" );
}

/*!
 * \brief DHistorialOrdenTrabajo::setearComoCierre
 */
void DHistorialOrdenTrabajo::setearComoCierre()
{
    ui->CBTipo->setearId( MTipoOperacionOrdenTrabajo::CierreOrden );
    ui->CBTipo->setEditable( false );
    ui->CBTipo->setEnabled( false );
    ui->CBTecnico->setVisible( false );
    ui->LTecnico->setVisible( false );
    setWindowTitle( "Cerrar orden" );
}

/*!
 * \brief DHistorialOrdenTrabajo::setearComoDevolverAlCliente
 */
void DHistorialOrdenTrabajo::setearComoDevolverAlCliente()
{
    ui->CBTipo->setearId( MTipoOperacionOrdenTrabajo::DevolucionCliente );
    ui->CBTipo->setEditable( false );
    ui->CBTipo->setEnabled( false );
    ui->CBTecnico->setVisible( false );
    ui->LTecnico->setVisible( false );
    setWindowTitle( "Devolver equipo al cliente" );
}