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
  /// @TODO ver modelo de historial
  /// @TODO Hacer autocompletado de marcas

  _id = -1;
  _editar = false;
  _mequipamiento = 0;

  addAction( new EActGuardar( this ) );
  addAction( new EActCerrar( this ) );
}

/*!
 * \brief FormEquipamiento::setearModeloEquipamiento
 * Setea el modelo de equipamiento para su uso.
 * \param m Puntero al modelo a utilizar
 */
void FormEquipamiento::setearModeloEquipamiento(MEquipamiento *m)
{
  if( m != 0 ) { _mequipamiento = m; }
}

/*!
 * \brief FormEquipamiento::guardar
 * Slot llamado al presionar el botón de guardar
 */
void FormEquipamiento::guardar()
{

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
