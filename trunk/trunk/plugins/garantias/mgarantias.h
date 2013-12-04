#ifndef MGARANTIAS_H
#define MGARANTIAS_H

#include <QSqlRelationalTableModel>

class MGarantias : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit MGarantias(QObject *parent = 0);
    void relacionar();
    QVariant data(const QModelIndex &item, int role) const;
    
signals:
    
public slots:
    
};

#endif // MGARANTIAS_H
