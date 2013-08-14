#ifndef FORMORDENTRABAJO_H
#define FORMORDENTRABAJO_H

#include "eventana.h"
#include "ui_formordentrabajobase.h"

using namespace Ui;

class FormOrdenTrabajo : public EVentana, public FormOrdenTrabajoBase
{
    Q_OBJECT
    
public:
    FormOrdenTrabajo( QWidget *parent = 0 );

protected slots:
    void cambioCliente( int id_cliente );
    
protected:
    void changeEvent( QEvent *e );
};

#endif // FORMORDENTRABAJO_H
