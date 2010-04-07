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
#include "scrollareaitem.h"
#include "dayitem.h"

ScrollAreaItem::ScrollAreaItem(QGraphicsItem *parent, QGraphicsScene *scene) : 
    CalendarItem(parent, scene), myVertical(this, scene), myContent(this, scene), ptrItem(0)
{
    myContent.setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
}

void ScrollAreaItem::setItem(CalendarItem *item)
{
    if(item != 0)
    {
        item->setParentItem(&myContent);
        myVertical.setMaximum(item->boundingRect().height());
    }
    ptrItem = item;
}

void ScrollAreaItem::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int left = 0;
    int top = 0;
    int width = (int)myBoundingRect.width();
    int height = (int)myBoundingRect.height();

    painter->setBrush(QBrush(QColor(127, 127, 127)));
    painter->drawRect(left, top, width, height);
}

void ScrollAreaItem::onResize(const QSizeF &size, const QSizeF &oldSize)
{
    layoutChanged();
}

void ScrollAreaItem::layoutChanged()
{
    //int left = 0;
    //int top = 0;
    qreal width = myBoundingRect.width();
    qreal height = myBoundingRect.height();

    qreal verticalBar = myVertical.boundingRect().width();

    // Content pane
    myContent.setSize(width - verticalBar, height);

    // Scrollbars
    myVertical.setPos(width - verticalBar, 0);
    myVertical.setSize(verticalBar, height);

    if(ptrItem != 0)
    {
        myVertical.setMaximum(ptrItem->boundingRect().height());
    }

    //myVertical.layoutChanged();
}

void ScrollAreaItem::scrollTo(qreal value)
{
    myVertical.scrollTo(value);
}

void ScrollAreaItem::ensureVisibility(qreal x, qreal y)
{
    myVertical.ensureVisibility(y);
}

qreal ScrollAreaItem::scrollBarWidth() const
{
    return myVertical.boundingRect().width();
}

void ScrollAreaItem::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    myVertical.scrollBy(-event->delta() / 4);
    layoutChanged();
}
