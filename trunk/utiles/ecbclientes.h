#ifndef ECBCLIENTES_H
#define ECBCLIENTES_H

#include <QComboBox>
#include <QList>

class ECBClientes : public QComboBox
{
    Q_OBJECT
public:
    ECBClientes( QWidget *parent = 0 );
    ~ECBClientes();
    void setearFiltro( const QString f );
    int idClienteActual();

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
