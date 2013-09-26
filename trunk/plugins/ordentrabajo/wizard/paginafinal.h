#ifndef PAGINAFINAL_H
#define PAGINAFINAL_H

#include "ui_paginafinal.h"

class PaginaFinal : public QWizardPage, private Ui::PaginaFinal
{
    Q_OBJECT
    
public:
    explicit PaginaFinal(QWidget *parent = 0);
    
};

#endif // PAGINAFINAL_H
