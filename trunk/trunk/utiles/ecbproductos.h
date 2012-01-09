#ifndef ECBPRODUCTOS_H
#define ECBPRODUCTOS_H

#include <QComboBox>

class ECBProductos : public QComboBox
{
    Q_OBJECT

public:
    ECBProductos( QWidget *parent = 0 );
    ~ECBProductos();
    QMap<int, QString> *listadoProductos();
    int idActual() const;
    void verificarExiste();

protected slots:
    void inicializar();

signals:
    void agregarProducto();

private slots:
    void enterApretado();

private:
    QMap<QString, int> *_mapa_pos_codigo;
    QMap<int, QString> *_mapa_id_nombre;
    QMap<int, int> *_mapa_pos_ids;

    int _min;
};

#endif // ECBPRODUCTOS_H
