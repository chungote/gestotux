#include "formequipamiento.h"

FormEquipamiento::FormEquipamiento(QWidget *parent) :
  QWidget(parent)
{
  setupUi(this);
}

void FormEquipamiento::changeEvent(QEvent *e)
{
  QWidget::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      retranslateUi(this);
      break;
    default:
      break;
    }
}
