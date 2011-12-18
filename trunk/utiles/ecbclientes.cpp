#include "ecbclientes.h"

#include <QCompleter>
#include <QTimer>
#include <QLineEdit>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

ECBClientes::ECBClientes(QWidget *parent) :
    QComboBox(parent)
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

    QTimer timer;
    timer.singleShot( 900, this, SLOT( inicializar() ) );
}


/*!
 * \fn ECBClientes::inicializar()
 * Función que carga los datos y setea todo como para su uso
 */
void ECBClientes::inicializar()
{
    // Cargo los datos del modelo
    QSqlQuery cola;
    if( cola.exec( "SELECT id, razon_social FROM clientes ORDER BY razon_social ASC" ) ) {
        int pos = 0;
        while( cola.next() ) {
            this->insertItem( pos, cola.record().value(1).toString(), cola.record().value(0).toInt() );
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
}

int ECBClientes::idClienteActual()
{
    return this->itemData( this->currentIndex() ).toInt();
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
        int c = this->findData( buscar );
        if( c != -1 ) {
            this->setCurrentIndex( c );
        } else {
            QMessageBox::information( this, "No encontrado", "El cliente o codigo de cliente buscado no existe." );
        }
    }
    return;
}