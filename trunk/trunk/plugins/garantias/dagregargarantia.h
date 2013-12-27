#ifndef DAGREGARGARANTIA_H
#define DAGREGARGARANTIA_H

#include "../ordentrabajo/ecbequipamiento.h"
#include "ui_dagregargarantia.h"
class MEquipamiento;

class DAgregarGarantia : public QDialog, private Ui::DAgregarGarantia
{
    Q_OBJECT
    
public:
    DAgregarGarantia( QWidget *parent = 0 );
    void setearIdComprontante( const int id_comprobante );
    void setearIdProducto( const int id_producto );
    void setearNombreProducto( const QString nombre_producto );
    void setearIdCliente( const int id_cliente );
    void setearIdComprobante( const int id_comprobante );

public slots:
    void accept();
    
protected:
    void changeEvent(QEvent *e);

protected slots:
    void buscarEquipamientos( int id_cliente );
    void buscarFactura( int id_equipamiento );

private:
    int _id_comprobante;
    int _id_producto;
    int _id_cliente;

    QString _nombre_producto;

    MEquipamiento *modelo;
};

#endif // DAGREGARGARANTIA_H
