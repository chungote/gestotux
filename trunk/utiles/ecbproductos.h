#ifndef ECBPRODUCTOS_H
#define ECBPRODUCTOS_H

#include <QComboBox>

class ECBProductos : public QComboBox
{
    Q_OBJECT

public:
    ECBProductos( QWidget *parent = 0 );
    ~ECBProductos();

protected slots:
    void inicializar();

signals:
    void agregarProducto();

private slots:
    void enterApretado();

private:
    QMap<int, int> *_mapa_pos_ids;
    QMap<QString, int> *_mapa_pos_codigo;
};

#endif // ECBPRODUCTOS_H
