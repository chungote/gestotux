#ifndef MVPAGOS_H
#define MVPAGOS_H

#include <QSqlRelationalTableModel>
#include <QDate>

class MVPagos : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit MVPagos(QObject *parent = 0);
    QVariant data(const QModelIndex& item, int role) const;
};

#endif // MVPAGOS_H
