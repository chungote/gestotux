#include "dhistorialordentrabajo.h"
#include "ui_dhistorialordentrabajo.h"

DHistorialOrdenTrabajo::DHistorialOrdenTrabajo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DHistorialOrdenTrabajo)
{
    ui->setupUi(this);
}

DHistorialOrdenTrabajo::~DHistorialOrdenTrabajo()
{
    delete ui;
}
