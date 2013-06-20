#include "formrangofechas.h"

FormRangoFechas::FormRangoFechas( QWidget *parent ) :
QDialog(parent)
{
    setupUi(this);
    this->setWindowTitle( "Elija el rango" );

    // Busco los maximos y mínimos
    /// @TODO Buscar maximos y minimos de fechas posibles
}

void FormRangoFechas::accept()
{
    qWarning( "No implementado" );
}

void FormRangoFechas::changeEvent(QEvent *e)
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
