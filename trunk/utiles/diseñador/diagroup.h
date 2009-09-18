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
#ifndef DIAGROUP_H
#define DIAGROUP_H

#include <QVariant>
#include <QDialog>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QListBox;
class QListBoxItem;
class QPushButton;
class QButtonGroup;
class QLabel;
class QLineEdit;
class QListView;
class QListViewItem;
class NCReportDesignerDocument;
class ReportGroup;
class ReportVariableListView;

class diaGroup : public QDialog
{
    Q_OBJECT

public:
	diaGroup( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~diaGroup();

	void assignDocument( NCReportDesignerDocument* );
	void refreshForm( bool enable );

public slots:
    virtual void newGroup();
    virtual void removeGroup();
    virtual void moveUp();
    virtual void moveDown();
	virtual void applyGroupSettings();

protected:
    QVBoxLayout* diaGroupLayout;
    QHBoxLayout* layGroup;
    QVBoxLayout* layGB;
    QSpacerItem* spGB;
    QVBoxLayout* bgGroupLayout;
    QGridLayout* layNames;
    QHBoxLayout* layBtn;
    QSpacerItem* spButt;

	QListBox* listGroups;
	QPushButton* btnNew;
	QPushButton* btnRemove;
	QPushButton* btnUp;
	QPushButton* btnDown;
	QButtonGroup* bgGroup;
	QLabel* lblName;
	QLabel* lblExp;
	QLineEdit* leExpr;
	QLineEdit* leName;
	QLabel* lblVars;
	ReportVariableListView* listVars;
	QPushButton* btnApply;
	QPushButton* btnOK;
	QPushButton* btnCancel;

	NCReportDesignerDocument* document;
	QListBoxItem* currItem;
	QMap<QString,ReportGroup> groups;

	void clearWidgets();

protected slots:
    virtual void languageChange();
    virtual void groupChanged( QListBoxItem* );

	void _changed_name( const QString& );
	void _changed_expr( const QString& );
	void _changed_resetvars( QListViewItem* );

	//virtual void groupNameChanged( const QString& );
	//virtual void groupNameChanged();
protected:
	void groupDataChange( const QString& gname_old, const QString& gname_new, bool changeName, bool changeExpr, bool changeReset );
	void setLineEditValue( QLineEdit*, const QString& );


};

#endif // DIAGROUP_H
