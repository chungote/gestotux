#ifndef MCREDENCIALES_H
#define MCREDENCIALES_H

#include <QSqlRelationalTableModel>

class MCredenciales : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit MCredenciales( QObject *parent = 0, bool relaciones = true );

};

#endif // MCREDENCIALES_H
