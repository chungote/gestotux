#include "paginafinal.h"

PaginaFinal::PaginaFinal(QWidget *parent) :
    QWizardPage(parent)
{
    setupUi(this);

    registerField( "orden_trabajo.requerente"    , LERequerente  ); // Persona que ingresa el pedido si no es el cliente.
    registerField( "orden_trabajo.ingresante*"   , LEIngresante  ); // Ingresante de la orden ( empleado )
    registerField( "orden_trabajo.fecha_ingreso*", DEIngreso     ); // Fecha de ingreso de la orden
    registerField( "orden_trabajo.fecha_entrega" , DTEDevolucion ); // Fecha posible de devolucion de la orden
    registerField( "orden_trabajo.causa_ingreso*", PTEFallas     ); // Causa o falla del ingreso
    registerField( "orden_trabajo.id_tecnico*"   , CBTecnico     ); // Tecnico asignado
}

int PaginaFinal::nextId() const
{ return -1; }

