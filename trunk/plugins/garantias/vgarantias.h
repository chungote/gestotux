#ifndef VGARANTIAS_H
#define VGARANTIAS_H

#include "evlista.h"
#include "mgarantias.h"

class VGarantias : public EVLista
{
    Q_OBJECT
public:
    VGarantias( QWidget *parent = 0 );

protected slots:
    void agregar( bool autoeliminarid );
    void imprimir();
    void aPdf();
    void eliminar();
    void darBaja();

private:
    MGarantias *modelo;
    QAction *ActDarBaja;
    
};

#endif // VGARANTIAS_H
