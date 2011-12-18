#ifndef ECBCLIENTES_H
#define ECBCLIENTES_H

#include <QComboBox>

class ECBClientes : public QComboBox
{
    Q_OBJECT
public:
    ECBClientes( QWidget *parent = 0 );
    int idClienteActual();

private slots:
    void verificarExiste();
    void inicializar();

};

#endif // ECBCLIENTES_H
