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
#include "mpresupuesto.h"
#include <QDate>
#include <QColor>

MPresupuesto::MPresupuesto(QObject *parent )
 : QSqlRelationalTableModel(parent)
{
    inicializar();
    relacionar();
}

void MPresupuesto::inicializar()
{
    setTable( "presupuestos" );
    // Descripciondes de las cabeceras
    setHeaderData( 0, Qt::Horizontal, "#ID" );
    setHeaderData( 1, Qt::Horizontal, "Cliente" );
    setHeaderData( 2, Qt::Horizontal, "Destinatario" );
    setHeaderData( 3, Qt::Horizontal, "Fecha" );
    setHeaderData( 4, Qt::Horizontal, "Total" );
    setHeaderData( 5, Qt::Horizontal, "Contenido" );
}

void MPresupuesto::relacionar()
{
  setRelation( 1, QSqlRelation( "clientes", "id", "razon_social" ) );
}

/*
CREATE TABLE IF NOT EXISTS `presupuestos` (
  `id_presupuesto` bigint(20) NOT NULL AUTO_INCREMENT,
  `id_cliente` bigint(20) DEFAULT NULL,
  `destinatario` text COLLATE utf8_spanish_ci,
  `direccion` text COLLATE utf8_spanish_ci,
  `fecha` date NOT NULL,
  `total` decimal(10,4) NOT NULL,
  `serie` bigint(20) NOT NULL,
  `numero` bigint(20) NOT NULL,
  PRIMARY KEY (`id_presupuesto`),
  UNIQUE KEY `presupuesto-serie-numero` (`serie`,`numero`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci AUTO_INCREMENT=1 ;
*/


QVariant MPresupuesto::data(const QModelIndex& idx, int role) const
{
 switch( role )
 {
        case Qt::DisplayRole:
        {
                switch( idx.column() )
                {
                        case 1:
                        case 2:
                        {
                                return QSqlRelationalTableModel::data( idx, role ).toString();
                                break;
                        }
                        case 3:
                        {
                                return QSqlRelationalTableModel::data( idx, role ).toDate();
                                break;
                        }
                        case 4:
                        {
                                return QString( "$ %L1" ).arg( QSqlRelationalTableModel::data( idx, role ).toDouble() );
                                break;
                        }
                        default:
                        {
                                return QSqlRelationalTableModel::data( idx, role );
                                break;
                        }
                }
                break;
        }
        case Qt::EditRole:
        {
                switch( idx.column() )
                {
                        case 1:
                        {
                                return QSqlRelationalTableModel::data( idx, role );
                                break;
                        }
                        case 2:
                        {
                                return QSqlRelationalTableModel::data( idx, role ).toString();
                                break;
                        }
                        case 3:
                        {
                                return QSqlRelationalTableModel::data( idx, role ).toDate();
                                break;
                        }
                        case 4:
                        {
                                return QSqlRelationalTableModel::data( idx, role ).toDouble();
                                break;
                        }
                        default:
                        {
                                return QSqlRelationalTableModel::data( idx, role);
                                break;
                        }
                }
                break;
        }
        case Qt::TextAlignmentRole:
        {
                switch( idx.column() )
                {
                        case 1:
                        case 2:
                        {
                                return int( Qt::AlignLeft | Qt::AlignVCenter );
                                break;
                        }
                        case 3:
                        {
                                return int( Qt::AlignCenter | Qt::AlignVCenter );
                                break;
                        }
                        case 4:
                        {
                                return int( Qt::AlignRight | Qt::AlignVCenter );
                                break;
                        }
                        default:
                        {
                                return QSqlRelationalTableModel::data( idx, role );
                                break;
                        }
                }
                break;
        }
        case Qt::BackgroundRole:
        {
                switch( idx.column() )
                {
                        case 2:
                        {
                                if( QSqlRelationalTableModel::data( QSqlRelationalTableModel::index( idx.row(), 2 ), Qt::EditRole ).toString().isEmpty() )
                                { return QColor( Qt::gray ); }
                                else
                                { return QSqlRelationalTableModel::data( idx, role ); }
                                break;
                        }
                        default:
                        {
                                return QSqlRelationalTableModel::data( idx, role );
                                break;
                        }
                }
                break;
        }
        default:
        {
                return QSqlRelationalTableModel::data( idx, role );
                break;
        }
 }
}

