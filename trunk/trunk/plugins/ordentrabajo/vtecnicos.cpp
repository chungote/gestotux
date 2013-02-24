#include "vtecnicos.h"

#include "mtecnicos.h"
#include "eactcerrar.h"
#include "dsino.h"

#include <QTableView>
#include <QInputDialog>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlError>

VTecnicos::VTecnicos(QWidget *parent) :
EVLista(parent)
{
    this->setObjectName("VistaTecnicos");
    this->setWindowTitle( "Tecnicos" );
    this->setWindowIcon( QIcon( ":/imagenes/tecnico.png" ) );

    modelo = new MTecnicos( this->vista );
    this->vista->setModel( this->modelo );

    this->vista->hideColumn( 0 ); // Oculta el ID del modelo
    this->vista->setAlternatingRowColors( true );
    this->vista->setSortingEnabled( true );
    this->vista->setItemDelegateForColumn( 2, new DSiNo( this->vista ) ); // Campo Booleano

    ActAgregar->setStatusTip( QString::fromUtf8( "Agregar nuevo técnico al sistema" ) );
    ActModificar->setStatusTip( QString::fromUtf8( "Modificar dato de un técnico" ) );

    ActHabilitar = new QAction( this );
    ActHabilitar->setText( "Habilitar" );
    ActHabilitar->setStatusTip( QString::fromUtf8( "Habilita un técnico que ha estado deshabilitado" ) );
    //ActHabilitar->setIcon();
    connect( ActHabilitar, SIGNAL( triggered() ), this, SLOT( habilitar() ) );

    ActDeshabilitar = new QAction( this );
    ActDeshabilitar->setText( "Deshabilitar" );
    ActDeshabilitar->setStatusTip( QString::fromUtf8( "Deshabilita un técnico que ha estado habilitado" ) );
    //ActHabilitar->setIcon();
    connect( ActDeshabilitar, SIGNAL( triggered() ), this, SLOT( habilitar() ) );

    ActMostrarDeshabilitados = new QAction( this );
    ActMostrarDeshabilitados->setText( "Deshabilitados" );
    ActMostrarDeshabilitados->setCheckable( true );
    ActMostrarDeshabilitados->setStatusTip( QString::fromUtf8( "Muestra los técnicos deshabilitados" ) );
    connect( ActMostrarDeshabilitados, SIGNAL( toggled( bool ) ), this, SLOT( cambiarVerDeshabilitado( bool ) ) );

    QAction *ActSep = new QAction( this );
    ActSep->setSeparator( true );

    this->addAction( ActAgregar );
    this->addAction( ActModificar );
    this->addAction( ActHabilitar );
    this->addAction( ActDeshabilitar );
    this->addAction( ActEliminar );
    this->addAction( new EActCerrar( this ) );
    this->addAction( ActSep );
    this->addAction( ActMostrarDeshabilitados );

    cambiarVerDeshabilitado( false );

    this->modelo->select();
}

/*!
 * \fn VTecnicos::agregar( bool )
 * Agrega un nuevo tecnico a la lista
 */
void VTecnicos::agregar( bool )
{
 // Agrego un nuevo técnico
    bool ok = false;
    QString nombre = QInputDialog::getText( this,  QString::fromUtf8( "Agregar técnico" ),  QString::fromUtf8( "Nueva razón social:" ), QLineEdit::Normal, QString(), &ok );
    if( ok && !nombre.isEmpty() ) {
        // Verifico que no exista ya el nombre
        if( MTecnicos::existe( nombre ) ) {
            QMessageBox::warning( this, "Error", QString::fromUtf8( "El técnico que está intentando ingresar ya se encuentra en la base de datos" ) );
        } else {
            QSqlRecord r = this->modelo->record();
            r.setValue( "razon_social", nombre );
            r.setValue( "habilitado", true );
            if( this->modelo->insertRecord( -1, r ) ) {
                QMessageBox::information( this, "Correcto",  QString::fromUtf8( "El técnico se agregó correctamente" ) );
            } else {
                QMessageBox::warning( this, "Incorrecto",  QString::fromUtf8( "No se pudo agregar el nuevo técnico" ) );
            }
        }
    }
}

/*!
 * \fn VTecnicos::modificar()
 * Modifica el técnico que esté seleccionado
 **/
