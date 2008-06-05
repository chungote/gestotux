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
#include "erenderizadorinforme.h"

#include <QTextDocument>
#include "formfiltro.h"
#include "../../TipoMovs.h"
#include <QTextCursor>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QTextTable>
#include <QProgressDialog>

ERenderizadorInforme::ERenderizadorInforme( QObject *padre )
: QObject( padre )
{
 _doc = new QTextDocument( this );
 cursor = new QTextCursor( _doc );
}


ERenderizadorInforme::~ERenderizadorInforme()
{
}

/*!
    \fn ERenderizadorInforme::setPropiedades( FormFiltro *f )
 */
void ERenderizadorInforme::setPropiedades( FormFiltro *f, QString estilo )
{
 _estilo = estilo;
 _filtra_tipo = _filtra_categoria = _filtra_fecha = _filtra_rango_fecha = _filtra_estab = false;
 if( f->tieneTipo() )
 {
   _filtra_tipo = true;
   _id_tipo = f->tipo();
 }
 if( f->tieneEstablecimiento() )
 {
	_filtra_estab = true;
	_id_estab = f->establecimiento();
 }
 if( f->tieneCategoria() )
 {
	_filtra_categoria = true;
	_id_cat = f->categoria();
 }
 if( f->tieneFechaEspecifica() )
 {
	_filtra_fecha = true;
	_fecha = f->FechaEspecifica();
 }
 if( f->tieneRangoFecha() )
 {
	_filtra_rango_fecha = true;
	_rango_fechas = f->rangoFechas();
 }
}

/*!
    \fn ERenderizadorInforme::hacerInforme()
 */
bool ERenderizadorInforme::hacerInforme()
{
 d = new QProgressDialog( 0 );
 d->setLabelText( "Buscando coincidencias..." );
 d->setMinimumDuration( 0 );
 QStringList tris = buscarTris();
 if( tris.isEmpty() )
 {
	d->setLabelText( "No se encontraron coincidencias" );
	d->setRange( 0, 1 );
	d->setValue( 1 );
 }
 foreach( QString tri, tris )
 {
	qDebug( QString( "haciendo tri: %1" ).arg( tri ).toLocal8Bit() );
  // Genero la cabecera para ese tri
  d->setLabelText( "Generando cabecera" );
  hacerCabecera( tri );
  d->setLabelText( "Buscando datos..." );
  generarCola( tri );
  if( cola.size() == 0 )
  {
   QTextCursor * cursor = new QTextCursor( _doc );
   cursor->insertText( "\n\nNo existen resultados" );
  }
  generarCabeceraTabla();
  colocarContenido();
 }
 d->setLabelText( "Mostrando Informe.." );
 return true;
}


/*!
    \fn ERenderizadorInforme::hacerCabecera()
 */
