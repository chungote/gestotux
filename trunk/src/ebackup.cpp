/***************************************************************************
 *   Copyright (C) 2006 by Esteban Zeller & Daniel Sequeira		   *
 *   juiraze@yahoo.com.ar  - daniels@hotmail.com			   *
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
#include "ebackup.h"
#include "preferencias.h"

#include <QStringList>
#include <QByteArray>
#include <QString>
#include <QVariant>
#include <QFile>
#include <QSqlDatabase>
#include <QPushButton>
#include <QFrame>
#include <QProgressBar>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QTabWidget>
#include <QLineEdit>
#include <QToolButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QDate>
#include <QProgressDialog>
#include <QTabWidget>
#include <QSqlDriver>
#include <QTextStream>
#include "eenviobackup.h"

Ebackup::Ebackup( QWidget* parent )
: EVentana( parent ), Ui_FormBackupBase()
{
 setupUi(this);
 this->setAttribute( Qt::WA_DeleteOnClose );
 setObjectName( "backup" );
 setWindowTitle( "Copia de Seguridad" );
 PBProgreso->setValue( 0 );
 LDebug->setText( "Presione Iniciar para comenzar" );
 // inicializo el deposito de datos
 datos = new QByteArray();
 comprimidos = new QByteArray();

 ActCerrar = new QAction( "Cerrar", this );
 ActCerrar->setStatusTip( "Cierra la ventana y cancela cualquier backup que se este realizando" );
 ActCerrar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
 connect( ActCerrar, SIGNAL( triggered() ), this, SLOT( close() ) );

 ActIniciar = new QAction( "Iniciar", this );
 ActIniciar->setStatusTip( "Inincia la generación de los backups" );
 ActIniciar->setIcon( QIcon( ":/imagenes/next.png" ) );
 connect( ActIniciar, SIGNAL( triggered() ), this, SLOT( iniciar() ) );

 ActDetener = new QAction( "Detener", this );
 ActDetener->setStatusTip( "Detiene la ejecución actual del backup" );
 ActDetener->setIcon( QIcon( ":/imagenes/stop.png" ) );
 connect( ActIniciar, SIGNAL( triggered() ), this, SLOT( detener() ) );
 connect( this, SIGNAL( cambiarDetener( bool ) ), ActDetener, SLOT( setEnabled( bool ) ) );

 emit cambiarDetener( false );

 addAction( ActIniciar );
 addAction( ActDetener );
 addAction( ActCerrar );

 ChBBaseDatos->setCheckState( Qt::Checked );

 connect( tBBuscar, SIGNAL( clicked() ), this, SLOT( abrirArchivoBackup() ) );

 Pestanas->setTabIcon( 0, QIcon( ":/imagenes/backup1.png" ) );
 Pestanas->setTabIcon( 1, QIcon( ":/imagenes/backup2.png" ) );
 Pestanas->widget( 0 )->setObjectName( "crearBackup" );
 Pestanas->widget( 1 )->setObjectName( "restaurarBackup" );
}


Ebackup::~Ebackup()
{
 delete comprimidos;
 delete datos;
}

/*!
 *   \fn Ebackup::iniciar()
 *	Realiza todo el proceso de creacion del backup.
 */
void Ebackup::iniciar()
{
 // Ver en que pesta�a esta
 if( Pestanas->currentIndex() == 0 )
 {
  generarBackup();
 }
 else if( Pestanas->currentIndex() == 1 )
 {
  restaurarBackup();
  return;
 }
 else
 {
  qWarning( "Pestaña desconocida" );
 }
}


/*!
    \fn Ebackup::generar_config()
    Genera un una copia de los valores de configuracion del programa y los prepara para la compresion.
 */
