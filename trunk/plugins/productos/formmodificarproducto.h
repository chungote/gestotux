#ifndef FORMMODIFICARPRODUCTO_H
#define FORMMODIFICARPRODUCTO_H

#include "ui_formproductobase.h"
#include <QDialog>
#include <QDockWidget>
#include <QDataWidgetMapper>
#include "mproductos.h"

class FormModificarProducto : public QDialog, private Ui::FormProductoBase
{
    Q_OBJECT
public:
    explicit FormModificarProducto( MProductos *mod, QWidget *parent = 0);
    void setearProducto( const int id );

signals:
    void agregarVentana( QWidget * );
    void agregarDockWidget( Qt::DockWidgetArea, QDockWidget * );

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
    MProductos *modelo;
    QDataWidgetMapper *mapa;

};

#endif // FORMMODIFICARPRODUCTO_H
