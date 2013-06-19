#ifndef FORMEQUIPAMIENTO_H
#define FORMEQUIPAMIENTO_H

#include "ui_formequipamientobase.h"

class FormEquipamiento : public QWidget, private Ui::FormEquipamientoBase
{
  Q_OBJECT
  
public:
  explicit FormEquipamiento(QWidget *parent = 0);
  
protected:
  void changeEvent(QEvent *e);
};

#endif // FORMEQUIPAMIENTO_H
