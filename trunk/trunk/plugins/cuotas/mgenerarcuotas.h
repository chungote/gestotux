#ifndef MGENERARCUOTAS_H
#define MGENERARCUOTAS_H

#include <QSqlTableModel>
#include <QPair>
#include <QHash>
#include "NumeroComprobante.h"

class MGenerarCuotas : public QSqlTableModel
{
    Q_OBJECT
public:
    MGenerarCuotas( QObject *parent = 0 );
    QVariant data( const QModelIndex &idx, int role ) const;
    int columnCount( const QModelIndex &parent ) const;
    int rowCount( const QModelIndex &parent ) const;
    
    bool calcularComprobantes();

signals:
    void cambioTotal( double );
    void cambioCantidad( int );
    void comprobantes( QPair<NumeroComprobante *,NumeroComprobante *> );

private:
    int _cant;
    double _total;
    QHash<int, int> *_numeros;
    QHash<int, int> *_planes;
    QHash<int, QString> *_clientes;
    QHash<int, int> *_clientes_id;
    QHash<int, QString> *_cuotas;
    QHash<int, double> *_importes;
    QHash<int, NumeroComprobante *> *_comprobantes;
    
};

#endif // MGENERARCUOTAS_H
