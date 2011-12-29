#ifndef FORMLISTACOMPRA_H
#define FORMLISTACOMPRA_H

#include "evlista.h"
#include <QSqlQueryModel>

class MListaCompra : public QSqlQueryModel {
    Q_OBJECT

    public:
        MListaCompra( QObject *parent );
        void setearIdCompra( const int id_compra );
        QVariant data(const QModelIndex &item, int role) const;
};

class VListaCompra : public EVLista
{
    Q_OBJECT

public:
    explicit VListaCompra(QWidget *parent = 0);
    void setearIdCompra( const int id_compra );

private:
    MListaCompra *cola;
};



#endif // FORMLISTACOMPRA_H
