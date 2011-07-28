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
#ifndef MSERVICIOS_H
#define MSERVICIOS_H

#include <QSqlTableModel>
#include <QDateTime>

/**
Clase que mantiene y administra los datos de los distintos tipos de servicios que tiene el programa

        @author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class MServicios : public QSqlTableModel
{
Q_OBJECT
public:
    MServicios(QObject *parent = 0);
    ~MServicios();

    QVariant data(const QModelIndex& item, int role) const;

    /*! \enum FormaIncompleto
      *  Define la manera en que se cobran los dias cuando un cliente se adihere a un serivicio fuera del inicio del periodo.
      */
    enum FormaIncompleto {
        DiasFaltantes = 1, /**< Cuenta los dias que faltan hasta el siguiente periodo, divide el valor del servicio por la cantidad de dias en el periodo y calcula el total con estos dos datos */
        MesCompleto = 2 /**< Cobra un periodo completo aunque sea un dia antes del fin del periodo */
    };

    /*! \enum Periodo
     *  Tipos de periodos que podemos considerar al generar el cobro de los servicios
     */
    enum Periodo {
        Semanal = 1, /**< Una semana - 7 dias */
        Quincenal = 2, /**< Dos semana - 15 dias */
        Mensual = 3,  /**< Un mes - 28 a 31 dias */
        BiMensual = 4,  /**< Dos meses - 56 a 62 dias */
        Trimestral = 5, /**< Tres meses */
        Cuatrimestral = 6, /**< Cuatro meses */
        Seximestral = 7, /**< Seis meses */
        Anual = 8, /**< 12 meses - 365 dias */
        Invalido = -1 /** Invalido - Para casos de error */
    };

    bool asociarCliente( int id_cliente, int id_servicio, QDateTime fecha = QDateTime::currentDateTime() );
    bool agregarServicio( QString nombre, QString detalle, QDate fecha_alta, double precio_base, int periodo, int dia_cobro, int forma_incompleto );

    static double precioBase( int id_servicio );
    static MServicios::Periodo obtenerPeriodo( const int id_servicio );
    static QString getNombreServicio( int id_servicio );
    static QDate getFechaAlta( const int id_servicio );

};

#endif
