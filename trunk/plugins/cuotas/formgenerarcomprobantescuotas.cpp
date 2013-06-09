#include "formgenerarcomprobantescuotas.h"

#include "eactcerrar.h"
#include "mpagos.h"
#include "mitemplancuota.h"

#include <QSqlDatabase>
#include <QMessageBox>

FormGenerarComprobantesCuotas::FormGenerarComprobantesCuotas( QWidget *parent ) :
    EVentana( parent )
{
    setupUi(this);
    this->setWindowTitle( "Generar comprobantes de cuotas" );
    //this->setWindowIcon( QIcon( ":/imagenes/nada.png" ) );

    this->GBProgreso->setVisible( false );

    // Inicializo el modelo de las cuotas
    modelo = new MGenerarCuotas( this );

    // Conecto los totales y demás
    connect( modelo, SIGNAL( cambioTotal( double ) ), DSBTotal, SLOT( setValue( double ) ) );
    connect( modelo, SIGNAL( cambioCantidad( int ) ), LCDNCantidad, SLOT( display( int ) ) );
    connect( modelo, SIGNAL( comprobantes( QPair<NumeroComprobante *, NumeroComprobante *> ) ), this, SLOT( cambioComprobantes( QPair<NumeroComprobante *, NumeroComprobante *> ) ) );

    TVVista->setModel( modelo );

    ActCalcular = new QAction( this );
    ActCalcular->setText( "Calcular" );
    connect( ActCalcular, SIGNAL( triggered() ), this, SLOT( calcularCuotas() ) );

    addAction( ActCalcular );
    addAction( new EActCerrar( this ) );
}

void FormGenerarComprobantesCuotas::changeEvent(QEvent *e)
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

/**
 * @brief FormGenerarComprobantesCuotas::cambioComprobantes
 * Coloca el numero de comprobantes en la etiqueta informativa correspondiente
 * @param nums Par de Numeros de Comprobante a generar
 */
void FormGenerarComprobantesCuotas::cambioComprobantes( QPair<NumeroComprobante *,NumeroComprobante *> nums)
{
  LComprobantes->setText( QString( "Emitiendo comprobantes número: %1 al %2" ).arg( nums.first->aCadena() ).arg( nums.second->aCadena() ) );
}

/**
 * @brief FormGenerarComprobantesCuotas::calcularCuotas
 * Llama al sistema para que vea de generar las los datos para modelo
 */
void FormGenerarComprobantesCuotas::calcularCuotas()
{
  modelo->calcularComprobantes();
  TVVista->update();
}

void FormGenerarComprobantesCuotas::emitirComprobantes()
{
  // Genero la transaccion
  QSqlDatabase::database( QSqlDatabase::defaultConnection, true ).transaction();

  // Deshabilito las acciones para que no pueda tocar nada mientras trabajo
  ActEmitir->setEnabled( false );
  ActCalcular->setEnabled( false );
  TVVista->setEnabled( false );

  // Muestro la barra de progreso
  GBProgreso->setVisible( true );

  // Coloco el rango ( busqueda de info = 1, emision = 2, guardado de datos = 3 )
  PgBEstado->setRange( 0, modelo->rowCount()*3 );

  MPagos *m = new MPagos( this, false );
  // Recorro el modelo y genero los recibos
  while( modelo->rowCount() > 0 ) {
      // Busco los datos del modelo
      LProgreso->setText( QString( "Buscando información para el plan de cuota %1" )
                          .arg( modelo->data( modelo->index( 0, 1 ), Qt::DisplayRole ).toString() ) );

      int id_cliente = modelo->data( modelo->index( 0, 2 ), Qt::EditRole ).toInt();
      double monto = modelo->data( modelo->index( 0, 4 ), Qt::EditRole ).toDouble();
      QString contenido = QString( "Pago de cuota %1 del plan de cuotas #%2")
              .arg( modelo->data( modelo->index( 0, 3 ), Qt::EditRole ).toString() )
              .arg( modelo->data( modelo->index( 0, 1 ), Qt::EditRole ).toInt() );
      QDate fecha = QDate::currentDate();

      PgBEstado->setValue( PgBEstado->value() + 1 );
      LProgreso->setText( QString( "Emitiendo recibo Nº %1" ).arg( modelo->data( modelo->index( 0, 5 ), Qt::EditRole ).toString() ) );

      // Emito el recibo con los datos pero lo pongo como "A Pagar luego" o como pagado = false
      int id_recibo = m->agregarRecibo( id_cliente, fecha, contenido, monto, true, false );
      if ( id_recibo == -1 ) {
          QMessageBox::information( this, "Error", "El recibo No ha sido agregado correctamente" );
          QSqlDatabase::database( QSqlDatabase::defaultConnection, true ).rollback();
      }

      PgBEstado->setValue( PgBEstado->value() + 1 );
      LProgreso->setText( "Recibo generado... Guardando relacion...." );

      // Guardo el numero de recibo en el registro de la cuota
      int id_item_plan_cuota = modelo->data( modelo->index( 0, 0 ), Qt::EditRole ).toInt();
      if( !MItemPlanCuota::setearItemCuotaPagado( id_item_plan_cuota, id_recibo ) ) {
          QMessageBox::information( this, "Error", "No se pudo asociar el recibo con el item del plan de cuota" );
          QSqlDatabase::database( QSqlDatabase::defaultConnection, true ).rollback();
      }
      PgBEstado->setValue( PgBEstado->value() + 1 );

      modelo->removeRow( 0 );
  }
  QSqlDatabase::database( QSqlDatabase::defaultConnection, true ).rollback();

}
