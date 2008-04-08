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
#include "TipoMovs.h"
#include <QTextCursor>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QTextTable>

ERenderizadorInforme::ERenderizadorInforme( QObject *padre )
: QObject( padre )
{
}


ERenderizadorInforme::~ERenderizadorInforme()
{
}


/*!
    \fn ERenderizadorInforme::setDocumento( QTextDocument *doc )
 */
void ERenderizadorInforme::setDocumento( QTextDocument *doc )
{
  _doc = doc;
  _doc->clear();
}


/*!
    \fn ERenderizadorInforme::setPropiedades( FormFiltro *f )
 */
void ERenderizadorInforme::setPropiedades( FormFiltro *f )
{
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
void ERenderizadorInforme::hacerInforme()
{
 hacerCabecera();
 setarCabeceraFiltros();
}


/*!
    \fn ERenderizadorInforme::hacerCabecera()
 */
void ERenderizadorInforme::hacerCabecera()
{
 QTextCursor *cursor = new QTextCursor( _doc );
 QTextCharFormat formatoCaracter;
 formatoCaracter.setFontWeight( QFont::Black );
 formatoCaracter.setFontPointSize( 12 );
 cursor->setCharFormat( formatoCaracter );
 QTextBlockFormat formatoBloque;
 formatoBloque.setAlignment( Qt::AlignCenter );
 cursor->setBlockFormat( formatoBloque );
 cursor->insertBlock( formatoBloque, formatoCaracter );
 cursor->insertText( "Administración de Caravanas Corrientes" );
}


/*!
    \fn ERenderizadorInforme::setarCabeceraFiltros()
 */
void ERenderizadorInforme::setarCabeceraFiltros()
{
 QTextCursor *cursor = new QTextCursor( _doc );
 cursor->movePosition( QTextCursor::End );
 QTextCharFormat formatoCaracter = cursor->charFormat();
 formatoCaracter.setFontWeight( QFont::Normal );
 formatoCaracter.setFontPointSize( 10 );
 cursor->setCharFormat( formatoCaracter );
 QTextBlockFormat formatoBloque = cursor->blockFormat();
 formatoBloque.setAlignment( Qt::AlignLeft );
 cursor->setBlockFormat( formatoBloque );
 cursor->insertBlock();
 if( _filtra_estab )
 {
  QSqlQuery cola( QString("SELECT nombre FROM car_establecimientos WHERE id_establecimiento = '%1'").arg( _id_estab ) );
  if( !cola.next() )
  {
   qWarning( "Error al buscar el nombre del establecimiento" );
  }
  else
  {
   cursor->insertText( QString( "Establecimiento: %1 \n" ).arg( cola.record().value(0).toString() ), formatoCaracter );
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
   cursor->insertText( QString( "Categoria: %1 \n" ).arg( cola.record().value(0).toString() ), formatoCaracter );
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
  cursor->insertText( texti , formatoCaracter );
 }

 // Inserto la tabla
 // Tengo que mostrar el TRI, DTA Y Codigo de caravana
 generarCola();
 if( cola.size() == 0 )
 {
  qWarning( "No existen resultados para la busqueda con estos parametros." );
  cursor->insertText( "\n\nNo existen resultados" );
  return;
 }
 // Genero la tabla
 cursor->movePosition( QTextCursor::End );
 QTextTable *tabla = cursor->insertTable( 1, 3 );
 QTextTableFormat formatoTabla = tabla->format();
 formatoTabla.setHeaderRowCount( 1 );
// Ancho de las cabeceras
 QVector<QTextLength> anchos;
 anchos<<QTextLength( QTextLength::PercentageLength, 20.0 )<<QTextLength( QTextLength::PercentageLength, 20.0 )<<QTextLength( QTextLength::PercentageLength, 20.0 );
 formatoTabla.setColumnWidthConstraints( anchos );
 formatoTabla.setCellPadding( 2.0 );
 formatoTabla.setBorder( 0 );
 tabla->setFormat( formatoTabla );
 
 tabla->cellAt( 0,0 ).firstCursorPosition().insertText( "#TRI" );
 tabla->cellAt( 0,1 ).firstCursorPosition().insertText( "#DTA" );
 tabla->cellAt( 0,2 ).firstCursorPosition().insertText( "#Caravana" );
 if( !cola.isActive() )
 {
  qCritical( "La cola esta inactiva" );
  return;
 }
 while( cola.next() )
 {
  int pos = tabla->rows();
  tabla->insertRows( pos, 1 );
  tabla->cellAt( pos, 0 ).firstCursorPosition().insertText( cola.record().value(0).toString() );
  tabla->cellAt( pos, 1 ).firstCursorPosition().insertText( cola.record().value(1).toString() );
  tabla->cellAt( pos, 2 ).firstCursorPosition().insertText( cola.record().value(2).toString() );
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
  where += QString( " t.fecha = '%1' " ).arg( _fecha.toString() );
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
 if( cola.exec( QString( "SELECT t.id_tri, t.dta, c.codigo FROM car_tri as t, car_caravana as c %1" ).arg( where ) ) )
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
