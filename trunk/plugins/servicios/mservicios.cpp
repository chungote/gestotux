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
#include "mservicios.h"

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDate>

#include "math.h"

/*
CREATE TABLE IF NOT EXISTS `servicios` (
  `id_servicio` bigint(1) NOT NULL AUTO_INCREMENT,
  `nombre` tinytext NOT NULL,
  `descripcion` text,
  `fecha_alta` date NOT NULL,
  `fecha_baja` date DEFAULT NULL,
  `precio_base` double(10,3) NOT NULL,
  `periodo` int(10) NOT NULL,
  `dia_cobro` int(10) NOT NULL,
  `forma_incompleto` int(10) NOT NULL,
  PRIMARY KEY (`id_servicio`)
) ENGINE=MyISAM ;
*/

MServicios::MServicios(QObject *parent)
 : QSqlTableModel(parent)
{
 setTable( "servicios" );
 setHeaderData( 0, Qt::Horizontal, tr( "#ID" ) );
 setHeaderData( 1, Qt::Horizontal, tr( "Nombre" ) );
 setHeaderData( 2, Qt::Horizontal, tr( "Descripcion" ) );
 setHeaderData( 3, Qt::Horizontal, tr( "Fecha de Alta" ) );
 setHeaderData( 4, Qt::Horizontal, tr( "Fecha de Baja" ) );
 setHeaderData( 5, Qt::Horizontal, tr( "Precio Base" ) );
 setHeaderData( 6, Qt::Horizontal, tr( "Periodo" ) );
 setHeaderData( 7, Qt::Horizontal, tr( "Dia de Cobro" ) );
 setHeaderData( 8, Qt::Horizontal, tr( "Forma de cobro incompleto" ) );
}


MServicios::~MServicios()
{
}

/*!
 * @fn MServicios::data( const QModelIndex& item, int role ) const
 * Implementacion del metodo de datos para que las enumeraciones se vena como texto
 */
QVariant MServicios::data( const QModelIndex& item, int role ) const {
    if( !item.isValid() ) { return QVariant(); }
    switch( role ) {
        case Qt::DisplayRole:
        {
            switch( item.column() ) {
                case 6: // Periodo
                {
                        switch( QSqlTableModel::data( item, role ).toInt() ) {
                            case MServicios::Semanal:
                            { return "Semanal"; }
                            case MServicios::Quincenal:
                            { return "Quincenal"; }
                            case MServicios::Mensual:
                            { return "Mensual"; }
                            case MServicios::BiMensual:
                            { return "Bimensual"; }
                            case MServicios::Trimestral:
                            { return "Trimestral"; }
                            case MServicios::Cuatrimestral:
                            { return "Cuatrimestral"; }
                            case MServicios::Seximestral:
                            { return "Seximestral"; }
                            case MServicios::Anual:
                            { return "Anual"; }
                        }
                }
                case 8: // Metodo Incompleto
                {
                        switch( QSqlTableModel::data( item, role ).toInt() ) {
                            case MServicios::DiasFaltantes:
                            { return "Dias Faltantes"; }
                            case MServicios::MesCompleto:
                            { return "Mes Completo"; }
                        }
                }
                case 5:
                { return QString( "$ %L1" ).arg( QSqlTableModel::data( item, role ).toDouble() ); }
                default:
                { return QSqlTableModel::data( item, role ); }
            }
        }
        case Qt::TextAlignmentRole:
        {
            switch( item.column() ) {
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                {
                    return int( Qt::AlignCenter | Qt::AlignHCenter );
                }
                default:
                {
                    return QSqlTableModel::data( item, role );
                }
            }
        }
        default:
        { return QSqlTableModel::data( item, role ); }
    }
}


/*!
    \fn MServicios::asociarCliente( int id_cliente, int id_servicio, QDateTime fecha )
        Asocia el cliente con el servicio correspondiente en la base de datos en la fecha de alta indicada.
        @param id_cliente Identificador de cliente
        @param id_servicio Identificador del servicio
        @param fecha Fecha en que el cliente se da de alta en el servicio
        @return Verdadero si la asociacion se pudo realizar correctamente
 */
