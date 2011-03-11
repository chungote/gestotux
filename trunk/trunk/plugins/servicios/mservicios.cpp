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
 * \fn MServicios::getPeriodoActual( int id_servicio )
 * Devuelve el periodo actual del servicio en el año en curso.
 * \param id_servicio ID del servicio que queremos buscar
 * \return ?
 */
QString MServicios::getPeriodoActual( const int id_servicio )
{
    QDate fecha_alta_servicio = getFechaAlta( id_servicio );
    QDate hoy = QDate::currentDate();
    int cant_dias_periodo = MServicios::getCantidadDiasPeriodo( id_servicio, hoy );
    // Calculo
    int t = fecha_alta_servicio.daysTo( hoy );
    double u = t/cant_dias_periodo;
    int periodo = floor( u );
    // Busco las fechas del inicio y fin del periodo
    return QString( "%1/%2 del <fecha_inicio_periodo> al <fecha_fin_periodo>" ).arg( periodo ).arg( hoy.year() )/*.arg( hoy.toString() ).arg( fecha_alta_servicio.toString() )*/;
}

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

/*!
 * \fn MServicios::getCantidadDiasPeriodo( const int id_servicio, const QDate fecha_calculo )
 * Devuelve la cantidad de días en el periodo del servicio solicitado. Utilitaria.
 * @param id_servicio Identificador del servicio al cual se le quiere saber la cantidad de días.
 * @param fecha_calculo utilizado para referencia en @MSercicios::getCantidadDiasEnPeriodo
 * @return Cantidad de días en el periodo del servicio
 */
int MServicios::getCantidadDiasPeriodo( const int id_servicio, const QDate fecha_calculo )
{
    QSqlQuery cola( QString( "SELECT periodo FROM servicios WHERE id_servicio = %2" ).arg( id_servicio ) );
    if( cola.exec() ) {
        if( cola.next() ) {
            return getDiasEnPeriodo( cola.record().value(0).toInt(), fecha_calculo );
        } else {
            qDebug( "Servicios:MServicios:Error al buscar la fecha de alta del periodo y su periodo -> next" );
            return -1;
        }
    } else {
        qDebug( "Servicios:MServicios:Error al buscar la fecha de alta del periodo y su periodo  -> exec" );
        return -1;
    }
}

/*!
 * \fn MServicios::getDiasEnPeriodo( const int id_periodo, const QDate fecha_alta, QDate fecha_calculo )
 * Considerando que todos los periodos se ajustan dentro de un año, devolverá el numero de días que tiene el periodo seleccionado en la fecha elegida ( sin parametro fecha actual ) segun la fecha de alta del servicio.
 * En el caso de que sea mensual, se devolverá la cantidad de días que tiene el mes de fecha_calculo
 * En el caso de que sea bimestral, se devolverá la cantidad de días que tiene el mes de fecha_calculo mas la cantidad de días que tiene el mes siguiente.
 * En el caso de que sea trimestra, se devolverá la cantidad de días que tiene el mes de fecha_calculo mas la cantidad de días que tienen los 2 meses siguientes.
 * @param id_periodo Tipo de periodo que estamos considerando
 * @param fecha_calculo Fecha que se desea averiguar el periodo ( predeterminada fecha actual )
 * @return Cantidad de Días que tiene el periodo que corresponde a la fecha solicitada
 */
int MServicios::getDiasEnPeriodo( const int tipo_periodo, QDate fecha_calculo )
{
    // Cuidado con los mensuales! ( feb en año bisiesto )
    switch( tipo_periodo )
    {
        case MServicios::Semanal:
        {
            // Semanal -> La semana siempre tiene 7 dias independientemente del día del mes
            // Corte anual ¿Considerarlo? ( cuando la semana no esta completa un año )
            return 7;
        }
        case MServicios::Quincenal:
        {
            // Quincenal -> se considera como "medio mes"
            // Verificar caso de febrero y meses con 30 o 31 días
            return 14;
        }
        case MServicios::Mensual:
        {
            // Mensual
            // Verificar el mes del periodo y devolver la cantidad de días
            return QDate( 0, fecha_calculo.month(), fecha_calculo.year() ).daysInMonth();
            // Eso se encarga automaticamnete de los años bisiestos
        }
        case MServicios::BiMensual:
        {
            // BiMensual
            // Siempre voy a pedir estos datos al inicio del periodo
            QDate f1( 0, fecha_calculo.month(), fecha_calculo.year() );
            QDate f2 = f1.addMonths(1);
            QDate f3( f2.daysInMonth(), f2.month(), f2.year() );
            return f1.daysTo( f3 );
        }
        case MServicios::Trimestral:
        {
            // Trimensual
            // Siempre voy a pedir estos datos al inicio del periodo
            QDate f1( 0, fecha_calculo.month(), fecha_calculo.year() );
            QDate f2 = f1.addMonths(2);
            QDate f3( f2.daysInMonth(), f2.month(), f2.year() );
            return f1.daysTo( f3 );
        }
        case MServicios::Cuatrimestral:
        {
            // Cuatrimestral
            // Siempre voy a pedir estos datos al inicio del periodo
            QDate f1( 0, fecha_calculo.month(), fecha_calculo.year() );
            QDate f2 = f1.addMonths(3);
            QDate f3( f2.daysInMonth(), f2.month(), f2.year() );
            return f1.daysTo( f3 );
        }
        case MServicios::Seximestral:
        {
            //Seximestral
            // Siempre voy a pedir estos datos al inicio del periodo
            QDate f1( 0, fecha_calculo.month(), fecha_calculo.year() );
            QDate f2 = f1.addMonths(5);
            QDate f3( f2.daysInMonth(), f2.month(), f2.year() );
            return f1.daysTo( f3 );
        }
        case MServicios::Anual:
        {
            // Como consideramos los servicios con base en 1 año, siempre es periodo 1
            return fecha_calculo.daysInYear();
        }
        default:
        { return 0; }
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