/***************************************************************************
 *   Copyright (C) 2006 by Norbert Szabo                                   *
 *   nszabo@helta.hu                                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef DIAVARIABLE_H
#define DIAVARIABLE_H

#include <QVariant>
#include <QDialog>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QGroupBox;
class QComboBox;
class QLabel;
class QLineEdit;
class ReportVariableListView;
class ReportVariable;
class QListViewItem;
class QPushButton;
class NCReportDesignerDocument;

class diaVariable : public QDialog
{
    Q_OBJECT

public:
    diaVariable( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~diaVariable();

	virtual void applySettings();
	void assignDocument( NCReportDesignerDocument* );
	void refreshForm( bool enable );


public slots:
    virtual void newVariable();
    virtual void removeVariable();

protected:
	QGroupBox* gbVar;
	QComboBox* comboFunc;
	QLabel* lblType;
	QLabel* lblField;
	QLabel* lblFunc;
	QComboBox* comboType;
	QLineEdit* leField;
	QLabel* lblName;
	QLineEdit* leName;
	ReportVariableListView* listVars;
	QPushButton* btnNew;
	QPushButton* btnDelete;
	QPushButton* btnOK;
	QPushButton* btnCancel;

	QHBoxLayout* diaVariableLayout;
    QVBoxLayout* layLeft;
    QGridLayout* gbVarLayout;
    QVBoxLayout* layBtn;
    QSpacerItem* spBtn;

	QListViewItem* currItem;
	QMap<QString,ReportVariable> variables;
	NCReportDesignerDocument *document;

protected slots:
    void languageChange();
	void _change_name(const QString&);
	void _change_field(const QString&);
	void _change_function(const QString&);
	void _change_datatype(const QString&);
	void _change_listView(QListViewItem *);

protected:
/*	void dataChange( const QString& name_old, const QString& name_new,
					 bool changeName, bool changeField, bool changeFunc, bool changeDataType );*/
	void dataChange( bool changeName, bool changeField, bool changeFunc, bool changeDataType );
	void setLineEditValue( QLineEdit*, const QString& );
	void setComboBoxValue( QComboBox*, const QString& );
	void clearWidgets();

};

#endif // DIAVARIABLE_H
