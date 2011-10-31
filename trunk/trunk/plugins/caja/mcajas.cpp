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

#include "mcajas.h"

#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>

#include "mmovimientoscaja.h"
#include "preferencias.h"

MCajas::MCajas(QObject *parent ) :
QSqlTableModel(parent)
{
    setTable( "caja" );
    this->setHeaderData( 0, Qt::Horizontal, "#ID" );
    this->setHeaderData( 1, Qt::Horizontal, "Nombre" );
    this->setHeaderData( 2, Qt::Horizontal, "Fecha de Alta"  );
    this->setHeaderData( 3, Qt::Horizontal, "Saldo Actual" );
}


QVariant MCajas::data( const QModelIndex &idx, int role ) const
{
    switch( role ) {
        case Qt::DisplayRole: {
            switch( idx.column() ) {
                case 3:
                { return QString( "$ %1" ).arg( QSqlTableModel::data( idx, Qt::EditRole ).toDouble() ); break; }
                default:
                { return QSqlTableModel::data( idx, role ); break; }
            }
            break;
        }
        case Qt::TextAlignmentRole: {
            switch( idx.column() ) {
                case 2:
                case 3:
                { return int( Qt::AlignCenter | Qt::AlignHCenter ); break; }
                default:
                { return QSqlTableModel::data( idx, role ); break; }
            }
            break;
        }
        default:
        {
            return QSqlTableModel::data( idx, role ); break;
        }
    }
}

Qt::ItemFlags MCajas::flags( const QModelIndex &/*idx*/ ) const
{
    return Qt::ItemFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );
}

/*!
  @fn MCajas::agregarCaja( QString nombre, QDate fecha_alta = QDate::currentDate(), double saldo_inicial )
  Funcion para agregar una caja nueva al sistema
  @param nombre Nombre de la caja
  @param fecha_alta Fecha en que se da de alta
  @param saldo_inicial Saldo inicial de la caja
 */
bool MCajas::agregarCaja( QString nombre, QDate fecha_alta, double saldo_inicial )
{
  QSqlRecord rec = this->record();
  rec.setValue( "nombre", nombre );
  rec.setValue( "fecha_alta", fecha_alta );
  rec.setValue( "saldo", saldo_inicial );
  if( insertRecord( -1, rec ) ) {
      // Agregar el registro de transaccion inicial en la tabla de movimientos
      MMovimientosCaja *mmov = new MMovimientosCaja( this );
      if( saldo_inicial > 0.0 ) {
          if( mmov->agregarMovimiento( query().lastInsertId().toInt(), "Apertura de Caja - Saldo Inicial", QString(), saldo_inicial, 0.0, true ) )
          {  return true; } else { return false; }
      } else {
        if( mmov->agregarMovimiento( query().lastInsertId().toInt(), "Apertura de Caja - Saldo Inicial", QString(), 0.0, saldo_inicial, true ) )
        {  return true; } else { return false; }
      }
  } else {
      qWarning( QString( "Error al insertar caja nueva: %1" ).arg( this->lastError().text() ).toLocal8Bit() );
      return false;
  }
}

#include <QSqlQuery>
/*!
 * @fn MCajas::actualizarSaldo( int id_caja, double cantidad )
 * Funcion que actualiza el sado de una caja especifica
 * @param id_caja Identificador de la caja a la cual se le actualizará el saldo
 * @param cantidad Cantidad ( positiva para aumentar, negativa para disminuir ) que se modificara al saldo
 */
