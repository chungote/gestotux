#ifndef FORMFACTURACIONEMITIDA_H
#define FORMFACTURACIONEMITIDA_H

#include "eventana.h"
#include "ui_formfacturacionemitida.h"
class QSqlQueryModel;

class FormFacturacionEmitida : public EVentana, private Ui::FormFacturacionEmitida
{
    Q_OBJECT
    
public:
    FormFacturacionEmitida(QWidget *parent = 0);
    void setearIdServicio( const int id_servicio );
    void setearIdPeriodo ( const int id_periodo  );
    
protected slots:
    void cambioServicio( int id_servicio );
    void cambioPeriodo( int id_periodo );

protected:
    void changeEvent(QEvent *e);

private:
    void cargarDatos();
    int _id_servicio;
    int _id_periodo_servicio;

    QSqlQueryModel *mpagado;
    QSqlQueryModel *mdeudor;
};

#endif // FORMFACTURACIONEMITIDA_H
