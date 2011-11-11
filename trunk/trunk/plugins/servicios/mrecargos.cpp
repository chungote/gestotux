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
#include "mrecargos.h"

#include <QSqlRecord>
#include "mservicios.h"
#include <QSqlError>
#include <QSqlQuery>

MRecargos::MRecargos( QObject *parent, bool relaciones )
 : QSqlRelationalTableModel(parent), _precio_base(0.0)
{
 setTable( "recargos" );
 setHeaderData( 0, Qt::Horizontal, tr( "#ID" ) );
 setHeaderData( 1, Qt::Horizontal, tr( "Servicio" ) );
 setHeaderData( 2, Qt::Horizontal, tr( "Dias pasados" ) );
 setHeaderData( 3, Qt::Horizontal, tr( "Porcentaje del precio base" ) );
 setHeaderData( 4, Qt::Horizontal, tr( "Recargo Fijo" ) );
 setHeaderData( 5, Qt::Horizontal, tr( "Precio recargado final" ) );
 if( relaciones ) {
     setRelation  ( 1, QSqlRelation( "servicios", "id_servicio", "nombre" ) );
 }
}


bool MRecargos::setData(const QModelIndex& idx, const QVariant& value, int role)
{
    switch( idx.column() ) {
    case 3:
    case 4:
    case 5:
        {
            bool valor = QSqlRelationalTableModel::setData( idx, value, role );
            emit dataChanged( index( idx.row(), 5 ), index( idx.row(), 5 ) );
            return valor;
            break;
        }
    default:
        {
            return QSqlRelationalTableModel::setData(idx, value, role);
            break;
        }
    }
}

QVariant MRecargos::data(const QModelIndex& idx, int role) const
{
 switch( role )
 {
  case Qt::EditRole:
  {
   switch( idx.column() )
   {
    case 0:
    case 2:
    { return QSqlRelationalTableModel::data( idx, role ).toInt(); break; }
    case 3:
    case 4:
    { return QSqlRelationalTableModel::data( idx, role ).toDouble(); break; }
    default:
    { return QSqlRelationalTableModel::data( idx, role ); break; }
   }
   break;
  }
  case Qt::DisplayRole:
  {
   switch( idx.column() )
   {
    case 3:
    { return QString( "%L1 %").arg( QSqlRelationalTableModel::data( idx, role ).toDouble() ); break; }
    case 4:
    { return QString( "$ %L1").arg( QSqlRelationalTableModel::data( idx, role ).toDouble() ); break; }
    case 5:
    {
     if( this->data( this->index( idx.row(), 3 ), Qt::EditRole ).toDouble() > 0.0 )
     {
      return QString( "$ %L1" ).arg( _precio_base + ( _precio_base * this->data( this->index( idx.row(), 3 ), Qt::EditRole ).toDouble() *.01 ) );
     }
     else if( this->data( this->index( idx.row(), 4 ), Qt::EditRole ).toDouble() > 0.0 )
     {
      return QString( "$ %L1" ).arg( _precio_base + this->data( this->index( idx.row(), 4 ), Qt::EditRole ).toDouble() );
     }
     else
     {
      return QString( "$ %L1" ).arg( _precio_base );
     }
     break;
    }
    default:
    { return QSqlRelationalTableModel::data( idx, role ); break; }
   }
  }
  case Qt::TextAlignmentRole:
  { return int( Qt::AlignCenter | Qt::AlignVCenter ); break; }
  default:
  { return QSqlRelationalTableModel::data( idx, role); break; }
 }
 return QSqlRelationalTableModel::data( idx, role );
}



/*!
    \fn MRecargos::agregarRecargo()
    Agrega un tipo de recargo a la lista de recargos para un servicio.
 */
