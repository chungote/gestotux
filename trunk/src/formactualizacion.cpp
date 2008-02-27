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
#include "gestotux.h"
#include "preferencias.h"
#include "eplugin.h"
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
#include <QTextEdit>
#include <QDomNodeList>

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
  connect( ftp, SIGNAL( commandFinished( int, bool ) ), this, SLOT( terminado( int, bool ) ) );
  connect( ftp, SIGNAL( commandStarted( int ) ), this, SLOT( inicio( int ) ) );
  connect( ftp, SIGNAL( stateChanged( int ) ), this, SLOT( cambioEstado( int ) ) );
  connect( ftp, SIGNAL( dataTransferProgress( int, int ) ), this, SLOT( tranferencia( int, int ) ) );
  connect( ftp, SIGNAL( readyRead( int ) ), this, SLOT( datosListos( int ) ) );

  //Inicio la verificacion
  // Busco los datos desde el registro para el host y puerto
  QSettings *p = preferencias::getInstancia();
  QString host = p->value( "actualizaciones/host", "tranfuga.no-ip.org" ).toString();
  quint16 puerto = p->value( "actualizaciones/puerto", 21 ).toInt();
  ftp->connectToHost( host, puerto );
  ftp->login();
  ftp->cd( "actualizaciones" );
  ftp->get( "actualizacion.xml" );
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
  //TELog->append( QString( "Termino comando %1, error %2" ).arg( comando ).arg( error ) );
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
  else
  {
   TELog->append( "Descarga correcta." );
  }

  TELog->append( "Analizando actualizaciones disponibles" );
  QDomElement docElem = docxml->documentElement();
  QDomNode n = docElem.firstChild();
  if( n.toElement().attribute( "version", 0 ).toInt() >= 0.1 )
  {
	TELog->append( "Existe una nueva version del programa. Por favor actualicela manualmente" );
	ftp->close();
	return;
  }
  else
  {
   TELog->append( "No se necesita actualizar el programa general." );
   // Veo cada uno de los plugins
   //Busco los nodos de plugins
   QDomNodeList listanodos = docxml->elementsByTagName( "plugin" );
   for( int i=0; i< listanodos.size(); i++ )
   {
	QDomNode nodo = listanodos.item( i );
	// Comparo las versiones del programa
	QString nombre = nodo.toElement().attribute( "nombre" );
	double versionNueva = nodo.toElement().attribute( "version" ).toDouble();
	double versionAnterior = gestotux::pluginsHash()->value( nombre )->version();
	if( versionNueva > versionAnterior )
	{
		TELog->append( QString( "Actualizando plugin %1..." ).arg( nombre ) );
		#ifdef Q_WS_WIN32
		QString nombre_os = "windows";
		#endif
		#ifdef Q_WS_X11
		QString nombre_os = "linux";
		#endif
		QDomNodeList nodos_os = n.toElement().elementsByTagName( nombre_os );
		QDomNode nodo_os = nodos_os.item( 0 );
		if( nodo_os.toElement().hasAttribute( "archivo" ) )
		{
			ftp->get( nodo_os.toElement().attribute( "archivo" ) );
			///@todo ver donde ponerlo para que al terminar el comando, lo sobreescriba y lo descarge
		}
	}
	else
	{
		TELog->append( QString( "El plugin %1 no necesita actualizarse" ).arg( nombre ) );
	}

   }
   TELog->append( "Lista la actualizacion" );
   ftp->close();
  }
}
