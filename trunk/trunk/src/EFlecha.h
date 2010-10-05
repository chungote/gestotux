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

#ifndef EFLECHA_H
#define EFLECHA_H

#include <QWidget>
#include <QLineF>
#include <QPaintEvent>
#include <QColor>

class EFlecha : public QWidget, public QLineF
{
    Q_OBJECT
public:
    explicit EFlecha( QWidget *parent );
    explicit EFlecha( QWidget *parent, QWidget *origen, QWidget *destino, int tamFlecha );
    void setearOrigen( QWidget *origen );
    void setearDestino( QWidget *destino );
    void setearTamFlecha( int tam );
    QSize sizeHint() const;

    enum PosicionWidgets {
        EsquinaSuperior = 0,
        EsquinaInferior = 0,
        Medio = 0
    };
protected:
    void paintEvent( QPaintEvent *evento );

private:
    QWidget *origen;
    QWidget *destino;
    float tamFlecha;

};

#endif // EFLECHA_H
