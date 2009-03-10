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
#include "ereporte.h"
#include <QSqlDatabase>
#include <QApplication>
#include "ncreport.h"


EReporte::EReporte(QObject *parent)
 : QObject(parent)
{
 Q_INIT_RESOURCE( ncreport );
 reporte = new NCReport( QString::null, 0 );
 reporte->setShowPrintDialog( true );
 reporte->setPreviewAsMain( true );	// preview is the main form on preview mode
 reporte->setDeleteReportAfterPreview( true );	// delete report object after close preview
 reporte->setPreviewIsMaximized( false );
 reporte->setParseMode( NCReport::fromFile );
 reporte->setFileEncoding( "iso8859-2" );
 reporte->setOutput( NCReport::Preview );
 reporte->setOutputFile( "print.pdf" );
}


EReporte::~EReporte()
{
}

/*!
    \fn EReporte::setArchivo( QString nombre )
 */
bool EReporte::setArchivo( QString nombre )
{
 if( !QFile::exists( QApplication::applicationDirPath() + nombre ) )
 {
	qDebug( qPrintable( "El archivo " + QApplication::applicationDirPath() + QDir::separator() + nombre + " no existe" ) );
	return false;
 }
 else
 {
	reporte->setReportFile( QApplication::applicationDirPath() + QDir::separator() + nombre );
	return true;
 }
}


/*!
    \fn EReporte::imprimir()
 */
void EReporte::imprimir()
{
 reporte->runReportToPrinter();
}


/*!
    \fn EReporte::aPdf()
 */
void EReporte::aPdf()
{
 reporte->runReportToPDF();
}

/*!
    \fn EReporte::previsualizar()
 */
void EReporte::previsualizar()
{
 reporte->runReportToPreview();
}


/*!
    \fn EReporte::agregarParametro( QString nombre, QVariant valor )
 */
void EReporte::agregarParametro( QString nombre, QVariant valor )
{
 switch( valor.type() )
 {
  case QVariant::UInt:
  case QVariant::ULongLong:
  case QVariant::Double:
  case QVariant::Int:
  {
    reporte->addParameter( valor.toString(), nombre, "number" );
  }
  case QVariant::Date:
  case QVariant::DateTime:
  {
   reporte->addParameter( valor.toString(), nombre, "date" );
  }
  default:
  {
   reporte->addParameter( valor.toString(), nombre );
  }
 }
}