void VTecnicos::modificar()
{
    if( this->vista->selectionModel()->selectedRows().size() <= 0 ) {
        QMessageBox::warning( this, "Error", QString::fromUtf8( "Seleccióne al menos un técnico para modificarlo" ) );
        return;
    }
    // Busco solo el primero
    QModelIndex idx = this->vista->selectionModel()->selectedRows().first();
    QString nombre_anterior = idx.model()->data( idx, Qt::EditRole ).toString();
    bool ok = false;
    QString nombre = QInputDialog::getText( this,  QString::fromUtf8( "Modificar técnico" ),  QString::fromUtf8( "Nueva razón social:" ), QLineEdit::Normal, nombre_anterior, &ok );
    if( ok && nombre_anterior != nombre && !nombre.isEmpty() ) {
        if( MTecnicos::existe( nombre ) ) {
            QMessageBox::warning( this, "Error", QString::fromUtf8( "El técnico que está intentando ingresar ya se encuentra en la base de datos" ) );
        } else {
            QSqlRecord r = this->modelo->record( idx.row() );
            r.setValue( "razon_social", nombre );
            if( this->modelo->setRecord( idx.row(), r ) ) {
                QMessageBox::information( this, "Correcto", QString::fromUtf8( "El técnico fue modificado correctamente" ) );
                return;
            } else {
                QMessageBox::warning( this, "Error", QString::fromUtf8( "No se pudo modificar el técnico" ) );
                qDebug( "Error al modificar el registro del técnico" );
                qDebug( this->modelo->lastError().text().toLocal8Bit() );
                return;
            }
        }
    }
    return;
}

/*!
 * \fn VTecnicos::eliminar()
 * Verifica si se puede eliminar un tecnico
 */
void VTecnicos::eliminar()
{
    if( this->vista->selectionModel()->selectedRows().size() <= 0 ) {
        QMessageBox::warning( this, "Error", QString::fromUtf8( "Seleccióne al menos un técnico para borrar" ) );
        return;
    }
    QModelIndexList indices = this->vista->selectionModel()->selectedRows();
    // Obtener la confirmación
    int ret = QMessageBox::question( this, QString::fromUtf8( "¿Está seguro?" ), QString::fromUtf8( "¿Está seguro que desea eliminar %1 tecnico%2?" ).arg( indices.size() ).arg( (indices.size() > 1) ? "s":"" ) );
    if( ret == QMessageBox::Ok ) {
        foreach( QModelIndex idx, indices ) {
            // Busco cada registro y verifico que no existan relaciones
            int id_tecnico = idx.model()->data( idx.model()->index( idx.row(), 0 ), Qt::EditRole ).toInt();
            if( !this->modelo->tieneDatosRelacionados( id_tecnico ) ) {
                this->modelo->removeRow( idx.row() );
            }
        }
    }
    QMessageBox::information( this, "Listo", "Los items que no fueron eliminados poseen alguna orden de trabajo relacionada. Si no desea perder la orden de trabajo o cambiar su tecnico asociado, ponga el técnico como deshabilitado." );
}

/*!
 * \fn VTecnicos::habilitar()
 * Habilita un técnico que ha estado deshabilitado
 */
void VTecnicos::habilitar()
{
    if( this->vista->selectionModel()->selectedRows().size() <= 0 ) {
        QMessageBox::warning( this, "Error", QString::fromUtf8( "Seleccióne al menos un técnico para borrar" ) );
        return;
    }
    QModelIndex idx = this->vista->selectionModel()->selectedRows().first();
    QSqlRecord r = this->modelo->record( idx.row() );
    r.setValue( "habilitado", true );
    if( this->modelo->setRecord( idx.row(), r ) ) {
        QMessageBox::information( this, "Correcto", QString::fromUtf8( "El técnico ha sido habilitado" ) );
    } else {
        QMessageBox::warning( this, "Error", QString::fromUtf8( "El técnico no pude ser habilitado" ) );
    }
}

/*!
 * \fn VTecnicos::deshabilitar()
 * Deshabilita un técnico que ha estado habilitado
 */
void VTecnicos::deshabilitar()
{
    if( this->vista->selectionModel()->selectedRows().size() <= 0 ) {
        QMessageBox::warning( this, "Error", QString::fromUtf8( "Seleccióne al menos un técnico para borrar" ) );
        return;
    }
    QModelIndex idx = this->vista->selectionModel()->selectedRows().first();
    QSqlRecord r = this->modelo->record( idx.row() );
    r.setValue( "habilitado", false );
    if( this->modelo->setRecord( idx.row(), r ) ) {
        QMessageBox::information( this, "Correcto", QString::fromUtf8( "El técnico ha sido habilitado" ) );
    } else {
        QMessageBox::warning( this, "Error", QString::fromUtf8( "El técnico no pude ser habilitado" ) );
    }
}

/*!
 * \fn VTecnicos::cambiarHabilitado()
 * Permite mostrar o ocultar los técnicos deshabilitados
 */
void VTecnicos::cambiarVerDeshabilitado( bool estado )
{
    this->modelo->setFilter( QString( "habilitado = %1" ).arg( estado ) );
    this->modelo->select();
}

