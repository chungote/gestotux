#ifndef VGARANTIAS_H
#define VGARANTIAS_H

#include "evlista.h"
#include "mgarantias.h"

class VGarantias : public EVLista
{
    Q_OBJECT
public:
    explicit VGarantias(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    MGarantias *modelo;
    
};

#endif // VGARANTIAS_H
