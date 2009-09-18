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
#ifndef NCCOLORCOMBO_H
#define NCCOLORCOMBO_H

#include <qcombobox.h>
#include <qcolor.h>

class NCColorCombo : public QComboBox
{
    Q_OBJECT
public:
	NCColorCombo( QWidget *parent, const char *name = 0 );
	~NCColorCombo();
	
	void setColor( const QColor &col );
	QColor color() const;
	void setWebColor( const QString & colorstring );
	QString webColor() const;

	
	
	void showEmptyList();
signals:
	void activated( const QColor &col );
	void highlighted( const QColor &col );

protected:
    virtual void resizeEvent( QResizeEvent *re );

private slots:
    void slotActivated( int index );
    void slotHighlighted( int index );

private:
    void addColors();
    QColor customColor;
    QColor internalcolor;

private:
	//class NCColorComboPrivate;
	//NCColorComboPrivate *d;
	bool _showEmptyList;
};

#endif
