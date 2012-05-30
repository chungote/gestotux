/***************************************************************************
 *   Copyright (C) 2006 by Esteban Zeller & Daniel Sequeira		   *
 *   juiraze@yahoo.com.ar  - daniels@hotmail.com			   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "ebackupremoto.h"
#include "preferencias.h"

#include <QStringList>
#include <QByteArray>
#include <QString>
#include <QVariant>
#include <QSqlDatabase>
#include <QPushButton>
#include <QFrame>
#include <QProgressBar>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QTabWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QDate>
#include <QProgressDialog>
#include <QTabWidget>
#include <QSqlDriver>

#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>

#include "eenviobackup.h"
#include "json.h"

using namespace QtJson;

EBackupRemoto::EBackupRemoto( QWidget* parent )
: EVentana( parent ), Ui_FormBackupRemotoBase()
{
 setupUi(this);
 this->setAttribute( Qt::WA_DeleteOnClose );
 setObjectName( "backup" );
 setWindowTitle( "Copia de Seguridad" );
 setWindowIcon( QIcon( ":/imagenes/backup.png" ) );
 PBProgreso->setValue( 0 );
 PBEnviado->setValue( 0 );
 LDebug->setText( "Presione Iniciar para comenzar" );

 ActCerrar = new QAction( "Cerrar", this );
 ActCerrar->setStatusTip( "Cierra la ventana y cancela cualquier backup que se este realizando" );
 ActCerrar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
 connect( ActCerrar, SIGNAL( triggered() ), this, SLOT( close() ) );

 ActIniciar = new QAction( "Iniciar", this );
 ActIniciar->setStatusTip( "Inincia la generaciÃ³n de los backups" );
 ActIniciar->setIcon( QIcon( ":/imagenes/next.png" ) );
 connect( ActIniciar, SIGNAL( triggered() ), this, SLOT( iniciar() ) );

 ActDetener = new QAction( "Detener", this );
 ActDetener->setStatusTip( QString::fromUtf8( "Detiene la ejecución actual del backup" ) );
 ActDetener->setIcon( QIcon( ":/imagenes/stop.png" ) );
 connect( ActIniciar, SIGNAL( triggered() ), this, SLOT( detener() ) );
 connect( this, SIGNAL( cambiarDetener( bool ) ), ActDetener, SLOT( setEnabled( bool ) ) );

 emit cambiarDetener( false );

 addAction( ActIniciar );
 addAction( ActDetener );
 addAction( ActCerrar );

 ChBBaseDatos->setCheckState( Qt::Checked );

 Pestanas->setTabIcon( 0, QIcon( ":/imagenes/backup1.png" ) );
 Pestanas->setTabIcon( 1, QIcon( ":/imagenes/backup2.png" ) );
 Pestanas->widget( 0 )->setObjectName( "crearBackup" );
 Pestanas->widget( 1 )->setObjectName( "restaurarBackup" );
 Pestanas->setCurrentIndex( 0 );
}


EBackupRemoto::~EBackupRemoto()
{}

/*!
 *   \fn EBackupRemoto::iniciar()
 *	Realiza todo el proceso de creacion del backup.
 */
void EBackupRemoto::iniciar()
{
 // Ver en que pestaña esta
 if( Pestanas->currentIndex() == 0 )
 {
  generarBackup();
 }
 else if( Pestanas->currentIndex() == 1 )
 {
  restaurarBackup();
  return;
 }
 else
 {
  qWarning( "Pestaña desconocida" );
 }
}

/*!
    \fn EBackupRemoto::generar_db( bool estructura )
        Funcion que hace la obtencion de los datos de la base de datos y los prepara para la compresion.
        @param estructura Hacer backup de la estructura de la db
        @return Verdadero si no existieron errores, falso en caso contrario
 */
bool EBackupRemoto::generar_db( bool estructura )
{
 QSqlDriver *db = QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).driver();
 ////////////////////////////////////////////////////////////////////////
 QStringList tablas = QSqlDatabase::database().tables();
 int total = 0;
 QString tabla; QSqlQuery cola;
 foreach( tabla, tablas )
 {
        //Calculo para la barra
        cola.exec( QString("SELECT COUNT(*) FROM %1" ).arg( tabla ) );
        if( cola.next() )
        {
                total += cola.record().value(0).toInt();
        }
 }
 total += tablas.size();

 // Hago la conexion
 manager = new QNetworkAccessManager( this );
 connect( manager, SIGNAL( finished( QNetworkReply* ) ), this, SLOT( respuesta( QNetworkReply* ) ) );

 preferencias *p = preferencias::getInstancia();
 p->beginGroup( "Preferencias" );
 p->beginGroup( "BackupRemoto" );
 QUrl url( p->value( "url_envio", "http://trafu.np-ip.org/TRSis/backup/envio" ).toString() );
 url.addQueryItem( "num_cliente", p->value( "numero_cliente", 1 ).toString() );
 url.addQueryItem( "id_servicio_backup", p->value( "id_servicio_backup", 1 ).toString() );
 url.addQueryItem( "driver", QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).driverName() );
 p->endGroup(); p->endGroup(); p = 0;

 // Envio el saludo de inicio
 QUrl envio = url;
 envio.addQueryItem( "inicio", "0"  );

 QNetworkRequest req( envio );
 req.setHeader( QNetworkRequest::ContentTypeHeader, "application/octet-stream" );
 lista.append( manager->post( req, envio.encodedQuery() ) );

 // Preparo todo para que pueda enviar datos
 req.setUrl( url );

 PBProgreso->setRange( 0, total );
 PBEnviado->setRange( 0, total );

 int pos = 0;

 foreach( tabla, tablas )
 {
        PBProgreso->setValue( PBProgreso->value() + 1 );
        cola.exec( QString( "SELECT * FROM %1" ).arg( tabla ) );
        while( cola.next() & _continuar )
        {
            QUrl url2 = url;
            url2.addQueryItem( "pos", QString::number( pos ) );
            url2.addQueryItem( "cola", db->sqlStatement( QSqlDriver::InsertStatement, tabla, cola.record(), false ) );

            lista.append( manager->post( req, url2.encodedQuery() ) );

            QApplication::processEvents();

            PBProgreso->setValue( PBProgreso->value() + 1 );
            pos++;
        }
        if( _continuar == false ) {
            url.addQueryItem( "cancelar", "0" );
            req.setUrl( url );
            manager->post( req, url.encodedQuery() );
            lista.clear();
        }
  }
 //////////////////////////////////////////////////////////////////////////////////////////////////////////
 PBProgreso->setValue( PBProgreso->value() + 1 );
 LDebug->setText( "Listo backup de Base de datos.. Esperando envios..." );
 return true;
}