bool MPresupuesto::setData(const QModelIndex& index, const QVariant& value, int role)
{
    return QSqlRelationalTableModel::setData(index, value, role);
}

#include <QSqlQuery>
#include <QSqlRecord>

NumeroComprobante &MPresupuesto::proximoComprobante() {
  QSqlQuery cola;
  if( cola.exec( QString( "SELECT MAX( serie ) FROM presupuestos" ) ) ) {
      if( cola.next() ) {
          int serie = cola.record().value(0).toInt();
          if( cola.exec( QString( "SELECT MAX( numero ) FROM presupuestos WHERE serie = %1" ).arg( serie ) ) ) {
              if( cola.next() ) {
                  int numero = cola.record().value(0).toInt();
                  NumeroComprobante *num = new NumeroComprobante( 0, serie, numero );
                  num->siguienteNumero();
                  return *num;
              } else {
                  qDebug( "Error de cola al hacer next al obtener el numero de prespuesto maximo");
              }
          } else {
              qDebug( "Error de cola al hacer exec al obtener el numero de prespuesto maximo" );
          }
      } else {
          qDebug( "Error de cola al hacer next al obtener el numero de serie de presupuesto maximo -  Se inicio una nueva numeracion" );
      }
  } else {
      NumeroComprobante *num = new NumeroComprobante( 0, 0, 1 );
      num->siguienteNumero();
      qDebug( "Error de cola al hacer exec al obtener el numero de serie de presupuesto maximo - Se inicio una nueva numeracion" );
      return *num;
  }
  NumeroComprobante *invalido = new NumeroComprobante( 0, -1, -1 );
  return *invalido;
}

/*!
 * \fn MPresupuesto::agregarPresupuesto()
    Agrega un presupuesto con los datos pasados de parametros y devuelve el id del registro recien insertado para utilizar con los items
    @param id_cliente Identificador de cliente
    @param texto_cliente Nombre del cliente si id-cliente no es valido
    @param direccion Direccion del cliente o destinatario si el id-cliente no es valido
    @param fechahora Fecha y hroa del presupeusto
    @returns ID de insercion o -1 si hubo un error
 */
int MPresupuesto::agregarPresupuesto(int id_cliente, QString texto_cliente, QString direccion, QDateTime fechahora ) {
    QSqlQuery cola;
    cola.prepare( "INSERT INTO presupuestos( id_cliente, nombre, direccion, fecha, serie, numero ) VALUES ( :id_cliente, :nombre, :direccion, :fecha, :serie, :numero )");
    if( id_cliente < 0 ) {
        cola.bindValue( ":id_cliente", QVariant() );
        cola.bindValue( ":nombre", texto_cliente );
        cola.bindValue( ":direccion", direccion );
    } else {
        cola.bindValue( ":id_cliente", id_cliente );
        cola.bindValue( ":nombre", QVariant() );
        cola.bindValue(":direccion", QVariant() );
    }
    cola.bindValue( ":fecha", fechahora );
    // busco el proximo numero de serie
    NumeroComprobante num = this->proximoComprobante();
    cola.bindValue( ":serie", num.serie() );
    cola.bindValue( ":numero", num.numero() );
    if( cola.exec() ) {
        // busco el ultimo id insetado
        QVariant ret = cola.lastInsertId();
        if( ret.isValid()){
            return ret.toInt();
        } else { return -1; }
    } else {
        qDebug( "Error al hacer exec para insertar un nuevo presupeusto.");
        return -1;
    }
}
