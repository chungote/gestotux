#ifndef ECBPRODUCTOS_H
#define ECBPRODUCTOS_H

#include <QComboBox>

/*!
 * \brief Combobox de productos con autodeteccion de codigo.
 *
 * Esta clase facilita la selección de los productos a traves de un combobox con las siguientes características:
 * - Permite una carga diferida para que cuando existan muchos productos, no se bloquee el constructor de la clase padre.
 * - Permite ingresar el codigo del producto y automaticamente seleccionará el producto que corresponda.
 * - Permite busqueda y filtrado de los productos ingresando texto en el combobox. \n
 * La clase le permitirá además obtener el Identificador del producto mediante el método idActual(). \n
 * La señal agregarProducto() y la fución listadoProductos() son utilizadas cuando seleccionó un producto y se lo desea agregar a algun listado. \n
 * El QMap que devuelve la función listadoProducots() contiene el identificador de la base de datos y el nombre del producto como fue mostrado en el combobox. \n
 * El combobox permite ingresar nuevos elementos que no estén declarados en la lista de productos, y les asignará un valor de indice < 0 sucesivamente. De esta forma cualquier texto puede ser ingresado en un listado de productos sin necesidad de declararlo primero en el listado de productos. \n
 * \author Esteban Zeller
 */
class ECBProductos : public QComboBox
{
    Q_OBJECT

public:
    ECBProductos( QWidget *parent = 0 );
    ~ECBProductos();
    QMap<int, QString> *listadoProductos();
    void setearListado( QMap<int, QString> *lista );
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