#ifndef FORMAGREGARPROVEEDOR_H
#define FORMAGREGARPROVEEDOR_H

#include "eventana.h"
#include "mproveedor.h"
#include "eactguardar.h"
#include "eactcerrar.h"
#include "mproveedor.h"
#include "ui_FormProveedorBase.h"
#include <QDataWidgetMapper>

class FormAgregarProveedor : public EVentana, private Ui::FormProveedorBase
{
    Q_OBJECT

public:
    FormAgregarProveedor( MProveedor *m, QWidget *parent = 0 );

public slots:
    void guardar();

protected:
    void changeEvent( QEvent *e );

private:
    MProveedor *modelo;
    QDataWidgetMapper *mapa;
};

#endif // FORMAGREGARPROVEEDOR_H
