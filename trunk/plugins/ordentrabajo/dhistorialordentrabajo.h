#ifndef DHISTORIALORDENTRABAJO_H
#define DHISTORIALORDENTRABAJO_H

#include <QDialog>

namespace Ui {
class DHistorialOrdenTrabajo;
}

class DHistorialOrdenTrabajo : public QDialog
{
    Q_OBJECT
    
public:
    explicit DHistorialOrdenTrabajo(QWidget *parent = 0);
    ~DHistorialOrdenTrabajo();
    
private:
    Ui::DHistorialOrdenTrabajo *ui;
};

#endif // DHISTORIALORDENTRABAJO_H
