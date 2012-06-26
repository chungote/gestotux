#ifndef FORMSIMULARCUOTAS_H
#define FORMSIMULARCUOTAS_H

#include "ui_formsimularcuotasbase.h"
#include "eventana.h"
#include "msimularcuotas.h"
class QTextDocument;

class FormSimularCuotas : public EVentana, private Ui::FormSimularCuotasBase
{
    Q_OBJECT
    
public:
    FormSimularCuotas( QWidget *parent = 0 );
    ~FormSimularCuotas();
    
protected:
    void changeEvent( QEvent *e );

protected slots:
    void cambioEntrega( double cantidad );
    void cambioImporte( double cantidad );
    void cambioInteres( double cantidad );
    void cambioCantidad( int cantidad );
    void cambioPeriodo( int idx );
    void cambioFechaInicio( QDate fecha );

private slots:
    void simular();
    void imprimir();
    void pdf();
    void confirmar();

private:
    QAction *ActSimular;
    QAction *ActConfirmar;
    QAction *ActImprimir;
    QAction *ActPdf;

    MSimularCuotas *modelo;
    QTextDocument *documento;

    void generaReporte();

};

#endif // FORMSIMULARCUOTAS_H
