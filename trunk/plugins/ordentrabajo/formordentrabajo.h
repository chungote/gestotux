#ifndef FORMORDENTRABAJO_H
#define FORMORDENTRABAJO_H

#include "eventana.h"
#include "ui_formordentrabajobase.h"


class FormOrdenTrabajo : public EVentana, private Ui::FormOrdenTrabajo
{
    Q_OBJECT
    
public:
    FormOrdenTrabajo( QWidget *parent = 0 );
    
protected:
    void changeEvent( QEvent *e );
};

#endif // FORMORDENTRABAJO_H
