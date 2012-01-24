#ifndef VLISTAPERIODOS_H
#define VLISTAPERIODOS_H

#include "evlista.h"
class MPeriodoServicio;

class VListaPeriodos : public EVLista
{
    Q_OBJECT
public:
    explicit VListaPeriodos( int id_servicio, QWidget *parent = 0 );
    
private:
    MPeriodoServicio *modelo;
    
};

#endif // VLISTAPERIODOS_H
