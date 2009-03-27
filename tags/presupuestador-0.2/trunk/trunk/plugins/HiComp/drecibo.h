/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   *
 *   juiraze@yahoo.com.ar   *
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
#ifndef DRECIBO_H
#define DRECIBO_H

#include <QSqlRelationalDelegate>
#include <QPolygonF>

/**
 * \brief Delegate para edici�n de recibos
 *
 * Delegate que funciona como selector de las vistas de recibos y permite editar los campos
 *
 *	@author Esteban Zeller <juiraze@yahoo.com.ar>
 */
class DRecibo : public QSqlRelationalDelegate
{
Q_OBJECT
public:
    DRecibo(QObject *parent = 0);
    ~DRecibo();
    void setModelData ( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const;
    void setEditorData ( QWidget * editor, const QModelIndex & index ) const;
    QWidget * createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    void paint( QPainter *painter, const QStyleOptionViewItem &option,  const QModelIndex &index ) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
    QPolygonF diamondPolygon;
    QPolygonF starPolygon;
};

#endif
