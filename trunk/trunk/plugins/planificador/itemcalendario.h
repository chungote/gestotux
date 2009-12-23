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

#ifndef ITEMCALENDARIO_H
#define ITEMCALENDARIO_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPainterPath>

class ItemCalendario : public QGraphicsItem
{
public:
    ItemCalendario(QGraphicsItem *parent = 0,
                   QGraphicsScene *scene = 0);

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget);

    virtual QPainterPath shape () const;

    QRectF boundingRect() const;

    void setSize(const QSize &size);
    void setSize(qreal width, qreal height);

    virtual void onResize(const QSizeF &size, const QSizeF &oldSize);

    virtual void layoutChanged();
    virtual void dataChanged();

protected:
    QRectF myBoundingRect;
};

#endif // ITEMCALENDARIO_H
