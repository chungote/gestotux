#include "ordentrabajowizard.h"

#include "wizard/paginacliente.h"
#include "wizard/paginaclientenuevo.h"
#include "wizard/paginaequipamiento.h"
#include "wizard/paginaequipamientonuevo.h"

OrdenTrabajoWizard::OrdenTrabajoWizard( QWidget *parent ) :
QWizard(parent)
{
    setPage( Pagina_Cliente, new PaginaCliente );
    setPage( Pagina_ClienteNuevo, new PaginaClienteNuevo );
    setPage( Pagina_Equipamiento, new PaginaEquipamiento );
    setPage( Pagina_EquipamientoNuevo, new PaginaEquipamientoNuevo );
    /*setPage( PaginaEquipamientoExistente, new PaginaEquipamientoExistente );
    setPage( PaginaFinal, new PaginaFinal );*/

    setStartId( Pagina_Cliente );

    setOption( HaveHelpButton, false );
    //setPixmap( QWizard::LogoPixmap, QPixmap( ":/images/logo.png" ) );

    setWindowTitle( "Agregar orden trabajo" );
}


/*!
 *
 * Registros ocupados:
 *
 * Pagina_cliente
 * cliente.id_cliente = Identificador del cliente
 *
 * Pagina_ClienteNuevo
 * cliente.nombre = Nombre del nuevo cliente
 * cliente.razonsocial = Razon social del nuevo cliente
 * cliente.apellido = apellido del nuevo cliente
 * cliente.direccion = direccion del nuevo cliente
 * cliente.inscripcion = idnetificador del id de estado fiscal
 * cliente.telefono = telefono del nuevo cliente
 *
 * Pagina_Equipamiento
 * equipamiento.nuevo = Se declara un nuevo equipamiento.
 * equipamiento.existente = se utiliza un equipamiento ya existente.
 *
 * Pagina_EquipamientoNuevo
 * equipamiento.descripcion = descripcion del nuevo equipamiento
 * equipamiento.modelo = modelo del nuevo equipamiento
 * equipamiento.marca = marca del nuevo equipamiento
 * equipamiento.observaciones = observaciones del nuevo equipamiento
 * equipamiento.numeroserie = numero de serie del nuevo equipamiento
 *
 * Pagina_EquipamientoExistente
 * Pagina_Final
 */