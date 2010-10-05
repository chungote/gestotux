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

#include "vcategoriasgastos.h"
#include <QWidget>
#include <QIcon>
#include <QTableView>
#include "mcategoriasgastos.h"
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>

VCategoriasGastos::VCategoriasGastos( QWidget *parent )
: EVLista(parent)
{
    this->setObjectName( "categorias_gastos" );
    this->setWindowTitle( "Categorias de gastos" );
    this->setWindowIcon( QIcon( ":/imagenes/categorias.png" ) );

    this->modelo = new MCategoriasGastos( this );
    this->vista->setModel( this->modelo );
    this->vista->hideColumn( 0 );
    this->modelo->select();

    this->addAction( ActAgregar );
    this->addAction( ActCerrar );
}

void VCategoriasGastos::agregar(bool autoeliminarid )
{
    QSqlRecord registro = this->modelo->record();
    if( autoeliminarid ) {
        registro.remove( registro.indexOf( "id_categorias_gastos" ) );
    }
    registro.setValue( "nombre", "" );
    if( this->modelo->insertRecord( -1, registro ) )  {
        return;
    } else {
        qWarning( "Error alinsertar el registro" );
        qDebug( QString( "Detalles: tipo: %1, errno: %2, descripcion: %3" ).arg( modelo->lastError().type() ).arg( modelo->lastError().number() ).arg( modelo->lastError().text() ).toLocal8Bit() );
    }
}
