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

#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include "calendaritem.h"

class ScrollAreaItem;

class ScrollBar : public CalendarItem
{
public:
    ScrollBar(ScrollAreaItem *scrollArea = 0, QGraphicsScene *scene = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
        QWidget *widget);

    virtual void layoutChanged();

    qreal getValue() const;
    void scrollTo(qreal value);
    void scrollBy(qreal srollBy);

    void setMinimum(qreal min);
    void setMaximum(qreal max);

    virtual void onResize(const QSizeF &size, const QSizeF &oldSize);

    void ensureVisibility(qreal y);

    int orientation;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    qreal myMin;
    qreal myMax;
    qreal myValue;
    qreal myFactor;

    qreal sliderMax;
    qreal sliderPos;
    qreal sliderHeight;

    int pressedControl;

    ScrollAreaItem *ptrArea;
    //ScrollHandle myHandle;
};

#endif
