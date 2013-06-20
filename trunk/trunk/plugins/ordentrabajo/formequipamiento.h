#ifndef FORMEQUIPAMIENTO_H
#define FORMEQUIPAMIENTO_H

#include "ui_formequipamientobase.h"
#include "eventana.h"

class FormEquipamiento : public EVentana, private Ui::FormEquipamientoBase
{
  Q_OBJECT
  
public:
  FormEquipamiento( QWidget *parent = 0 );
  
protected:
  void changeEvent(QEvent *e);
};

#endif // FORMEQUIPAMIENTO_H
