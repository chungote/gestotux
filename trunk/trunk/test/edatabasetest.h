#ifndef EDATABASETEST_H
#define EDATABASETEST_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QString>
#include <QFile>
#include <QDir>
#include <QCoreApplication>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QFile>
#include <QSqlError>

/*!
 * \brief The EDatabaseTest class
 */
class EDatabaseTest
{
public:
    EDatabaseTest();
    ~EDatabaseTest();
    void generarTabla( QString nombre );
    void iniciarTabla( QString nombre );
    void limpiarTabla( QString nombre );
    void borrarTabla( QString nombre );

private:
    /*!
     * \brief mapa
     * Mapa de dependencia entre tablas
     */
    QMap<QString, QList<QString> > mapa;
    /*!
     * \brief archivos
     * Mapa de en que archivo se encuentra las tablas
     */
    QMap<QString, QString> archivos;
    /*!
     * \brief _lista_archivos
     * Lista de archivos a ejecutar
     */
    QList<QString> *_lista_archivos;

    /*!
     * \brief _lista_tablas
     * Lista de tablas inicializadas
     */
    QList<QString> _lista_tablas;

    void buscarDepenencias( QString nombre );
};

/*!
 * \brief EDatabaseTest::EDatabaseTest
 * \param parent
 */
EDatabaseTest::EDatabaseTest()
{
    if( QSqlDatabase::isDriverAvailable( "QSQLITE" ) )
    {
     QFile *base = new QFile( QCoreApplication::applicationDirPath().append( QDir::separator() ).append( "test.database" ).toLocal8Bit() );
     if( !base->open( QIODevice::ReadOnly ) )
     {
       qDebug( "-------------------------------------------------" );
       qDebug( "El archivo de Base de datos no existe!");
       qDebug( "-------------------------------------------------" );
              QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE");
              DB.setDatabaseName( QCoreApplication::applicationDirPath().append( QDir::separator() ).append( "test.database" ) );
              if( !DB.open() )
              {
                      qDebug() << "Ultimo error: " << DB.lastError().text();
                      abort();
              }
      }
      else
      {
              // Aunque exista chequeo que no sea de tam 0
              if( base->size() <= 0 )
              { qFatal( "Error! El archivo de db tiene menos o es igual a 0 bytes " ); }
      }
      delete base;
      QSqlDatabase DB = QSqlDatabase::addDatabase( "QSQLITE" );
      DB.setDatabaseName( QCoreApplication::applicationDirPath().append( QDir::separator() ).append( "test.database" ) );
      if( !DB.open() )
      {
              qDebug() << "Ultimo error: " << DB.lastError().text();
              abort();
      } else { qDebug( "Base de datos SQLite abierta correctamente" ); }
     } else {
        qFatal( "No se puede encontrar el driver de SQLITE" );
    }
    // Inicializo el listado de archivos
    _lista_archivos = new QList<QString>();

}

/*!
 * \brief EDatabaseTest::~EDatabaseTest
 */
EDatabaseTest::~EDatabaseTest() {
    delete _lista_archivos;
    _lista_archivos = 0;
}

/*!
 * \brief EDatabaseTest::generarTabla
 * \param nombre
 */
void EDatabaseTest::generarTabla( QString nombre )
{
    // Ejecutar los nombres de tablas que dependan de esta
    if( mapa.find( nombre ) == mapa.end() ) {
        qFatal( "No se encuentra la tabla necesaria" );
        return;
    }

    // busco las depenencias
    this->buscarDepenencias( nombre );

    // Ejecuto la lista de archivos

    foreach( QString archivo, *_lista_archivos ) {
        if( QFile::exists(  QCoreApplication::applicationDirPath().append( QDir::separator() )+archivo+"."+QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).driverName()+".sql" ) )
        {
               QString narchivo = ":/sql/";
               narchivo.append( archivo );
               narchivo.append( "." );
               narchivo.append( QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).driverName() );
               narchivo.append( ".sql" );
               QFile archivo( narchivo );
               if( archivo.open( QIODevice::ReadOnly | QIODevice::Text ) )
               {
                       QStringList cadenas = QString( archivo.readAll() ).split( ";" );
                       QString cadena; QSqlQuery cola;
                       foreach( cadena, cadenas )
                       {
                               //qDebug() << cadena;
                               if( cadena.isEmpty() || cadena.isNull() ) {
                                       qDebug() << "Cadena vacia, salteandola...";
                                   } else {
                                       if( !cola.exec( cadena ) )
                                       {
                                               qDebug() << cadena;
                                               qDebug() << " Fallo...." << cola.lastError().text();
                                               return;
                                       }
                                       else
                                       { qDebug( "Ok" ); }
                                   }
                       }
               }
               else
               { qDebug() << "Error al abrir el archivo: " << narchivo; }
        }
        else
        { qDebug() << "No se pudo generar las tablas del plugin " << archivo << ". No se encontro el archivo: :/sql/" << archivo << "." << QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).driverName() << ".sql"; }
    }
}

/*!
 * \brief EDatabaseTest::limpiarTabla
 * \param nombre
 */
void EDatabaseTest::limpiarTabla( QString nombre )
{
    if( _lista_tablas.contains( nombre ) ) {
        QSqlQuery cola;
        cola.exec( "TRUNCATE TABLE " + nombre );
    } else {
        qDebug() << "La tabla " << nombre << " no está inicializada! - No se truncara.";
    }
}

/*!
 * \brief EDatabaseTest::borrarTabla
 * \param nombre
 */
void EDatabaseTest::borrarTabla( QString nombre )
{
    if( _lista_tablas.contains( nombre ) ) {
        QSqlQuery cola;
        cola.exec( "DROP TABLE " + nombre );
    } else {
        qDebug() << "La tabla " << nombre << " no está inicializada. - No se borrará.";
    }
}

/*!
 * \brief EDatabaseTest::buscarDepenencias
 * \param nombre
 */
void EDatabaseTest::buscarDepenencias( QString nombre )
{
    // Agrego el archivo actual
    _lista_archivos->append( archivos.value( nombre ) );

    // Verifico a ver si existen las dependencias
    QList<QString> lista = mapa.value( nombre );
    foreach( QString tabla, lista ) {
        if( _lista_archivos->contains( archivos.value( nombre ) ) ) {
            continue;
        } else {
            this->buscarDepenencias( nombre );
        }
    }
}

/*!
 * \brief EDatabaseTest::iniciarTabla
 * \param nombre
 */
void EDatabaseTest::iniciarTabla( QString nombre ) {
    // Busco si existe la tabla necesaria
    if( archivos.contains( nombre ) ) {
        /// @TODO: Agregar inicialización de tabla aquí
        _lista_tablas.append( nombre );
    } else {
        qDebug() << "No se puede encontrar el archivo de inicialización para la tabla -> " << nombre << " <- No se creará";
    }
}

#endif // EDATABASETEST_H