bool MCajas::actualizarSaldo( const int id_caja, const double cantidad )
{
 QSqlQuery cola;
 if( cola.exec( QString( "SELECT saldo FROM %1 WHERE id_caja = %2" ).arg( "caja" ).arg( id_caja )  ) ) {
     if( cola.next() ) {
        double saldo_nuevo = cola.record().value(0).toDouble() + cantidad;
        if( cola.exec( QString( "UPDATE caja SET saldo = %1 WHERE id_caja = %2" ).arg( saldo_nuevo ).arg( id_caja ) ) ) {
            return true;
        } else {
            qWarning( QString( "Error al guardar el nuevo saldo." ).toLocal8Bit() );
            return false;
        }
    } else {
        qWarning( QString( "Error al buscar el saldo anterior haciendo next. <br /> Posiblemente la caja predeterminada este mal guardada. Por favor, cambiela desde las preferencias e intente realizar la operacion nuevamente." ).toLocal8Bit() );
        qDebug( cola.lastError().text().toLocal8Bit() );
        qDebug( cola.lastQuery().toLocal8Bit() );
        return false;
    }
 } else {
    qWarning( QString( "Error al buscar el saldo anterior." ).toLocal8Bit() );
    return false;
 }
}

/*!
 * @fn MCajas::saldo( const int id_caja )
 * Funcion que devuelve el saldo actual de una caja
 * @param id_caja Identificador de la caja a la cual se le actualizará el saldo
 * @return Saldo de la caja
 */
double MCajas::saldo( const int id_caja )
{
   QSqlQuery cola;
   if( cola.exec( QString( "SELECT saldo FROM %1 WHERE id_caja = %2" ).arg( "caja" ).arg( id_caja )  ) ) {
       //qDebug( QString( "Ejecutado: %1" ).arg( cola.lastQuery() ).toLocal8Bit() );
       if( cola.next() ) {
        return cola.record().value("saldo").toDouble();
       } else { return 0.0;  }
   } else {
        qDebug( "Saldo no encontrado" );
        return 0.0;
   }
}

/*!
 * @fn MCajas::hacerCierre( const int id_caja, QDateTime fecha, double saldo )
 * Funcion que realiza el cierre de una caja.
 * @param id_caja Identificador de la caja a la cual se le actualizar el saldo
 * @param fecha Fecha y hora en que se realiza el cierre
 * @param saldo Saldo que se contabilizo
 * @return Saldo de la caja
 */
bool MCajas::hacerCierre( const int id_caja, QDateTime fecha, double saldo )
{
   MMovimientosCaja *m = new MMovimientosCaja();
   bool ret;
   if( m->verificarCierreCaja( id_caja ) ) {
     ret = m->agregarCierre( id_caja, fecha, saldo );
   } else {
       qWarning( "No se pudo realizar el cierre porque ya existe uno anterior y no hay operaciones aparte de esta");
       ret = false;
   }
   delete m;
   return ret;
}

/*!
 * @fn MCajas::nombreCaja( const int id_caja )
 * Funcion que retorna el nombre de una caja
 * @param id_caja Identificador de la caja
 * @returns Nombre de la caja
 */
QString MCajas::nombreCaja( const int id_caja )
{
    QSqlQuery cola;
    if( cola.exec( QString( "SELECT nombre FROM %1 WHERE id_caja = %2" ).arg( "caja" ).arg( id_caja )  ) ) {
        //qDebug( QString( "Ejecutado: %1" ).arg( cola.lastQuery() ).toLocal8Bit() );
        if( cola.next() ) {
         return cola.record().value(0).toString();
        } else { return QString();  }
    } else {
         qDebug( "Nombre no encontrado" );
         return QString();
    }
}

/*!
 * @fn MCajas::cajaPredeterminada()
 * Devuelve la caja que se haya elegido como predeterminada en las funciones de preferencias de cajas.
 * Si no se eligio ninguna, devuelve -1
 * @returns ID de la caja predeterminada
 */
int MCajas::cajaPredeterminada()
{
    preferencias *p = preferencias::getInstancia();
    p->inicio();
    p->beginGroup( "Preferencias");
    p->beginGroup( "Caja" );
    p->beginGroup( "caja-predeterminada" );
    int id = p->value( QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).driverName(), -1 ).toInt();
    p->endGroup();
    p->endGroup();
    p->endGroup();
    p = 0;
    return id;
}
