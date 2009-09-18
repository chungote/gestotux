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
#ifndef DIAPAGE_H
#define DIAPAGE_H

#include <QVariant>
#include <QDialog>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QGroupBox;
class QLineEdit;
class QLabel;
class QComboBox;
class QSpinBox;
class QButtonGroup;
class QRadioButton;
class QPushButton;
class NCReportDesignerDocument;
class QTabWidget;
class QWidget;

class diaPage : public QDialog
{
		Q_OBJECT

	public:
		diaPage ( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, Qt::WFlags fl = 0 );
		~diaPage();

		void assignDocument ( NCReportDesignerDocument* );
		void applySettings();
	protected:
		QTabWidget *tab;
		QWidget *pagePage;
		QWidget *pageDataSource;

		QVBoxLayout *layPagePage;
		QVBoxLayout *layPageDataSource;

		QGroupBox* gbGen;
		QLineEdit* leFont;
		QLineEdit* leMasterAlias;
		QLabel* lblEncode;
		QLabel* lblPrintMode;
		QComboBox* comboPrinterMode;
		QLabel* textLabel10;
		QLabel* lblFont;
		QLabel* lblPageSize;
		QLabel* lblFonstSize;
		QLabel* lblName;
		QSpinBox* spFontSize;
		QComboBox* comboEncodings;
		QComboBox* comboPageSize;
		QLineEdit* leName;
		QGroupBox* gbMargin;
		QLabel* lblLeft;
		QSpinBox* spRight;
		QLabel* lblBottom;
		QSpinBox* spBottom;
		QLabel* lblTop;
		QSpinBox* spTop;
		QLabel* lblRight;
		QSpinBox* spLeft;
		QButtonGroup* gbOrient;
		QRadioButton* radioP;
		QRadioButton* radioL;
		QGroupBox* gbCon;
		QGroupBox* gbText;
		QLabel* lblHot;
		QLabel* lblDB;
		QLabel* lblUser;
		QLabel* lblPassword;
		QLineEdit* leHost;
		QLineEdit* leDB;
		QLineEdit* leUSer;
		QLineEdit* lePassw;

		QHBoxLayout* layDSTop;
		QComboBox* comboDataSource;
		QLabel* lblDataSrc;
		QLabel* lblResrcText;
		QLabel* lblTextDataDelim;
		QLabel* lblRowFilter;
		QLineEdit* leResourceText;
		QComboBox* comboDelimiter;
		QLineEdit* leRowFilter;

		QPushButton* btnOK;
		QPushButton* btnCancel;

		QHBoxLayout* diaPageLayout;
		QVBoxLayout* layLeft;
		QGridLayout* gbGenLayout;
		QHBoxLayout* layMargin;
		QGridLayout* gbMarginLayout;
		QVBoxLayout* gbOrientLayout;
		QGridLayout* gbConLayout;
		QGridLayout* gbTextLayout;
		QVBoxLayout* layBtn;
		QSpacerItem* spBtn;

		NCReportDesignerDocument *document;


	protected slots:
		virtual void languageChange();

	protected:
		void initComboBoxes();

};

#endif // DIAPAGE_H
