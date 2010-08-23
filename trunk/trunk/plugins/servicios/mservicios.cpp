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
#include <QSqlRecord>
#include <QSqlError>
#include <QDate>

MServicios::MServicios(QObject *parent)
 : QSqlTableModel(parent)
{
 setTable( "servicios" );
 setHeaderData( 0, Qt::Horizontal, tr( "#ID" ) );
 setHeaderData( 1, Qt::Horizontal, tr( "Nombre" ) );
 setHeaderData( 2, Qt::Horizontal, tr( "Fecha de Alta" ) );
 setHeaderData( 3, Qt::Horizontal, tr( "Fecha de Baja" ) );
 setHeaderData( 4, Qt::Horizontal, tr( "Precio Base" ) );
 setHeaderData( 5, Qt::Horizontal, tr( "Periodo" ) );
 setHeaderData( 6, Qt::Horizontal, tr( "Dia de Cobro" ) );
 setHeaderData( 7, Qt::Horizontal, tr( "Forma de cobro incompleto" ) );
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
                case 5: // Periodo
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
                case 7: // Metodo Incompleto
                {
                        switch( QSqlTableModel::data( item, role ).toInt() ) {
                            case MServicios::DiasFaltantes:
                            { return "Dias Faltantes"; }
                            case MServicios::MesCompleto:
                            { return "Mes Completo"; }
                        }
                }
                case 4:
                { return QString( "$ %L1" ).arg( QSqlTableModel::data( item, role ).toDouble() ); }
                default:
                { return QSqlTableModel::data( item, role ); }
            }
        }
        default:
        { return QSqlTableModel::data( item, role ); }
    }
}





/*!
    \fn MServicios::asociarCliente( int id_cliente, int id_servicio, QDate fecha )
        Asocia el cliente con el servicio correspondiente en la base de datos en la fecha de alta indicada.
        @param id_cliente Identificador de cliente
        @param id_servicio Identificador del servicio
        @param fecha Fecha en que el cliente se da de alta en el servicio
        @return Verdadero si la asociacion se pudo realizar correctamente
 */
bool MServicios::asociarCliente( int id_cliente, int id_servicio, QDate fecha )
{
 QSqlTableModel *modelo = new QSqlTableModel();
 modelo->setTable( "servicios_cliente" );
 modelo->setEditStrategy( QSqlTableModel::OnManualSubmit );
 QSqlRecord registro = modelo->record();
 registro.setValue( "id_cliente", id_cliente );
 registro.setValue( "id_servicio", id_servicio );
 registro.setValue( "fecha_adhesion", fecha );
 registro.setNull( "fecha_baja" );
 if( modelo->insertRecord( -1, registro ) )
 {
  if( !modelo->submitAll() )
  {
   qWarning( qPrintable( "Error al hacer submit en el modelo: " + modelo->lastError().text() ) );
   return false;
  }
 }
 else
 {
  qWarning( qPrintable( "Error al hacer insertar en el modelo: " + modelo->lastError().text() ) );
  return false;
 }
 delete modelo;
 return true;
}

/*!
    \fn MServicios::agregarServicio( QString nombre, QString detalle, QDate fecha_alta, double precio_base, Periodo periodo, int dia_cobro, int forma_incompleto )
        Agrega un nuevo servicio a la base de datos con los datos pasados como parametro
        @param nombre Nombre del servicio
        @param detalle Explicacion mas detallada del servicio
        @param fecha_alta Fecha desde cuando empieza a funcionar el servicio
        @param precio_base Precio base sobre el cual se calculan los recargos
        @param periodo Periodo de cobro del servicio @MServicios::Periodo
        @param dia_cobro Dia del periodo en que se inicia el cobro del servicio
        @param forma_incompleto Forma de cobro cuando se da de alta un cliente fuera del inicio del periodo @MServicios::FormaIncompleto
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