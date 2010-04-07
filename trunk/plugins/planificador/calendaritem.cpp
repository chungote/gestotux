/*******************************************************************************

    Copyright (C) 2008 Jukka-Pekka Mäkelä.
    Contact: jpm@mehteenit.net

    This file is part of QuickCalendar.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QuickCalendar.  If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************/

#include <QtGui>
#include "calendaritem.h"

/*!
    Constructor
*/
CalendarItem::CalendarItem(QGraphicsItem *parent,
                           QGraphicsScene *scene) :
    QGraphicsItem(parent, scene)
{
}

/*!
    Returns shape of calendar item.
*/
QPainterPath CalendarItem::shape () const
{
    QPainterPath result;
    result.addRect(myBoundingRect);
    return result;
}

/*!
    Paints calendar item.
*/
void CalendarItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    painter->setPen(QColor(0,0,0,128));
//    painter->drawRect(0,0,myBoundingRect.width(),myBoundingRect.height());
}

/*!
    Returns boundingRect
*/
QRectF CalendarItem::boundingRect() const
{
    return myBoundingRect;
}

/*!
    Sets size.
*/
void CalendarItem::setSize(const QSize &size)
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
void CalendarItem::setSize(qreal width, qreal height)
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
void CalendarItem::onResize(const QSizeF &size, const QSizeF &oldSize)
{
}

/*!
    Validates layout. Default implementation does nothing.
*/
void CalendarItem::layoutChanged()
{
}

/*!
    Handles dataChanged event. Default implementation does nothing.
*/
void CalendarItem::dataChanged()
{
}
