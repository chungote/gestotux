#ifndef VEQUIPAMIENTO_H
#define VEQUIPAMIENTO_H

#include "evlista.h"
/**
 * @brief The VEquipamiento class
 * Esta clase sirve para ver cuales de los equipamientos actuales está dado de alto en el sistema
 * @author Esteban Zeller
 */
class VEquipamiento : public EVLista
{
    Q_OBJECT
public:
    VEquipamiento( QWidget *parent = 0 );
};

#endif // VEQUIPAMIENTO_H
