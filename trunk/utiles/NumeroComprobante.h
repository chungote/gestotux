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

#ifndef NUMEROCOMPROBANTE_H
#define NUMEROCOMPROBANTE_H

#include <QObject>
#include <QPair>

class NumeroComprobante : public QObject
{
    Q_OBJECT
public:
    explicit NumeroComprobante( QObject *parent = 0 );
    explicit NumeroComprobante( QObject *padre = 0, int serie = 0, int numero = 0 );
    void setearNumeroSerie( int serie );
    void setearNumero( int numero );
    int serie() const;
    int numero() const;
    QString aCadena();
    bool esValido() const;

private:
    QPair<int,int> _dato;
    int cuentaRecursivo( const int dato );
    QString numeroLleno();
    QString serieLleno();
};

#endif // NUMEROCOMPROBANTE_H
