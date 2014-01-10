#ifndef FORMVENCIMIENTOGARANTIAS_H
#define FORMVENCIMIENTOGARANTIAS_H

#include "ui_formvencimientogarantias.h"
#include "mvgarantias.h"
class EActCerrar;

class FormVencimientoGarantias : public QWidget, private Ui::FormVencimientoGarantias
{
    Q_OBJECT
    
public:
    FormVencimientoGarantias( QWidget *parent = 0 );

protected slots:
    void cambioFecha( QDate fecha );
    
protected:
    void changeEvent(QEvent *e);

private:
    MVGarantias *mgarantias;
    EActCerrar *ActCerrar;

};

#endif // FORMVENCIMIENTOGARANTIAS_H
