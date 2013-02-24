#ifndef VTIPOORDENTRABAJO_H
#define VTIPOORDENTRABAJO_H

#include "mtipoordentrabajo.h"
#include "evlista.h"

/**
 * \brief Listado de tipos de orden de trabajos
 *
 * Vista de la lista de tipos de orden de trabajo
 * @author Esteban Zeller <juiraze@yahoo.com.ar>
 */
class VTipoOperacionOrdenTrabajo : public EVLista
{
    Q_OBJECT
public:
    VTipoOperacionOrdenTrabajo( QWidget *parent = 0 );

public slots:
    void agregar(bool autoeliminarid);
    void modificar();
    void eliminar();

private:
    MTipoOrdenTrabajo *modelo;

};

#endif // VTIPOORDENTRABAJO_H
