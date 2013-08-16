#ifndef VRECIBOSIMPAGOS_H
#define VRECIBOSIMPAGOS_H

#include "evlista.h"
#include "mrecibosimpagos.h"

class VRecibosImpagos : public EVLista
{
    Q_OBJECT
public:
    VRecibosImpagos( QWidget *parent = 0 );

private:
    MRecibosImpagos *mp;
    
};

#endif // VRECIBOSIMPAGOS_H
