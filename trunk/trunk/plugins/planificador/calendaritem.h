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

#ifndef CALENDARITEM_H
#define CALENDARITEM_H

#include <QGraphicsItem>
#include <QPainterPath>
#include <QSizeF>

/*!
    \class CalendarItem
    \brief Base class for all Graphics View items.
*/

class CalendarItem : public QGraphicsItem
{

public:
    CalendarItem(QGraphicsItem *parent = 0,
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

#endif
