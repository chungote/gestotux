/********************************************************************************
** Form generated from reading ui file 'FormAgregarReciboBase.ui'
**
** Created: Tue Jan 29 23:44:51 2008
**      by: Qt User Interface Compiler version 4.3.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_FORMAGREGARRECIBOBASE_H
#define UI_FORMAGREGARRECIBOBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDateEdit>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_FormAgregarReciboBase
{
public:
    QVBoxLayout *vboxLayout;
    QLabel *label;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout1;
    QLabel *label_3;
    QDateEdit *dEFechaPago;
    QHBoxLayout *hboxLayout2;
    QLabel *label_2;
    QComboBox *CBClientes;
    QGroupBox *groupBox;
    QHBoxLayout *hboxLayout3;
    QRadioButton *RBCuentaCorriente;
    QRadioButton *RBContado;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QTextEdit *TETexto;
    QGroupBox *groupBox_3;
    QHBoxLayout *hboxLayout4;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *hboxLayout5;
    QHBoxLayout *hboxLayout6;
    QLabel *label_4;
    QDoubleSpinBox *dSBImporte;
    QCheckBox *cBRecargos;
    QHBoxLayout *hboxLayout7;
    QCheckBox *cBPagoMes;
    QHBoxLayout *hboxLayout8;
    QLabel *lmes;
    QComboBox *CBMeses;
    QFrame *line;
    QVBoxLayout *vboxLayout3;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout9;
    QLabel *label_6;
    QLineEdit *LETotal;
    QSpacerItem *spacerItem1;

    void setupUi(QWidget *FormAgregarReciboBase)
    {
    if (FormAgregarReciboBase->objectName().isEmpty())
        FormAgregarReciboBase->setObjectName(QString::fromUtf8("FormAgregarReciboBase"));
    FormAgregarReciboBase->resize(767, 508);
    vboxLayout = new QVBoxLayout(FormAgregarReciboBase);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    label = new QLabel(FormAgregarReciboBase);
    label->setObjectName(QString::fromUtf8("label"));
    label->setAlignment(Qt::AlignCenter);

    vboxLayout->addWidget(label);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    label_3 = new QLabel(FormAgregarReciboBase);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    hboxLayout1->addWidget(label_3);

    dEFechaPago = new QDateEdit(FormAgregarReciboBase);
    dEFechaPago->setObjectName(QString::fromUtf8("dEFechaPago"));

    hboxLayout1->addWidget(dEFechaPago);


    vboxLayout1->addLayout(hboxLayout1);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    label_2 = new QLabel(FormAgregarReciboBase);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    hboxLayout2->addWidget(label_2);

    CBClientes = new QComboBox(FormAgregarReciboBase);
    CBClientes->setObjectName(QString::fromUtf8("CBClientes"));
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(CBClientes->sizePolicy().hasHeightForWidth());
    CBClientes->setSizePolicy(sizePolicy);

    hboxLayout2->addWidget(CBClientes);


    vboxLayout1->addLayout(hboxLayout2);


    hboxLayout->addLayout(vboxLayout1);

    groupBox = new QGroupBox(FormAgregarReciboBase);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    hboxLayout3 = new QHBoxLayout(groupBox);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    RBCuentaCorriente = new QRadioButton(groupBox);
    RBCuentaCorriente->setObjectName(QString::fromUtf8("RBCuentaCorriente"));

    hboxLayout3->addWidget(RBCuentaCorriente);

    RBContado = new QRadioButton(groupBox);
    RBContado->setObjectName(QString::fromUtf8("RBContado"));

    hboxLayout3->addWidget(RBContado);


    hboxLayout->addWidget(groupBox);


    vboxLayout->addLayout(hboxLayout);

    groupBox_2 = new QGroupBox(FormAgregarReciboBase);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    gridLayout = new QGridLayout(groupBox_2);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    TETexto = new QTextEdit(groupBox_2);
    TETexto->setObjectName(QString::fromUtf8("TETexto"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(TETexto->sizePolicy().hasHeightForWidth());
    TETexto->setSizePolicy(sizePolicy1);

    gridLayout->addWidget(TETexto, 0, 0, 1, 1);


    vboxLayout->addWidget(groupBox_2);

    groupBox_3 = new QGroupBox(FormAgregarReciboBase);
    groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
    QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
    groupBox_3->setSizePolicy(sizePolicy2);
    hboxLayout4 = new QHBoxLayout(groupBox_3);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    hboxLayout6 = new QHBoxLayout();
    hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
    label_4 = new QLabel(groupBox_3);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    hboxLayout6->addWidget(label_4);

    dSBImporte = new QDoubleSpinBox(groupBox_3);
    dSBImporte->setObjectName(QString::fromUtf8("dSBImporte"));
    QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy3.setHorizontalStretch(0);
    sizePolicy3.setVerticalStretch(0);
    sizePolicy3.setHeightForWidth(dSBImporte->sizePolicy().hasHeightForWidth());
    dSBImporte->setSizePolicy(sizePolicy3);
    dSBImporte->setMaximum(100000);

    hboxLayout6->addWidget(dSBImporte);


    hboxLayout5->addLayout(hboxLayout6);

    cBRecargos = new QCheckBox(groupBox_3);
    cBRecargos->setObjectName(QString::fromUtf8("cBRecargos"));

    hboxLayout5->addWidget(cBRecargos);


    vboxLayout2->addLayout(hboxLayout5);

    hboxLayout7 = new QHBoxLayout();
    hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
    cBPagoMes = new QCheckBox(groupBox_3);
    cBPagoMes->setObjectName(QString::fromUtf8("cBPagoMes"));

    hboxLayout7->addWidget(cBPagoMes);

    hboxLayout8 = new QHBoxLayout();
    hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
    lmes = new QLabel(groupBox_3);
    lmes->setObjectName(QString::fromUtf8("lmes"));

    hboxLayout8->addWidget(lmes);

    CBMeses = new QComboBox(groupBox_3);
    CBMeses->setObjectName(QString::fromUtf8("CBMeses"));
    sizePolicy.setHeightForWidth(CBMeses->sizePolicy().hasHeightForWidth());
    CBMeses->setSizePolicy(sizePolicy);

    hboxLayout8->addWidget(CBMeses);


    hboxLayout7->addLayout(hboxLayout8);


    vboxLayout2->addLayout(hboxLayout7);


    hboxLayout4->addLayout(vboxLayout2);

    line = new QFrame(groupBox_3);
    line->setObjectName(QString::fromUtf8("line"));
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    hboxLayout4->addWidget(line);

    vboxLayout3 = new QVBoxLayout();
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    spacerItem = new QSpacerItem(20, 21, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout3->addItem(spacerItem);

    hboxLayout9 = new QHBoxLayout();
    hboxLayout9->setObjectName(QString::fromUtf8("hboxLayout9"));
    label_6 = new QLabel(groupBox_3);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    hboxLayout9->addWidget(label_6);

    LETotal = new QLineEdit(groupBox_3);
    LETotal->setObjectName(QString::fromUtf8("LETotal"));
    QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
    sizePolicy4.setHorizontalStretch(0);
    sizePolicy4.setVerticalStretch(0);
    sizePolicy4.setHeightForWidth(LETotal->sizePolicy().hasHeightForWidth());
    LETotal->setSizePolicy(sizePolicy4);
    LETotal->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    LETotal->setReadOnly(true);

    hboxLayout9->addWidget(LETotal);


    vboxLayout3->addLayout(hboxLayout9);

    spacerItem1 = new QSpacerItem(20, 16, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout3->addItem(spacerItem1);


    hboxLayout4->addLayout(vboxLayout3);


    vboxLayout->addWidget(groupBox_3);


    retranslateUi(FormAgregarReciboBase);

    QMetaObject::connectSlotsByName(FormAgregarReciboBase);
    } // setupUi

    void retranslateUi(QWidget *FormAgregarReciboBase)
    {
    FormAgregarReciboBase->setWindowTitle(QApplication::translate("FormAgregarReciboBase", "Form", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("FormAgregarReciboBase", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; font-weight:600; color:#000000;\">Nuevo Recibo</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("FormAgregarReciboBase", "Fecha:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("FormAgregarReciboBase", "Cliente:", 0, QApplication::UnicodeUTF8));
    groupBox->setTitle(QApplication::translate("FormAgregarReciboBase", "Forma de Pago", 0, QApplication::UnicodeUTF8));
    RBCuentaCorriente->setText(QApplication::translate("FormAgregarReciboBase", "Cuenta Corriente", 0, QApplication::UnicodeUTF8));
    RBContado->setText(QApplication::translate("FormAgregarReciboBase", "Contado", 0, QApplication::UnicodeUTF8));
    groupBox_2->setTitle(QApplication::translate("FormAgregarReciboBase", "Texto", 0, QApplication::UnicodeUTF8));
    groupBox_3->setTitle(QApplication::translate("FormAgregarReciboBase", "Precio", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("FormAgregarReciboBase", "Importe:", 0, QApplication::UnicodeUTF8));
    dSBImporte->setPrefix(QApplication::translate("FormAgregarReciboBase", "$ ", 0, QApplication::UnicodeUTF8));
    cBRecargos->setText(QApplication::translate("FormAgregarReciboBase", "Aplicar recargos por pago fuera de termino", 0, QApplication::UnicodeUTF8));
    cBPagoMes->setText(QApplication::translate("FormAgregarReciboBase", "Pago de Mes", 0, QApplication::UnicodeUTF8));
    lmes->setText(QApplication::translate("FormAgregarReciboBase", "Mes:", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("FormAgregarReciboBase", "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Total:</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(FormAgregarReciboBase);
    } // retranslateUi

};

namespace Ui {
    class FormAgregarReciboBase: public Ui_FormAgregarReciboBase {};
} // namespace Ui

#endif // UI_FORMAGREGARRECIBOBASE_H
