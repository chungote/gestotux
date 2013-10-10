#include "ordentrabajowizard.h"

#include <QSqlDatabase>
#include <QMessageBox>

#include "wizard/paginacliente.h"
#include "wizard/paginaclientenuevo.h"
#include "wizard/paginaequipamiento.h"
#include "wizard/paginaequipamientonuevo.h"
#include "wizard/paginaequipamientoexistente.h"
#include "wizard/paginafinal.h"

#include "mordentrabajo.h"

OrdenTrabajoWizard::OrdenTrabajoWizard( QWidget *parent ) :
QWizard(parent)
{
    setPage( Pagina_Cliente, new PaginaCliente );
    setPage( Pagina_ClienteNuevo, new PaginaClienteNuevo );
    setPage( Pagina_Equipamiento, new PaginaEquipamiento );
    setPage( Pagina_EquipamientoNuevo, new PaginaEquipamientoNuevo );
    setPage( Pagina_EquipamientoExistente, new PaginaEquipamientoExistente );
    setPage( Pagina_Final, new PaginaFinal );

    setStartId( Pagina_Cliente );

    setOption( HaveHelpButton, false );
    /// @TODO: Agregar logotipo para titorial de orden de trabajo.
    //setPixmap( QWizard::LogoPixmap, QPixmap( ":/images/logo.png" ) );

    setWindowTitle( "Agregar orden trabajo" );
}

void OrdenTrabajoWizard::done( int result )
{
    // Utilizando los datos indicados por el usuario
    // genero la orden de trabajo.
    QSqlDatabase::database().transaction();

    int id_cliente = -1;
    if( visitedPages().contains( Pagina_Cliente ) ) {
        id_cliente = field( "cliente.id_cliente" ).toInt();
    } else {
        // Guardo los datos del cliente
        /// @TODO: Crear un nuevo cliente con esos datos!
    }

    int id_equipamiento = -1;
    if( visitedPages().contains( Pagina_EquipamientoExistente ) ) {
        id_equipamiento = field( "equipamiento.id_equipamiento" ).toInt();
    } else {
        /// @TODO: Crear un nuevo equipamiento con los datos!
    }

    MOrdenTrabajo *mot = new MOrdenTrabajo();
    if( !mot->agregarOrdenTrabajo( id_cliente,
                                   id_equipamiento,
                                   field( "orden_trabajo.id_tecnico"    ).toInt()   ,
                                   field( "orden_trabajo.requerente"    ).toString(),
                                   field( "orden_trabajo.ingresante"    ).toString(),
                                   field( "orden_trabajo.fecha_ingreso" ).toDate()  ,
                                   field( "orden_trabajo.fecha_entrega" ).toDate()  ,
                                   field( "orden_trabajo.causa_ingreso" ).toString() ) ) {
        QMessageBox::critical( this, "Error", "No se pudo guardar la orden de trabajo" );
        QSqlDatabase::database().rollback();
        return;
    }

    /// @TODO: Agregar logica aquí para guardar la orden de trabajo

    if( QSqlDatabase::database().commit() == true ) {
        QMessageBox::information( this, "Error", "No se pudo hacer el commit de la base de datos" );
        QSqlDatabase::database().rollback();
        return;
    }
    QDialog::done( result );
}


/*!
 *
 * Registros ocupados:
 *
 * Pagina_cliente
 * cliente.id_cliente = Identificador del cliente
 *
 * Pagina_ClienteNuevo
 * cliente.nombre      = Nombre del nuevo cliente
 * cliente.razonsocial = Razon social del nuevo cliente
 * cliente.apellido    = apellido del nuevo cliente
 * cliente.direccion   = direccion del nuevo cliente
 * cliente.inscripcion = idnetificador del id de estado fiscal
 * cliente.telefono    = telefono del nuevo cliente
 *
 * Pagina_Equipamiento
 * equipamiento.nuevo     = Se declara un nuevo equipamiento.
 * equipamiento.existente = se utiliza un equipamiento ya existente.
 *
 * Pagina_EquipamientoNuevo
 * equipamiento.descripcion   = descripcion del nuevo equipamiento
 * equipamiento.modelo        = modelo del nuevo equipamiento
 * equipamiento.marca         = marca del nuevo equipamiento
 * equipamiento.observaciones = observaciones del nuevo equipamiento
 * equipamiento.numeroserie   = numero de serie del nuevo equipamiento
 *
 * Pagina_EquipamientoExistente
 * equipamiento.id_equipamiento  = identificador del equipamiento
 *
 * Pagina_Final
 * orden_trabajo.requerente    = Persona que ingresa el pedido si no es el cliente.
 * orden_trabajo.ingresante    = Ingresante de la orden ( empleado )
 * orden_trabajo.fecha_ingreso = Fecha de ingreso de la orden
 * orden_trabajo.fecha_entrega = Fecha posible de devolucion de la orden
 * orden_trabajo.causa_ingreso = Causa o falla del ingreso
 * orden_trabajo.id_tecnico    = Tecnico asignado
 */