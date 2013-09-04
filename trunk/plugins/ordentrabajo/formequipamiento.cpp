#include "formequipamiento.h"

#include "eactcerrar.h"
#include "eactguardar.h"
#include "mequipamiento.h"

#include <QDebug>
#include <QMessageBox>

FormEquipamiento::FormEquipamiento( QWidget *parent ) :
  EVentana( parent )
{
  setupUi( this );
  this->setWindowTitle( "Equipamiento" );
  this->setWindowIcon( QIcon(":/imagenes/equipamiento.png" ) );

  _id = -1;
  _editar = false;
  _mequipamiento = 0;

  CBMarca->setEditable( true );

  addAction( new EActGuardar( this ) );
  addAction( new EActCerrar( this ) );
}

/*!
 * \brief FormEquipamiento::setearModeloEquipamiento
 * Setea el modelo de equipamiento para su uso.
 * \param m Puntero al modelo a utilizar
 */
void FormEquipamiento::setearModeloEquipamiento( MEquipamiento *m )
{
  if( m != 0 ) { _mequipamiento = m; }
}

/*!
 * \brief FormEquipamiento::setearAgregar
 * Setea el estado del formulario de edición a agregado de nuevo equipamiento
 * \param estado si desea colocarse en agregar o no
 */
void FormEquipamiento::setearAgregar( bool estado )
{
  if( estado ) {
    GBHistorial->setVisible( false );
    _editar = false;
    this->setWindowTitle( "Agregar Equipamiento" );
  } else {
    GBHistorial->setVisible( true );
    _editar = true;
    this->setWindowTitle( "Editar Equipamiento" );
    /// @TODO cargar datos del equipamiento
  }
}

void FormEquipamiento::setearIndice( QModelIndex indice )
{
    // Extraigo el dato del ID de equipameinto
    int temp = indice.model()->data( indice.model()->index( indice.row(), 0 ), Qt::EditRole ).toInt();
    if( temp > 0 ) {
        this->_id = temp;
        this->cargarDatos();
    } else {
        qDebug() << "Identificador de ID de equipamiento incorrecto";
    }
}

/*!
 * \brief FormEquipamiento::guardar
 * Slot llamado al presionar el botón de guardar
 */
void FormEquipamiento::guardar()
{
    QMessageBox::information( this, "Error", "No implementado" );
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

/*!
 * \brief FormEquipamiento::cargarDatos
 * Carga los datos del equipamiento seteado en this->_id
 */
void FormEquipamiento::cargarDatos()
{
    if( this->_id <= 0 ) {
        return;
    }
}
