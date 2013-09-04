#ifndef MEQUIPAMIENTO_H
#define MEQUIPAMIENTO_H

#include <QSqlRelationalTableModel>
#include <QDate>
#include <QSqlRecord>

class MEquipamiento : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    MEquipamiento( QObject *parent = 0 );

    QVariant data(const QModelIndex &item, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool existe( const int id_equipamiento );
    void cargarDatos( const int id_equipamiento );

    QString descripcion()   { return _datos.value("descripcion").toString();   }
    QString marca()         { return _datos.value("marca").toString();         }
    QString modelo()        { return _datos.value("modelo").toString();        }
    QString numeroSerie()   { return _datos.value("num_serie").toString();     }
    QString observaciones() { return _datos.value("observaciones").toString(); }
    bool enGarantia();

    static bool tieneDatosRelacionados( const int id_equipamiento );

    bool eliminarConRelacionados( const int id_equipamiento );
    bool darDeBaja( const int id_equipamiento, const QString razon, QDateTime fecha = QDateTime::currentDateTime() );
    bool darReAlta( const int id_equipamiento, const QString razon, QDateTime fechahora = QDateTime::currentDateTime() );

private:
    QSqlRecord _datos;

};

#endif // MEQUIPAMIENTO_H
