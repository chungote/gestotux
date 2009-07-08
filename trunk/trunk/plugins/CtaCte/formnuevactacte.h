/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   				   *
 *   juiraze@yahoo.com.ar   						   *
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

#ifndef FORMNUEVACTACTE_H
#define FORMNUEVACTACTE_H

#include <QWidget>
#include "ui_FormCtaCteBase.h"
class QSqlRelationalTableModel;

class FormNuevaCtaCte : public QDialog, private Ui::FormCtaCteBase
{
Q_OBJECT
public:
	FormNuevaCtaCte ( QWidget* parent = 0, Qt::WFlags fl = 0 );
	~FormNuevaCtaCte();
    void setModelo( QSqlRelationalTableModel *m );
public slots:
protected:
    QSqlRelationalTableModel *modelo;
    void accept();
};

#endif

