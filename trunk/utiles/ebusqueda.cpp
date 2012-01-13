#include "ebusqueda.h"

EBusqueda::EBusqueda( QWidget *parent, QSqlTableModel *modelo, QString titulo ) :
    QDockWidget( parent ), Ui::EBusquedaBase()
{
    setupUi( this );
    setObjectName( "dock-busqueda" );
    if( titulo.isEmpty() || titulo.isNull() ) {
        this->setWindowTitle( "Buscador y filtrador" );
    } else { this->setWindowTitle( titulo ); }

    connect( CBTipo, SIGNAL( currentIndexChanged( int ) ), this, SLOT( filtrar() ) );
    connect( LETexto, SIGNAL( textChanged(QString) ), this, SLOT( filtrar() ) );
    connect( PBBorrar, SIGNAL( clicked() ), this, SLOT( borrar() ) );

    _modelo = modelo;
    // Guardo el filtro anterior
    QString _filtro_anterior = _modelo->filter();
}

void EBusqueda::filtrar()
{
    if( filtros.isEmpty() || CBTipo->currentIndex() == -1
        || LETexto->text().isEmpty() || LETexto->text().isNull() )
        return;
    _modelo->setFilter( filtros.at( CBTipo->currentIndex() ).arg( LETexto->text() ) );
    _modelo->select();
}

void EBusqueda::borrar()
{
    this->_modelo->setFilter( _filtro_anterior );
    this->_modelo->select();
    this->CBTipo->setCurrentIndex( -1 );
    this->LETexto->setText( "" );
}

/*!
 * \fn EBusqeuda::agregarFiltro( QString nombre, QString filtro )
 * Funcion que agregar� un filtro al sistema de filtrado automatico.
 * Este sistema colocar� el nombre como item de la lista desplegable.
 * El parametro filtro deber� ser lo que le sigue al WHERE de una consulta select donde los %1 ser�n reemplazados por lo ingresado en el cuadro de texto.
 * \param nombre Nombre del filtro tal como aparecera en la lista deplegable.
 * \param filtro Filtro a a plicar a la consulta sql donde %1 ser� reemplazado por el texto ingresado por el usuario.
 */
void EBusqueda::agregarFiltro( QString nombre, QString filtro )
{
    if( nombre.isEmpty() || filtro.isEmpty() || nombre.isNull() || filtro.isNull() )
    {
        qWarning( "EBusqueda: esta intentando insertar un filtro con alg�n dato vac�o." );
        return;
    }
    CBTipo->insertItem( CBTipo->count(), nombre );
    filtros.insert( filtro.size(), filtro );
}

void EBusqueda::changeEvent( QEvent *e )
{
    QDockWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    case QEvent::Hide:
    case QEvent::Close:
        borrar();
        break;
    default:
        break;
    }
}

void EBusqueda::setearTitulo( QString titulo )
{ this->setWindowTitle( titulo ); }