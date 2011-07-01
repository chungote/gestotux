#ifndef FORMAGREGARPRODUCTO_H
#define FORMAGREGARPRODUCTO_H

#include "ui_formproductobase.h"
#include <QDialog>

class FormAgregarProducto : public QDialog, private Ui::FormProductoBase
{
    Q_OBJECT
    public:
        FormAgregarProducto( QWidget *parent = 0 );

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
};

#endif // FORMAGREGARPRODUCTO_H
