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
#ifndef QUERY_EDITOR_H
#define QUERY_EDITOR_H

#include <QVariant>
#include <QDialog>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QLineEdit;
class QListBox;
class QListBoxItem;
class QPushButton;
class QTextEdit;
class NCReportDesignerDocument;

class diaQuery : public QDialog
{
    Q_OBJECT

public:
    diaQuery( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
    ~diaQuery();

	void assignDocument( NCReportDesignerDocument* );

public slots:
    virtual void addQuery();
    virtual void removeQuery();
    virtual void moveUp();
    virtual void renameQuery();

	virtual void currentChanged( QListBoxItem * );
	virtual void qryChanged();

protected:
    QVBoxLayout* query_editorLayout;
    QHBoxLayout* layUp;
    QVBoxLayout* layLeft;
    QHBoxLayout* layName;
    QVBoxLayout* layBtn;
    QSpacerItem* spBtn;
	QLabel* lblName;
	QLineEdit* leName;
	QListBox* listQuery;
	QLabel* textLabel2;
	QPushButton* btnAdd;
	QPushButton* btnRemove;
	QPushButton* btnRename;
	QPushButton* btnUp;
	QPushButton* btnClose;
	QTextEdit* editQuery;

	NCReportDesignerDocument* document;

protected slots:
    virtual void languageChange();

};

#endif // QUERY_EDITOR_H
