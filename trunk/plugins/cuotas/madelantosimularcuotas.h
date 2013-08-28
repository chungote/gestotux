#ifndef MADELANTOSIMULARCUOTAS_H
#define MADELANTOSIMULARCUOTAS_H

#include "msimularcuotas.h"

class MAdelantoSimularCuotas : public MSimularCuotas
{
    Q_OBJECT
public:
    MAdelantoSimularCuotas( QObject *parent = 0 );
    ~MAdelantoSimularCuotas();

    void setearImporteAdelanto( double importe ) { _adelanto = importe; regenerar(); }
    double importeAdelanto() { return _adelanto; }

    void regenerar();

    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    
private:
    double _adelanto;
    QHash<int,double> *adelantos;

};

#endif // MADELANTOSIMULARCUOTAS_H
