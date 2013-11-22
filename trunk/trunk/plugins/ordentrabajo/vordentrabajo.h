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

protected slots:
    void ver();
    void agregar( bool autoeliminarid );
    void modificar();
    void eliminar();
    void aPdf();
    void imprimir();
    void menuContextual( const QModelIndex &indice, QMenu *menu );
    
private:
    QAction *ActVer;
};

#endif // VORDENTRABAJO_H
