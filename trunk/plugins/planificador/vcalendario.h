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

#ifndef VCALENDARIO_H
#define VCALENDARIO_H

#include <QGraphicsView>
#include "estilocalendario.h"
#include "itemcalendario.h"
#include "itemsemana.h"

class VCalendario : public QGraphicsView
{
Q_OBJECT
public:
    explicit VCalendario(QWidget *parent = 0);

    enum ModoMostrar {
      MostrarSemanasCompletas = 0,
      MostrarRango = 1,
    };

    int modoMostrar() const { return _modoMostrar; }

    int expandidoDiaSemana() const { return _DiaSemanaExpandido; }

    int semanaExpandidaNumero() const;

    ItemSemana *ItemSemanaExpandido() const { return _itemSemanaExpandido; }

    int contadorSemanas() const { return _contadorSemanas; }

    int anchoDia( int diaDeSemana ) const {
        if( diDeSemana >= 0 && diaDeSemana < 21 ) return _anchoDias[diaDeSemana]; else return 0;
    }

    EstiloCalendario * estilo() const { return pEstilo; }

    QList<Calendario*>* calendarios() { return pCalendarios; }
signals:
    void agregarVentana( QWidget * );
    void fechaExpandida( const QDate &fecha );

public slots:
    void expandirFecha( const QDate &fecha );
    void expandirDiaDeSemana( int diaDeSemana );
    void expandirSemana( int numSemana );
    void expandirSemana( ItemSemana *semana );
    void colapsarTodo();

    void setearRango( const QDate &inicio, const QDate &fin );
    void setearMes( int ano, int mes );

    void setearModoMostrar( ModoMostrar modo );
    void setearCalendarios( QList<Calendario *> *calendarios );

    void mostrarFormularioCita( Cita *cita );

    void dataChanged();
    void layoutChanged();

protected:
    void resizeEvent( QResizeEvent *event );

private slots:
    void onFormClosed( Cita *cita );

private:
    ItemSemana *_itemSemanaExpandido;
    int _modoMostrar;
    int _DiaSemanaExpandido;
    int _contadorSemanas;

    QDate _fechaInicio;
    QDate _fechaFin;

    QDate _rangoInicio;
    QDate _rangoFin;

    QDate _fechaExpandida;

    ItemCalendario *pCabecera;
    ItemCalendario *pPanelContenido;

    QList<ItemSemana *> _semanas;
    ItemSemana *_itemSemanaExpandido;

    int _anchoDias[21];

    EstiloCalendario *pEstilo;
    QList<Calendario*> *pCalendarios;
};

#endif // VCALENDARIO_H
