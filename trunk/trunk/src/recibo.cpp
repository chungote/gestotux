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
#include "recibo.h"

#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QPaintEngine>
#include <QVariant>
#include <QDebug>
#include <QSvgRenderer>
#include <QSqlError>
#include <QTextStream>
#include <math.h>
#include "preferencias.h"

Recibo::Recibo(QObject *parent)
 : QObject(parent)
{
 QFile archivo( ":/recibos.svg" );
 if( !archivo.open( QIODevice::ReadOnly ) )
 {
  qCritical( "No se puede encontrar el archivo original de recibo" );
  return;
 }
 if( !domdoc.setContent( &archivo ) )
 {
  qWarning( "Error al pasar el contenido desde el archivo al documento dom" );
  return;
 }
 archivo.close();
}


Recibo::~Recibo()
{
}




/*!
    \fn Recibo::obtenerByteArray()
 */
QByteArray Recibo::obtenerByteArray()
{
 return( domdoc.toByteArray() );
}


/*!
    \fn Recibo::titulo()
 */
QString Recibo::titulo()
{
 return nombre_cliente;
}


/*!
    \fn Recibo::cargarRegistro( idDB )
 */
bool Recibo::cargarRegistro( int idDB )
{
 QSqlQuery cola( QString( "SELECT c.nombre, c.apellido, c.direccion, r.id, r.texto, r.precio, r.fecha_pago, r.contado, r.cuenta_corriente FROM recibos r, clientes c WHERE r.id = '%1' AND r.cliente = c.id" ).arg( idDB ) );
 if( !cola.exec() )
 {
  qWarning( "Error al ejecutar la cola de obtencion de datos de recibo" );
  qWarning( QString( "id= %1; error=%2" ).arg( idDB ).arg( cola.lastError().text() ).toLocal8Bit() );
  return false;
 }
 if( cola.next() )
 {
    this->num_recibo = cola.record().value(3).toInt();
    this->nombre_cliente = cola.record().value(1).toString() + ", " + cola.record().value(0).toString();
    this->direccion = cola.record().value(2).toString();
    this->total = cola.record().value(5).toDouble();
    this->fecha_pagado = cola.record().value(6).toDate();
    this->descripcion = cola.record().value(4).toString();
    this->contado = cola.record().value(7).toBool();
    this->cuenta_corriente = cola.record().value(8).toBool();
    reajusteXML();
    return true;
 }
 else
 {
  qWarning( "Al parecer no existe el id seleccionado" );
  qWarning( QString( "id= %1; error=%2" ).arg( idDB ).arg( cola.lastError().text() ).toLocal8Bit() );
  return false;
 }
}


/*!
    \fn Recibo::reajusteXML()
 */
void Recibo::reajusteXML()
{
 QDomNodeList lista = domdoc.elementsByTagName( "text" );
 if( lista.isEmpty() )
 {
  qWarning( "Error: no existen nodos de texto en el xml!" );
  return;
 }

 for( int i = 0; i< lista.size(); i++ )
 {
  if( lista.item(i).toElement().attribute( "id" ) == "tTotal" )
  {
   lista.item(i).firstChild().toText().setData( QString( "$ %L1" ).arg( total, 10, 'f', 2, QLatin1Char(' ') ) );
  }
  else if ( lista.item(i).toElement().attribute( "id" ) == "tCliente" )
  {
   lista.item(i).firstChild().toText().setData( nombre_cliente );
  }
  else if( lista.item(i).toElement().attribute( "id" ) == "tDireccion" )
  {
   lista.item(i).firstChild().toText().setData( direccion );
  }
  else if( lista.item(i).toElement().attribute( "id" ) == "tNumRecibo" )
  {
   lista.item(i).firstChild().toText().setData( generarNumeroRecibo() );
  }
  else if( lista.item(i).toElement().attribute( "id" ) == "tFechaDia" )
  {
   lista.item(i).firstChild().toText().setData( fecha_pagado.toString( "dd" ) );
  }
  else if( lista.item(i).toElement().attribute( "id" ) == "tFechaMes" )
  {
   lista.item(i).firstChild().toText().setData( fecha_pagado.toString( "MM" ) );
  }
  else if( lista.item(i).toElement().attribute( "id" ) == "tFechaAno" )
  {
   lista.item(i).firstChild().toText().setData( fecha_pagado.toString( "yy" ) );
  }
  else if( lista.item(i).toElement().attribute( "id" ) == "tContado" )
  {
   if( !this->contado )
   {
    lista.item(i).firstChild().toText().setData( "" );
   }
  }
  else if( lista.item(i).toElement().attribute( "id" ) == "tCuentaCorriente" )
  {
   if( !this->cuenta_corriente )
   {
    lista.item(i).firstChild().toText().setData( "" );
   }
  }
 }

 lista = domdoc.elementsByTagName( "rect" );
 for( int i = 0; i< lista.size(); i++ )
 {
  if( lista.item(i).toElement().attribute( "id" ) == "rTexto" )
  {
   QDomNode padre = lista.item(i).parentNode();
   this->hacerText( padre,
                    lista.item(i).toElement().attribute( "width" ).toDouble(),
                    lista.item(i).toElement().attribute( "x" ).toDouble(),
                    lista.item(i).toElement().attribute( "y" ).toDouble() );
   padre.removeChild( lista.item(i) );
  }
 }
 /*QFile arch( "salida.svg" );
 arch.open( QIODevice::WriteOnly );
 QTextStream s( &arch );
 s << domdoc.toByteArray();
 arch.flush();
 arch.close();*/
}


