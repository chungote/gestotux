/****************************************************************************
** Form implementation generated from reading ui file 'ncreportdesignerwidgetsetdialogui.ui'
**
** Created: k aug 22 11:50:39 2006
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "ncreportdesignerwidgetsetdialogui.h"
#include "nccolorcombo.h"

#include <QVariant>
#include <QPushButton>
#include <QTabWidget>
#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>


/*
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>*/

/*
 *  Constructs a NCReportDesignerWidgetSetDialogUI as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
NCReportDesignerWidgetSetDialogUI::NCReportDesignerWidgetSetDialogUI( QWidget* parent, const char* name, bool modal, Qt::WindowFlags fl )
    : QDialog( parent, fl )
{
    if ( !name )
	name = "setdialog";
    this->setObjectName( name );
    this->setModal( modal );

    // signals and slots connections
   /* connect( buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
    connect( buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( cbBold, SIGNAL( toggled(bool) ), this, SLOT( fontBoldChanged(bool) ) );
    connect( cbItalic, SIGNAL( toggled(bool) ), this, SLOT( fontItalicChanged(bool) ) );
    connect( cbUnderline, SIGNAL( toggled(bool) ), this, SLOT( fontUnderlineChanged(bool) ) );
    connect( cbStrikeout, SIGNAL( toggled(bool) ), this, SLOT( fontStrikeChanged(bool) ) );
    connect( leFont, SIGNAL( textChanged(const QString&) ), this, SLOT( fontStyleChanged(const QString&) ) );
    connect( comboFontSize, SIGNAL( textChanged(const QString&) ), this, SLOT( fontSizeChanged(const QString&) ) );
    connect( bgHAlign, SIGNAL( clicked(int) ), this, SLOT( alignHChanged(int) ) );
    connect( bgVAlign, SIGNAL( clicked(int) ), this, SLOT( alignVChanged(int) ) );
    connect( bgBackM, SIGNAL( clicked(int) ), this, SLOT( backModeChanged(int) ) );
    connect( buttonApply, SIGNAL( clicked() ), this, SLOT( applyOptions() ) );*/
}

/*
 *  Destroys the object and frees any allocated resources
 */
NCReportDesignerWidgetSetDialogUI::~NCReportDesignerWidgetSetDialogUI()
{
    // no need to delete child widgets, Qt does it all for us
}

void NCReportDesignerWidgetSetDialogUI::applyOptions()
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::applyOptions(): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::fontStyleChanged(const QString&)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::fontStyleChanged(const QString&): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::fontSizeChanged(const QString&)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::fontSizeChanged(const QString&): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::fontColorChanged(const QString&)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::fontColorChanged(const QString&): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::fontBoldChanged(bool)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::fontBoldChanged(bool): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::fontItalicChanged(bool)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::fontItalicChanged(bool): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::fontUnderlineChanged(bool)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::fontUnderlineChanged(bool): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::fontStrikeChanged(bool)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::fontStrikeChanged(bool): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::alignHChanged(int)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::alignHChanged(int): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::alignVChanged(int)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::alignVChanged(int): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::backModeChanged(int)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::backModeChanged(int): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::selectFont()
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::selectFont(): Not implemented yet" );
}

void NCReportDesignerWidgetSetDialogUI::changedDataType(int)
{
    qWarning( "NCReportDesignerWidgetSetDialogUI::changedDataType(int): Not implemented yet" );
}

