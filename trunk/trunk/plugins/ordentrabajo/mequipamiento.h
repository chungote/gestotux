#ifndef MEQUIPAMIENTO_H
#define MEQUIPAMIENTO_H

#include <QSqlRelationalTableModel>

class MEquipamiento : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    MEquipamiento( QObject *parent = 0 );

    QVariant data(const QModelIndex &item, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    static bool tieneDatosRelacionados( const int id_equipamiento );
};

#endif // MEQUIPAMIENTO_H
