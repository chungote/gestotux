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
#include <QProgressDialog>
#include <QErrorMessage>

EMovimiento::EMovimiento(QObject *parent)
 : QObject(parent)
{
 tipo_mov = EMovimiento::invalido;
 id_db = -1;
}


EMovimiento::~EMovimiento()
{
}

int EMovimiento::tipoMov() const
{
	return tipo_mov;
}


void EMovimiento::setTipoMov( const int& theValue )
{
 if( tipo_mov == EMovimiento::invalido )
 {
  tipo_mov = theValue;
  qDebug( QString( "Seteado tipo de movimiento a %1 " ).arg( tipo_mov ).toLocal8Bit() );
 }
}


/*!
    \fn EMovimiento::cargarMovimiento( int idDb )
	Carga todos los datos relacionados con el id de la base de datos de un movimiento
	@param idDB Identificador de clave primaria que indica el movimiento que se debe cargar
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
	setTipoMov( cola.record().value( "razon" ).toInt() );
	switch( tipoMov() )
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
	// Cargo las caravanas que corresponden a este tri
	return cargarCaravanas();
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
	Devuleve la lista de caravanas que componen este tri
	@return Objecto QStringList con los codigos de caravanas
 */
QStringList EMovimiento::caravanas()
{
	//Devulve la lista de los codigos de caravanas que corresponden a este TRI
	if( !_caravanas.isEmpty() )
	{
		return _caravanas;
	}
	else
	{
		return QStringList();
	}
	
}


QString EMovimiento::getDTA() const
{
	return DTA;
}


bool EMovimiento::setDTA ( const QString& theValue )
{
	// Verifico que no exista antes
	QSqlQuery cola;
	if( cola.exec(QString( "SELECT id_tri FROM car_tri WHERE dta = '%1'" ).arg( theValue ) ) )
	{
		if( cola.next() )
		{
			qWarning( "El #DTA que esta intentando utilizar para este TRI ya existe" );
			return false;
		}
		else
		{
			qDebug( "Seteando DTA" );
			DTA = theValue;
			return true;
		}
	}
	else
	{
		qWarning( QString( "Error al buscar si existe anteriormente un dta\n Error: %1\n %2" ).arg( cola.lastError().text() ).arg( cola.lastQuery() ).toLocal8Bit() );
	}
}


/*!
    \fn EMovimiento::cargarNombreCategoria( int idDB )
	Funcion que carga el nombre de la categoria en la variable del objeto
	@param idDB identificador de clave primaria de la categoria
 */
void EMovimiento::cargarNombreCategoria( const int idDB )
{
 QSqlQuery cola2;
 if( cola2.exec( QString( "SELECT nombre FROM car_categorias WHERE id_categoria = '%1'" ).arg( idDB ) ) )
 {
	if( cola2.next() )
	{
		categoria.second = cola2.record().value(0).toString();
	}
 }
 else
 {
 	qWarning( QString( "Error al buscar el nombre de la categoria\n Error: %1\n %2" ).arg( cola2.lastError().text() ).arg( cola2.lastQuery() ).toLocal8Bit() );
 }
}


/*!
    \fn EMovimiento::cargarNombreComprador( int idDB )
	Funcion que carga el nombre del comprador en la variable del objeto
	@param idDB identificador de clave primaria del cliente comprador
 */
void EMovimiento::cargarNombreComprador( const int idDB )
{
 QSqlQuery cola2;
 if( cola2.exec( QString( "SELECT apellido || ', ' || nombre FROM clientes WHERE id = '%1'" ).arg( idDB ) ) )
 {
	if( cola2.next() )
	{
		comprador.second = cola2.record().value(0).toString();
	}
 }
 else
 {
 	qWarning( QString( "Error al buscar el cliente como comprador\n Error: %1\n %2" ).arg( cola2.lastError().text() ).arg( cola2.lastQuery() ).toLocal8Bit() );
 }
}


/*!
    \fn EMovimiento::setComprador( int id )
 */
void EMovimiento::setComprador( const int id )
{
 comprador.first = id;
 cargarNombreComprador( id );
}


/*!
    \fn EMovimiento::setCategoria( int id )
 */
void EMovimiento::setCategoria( const int id )
{
 categoria.first = id;
 cargarNombreCategoria( id );
}


/*!
    \fn EMovimiento::cargarNombreVendedor( int idDB )
	Funcion que carga el nombre del vendedor en la variable del objeto
	@param idDB identificador de clave primaria del cliente vendedor
 */
void EMovimiento::cargarNombreVendedor( const int idDB )
{
  QSqlQuery cola2;
 if( cola2.exec( QString( "SELECT apellido || ', ' || nombre FROM clientes WHERE id = '%1'" ).arg( idDB ) ) )
 {
	if( cola2.next() )
	{
		vendedor.second = cola2.record().value(0).toString();
	}
 }
 else
 {
 	qWarning( QString( "Error al buscar el cliente como vendedor\n Error: %1\n %2" ).arg( cola2.lastError().text() ).arg( cola2.lastQuery() ).toLocal8Bit() );
 }
}


