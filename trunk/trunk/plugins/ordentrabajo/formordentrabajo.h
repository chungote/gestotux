#ifndef FORMORDENTRABAJO_H
#define FORMORDENTRABAJO_H

#include "ui_formordentrabajobase.h"

class FormOrdenTrabajo : public QWidget, private Ui::FormOrdenTrabajo
{
    Q_OBJECT
    
public:
    explicit FormOrdenTrabajo(QWidget *parent = 0);
    
protected:
    void changeEvent(QEvent *e);
};

#endif // FORMORDENTRABAJO_H
