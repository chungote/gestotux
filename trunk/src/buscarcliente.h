#ifndef BUSCARCLIENTE_H
#define BUSCARCLIENTE_H

#include "mclientes.h"
#include "ui_buscarclientebase.h"

class BuscarCliente : public QDockWidget, private Ui::BuscarCliente
{
    Q_OBJECT

public:
    explicit BuscarCliente( QWidget *parent = 0, MClientes *m = 0 );

protected:
    void changeEvent(QEvent *e);

private slots:
    void cambioTipo( int );
    void cambioTexto();
    void borrar();

private:
    MClientes *modelo;
    QString _texto;
    int _tipo;
    void filtrar();

};

#endif // BUSCARCLIENTE_H
