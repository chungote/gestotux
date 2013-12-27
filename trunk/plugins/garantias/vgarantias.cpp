#include "vgarantias.h"

#include <QTableView>
#include <QMessageBox>
#include <QInputDialog>

#include "EReporte.h"

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
    EReporte *rep = new EReporte( 0 );
    rep->especial( "garantia", ParameterList() );
    foreach( QModelIndex item, vista->selectionModel()->selectedRows( 0 ) ) {
        int id_garantia = item.model()->data( item.model()->index( item.row(), 0 ), Qt::EditRole ).toInt();
        ParameterList lista;
        lista.append( "id_garantia", id_garantia );
        rep->hacerPDF( lista );
    }
    delete rep;
    rep = 0;
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
