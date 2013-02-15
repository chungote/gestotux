#ifndef FEEDBACKSENDER_H
#define FEEDBACKSENDER_H

#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

class FeedbackSender : public QThread
{
    Q_OBJECT
public:
    FeedbackSender( QObject *parent = 0 );

    void run();

private slots:
    void respuesta( QNetworkReply * );

private:
    /*!
     * Administrador de red
     */
     QNetworkAccessManager *manager;

     /*!
      * Puntero de request
      */
     QNetworkRequest *req;

    /*!
     * Lista de solicitudes de red -  envio de colas
     */
     QNetworkReply *lista;

    /*!
     * Apuntador de archivo
     */
     QFile *f;

    /*!
     * Contador de reintentos
     */
     int reintentos;

};

#endif // FEEDBACKSENDER_H
