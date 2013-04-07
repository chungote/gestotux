#include "dremarcadormasivo.h"

DRemarcadorMasivo::DRemarcadorMasivo(QWidget *parent) :
QDialog( parent )
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

  TVProductos->setModel( modelo );
  TVProductos->hideColumn( 0 );

  connect( PBAgregar, SIGNAL( clicked() ), this, SLOT( agregarProducto() ) );
  connect( PBEliminar, SIGNAL( clicked() ), this, SLOT( eliminarProducto() ) );

  PBAgregar->setIcon( QIcon( ":/imagenes/add.png" ) );
  PBEliminar->setIcon( QIcon( ":/imagenes/eliminar.png" ) );
  PBEliminar->setText( "Eliminar producto" );

  // Pongo como predeterminado el porcentaje
  RBPorcentaje->setChecked( true );
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

void DRemarcadorMasivo::cambioAPorcentaje( bool estado )
{
    if( !estado )
        return;

    DSBValor->setPrefix( "" );
    DSBValor->setSuffix( " %" );
    DSBValor->setValue( 0.0 );
    modelo->setearPorcentaje( true );
}

void DRemarcadorMasivo::cambioAMontoFijo( bool estado )
{
    if( !estado )
        return;

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
    qWarning( "No implementado" );
}
