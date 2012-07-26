#ifndef MPLANCUOTA_H
#define MPLANCUOTA_H

#include <QSqlTableModel>
/*!
 * \brief Modelo para los planes de cuotas
 *
 * \author Esteban Zeller
 */
class MPlanCuota : public QSqlTableModel
{
    Q_OBJECT
public:
    MPlanCuota( QObject *parent = 0 );

    bool agregarPlanCuota( int id_cliente, double cantidad, double interes, int periodo, double entrega, QDate fecha_inicio );
    
};

#endif // MPLANCUOTA_H