bool Ebackup::generar_config()
{
 preferencias *p = preferencias::getInstancia();
 // Obtengo todas las claves
 QStringList claves = p->allKeys();
 PBProgreso->setRange( 0, ( claves.size() * 2 ) + 2 );
 PBProgreso->setValue( 0 );
 // Genero los datos concatenando las variables
 // Inicio de preferencias
 // Cabecera de los datos
 datos->append("|->preferencias->");
 // bucle que recorre cada valor
 QStringList::const_iterator iterador;
 for( iterador = claves.constBegin(); iterador != claves.constEnd(); ++iterador )
 {
	if( !_continuar )
	{ return false; }
   datos->append( (*iterador).toLocal8Bit().constData() );
   PBProgreso->setValue( PBProgreso->value() + 1 );
   datos->append( "=" );
   // Separador de valores
   QVariant v = p->value( (*iterador), QVariant() );
   QString result;
   switch( v.type() )
   {
	///////////////////////////////////////////////////////////////////////////
	// Copiado desde la clase qsettings de qt
       case QVariant::Invalid:
       {
            result = QLatin1String("@Invalid()");
            break;
       }

        case QVariant::ByteArray:
        {
            QByteArray a = v.toByteArray();
            result = QLatin1String("@ByteArray(");
            result += QString::fromLatin1(a.constData(), a.size());
            result += QLatin1Char(')');
            break;
        }

        case QVariant::String:
        case QVariant::LongLong:
        case QVariant::ULongLong:
        case QVariant::Int:
        case QVariant::UInt:
        case QVariant::Bool:
        case QVariant::Double:
        case QVariant::KeySequence: {
            result = v.toString();
            if (result.startsWith(QLatin1Char('@')))
                result.prepend(QLatin1Char('@'));
            break;
        }
        case QVariant::Rect: {
            QRect r = qvariant_cast<QRect>(v);
            result += QLatin1String("@Rect(");
            result += QString::number(r.x());
            result += QLatin1Char(' ');
            result += QString::number(r.y());
            result += QLatin1Char(' ');
            result += QString::number(r.width());
            result += QLatin1Char(' ');
            result += QString::number(r.height());
            result += QLatin1Char(')');
            break;
        }
        case QVariant::Size: {
            QSize s = qvariant_cast<QSize>(v);
            result += QLatin1String("@Size(");
            result += QString::number(s.width());
            result += QLatin1Char(' ');
            result += QString::number(s.height());
            result += QLatin1Char(')');
            break;
        }
        case QVariant::Point: {
            QPoint p = qvariant_cast<QPoint>(v);
            result += QLatin1String("@Point(");
            result += QString::number(p.x());
            result += QLatin1Char(' ');
            result += QString::number(p.y());
            result += QLatin1Char(')');
            break;
        }
        default: {
            QByteArray a;
            {
                QDataStream s(&a, QIODevice::WriteOnly);
                s.setVersion(QDataStream::Qt_4_0);
                s << v;
            }

            result = QLatin1String("@Variant(");
            result += QString::fromLatin1(a.constData(), a.size());
            result += QLatin1Char(')');
            break;
        }
        //////////////////////////////////////////////////////////////////////////////
    }
    datos->append( result );
    PBProgreso->setValue( PBProgreso->value() + 1 );
   // Separador de preferencia
   datos->append( "\n" );
 }
 // fin de los datos
 datos->append("<-preferencias<-|");
 // Comprimo los datos y los envio al buffer de comprimidos
 LDebug->setText( LDebug->text() + "... Comprimiendo.... " );
 comprimir();
 PBProgreso->setValue( PBProgreso->value() + 1 );
 // Limpio el buffer asi se libera la memoria
 LDebug->setText( LDebug->text() + "... Limpiando.... " );
 datos->clear();
 PBProgreso->setValue( PBProgreso->value() + 1 );
 LDebug->setText( "Listo backup de configuracion" );
 return true;
}


/*!
    \fn Ebackup::generar_db( bool estructura )
	Funcion que hace la obtencion de los datos de la base de datos y los prepara para la compresion.
	@param estructura Hacer backup de la estructura de la db
	@return Verdadero si no existieron errores, falso en caso contrario
 */
