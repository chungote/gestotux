#include "feedbacksender.h"

#include "preferencias.h"
#include <QFile>
#include <QApplication>
#include <QDir>
#include <QMessageBox>

FeedbackSender::FeedbackSender(QObject *parent) :
QThread(parent)
{
    reintentos = 4;
}

/**
 * @brief FeedbackSender::run
 * Codigo que verifica la existencia de un error previo y envía el error al servidor de gestotux
 * @author Esteban Zeller
 */
void FeedbackSender::run()
{
    if( reintentos == 0 ) {
        qDebug( "Feedback: Numero de reintentos maximo alcanzados" );
        exit( 2 );
    }

    preferencias *p = preferencias::getInstancia();
    p->inicio();
    bool ultimo_error = p->value( "lastError", false ).toBool();

    if( ultimo_error == false ) {
        qDebug( "Feedback: No hubo error en el ultimo cierre.");
        exit( 0 ); // No hubo error en el ultimo cierre
    }
    p->beginGroup( "Preferencias" );
    p->beginGroup( "Feedback" );
    bool enviar = p->value( "enviar_reporte", true ).toBool();

    if( !enviar ) {
        exit( 0 ); // No quiere enviar los datos
    }

    // Abro el archivo y genero el encabezado para que llegue al servidor
    if( !QFile::exists(  QApplication::applicationDirPath().append( QDir::separator() ).append( "debugOld.txt" ) ) ) {
        qDebug( "Feedback: No se pudo enviar el archivo de errores ya que no existe la copia anterior" );
        exit( 1 );
    }

    QFile *f = new QFile( QApplication::applicationDirPath().append( QDir::separator() ).append( "debugOld.txt" ) );
    if( ! f->open( QIODevice::ReadOnly ) ) {
        qDebug( "Feedback: Error al intentar abrir el archivo debugOld.txt como solo lectura" );
        exit( 1 );
    }

    manager = new QNetworkAccessManager( this );
    connect( manager, SIGNAL( finished( QNetworkReply* ) ), this, SLOT( respuesta( QNetworkReply* ) ) );

    QUrl url( p->value( "url_envio", "http://www.gestotux.com.ar/feedback/envio" ).toString() );
    p->inicio();
    p->beginGroup( "carga" );
    url.addQueryItem( "cliente", p->value( "pluginInfo", "default" ).toString() );
    p->endGroup(); p = 0;

    req = new QNetworkRequest( url );

    // Envio el archivo
    lista = manager->post( *req, f );

    exec();
}

/**
 * \fn FeedbackSender::respuesta( QNetworkReply *resp )
 * \param resp Respuesta recibida del servidor
 * Slot llamado cuando se obtiene la respuesta
 **/
void FeedbackSender::respuesta( QNetworkReply *resp )
{
    if( resp->error() != QNetworkReply::NoError ) {
        qDebug( "Error de red al enviar informe de errores" );
        qDebug( resp->errorString().toLocal8Bit() );
        // Intento nuevamente más tarde hasta n veces
        reintentos--;
        qDebug( QString( "Numero de reintentos faltantes: %1" ).arg( reintentos ).toLocal8Bit() );
        sleep( 10000 );
    } else if( resp->isFinished() ) {
        QApplication::processEvents();
        resp->deleteLater();
        qDebug( "Feedback: Envio de error completado." );
        f->close();
        f->remove();
        QMessageBox::information( 0, "Correcto", "El informe de errores de el ultimo uso del programa se envió correctamente." );
        exit( 0 );
   }
}

