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
#include "hicomp.h"

#include <QString>
#include <QIcon>
#include <QAction>
#include <QMenuBar>
#include <QList>
#include <QStackedWidget>
#include <QWidget>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

QString HiComp::nombrePrograma()  const
{  return QString( "%1 - %2" ).arg( this->empresa() ).arg( this->version() );  }

QIcon HiComp::iconoPrograma() const
{  return QIcon( ":/imagenes/icono.png" ); }

/*!
    \fn HiComp::accionesBarra()
        Retorna las acciones que tiene la barra lateral para este plugin
        @return Lista de acciones
 */
QList<QActionGroup *> HiComp::accionesBarra()
{
 /*QActionGroup *recibos = new QActionGroup( this );
 recibos->setObjectName( "recibos" );
 recibos->addAction( ActNuevoRecibo );
 recibos->addAction( ActRecibos );
 recibos->setProperty( "icono", ":/imagenes/recibo.png" );
 recibos->setProperty( "titulo", "Recibos" );
 QList<QActionGroup*> lista;
 lista.append( recibos );*/
 return QList<QActionGroup*>();
}


bool HiComp::inicializar()
{
 Q_INIT_RESOURCE(hicomp);
 // Genero las acciones y la lista
 ActPagarRecibo = new QAction( "Pagar Recibos", this );
 ActPagarRecibo->setToolTip( "Abre la ventana de dialogo para pagar un recibo ya emitido" );
 //ActPagarRecibo->setIcon( QIcon( ":/imagenes/anteriores.png" ) );
 connect( ActPagarRecibo, SIGNAL( triggered() ), this, SLOT( pagarRecibosEmitidos() ) );

 /*ActNuevoRecibo = new QAction( "Nuevo Recibo", this );
 ActNuevoRecibo->setToolTip( "Crear un nuevo recibo" );
 ActNuevoRecibo->setIcon( QIcon( ":/imagenes/nuevo.png" ) );
 connect( ActNuevoRecibo, SIGNAL( triggered() ), this, SLOT( nuevoRecibo() ) );*/

 return true;
}


QString HiComp::directorioBackup() const
{ return "HiComp"; }


QString HiComp::directorioActualizaciones() const
{ return "HiComp"; }


/*!
    \fn HiComp::formsPreferencias()
 */
QWidgetList HiComp::formsPreferencias()
{
 return QWidgetList();
}

/*!
    \fn HiComp::nombre() const
 */
QString HiComp::nombre() const
{ return "hicomp"; }


/*!
    \fn HiComp::tipo() const
 */
int HiComp::tipo() const
{ return EPlugin::info; }


/*!
    \fn HiComp::crearMenu( QMenuBar *m )
 */
void HiComp::crearMenu( QMenuBar *m )
{
 QMenu *menuHer = m->findChild<QMenu *>( "menuHerramientas" );
 menuHer->addSeparator();
 menuHer->addAction( ActPagarRecibo );
}

bool HiComp::verificarTablas( QStringList )
{
 /*if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "recibos" ) )
 {qWarning( "Error al buscar las tablas del plugin hi comp - recibos" ); return false; }
 if( !QSqlDatabase::database().tables( QSql::Tables ).contains( "clientes" ) )
 {qWarning( "Error al buscar las tablas del plugin hi comp - clientes" ); return false; }*/
 return true;
}


/*!
    \fn HiComp::version() const
 */
double HiComp::version() const
{  return 0.5; }


/*!
    \fn HiComp::empresa() const
 */
QString HiComp::empresa() const
{ return "HiComp Computacion"; }


/*!
    \fn HiComp::companeros()
 */
QString HiComp::companeros()
{  return QString(); }


/*!
    \fn HiComp::crearToolBar( QToolBar *t )
 */
void HiComp::crearToolBar( QToolBar */*t*/ )
{}


/*!
    \fn HiComp::seCierraGestotux()
 */
void HiComp::seCierraGestotux()
{
 Q_CLEANUP_RESOURCE(hicomp);
}

QImage HiComp::imagenPrograma() const
{
    return QImage( ":/imagenes/icono.png" );
}

QAction *HiComp::botonPantallaInicial()
{
    return ( new QAction( this ) );
}

#include "DPagarRecibo.h"
void HiComp::pagarRecibosEmitidos()
{
  DPagarRecibo d;
  d.exec();
  return;
}

QString HiComp::reporte( int tipo ) {
    switch( tipo ) {
        case EReporte::Presupuesto:
        { return "Presupuesto"; break; }
        case EReporte::Factura:
        { return "Factura"; break; }
        case EReporte::Recibo:
        { return "Recibo-hicomp"; break; }
        case EReporte::AnulacionFactura:
        { return "AnulacionFactura"; break; }
        default:
        { return ""; break; }
    }
}

#include <QDate>
#include <QSqlQuery>
#include <QSqlError>


void HiComp::reporteParametros( int tipo, QString &nombre, ParameterList &parametros ) {
    switch( tipo ) {
        case EReporte::Recibo:
        {
            qDebug( "Generando parametros para servicio" );
            // Busco los parametros para realizar los recargos
            int id_servicio = parametros.value( "id_servicio" ).toInt();
            // Busco los datos del servicio
            double precio_base = parametros.value( "precio_base" ).toDouble();
            QDate fecha_inicio = parametros.value( "fecha_inicio" ).toDate();
            // el precio
            QSqlQuery cola;
            if( cola.exec( QString( "SELECT cant_dias, recargo, porcentaje FROM recargos WHERE id_servicio = %1" ).arg( id_servicio ) ) ) {
                int i = 1;
                while( cola.next() ) {
                    if( cola.record().isNull( 1 ) ) {
                        parametros.append( QString( "recargo%1" ).arg( i ), cola.record().value(2).toDouble() );
                        parametros.append( QString( "total%1" ).arg( i ), precio_base * ( 1 + ( cola.record().value(2).toDouble() / 100 ) ));
                    } else {
                        parametros.append( QString( "recargo%1" ).arg( i ), cola.record().value(1).toDouble() );
                        parametros.append( QString( "total%1" ).arg( i ), precio_base + cola.record().value(1).toDouble() );
                    }
                    parametros.append( QString( "fecha%1" ).arg( i ), fecha_inicio.addDays( cola.record().value("cant_dias" ).toInt() ).toString( "dd/MM/yyyy" ) );
                    i++;
                }
                if( i < 4 ) {
                    for( int j = i; j <= 4; j++ ) {
                        parametros.append( QString( "recargo%1" ).arg( j ), "" );
                        parametros.append( QString( "total%1" ).arg( j ), "" );
                        parametros.append( QString( "fecha%1" ).arg( j ), "" );
                    }
                }
            } else {
                qDebug( "HiComp::ReporteParametros::Recibo:: Error de exec de recargos" );
                qDebug( cola.lastError().text().toLocal8Bit() );
                return;
            }

            break;
        }
        default:
        { break; }
    }
    return;
}

Q_EXPORT_PLUGIN2(hicomp, HiComp )