void MRecargos::agregarRecargo()
{
 if( _servicio_actual <= 0 ) {
   qDebug( "Error, no hay un id de servicio seteado ( id <= 0 )" );
   return;
 } else { qDebug( QString( "id_servicio = %1" ).arg( _servicio_actual ).toLocal8Bit() ); }
 QSqlRecord registro = this->record();
 registro.remove( 0 );
 registro.setValue( "id_servicio", _servicio_actual );
 registro.setValue( "cant_dias", 1 );
 registro.setGenerated( 3, true );
 /*for( int i = 0; i < registro.count(); i++ ) {
     qDebug( QString( "%1: %2 - %3" ).arg( i ).arg( registro.fieldName( i ) ).arg( registro.value( i ).toString() ).toLocal8Bit() );
 }*/
 if( !this->insertRecord( -1, registro ) ) {
     qDebug( "No se pudo agregar el registro" );
 }
}


/*!
    \fn MRecargos::setearServicio( int id_servicio )
    Metodo para setear el filtro de los recargos actuales segun el ID.
    El ID debe ser mayor que cero.
    @param id_servicio ID del servicio a filtrar.
 */
void MRecargos::setearServicio( int id_servicio )
{
    if( id_servicio > 0 ) {
        this->_servicio_actual = id_servicio;
        this->setFilter( QString( "id_servicio = %1" ).arg( id_servicio ) );
        // Busco el precio base
        this->_precio_base = MServicios::precioBase( _servicio_actual );
        this->select();
    } else {
        qDebug( QString( "MRecargos::setearServicio::id de servicio erroneo: %1" ).arg( id_servicio ).toLocal8Bit() );
    }
}


/*!
    \fn MRecargos::setearPrecioBase( double precio )
    Setea el precio base para el servicio seleccionado en la clase para calcular los precios.
    @param precio Precio a setear
 */
void MRecargos::setearPrecioBase( double precio )
{
    _precio_base = precio;
    emit dataChanged( index( 0, 5 ), index( rowCount(), 5 ) );
}


/*!
    \fn MRecargos::columnCount( const QModelIndex & index ) const
    Sobre carga para indicar de que existe una columna mas que calcula el sobrecargo.
 */
int MRecargos::columnCount( const QModelIndex &/*index*/ ) const
{
 return QSqlRelationalTableModel::columnCount() + 1;
}

#include "mperiodoservicio.h"
/*!
 * \fn double MRecargos::calcularRecargo( const int id_recargo )
 * Devuelve la cantidad a aplicar de recargo ( precio del servicio * porcentaje o recargo fijo. No incluye el precio del servicio.
 * \param id_recargo Identificador del recargo
 * \returns cantidad a recargar
 */
double MRecargos::calcularRecargo( const int id_recargo )
{
    QSqlQuery cola;
    // busco el tipo de recargo
    cola.prepare( "SELECT porcentaje, recargo, id_servicio FROM recargos WHERE id_recargo = :id_recargo" );
    cola.bindValue( ":id_recargo", id_recargo );
    if( !cola.exec() ) {
        qDebug( "Error al ejecutar la cola de averiguacionde los datos del recargo" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
        return -1.0;
    }
    double porcentaje = cola.record().value(0).toDouble();
    double recargo = cola.record().value(1).toDouble();
    double aplicar = 0.0;
    if( recargo <= 0.0 ) {
        // Uso el recargo
        double precio = MServicios::precioBase( cola.record().value(2).toInt() );
        if( precio != 0.0 ) {
            aplicar = precio * porcentaje;
        } else {
            qDebug( "Existio un error al intentar buscar el precio base del servicio buscando el recargo" );
            return -1.0;
        }
    } else {
        aplicar = recargo;
    }
    return aplicar;
}

/*
  CREATE TABLE IF NOT EXISTS `recargos` (
    `id_recargo` bigint NOT NULL AUTO_INCREMENT,
    `id_servicio` bigint NOT NULL,
    `cant_dias` int NOT NULL,
    `porcentaje` double(4,2) DEFAULT NULL,
    `recargo` double DEFAULT NULL,
    PRIMARY KEY (`id_recargo`)
  ) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;
  */