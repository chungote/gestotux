#ifndef MGARANTIAS_H
#define MGARANTIAS_H

#include <QSqlRelationalTableModel>
#include <QDate>

class MGarantias : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit MGarantias(QObject *parent = 0);
    void relacionar();
    QVariant data( const QModelIndex &item, int role ) const;

    bool darDeBaja( const int id_garantia, const QString razon, const QDate fecha = QDate::currentDate() );
        
};

#endif // MGARANTIAS_H
