#ifndef VPLANCUOTAS_H
#define VPLANCUOTAS_H

#include "evlista.h"

/*!
 * \brief Visor de cuotas activas
 *
 * Muestra el listado de las cuotas activas y terminadas para todo el sistema
 * \author Esteban Zeller <tranfuga25s@gmail.com>
 */
class VPlanCuotas : public EVLista
{
    Q_OBJECT
public:
    VPlanCuotas( QWidget *parent = 0 );
    
private slots:
    void simular();

private:
    QAction *ActSimular;

};

#endif // VPLANCUOTAS_H
