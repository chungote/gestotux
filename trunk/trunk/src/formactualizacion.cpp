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

	ActCerrar = new QAction( "Cerrar", this );
	ActCerrar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
	ActCerrar->setShortcut( QKeySequence( "Ctrl+c" ) );
	ActCerrar->setToolTip( "Cierra la ventana de actualizacion ( Ctrl + c ) " );
	ActCerrar->setStatusTip( "Cierra la ventana de actualizaciones" );
	connect( ActCerrar, SIGNAL( triggered() ), this, SLOT( close() ) );

	ActIniciar = new QAction( "Iniciar", this );
	ActIniciar->setStatusTip( "Inicia la actualizacion" );
	ActIniciar->setShortcut( QKeySequence( "Ctrl+i" ) );
	ActIniciar->setIcon( QIcon( ":/imagenes/next.png" ) );
	connect( ActIniciar, SIGNAL( triggered() ), this, SLOT( iniciar() ) );

	ActDetener = new QAction( "Detener", this );
	ActDetener->setIcon( QIcon( ":/imagenes/stop.png" ) );
	ActDetener->setStatusTip( "Detiene la actualizacion" );
	ActDetener->setToolTip( "Detiene la actualizacion ( Ctrl +d )" );
	ActDetener->setShortcut( QKeySequence( "Ctrl+d" ) );
	ActDetener->setEnabled( false );
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
  //connect( ftp, SIGNAL( commandStarted( int ) ), this, SLOT( inicio( int ) ) );
  connect( ftp, SIGNAL( stateChanged( int ) ), this, SLOT( cambioEstado( int ) ) );
  connect( ftp, SIGNAL( dataTransferProgress( qint64 , qint64 ) ), this, SLOT( transferencia( qint64, qint64 ) ) );
  //connect( ftp, SIGNAL( readyRead() ), this, SLOT( datosListos() ) );

  //Inicio la verificacion
  ActIniciar->setEnabled( false );
  ActDetener->setEnabled( true );
  // Busco los datos desde el registro para el host y puerto
  QSettings *p = preferencias::getInstancia();
  QString host = p->value( "actualizaciones/host", "tranfuga.no-ip.org" ).toString();
  quint16 puerto = p->value( "actualizaciones/puerto", 21 ).toInt();
  ftp->connectToHost( host, puerto );
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
	ActIniciar->setEnabled( true );
	ActDetener->setEnabled( false );
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
  TELog->append( " Inicio del comando " + id );
}

#include <QTemporaryFile>
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
   // Coneccion
   case 1:
   {
      ftp->login();
      break;
   }
   // Login
   case 2:
   {
	  ftp->cd( "actualizaciones" );
	  break;
   }
   case 3:
   {
	ftp->get( "actualizacion.xml" );
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
	if( _arch_dest.find( comando ) != _arch_dest.end() )
	{
		// Se termino de descargar el archivo
		QPair<QString,QString> par = _arch_dest.value( comando );
		_arch_dest.remove( comando );
		TELog->append( "Se termino de descargar el archivo: " + par.first );
		QTemporaryFile archivoRecibido( this );
		archivoRecibido.open();
		archivoRecibido.write( ftp->readAll() );
		qDebug( QString( "Creado archivo temporal: %1 ").arg( archivoRecibido.fileName() ).toLocal8Bit() );
		// lo coloco en la ubicacion necesaria
		QDir dir( QApplication::applicationDirPath() );
		dir.cd( "plugins" );
		dir.cd( par.second );
		if( QFile::exists( dir.filePath( par.first + ".back" ) ) )
		{
			QFile::remove( dir.filePath( par.first + ".back" ) );
		}
		QFile::rename( dir.filePath( par.first ), dir.filePath( par.first + ".back" ) );
		if( QFile::copy( QDir::temp().filePath( archivoRecibido.fileName() ), dir.filePath( par.first ) ) )
		{
			TELog->append( "Archivo actualizado correctamente" );
		}
		else
		{
			qDebug( "Error al copiar el archivo" );
		}
	}
	else
	{
		qDebug( QString("Comando desconocido: %1").arg( comando ).toLocal8Bit() );
	}
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
  if( !docxml->setContent( ftp->readAll(), false ) )
  {
   TELog->append( "Error al analizar el contenido del archivo de actualizaciones" );
   _continuar_actualizando = false;
   return;
  }
  else
  {
   TELog->append( "Descarga correcta." );
  }

  TELog->append( "Analizando actualizaciones disponibles" );
  QDomElement docElem = docxml->documentElement();
  QDomNode n = docElem.firstChild();
  if( n.toElement().attribute( "version", 0 ).toInt() >= 0.2 )
  {
	if( CkBGenerales->isChecked() )
	{
		TELog->append( "Existe una nueva version del programa. Por favor actualicela manualmente" );
	}
	else
	{
		TELog->append( "No existen actualizaciones para esta version de Gestotux. Por Favor actualize el programa a una veriosn superior" );
	}
	ftp->close();
	return;
  }
  else
  {
	if( CkBGenerales->isChecked() )
	{
		  TELog->append( "No se necesita actualizar el programa general." );
	}
   // Veo cada uno de los plugins
   //Busco los nodos de plugins
   QDomNodeList listanodos = docxml->elementsByTagName( "plugin" );
   for( unsigned int i=0; i< listanodos.length(); i++ )
   {
	QDomNode nodo = listanodos.item( i );
	qDebug( QString( "Nodo: %1, nombre=%2,version=%3" ).arg( nodo.nodeName() ).arg( nodo.toElement().attribute("nombre") ).arg(nodo.toElement().attribute("version") ).toLocal8Bit() );
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
		QDomNode nodo_os = n.toElement().elementsByTagName( nombre_os ).item(0);
		qDebug( QString( "Nodo OS: %1" ).arg( nodo.nodeName() ).toLocal8Bit() );
		QDomNodeList nodos_archivos = nodo_os.toElement().elementsByTagName( "archivo" );
		unsigned int posNodo = 0;
		qDebug( QString( "Encontrado %1 nodos").arg( nodos_archivos.length() ).toLocal8Bit() );
		while( posNodo < nodos_archivos.length() )
		{
			QDomNode nodo_archivo = nodos_archivos.item(posNodo);
			QPair<QString,QString> tmp;
			tmp.first = nodo_archivo.toElement().attribute( "nombre" );
			tmp.second = nodo_archivo.toElement().attribute( "directorio_destino" );
			qDebug( QString( "Encontrado archivo %1, dir %2" ).arg( tmp.first ).arg( tmp.second ).toLocal8Bit() );
			TELog->append( QString( "Descargando archivo %1..." ).arg( tmp.first ) );
			int pos = ftp->get( tmp.first );
			_arch_dest.insert( pos, tmp );
			posNodo++;
		}
	}
	else
	{
		TELog->append( QString( "El plugin %1 no necesita actualizarse." ).arg( nombre ) );
	}

   }
   TELog->append( "Lista la actualizacion" );
   ftp->close();
  }
}


/*!
    \fn FormActualizacion::transferencia( qint64 echo, qint64 total )
 */
void FormActualizacion::transferencia( qint64 echo, qint64 total )
{
 //qDebug( QString("transferencia %1 de %2 ").arg(echo).arg(total).toLocal8Bit() );
 PBProgreso->setRange( 0, total );
 PBProgreso->setValue( echo );
}
