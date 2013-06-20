#include "formequipamiento.h"

#include "eactcerrar.h"
#include "eactguardar.h"

FormEquipamiento::FormEquipamiento( QWidget *parent ) :
  EVentana( parent )
{
  setupUi( this );
  this->setWindowTitle( "Equipamiento" );
  this->setWindowIcon( QIcon(":/imagenes/equipamiento.png" ) );

  /// @TODO Inicializar cb de marcas
  /// @TODO inicializar cb de clientes
  /// @TODO ver modelo de historial
  /// @TODO Hacer autocompletado de marcas

  addAction( new EActGuardar( this ) );
  addAction( new EActCerrar( this ) );
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
