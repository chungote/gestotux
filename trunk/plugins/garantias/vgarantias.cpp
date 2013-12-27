#include "vgarantias.h"

#include <QTableView>
#include <QMessageBox>
#include <QInputDialog>

VGarantias::VGarantias(QWidget *parent) :
    EVLista(parent)
{

    setObjectName( "visor-garantias" );
    setWindowTitle( QString::fromUtf8( "Garantías activas" ) );
    setWindowIcon( QIcon( ":/imagenes/garantia.png" ) );

    modelo = new MGarantias( this );

    vista->setModel( modelo );
    vista->hideColumn( 0 );

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

void VGarantias::imprimir()
{
    if( vista->selectionModel()->selectedRows().count() <= 0 ) {
        QMessageBox::information( this, "Error", "Seleccione una garantía para volver a imprimir" );
        return;
    }
    qWarning( "No implementado" );
    return;
}

void VGarantias::aPdf()
{
    if( vista->selectionModel()->selectedRows().count() <= 0 ) {
        QMessageBox::information( this, "Error", "Seleccione una garantía para pasar a pdf" );
        return;
    }
    qWarning( "No implementado" );
    return;
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
    qWarning( "No implementado" );
    return;
}

/*!
 * \brief VGarantias::darBaja
 */
void VGarantias::darBaja()
{
    if( vista->selectionModel()->selectedRows().count() <= 0 ) {
        QMessageBox::information( this, "Error", "Seleccione una garantía para dar de baja" );
        return;
    }
    foreach( QModelIndex item, vista->selectionModel()->selectedRows( 0 ) ) {
        if( item.model()->data( item.model()->index( item.row(), modelo->fieldIndex( "fecha_baja" ) ), Qt::EditRole ).isNull() ) {
            int id_garantia = item.model()->data( item.model()->index( item.row(), 0 ), Qt::EditRole ).toInt();
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
