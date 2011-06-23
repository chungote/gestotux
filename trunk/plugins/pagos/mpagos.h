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
#ifndef MPAGOS_H
#define MPAGOS_H

#include <QSqlRelationalTableModel>
#include "NumeroComprobante.h"

/**
 * \brief Modelo de los pagos
 *
 * Modelo que administra los pagos realizados en el programa.
 *
 * @author Esteban Zeller <juiraze@yahoo.com.ar>
 */
class MPagos : public QSqlRelationalTableModel
{
    Q_OBJECT

public:
    enum FormaPago {
        SinPagar = 0,
        Efectivo = 1,
        Otro = 2
    };

    MPagos(QObject *parent = 0, bool relaciones = false );

    QVariant data(const QModelIndex& item, int role) const;

    int agregarRecibo( int id_cliente, QDate fecha, QString contenido, double total, bool efectivo, bool pagado = true );

    int buscarUltimoNumeroRecibo() const;
    QDate buscarFechaUltimoRecibo() const;
    bool setearComoPagado( const int id_recibo, const bool efectivo );
    bool buscarSiPagado( const int serie, const int numero );
    bool buscarSiPagado( const NumeroComprobante num );
    int buscarIdPorSerieNumero( const NumeroComprobante num );
    int buscarIdPorSerieNumero( const int serie, const int numero );
    double buscarImporte( NumeroComprobante num );
    NumeroComprobante &buscarNumeroComprobantePorId( const int id_recibo );

    static NumeroComprobante &buscarMenorSerieNumeroPagado();
    static int numeroSerieActual();
    static int numeroReciboActual( const int serie );
    static NumeroComprobante &proximoSerieNumeroRecibo();

private:
    void inicializar();
    void relacionar();
};

#endif
