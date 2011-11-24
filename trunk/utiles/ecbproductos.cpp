#include "ecbproductos.h"

#include <QCompleter>
#include <QTimer>
#include <QLineEdit>

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
    if( cola.exec( "SELECT id, codigo, nombre FROM producto WHERE habilitado = 1 ORDER BY nombre ASC" ) ) {
        int pos = 0;
        while( cola.next() ) {
            // Pos = currentIndex();
            // id_producto = item cb itemData
            // codigo = _mapa_pos_codigo
            this->insertItem( pos, cola.record().value(2).toString(), cola.record().value(0).toInt() );
            this->_mapa_pos_codigo->insert( cola.record().value(1).toString(), pos );
            this->_mapa_id_nombre->insert ( cola.record().value(0).toInt()   , cola.record().value(2).toString() );
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
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
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

int ECBProductos::idActual() const
{ return this->itemData( this->currentIndex() ).toInt(); }

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
            //this->_mapa_pos_ids->insert( _min, this->count() );
            this->_mapa_id_nombre->insert( _min, this->lineEdit()->text() );
            this->insertItem( pos_nueva, this->lineEdit()->text(), _min );
            this->setCurrentIndex( pos_nueva );
            this->_min--;
        }
    }
}
