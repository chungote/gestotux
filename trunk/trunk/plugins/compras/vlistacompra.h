#ifndef FORMLISTACOMPRA_H
#define FORMLISTACOMPRA_H

#include "evlista.h"

class VListaCompra : public EVLista
{
    Q_OBJECT

public:
    explicit VListaCompra(QWidget *parent = 0);
    void setearIdCompra( const int id_compra );
};

#endif // FORMLISTACOMPRA_H
