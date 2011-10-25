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

    _mapa_ids_pos = new QMap<int, int>();
    _mapa_codigo_pos = new QMap<QString, int>();
    _mod_prod = 0;

    QTimer timer;
    timer.singleShot( 900, this, SLOT( inicializar() ) );
}


ECBProductos::~ECBProductos()
{
    delete _mapa_ids_pos;
    delete _mapa_codigo_pos;
    if(!_mod_prod )
        delete _mod_prod;
    _mapa_ids_pos = 0;
    _mapa_codigo_pos = 0;
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
    if( cola.exec( "SELECT id, codigo, nombre FROM producto ORDER BY nombre ASC" ) ) {
        int pos = 0;
        while( cola.next() ) {
            // Pos = currentIndex();
            // id_producto = _mapa_pos_ids
            // codigo = _mapa_pos_codigo
            this->insertItem( pos, cola.record().value(2).toString(), cola.record().value(0).toInt() );
            this->_mapa_codigo_pos->insert( cola.record().value(1).toString(), pos );
            this->_mapa_ids_pos->insert   ( cola.record().value(0).toInt(), pos    );
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
    // Veo que tipo de entrada es
    QString buscar = this->lineEdit()->text();
    int b = this->findText( buscar );
    if( b != -1 ) {
        this->setCurrentIndex( b );
    } else {
        QMap<QString, int>::const_iterator i =  this->_mapa_codigo_pos->find( buscar );
        if( i != this->_mapa_codigo_pos->end() ) {
            this->setCurrentIndex( i.value() );
        }
    }
    emit agregarProducto();
    return;
}

QMap<int, QString> *ECBProductos::listadoProductos()
{
    if( _mod_prod != 0 ) {
        for( int i = 0; i < count(); i++ ) {
            _mod_prod->insert( itemData( i ).toInt(), itemText( i ) );
        }
    }
    return _mod_prod;
}
