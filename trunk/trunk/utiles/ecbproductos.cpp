#include "ecbproductos.h"

#include <QCompleter>
#include <QTimer>
#include <QLineEdit>

ECBProductos::ECBProductos(QWidget *parent) :
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

    _mapa_pos_ids = new QMap<int, int>();
    _mapa_pos_codigo = new QMap<QString, int>();

    QTimer timer;
    timer.singleShot( 900, this, SLOT( inicializar() ) );
}


ECBProductos::~ECBProductos()
{
    delete _mapa_pos_ids;
    delete _mapa_pos_codigo;
    _mapa_pos_ids = 0;
    _mapa_pos_codigo = 0;
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
    if( cola.exec( "SELECT id, codigo, nombre FROM producto" ) ) {
        int pos = 0;
        while( cola.next() ) {
            // Pos = currentIndex();
            // id_producto = _mapa_pos_ids
            // codigo = _mapa_pos_codigo
            this->insertItem( pos, cola.record().value(2).toString(), cola.record().value(0).toInt() );
            this->_mapa_pos_codigo->insert( cola.record().value(1).toString(), pos );
            this->_mapa_pos_ids->insert   ( cola.record().value(0).toInt(), pos    );
            pos++;
        }
        if( pos == 0 ) {
            qWarning( "No hay ningun producto para cargar!" );
            this->lineEdit()->setText( "No hay productos cargados..." );
        }
        this->setEnabled( true );
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
        emit agregarProducto();
        return;
    }
    QMap<QString, int>::const_iterator i =  this->_mapa_pos_codigo->find( buscar );
    if( i != this->_mapa_pos_codigo->end() ) {
        this->setCurrentIndex( i.value() );
        emit agregarProducto();
        return;
    }
    return;
}
