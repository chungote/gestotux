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
#ifndef MCUENTACORRIENTE_H
#define MCUENTACORRIENTE_H

#include <QSqlRelationalTableModel>
#include <QDateTime>

/**
Clase de modelo para las cuentas correintes

        @author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class MCuentaCorriente : public QSqlRelationalTableModel
{
Q_OBJECT
public:

    enum EstadoCuenta {
        LimiteCorrecto = 0,
        LimiteExcedido = 1,
        EnLimite = 2,
        ErrorBuscarLimite = 3
    };

    enum Error {
        ErrorNumeroCuenta = -2,
        ErrorClienteInvalido = -3,
        ErrorBuscarSaldo = -1
    };


    MCuentaCorriente( QObject *parent = 0, bool relaciones = true );
    QVariant data(const QModelIndex& item, int role) const;
    void filtrarSoloDeudoras( bool sino );
    static QString obtenerNumeroCuentaCorriente( const int id_cliente );
    static int verificarSaldo( const QString numero_cuenta, double aplicar );
    static bool actualizarSaldo( const QString numero_cuenta, const double aplicar );
    static double saldo( const QString numero_cuenta );
    static bool agregarCuentaCorrientePredeterminada( const int id_cliente, const QDateTime fecha_alta = QDateTime::currentDateTime() );

};

#endif
