#ifndef MVPLANCUOTA_H
#define MVPLANCUOTA_H

#include <QSqlTableModel>

class MVPlanCuota : public QSqlTableModel
{
    Q_OBJECT
public:
    explicit MVPlanCuota( QObject *parent = 0 );
    
};

#endif // MVPLANCUOTA_H
