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
#ifndef HICOMPPRESUPUESTO_H
#define HICOMPPRESUPUESTO_H

#include <epresupuesto.h>

class QSqlRecord;
/**
 * \brief Implmenetacion de plugin presupuesto para HiComp
 *
 * Plugin de implmentacion de presupuesto para la compania HiComp Computacion
 *
 *	@author Esteban Zeller <juiraze@yahoo.com.ar>
 */
class HiCompPresupuesto : public QObject, EPresupuesto
{
Q_OBJECT
Q_INTERFACES(EPresupuesto)
public:
    QString nombre() const;
    double version() const;
    double total();
    QString cliente();
    QString titulo();
    QTextDocument * getDocumento();
    QTextTable * tablaProductos();
    void inicializar();
    QDate fecha();
    void setCliente( QString nombre );
    void setFecha( QDate fecha );
    void setTituloPersonalizado( QString titulo );
    void setTotal( double total );
    void generarTabla( QSqlTableModel *modelo, QString titulo, bool cabecera );
    void limpieza();
    void regenerar( const QTextDocument *doc );

};

#endif
