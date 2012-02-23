#include "ecbpaises.h"

ECBPaises::ECBPaises(QWidget *parent) :
    QComboBox(parent)
{
    this->setObjectName( "SelectorPaises" );
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

    _id_pais = -1;
    QTimer timer;
    timer.singleShot( 900, this, SLOT( inicializar() ) );
}

void ECBPaises::setearFiltro( const QString f ) {
    this->filtro = f;
    // Hago la carga diferida
    QTimer timer;
    timer.singleShot( 900, this, SLOT( inicializar() ) );
}

ECBPaises::~ECBPaises()
{
    delete ids;
}

/*!
 * \fn ECBPaises::inicializar()
 * Funcion que carga los datos y setea todo como para su uso
 */
void ECBPaises::inicializar()
{
    // Cargo los datos del modelo
    QSqlQuery cola;
    // Limpio el combobox para que no cargue datos repetidos
    this->clear();
    //qDebug( QString( "SELECT id_pais, nombre FROM paises %1 ORDER BY nombre ASC" ).arg( filtro ).toLocal8Bit() );
    if( cola.exec( QString( "SELECT id_pais, nombre FROM paises %1 ORDER BY nombre ASC" ).arg( filtro ) ) ) {
        int pos = 0;
        while( cola.next() ) {
            this->insertItem( pos, cola.record().value(1).toString() );
            ids->insert( pos, cola.record().value(0).toInt() );
            pos++;
        }
        if( pos == 0 ) {
            qWarning( "No hay ningun pais para cargar!" );
            this->lineEdit()->setText( "No hay paises cargados..." );
            this->setEnabled( false );
            return;
        }
        this->setEnabled( true );
        this->setCurrentIndex( this->ids->indexOf( _id_pais ) );
    } else {
        qWarning( "Error al intentar ejecutar la cola para cargar los paises" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
    }
}

/*!
 * \fn ECBPaises::idActual()
 * Devuelve el id de cliente actual
 */
int ECBPaises::idActual()
{   return ids->value( this->currentIndex() );    }

/*!
 * \fn ECBPaises::setearId( cons int id_cliente )
 * Setea el identificador del pais
 */
void ECBPaises::setearId( int id_pais )
{
    if( id_pais <= 0 ) { return; }
    if( this->ids->isEmpty() ) {
        QTimer timer;
        this->_id_pais = id_pais;
        timer.singleShot( 900, this, SLOT( setearIdRetrasado() ) );
        return;
    }
    int pos = this->ids->indexOf( id_pais );
    if( pos < 0 ) {
        qDebug( QString( "ECBPaises::setearId: Error buscando el id de paises desde cbpaises: id = %1" ).arg( id_pais ).toLocal8Bit() );
        this->setCurrentIndex( -1 );
    } else {
        this->setCurrentIndex( pos );
    }
}

void ECBPaises::setearIdRetrasado()
{
    if( _id_pais <= 0 ) { return; }
    int pos = this->ids->indexOf( _id_pais );
    if( pos < 0 ) {
        qDebug( QString( "ECBPaises::setearIdRetrasado: Error buscando el id de paises desde cbpaises: id = %1" ).arg( _id_pais ).toLocal8Bit() );
        this->setCurrentIndex( -1 );
    } else {
        this->setCurrentIndex( pos );
    }
}

/*!
 * \fn ECBPaises::verificarExiste()
 * Ve si el numero de cliente o texto buscado existe en la lista. Si existe lo coloca como item actual.
 */
void ECBPaises::verificarExiste()
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
            QMessageBox::information( this, "No encontrado", "El pais o codigo de pais buscado no existe." );
        }
    }
    return;
}
