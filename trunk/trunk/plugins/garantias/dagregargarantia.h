#ifndef DAGREGARGARANTIA_H
#define DAGREGARGARANTIA_H

#include "../ordentrabajo/ecbequipamiento.h"
#include "ui_dagregargarantia.h"
class MEquipamiento;
#include "NumeroComprobante.h"

class DAgregarGarantia : public QDialog, private Ui::DAgregarGarantia
{
    Q_OBJECT
    
public:
    DAgregarGarantia( QWidget *parent = 0 );
    void setearIdComprobantante( const int id_comprobante );
    void setearIdProducto( const int id_producto );
    void setearNombreProducto( const QString nombre_producto );
    void setearIdCliente( const int id_cliente );
    void setearIdComprobante( const int id_comprobante );

signals:
    void actualizarModelos();

public slots:
    void accept();
    
protected:
    void changeEvent(QEvent *e);

protected slots:
    void buscarEquipamientos( int id_cliente );
    void buscarFactura( int id_equipamiento );
    void actualizarFechaFinGarantia( QDate fecha );

private:
    int _id_comprobante;
    int _id_producto;
    int _id_cliente;

    QString _nombre_producto;

    NumeroComprobante _proxima_garantia;

    MEquipamiento *modelo_equipamiento;
};

#endif // DAGREGARGARANTIA_H
