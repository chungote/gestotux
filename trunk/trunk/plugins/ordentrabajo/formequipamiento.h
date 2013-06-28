#ifndef FORMEQUIPAMIENTO_H
#define FORMEQUIPAMIENTO_H

#include "ui_formequipamientobase.h"
#include "eventana.h"
#include "mequipamiento.h"

class FormEquipamiento : public EVentana, private Ui::FormEquipamientoBase
{
  Q_OBJECT
  
public:
  FormEquipamiento( QWidget *parent = 0 );
  void setearModeloEquipamiento( MEquipamiento *m );
  void setearAgregar( bool estado );
  void setearEditar( bool estado ) { setearAgregar( !estado ); }

public slots:
  void guardar();
  
protected:
  void changeEvent(QEvent *e);

private:
  int _id;
  bool _editar;

  MEquipamiento *_mequipamiento;

};

#endif // FORMEQUIPAMIENTO_H
