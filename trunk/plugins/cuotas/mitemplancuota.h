#ifndef MITEMPLANCUOTA_H
#define MITEMPLANCUOTA_H

#include <QSqlRelationalTableModel>

#include <QDate>

/*!
 * \brief Clase para administrar los items y pagos de las cuotas.
 *
 * Esta clase permite mantener y administrar los pagos de los planes de cuotas asociados.
 * \author Esteban Zeller <juiraze@yahoo.com.ar>
 */
class MItemPlanCuota : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    explicit MItemPlanCuota( QObject *parent = 0 );
    
    static bool agregarItem( int id_plan, int num_cuota, QDate fecha_venc, double importe );

    QVariant data(const QModelIndex &item, int role) const;

};

#endif // MITEMPLANCUOTA_H
