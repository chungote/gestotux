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
#ifndef MRECARGOS_H
#define MRECARGOS_H

#include <QSqlRelationalTableModel>

/**
Modelo para mantener los datos de los recargos que se aplican

        @author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class MRecargos : public QSqlRelationalTableModel
{
Q_OBJECT
public:
    MRecargos(QObject *parent = 0, bool relaciones = true );
    ~MRecargos();

    bool setData(const QModelIndex& index, const QVariant& value, int role);
    QVariant data(const QModelIndex& idx, int role) const;
    void agregarRecargo();
    void setearServicio( int id_servicio = -1 );
    int columnCount( const QModelIndex & index = QModelIndex() ) const;

public slots:
    void setearPrecioBase( double precio );

private:
        double _precio_base;
        int _servicio_actual;
};

#endif
