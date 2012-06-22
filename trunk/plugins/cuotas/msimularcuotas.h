#ifndef MSIMULARCUOTAS_H
#define MSIMULARCUOTAS_H

#include <QAbstractTableModel>
#include <QDate>

class MSimularCuotas : public QAbstractTableModel
{
    Q_OBJECT

public:
    enum Periodo {
        Invalido      = -1,
        Semanal       = 1,
        Quincenal     = 2,
        Mensual       = 3,
        Bimensual     = 4,
        Trimestral    = 5,
        Cuatrimestral = 6,
        Semestral     = 7,
        Anual         = 8
    };

    MSimularCuotas( QObject *parent = 0 );
    ~MSimularCuotas();

    void setCuotas( int c );
    void setImporte( double i ) { importe = i; }
    void setPeriodo( Periodo p ) { periodo = p; }
    void setInteres( double i ) { interes = i; }
    void setFechaInicio( QDate f ) { fecha_inicio = f; }

    void regenerar();

    int rowCount( const QModelIndex &parent = QModelIndex() ) const;
    int columnCount( const QModelIndex &parent = QModelIndex() ) const;
    QVariant data( const QModelIndex &index, int role ) const;
    Qt::ItemFlags flags( const QModelIndex & index ) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    double importe;
    double interes;
    int cantidad;
    Periodo periodo;
    QDate fecha_inicio;

    QHash<int,double> *sumatoria;

    bool valido() const;
    int diasPeriodo( Periodo periodo ) const;

};

#endif // MSIMULARCUOTAS_H
