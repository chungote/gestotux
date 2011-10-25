#ifndef ECBPRODUCTOS_H
#define ECBPRODUCTOS_H

#include <QComboBox>

class ECBProductos : public QComboBox
{
    Q_OBJECT

public:
    ECBProductos( QWidget *parent = 0 );
    ~ECBProductos();
    QMap<int, QString> *_mod_prod;
    QMap<int, QString> *listadoProductos();

protected slots:
    void inicializar();

signals:
    void agregarProducto();

private slots:
    void enterApretado();

private:
    QMap<int, int> *_mapa_ids_pos;
    QMap<QString, int> *_mapa_codigo_pos;

};

#endif // ECBPRODUCTOS_H
