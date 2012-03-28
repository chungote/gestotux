#ifndef FORMMODIFICARPRESUPUESTO_H
#define FORMMODIFICARPRESUPUESTO_H

#include "eventana.h"
#include "ui_FormPresupuestoBase.h"
class QSqlQueryModel;
class MProductosTotales;

class FormModificarPresupuesto : public EVentana, public Ui::FormPresupuestoBase
{
    Q_OBJECT
public:
    explicit FormModificarPresupuesto(QWidget *parent = 0);
    void setearIdPresupuesto( int id_presupuesto );

protected slots:
    void cancelar();
    void guardar( bool cerrar );
    void guardar();
    void agregarProducto();
    void eliminarProducto();
    void borrarTodoProducto();
    void cambioCliente( int id_combo );

private:
    int _id_presupuesto;
   /*!
    * Modelo utilizado por el combo box de clientes para hacer su selección
    */
    QSqlQueryModel *modeloClientes;
   /*!
    * Modelo para mostrar la lista de productos e items
    */
    MProductosTotales *m;

};

#endif // FORMMODIFICARPRESUPUESTO_H