/*!
    \fn EMovimiento::setVendedor( int idDB )
 */
void EMovimiento::setVendedor( const int idDB )
{
 vendedor.first = idDB;
 cargarNombreVendedor( idDB );
}


/*!
    \fn EMovimiento::cargarNombreEstablecimientoDestino( int idDB )
 */
void EMovimiento::cargarNombreEstablecimientoDestino( const int idDB )
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
 	qWarning( QString( "Error al buscar el establecimiento de destino\n Error: %1\n %2" ).arg( cola2.lastError().text() ).arg( cola2.lastQuery() ).toLocal8Bit() );
 }
}


/*!
    \fn EMovimiento::setEstablecimientoDestino( int idDB )
 */
void EMovimiento::setEstablecimientoDestino( const int idDB )
{
 destino.first = idDB;
 cargarNombreEstablecimientoDestino( idDB );
}

/*!
    \fn EMovimiento::cargarNombreEstablecimientoDestino( int idDB )
 */
void EMovimiento::cargarNombreEstablecimientoOrigen( const int idDB )
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
 	qWarning( QString( "Error al buscar el establecimiento de origen\n Error: %1\n %2" ).arg( cola2.lastError().text() ).arg( cola2.lastQuery() ).toLocal8Bit() );
 }
}


/*!
    \fn EMovimiento::setEstablecimientoDestino( int idDB )
 */
void EMovimiento::setEstablecimientoOrigen( const int idDB )
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
int EMovimiento::guardar( QProgressDialog *dialogo )
{
 if( tipoMov() != invalido )
 {
	bool estado = true;
	// Calculo la cantidad para el dialogo
	dialogo->setRange( 0, (_caravanas.size() * 2) + 1 );
	dialogo->setValue( 0 );
 	QSqlQuery cola;
	QString scola = QString( " car_tri( dta, razon, id_categoria, id_estab_destino, id_estab_origen, id_comprador, id_vendedor ) VALUES ( '%1', '%2', '%3', '%4', '%5', '%6', '%7' )" ).arg( DTA ).arg( tipoMov() ).arg( categoria.first ).arg( destino.first ).arg( origen.first ).arg( comprador.first ).arg( vendedor.first );
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
	dialogo->setValue( dialogo->value() + 1 );
	if( cola.exec( scola ) )
	{
		//Devulevo el id que inserte
		if( id_db == -1 )
		{
			QSqlQuery cola1( "SELECT seq FROM sqlite_sequence WHERE name = 'car_tri' LIMIT 1" );
			if( cola1.next() )
			{
				if( cola1.record().value("seq").toInt() > 0 )
				{
					id_db =  cola1.record().value(0).toInt();
					qDebug( QString("usando id de insercion %1" ).arg( id_db ).toLocal8Bit() );
				}
				else
				{
					qWarning( "Error al obtener el id insertado" );
					return -4;
				}
				
			}
			else
			{
				qWarning( QString( "Error al obtener el numero de tri al hacer insercion\n Error: %1\n %2" ).arg( cola1.lastError().text() ).arg( cola1.lastQuery() ).toLocal8Bit() );
				return -1;
			}
		}
	}
	else
	{
		qWarning( QString( "Error al insertar o actualizar el registro de tri\n Error: %1\n %2" ).arg( cola.lastError().text() ).arg( cola.lastQuery() ).toLocal8Bit() );
		return -2;
	}
	// Guardo las caravanas
	QString codigo;
	foreach( codigo, _caravanas )
	{
		if( estado )
		{
			estado = guardarCaravana( codigo );
			dialogo->setValue( dialogo->value() + 1 );
			if( estado )
			{
				estado = asociarCaravana( codigo );
				dialogo->setValue( dialogo->value() + 1 );
			}
			else
			{
				qDebug( "Error al intenar asociar la caravana" );
				return -3;
			}
		}
		else
		{
			qDebug( "Error al intenar guardar la caravana" );
			return -3;
		}
	}
	return id_db;
 }
 else
 {
  qWarning( "Error al intentar guardar o acutalizar el registro, su tipo fue invalido" );
  dialogo->setValue( dialogo->maximum() );
  return -14;
 }
}


/*!
    \fn EMovimiento::setCaravanas( QStringList caravanas )
 */
void EMovimiento::setCaravanas( QStringList caravanas )
{
 if( tipoMov() == compra || tipoMov() == stock )
 {
  ///@todo Agrego un control de las existentes aca?
  _caravanas = caravanas;
 }
    /// @todo implement me
}


/*!
    \fn EMovimiento::agregarCaravana( QString codigo, bool verificar )
 */
