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
#ifndef NCREPORTDESIGNERWIDGETSETDIALOG_H
#define NCREPORTDESIGNERWIDGETSETDIALOG_H

#include "ncreportdesignerwidgetsetdialogui.h"

class NCReportDesignerWidget;
class NCReportDesignerDocument;
class WProperty;

class NCReportDesignerWidgetSetDialog : public NCReportDesignerWidgetSetDialogUI
{
  Q_OBJECT
public:
	NCReportDesignerWidgetSetDialog( NCReportDesignerWidget *dwidget, QWidget* parent, NCReportDesignerDocument*,
									 const char* name = 0, bool modal = FALSE, Qt::WindowFlags fl = 0 );
	~NCReportDesignerWidgetSetDialog();

	void setWidget( NCReportDesignerWidget* );
	void setDocument( NCReportDesignerDocument* );
	void setSaveToProperty( WProperty* );
	/*! save settings to property has set before */
	void saveSettings();
public slots:
	virtual void applyOptions();

protected:
	void init();
	void loadOptions();

protected slots:
	virtual void backModeChanged(int);
	virtual void alignVChanged(int);
	virtual void alignHChanged(int);
	virtual void fontStrikeChanged( bool );
	virtual void fontUnderlineChanged( bool );
	virtual void fontItalicChanged( bool );
	virtual void fontBoldChanged( bool );
	virtual void fontColorChanged(const QString&);
	virtual void fontSizeChanged(const QString&);
	virtual void fontStyleChanged(const QString&);
	virtual void selectFont();
	virtual void changedDataType(int);

private:
	NCReportDesignerWidget *dw;
	NCReportDesignerDocument *document;
	WProperty* p;


};

#endif

