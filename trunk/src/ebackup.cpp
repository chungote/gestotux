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
#include "eenviobackup.h"

Ebackup::Ebackup( QWidget* parent )
: EVentana( parent ), Ui_FormBackupBase()
{
 setupUi(this);
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

 ChBCompri->setCheckState( Qt::Checked );
 ChBBaseDatos->setCheckState( Qt::Checked );
}


Ebackup::~Ebackup()
{}

/*!
 *   \fn Ebackup::iniciar()
 *	Realiza todo el proceso de creacion del backup.
 */
void Ebackup::iniciar()
{
 emit cambiarDetener( true );
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
  if( !generar_db( true, true ) )
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
   p->sync();
   close();
  }
 }
 emit cambiarDetener( false );
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
    \fn Ebackup::generar_db( bool estructura, bool datos )
	Funcion que hace la obtencion de los datos de la base de datos y los prepara para la compresion.
	@param estructura Hacer backup de la estructura de la db
	@param datos Hacer backup de los datos de la db
	@return Verdadero si no existieron errores, falso en caso contrario
 */
bool Ebackup::generar_db( bool estructura, bool data )
{
 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
 // calculos para progreso
 QSqlQuery tam( "SELECT COUNT(name) FROM sqlite_master WHERE type='table'" );
 if( !tam.exec() )
 {
  qDebug( "Error al ejecutar la cola tam" );
  return false;
 }
 if( !tam.next() )
 {
  qDebug( "error en el next tam" );
  return false;
 }
 int cant_tablas = tam.record().value( 0 ).toInt();
 PBProgreso->setRange( 0, cant_tablas + 3 );
 // Intento nuevo
 datos->append( "|->basedatossql->\n" );
 datos->append( "BEGIN TRANSACTION;\n" );
 QSqlQuery cola( "SELECT name, sql FROM sqlite_master WHERE type='table'" );
 while( cola.next() )
 {
  if( estructura )
  {
   datos->append( cola.record().value( "sql" ).toString() + "\n" );
  }
  // Calculo de la cantidad de campos
  tam.prepare( QString( "SELECT COUNT(*) FROM %1" ).arg( cola.record().value( "name" ).toString() ) );
  if( !tam.exec() )
  {
   qDebug( "Error de calculo de registros" );
   qDebug( tam.executedQuery().toLocal8Bit() );
  }
  QString inicio( "INSERT INTO %1 VALUES ( " );
  QSqlQuery cola1( QString( "SELECT * FROM %1" ).arg( cola.record().value( "name" ).toString() ) );
  while( cola1.next() )
  {
   inicio = "INSERT INTO ";
   QSqlRecord reg = cola1.record();
   inicio.append( cola.record().value( "name" ).toString() );
   inicio.append(  " VALUES ( " );
   for( int i = 0; i< reg.count(); i++ )
   {
    switch( reg.field( i ).type() )
    {
	case QVariant::String:
	{
		inicio.append( "'" );
		inicio.append( reg.value( i ).toString() );
		inicio.append( "'" );
		break;
	}
	case QVariant::Double:
	case QVariant::Int:
	{
	        inicio.append( "'" );
		inicio.append( reg.value( i ).toString() );
		inicio.append( "'" );
		break;
	}
	case QVariant::Date:
	{
		inicio.append( "'" );
		inicio.append( reg.value( i ).toDate().toString( "yyyy-MM-dd") );
		inicio.append( "'" );
		break;
	}
	case QVariant::ByteArray:
	{
	       inicio.append( "'" );
	       inicio.append( QString( reg.value( i ).toByteArray() ) );
	       inicio.append( "'" );
	       break;
	}
	case QVariant::UserType:
	{
	       qDebug( "Tipo predefinido" );
	       inicio.append( "''" );
	       break;
	}
	default:
	{
		inicio.append( "'" );
		qDebug( QString( "Tipo de campo: %1, campo: %2" ).arg( reg.field( i ).type() ).arg( i ).toLocal8Bit() );
		inicio.append( reg.value( i ).toString() );
		inicio.append( "'" );
		break;
	}
    }
    if( i < reg.count() -1 )
    {
     inicio.append( ", " );
    }
   }
   inicio.append( ");\n" );
   datos->append( inicio );
   inicio.clear();
  }
  PBProgreso->setValue( PBProgreso->value() + 1 );
 }
 datos->append( "COMMIT;\n" );
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
 if( ChBCompri->isChecked() )
 {
  /*comprimidos->append( qCompress( *datos ) );*/
  comprimidos->append( *datos );
 }
 else
 {
  comprimidos->append( *datos );
 }
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
 if( !destino->open( QIODevice::ReadWrite ) )
 {
	qDebug( "Error al abrir el archivo en modo lectura escritura" );
	return false;
 }

 qint64 escritos = destino->write( *comprimidos );
 if( escritos != comprimidos->size() )
 {
  qDebug( "Las cantidades de bytes no coinciden" );
  qDebug( QString( "Bytes escritos: %1, Bytes de buffer: %2" ).arg(escritos).arg(comprimidos->size()).toLocal8Bit() );
  destino->flush();
  destino->close();
  return false;
 }
 else
 {
  destino->flush();
  destino->close();
  return true;
 }
}
