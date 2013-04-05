#include "dremarcadormasivo.h"

DRemarcadorMasivo::DRemarcadorMasivo(QWidget *parent) :
  QDialog(parent)
{
  setupUi(this);

  setWindowTitle( "Remarcador masivo" );
  setWindowIcon( QIcon( ":/imagenes/producto.png" ) );

  connect( RBFijo      , SIGNAL( toggled( bool ) ), this, SLOT( cambioAMontoFijo ( bool ) ) );
  connect( RBPorcentaje, SIGNAL( toggled( bool ) ), this, SLOT( cambioAPorcentaje( bool ) ) );

  modelo = new MTempProductoRemarcar( this );

  connect( DSBValor, SIGNAL( valueChanged( double ) ), modelo, SLOT( cambioValor( double ) ) );
  connect( CkBDeshabilitados, SIGNAL( toggled( bool ) ), modelo, SLOT( cambioDeshabilitados( bool ) ) );
  connect( CkBSinStock, SIGNAL( toggled( bool ) ), modelo, SLOT( cambioSinStock( bool ) ) );

  this->TVProductos->setModel( modelo );
  this->TVProductos->hideColumn( 0 );
}

void DRemarcadorMasivo::changeEvent(QEvent *e)
{
  QDialog::changeEvent(e);
  switch (e->type()) {
    case QEvent::LanguageChange:
      retranslateUi(this);
      break;
    default:
      break;
    }
}

void DRemarcadorMasivo::cambioAPorcentaje()
{
  DSBValor->setPrefix( "" );
  DSBValor->setSuffix( " %" );
  DSBValor->setValue( 0.0 );
  modelo->setearPorcentaje( true );
}

void DRemarcadorMasivo::cambioAMontoFijo()
{
  DSBValor->setPrefix( "$ " );
  DSBValor->setSuffix( "" );
  DSBValor->setValue( 0.0 );
  modelo->setearValorFijo( true );
}

void DRemarcadorMasivo::agregarProducto()
{
}

void DRemarcadorMasivo::eliminarProducto()
{
}

void DRemarcadorMasivo::accept()
{
}

