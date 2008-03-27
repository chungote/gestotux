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
#include "emovimiento.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QVariant>

EMovimiento::EMovimiento(QObject *parent)
 : QObject(parent)
{
 setTipoMov( EMovimiento::invalido );
 id_db = -1;
}


EMovimiento::~EMovimiento()
{
}

int EMovimiento::tipoMov() const
{
	return tipo_mov;
}


void EMovimiento::setTipoMov( const tipo& theValue )
{
 if( tipo_mov == EMovimiento::invalido )
 {
  tipo_mov = theValue;
 }
}


/*!
    \fn EMovimiento::cargarMovimiento( int idDb )
 */
bool EMovimiento::cargarMovimiento( int idDb )
{
 QSqlQuery cola;
 if( cola.exec( QString( "SELECT * FROM car_tri WHERE id_tri = '%1'" ).arg( idDb ) ) )
 {
  if( cola.next() )
  {
	DTA = cola.record().value( "dta" ).toString();
	id_db = cola.record().value( "id_tri" ).toInt();
	setCategoria( cola.record().value( "id_categoria" ).toInt() );
	// Busco el establecimiento
	switch( cola.record().value( "razon" ).toInt() )
	{
		case compra:
		{
			//cargo el vendedor y el destino
			setVendedor( cola.record().value( "id_vendedor" ).toInt() );
			comprador.first = -1;
			origen.first = -1;
			setEstablecimientoDestino( cola.record().value( "id_estab_destino" ).toInt() );
			break;
		}
		case venta:
		{
			//cargo el comprador y el origen
			setComprador( cola.record().value( "id_comprador" ).toInt() );
			vendedor.first = -1;
			destino.first = -1;
			setEstablecimientoOrigen(cola.record().value( "id_estab_origen" ).toInt());
			break;
		}
		case mudanza:
		{
			//cargo el destino y el origen
			vendedor.first = -1;
			comprador.first = -1;
			setEstablecimientoOrigen( cola.record().value( "id_estab_origen" ).toInt() );
			setEstablecimientoDestino( cola.record().value( "id_estab_destino" ).toInt() );
			break;
		}
		case stock:
		{
			vendedor.first = -1;
			comprador.first = -1;
			origen.first = -1;
			setEstablecimientoDestino( cola.record().value( "id_estab_destino" ).toInt() );
			break;
		}
	}
  }
  else
  {
 	qWarning( QString( "Error al next buscar el tri\n Error: %1\n %2" ).arg( cola.lastError().text() ).arg( cola.lastQuery() ).toLocal8Bit() );
	return false;
  }
 }
 else
 {
	qWarning( QString( "Error al buscar el tri\n Error: %1\n %2" ).arg( cola.lastError().text() ).arg( cola.lastQuery() ).toLocal8Bit() );
  	return false;
 }
}


/*!
    \fn EMovimiento::caravanas()
 */
QStringList EMovimiento::caravanas()
{
    /// @todo implement me
	//Devulve la lista de los codigos de caravanas que corresponden a este TRI
}


QString EMovimiento::getDTA() const
{
	return DTA;
}


void EMovimiento::setDTA ( const QString& theValue )
{
	DTA = theValue;
}


/*!
    \fn EMovimiento::cargarNombreCategoria( int idDB )
 */
void EMovimiento::cargarNombreCategoria( int idDB )
{
 QSqlQuery cola2;
 if( cola2.exec( QString( "SELECT nombre FROM car_categorias WHERE id_categorias = '%1'" ).arg( idDB ) ) )
 {
	if( cola2.next() )
	{
		categoria.second = cola2.record().value(0).toString();
	}
 }
 else
 {
 	qWarning( QString( "Error al buscar el tri\n Error: %1\n %2" ).arg( cola2.lastError().text() ).arg( cola2.lastQuery() ).toLocal8Bit() );
 }
}


/*!
    \fn EMovimiento::cargarNombreComprador( int idDB )
 */
void EMovimiento::cargarNombreComprador( int idDB )
{
 QSqlQuery cola2;
 if( cola2.exec( QString( "SELECT apellido || ', ' || nombre FROM clientes WHERE id_cliente = '%1'" ).arg( idDB ) ) )
 {
	if( cola2.next() )
	{
		comprador.second = cola2.record().value(0).toString();
	}
 }
 else
 {
 	qWarning( QString( "Error al buscar el tri\n Error: %1\n %2" ).arg( cola2.lastError().text() ).arg( cola2.lastQuery() ).toLocal8Bit() );
 }
}


/*!
    \fn EMovimiento::setComprador( int id )
 */
void EMovimiento::setComprador( int id )
{
 comprador.first = id;
 cargarNombreComprador( id );
}


/*!
    \fn EMovimiento::setCategoria( int id )
 */
void EMovimiento::setCategoria( int id )
{
 categoria.first = id;
 cargarNombreCategoria( id );
}


