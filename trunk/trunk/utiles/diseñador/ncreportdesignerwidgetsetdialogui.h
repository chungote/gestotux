/****************************************************************************
** Form interface generated from reading ui file 'ncreportdesignerwidgetsetdialogui.ui'
**
** Created: k aug 22 11:50:31 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef SETDIALOG_H
#define SETDIALOG_H

#include <QDialog>
// #include <qvariant.h>
// #include <qpixmap.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class NCColorCombo;
class QTabWidget;
class QWidget;
class QLabel;
class QTextEdit;
class QLineEdit;
class QComboBox;
class QGroupBox;
class QSpinBox;
class QCheckBox;
class QPushButton;
class QButtonGroup;
class QRadioButton;

class NCReportDesignerWidgetSetDialogUI : public QDialog
{
    Q_OBJECT

public:
    NCReportDesignerWidgetSetDialogUI( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WindowFlags fl = 0 );
    ~NCReportDesignerWidgetSetDialogUI();

public slots:
    virtual void applyOptions();

protected slots:
    virtual void fontStyleChanged(const QString&);
    virtual void fontSizeChanged(const QString&);
    virtual void fontColorChanged(const QString&);
    virtual void fontBoldChanged( bool );
    virtual void fontItalicChanged( bool );
    virtual void fontUnderlineChanged( bool );
    virtual void fontStrikeChanged( bool );
    virtual void alignHChanged(int);
    virtual void alignVChanged(int);
    virtual void backModeChanged(int);
    virtual void selectFont();
    virtual void changedDataType(int);


private:
    QPixmap image0;

};

#endif // SETDIALOG_H
