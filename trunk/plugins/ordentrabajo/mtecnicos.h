#ifndef MTECNICOS_H
#define MTECNICOS_H

#include <QSqlTableModel>

class MTecnicos : public QSqlTableModel
{
    Q_OBJECT
public:
    MTecnicos( QObject *parent = 0 );

    static bool existe( const QString nombre );
    bool tieneDatosRelacionados( const int id_tecnico );
};

#endif // MTECNICOS_H
