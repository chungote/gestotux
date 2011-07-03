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

#include "MItemPresupuesto.h"
#include <QSqlQuery>
#include <QSqlError>

MItemPresupuesto::MItemPresupuesto(QObject *parent) :
    QSqlRelationalTableModel(parent) {
    inicializar();
    relacionar();
}


void MItemPresupuesto::inicializar() {
    setTable( "item_presupuesto" );
    setHeaderData( 0, Qt::Horizontal, "#Orden" );
    setHeaderData( 1, Qt::Horizontal, "#Presupuesto" );
    setHeaderData( 2, Qt::Horizontal, "Cantidad" );
    setHeaderData( 3, Qt::Horizontal, "Texto" );
    setHeaderData( 4, Qt::Horizontal, "Precio Unitario" );
    setHeaderData( 5, Qt::Horizontal, "#Producto" );

}

void MItemPresupuesto::relacionar() {}

/*!
 * \fn MItemPresupuesto::agregarItemPresupuesto(  const int id_presupuesto, const dobule cantidad, const QString texto, const double precio_unitario )
 * Agrega un item de presupuesto con el presupuesto relacionado pasado como parametro
 * @param id_presupuesto Identificador del Presupuesto
 * @param cantidad Cantidad del item
 * @param texto Texto del item
 * @param precio Precio unitario del item
 * @returns Verdadero si se pudo guardar correctamente
 */
bool MItemPresupuesto::agregarItemPresupuesto( const int id_presupuesto, const double cantidad, const QString texto, const double precio_unitario ) {
 QSqlQuery cola;
 if( ! cola.prepare( "INSERT INTO item_presupuesto( id_presupuesto, cantidad, texto, precio_unitario ) VALUES ( :id_presupuesto, :cantidad, :texto, :precio_unitario );" ) ) {
     qDebug( "Error al intentar preparar la cola de inserción" );
     qDebug( QString( "Error: %1 - %2" ).arg( cola.lastError().number() ).arg( cola.lastError().text() ).toLocal8Bit() );
 }
 ///@todo Si Sqlite verificar que existe presupuesto
 cola.bindValue( ":id_presupuesto", id_presupuesto );
 cola.bindValue( ":cantidad", cantidad );
 cola.bindValue( ":texto", texto );
 cola.bindValue( ":precio_unitario", precio_unitario );
 if( cola.exec() ) {
     return true;
 } else {
     qDebug( "Error al intentar insertad valor de item de presupuesto" );
     qDebug( QString( "Error: %1 - %2 - %3" ).arg( cola.lastError().number() ).arg( cola.lastError().text() ).arg( cola.lastQuery() ).toLocal8Bit() );
     return false;
 }

}