bool MServicios::asociarCliente( int id_cliente, int id_servicio, QDateTime fecha )
{
 QSqlTableModel *modelo = new QSqlTableModel();
 modelo->setTable( "servicios_clientes" );
 modelo->setEditStrategy( QSqlTableModel::OnManualSubmit );
 QSqlRecord registro = modelo->record();
 registro.setValue( "id_cliente", id_cliente );
 registro.setValue( "id_servicio", id_servicio );
 registro.setValue( "fecha_alta", fecha );
 registro.setNull( "fecha_baja" );
 if( modelo->insertRecord( -1, registro ) )
 {
  if( !modelo->submitAll() )
  {
   qWarning( qPrintable( "Error al hacer submit en el modelo: " + modelo->lastError().text() ) );
   delete modelo;
   return false;
  }
 }
 else
 {
  qWarning( qPrintable( "Error al hacer insertar en el modelo: " + modelo->lastError().text() ) );
  delete modelo;
  return false;
 }
 delete modelo;
 qDebug( "Datos guardados correctamente" );
 return true;
}

/*!
    \fn MServicios::agregarServicio( QString nombre, QString detalle, QDate fecha_alta, double precio_base, int periodo, int dia_cobro, int forma_incompleto )
    Agrega un nuevo servicio a la base de datos con los datos pasados como parametro
    \param nombre Nombre del servicio
    \param detalle Explicacion mas detallada del servicio
    \param fecha_alta Fecha desde cuando empieza a funcionar el servicio
    \param precio_base Precio base sobre el cual se calculan los recargos
    \param periodo Periodo de cobro del servicio #MServicios::Periodo
    \param dia_cobro Dia del periodo en que se inicia el cobro del servicio
    \param forma_incompleto Forma de cobro cuando se da de alta un cliente fuera del inicio del periodo #MServicios::FormaIncompleto
 */
bool MServicios::agregarServicio( QString nombre, QString detalle, QDate fecha_alta, double precio_base, int periodo, int dia_cobro, int forma_incompleto )
{
  // Teoricamente los datos se controlaron de ser correctos
  QSqlRecord registro = this->record();
  registro.setValue( "nombre", nombre );
  registro.setValue( "detalle", detalle );
  registro.setValue( "fecha_alta", fecha_alta );
  registro.setValue( "precio_base", precio_base );
  registro.setValue( "periodo", periodo ); // Agregar verificacion de enumeracion
  registro.setValue( "dia_cobro", dia_cobro );// Agregar verificacion de enumeracion
  registro.setValue( "forma_incompleto", forma_incompleto );// Agregar verificacion de enumeracion
  if( this->insertRecord( -1, registro ) ) {
      return true;
  } else {
      qDebug( QString( "Error MServicios::agregarServicio(): %1").arg( this->lastError().text() ).toLocal8Bit() );
      return false;
  }
}

/*!
 * \fn MServicios::precioBase( int id_servicio )
 * Devuelve el precio base de un servicio
 * @param id_servicio Identificador del servicio al cual se le quiere saber el percio base.
 * @return precio base para el servicio solicitado o 0.0 si existió un error.
 */
double MServicios::precioBase( int id_servicio )
{
  QSqlQuery cola( QString( "SELECT precio_base FROM %2 WHERE id_servicio = %1" ).arg( id_servicio ).arg( "servicios" ) );
  if( cola.exec() ) {
    if( cola.next() )
    {
     return cola.record().value(0).toDouble();
    } else { qDebug( "Error al hacer next en la cola de precio base de servicio" ); return 0.0; }
  } else { qDebug( "Error al hacer exec en la cola de precio base de servicio" ); return 0.0; }
}

/*!
 * \fn MServicios::getNombreServicio( int id_servicio )
 * Devuelve el nombre de un servicio
 * @param id_servicio Identificador del servicio al cual se le quiere saber el nombre.
 * @return Nombre del servicio o una cadena vacía si existio un error al obtener el nombre
 */
QString MServicios::getNombreServicio( int id_servicio )
{
  QSqlQuery cola( QString( "SELECT nombre FROM %2 WHERE id_servicio = %1" ).arg( id_servicio ).arg( "servicios") );
  if( cola.exec()) {
      if( cola.next() ) {
          return cola.record().value(0).toString();
      } else { qDebug( "Servicios:MServicios:Error al hacer el next en la cola de nombre del servicio" ); return ""; }
  } else { qDebug( "Servicios:MServicios:Error al hacer el exec en la cola del nombre del servicio" ); return ""; }
}

/*!
 * \fn MServicios::getFechaAlta( const int id_servicio )
 * Devuelve la fecha de alta de un servicio
 * \param id_servicio Identificador de servicio
 * \return Fecha de alta si se pudo encontrar o un QDate() si existio un error.
 */