void EBackupRemoto::respuesta( QNetworkReply *resp ) {
    if( resp->error() != QNetworkReply::NoError ) {
        QMessageBox::warning( this, "Error", resp->errorString().toLocal8Bit() );
    } else  if( resp->isFinished() ) {
        QByteArray cont( resp->readAll() );
        QApplication::processEvents();
        bool ok = false;
        QVariantMap mapa = Json::parse( cont, ok ).toMap();
        if( !ok ) {
            QMessageBox::warning( this, "Error", "Error de interpretación de los datos descargados. Intente nuevamente." );
            qDebug( cont );
            return;
        }
        if( mapa["error"].toBool() ) {
            QMessageBox::warning( this, "Error", QString( "Error: %1" ).arg( mapa["texto"].toString() ).toLocal8Bit() );
            _continuar = false;
            emit cambiarDetener( false );
            return;
        } else {
            lista.removeOne( resp );
            PBEnviado->setValue( PBEnviado->value() + 1 );
            if( lista.isEmpty() ) {
                 preferencias *p = preferencias::getInstancia();
                 p->beginGroup( "Preferencias" );
                 p->beginGroup( "BackupRemoto" );
                 QUrl url( p->value( "url_envio", "http://trafu.np-ip.org/TRSis/backup/envio" ).toString() );
                 url.addQueryItem( "num_cliente", p->value( "numero_cliente", 1 ).toString() );
                 url.addQueryItem( "id_servicio_backup", p->value( "id_servicio_backup", 1 ).toString() );
                 url.addQueryItem( "driver", QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).driverName() );
                 p->endGroup(); p->endGroup(); p = 0;
                 url.addQueryItem( "fin", "0" );
                 QNetworkRequest req( url );
                 req.setHeader( QNetworkRequest::ContentTypeHeader, "application/octet-stream" );
                 manager->post( req, url.encodedQuery() );
                _continuar = false;
                emit cambiarDetener( false );
            }
        }
    }
}


/*!
    \fn EBackupRemoto::detener()
     Slot llamado para detener la generacion del backup
 */
void EBackupRemoto::detener()
{  _continuar = false; }


/*!
    \fn EBackupRemoto::generarBackup()
 */
void EBackupRemoto::generarBackup()
{
  emit cambiarDetener( true );
 _continuar = true;
 if( !ChBBaseDatos->isChecked() && !ChBConfirugacion->isChecked() )
 {
  QMessageBox::information( this, "Seleccione opciones" , "Por favor, seleccione una opcion para iniciar la copia de seguridad" );
  emit cambiarDetener( false );
  return;
 }
 LDebug->setText( "Iniciando" );
 if( ChBBaseDatos->isChecked() )
 {
  LDebug->setText( "Generando backup de Base de datos" );
  if( !generar_db( CkBEstructura->isChecked() ) )
  {
   qDebug( "Error al intentar generar la copia de seg de la db" );
   emit cambiarDetener( false );
   return;
  }
 }
 if( ChBConfirugacion->isChecked() )
 {
  LDebug->setText( "Generando backup de Configuracion del programa" );
  /*if( !generar_config() )
  {
   qDebug( "Error al generar el backup de la config" );
   emit cambiarDetener( false );
   return;
  }*/
 }
 else
 {
  PBProgreso->setValue( PBProgreso->maximum() );
 }
 emit cambiarDetener( false );
}


/*!
    \fn EbackupRemoto::restaurarBackup()
 */
void EBackupRemoto::restaurarBackup()
{
 emit cambiarDetener( true );
 _continuar = true;
 return;
}

/*!
    \fn EbackupRemoto::ejecutarColas( QStringList colas )
    Metodo utilizado para ejecutar las consultas SQl definidas en @param colas en la base de datos.
    Todas las consultas se realizan dentro de una transacción, y de fallar cualquiera de las consultas, se realiza un rollback.
    @param colas Lista de QString con las consultas SQL dentro.
    @return Verdadero si todas las consultas fueron ejecutadas correctamente.
 */
bool EBackupRemoto::ejecutarColas( QStringList colas )
{
 bool estado = true;
 QSqlQuery *cola = new QSqlQuery();
 while( colas.size() > 0  && estado == true )
 {
  if( cola->exec( colas.at( 0 ) ) )
  {
    colas.removeFirst();
  }
  else
  {
        qWarning( qPrintable( cola->lastError().text() + ". Cola: " + cola->lastQuery() ) );
        estado = false;
  }
 }
 delete cola;
 if( estado == false )
 {
  QSqlDatabase::database().rollback();
 }
 else
 {
  QSqlDatabase::database().commit();
 }
 return estado;
}