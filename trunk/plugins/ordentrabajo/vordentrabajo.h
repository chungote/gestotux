#ifndef VORDENTRABAJO_H
#define VORDENTRABAJO_H

#include "evlista.h"

class VOrdenTrabajo : public EVLista
{
    Q_OBJECT
public:
    VOrdenTrabajo(QWidget *parent = 0);
    
signals:
    void agregarVentana( QWidget * );

public slots:
    
};

#endif // VORDENTRABAJO_H
