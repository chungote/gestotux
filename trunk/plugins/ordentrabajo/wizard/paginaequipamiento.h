#ifndef PAGINAEQUIPAMIENTO_H
#define PAGINAEQUIPAMIENTO_H

#include "ui_paginaequipamiento.h"

class PaginaEquipamiento : public QWizardPage, private Ui::PaginaEquipamiento
{
    Q_OBJECT
    
public:
    PaginaEquipamiento( QWidget *parent = 0 );
    int nextId();
    
};

#endif // PAGINAEQUIPAMIENTO_H
