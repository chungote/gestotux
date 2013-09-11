#include "dhistorialordentrabajo.h"
#include "ui_dhistorialordentrabajo.h"

#include "mtipooperacionordentrabajo.h"

DHistorialOrdenTrabajo::DHistorialOrdenTrabajo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DHistorialOrdenTrabajoBase)
{
    ui->setupUi( this );
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

}
