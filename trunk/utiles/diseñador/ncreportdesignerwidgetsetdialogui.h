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

    QTabWidget* tab;
    QWidget* pageData;
    QLabel* lblLabel;
    QTextEdit* textLabel;
    QLabel* lblSrc;
    QLineEdit* lePrintWhen;
    QLabel* lblFunc;
    QLineEdit* leSource;
    QComboBox* comboDSource;
    QLabel* lblPWhen;
    QLabel* lblSrcType;
    QLabel* lblEmbed;
    QLabel* lblLookup;
    QLineEdit* leFunction;
    QLineEdit* leLookup;
    QLineEdit* leEmbed;
    QWidget* TabPage;
    QLabel* lblType;
    QComboBox* comboType;
    QGroupBox* gbNumFormat;
    QLabel* lblNumFormat;
    QLineEdit* leNumFormat;
    QLabel* lblNoDec;
    QSpinBox* spDec;
    QLabel* lblDecPoint;
    QLineEdit* leDecPoint;
    QLineEdit* leSeparator;
    QLabel* lblSetSymb;
    QCheckBox* cbBlankIfZero;
    QCheckBox* cbThousandSep;
    QLabel* lblHelpNumF;
    QGroupBox* gbDateFormat;
    QLabel* lblDateFmt;
    QLineEdit* leDateFormat;
    QWidget* pageTxt;
    NCColorCombo* comboColor;
    QPushButton* btnSelFont;
    QLabel* lblFont;
    QComboBox* comboFontSize;
    QLineEdit* leFont;
    QLabel* lblTxtColor;
    QLabel* lblFontSize;
    QLabel* lblSample;
    QCheckBox* cbBold;
    QCheckBox* cbItalic;
    QCheckBox* cbUnderline;
    QCheckBox* cbStrikeout;
    QButtonGroup* bgHAlign;
    QRadioButton* radioLeft;
    QRadioButton* radioCenter;
    QRadioButton* radioRight;
    QButtonGroup* bgVAlign;
    QRadioButton* radioTop;
    QRadioButton* radioMid;
    QRadioButton* radioBottom;
    QCheckBox* cbWordBreak;
    QCheckBox* cbRichText;
    QCheckBox* cbDynamicHeight;
    QCheckBox* cbLoadFromFile;

    QLabel* lblRotat;
    QSpinBox* spinRotation;
    QWidget* pageLine;
    QButtonGroup* bgBackM;
    QRadioButton* radioTransp;
    QRadioButton* radioFill;
    QLabel* lblFillcol;
    QComboBox* comboLineStyle;
    NCColorCombo* comboColorF;
    QLabel* lblLinesty;
    QLabel* lblLinecol;
    QSpinBox* spinLineWidth;
    NCColorCombo* comboColorL;
    QLabel* lblLinew;
    QPushButton* buttonApply;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;

public slots:
    virtual void applyOptions();

protected:
    QVBoxLayout* setdialogLayout;
    QVBoxLayout* pageDataLayout;
    QSpacerItem* spacerDS;
    QGridLayout* layDSGrid;
    QVBoxLayout* TabPageLayout;
    QSpacerItem* spDataF;
    QHBoxLayout* layout42;
    QSpacerItem* spDataType;
    QGridLayout* gbNumFormatLayout;
    QHBoxLayout* gbDateFormatLayout;
    QSpacerItem* spDF;
    QVBoxLayout* pageTxtLayout;
    QSpacerItem* spacerTextPage;
    QHBoxLayout* layFont1;
    QGridLayout* layFontIn;
    QHBoxLayout* layCb;
    QSpacerItem* spacerCb;
    QHBoxLayout* layRadio;
    QHBoxLayout* bgHAlignLayout;
    QHBoxLayout* bgVAlignLayout;
    QHBoxLayout* layRot;
    QSpacerItem* spacerRot;
    QVBoxLayout* pageLineLayout;
    QSpacerItem* spacerPageLine;
    QHBoxLayout* layLin1;
    QSpacerItem* spacerBM;
    QHBoxLayout* bgBackMLayout;
    QHBoxLayout* layLin2;
    QSpacerItem* spacerLineS;
    QGridLayout* layout11;
    QHBoxLayout* layBtn;
    QSpacerItem* spacerBtn;
    QSpacerItem* spacerBtn2;

protected slots:
    virtual void languageChange();

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
