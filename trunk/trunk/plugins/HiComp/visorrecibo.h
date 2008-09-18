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
#ifndef VISORRECIBO_H
#define VISORRECIBO_H

#include <QSvgWidget>
#include <QAction>
#include "recibo.h"

/**
	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class visorRecibo : public QSvgWidget
{
  Q_OBJECT
public:
    visorRecibo( QWidget *parent = 0 );
    ~visorRecibo();
    QString nombre();
    Recibo * recibo();
    void verRecibo( int idDB );

private:
    Recibo *rec;
    QAction *ActCerrar;
    QAction *ActImprimir;
    QAction *ActPdf;

public slots:
    void imprimir();

protected slots:
    void aPdf();

signals:
	void agregarVentana( QWidget * );
};

#endif
