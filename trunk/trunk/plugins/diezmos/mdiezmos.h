#ifndef MDIEZMOS_H
#define MDIEZMOS_H

#include <QSqlTableModel>
#include <QVector>

/*!
 * \brief The MDiezmos class
 * \author Esteban Zeller
 */
class MDiezmos : public QSqlTableModel
{
    Q_OBJECT
public:
    MDiezmos( QObject *parent = 0 );

    int columnCount( const QModelIndex &parent ) const;
    QVariant data( const QModelIndex &idx, int role ) const;

private:
    QVector<double> saldos;

    void recalcularSaldos( const double valor, const int fila, const int columna ) const;
    
};

#endif // MDIEZMOS_H
