#ifndef MEQUIPAMIENTO_H
#define MEQUIPAMIENTO_H

#include <QSqlRelationalTableModel>
#include <QDate>

class MEquipamiento : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    MEquipamiento( QObject *parent = 0 );

    QVariant data(const QModelIndex &item, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    static bool tieneDatosRelacionados( const int id_equipamiento );

    bool eliminarConRelacionados( const int id_equipamiento );
    bool darDeBaja( const int id_equipamiento, const QString razon, QDateTime fecha = QDateTime::currentDateTime() );
    bool darReAlta( const int id_equipamiento, const QString razon, QDateTime fechahora = QDateTime::currentDateTime() );
};

#endif // MEQUIPAMIENTO_H
