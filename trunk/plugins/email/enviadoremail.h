#ifndef ENVIADOREMAIL_H
#define ENVIADOREMAIL_H

#include <QThread>
#include <QSqlDatabase>
#include "email.h"

class EnviadorEmail : public QThread
{
    Q_OBJECT
public:
    EnviadorEmail( QString usuario,
                   QString contrasena,
                   QString direccion,
                   Email *parent,
                   QSqlDatabase db );
    void terminarEjecucion();

signals:
    void status( const QString &texto );

public slots:
    void enviarEmail();

private:
    QSqlDatabase db;
    QString _usuario;
    QString _contrasena;
    QString _host;

};

#endif // ENVIADOREMAIL_H
