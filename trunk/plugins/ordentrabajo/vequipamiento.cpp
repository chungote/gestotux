#include "vequipamiento.h"

#include "mequipamiento.h"
#include "formequipamiento.h"

#include <QTableView>
#include <QMessageBox>
#include <QInputDialog>
#include <QMenu>

VEquipamiento::VEquipamiento(QWidget *parent) :
EVLista( parent )
{
    this->setObjectName( "VisorEquipamiento" );
    this->setWindowTitle( "Equipamientos" );
    this->setWindowIcon( QIcon( ":/imagenes/equipamiento.png" ) );

    this->modelo = new MEquipamiento( this );
    this->vista->setModel( this->modelo );
    this->vista->setSelectionBehavior( QAbstractItemView::SelectRows );
    this->vista->setAlternatingRowColors( true );
    this->vista->hideColumn( modelo->fieldIndex( "id_equipamiento" ) );
    this->vista->hideColumn( modelo->fieldIndex( "num_serie" ) );
    this->vista->hideColumn( modelo->fieldIndex( "fecha_baja" ) );
    this->vista->hideColumn( modelo->fieldIndex( "razon_baja" ) );
    this->vista->hideColumn( modelo->fieldIndex( "fecha_compra" ) );
    this->vista->hideColumn( modelo->fieldIndex( "modelo" ) );
    this->vista->hideColumn( modelo->fieldIndex( "marca" ) );
    this->vista->setSortingEnabled( true );
    this->modelo->select();

    ActDarBaja = new QAction( this );
    ActDarBaja->setText( "Baja" );
    ActDarBaja->setStatusTip( "Da de baja el equipamiento seleccionado" );
    connect( ActDarBaja, SIGNAL( triggered() ), this, SLOT( darBaja() ) );

    ActDarAlta = new QAction( this );
    ActDarAlta->setText( "Alta" );
    ActDarAlta->setStatusTip( "Da de alta nuevamente el equipamiento seleccionado" );
    connect( ActDarAlta, SIGNAL( triggered() ), this, SLOT( darAlta() ) );

    addAction( ActAgregar );
    addAction( ActModificar );
    addAction( ActDarBaja );
    addAction( ActEliminar );
    addAction( ActCerrar );
}

/*!
 * \brief VEquipamiento::agregar
 */
void VEquipamiento::agregar( bool )
{
    FormEquipamiento *f = new FormEquipamiento();
    f->setearModeloEquipamiento( qobject_cast<MEquipamiento *>( this->modelo ) );
    f->setearAgregar( true );
    emit agregarVentana( f );
}

/*!
 * \brief VEquipamiento::modificar
 */
void VEquipamiento::modificar()
{
    QModelIndexList lista = this->vista->selectionModel()->selectedRows();
    if( lista.size() <= 0 ) {
        QMessageBox::information( this, "Error", QString::fromUtf8( "Por favor, seleccione algún equipamiento para modificar" ) );
        return;
    }
    foreach( QModelIndex indice, lista ) {
        FormEquipamiento *f = new FormEquipamiento();
        f->setearModeloEquipamiento( qobject_cast<MEquipamiento *>( this->modelo ) );
        f->setearAgregar( false );
        f->setearIndice( indice );
        emit agregarVentana( f );
    }
}

/*!
 * \brief VEquipamiento::eliminar
 */
void VEquipamiento::eliminar()
{
    QModelIndexList lista = this->vista->selectionModel()->selectedRows();
    if( lista.size() <= 0 ) {
        QMessageBox::information( this, "Error", QString::fromUtf8( "Por favor, seleccione algún equipamiento para eliminar" ) );
        return;
    }
    if( QMessageBox::question( this, "¿Está seguro?", "Está seguro que desea eliminar estos equpamientos? \n Se eliminarán todos los registros relacionados con estos datos, exceptuando las facturas y garantías" ) != QMessageBox::Ok ) {
        return;
    }
    foreach( QModelIndex indice, lista ) {
        int id_equipamiento = modelo->data( modelo->index( indice.row(), 0 ), Qt::DisplayRole ).toInt();
        if( !modelo->eliminarConRelacionados( id_equipamiento ) ) {
            QMessageBox::information( this, "Error", "No se pudo eliminar el equipamiento " + id_equipamiento );
        }
    }
}

void VEquipamiento::darBaja()
{
    QModelIndexList lista = this->vista->selectionModel()->selectedRows();
    if( lista.size() <= 0 ) {
        QMessageBox::information( this, "Error", QString::fromUtf8( "Por favor, seleccione algún equipamiento para dar de baja" ) );
        return;
    }
    if( QMessageBox::question( this, "¿Está seguro?", "Está seguro que desea dar de baja estos equpamientos?" ) != QMessageBox::Ok ) {
        return;
    }
    foreach( QModelIndex indice, lista ) {
        bool ok = false;
        QString razon = QInputDialog::getText( this, QString::fromUtf8( "Razón" ), QString::fromUtf8( "Razón:" ), QLineEdit::Normal, QString(), &ok );
        if( ok ) {
            if( !razon.isEmpty() ) {
                razon.append( "Razón desconocida" );
            }
            int id_equipamiento = modelo->data( modelo->index( indice.row(), 0 ), Qt::DisplayRole ).toInt();
            if( modelo->darDeBaja( id_equipamiento ) ) {
                QMessageBox::information( this, "Correcto", "El equipamiento se pudo dar de baja correctamente" );
            } else {
                QMessageBox::information( this, "Incorrecto", "El equipamiento no se pudo dar de baja" );
            }
        }
    }
}

void VEquipamiento::menuContextual(const QModelIndex &indice, QMenu *menu)
{
    menu->addAction( ActAgregar );
    menu->addAction( ActModificar );
    if( modelo->data( modelo->index( indice.row(), modelo->fieldIndex( "fecha_baja" ) ), Qt::UserRole ).toBool() ) {
        menu->addAction( ActDarBaja );
    } else {
        menu->addAction( ActDarAlta );
    }
    menu->addAction( ActEliminar );
}
