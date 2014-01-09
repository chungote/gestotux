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
    bool estaActiva( const int id_garantia );
    bool eliminar( const int id_garantia );

    int agregarGarantia( const int id_cliente,
                         const QString texto_producto,
                         const QDate fecha_inicio,
                         const QDate fecha_fin,
                         const int id_equipamiento,
                         const int id_producto,
                         const int id_factura );
        
};

#endif // MGARANTIAS_H