void ERenderizadorInforme::hacerCabecera( QString tri )
{
 cursor->movePosition( QTextCursor::End );
 cursor->insertHtml( "<h1>Administración de Caravanas Corrientes</h1><br />" );
 // Busco los datos del tri
 QSqlQuery cola( QString("SELECT * FROM car_tri WHERE id_tri = '%1'" ).arg( tri ) );
 if( cola.next() )
 {
	/*
	nombre de la empresa arriba en grande centrado
	abajo
	centrado un poquito mas chico
	nombre del sistema (Sistema de  gestion de trazabilidad) Administracion Corrientes S.A nombre de la empresa
	Nro de Tri
	Fecha
	Categoria
	Cantidad de caravanas
	Vendedor (o campo destino y origen)
	Comprador
	Nro de dta
	Nro de Guia
	*/
	cursor->insertText( QString( "#TRI: %1.\n" ).arg( cola.record().value( "id_tri" ).toString() ) );
	cursor->insertText( QString( "Fecha: %1.\n" ).arg( cola.record().value( "fecha" ).toDate().toString() ) );
	QSqlQuery colaAuxiliar;
	colaAuxiliar.exec(  QString("SELECT nombre FROM car_categorias WHERE id_categoria = '%1'").arg( cola.record().value( "id_categoria" ).toString() ) );
	if(colaAuxiliar.next())
	{
 		cursor->insertText( QString( "Categoria: %1\n" ).arg( colaAuxiliar.record().value(0).toString() ) );
	} else { qDebug( QString( "Error al ejecutar la cola de nombre de categoria: %1" ).arg( colaAuxiliar.lastError().text() ).toLocal8Bit() ); }
	QString texti;
	switch( cola.record().value( "razon" ).toInt() )
	{
		case venta:
		{
			texti = "Venta de Caravanas";
			colaAuxiliar.exec( QString("SELECT nombre FROM car_establecimientos WHERE id_establecimiento = '%1'").arg( cola.record().value( "id_estab_origen" ).toInt() ) );
			if( colaAuxiliar.next() )
			{
				cursor->insertText( QString( "Establecimiento de origen:  %1\n" ).arg( colaAuxiliar.record().value(0).toString() ) );
			}
			else
			{ qDebug( "Error al ejecutar la cola de nombre de establecimiento" ); }
		}
		case compra:
		{
			texti = "Ingreso de Caravanas por Compra";
			colaAuxiliar.exec( QString("SELECT nombre FROM car_establecimientos WHERE id_establecimiento = '%1'").arg( cola.record().value( "id_estab_destino" ).toInt() ) );
			if( colaAuxiliar.next() )
			{
				cursor->insertText( QString( "Establecimiento de destino:  %1\n" ).arg( colaAuxiliar.record().value(0).toString() ) );
			}
			else
			{ qDebug( "Error al ejecutar la cola de nombre de establecimiento" ); }
		}
		case mudanza:
		{
			texti = "Movimiento de Caravanas entre Establecimientos";
			colaAuxiliar.exec( QString("SELECT nombre FROM car_establecimientos WHERE id_establecimiento = '%1'").arg( cola.record().value( "id_estab_origen" ).toInt() ) );
			if( colaAuxiliar.next() )
			{
				cursor->insertText( QString( "Establecimiento de origen:  %1\n" ).arg( colaAuxiliar.record().value(0).toString() ) );
			}
			else
			{ qDebug( "Error al ejecutar la cola de nombre de establecimiento" ); }
			colaAuxiliar.exec( QString("SELECT nombre FROM car_establecimientos WHERE id_establecimiento = '%1'").arg( cola.record().value( "id_estab_destino" ).toInt() ) );
			if( colaAuxiliar.next() )
			{
				cursor->insertText( QString( "Establecimiento de destino:  %1\n" ).arg( colaAuxiliar.record().value(0).toString() ) );
			}
			else
			{ qDebug( "Error al ejecutar la cola de nombre de establecimiento" ); }
		}
	}
	cursor->insertText( texti + "\n" );
	cursor->insertText( QString( "#DTA: %1\n" ).arg( cola.record().value( "dta" ).toString() ) );
	if( !cola.record().value("guia").toString().isEmpty() )
	{ cursor->insertText( QString( "#Guia: %1\n" ).arg( cola.record().value( "guia" ).toString() ) ); }
 }
 else
 {
  qDebug( "Error al seleccionar el tipo de movimiento" );
  qDebug( cola.lastError().text().toLocal8Bit() );
  return;
 }
 // listo
}


/*!
    \fn ERenderizadorInforme::setarCabeceraFiltros()
 */
