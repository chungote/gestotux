/********************************************************************************
** Form generated from reading ui file 'FormPrefOpcionesBase.ui'
**
** Created: Tue 28. Aug 21:48:14 2007
**      by: Qt User Interface Compiler version 4.3.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_FORMPREFOPCIONESBASE_H
#define UI_FORMPREFOPCIONESBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_FormPrefOpcionesBase
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *GBMiselaceas;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QSpinBox *SBLimite;

    void setupUi(QWidget *FormPrefOpcionesBase)
    {
    if (FormPrefOpcionesBase->objectName().isEmpty())
        FormPrefOpcionesBase->setObjectName(QString::fromUtf8("FormPrefOpcionesBase"));
    QSize size(400, 300);
    size = size.expandedTo(FormPrefOpcionesBase->minimumSizeHint());
    FormPrefOpcionesBase->resize(size);
    vboxLayout = new QVBoxLayout(FormPrefOpcionesBase);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    GBMiselaceas = new QGroupBox(FormPrefOpcionesBase);
    GBMiselaceas->setObjectName(QString::fromUtf8("GBMiselaceas"));
    vboxLayout1 = new QVBoxLayout(GBMiselaceas);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    label = new QLabel(GBMiselaceas);
    label->setObjectName(QString::fromUtf8("label"));
    label->setScaledContents(true);
    label->setWordWrap(true);

    hboxLayout->addWidget(label);

    SBLimite = new QSpinBox(GBMiselaceas);
    SBLimite->setObjectName(QString::fromUtf8("SBLimite"));

    hboxLayout->addWidget(SBLimite);


    vboxLayout1->addLayout(hboxLayout);


    vboxLayout->addWidget(GBMiselaceas);


    retranslateUi(FormPrefOpcionesBase);

    QMetaObject::connectSlotsByName(FormPrefOpcionesBase);
    } // setupUi

    void retranslateUi(QWidget *FormPrefOpcionesBase)
    {
    FormPrefOpcionesBase->setWindowTitle(QApplication::translate("FormPrefOpcionesBase", "Form", 0, QApplication::UnicodeUTF8));
    GBMiselaceas->setTitle(QApplication::translate("FormPrefOpcionesBase", "Miselaceas", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("FormPrefOpcionesBase", "Cantidad de entradas que se mostraran al seleccionar mascota para ingresar nuevo servicio:", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(FormPrefOpcionesBase);
    } // retranslateUi

};

namespace Ui {
    class FormPrefOpcionesBase: public Ui_FormPrefOpcionesBase {};
} // namespace Ui

#endif // UI_FORMPREFOPCIONESBASE_H