/*!
    \fn EMovimiento::cargarNombreVendedor( int idDB )
 */
void EMovimiento::cargarNombreVendedor( int idDB )
{
  QSqlQuery cola2;
 if( cola2.exec( QString( "SELECT apellido || ', ' || nombre FROM clientes WHERE id_cliente = '%1'" ).arg( idDB ) ) )
 {
	if( cola2.next() )
	{
		vendedor.second = cola2.record().value(0).toString();
	}
 }
 else
 {
 	qWarning( QString( "Error al buscar el tri\n Error: %1\n %2" ).arg( cola2.lastError().text() ).arg( cola2.lastQuery() ).toLocal8Bit() );
 }
}


/*!
    \fn EMovimiento::setVendedor( int idDB )
 */
void EMovimiento::setVendedor( int idDB )
{
 vendedor.first = idDB;
 cargarNombreVendedor( idDB );
}


/*!
    \fn EMovimiento::cargarNombreEstablecimientoDestino( int idDB )
 */
void EMovimiento::cargarNombreEstablecimientoDestino( int idDB )
{
 QSqlQuery cola2;
 if( cola2.exec( QString( "SELECT nombre FROM car_establecimientos WHERE id_establecimiento = '%1'" ).arg( idDB ) ) )
 {
 	if( cola2.next() )
	{
		destino.second = cola2.record().value(0).toString();
	}
 }
 else
 {
 	qWarning( QString( "Error al buscar el tri\n Error: %1\n %2" ).arg( cola2.lastError().text() ).arg( cola2.lastQuery() ).toLocal8Bit() );
 }
}


/*!
    \fn EMovimiento::setEstablecimientoDestino( int idDB )
 */
void EMovimiento::setEstablecimientoDestino( int idDB )
{
 destino.first = idDB;
 cargarNombreEstablecimientoDestino( idDB );
}

/*!
    \fn EMovimiento::cargarNombreEstablecimientoDestino( int idDB )
 */
void EMovimiento::cargarNombreEstablecimientoOrigen( int idDB )
{
 QSqlQuery cola2;
 if( cola2.exec( QString( "SELECT nombre FROM car_establecimientos WHERE id_establecimiento = '%1'" ).arg( idDB ) ) )
 {
 	if( cola2.next() )
	{
		origen.second = cola2.record().value(0).toString();
	}
 }
 else
 {
 	qWarning( QString( "Error al buscar el tri\n Error: %1\n %2" ).arg( cola2.lastError().text() ).arg( cola2.lastQuery() ).toLocal8Bit() );
 }
}


/*!
    \fn EMovimiento::setEstablecimientoDestino( int idDB )
 */
void EMovimiento::setEstablecimientoOrigen( int idDB )
{
 origen.first = idDB;
 cargarNombreEstablecimientoOrigen( idDB );
}


QDate EMovimiento::getFecha() const
{
	return fecha;
}


void EMovimiento::setFecha ( const QDate& theValue )
{
	fecha = theValue;
}


/*!
    \fn EMovimiento::guardar()
 */
int EMovimiento::guardar()
{
 if( tipoMov() != invalido )
 {
 	QSqlQuery cola;
	QString scola( " car_tri( dta, razon, id_categoria, id_estab_destino, id_estab_origen, id_comprador, id_vendedor ) VALUES ( %1, %2, %3, %4, %5, %6, %7 )" );
   	if( id_db  == -1 )
 	{
  		// Agrego un nuevo registro
		scola.prepend( "INSERT INTO" );
 	}
 	else
 	{
  		// Actualizo el registro actual
		scola.prepend( "UPDATE" );
		scola.append( QString( " WHERE id_tri = '%1' LIMIT 1").arg( id_db ) );
 	}
	// reemplazo los parametros
	scola.arg( DTA ).arg( tipo_mov ).arg( categoria.first ).arg( destino.first ).arg( origen.first ).arg( comprador.first ).arg( vendedor.first );
	if( cola.exec( scola ) )
	{
		//Devulevo el id que inserte
		if( id_db != -1 )
		{
			return id_db;
		}
		else
		{
			QSqlQuery cola1( "SELECT seq FROM sqlite_sequences WHERE name = 'car_tri' LIMIT 1" );
			if( cola.next() )
			{
				return cola.record().value(0).toInt();
			}
			else
			{
				qWarning( QString( "Error al obtener el numero de tri al hacer insercion\n Error: %1\n %2" ).arg( cola.lastError().text() ).arg( cola.lastQuery() ).toLocal8Bit() );
				return -1;
			}
		}
	}
	else
	{
		qWarning( QString( "Error al insertar o actualizar el registro de tri\n Error: %1\n %2" ).arg( cola.lastError().text() ).arg( cola.lastQuery() ).toLocal8Bit() );
		return -2;
	}
 }
 else
 {
  qWarning( "Error al intentar guardar o acutalizar el registro, su tipo fue invalido" );
  return -14;
 }
}
