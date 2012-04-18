#ifndef FORMAGREGARPRODUCTO_H
#define FORMAGREGARPRODUCTO_H

#include "ui_formproductobase.h"
#include <QDialog>
#include <QDockWidget>

/*!
 * \brief Formulario para agregar un producto
 *
 * Clase que permite agregar un nuevo producto
 * \author Esteban Zeller
 */
class FormAgregarProducto : public QDialog, private Ui::FormProductoBase
{
    Q_OBJECT
    public:
        FormAgregarProducto( QWidget *parent = 0 );
        void setearPrecioCosto( const double precio );
        void setearNombre( const QString nombre );
        void setearStockInicial( const int cantidad );

    public slots:
        void accept();

    private slots:
        void cambioPrecioCosto( double costo );

    private:
        double _recargo;
        bool _categorias;
        bool _marcas;
        bool _descripcion;
        bool _stock;
        bool _modelo;

    signals:
        void agregarVentana( QWidget * );
        void agregarDockWidget( Qt::DockWidgetArea, QDockWidget * );
};

#endif // FORMAGREGARPRODUCTO_H