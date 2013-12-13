#include "ddardiezmo.h"

DDarDiezmo::DDarDiezmo(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
}

/*!
 * \brief DDarDiezmo::accept
 */
void DDarDiezmo::accept()
{
    qWarning( "No implementado" );
    return;
}

/*!
 * \brief DDarDiezmo::changeEvent
 * \param e
 */
void DDarDiezmo::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
        case QEvent::LanguageChange:
            retranslateUi(this);
            break;
        default:
            break;
    }
}
