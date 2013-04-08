#include "dremarcadormasivo.h"

#include <QMessageBox>

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
  connect( CkBDeshabilitados, SIGNAL( toggled( bool ) ), this, SLOT( cambioDeshabilitados( bool ) ) );
  connect( CkBSinStock, SIGNAL( toggled( bool ) ), this, SLOT( cambioSinStock( bool ) ) );

  TVProductos->setModel( modelo );
  TVProductos->hideColumn( 0 );

  connect( PBAgregar, SIGNAL( clicked() ), this, SLOT( agregarProducto() ) );
  connect( PBEliminar, SIGNAL( clicked() ), this, SLOT( eliminarProducto() ) );

  PBAgregar->setIcon( QIcon( ":/imagenes/add.png" ) );
  PBEliminar->setIcon( QIcon( ":/imagenes/eliminar.png" ) );
  PBEliminar->setText( "Eliminar producto" );

  // Pongo como predeterminado el porcentaje
  RBPorcentaje->setChecked( true );

  CBProductos->setearTabla( "producto" );
  CBProductos->setearCampoId( "id" );
  CBProductos->setearCampoTexto( "nombre" );
  CBProductos->setearCampoOrden( "nombre" );

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
  modelo->agregarProducto( CBProductos->idActual() );
}

void DRemarcadorMasivo::eliminarProducto()
{
  if( TVProductos->selectionModel()->selectedRows().size() <= 0 ) {
      QMessageBox::information( this, "Error", "Por favor, seleccione al menos un producto para sacar del listado" );
      return;
  }
  foreach( QModelIndex idx, TVProductos->selectionModel()->selectedRows() ) {
      modelo->eliminarProducto( idx );
  }
}

void DRemarcadorMasivo::accept()
{
    qWarning( "No implementado" );
}

void DRemarcadorMasivo::cambioSinStock( bool estado )
{
    modelo->cambioSinStock( estado );
    recalcularFiltro();
}

void DRemarcadorMasivo::cambioDeshabilitados( bool estado )
{
    modelo->cambioDeshabilitados( estado );
    recalcularFiltro();
}

void DRemarcadorMasivo::recalcularFiltro() {
    QString filtro = " WHERE ";
    if( CkBDeshabilitados->isChecked() ) {
        filtro.append( " habilitado = 1" );
    } else {
        filtro.append( " habilitado = 0" );
    }
    if( !CkBSinStock->isChecked() ) {
        filtro.append( " AND stock > 0" );
    }
    CBProductos->setearFiltro( filtro, true );
}
