#ifndef PAGINACLIENTE_H
#define PAGINACLIENTE_H

#include <QWizardPage>
#include <QLabel>

#include "ecbclientes.h"

class PaginaCliente : public QWizardPage
{
    Q_OBJECT
public:
    PaginaCliente( QWidget *parent = 0 );

    int nextId() const;
    QString clienteIngresado() { return CBClientes->currentText(); }

private:
    QLabel *arriba;
    ECBClientes *CBClientes;

};

#endif // PAGINACLIENTE_H
