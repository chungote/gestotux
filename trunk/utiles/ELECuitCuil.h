#ifndef ELECUITCUIL_H
#define ELECUITCUIL_H

#include <QLineEdit>

class ELECuitCuil : public QLineEdit
{
    Q_OBJECT
public:
    explicit ELECuitCuil(QWidget *parent = 0);
    bool verificar();
    QString text() const;

};

#endif // ELECUITCUIL_H
