#ifndef DPAGOCUOTA_H
#define DPAGOCUOTA_H

#include "ui_DPagoCuotaBase.h"
#include "mvplancuota.h"

class DPagoCuota : public QDialog, private Ui::DPagoCuota
{
    Q_OBJECT
    
public:
    DPagoCuota( QWidget *parent = 0 );
    void setearPlanCuota( const int id_plan_cuota );
    void setearModelo( MVPlanCuota *m );
    
protected:
    void changeEvent(QEvent *e);

private:
    int _id_plan_cuota;
    MVPlanCuota *_model;

    void cargarDatos();
};

#endif // DPAGOCUOTA_H
