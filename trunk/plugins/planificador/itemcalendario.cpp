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

#include "itemcalendario.h"
#include <QtGui>

ItemCalendario::ItemCalendario(QGraphicsItem *parent,
                               QGraphicsScene *scene ) :
QGraphicsItem(parent, scene)
{
}

/*!
    Returns shape of calendar item.
*/
QPainterPath ItemCalendario::shape () const
{
    QPainterPath result;
    result.addRect(myBoundingRect);
    return result;
}

/*!
    Paints calendar item.
*/
void ItemCalendario::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->setPen(QColor(0,0,0,128));
//    painter->drawRect(0,0,myBoundingRect.width(),myBoundingRect.height());
}

/*!
    Returns boundingRect
*/
QRectF ItemCalendario::boundingRect() const
{
    return myBoundingRect;
}

/*!
    Sets size.
*/
void ItemCalendario::setSize(const QSize &size)
{
        if(size.width() != myBoundingRect.width() ||
           size.height() != myBoundingRect.height())
    {
        prepareGeometryChange();
        QSizeF old = myBoundingRect.size();
        myBoundingRect.setWidth(size.width());
        myBoundingRect.setHeight(size.height());
        onResize(size, old);
        update();
    }
}

/*!
    Sets size.
*/
void ItemCalendario::setSize(qreal width, qreal height)
{
    if(width != myBoundingRect.width() || height != myBoundingRect.height())
    {
        prepareGeometryChange();
        QSizeF old = myBoundingRect.size();
        QSizeF size(width, height);
        myBoundingRect.setWidth(width);
        myBoundingRect.setHeight(height);
        onResize(size, old);
        update();
    }
}

/*!
    Handles resize event. Default implementation does nothing.
*/
void ItemCalendario::onResize(const QSizeF &size, const QSizeF &oldSize)
{
}

/*!
    Validates layout. Default implementation does nothing.
*/
void ItemCalendario::layoutChanged()
{
}

/*!
    Handles dataChanged event. Default implementation does nothing.
*/
void ItemCalendario::dataChanged()
{
}
