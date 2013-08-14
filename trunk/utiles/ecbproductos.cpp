#include "ecbproductos.h"

#include <QCompleter>
#include <QTimer>
#include <QLineEdit>
#include <QDebug>

ECBProductos::ECBProductos( QWidget *parent ) :
 QComboBox(parent)
{
    this->setObjectName( "SelectorProductos" );
    // Seteo las propiedades del combobox
    this->setInsertPolicy( QComboBox::NoInsert );
    this->setSizeAdjustPolicy( QComboBox::AdjustToContentsOnFirstShow );
    this->setEditable( true );
    this->completer()->setCompletionMode( QCompleter::PopupCompletion );
    this->setCurrentIndex( -1 );
    this->setInsertPolicy( QComboBox::NoInsert );
    this->connect( this->lineEdit(), SIGNAL( returnPressed() ), this, SLOT( enterApretado() ) );

    this->lineEdit()->setText( "Cargando datos..." );
    this->setEnabled( false );

    _mapa_pos_codigo = new QMap<QString, int>();
    _mapa_id_nombre = new QMap<int, QString>();
    _mapa_pos_ids = new QMap<int, int>();

    this->_min = -1;

    QTimer timer;
    timer.singleShot( 900, this, SLOT( inicializar() ) );
}

ECBProductos::~ECBProductos()
{
    delete _mapa_pos_codigo;
    _mapa_pos_codigo = 0;
    delete _mapa_id_nombre;
    _mapa_id_nombre = 0;
    delete _mapa_pos_ids;
    _mapa_pos_ids = 0;
}

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
/*!
 * \fn ECBProductos::inicializar()
 * Función que carga los datos y setea todo como para su uso
 */
void ECBProductos::inicializar()
{
    // Cargo los datos del modelo
    QSqlQuery cola;
    if( cola.exec( "SELECT id, codigo, nombre FROM producto WHERE habilitado IN ( 1, 'true' ) ORDER BY nombre ASC" ) ) {
        int pos = 0;
        while( cola.next() ) {
            // Pos = currentIndex();
            // id_producto = _mapa_pos_ids
            // codigo = _mapa_pos_codigo
            this->insertItem( pos, cola.record().value(2).toString(), cola.record().value(0).toInt() );
            this->_mapa_pos_codigo->insert( cola.record().value(1).toString(), pos );
            this->_mapa_id_nombre->insert ( cola.record().value(0).toInt()   , cola.record().value(2).toString() );
            this->_mapa_pos_ids->insert   ( pos, cola.record().value(0).toInt() );
            pos++;
        }
        if( pos == 0 ) {
            qWarning( "No hay ningun producto para cargar!" );
            this->lineEdit()->setText( "No hay productos cargados..." );
        }
        this->setEnabled( true );
        this->setCurrentIndex( -1 );
    } else {
        qWarning( "Error al intentar ejecutar la cola para cargar los productos" );
        qDebug() << cola.lastError().text();
        qDebug() << cola.lastQuery();
    }
}

void ECBProductos::enterApretado()
{
    verificarExiste();
    emit agregarProducto();
    return;
}

QMap<int, QString> *ECBProductos::listadoProductos()
{ return this->_mapa_id_nombre; }

void ECBProductos::setearListado( QMap<int, QString> *lista )
{
    // Verifica que los demás items estén de acuerdo con esta lista
    // El mappeo debe sacar solo los elementos menores que cero
    QList<int> l2 = lista->keys();
    for( int i = 0; i < l2.size(); i++ ) {
        if( l2.value(i) < 0 ) {
            // Ingreso este valor al cb
            QString texto = lista->value( l2.value( i ) );
            int indice = l2.value( i );
            int pos = this->count();
            this->insertItem( pos, texto, indice );
            this->_mapa_id_nombre->insert( indice, texto );
            this->_mapa_pos_ids->insert( pos, indice );
            this->_mapa_pos_codigo->insert( QString::number( indice ), pos );
        }
    }
}

int ECBProductos::idActual() const
{
    return this->_mapa_pos_ids->value( this->currentIndex() );
}

void ECBProductos::verificarExiste()
{
    // Veo que tipo de entrada es
    QString buscar = this->lineEdit()->text();
    int b = this->findText( buscar );
    if( b != -1 ) {
        this->setCurrentIndex( b );
    } else {
        QMap<QString, int>::const_iterator i =  this->_mapa_pos_codigo->find( buscar );
        if( i != this->_mapa_pos_codigo->end() ) {
            this->setCurrentIndex( i.value() );
        } else {
            // Tengo que agregarlo como item exclusivo
            // Agregado al final pero con ID <= -1
            int pos_nueva = this->count();
            this->_mapa_pos_codigo->insert( QString::number( _min ), pos_nueva );
            this->_mapa_pos_ids->insert( pos_nueva, _min );
            this->_mapa_id_nombre->insert( _min, this->lineEdit()->text() );
            this->insertItem( pos_nueva, this->lineEdit()->text(), _min );
            this->setCurrentIndex( pos_nueva );
            this->_min--;
        }
    }
}
