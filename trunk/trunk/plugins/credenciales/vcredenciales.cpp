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
    this->rmodel->select();

    addAction( ActCerrar );
}
