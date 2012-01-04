#include "ecbclientes.h"

#include <QCompleter>
#include <QTimer>
#include <QLineEdit>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

ECBClientes::ECBClientes(QWidget *parent) :
    QComboBox(parent), filtro()
{
    this->setObjectName( "SelectorClientes" );
    // Seteo las propiedades del combobox
    this->setInsertPolicy( QComboBox::NoInsert );
    this->setSizeAdjustPolicy( QComboBox::AdjustToContentsOnFirstShow );
    this->setEditable( true );
    this->completer()->setCompletionMode( QCompleter::PopupCompletion );
    this->setCurrentIndex( -1 );
    this->setInsertPolicy( QComboBox::NoInsert );
    this->connect( this->lineEdit(), SIGNAL( returnPressed() ), this, SLOT( verificarExiste() ) );

    this->lineEdit()->setText( "Cargando datos..." );
    this->setEnabled( false );

    ids = new QList<int>();

    QTimer timer;
    timer.singleShot( 900, this, SLOT( inicializar() ) );
}

void ECBClientes::setearFiltro( const QString f ) {
    this->filtro = f;
    QTimer timer;
    timer.singleShot( 900, this, SLOT( inicializar() ) );
}

ECBClientes::~ECBClientes()
{
    delete ids;
}

/*!
 * \fn ECBClientes::inicializar()
 * Funcion que carga los datos y setea todo como para su uso
 */
void ECBClientes::inicializar()
{
    // Cargo los datos del modelo
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT id, razon_social FROM clientes %1 ORDER BY razon_social ASC" ).arg( filtro ) ) ) {
        int pos = 0;
        while( cola.next() ) {
            this->insertItem( pos, cola.record().value(1).toString() );
            ids->insert( pos, cola.record().value(0).toInt() );
/*            this->setItemData( pos , cola.record().value(0) );
            if( this->itemData( pos, Qt::UserRole ).isValid() )
                qDebug( this->itemData( pos, Qt::UserRole ).toString().toLocal8Bit() );*/
            pos++;
        }
        if( pos == 0 ) {
            qWarning( "No hay ningun cliente para cargar!" );
            this->lineEdit()->setText( "No hay clientes cargados..." );
        }
        this->setEnabled( true );
        this->setCurrentIndex( -1 );
    } else {
        qWarning( "Error al intentar ejecutar la cola para cargar los clientes" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
    }
/*    for( int i = 0; i < this->count(); i ++ ) {
        qDebug( QString( "pos: %1 - %2 - ID: %3 " ).arg( i ).arg( this->itemText( i ) ).arg( itemData( i ).toString() ).toLocal8Bit() );
    }*/
}

/*!
 * \fn ECBClientes::idClienteActual()
 * Devuelve el id de cliente actual
 */
int ECBClientes::idClienteActual()
{
  /*for( int i = 0; i < this->count(); i ++ ) {
      qDebug( QString( "pos: %1, - %2 - ID: %3 " ).arg( i ).arg( this->itemText( i ) ).arg( itemData( i ).toString() ).toLocal8Bit() );
    }*/
    //qDebug( QString::number( ids->value( this->currentIndex() ) ).toLocal8Bit() );
    //return this->itemData( this->currentIndex() ).toInt();
    return ids->value( this->currentIndex() );
}

/*!
 * \fn ECBClientes::verificarExiste()
 * Ve si el numero de cliente o texto buscado existe en la lista. Si existe lo coloca como item actual.
 */
void ECBClientes::verificarExiste()
{
    // Veo que tipo de entrada es
    QString buscar = this->lineEdit()->text();
    int b = this->findText( buscar );
    if( b != -1 ) {
        this->setCurrentIndex( b );
    } else {
        // No es un nombre de cliente sino un numero de cliente.
        //int c =  this->findData( buscar );
        int c = ids->indexOf( buscar.toInt() );
        if( c != -1 ) {
            this->setCurrentIndex( c );
        } else {
            QMessageBox::information( this, "No encontrado", "El cliente o codigo de cliente buscado no existe." );
        }
    }
    return;
}
