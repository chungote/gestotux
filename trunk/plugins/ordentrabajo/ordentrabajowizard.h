#ifndef ORDENTRABAJOWIZARD_H
#define ORDENTRABAJOWIZARD_H

#include <QWizard>

class OrdenTrabajoWizard : public QWizard
{
    Q_OBJECT
public:

    enum {
        Pagina_Cliente,
        Pagina_ClienteNuevo,
        Pagina_Equipamiento,
        Pagina_EquipamientoExistente,
        Pagina_EquipamientoNuevo,
        Pagina_Final
    };

    OrdenTrabajoWizard( QWidget *parent = 0 );
    
};

#endif // ORDENTRABAJOWIZARD_H
