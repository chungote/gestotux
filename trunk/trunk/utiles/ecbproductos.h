#ifndef ECBPRODUCTOS_H
#define ECBPRODUCTOS_H

#include <QComboBox>

class ECBProductos : public QComboBox
{
    Q_OBJECT

public:
    ECBProductos( QWidget *parent = 0 );
    ECBProductos( ECBProductos *p, QWidget *parent = 0 );
    ~ECBProductos();
    QMap<int, QString> *_mod_prod;
    QMap<int, QString> *listadoProductos();

    QMap<int,QString> *listadoProductos();
    int idActual() const;

protected slots:
    void inicializar();

signals:
    void agregarProducto();

private slots:
    void enterApretado();

private:
<<<<<<< .mine
    QMap<QString, int> *_mapa_pos_codigo;
=======
    QMap<int, int> *_mapa_ids_pos;
    QMap<QString, int> *_mapa_codigo_pos;

>>>>>>> .r445
    QMap<int, QString> *_mapa_id_nombre;

    int _min;
};

#endif // ECBPRODUCTOS_H
