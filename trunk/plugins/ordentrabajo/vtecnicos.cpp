#include "vtecnicos.h"

#include "mtecnicos.h"
#include "eactcerrar.h"
#include "dsino.h"

#include <QTableView>
#include <QInputDialog>
#include <QMessageBox>
#include <QSqlRecord>

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
    connect( ActMostrarDeshabilitados, SIGNAL( toggled( bool ) ), this, SLOT( cambiarHabilitado( bool ) ) );

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

    cambiarHabilitado( false );

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
{ qWarning( "No Implementado todavía" ); }

/*!
 * \fn VTecnicos::eliminar()
 * Verifica si se puede eliminar un tecnico
 */
void VTecnicos::eliminar()
{ qWarning( "Eliminar datos es peligroso!"); }

/*!
 * \fn VTecnicos::habilitar()
 * Habilita un técnico que ha estado deshabilitado
 */
void VTecnicos::habilitar()
{ qWarning( "No implementado todavía" ); }

/*!
 * \fn VTecnicos::deshabilitar()
 * Deshabilita un técnico que ha estado habilitado
 */
void VTecnicos::deshabilitar()
{ qWarning( "No implementado todavía" ); }

/*!
 * \fn VTecnicos::cambiarHabilitado()
 * Permite mostrar o ocultar los técnicos deshabilitados
 */
void VTecnicos::cambiarHabilitado( bool estado )
{
    if( !estado ) {
        this->modelo->setFilter( " habilitado = 0" );
    } else {
        this->modelo->setFilter( QString() );
    }
    this->modelo->select();
}

