#ifndef MTECNICOS_H
#define MTECNICOS_H

#include <QSqlTableModel>

class MTecnicos : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit MTecnicos(QObject *parent = 0);
    
};

#endif // MTECNICOS_H
