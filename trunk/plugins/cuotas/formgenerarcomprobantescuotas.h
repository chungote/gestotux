#ifndef FORMGENERARCOMPROBANTESCUOTAS_H
#define FORMGENERARCOMPROBANTESCUOTAS_H

#include "ui_formgenerarcomprobantescuotasbase.h"
#include "eventana.h"
#include "mgenerarcuotas.h"
#include "NumeroComprobante.h"

class FormGenerarComprobantesCuotas : public EVentana, private Ui::FormGenerarComprobantesCuotas
{
    Q_OBJECT
    
public:
    FormGenerarComprobantesCuotas( QWidget *parent = 0 );
    
protected:
    void changeEvent(QEvent *e);

protected slots:
    void cambioComprobantes( QPair<NumeroComprobante *, NumeroComprobante *> nums );

private:
    MGenerarCuotas *modelo;
};

#endif // FORMGENERARCOMPROBANTESCUOTAS_H
