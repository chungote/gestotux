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
#include "presupuestodefault.h"

#include <QTextTable>

/*!
    \fn PresupuestoDefault::nombre() const
	Devuelve el nombre  del plugin
	@return Nombre del plugin
 */
QString PresupuestoDefault::nombre() const
{ 
    return "default";
}

/*!
    \fn PresupuestoDefault::version() const
	Devuelve la version actual del plugin
	@return Version del plugin
 */
double PresupuestoDefault::version() const
{
    return 0.1;
}

Q_EXPORT_PLUGIN2( default, PresupuestoDefault );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PresupuestoDefault::setTituloPersonalizado( const QString titulo )
{ _titulo = titulo; }

void PresupuestoDefault::setCliente( const QString cliente )
{ _texto_destinatario = cliente; }

void PresupuestoDefault::setFecha( const QDate fecha )
{ _fecha = fecha; }

QTextTable* PresupuestoDefault::tablaProductos()
{ return _tablaProductos; }

void PresupuestoDefault::setTablaProductos ( QTextTable* theValue )
{ _tablaProductos = theValue; }

void PresupuestoDefault::setTotal( const double t )
{ _total = t; }

QTextDocument * PresupuestoDefault::getDocumento()
{ return _doc; }

QString PresupuestoDefault::cliente()
{ return _texto_destinatario; }

QString PresupuestoDefault::titulo()
{ return _titulo; }

double PresupuestoDefault::total()
{ return _total; }

QDate PresupuestoDefault::fecha()
{ return _fecha; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <QTextTable>
#include <QTextCursor>
#include <QSqlTableModel>
void PresupuestoDefault::generarTabla( QSqlTableModel *mod, const QString tituloTabla, const bool cabeceras )
{
 // Calculo la cantidad de filas mas las opcionales cabeceras
 int filas = mod->rowCount();
 if( !tituloTabla.isEmpty() )
 { filas++; }
 if( cabeceras )
 { filas++; }
 if( _tablaProductos == 0 )
 {
   QTextCursor *cursor = new QTextCursor( _doc );
   _tablaProductos = cursor->insertTable( filas, mod->columnCount()-2 );
 }
 else
 {
  // Hago que la tabla quede con la cantidad de filas que tiene el modelo
  int diferencia = filas - _tablaProductos->rows();
  if( diferencia > 0 )
  {
    _tablaProductos->insertRows( -1, qAbs(diferencia) );
  }
  else if( diferencia < 0 )
  {
   _tablaProductos->removeRows( -1, qAbs(diferencia) );
  }
  else
  {
   qDebug( "No se modifico la cantidad de filas" );
  }
 }
 // Coloco el titulo de la tabla
 int desplazado = 0;
 if( !tituloTabla.isEmpty() )
 {
  _tablaProductos->mergeCells( 0,0, 1, mod->columnCount()-2 );
  QTextCursor *ctemp = new QTextCursor( _tablaProductos->cellAt( 0, 0 ).firstCursorPosition() );
  ctemp->setPosition( _tablaProductos->cellAt( 0, 0 ).lastCursorPosition().position(), QTextCursor::KeepAnchor );
  ctemp->removeSelectedText();
  _tablaProductos->cellAt( 0, 0 ).firstCursorPosition().insertText( tituloTabla );
  // Sumo el desplazamiento para el inicio de las filas
  desplazado++;
 }
 // Cabeceras de las columnas
 if( cabeceras )
 {
  for(int i = 2; i<mod->columnCount(); i++ )
  {
   //Borro lo que estaba antes
   QTextCursor *ctemp = new QTextCursor( _tablaProductos->cellAt( desplazado, i-2 ).firstCursorPosition() );
   ctemp->setPosition( _tablaProductos->cellAt( 1, i-2 ).lastCursorPosition().position(), QTextCursor::KeepAnchor );
   ctemp->removeSelectedText();
   _tablaProductos->cellAt( desplazado, i-2 ).firstCursorPosition().insertText( mod->headerData( i, Qt::Horizontal, Qt::DisplayRole ).toString() );
  }
  desplazado++;
 }
 //fila va a ser respecto al modelo
 for( int fila = 0; fila < mod->rowCount(); fila++ )
 {
  for( int col = 2; col < mod->columnCount(); col++ )
  {
   QTextTableCell celda = _tablaProductos->cellAt( fila+desplazado, col-2 );
   if( celda.isValid() )
   {
    QTextCursor *ctemp = new QTextCursor( celda.firstCursorPosition() );
    ctemp->setPosition( celda.lastCursorPosition().position(), QTextCursor::KeepAnchor );
    ctemp->removeSelectedText();
    if( !celda.firstCursorPosition().isNull() )
    {
      celda.firstCursorPosition().insertText( mod->data( mod->index( fila, col ), Qt::DisplayRole ).toString() );
    }
   }
  }
 }
}

#include <QFile>
/*!
    \fn PresupuestoDefault::regenerar( const QTextDocument *docCont )
 */
void PresupuestoDefault::regenerar( const QTextDocument *docCont )
{
 if( archivo == 0 )
 {
  archivo= new QFile( ":/presupuesto/pre.html" );
  if( !archivo->open( QIODevice::ReadOnly ) )
  {
    qWarning( "Error al abrir el archivo pre.html" );
    return;
  }
  
 }
}
