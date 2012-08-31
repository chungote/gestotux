#include "formrecibo.h"

#include "mpagos.h"
#include "eactcerrar.h"

FormRecibo::FormRecibo(QWidget *parent) :
EVentana(parent)
{
    setupUi(this);

    addAction( new EActCerrar( this ) );
}

void FormRecibo::setId(int id)
{
    if( id <= 0 )
        return;

    _id_actual = id;
    cargarDatos();
}

void FormRecibo::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
        case QEvent::LanguageChange:
            retranslateUi(this);
            break;
        default:
            break;
    }
}

void FormRecibo::cargarDatos()
{
}