void ERenderizadorInforme::setarCabeceraFiltros()
{
 cursor->movePosition( QTextCursor::End );
 if( _filtra_estab )
 {
  QSqlQuery cola( QString("SELECT nombre FROM car_establecimientos WHERE id_establecimiento = '%1'").arg( _id_estab ) );
  if( !cola.next() )
  {
   qWarning( "Error al buscar el nombre del establecimiento" );
  }
  else
  {
   cursor->insertHtml( QString( "Establecimiento: %1" ).arg( cola.record().value(0).toString() ).prepend( "<h3>" ).append( "</h3><br />" ) );
  }
 }
 if( _filtra_categoria )
 {
  QSqlQuery cola( QString("SELECT nombre FROM car_categorias WHERE id_categoria = '%1'").arg( _id_cat ) );
  if( !cola.next() )
  {
   qWarning( "Error al buscar el nombre de la categoria" );
  }
  else
  {
   cursor->insertHtml( QString( "Categoria: %1" ).arg( cola.record().value(0).toString() ).prepend( "<h3>" ).append( "</h3><br />" ) );
  }
 }
 if( _filtra_tipo )
 {
  QString texti;
  switch( _id_tipo )
  {
	case stock:
	{
	 texti = "Ingreso de Caravanas por Stock";
	 break;
	}
	case compra:
	{
	 texti = "Ingreso de Caravanas por Compra";
	 break;
	}
	case venta:
	{
	 texti = "Venta de Caravanas";
	 break;
	}
	case mudanza:
	{
	 texti = "Movimiento de Caravanas entre Establecimientos";
	 break;
	}
	default:
	{
	 texti = "Desconocido";
	 break;
	}
  }
  cursor->insertHtml( "<h3>" + texti + "</h3><br />" );
 }
 if( _filtra_fecha )
 {
  cursor->insertHtml( QString( "Fecha: %1" ).arg( _fecha.toString( "dd/MM/yyyy" ) ).prepend( "<h3>" ).append( "</h3><br />" ) );
 }
 if( _filtra_rango_fecha )
 {
  cursor->insertHtml( QString( "Entre %1 y %2" ).arg( _rango_fechas.first.toString( "dd/MM/yyy" ) ).arg( _rango_fechas.second.toString( "dd/MM/yyy" ) ).prepend( "<h3>" ).append( "</h3><br />" ) );
 }
}


void ERenderizadorInforme::generarCabeceraTabla()
{
 // Genero la tabla
 cursor->movePosition( QTextCursor::End );
 tabla = cursor->insertTable( 1, 2 );
 tabla->format().setHeaderRowCount(1);
 tabla->cellAt( 0,0 ).firstCursorPosition().insertHtml( "#Num" );
 tabla->cellAt( 0,1 ).firstCursorPosition().insertHtml( "#Caravana" );
}


void ERenderizadorInforme::colocarContenido()
{
 if( !cola.isActive() )
 {
  qCritical( "La cola esta inactiva" );
  return;
 }
 d->setLabelText( "Generando informe" );
 d->setRange( 0, cola.size() );
 while( cola.next() )
 {
  int pos = tabla->rows();
  tabla->insertRows( pos, 1 );
  tabla->cellAt( pos, 0 ).firstCursorPosition().insertHtml( QString( "%L1" ).arg( pos ) );
  tabla->cellAt( pos, 1 ).firstCursorPosition().insertHtml( cola.record().value(0).toString() );
  d->setValue( d->value() + 1 );
 }
}


/*!
    \fn ERenderizadorInforme::generarCola()
 */
void ERenderizadorInforme::generarCola()
{
 QString where;bool filtra_algo = false;
 if( _filtra_categoria )
 {
  if( !where.isEmpty() )
  {
    where += " AND ";
  }
  where += QString("t.id_categoria = '%1'").arg( _id_cat );
  filtra_algo = true;
 }
 if( _filtra_tipo )
 {
  if( !where.isEmpty() )
  {
    where += " AND ";
  }
  where += QString("t.razon = '%1'").arg( _id_tipo );
  filtra_algo = true;
 }
 if( _filtra_estab )
 {
  if( !where.isEmpty() )
  {
    where += " AND ";
  }
  where += QString( " t.id_tri IN ( SELECT id_tri FROM car_tri WHERE ( id_estab_origen = '%1' OR id_estab_destino = '%1' ) )" ).arg( _id_estab );
  filtra_algo = true;
 }
 if( _filtra_fecha )
 {
  if( !where.isEmpty() )
  {
   where += " AND ";
  }
  where += QString( " t.fecha = '%1' " ).arg( _fecha.toString(Qt::ISODate) );
  filtra_algo = true;
 }
 if( _filtra_rango_fecha )
 {
  if( !where.isEmpty() )
  {
   where += " AND ";
  }
  where += QString( " t.fecha BETWEEN( '%1', '%2' )  " ).arg( _rango_fechas.first.toString(Qt::ISODate) ).arg( _rango_fechas.second.toString(Qt::ISODate) );
  filtra_algo = true;
 }
 if( filtra_algo )
 {
  where.prepend( "WHERE " );
 }
 if( cola.exec( QString( "SELECT c.codigo FROM car_tri as t, car_caravana as c %1" ).arg( where ) ) )
 {
  qDebug( cola.lastQuery().toLocal8Bit() );
  return;
 }
 else
 {
  	qWarning( QString( "Error al hacer el exec de la cola de datos\n Error: %1\n %2" ).arg( cola.lastError().text() ).arg( cola.lastQuery() ).toLocal8Bit() );
	return;
 }

}

