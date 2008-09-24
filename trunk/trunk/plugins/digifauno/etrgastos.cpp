//
// C++ Implementation: etrgastos
//
// Description:
//
//
// Author: Esteban Javier Zeller <juiraze@yahoo.com.ar>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "etrgastos.h"
#include <QSqlQuery>
#include <QVariant>
#include <QProgressDialog>
#include <QSqlError>
#include <QSqlRecord>
#include <QTextDocument>
#include <QTextTableCell>
#include <QDate>
#include <QTextCursor>

ETRGastos::ETRGastos()
 : QThread()
{
}


ETRGastos::~ETRGastos()
{
}


void ETRGastos::run()
{
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // Seccion de Gastos
 QSqlQuery cola;
 cola.prepare( QString( "SELECT COUNT(id) FROM gastos WHERE fecha BETWEEN '%1' AND '%2' " ).arg( primero.toString( "yyyy-MM-dd" ) ).arg( ultimo.toString( "yyyy-MM-dd" ) ) );
 if( cola.exec() )
 {
  if( !cola.next() )
  {
   qDebug( "error en  next1()" );
   qDebug( cola.lastError().text().toLocal8Bit() );
   qDebug( cola.lastQuery().toLocal8Bit() );
   return;
  }
  else
  {
   QVariant cantidad = cola.record().value( 0 );
   if( cantidad.toInt() > 0 )
   {
    if( noSeguir )
    {
      return;
    }
        dialogo->setLabelText( "Gastos - Sumando..." );
        dialogo->setRange( 0, cantidad.toInt()+1 );
        dialogo->setValue( 0 );
	// Busco la cantidad en precio
	cola.prepare( QString( "SELECT SUM( costo ) FROM gastos WHERE fecha BETWEEN '%1' AND '%2'" ).arg( primero.toString( "yyyy-MM-dd" ) ).arg( ultimo.toString( "yyyy-MM-dd" ) ) );
	if( cola.exec() )
	{
		if( cola.next() )
		{
		      if( noSeguir )
		      {
		        return;
		      }
			total -= cola.record().value(0).toDouble();
			QVariant subtotalgastos = cola.record().value(0);

			tabla->insertRows( -1, 1 );
			tabla->mergeCells( tabla->rows()-1, 0, 1, 3 );

			QTextTableCell celda = tabla->cellAt( tabla->rows()-1,0 );
			celda.firstCursorPosition().setBlockFormat( centrado );
			celda.firstCursorPosition().insertText( "GASTOS", cabeceraSeccion );

                        dialogo->setLabelText( "Gastos - Generando contenidos... " );
                        // Listado de gastos
                        QSqlQuery cola1;
                        if( cola1.exec( QString( "SELECT descripcion, COUNT( id ), SUM( costo ) FROM gastos WHERE fecha BETWEEN '%1' AND '%2' GROUP BY descripcion" ).arg( primero.toString( "yyyy-MM-dd" ) ).arg( ultimo.toString( "yyyy-MM-dd" ) ) ) )
                        {
                          while( cola1.next() )
                          {
                           if( noSeguir ) {return;}
                              dialogo->setValue( dialogo->value() + 1 );
                             tabla->insertRows( -1, 1 );
                             tabla->cellAt( tabla->rows()-1, 0 ).firstCursorPosition().setBlockFormat( centrado );
                             tabla->cellAt( tabla->rows()-1, 0 ).firstCursorPosition().insertText( QString( "%L1" ).arg( cola1.record().value(1).toInt() ) );
                             tabla->cellAt( tabla->rows()-1, 1 ).firstCursorPosition().insertText( cola1.record().value(0).toString() );
                             tabla->cellAt( tabla->rows()-1, 2 ).firstCursorPosition().setBlockFormat( centrado );
                             tabla->cellAt( tabla->rows()-1, 2 ).firstCursorPosition().insertText( QString( "$ %L1" ).arg( cola1.record().value(2).toDouble() ) );
                          }

                        }
                        else
                        {
                          qDebug( "Error al ejecutar cola1 - gastos" );
                          qDebug( cola1.lastError().text().toLocal8Bit() );
                          qDebug( cola1.lastQuery().toLocal8Bit() );
                        }
			// Pongo el totales
			dialogo->setLabelText( "Gastos - Seteando subtotal... " );
			tabla->insertRows( -1, 1 );
			tabla->mergeCells( tabla->rows()-1, 0, 1, 2 );
			tabla->cellAt( tabla->rows()-1, 0 ).firstCursorPosition().setBlockFormat( derecha );
			tabla->cellAt( tabla->rows()-1, 0 ).firstCursorPosition().insertText( "Total de gastos:" );
			tabla->cellAt( tabla->rows()-1, 2 ).firstCursorPosition().setBlockFormat( centrado );
			tabla->cellAt( tabla->rows()-1, 2 ).firstCursorPosition().insertText( QString( "$ %L1" ).arg( subtotalgastos.toDouble() ) );
			dialogo->setValue( dialogo->value() + 1 );
		}
 	}
	else
	{
	 qDebug( "Error de exec cola sum costo gastos" );
         qDebug( cola.lastError().text().toLocal8Bit() );
         qDebug( cola.lastQuery().toLocal8Bit() );
	}
   }
  }
 }
 else
 {
  qDebug( "Error al intentar ejecutar cola de cantidad de gastos " );
 }
 exec();
}

