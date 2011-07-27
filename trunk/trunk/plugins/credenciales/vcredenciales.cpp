#include <QTableView>
#include "MCredenciales.h"
#include "vcredenciales.h"

VCredenciales::VCredenciales(QWidget *parent) :
    EVLista(parent)
{
    this->setObjectName( "listacredenciales" );
    this->setWindowTitle( "Listado de Credenciales" );

    this->rmodel = new MCredenciales( this );
    this->vista->setModel( this->rmodel );
    this->vista->hideColumn( 0 );
    this->vista->setSelectionBehavior( QTableView::);
    this->rmodel->select();

    addAction( ActImprimir );
    addAction( ActCerrar );
}

void VCredenciales::imprimir()
{
    // Busco los ids seleccionados
    QModelIndexList *lista = this->vista->selectionModel()->selectedRows();
    if( lista->isEmpty() ) {
        QMessageBox::information( this, "Error", "Seleccione una credencial para reimprimirla." );
        return;
    }
    // Busca el id
    int id = this->modelo->data( this->modelo->index( lista->first().row(), 0 ), Qt::EditRole ).toInt();
    EReporte *rep = new EReporte( 0 );
    ParamterList param;
    param.append( new Parameter( "id_credencial", id ) );
    rep->especial( "credencial-union", param );
    if( ! rep->hacer() ) {
        qWarning( "Error al imprimir" );
    }
}
