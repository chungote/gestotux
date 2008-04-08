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
#ifndef ERENDERIZADORINFORME_H
#define ERENDERIZADORINFORME_H

#include <QObject>
class QTextDocument;
class FormFiltro;
#include <QSqlQuery>
#include <QDate>
#include <QPair>
/**
	@author Esteban Zeller <juiraze@yahoo.com.ar>
*/
class ERenderizadorInforme : public QObject
{
 Q_OBJECT
public:
    ERenderizadorInforme( QObject *padre = 0);
    ~ERenderizadorInforme();
    void setDocumento( QTextDocument *doc );
    void setPropiedades( FormFiltro *f );
    void hacerInforme();
    void hacerCabecera();
    void setarCabeceraFiltros();
    void generarCola();

private:
    QTextDocument *_doc;
	bool _filtra_tipo,_filtra_estab,_filtra_categoria,_filtra_fecha,_filtra_rango_fecha;
	int _id_cat,_id_estab,_id_tipo;
	QPair<QDate,QDate> _rango_fechas;
	QSqlQuery cola;
	QDate _fecha;
};

#endif