QDate MServicios::getFechaAlta( const int id_servicio )
{
    QSqlQuery cola( QString( "SELECT fecha_alta FROM servicios WHERE id_servicio = %2" ).arg( id_servicio ) );
    if( cola.exec() ) {
        if( cola.next() ) {
            return cola.record().value(0).toDate();
        } else {
            qDebug( "Servicios:MServicios:Error al buscar la fecha de alta del periodo -> next" );
            return QDate();
        }
    } else {
        qDebug( "Servicios:MServicios:Error al buscar la fecha de alta del periodo -> exec" );
        return QDate();
    }
}




MServicios::Periodo MServicios::obtenerPeriodo( const int id_servicio ) {
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT periodo FROM servicios WHERE id_servicio = %1" ).arg( id_servicio )  ) ) {
        if( cola.next() ) {
            switch( cola.record().value(0).toInt() ) {
                case MServicios::Semanal:       { return MServicios::Semanal;       break; }
                case MServicios::Quincenal:     { return MServicios::Quincenal;     break; }
                case MServicios::Mensual:       { return MServicios::Mensual;       break; }
                case MServicios::BiMensual:     { return MServicios::BiMensual;     break; }
                case MServicios::Trimestral:    { return MServicios::Trimestral;    break; }
                case MServicios::Cuatrimestral: { return MServicios::Cuatrimestral; break; }
                case MServicios::Seximestral:   { return MServicios::Seximestral;   break; }
                case MServicios::Anual:         { return MServicios::Anual;         break; }
                default: { return MServicios::Invalido; break; }
            }
        } else {
            qDebug( "Error de next en cola de obtencion de periodo en serivicio" );
            qDebug( cola.lastError().text().toLocal8Bit() );
            qDebug( cola.lastQuery().toLocal8Bit() );
            return MServicios::Invalido;
        }
    } else {
        qDebug( "Error de exec en la cola de obtencion de periodo de un servicio" );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
        return MServicios::Invalido;
    }
    return MServicios::Invalido;
}

/*!
 * \fn MServicios::verificarSiPuedeEliminar( const int id_servicio )
 * Verifica si existe algun dato relacionado con el servicio que se intenta eliminar para definir si es posible eliminarlo o no.
 * \param id_servicio Identificador del servicio buscado
 * \return verdadero si no existe ningun dato asociado al servicio
 */
bool MServicios::verificarSiPuedeEliminar( const int id_servicio )
{
    QSqlQuery cola;
    bool retorno = true;
    // Asociacion cliente-servicio
    if( cola.exec( QString( "SELECT COUNT(id_servicio) FROM servicios_clientes WHERE id_servicio = %1"  ).arg( id_servicio ) ) ) {
        if( cola.next() )  {
            if( cola.record().value(0).toInt() > 0 ) { return false; }
        } else {
            qDebug( "MServicios::verificarSiPuedeEliminar::Error next 1 verificacion -  servicios_clientes" );
            return false;
        }
    } else {
        qDebug( "MServicios::verificarSiPuedeEliminar::Error exec 1 verificacion -  servicios_clientes" );
        return false;
    }
    // Asociacion recargo-servicio
    if( cola.exec( QString( "SELECT COUNT(id_servicio) FROM recargos WHERE id_servicio = %1"  ).arg( id_servicio ) ) ) {
        if( cola.next() )  {
            if( cola.record().value(0).toInt() > 0 ) { return false; }
        } else {
            qDebug( "MServicios::verificarSiPuedeEliminar::Error next 2 verificacion -  recargos" );
            return false;
        }
    } else {
        qDebug( "MServicios::verificarSiPuedeEliminar::Error exec 2 verificacion -  recargos" );
        return false;
    }
    // Asociación servicio-periodo
    if( cola.exec( QString( "SELECT COUNT(id_servicio) FROM periodo_servicio WHERE id_servicio = %1"  ).arg( id_servicio ) ) ) {
        if( cola.next() )  {
            if( cola.record().value(0).toInt() > 0 ) { return false; }
        } else {
            qDebug( "MServicios::verificarSiPuedeEliminar::Error next 3 verificacion - periodo_servicio" );
            return false;
        }
    } else {
        qDebug( "MServicios::verificarSiPuedeEliminar::Error exec 3 verificacion - periodo_servicio" );
        return false;
    }
    return retorno;
}


/*
"id_servicio" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL
"nombre" TEXT NOT NULL
"descripcion" TEXT
"fecha_alta" DATETIME NOT NULL
"fecha_baja" DATETIME
"precio_base" DOUBLE NOT NULL
"periodo" INTEGER NOT NULL
"dia_cobro" INTEGER NOT NULL
"forma_incompleto" INTEGER NOT NULL
*/