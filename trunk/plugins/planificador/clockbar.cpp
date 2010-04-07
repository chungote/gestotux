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
#include "clockbar.h"

ClockBar::ClockBar(QGraphicsItem *parent, QGraphicsScene *scene) : 
    CalendarItem(parent, scene)
{
    prepareGeometryChange();

    QFont font("Arial", 18, QFont::Normal);
    QFontMetrics fm(font);
    myBoundingRect.adjust(0,0,10 + fm.width("MM"), 24*10*4);
}

void ClockBar::paint(QPainter *painter,
    const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int width = (int)myBoundingRect.width();
    int height = (int)myBoundingRect.height();

    painter->setBrush(QBrush(QColor(200,200,200)));
    painter->drawRect(0.5,0.5,width-0.5,height-0.5);

    QFont font("Arial", 18, QFont::Normal);
    QFontMetrics fm(font);
    QRectF hourRect(-5, 0, fm.width("MM"), fm.height()); // = fm.tightBoundingRect("MM"); //

    painter->setFont(font);
    painter->setPen(QPen(QColor(80,80,80)));

    int y = 0;
    for(int i=0;i<24;i++)
    {
        painter->drawLine(0,y,width,y);
        painter->drawText(hourRect, Qt::AlignRight, QString::number(i));
        hourRect.adjust(0, 4*10, 0, 4*10);
        y += 4*10;
    }

    font.setPixelSize(10);
    painter->setFont(font);
    fm = painter->fontMetrics();
    y = 0;
    int x = hourRect.left() + hourRect.width();
    for(int i=0;i<24;i++)
    {
        painter->drawText(x, y + fm.ascent(), "00");
        y += 4*10;
    }
}
