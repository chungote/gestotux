#ifndef FORMORDENTRABAJO_H
#define FORMORDENTRABAJO_H

#include "eventana.h"
#include "ui_formordentrabajobase.h"

using namespace Ui;

class FormOrdenTrabajo : public EVentana, public FormOrdenTrabajoBase
{
    Q_OBJECT
    
public:
    FormOrdenTrabajo( bool agregar, QWidget *parent = 0 );
    void setearIdOrdenTrabajo( const int id_orden_trabajo );

protected slots:
    void cambioCliente( int id_cliente );
    void cambioTecnico( int id_tecnico );
    void cerrarOrden();
    void devolverCliente();
    void agregarFacturacion();
    void eliminarFacturacion();
    void agregarHistorial();
    void eliminarHistorial();
    void facturarOrden();
    void imprimir();
    void pdf();
    void cancelar();
    void guardar();
    
protected:
    void changeEvent( QEvent *e );

private:
    QAction *ActCerrarOrden;
    QAction *ActFacturarOrden;
    QAction *ActDevolverCliente;
    QAction *ActImprimir;
    QAction *ActPdf;
    QAction *ActCancelarOrden;

    bool _agregando;

};

#endif // FORMORDENTRABAJO_H
