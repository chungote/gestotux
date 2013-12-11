#ifndef VDIEZMOS_H
#define VDIEZMOS_H

#include "mdiezmos.h"
#include "evlista.h"

class VDiezmos : public EVLista
{
    Q_OBJECT
public:
    explicit VDiezmos(QWidget *parent = 0);
    
signals:
    
public slots:

private:
    MDiezmos *modelo;
    
};

#endif // VDIEZMOS_H
