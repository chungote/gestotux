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

#include <QFtp>
#include <QSettings>
#include "formactualizacion.h"
#include "actualizacion.h"
#include <QDomDocument>
#include <QDomNode>
#include <QTextEdit>

FormActualizacion::FormActualizacion(QWidget* parent, Qt::WFlags fl)
: QWidget( parent, fl ), Ui::FormActualizacionBase()
{
	this->setAttribute( Qt::WA_DeleteOnClose );
	setupUi(this);

	QAction *ActCerrar = new QAction( "Cerrar", this );
	ActCerrar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
	ActCerrar->setShortcut( QKeySequence( "Ctrl+c" ) );
	ActCerrar->setToolTip( "Cierra la ventana de actualizacion ( Ctrl + c ) " );
	ActCerrar->setStatusTip( "Cierra la ventana de actualizaciones" );
	connect( ActCerrar, SIGNAL( triggered() ), this, SLOT( close() ) );

	QAction *ActIniciar = new QAction( "Iniciar", this );
	ActIniciar->setStatusTip( "Inicia la actualizacion" );
	ActIniciar->setShortcut( QKeySequence( "Ctrl+i" ) );
	ActIniciar->setIcon( QIcon( ":/imagenes/next.png" ) );
	connect( ActIniciar, SIGNAL( triggered() ), this, SLOT( iniciar() ) );

	QAction *ActDetener = new QAction( "Detener", this );
	ActDetener->setIcon( QIcon( ":/imagenes/stop.png" ) );
	ActDetener->setStatusTip( "Detiene la actualizacion" );
	ActDetener->setToolTip( "Detiene la actualizacion ( Ctrl +d )" );
	ActDetener->setShortcut( QKeySequence( "Ctrl+d" ) );
	connect( ActDetener, SIGNAL( triggered()), this, SLOT( detener() ) );

	
	addAction( ActIniciar );
	addAction( ActDetener );
	addAction( ActCerrar );
}

FormActualizacion::~FormActualizacion()
{
}


/*!
    \fn FormActualizacion::iniciar()
 */
void FormActualizacion::iniciar()
{
 _continuar_actualizando = true;

  ftp = new QFtp( this );
  connect( ftp, SIGNAL( commandFinished( int, bool ) ), this, SLOT( finComando( int, bool ) ) );
  connect( ftp, SIGNAL( commandStarted( int ) ), this, SLOT( inicio( int ) ) );
  connect( ftp, SIGNAL( stateChanged( int ) ), this, SLOT( cambioEstado( int ) ) );
  connect( ftp, SIGNAL( dataTransferProgress( int, int ) ), this, SLOT( tranferencia( int, int ) ) );
  connect( ftp, SIGNAL( readyRead( int ) ), this, SLOT( datosListos( int ) ) );
  connect( ftp, SIGNAL( finished( int, bool ) ), this, SLOT( terminado( int, bool ) ) );

  //Inicio la verificacion
  // Busco los datos desde el registro para el host y puerto
  QSettings *p = actualizacion::pref();
  QString host = p->value( "actualizaciones/host", "tranfuga.no-ip.org" ).toString();
  quint16 puerto = p->value( "actualizaciones/puerto", 21 ).toInt();
  ftp->connectToHost( host, puerto );
  ftp->login();
  ftp->cd( "actualizaciones" );
  ftp->get( "actualizacion.xml" );
  ftp->close();
}


/*!
    \fn FormActualizacion::detener()
 */
void FormActualizacion::detener()
{
  _continuar_actualizando = false;
}


/*!
    \fn FormActualizacion::finComando( int comando, bool error )
 */
void FormActualizacion::finComando( int comando, bool error )
{
  if( error )
 {
  TELog->append( QString( "Error al ejecutar el comando : %1, \n error: %2" ).arg( comando ).arg( ftp->errorString() ) );
 }
}


/*!
    \fn FormActualizacion::cambioEstado( int estado )
 */
void FormActualizacion::cambioEstado( int estado )
{
 switch( estado )
 {
  case QFtp::Unconnected:
  {
	TELog->append( "Se desconecto del servidor" );
	break;
  }
  case QFtp::HostLookup:
  {
	TELog->append( "Buscando el servidor de actualizaciones" );
	break;
  }
  case QFtp::Connecting:
  {
	TELog->append( "Conectando al servidor" );
	break;
  }
  case QFtp::Connected:
  {
	TELog->append( "Conectado... ");
	break;
  }
  case QFtp::LoggedIn:
  {
	TELog->append( "Autenticando" );
	break;
  }
  case QFtp::Closing:
  {
	TELog->append( "Cerrando conexion... " );
	break;
  }
  default:
  {
   	TELog->append( "Cambio al estado por default" );
   	break;
  }
 }
}


/*!
    \fn FormActualizacion::inicio( int )
 */
void FormActualizacion::inicio( int id )
{
  // TELog->append( " Inicio del comando " + id );
}


/*!
    \fn FormActualizacion::terminado( int comando, bool  error )
 */
void FormActualizacion::terminado( int comando, bool  error )
{
  TELog->append( QString( "Termino comando %1, error %2" ).arg( comando ).arg( error ) );
  if( error )
  {
   _continuar_actualizando = false;
   return;
  }
  switch( comando )
  {
   case 3:
   {
 	TELog->append( "Descargando indice" );
	break;
   }
   case 4:
   {
	// Analizar el archivo
	TELog->append( "Analizando actualizaciones disponibles" );
	analizarGeneral();
	break;
   }
   default:
   {
    break;
   }
  }
}


/*!
    \fn FormActualizacion::analizarGeneral()
 */
void FormActualizacion::analizarGeneral()
{
  QDomDocument *docxml = new QDomDocument();
  if( !docxml->setContent( ftp->readAll() ) )
  {
   TELog->append( "Error al analizar el contenido del archivo de actualizaciones" );
   /// El Error va a estar por consola
   return;
  }

 
}
