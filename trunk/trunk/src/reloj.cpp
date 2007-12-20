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
#include "reloj.h"

#include <QTimer>
#include <QTime>
#include <QPainter>

Reloj::Reloj(QWidget *parent)
 : QLCDNumber( parent )
{
 setSegmentStyle(Filled);

 QTimer *timer = new QTimer(this);
 connect( timer, SIGNAL( timeout() ), this, SLOT( showTime() ) );
 timer->start(1000);
}


Reloj::~Reloj()
{
}

void Reloj::showTime()
{
     QTime time = QTime::currentTime();
     QString text = time.toString("hh:mm");
     if ((time.second() % 2) == 0)
         text[2] = ' ';
     display(text);
}
