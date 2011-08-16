#ifndef ELECUITCUIL_H
#define ELECUITCUIL_H

#include <QLineEdit>

class ELECuitCuil : public QLineEdit
{
    Q_OBJECT
public:
    explicit ELECuitCuil(QWidget *parent = 0);
    bool verificar();

};

#endif // ELECUITCUIL_H
