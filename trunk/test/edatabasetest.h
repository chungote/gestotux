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
#include <QSettings>

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
    void vaciarTabla( QString nombre );
    void borrarTabla( QString nombre );

    void generarTablas();
    void borrarTablas();
    void iniciarTablas();
    void vaciarTablas();

protected:
    QStringList tablas;

private:
    /*!
     * \brief mapa
     * Mapa de dependencia entre tablas
     */
    QMap<QString, QList<QString> > mapa;

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
        qDebug() << "Usando base de datos: " << QCoreApplication::applicationDirPath().append( QDir::separator() ).append( "test.database" );
     QFile *base = new QFile( QCoreApplication::applicationDirPath().append( QDir::separator() ).append( "test.database" ).toLocal8Bit() );
     if( !base->open( QIODevice::ReadOnly ) )
     {
         qDebug() << "Creando base de datos...";
         QSqlDatabase DB = QSqlDatabase::addDatabase("QSQLITE");
         DB.setDatabaseName( QCoreApplication::applicationDirPath().append( QDir::separator() ).append( "test.database" ) );
         if( !DB.open() ) {
             qDebug() << "Ultimo error: " << DB.lastError().text();
             abort();
         }
      }
      delete base;
      QSqlDatabase DB = QSqlDatabase::addDatabase( "QSQLITE" );
      DB.setDatabaseName( QCoreApplication::applicationDirPath().append( QDir::separator() ).append( "test.database" ) );
      if( !DB.open() )
      {
              qDebug() << "Ultimo error: " << DB.lastError().text();
              abort();
      } else {
          qDebug( "Base de datos SQLite abierta correctamente" );
      }
     } else {
        qFatal( "No se puede encontrar el driver de SQLITE" );
    }

    //////////////////////////////////////////////////////////////////////////////////////
    // Cargo las dependencias
    QDir path( QCoreApplication::applicationDirPath() );
    path.cdUp();
    if( !path.cd( "sql" ) ) {
        qFatal( "No se puede entrar al directorio sql!" );
    }
    QSettings dep( path.filePath( "dependences.ini" ), QSettings::IniFormat );
    if( dep.status() != QSettings::NoError ) {
        qDebug() << "Error al cargar las preferencias!";
    } else {
        qDebug() << "Cargadas dependencias desde " << path.filePath( "dependences.ini" );
    }
    dep.beginGroup( "Dependences" );
    QStringList lista_tablas = dep.childKeys();
    qDebug() << lista_tablas;
    foreach( QString tabla, lista_tablas ) {
        qDebug() << "Dependencia de " << tabla << " -> " << dep.value( tabla ).toStringList();
        mapa.insert( tabla, dep.value( tabla ).toStringList() );
    }

}

/*!
 * \brief EDatabaseTest::~EDatabaseTest
 */
EDatabaseTest::~EDatabaseTest() {

}

/*!
 * \brief EDatabaseTest::generarTabla
 * \param nombre
 */
void EDatabaseTest::generarTabla( QString nombre )
{

    // Ejecutar los nombres de tablas que dependan de esta
    if( mapa.find( nombre ) == mapa.end() ) {
        // Agrego la tabla porque no hay dependencias
        this->tablas.append( nombre );
        return;
    }

    // busco las depenencias
    this->buscarDepenencias( nombre );
}

/*!
 * \brief EDatabaseTest::vaciarTabla
 * \param nombre
 */
void EDatabaseTest::vaciarTabla( QString nombre )
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
        if( cola.exec( "DROP TABLE " + nombre ) ) {
            _lista_tablas.removeAll( nombre );
        }
    } else {
        qDebug() << "La tabla " << nombre << " no está inicializada. - No se borrará.";
    }
}

void EDatabaseTest::generarTablas()
{
    foreach( QString t, this->tablas ) {
        this->generarTabla( t );
    }
}

void EDatabaseTest::borrarTablas()
{
    foreach( QString t, this->tablas ) {
        this->borrarTabla( t );
    }
}

void EDatabaseTest::iniciarTablas()
{
    foreach( QString t, this->tablas ) {
        this->iniciarTabla( t );
    }
}

void EDatabaseTest::vaciarTablas()
{
    foreach( QString t, this->tablas ) {
        this->vaciarTabla( t );
    }
}

/*!
 * \brief EDatabaseTest::buscarDepenencias
 * \param nombre
 */
void EDatabaseTest::buscarDepenencias( QString nombre )
{

    // Verifico a ver si existen las dependencias
    QList<QString> lista = mapa.value( nombre );
    foreach( QString tabla, lista ) {
        if( tablas.contains( tabla ) ) {
            continue;
        } else {
            this->buscarDepenencias( tabla );
        }
    }
}

/*!
 * \brief EDatabaseTest::iniciarTabla
 * \param nombre
 */
void EDatabaseTest::iniciarTabla( QString nombre ) {
    // Busco si no está ya inicializada
    if( !_lista_tablas.contains( nombre ) ) {
        qDebug() << "Inicializando tabla " << nombre;
        QDir *path = new QDir( QCoreApplication::applicationDirPath() );
        path->cdUp();
        path->cd( "sql" );
        path->cd( QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).driverName() );
        // Ejecuto la lista de archivos
        if( path->exists( nombre + ".sql" ) )
        {
               QString nombre_archivo = nombre;
               nombre_archivo.append( ".sql" );
               QFile archivo( path->filePath( nombre_archivo ) );
               if( archivo.open( QIODevice::ReadOnly | QIODevice::Text ) )
               {
                       QStringList cadenas = QString( archivo.readAll() ).split( ";" );
                       QString cadena; QSqlQuery cola;
                       foreach( cadena, cadenas )
                       {
                               //qDebug() << cadena;
                               if( !cadena.isEmpty() && !cadena.isNull() ) {
                                       if( !cola.exec( cadena ) )
                                       {
                                               qWarning() << cadena;
                                               qWarning() << " Fallo...." << cola.lastError().text();
                                               return;
                                       }
                               }
                       }
                       archivo.close();
                       qDebug() << "Tabla " << nombre << " inicializada.";
                       _lista_tablas.append( nombre );
               }
               else
               {
                   qDebug() << "Error al abrir el archivo: " << nombre_archivo;
               }
        }
        else
        {
            qDebug() << "No se pudo generar la tabla -" << nombre << "-. No se encontro el archivo: " << path->filePath( nombre + ".sql" );
        }

    } else {
        qDebug() << "No se puede encontrar el archivo de inicialización para la tabla -> " << nombre << " <- No se creará";
    }
}

#endif // EDATABASETEST_H