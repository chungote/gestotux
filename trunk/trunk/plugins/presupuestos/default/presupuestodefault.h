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
#ifndef DEFAULT_H
#define DEFAULT_H

#include "epresupuesto.h"
#include <QObject>
#include <QTextDocument>
#include <QTextTable>
#include <QDate>
class QFile;

/**
 *  \brief Implementacion predeterminada de un presupuesto
 *    
 *  Implementacion predeterminada del modelado de un presupuesto para gestotux
 *	@author Esteban Zeller <juiraze@yahoo.com.ar>
 */
class PresupuestoDefault : public QObject, EPresupuesto
{
Q_OBJECT
Q_INTERFACES(EPresupuesto)
public:
    QString nombre() const;
    double version() const;
    QTextTable *tablaProductos();
    void setTituloPersonalizado( const QString titulo );
    void setCliente( const QString cliente );
    void setFecha( const QDate fecha );
    void setTablaProductos ( QTextTable* theValue );
    void setTotal( const double t );
    QTextDocument * getDocumento();
    QString cliente();
    QString titulo();
    double total();
    QDate fecha();
    void generarTabla( QSqlTableModel *mod, const QString tituloTabla, const bool cabeceras );
    void regenerar( const QTextDocument *docCont );

protected:
    QTextDocument *_doc;
    double _total;
    QString _texto_destinatario;
    QString _titulo;
    QDate _fecha;
    QTextTable *_tablaProductos;
    QFile *archivo;
};

#endif