/*!
    \fn ERenderizadorInforme::cerrarDialogo()
 */
void ERenderizadorInforme::cerrarDialogo()
{
 d->close();
}

#include <QPrinter>
#include <QTextEdit>
/*!
    \fn ERenderizadorInforme::imprimir( QPrinter *impresora )
 */
void ERenderizadorInforme::imprimir( QPrinter *impresora )
{
 QTextDocument d;
 d.setDefaultStyleSheet( _estilo );
 d.setHtml( _doc->toHtml() );
 d.print( impresora );
}


/*!
    \fn ERenderizadorInforme::buscarTris()
	Busca la lista de tris que coinciden con el codigo y los devuelve en una lista
 */
QStringList ERenderizadorInforme::buscarTris()
{
  QStringList lista;
  QString where;
  bool filtra_algo = false;
 if( _filtra_categoria )
 {
  if( !where.isEmpty() )
  {
    where += " AND ";
  }
  where += QString("t.id_categoria = '%1'").arg( _id_cat );
  filtra_algo = true;
 }
 if( _filtra_tipo )
 {
  if( !where.isEmpty() )
  {
    where += " AND ";
  }
  where += QString("t.razon = '%1'").arg( _id_tipo );
  filtra_algo = true;
 }
 if( _filtra_estab )
 {
  if( !where.isEmpty() )
  {
    where += " AND ";
  }
  where += QString( " t.id_tri IN ( SELECT id_tri FROM car_tri WHERE ( id_estab_origen = '%1' OR id_estab_destino = '%1' ) )" ).arg( _id_estab );
  filtra_algo = true;
 }
 if( _filtra_fecha )
 {
  if( !where.isEmpty() )
  {
   where += " AND ";
  }
  where += QString( " t.fecha = '%1' " ).arg( _fecha.toString(Qt::ISODate) );
  filtra_algo = true;
 }
 if( _filtra_rango_fecha )
 {
  if( !where.isEmpty() )
  {
   where += " AND ";
  }
  where += QString( " t.fecha BETWEEN( '%1', '%2' )  " ).arg( _rango_fechas.first.toString(Qt::ISODate) ).arg( _rango_fechas.second.toString(Qt::ISODate) );
  filtra_algo = true;
 }
 if( filtra_algo )
 {
  where.prepend( "WHERE " );
 }
 if( cola.exec( QString( "SELECT id_tri FROM car_tri %1" ).arg( where ) ) )
 {
  qDebug( cola.lastQuery().toLocal8Bit() );
  while( cola.next() )
  {
	lista.append( cola.record().value(0).toString() );
  }
  return lista;
 }
 else
 {
  	qWarning( QString( "Error al hacer el exec de la cola de obtener tris\n Error: %1\n %2" ).arg( cola.lastError().text() ).arg( cola.lastQuery() ).toLocal8Bit() );
	return QStringList();
 }
}


/*!
    \fn ERenderizadorInforme::generarCola( QString tri )
 */
void ERenderizadorInforme::generarCola( QString tri )
{
 cola.exec( QString( "SELECT codigo FROM car_caravana WHERE id_caravana IN ( SELECT id_caravana FROM car_carv_tri WHERE id_tri='%1' )" ).arg( tri ) );
}
