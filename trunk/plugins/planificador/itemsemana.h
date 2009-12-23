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

#ifndef ITEMSEMANA_H
#define ITEMSEMANA_H

#include <QDate>
#include <QGraphicsScene>
#include "vcalendario.h"

class ItemSemana : public ItemCalendario
{
public:
    ItemSemana(VCalendario *calendarView,
               const QDate &fecha,
               const QDate &fin,
               QGraphicsItem *parent = 0,
               QGraphicsScene *scene = 0);
    ~ItemSemana() {}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                    QWidget *widget);

        virtual void layoutChanged();
        virtual void dataChanged();

        bool tieneFecha(const QDate &fecha );
        int diaDeSemana(const QDate &fecha );

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    private:
        VCalendario *pCalendario;

        ItemCalendario *dayHeaderContainer;
        ItemCalendario *dayContentContainer;

        ItemCalendario *ptrScrollPane;

        /*ScrollAreaItem *ptrScrollArea;

        ClockBar *clockBar;*/

        QDate _fecha;
        QDate _rangoInicio;
        QDate _rangoFin;

        QList <ItemDia *> _dias;

        QFont _fuente;

        friend class VCalendario;
        friend class ItemDia;
        friend class ItemContenidoDia;
        friend class ItemCita;
};

#endif // ITEMSEMANA_H
