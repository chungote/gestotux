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
#include "scrollbar.h"
#include "scrollareaitem.h"

ScrollBar::ScrollBar(ScrollAreaItem *scrollArea, QGraphicsScene *scene) : 
    CalendarItem(scrollArea, scene), ptrArea(scrollArea)
{
    myMin = 0.0;
    myMax = 0.0;
    myValue = 0.0;
    myFactor = 1.0;

    sliderPos = 0;
    sliderMax = 0;
    pressedControl = 0;

    myBoundingRect.adjust(0,0,16,16);
}

void ScrollBar::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int width = (int)myBoundingRect.width();
    int height = (int)myBoundingRect.height();

    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(QColor(161,161,129)));
    painter->drawRect(0,height/3,width,height/3);

    painter->setBrush(QBrush(QColor(191,191,191)));
    painter->drawRect(0,0,width,height/3);
    painter->drawRect(0,(height*2)/3,width,height/3);

    painter->setPen(QPen(QColor(63,63,63)));
    painter->setBrush(QBrush(QColor(255,255,255,127)));
    painter->drawRect(0, sliderPos, width, sliderHeight);
}

void ScrollBar::layoutChanged()
{
    qreal height = myBoundingRect.height();

    sliderHeight = height * myFactor;
    sliderPos = myValue * myFactor;

    ptrArea->ptrItem->setPos(0, -myValue);

    ptrArea->update();
}

void ScrollBar::onResize(const QSizeF &size, const QSizeF &oldSize)
{
    qreal posFactor = 0;

    if(oldSize.height() != 0)
        posFactor = size.height() / oldSize.height();

    if(posFactor != 1)
    {
        if(myMax != 0)
            myFactor = size.height() / myMax;
        else
            myFactor = 0;

        if(myFactor > 1)
            scrollTo(0);
        else
            scrollTo(posFactor * myValue);
    }
}

void ScrollBar::setMinimum(const qreal min)
{
    if(min != myMin)
    {
        myMin = min;
        layoutChanged();
    }
}

void ScrollBar::setMaximum(const qreal max)
{
    if(max != myMax)
    {
        myMax = max;

        if(myMax != 0)
            myFactor = myBoundingRect.height() / myMax;
        else
            myFactor = 0;

        if(myFactor >= 1)
            myValue = 0;

        layoutChanged();
    }
}

qreal ScrollBar::getValue() const
{
    return myValue;
}

void ScrollBar::scrollTo(qreal value)
{
    if(value != myValue)
    {
        if(myFactor > 1)
            myValue = 0;
        else
        {
            if(value < myMin)
                myValue = myMin;
            else if(value > myMax - myBoundingRect.height())
                myValue = myMax - myBoundingRect.height();
            else
                myValue = value;
        }

        layoutChanged();
    }
}

void ScrollBar::scrollBy(qreal scrollBy)
{
    if(myFactor < 1)
        scrollTo(myValue + scrollBy);
}

void ScrollBar::ensureVisibility(qreal y)
{
    if(y > myValue + myBoundingRect.height())
    {
        scrollBy(10);
    }else if(y < myValue)
    {
        scrollBy(-10);
    }
}

void ScrollBar::mousePressEvent(QGraphicsSceneMouseEvent *event)
 {
    if (event->button() != Qt::LeftButton) {
        event->ignore();
        return;
    }

    if(event->pos().y() < sliderPos || event->pos().y() > sliderPos + sliderHeight)
        return;

    pressedControl = 1;
    setCursor(Qt::ClosedHandCursor);
 }

void ScrollBar::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(pressedControl == 1){
        if(myFactor != 0)
            scrollBy((event->pos().y() - event->lastPos().y()) / myFactor);
    }
}

void ScrollBar::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressedControl = 0;
    setCursor(Qt::ArrowCursor);
}