bool Ebackup::generar_db( bool estructura )
{
 QSqlDriver *db = QSqlDatabase::database().driver();
 datos->append( "|->basedatossql->\n" );
 // veo que tipo de db es la que se esta usando
 datos->append( QString("formato=%1;\n").arg( QSqlDatabase::database().driverName() ) );
 ////////////////////////////////////////////////////////////////////////
 QStringList tablas = QSqlDatabase::database().tables();
 int total = 0;
 QString tabla; QSqlQuery cola;
 foreach( tabla, tablas )
 {
	//Calculo para la barra
	cola.exec( QString("SELECT COUNT(*) FROM %1" ).arg( tabla ) );
	if( cola.next() )
	{
		total += cola.record().value(0).toInt();
	}
 }
 total += tablas.size();
 PBProgreso->setRange( 0, total );
 if( estructura )
 {
  QFile origen( ":/sql/tablas."+QSqlDatabase::database().driverName()+".sql" );
  if( origen.open( QIODevice::ReadOnly ) )
  {
	datos->append( QTextStream( &origen ).readAll() );
  }
 }
 foreach( tabla, tablas )
 {
  PBProgreso->setValue( PBProgreso->value() + 1 );
	// Genero la cola de creacion de la tabla si es necesario
	/*if( estructura )
	{
	}*/
	cola.exec( QString( "SELECT * FROM %1" ).arg( tabla ) );
	while( cola.next() )
	{
		datos->append( db->sqlStatement( QSqlDriver::InsertStatement, tabla, cola.record(), false ) );
		datos->append( ";\n" );
		PBProgreso->setValue( PBProgreso->value() + 1 );
	}
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////
 datos->append( "<-basedatossql<-|" );
 LDebug->setText( LDebug->text() + "... Comprimiendo.... " );
 comprimir();
 PBProgreso->setValue( PBProgreso->value() + 1 );
 LDebug->setText( LDebug->text() + "... Limpiando.... " );
 datos->clear();
 PBProgreso->setValue( PBProgreso->value() + 1 );
 LDebug->setText( "Listo backup de Base de datos" );
 return true;
}


/*!
    \fn Ebackup::comprimir()
	Funcion que comprime los datos en datos y lo agrega al buffer de datos comprimidos
	@return Verdadero si no hubo errores.
 */
bool Ebackup::comprimir()
{
 comprimidos->append( *datos );
 return true;
}


/*!
    \fn Ebackup::guardar_a_archivo( QString *nombre )
	Guarda los datos comprimidos en el archivo cuya ruta se encuentra en "nombre"
	@param nombre path del archivo de salida
	@return Verdadero si no hubo errores
 */
bool Ebackup::guardar_a_archivo( QString *nombre )
{
 destino = new QFile( *nombre );
 if( !destino->open( QIODevice::ReadWrite | QIODevice::Truncate ) )
 {
	qDebug( "Error al abrir el archivo en modo lectura escritura" );
	delete destino;
	return false;
 }
 qint64 escritos = destino->write( *comprimidos );
 if( escritos != comprimidos->size() )
 {
  qDebug( "Las cantidades de bytes no coinciden" );
  qDebug( QString( "Bytes escritos: %1, Bytes de buffer: %2" ).arg(escritos).arg(comprimidos->size()).toLocal8Bit() );
  destino->flush();
  destino->close();
  delete destino;
  return false;
 }
 else
 {
  destino->flush();
  destino->close();
  delete destino;
  return true;
 }
}


/*!
    \fn Ebackup::detener()
 */
void Ebackup::detener()
{
  _continuar = false;
}


/*!
    \fn Ebackup::generarBackup()
 */
void Ebackup::generarBackup()
{
  emit cambiarDetener( true );
 _continuar = true;
 QSqlQuery cola( "DELETE FROM ventas WHERE id IN ( SELECT id FROM ventas WHERE id NOT IN ( SELECT id_venta FROM ventas_productos ) )" );
 if( !ChBBaseDatos->isChecked() && !ChBConfirugacion->isChecked() )
 {
  QMessageBox::information( this, "Seleccione opciones" , "Por favor, seleccione una opcion para iniciar la copia de seguridad" );
  emit cambiarDetener( false );
  return;
 }
 LDebug->setText( "Iniciando" );
 if( ChBBaseDatos->isChecked() )
 {
  LDebug->setText( "Generando backup de Base de datos" );
  if( !generar_db( CkBEstructura->isChecked() ) )
  {
   qDebug( "Error al intentar generar la copia de seg de la db" );
   emit cambiarDetener( false );
   return;
  }
 }
 if( ChBConfirugacion->isChecked() )
 {
  LDebug->setText( "Generando backup de Configuracion del programa" );
  if( !generar_config() )
  {
   qDebug( "Error al generar el backup de la config" );
   emit cambiarDetener( false );
   return;
  }
 }
 else
 {
  PBProgreso->setValue( PBProgreso->maximum() );
 }
 LDebug->setText( "Guardando..." );
 QString nombre = QDate::currentDate().toString( "yyyyMMdd" );
 QFileDialog::Options options;
 options |= QFileDialog::DontUseNativeDialog;
 QString selectedFilter;
 QString fileName = QFileDialog::getSaveFileName( this,
						  "Seleccione el lugar a donde guardar el archivo",
						  QDir::home().path()+QDir::separator()+nombre,
						  "Archivos de Backup ( *.bkp );; Todos los archivos (*.*)",
						  &selectedFilter,
						  options );
 if( !fileName.isEmpty() )
 {
  if( !fileName.contains( ".bkp" ) )
  {
   fileName.append( ".bkp" );
  }
  if( !guardar_a_archivo( &fileName ) )
  {
   //qDebug( "Error al intentar guardar el archivo" );
   QMessageBox::critical( this, "Error", "Hubo un error al intentar guardar el archivo de backup" );
   emit cambiarDetener( false );
   return;
  }
  else
  {
   QMessageBox::information( this, "Informacion", "El archivo de backup se ha guardado correctamente" );
   preferencias *p = preferencias::getInstancia();
   p->setValue( "backup/archivo", fileName );
   p->setValue( "backup/enviado", false );
   p->setValue( "backup/fecha", QDate::currentDate() );
   p->sync();
   close();
  }
 }
 emit cambiarDetener( false );
}


/*!
    \fn Ebackup::restaurarBackup()
 */
void Ebackup::restaurarBackup()
{
 emit cambiarDetener( true );
 _continuar = true;
 // Intento abrir el archivo de backup
 QFile archivo( LEArchivo->text() );
 if( !archivo.open( QIODevice::ReadOnly ) )
 {
	qWarning( "No se puede arbir el archivo de backup para restaruarlo. Verifique que la ruta sea correcta y que no este en uso" );
	emit cambiarDetener( false );
	return;
 }

 QString contenido = archivo.readAll();
 if( contenido.isEmpty() )
 {
  qWarning( "Error al leer el archivo. teoricamente esta vacio." );
  emit cambiarDetener( false );
  return;
 }
 // empiezo a analizar el contenido
 // tengo que encontrar la cabecera sino es invalido
 if( contenido.startsWith( "|->basedatossql->", Qt::CaseSensitive ) )
 {
  // Encontrado datos sql, elimino la cabecera
  contenido.remove( 0, QString( "|->basedatossql->formato= " ).size() );
  // ahora tiene que estar el formato
  QString formato = contenido.section( ";", 0, 0 );
  if( formato != QSqlDatabase::database().driverName() )
  {
   qWarning( QString( "Este backup no es para este tipo de base de datos. Formato: " + formato ).toLocal8Bit() );
   return;
  }
  // saco esa subcadena
  contenido.remove( 0, formato.size() + 1 );
  // desde ahora hasta el fin de la etiqueta, es sql puro
  // busco la etiqueta de fin
  int posfinal = contenido.indexOf( "<-basedatossql<-|" );
  QStringRef cadenas( &contenido, 0, posfinal );
  ejecutarColas( cadenas.string()->split( ";" ) );
  contenido.remove( 0, posfinal + QString( "<-basedatosql<-|").size() );
 }
 // Verifico si contiene el backup de las preferencias
 if( contenido.startsWith( "|->preferencias->", Qt::CaseSensitive ) )
 {
  // Elimino la cabecera de las preferencias
  contenido.remove( 0, QString( "|->preferencias->" ).size() );
  // Busco el fin de las preferencias
  int posfinal = contenido.indexOf( "<-preferencias<-|" );
  QStringRef pref( &contenido, 0, posfinal );
  regenerarPreferencias( pref.string() );
  contenido.remove( 0, posfinal + QString( "<-preferencias<-|").size() );
 }
 // fin de la recuperaci�n
 return;
}


/*!
    \fn Ebackup::abrirArchivoBackup()
 */
void Ebackup::abrirArchivoBackup()
{
 QFileDialog::Options options;
 options |= QFileDialog::DontUseNativeDialog;
 QString selectedFilter;
 QString fileName = QFileDialog::getOpenFileName( this,
						  "Seleccione el archivo de backup",
						  QDir::home().path()+QDir::separator(),
						  "Archivos de Backup ( *.bkp )",
						  &selectedFilter,
						  options );
 LEArchivo->setText( fileName );
}


/*!
    \fn Ebackup::ejecutarColas( QStringList colas )
 */
bool Ebackup::ejecutarColas( QStringList colas )
{
 bool estado = true;
 QSqlQuery *cola = new QSqlQuery();
 while( colas.size() > 0  && estado == true )
 {
  if( cola->exec( colas.at( 0 ) ) )
  {
    colas.removeFirst();
  }
  else
  {
	qWarning( qPrintable( cola->lastError().text() + ". Cola: " + cola->lastQuery() ) );
	estado = false;
  }
 }
 delete cola;
 if( estado == false )
 {
  QSqlDatabase::database().rollback();
 }
 else
 {
  QSqlDatabase::database().commit();
 }
 return estado;
}


/*!
    \fn Ebackup::regenerarPreferencias( const QString *pref )
 */
void Ebackup::regenerarPreferencias( const QString *pref )
{
    /// \todo implement me
}
