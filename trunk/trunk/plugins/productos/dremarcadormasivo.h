#ifndef DREMARCADORMASIVO_H
#define DREMARCADORMASIVO_H

#include "ui_dremarcadormasivobase.h"
#include "mtempproductoremarcar.h"

class DRemarcadorMasivo : public QDialog, private Ui::DRemarcadorMasivo
{
  Q_OBJECT
  
public:
  DRemarcadorMasivo( QWidget *parent = 0 );
  
protected:
  void changeEvent(QEvent *e);

protected slots:
  void cambioAPorcentaje( bool );
  void cambioAMontoFijo( bool );
  void agregarProducto();
  void eliminarProducto();
  void accept();

private:
  MTempProductoRemarcar *modelo;

};

#endif // DREMARCADORMASIVO_H
