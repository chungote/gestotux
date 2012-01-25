#ifndef ECBCLIENTES_H
#define ECBCLIENTES_H

#include <QComboBox>
#include <QList>

/*!
 * \brief Combobox con listado de clientes
 *
 * Esta clase le permite obtener un combo box con el listado de clientes segun el filtro que poseea activo y le permite mappear id_cliente <-> combo directamente. \n
 * Al cargarse la clase lanza una señal que permite la carga de datos en diferido. Mientras el sistema este cargando los datos, no se podrá realizar acciones con el combobox y aparecera el texto de "Cargando datos...". \n
 * Una vez finalizada la carga se habilitará para su uso normal. \n
 * Para obtener el ID de base de datos del cliente que este seleccionado se utiliza el metodo \ref idClienteActual() , y se puede colocar como seleccionado un cliente mediante el método \ref setearId(). \n
 * La carga de los datos se hará respetando las clausulas de el filtro que exista. De manera predeterminada el filtro esta vacío, pero puede ser cambiado utilizando el método \ref setearFiltro(). \n
 * Cada vez que se cambie el filtro se disparará una recarga de los datos que contiene el combobox.
 * \author Esteban Zeller
 */
class ECBClientes : public QComboBox
{
    Q_OBJECT
public:
    ECBClientes( QWidget *parent = 0 );
    ~ECBClientes();
    void setearFiltro( const QString f );
    int idClienteActual();
    void setearId( const int id_cliente );

private slots:
    void verificarExiste();
    void inicializar();

private:
   /*!
    * Guarda el ID de cliente segun la posicion del cb
    */
    QList<int> *ids;
   /*!
    * Filtro para la consulta de clientes
    */
    QString filtro;

};

#endif // ECBCLIENTES_H