/*!
    \fn Recibo::imprimir( QPrinter impresora )
 */
void Recibo::imprimir( QPrinter *impresora )
{
 QSvgRenderer rend( this->obtenerByteArray() );
 QPainter pintador( impresora );
 rend.render( &pintador );
 // Calculo el defasaje inicial
 QDomNodeList nodos = domdoc.elementsByTagName( "rect" );
 QDomElement nodo;
 for( int i=0; i<nodos.size(); i++ )
 {
  if( nodos.item(i).toElement().attribute( "id" ) == "rGrande" )
  {
   nodo = nodos.item(i).toElement();
  }
 }
 preferencias *p = preferencias::getInstancia();
 p->inicio();
 double defasaje = nodo.attribute( "x" ).toDouble() + nodo.attribute( "width" ).toDouble();
 defasaje *= 30;
 defasaje += p->value( "preferencias/recibos/margen", 40 ).toDouble() * 30;
 pintador.translate( QPointF( defasaje, 0 ) );
 rend.render( &pintador );
}


/*!
    \fn Recibo::generarNumeroRecibo()
 */
QString Recibo::generarNumeroRecibo()
{
  QString t1 = QString::number( num_recibo );
  if( t1.length() < 6 )
  {
   for( int i = t1.length(); i<=6; i++ )
   {
    t1.prepend( "0" );
   }
   t1.prepend( "0000-" );
   return t1;
  }
  else
  {
   for( int i = t1.length(); i<=10; i++ )
   {
    t1.prepend( "0" );
   }
   t1.insert( 4, '-' );
   return t1;
  }
}


/*!
    \fn Recibo::hacerText( QDomNode padre )
 */
void Recibo::hacerText( QDomNode padre, const double ancho, double x, double y )
{
 int contador = 0;
 double total = 0;
 double posx = x;
 double posy = y;
 QString descripcion2 = descripcion;
 while( contador < descripcion2.count() )
 {
  if( total < ancho )
  {
    total += anchoCaracter( descripcion2.at( contador ) );
    {
     contador++;
    }
  }
  else
  {
    QDomNode nodo = domdoc.createElement( "text" );
    nodo.toElement().setAttribute( "x", posx );
    nodo.toElement().setAttribute( "y", posy );
    posy += 4.5;
    nodo.toElement().setAttribute( "font-size", "4" );
    nodo.toElement().setAttribute( "font-family", "Verdana" );
    nodo.toElement().setAttribute( "fill", "black" );
    // Veo hasta donde llege
    QString texto = descripcion2.left( contador );
    descripcion2.remove( descripcion2.left( contador ) );
    nodo.appendChild( domdoc.createTextNode( texto ) );
    padre.appendChild( nodo );
    total = 0;
    contador = 0;
  }
 }
 if( total < ancho )
 {
  QDomNode nodo = domdoc.createElement( "text" );
    nodo.toElement().setAttribute( "x", posx );
    nodo.toElement().setAttribute( "y", posy );
    posy += 4.5;
    nodo.toElement().setAttribute( "font-size", "4" );
    nodo.toElement().setAttribute( "font-family", "Verdana" );
    nodo.toElement().setAttribute( "fill", "black" );
    // Veo hasta donde llege
    QString texto = descripcion2.left( contador );
    descripcion2.remove( descripcion2.left( contador ) );
    nodo.appendChild( domdoc.createTextNode( texto ) );
    padre.appendChild( nodo );
 }
 // ver si me queda algo que no se haya completado
}




double Recibo::anchoCaracter( QString car )
{
 // Si es mayusculas
 if( car.contains( QRegExp( "[A-Z]", Qt::CaseSensitive, QRegExp::RegExp ) ) )
 {
  return 4.3;
 }
 // Si es minusculas
 if( car.contains( QRegExp( "[a-z]", Qt::CaseSensitive, QRegExp::RegExp ) ) )
 {
  return 2.10;
 }
 // si es !
 if( car ==  "!" )
 {
  return 1.45;
 }
 // si es .
 if( car == "." )
 {
  return 1.28;
 }
 // si es espacio
 return 1.58;
}
