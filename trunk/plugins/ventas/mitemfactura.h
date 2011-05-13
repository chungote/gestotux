#ifndef MITEMFACTURA_H
#define MITEMFACTURA_H

#include <QSqlRelationalTableModel>

class MItemFactura : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit MItemFactura(QObject *parent = 0);

private:
    void inicializar();
    void relacionar();

};

#endif // MITEMFACTURA_H
