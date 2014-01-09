#include "vgarantias.h"

#include <QTableView>
#include <QMessageBox>
#include <QInputDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrinterInfo>

#include "egarantiasvg.h"
#include "mvgarantiassvg.h"

VGarantias::VGarantias(QWidget *parent) :
    EVLista(parent)
{

    setObjectName( "visor-garantias" );
    setWindowTitle( QString::fromUtf8( "Garantías activas" ) );
    setWindowIcon( QIcon( ":/imagenes/garantia.png" ) );

    modelo = new MGarantias( this );

    vista->setModel( modelo );
    vista->hideColumn( 0 );
    vista->hideColumn( modelo->fieldIndex( "fecha_baja" ) );
    vista->hideColumn( modelo->fieldIndex( "razon_baja" ) );
    vista->hideColumn( modelo->fieldIndex( "id_producto" ) );

    modelo->select();

    ActDarBaja = new QAction( this );
    ActDarBaja->setText( "Baja" );
    connect( ActDarBaja, SIGNAL( triggered() ), this, SLOT( darBaja() ) );

    ActAgregar->setIcon( QIcon( ":/imagenes/garantia_agregar.png" ) );
    ActEliminar->setIcon( QIcon( ":/imagenes/garantia_eliminar.png" ) );
    ActDarBaja->setIcon( QIcon( ":/imagenes/garantia_cancelar.png" ) );

    addAction( ActAgregar  );
    addAction( ActDarBaja  );
    addAction( ActEliminar );
    addAction( ActImprimir );
    addAction( ActPdf      );
    addAction( ActCerrar   );
}

#include "dagregargarantia.h"
/*!
 * \brief VGarantias::agregar
 * \param autoeliminarid
 */
void VGarantias::agregar(bool)
{
    DAgregarGarantia *d = new DAgregarGarantia();
    //d->setearModelo( modelo );
    d->exec();
}

/*!
 * \brief VGarantias::imprimir
 */
void VGarantias::imprimir()
{
    if( vista->selectionModel()->selectedRows().count() <= 0 ) {
        QMessageBox::information( this, "Error", QString::fromUtf8( "Seleccione una garantía para volver a imprimir" ) );
        return;
    }

    #ifndef QT_NO_PRINTER
     QPrinter printer( QPrinter::HighResolution );
    #endif
    #ifdef QT_WS_WIN
      printer.setOutputFormat( QPrinter::NativeFormat );
    #endif
    QPrintDialog printDialog( &printer, this );

    MVGarantiasSvg modelo_svg;
    if (printDialog.exec() == QDialog::Accepted) {
         foreach( QModelIndex item, vista->selectionModel()->selectedRows( 0 ) ) {
             int id_garantia = item.model()->data( item.model()->index( item.row(), 0 ), Qt::EditRole ).toInt();
             EGarantiaSVG svg;
             svg.setearRegistro( modelo_svg.obtenerRegistro( id_garantia ) );
             svg.cargarDatos();
             svg.imprimir( &printer );
         }
    }
}

/*!
 * \brief VGarantias::aPdf
 */
void VGarantias::aPdf()
{
    if( vista->selectionModel()->selectedRows().count() <= 0 ) {
        QMessageBox::information( this, "Error", QString::fromUtf8( "Seleccione una garantía para pasar a pdf" ) );
        return;
    }
    MVGarantiasSvg modelo_svg;
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog printDialog( &printer, this );
    if (printDialog.exec() == QDialog::Accepted) {
         foreach( QModelIndex item, vista->selectionModel()->selectedRows( 0 ) ) {
             int id_garantia = item.model()->data( item.model()->index( item.row(), 0 ), Qt::EditRole ).toInt();
             EGarantiaSVG svg;
             QSqlRecord registro = modelo_svg.obtenerRegistro( id_garantia );
             svg.setearRegistro( registro );
             svg.cargarDatos();
             QString nombre_archivo = QString( "Garantia #%1" ).arg( registro.value("id_garantia" ).toString() );
             printer.setOutputFileName( nombre_archivo );
             svg.imprimir( &printer );
         }
    }
}

/*!
 * \brief VGarantias::eliminar
 * Este metodo se utiliza para eliminar las garantías ya pasadas
 */
void VGarantias::eliminar()
{
    if( vista->selectionModel()->selectedRows().count() <= 0 ) {
        QMessageBox::information( this, "Error", "Seleccione una garantía para eliminar" );
        return;
    }
    int ret = QMessageBox::question( this,
                                     QString::fromUtf8( "¿Está seguro?" ),
                                     QString::fromUtf8( "¿Està seguro que desea eliminar %1 garantía(s)" ).arg( vista->selectionModel()->selectedRows().count() ),
                                     QMessageBox::Yes,
                                     QMessageBox::No );
    if( ret == QMessageBox::Yes ) {
        foreach( QModelIndex item, vista->selectionModel()->selectedRows( 0 ) ) {
            int id_garantia = item.model()->data( item.model()->index( item.row(), 0 ), Qt::EditRole ).toInt();
            if( !modelo->estaActiva( id_garantia ) ) {
                if( !modelo->eliminar( id_garantia ) ) {
                    QMessageBox::information( this, "Error", QString::fromUtf8( "No se pudo dar de baja la garantia %1" ).arg( item.row() ) );
                } else {
                    QMessageBox::information( this, "Correcto", QString::fromUtf8( "La garantía %1 fue dada de baja correctamente" ).arg( item.row() ) );
                }
            } else {
                QMessageBox::information( this, "Error", QString::fromUtf8( "El item %1 NO está dado de baja" ).arg( item.row() ) );
            }
        }
    }
    modelo->select();
}

/*!
 * \brief VGarantias::darBaja
 * Da de baja una garantía activa
 */
void VGarantias::darBaja()
{
    if( vista->selectionModel()->selectedRows().count() <= 0 ) {
        QMessageBox::information( this, "Error", "Seleccione una garantía para dar de baja" );
        return;
    }
    foreach( QModelIndex item, vista->selectionModel()->selectedRows( 0 ) ) {
        int id_garantia = item.model()->data( item.model()->index( item.row(), 0 ), Qt::EditRole ).toInt();
        if( modelo->estaActiva( id_garantia ) ) {
            bool ok = false;
            QString razon = QInputDialog::getText( this,
                                                   QString::fromUtf8( "Razón" ),
                                                   QString::fromUtf8( "Ingrese la razón de baja para %1:" ).arg( item.row() ),
                                                   QLineEdit::Normal,
                                                   QString(),
                                                   &ok );
            if( ok ) {
                if( !modelo->darDeBaja( id_garantia, razon, QDate::currentDate() ) ) {
                    QMessageBox::information( this, "Error", QString::fromUtf8( "No se pudo dar de baja la garantia %1" ).arg( item.row() ) );
                } else {
                    QMessageBox::information( this, "Correcto", QString::fromUtf8( "La garantía %1 fue dada de baja correctamente" ).arg( item.row() ) );
                }
            }
        } else {
            QMessageBox::information( this, "Error", QString::fromUtf8( "El item %1 ya está dado de baja" ).arg( item.row() ) );
        }
    }
    modelo->select();
}