bool EMovimiento::agregarCaravana( QString codigo, bool verificar )
{
 if( !verificar )
 {
  _caravanas.append( codigo );
  return true;
 }
 QSqlQuery cola;
 if( cola.exec( QString( "SELECT COUNT(codigo) FROM car_caravana WHERE codigo = '%1'" ).arg( codigo ) ) )
  {
   if( cola.next() )
   {
    if( cola.record().value(0).toInt() >= 1 )
    {
 	qWarning( QString( "La caravana de codigo %1 ya existe al menos %2 veces en el sistema, no sera guardada en este tri" ).arg( codigo ).arg( cola.record().value(0).toInt() ).toLocal8Bit() );
	return false;
    }
    else
    {
	_caravanas.append( codigo );
	return true;
    }
   }
   else
   {
     qWarning( QString( "Error al hace next en buscar codigos de caravanas varificando\n Error: %1\n %2" ).arg( cola.lastError().text() ).arg( cola.lastQuery() ).toLocal8Bit() );
     return false;
   }
  }
  else
  {
    qWarning( QString( "Error al buscar codigos de caravanas con verificacion\n Error: %1\n %2" ).arg( cola.lastError().text() ).arg( cola.lastQuery() ).toLocal8Bit() );
    return false;
  }
}


/*!
    \fn EMovimiento::eliminarCaravana( QString codigo )
 */
void EMovimiento::eliminarCaravana( QString codigo )
{
 // Verifico que este en la lista
 if( _caravanas.contains( codigo ) )
 {
  _caravanas.removeAt( _caravanas.indexOf( codigo ) );
 }
}


/*!
    \fn EMovimiento::guardarCaravana( QString codigo )
 */
bool EMovimiento::guardarCaravana( QString codigo )
{
 switch( tipoMov() )
 {
 	case compra:
	case stock:
	{
		QSqlQuery cola;
		if( !cola.exec( QString( "INSERT INTO car_caravana( codigo ) VALUES ( '%1' )" ).arg( codigo ) ) )
		{
			qWarning( QString( "Error al agregar nueva caravana\n Error: %1\n cola: %2" ).arg( cola.lastError().text() ).arg( cola.lastQuery() ).toLocal8Bit() );
			return false;
		}
		else
		{
			qDebug( "Caravana Agregada" );
			return true;
		}
		break;
	}
	case venta:
	case mudanza:
	{
		qDebug( "La caravana ya debe existir en la db" );
		return true;
		break;
	}
	default:
	{
		qDebug( "No se guardo ninguna caravana. Tipo de movimiento sin implmenetacion" );
		qDebug( QString::number( tipoMov() ).toLocal8Bit() );
		return false;
		break;
	}
 }
 // Sino es de esos tipos, ya esta dada de alta en la db
 return false;
}


/*!
    \fn EMovimiento::asociarCaravana( QString codigo )
 */
bool EMovimiento::asociarCaravana( QString codigo )
{
 // Siempre existe el codigo de caravana dado de alta al llamar esta funcion
 QSqlQuery cola;
 if( !cola.exec( QString( "SELECT id_caravana FROM car_caravana WHERE codigo = '%1' LIMIT 1" ).arg( codigo ) ) )
 {
	qWarning( QString( "Error al buscar el id de caravana\n Error: %1\n cola: %2" ).arg( cola.lastError().text() ).arg( cola.lastQuery() ).toLocal8Bit() );
	return false;
 }
 else
 {
	if( cola.next() )
	{
		int id_caravana = cola.record().value(0).toInt();
		if( id_caravana <= 0 )
		{
			qDebug( "Error al controlar el id de caravana" );
			return false;
		}
		QSqlQuery cola1;
		if( !cola1.exec( QString( "INSERT INTO car_carv_tri( id_caravana, id_tri ) VALUES ( '%1' ,'%2' )" ).arg( id_caravana ).arg( id_db ) ) )
		{
			qWarning( QString( "Error al agregar nueva caravana\n Error: %1\n cola: %2" ).arg( cola1.lastError().text() ).arg( cola1.lastQuery() ).toLocal8Bit() );
			return false;
		}
		else
		{
			qDebug( "Asociacion exitosa" );
			return true;
		}
	}
	else
	{
		qWarning( QString( "Error al next de buscar numero de caravana al agregar asociacion\n Error: %1\n cola: %2" ).arg( cola.lastError().text() ).arg( cola.lastQuery() ).toLocal8Bit() );
		return false;
	}
 }
}


/*!
    \fn EMovimiento::cargarCaravanas()
 */
bool EMovimiento::cargarCaravanas()
{
 QSqlQuery cola;
 if( cola.exec( QString( "SELECT codigo FROM car_caravana WHERE id_caravana IN ( SELECT id_caravana FROM car_carv_tri WHERE id_tri = '%1' )" ).arg( id_db ) ) )
 {
	while( cola.next() )
	{
		// Le pongo false para que no verifique que existe la caravana
		agregarCaravana( cola.record().value(0).toString(), false );
	}
	return true;
 }
 else
 {
  qWarning( QString( "Error al cargar las caravanas de un tri especifico.\n Error: %1\n cola: %2" ).arg( cola.lastError().text() ).arg( cola.lastQuery() ).toLocal8Bit() );
  return false;
 }
}
