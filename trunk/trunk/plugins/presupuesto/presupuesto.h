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
#ifndef PRESUPUESTO_H
#define PRESUPUESTO_H

#include <QObject>
#include <QSqlRecord>
#include <QPluginLoader>
#include <epresupuesto.h>
#include <QTextDocument>
#include <QTextTable>
#include <QDate>
class QPainter;
/**
 * \brief Clase de presupuesto
 *
 *  Clase que sirve como contenedor de un presupuesto y puede hacer todas sus operaciones
 *
 *  @author Esteban Zeller <juiraze@yahoo.com.ar>
 */
class Presupuesto : public QObject
{
Q_OBJECT
public:
	Presupuesto(QObject *parent = 0);
	~Presupuesto();
	bool registro( int id );
	void imprimir( QPainter *pintador );
	bool esValido();
	void setFecha ( const QDate& theValue );
	QDate fecha() const;
	void setTitulo ( const QString& theValue );
	QString titulo() const;
	void setTotal ( double theValue );
	double total() const;
	void setId_cliente ( int theValue );
	int id_cliente() const;
	void setTexto_destinatario ( const QString& theValue );
	QString texto_destinatario() const;
	void generarDoc( const QTextDocument *docCont );
	void generarTablaProductos( QSqlTableModel *modelo, const QString tituloTabla, const bool cabeceras );
    QTextDocument * previsualizacion();

private:
	EPresupuesto *_plugin;
	QPluginLoader *loader;
	int _id_cliente;
	QSqlRecord _registro;
};

#endif
