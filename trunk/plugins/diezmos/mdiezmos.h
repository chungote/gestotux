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
    ~MDiezmos();

    int columnCount( const QModelIndex &parent ) const;
    QVariant data( const QModelIndex &idx, int role ) const;

private:
    QVector<double> *saldos;
    
};

#endif // MDIEZMOS_H
