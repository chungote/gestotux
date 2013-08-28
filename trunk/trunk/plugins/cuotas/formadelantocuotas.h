#ifndef FORMADELANTOCUOTAS_H
#define FORMADELANTOCUOTAS_H

#include "formdetallecuotas.h"
#include "mplancuota.h"
#include "mitemplancuota.h"
#include "madelantosimularcuotas.h"
#include <QTextDocument>

class FormAdelantoCuotas : public FormDetalleCuotas
{
    Q_OBJECT
public:
    FormAdelantoCuotas( QWidget *parent = 0 );
    void setearIdPlanCuota( int id );

private slots:
    void imprimir();
    void pdf();
    void confirmar();
    void cambiarImporte( double );

private:
    QAction *ActConfirmar;
    QAction *ActImprimir;
    QAction *ActPdf;

    MPlanCuota *modelo;
    MAdelantoSimularCuotas *modelo_item;
    QTextDocument *documento;

    void generaReporte();

};

#endif // FORMADELANTOCUOTAS_H
