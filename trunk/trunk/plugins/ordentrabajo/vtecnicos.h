#ifndef VTECNICOS_H
#define VTECNICOS_H

#include "evlista.h"

/**
 * \brief Listado de tecnicos activos en el sistema
 *
 * Vista de la lista de tecnicos habilitados
 * @author Esteban Zeller <juiraze@yahoo.com.ar>
 */
class VTecnicos : public EVLista
{
    Q_OBJECT
public:
    VTecnicos( QWidget *parent = 0 );

public slots:
    void agregar(bool autoeliminarid);
    void modificar();
    void eliminar();
    void habilitar();
    void deshabilitar();
    void cambiarVerDeshabilitado( bool estado);

private:
    QAction *ActHabilitar;
    QAction *ActDeshabilitar;
    QAction *ActMostrarDeshabilitados;

};

#endif // VTECNICOS_H
