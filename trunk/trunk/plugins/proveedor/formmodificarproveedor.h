#ifndef FORMMODIFICARPROVEEDOR_H
#define FORMMODIFICARPROVEEDOR_H

#include "eventana.h"
#include "ui_FormProveedorBase.h"
#include "mproveedor.h"
#include <QDataWidgetMapper>

class FormModificarProveedor : public EVentana, private Ui::FormProveedorBase
{
    Q_OBJECT
public:
    explicit FormModificarProveedor( MProveedor *m, QWidget *parent = 0);

public slots:
    void guardar();

private:
    QDataWidgetMapper *mapa;
    MProveedor *modelo;

};

#endif // FORMMODIFICARPROVEEDOR_H
