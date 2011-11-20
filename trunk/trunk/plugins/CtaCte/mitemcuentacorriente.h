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
#ifndef MITEMCUENTACORRIENTE_H
#define MITEMCUENTACORRIENTE_H

#include <QSqlRelationalTableModel>
#include "NumeroComprobante.h"
#include <QDateTime>

/**
	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class MItemCuentaCorriente : public QSqlRelationalTableModel
{
Q_OBJECT

public:
	enum TipoOperacionCtaCte {
	  Recibo = 0,
	  Factura = 1,
	  NotaCredito = 2,
          NotaDebito = 3,
          CobroServicio = 4,
          RecargoCobroServicio = 5,
          AnulacionFactura = 6
	 };

    MItemCuentaCorriente( QObject *parent = 0, bool saldos = false );
    ~MItemCuentaCorriente();
    QVariant data(const QModelIndex& item, int role) const;

    static int agregarOperacion( const QString &numero_cuenta, const QString &num_comb, const int &num_ref, const TipoOperacionCtaCte tipo, const QDate &fecha, const QString &descripcion, const double &aplicar );
    static int agregarOperacion( const QString &numero_cuenta, const NumeroComprobante &num_comb, const int &num_ref, const TipoOperacionCtaCte tipo, const QDate &fecha, const QString &descripcion, const double &aplicar );
    static double valorOperacion( const int id_op_ctacte );
    static int buscarIDPorComprobante( TipoOperacionCtaCte tipo, int id );
    static bool cancelarOperacion( const int id_op_ctacte, QString razon, QDateTime fechahora );
    static QString buscarNumeroCuentaCorrientePorIdOperacion( const int id_op_ctacte );


    int columnCount(const QModelIndex &parent) const;
    bool seleccionarNumCuenta( const QString &num_cuenta );

private:
    QHash<int, double> *saldos;
    bool _saldo;
    QString _num_cuenta;

};

#endif
